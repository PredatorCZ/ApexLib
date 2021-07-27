/*  Apex Engine Format Library
    Copyright(C) 2014-2020 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#include "adf.hpp"
#include "apex/adf_instance.hpp"
#include "datas/binreader.hpp"
#include "datas/except.hpp"
#include "datas/fileinfo.hpp"
#include "datas/master_printer.hpp"

constexpr uint32 ADFID = CompileFourCC(" FDA");

ADFInstanceInternal *ADFInternal::FindRawInstance(JenHash3 hash,
                                                  size_t numSkips) {
  size_t currentSkip = 0;

  for (auto &i : instances) {
    if (i.typeHash == hash ||
        (i.instance && i.instance->GetSuperClass() == hash)) {
      if (currentSkip == numSkips) {
        return &i;
      } else {
        currentSkip++;
      }
    }
  }

  return nullptr;
}

ADFInstance *ADFInternal::FindInstance(JenHash3 hash, size_t numSkips) {
  ADFInstanceInternal *rInst = FindRawInstance(hash, numSkips);

  return rInst ? rInst->instance.get() : nullptr;
}

const StringHash &ADFInternal::AddStringHash(es::string_view input) {
  JenHash3 hash(input);
  auto foundString = hashes.find(hash);

  if (es::IsEnd(hashes, foundString)) {
    hashes.emplace(input.to_string());
  }

  return *foundString;
}

const std::string &ADFInternal::FindString(JenHash3 hash) {
  return FindStringHash(hash).string;
}

const StringHash &ADFInternal::FindStringHash(JenHash3 hash) {
  auto foundString = hashes.find(hash);

  if (es::IsEnd(hashes, foundString)) {
    throw std::out_of_range("String not found.");
  }

  return *foundString;
}

void ADFInternal::AddInstance(std::unique_ptr<ADFInstance> &&instance,
                              const StringHash &hash) {
  instances.emplace_back(hash, std::move(instance));
}

void AdfExternalString::Fixup(ADFInternal &base) {
  sh = *base.names.find(externalIndex);
}

/************************************************************************/
/***************************** LOADING **********************************/
/************************************************************************/

void ADFDescriptorBase::Load(BinReaderRef rd, ADFInternal &) {
  rd.Read(numMembers);
}

void ADFDescriptorStructure::Load(BinReaderRef rd, ADFInternal &base) {
  ADFDescriptorBase::Load(rd, base);
  members.resize(numMembers);

  for (auto &m : members) {
    rd.Read(m);
    m.name.Fixup(base);
  }
}

void ADFDescriptorExplicitEnum::Load(BinReaderRef rd, ADFInternal &base) {
  ADFDescriptorBase::Load(rd, base);
  members.resize(numMembers);

  for (auto &m : members) {
    rd.Read(m);
    m.name.Fixup(base);
  }
}

void ADFDescriptor::Load(BinReaderRef rd) {
  rd.Read<ADFDescriptorData>(*this);

  if (type == ADFDescriptorType::Structure) {
    polyData = std::make_unique<ADFDescriptorStructure>();
  } else if (type == ADFDescriptorType::Enumeration) {
    polyData = std::make_unique<ADFDescriptorExplicitEnum>();
  } else {
    polyData = std::make_unique<ADFDescriptorBase>();
  }

  return polyData->Load(rd, main);
}

void ADFInternal::Load(BinReaderRef rd) {
  rd.Push();
  rd.Read<ADFData>(*this);

  if (ID != ADFID) {
    rd.Pop();
    throw es::InvalidHeaderError(ID);
  }

  rd.ReadString(comment);

  if (hashesOffset) {
    rd.Seek(hashesOffset);
    std::string tmpName;

    for (size_t i = 0; i < numHashes; i++) {
      rd.ReadString(tmpName);
      JenHash3 jh;
      rd.Read(jh);
      rd.Skip<uint32>();

      hashes.emplace(tmpName);
    }
  }

  if (namesOffset) {
    rd.Seek(namesOffset + numNames);
    std::string tmpName;

    for (size_t i = 0; i < numNames; i++) {
      rd.ReadString(tmpName);
      names.emplace(tmpName, i);
    }
  }

  if (definitionsOffset) {
    rd.Seek(definitionsOffset);

    for (size_t i = 0; i < numDefinitions; i++) {
      ADFDescriptor cDesc(*this);
      cDesc.Load(rd);
      descriptors.emplace(cDesc.nameHash, std::move(cDesc));

      /*if (result)
      {
              printerror("[ADF] Could load descriptor: ",
                      << i.name->string.c_str() << " type: "
                      << (static_cast<int>(i.type) <
      _EnumWrap<ADFDescriptorType>::_reflectedSize ?
      _EnumWrap<ADFDescriptorType>{}._reflected[static_cast<int>(i.type)] :
      "Undefined")); break;
      }*/
    }
  }

  if (instancesOffset) {
    rd.Seek(instancesOffset);

    for (size_t i = 0; i < numInstances; i++) {
      instances.emplace_back();
      rd.Read<ADFInstanceInternalData>(instances.back());
      instances.back().name.Fixup(*this);
    }

    for (auto &i : instances) {
      if (InstanceContructoreExits(i.typeHash)) {
        rd.Seek(i.offset);
        rd.ReadContainer(i.instanceBuffer, i.size);
        i.instance = ConstructInstance(i.typeHash, &i.instanceBuffer[0]);
        i.instance->Fixup(&i.instanceBuffer[0]);
      } else {
        const std::string *clname = nullptr;
        auto fnd = descriptors.find(i.typeHash);

        if (!es::IsEnd(descriptors, fnd)) {
          clname = &fnd->second.name->string;
        }

        printwarning("[ADF] Uregistered class: "
                     << (clname ? *clname : _T("")) << _T(" (0x") << std::hex
                     << i.typeHash << std::dec << ')');
      }
    }
  }
}

static StringHash dummyHash{"__dummy__"};

ADF::ptr ADF::Create(const std::string &fileName) {
  BinReader rd(fileName);
  auto adf = std::make_unique<ADFInternal>();

  try {
    adf->Load(rd);
  } catch (es::InvalidHeaderError &) {
    adf->LoadAsRenderBlockModel(rd);
  }

  AFileInfo selfPath(fileName);

  for (auto it = adf->instances.begin(); it != adf->instances.end(); it++) {
    if (!it->instance) {
      continue;
    }

    auto rFile = it->instance->RequestsFile();

    if (rFile.empty()) {
      continue;
    }

    AFileInfo reqPath(rFile);
    auto rPath = reqPath.CatchBranch(selfPath.GetFolder());
    auto exAdf = Create(rPath);

    if (exAdf) {
      continue;
    }
    ADFInternal *extAdf = static_cast<ADFInternal *>(exAdf.get());

    if (extAdf->instances.empty()) {
      continue;
    }

    for (auto &h : extAdf->hashes) {
      auto nHash = adf->hashes.emplace(h.hash);
      nHash.first->string.swap(h.string);
    }

    for (auto &exInstance : extAdf->instances) {
      auto foundIntance = adf->FindRawInstance(exInstance.typeHash);

      if (foundIntance && *foundIntance->name != dummyHash) {
        foundIntance->instance->Merge(exInstance.instance.get());

        ADFInstanceInternal newInstance;
        newInstance.name.sh = dummyHash;
        newInstance.instanceBuffer.swap(exInstance.instanceBuffer);
        adf->instances.emplace_back(std::move(newInstance));
      } else {
        if (exInstance.instance) {
          exInstance.instance->ReplaceReferences(adf.get());
        }

        if (*exInstance.name != dummyHash) {
          adf->names.emplace(*exInstance.name);
        }

        adf->instances.emplace_back(std::move(exInstance));
      }
    }
  }

  return std::move(adf);
}
