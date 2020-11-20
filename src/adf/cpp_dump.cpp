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

#include "../adf.hpp"
#include "datas/pugiex.hpp"
#include <iomanip>
#include <sstream>

extern const std::map<JenHash3, es::string_view> types;

struct CPPSettingsInternal : ADFCPPGenSettings {
  std::vector<std::string> oreg;
};
/*
int ADF::ExportDefinitionsToCPP(std::ostream &str) const
{
        CPPRegistry classes;

        for (auto &d : descriptors)
                d.CPPDump(classes);

        bool useBitFields = false;

        for (auto &d : descriptors)
                if (d.type == ADFDescriptorType::BitField)
                {
                        useBitFields = true;
                        break;
                }

        str << "// ApexLib ADF generated header file.\n\n#pragma once\n";

        if (useBitFields)
                str << "#include \"datas/flags.hpp\"\n\n";

        for (CPPRegistry::reverse_iterator it = classes.rbegin(); it !=
classes.rend(); it++)
        {
                str << **it;
                delete *it;
        }

        return 0;
}

int ADF::ExportDefinitionsToCPP(const char *fileName) const
{
        std::ofstream str(fileName);
        ExportDefinitionsToCPP(str);
        return 0;
}

void ADF::Descriptor::CPPDump(CPPRegistry &classes) const
{
        descriptorData->CPPDump(this, classes);
}*/

void ADFDescriptorExplicitEnum::Save(const ADFDescriptor *main,
                                     CPPSettingsInternal &settings) const {
  std::stringstream str;

  str << "enum ";

  if (settings.enumClass) {
    str << "class ";
  }

  str << main->name->string;

  switch (main->size) {
  case 1:
    str << " : uint8";
    break;
  case 2:
    str << " : uint16";
    break;
  case 4:
    str << " : uint32";
    break;
  case 8:
    str << " : uint64";
    break;
  }

  str << " {\n";

  int32 cNumber = -1, sNumber = 0;

  for (auto &m : members) {
    if (cNumber < 0) {
      cNumber = m.value;
      sNumber = cNumber;
    } else if (m.value == cNumber + 1) {
      cNumber++;
    } else {
      cNumber = -1;
      break;
    }
  }

  cNumber = ~cNumber; // isLinear

  for (auto &m : members) {
    str << std::setfill(settings.indentType) << std::setw(settings.numIndents)
        << m.name->string;

    if (!cNumber || sNumber) {
      str << " = " << m.value;

      if (sNumber) {
        sNumber = 0;
      }
    }

    str << ",\n";
  }

  str << "};\n";

  settings.oreg.emplace_back(str.str());
}

void ADFDescriptorBase::Save(const ADFDescriptor *main,
                             CPPSettingsInternal &settings) const {}

std::ostream &PrintVarName(std::ostream &str, const char *varName) {
  if (!varName[1] || isupper(varName[1]) != 0)
    str << varName;
  else
    str << static_cast<char>(tolower(*varName)) << varName + 1;

  return str;
}

bool GetTypeName(const JenHash3 hash, const ADFDescriptor *main,
                 std::ostream &str, const char *varName = nullptr) {
  auto foundPredefined = types.find(hash);

  if (!es::IsEnd(types, foundPredefined)) {
    str << foundPredefined->second;
    return false;
  }

  auto foundDynamic = main->main.descriptors.find(hash);

  if (es::IsEnd(main->main.descriptors, foundDynamic)) {
    return false;
  }

  auto &dt = foundDynamic->second;

  switch (dt.type) {
  case ADFDescriptorType::Array:
    str << "AdfArray<";
    GetTypeName(dt.elementTypeHash, main, str);
    str << '>';
    return false;
  case ADFDescriptorType::StringHash:
    str << "JenHash3";
    return false;
  case ADFDescriptorType::String:
    str << "AdfString";
    return false;
  case ADFDescriptorType::Structure: {
    str << dt.name->string;
    break;
  }
  case ADFDescriptorType::InlineArray: {
    if (dt.elementTypeHash == 0x7515A207 && dt.elementSize > 1 &&
        dt.elementSize < 5) // float
    {
      str << "Vector";

      if (dt.elementSize != 3) {
        str << dt.elementSize;
      }

      if (varName) {
        PrintVarName(str << ' ', varName);
      }

      str << ";\n";
    } else {
      GetTypeName(dt.elementTypeHash, main, str);

      if (varName) {
        PrintVarName(str << ' ', varName);
      }

      str << '[' << dt.elementSize << "];\n";
    }

    return varName != nullptr;
  }
  }

  return false;
}

void ADFDescriptorStructure::Save(const ADFDescriptor *main,
                                  CPPSettingsInternal &settings) const {
  std::stringstream str;

  str << "struct " << main->name->string << " {\n";

  JenHash3 lastType(0);
  std::vector<std::vector<const Member *>> bitFields;

  for (auto &m : members) {
    str << '\t';

    ADFDescriptor *subDesc = nullptr;

    auto foundDynamic = main->main.descriptors.find(m.typeHash);

    if (!es::IsEnd(main->main.descriptors, foundDynamic)) {
      subDesc = &foundDynamic->second;
    }

    if (m.typeHash == lastType) {
      if (subDesc && subDesc->type == ADFDescriptorType::BitField) {
        (*(bitFields.end() - 1)).push_back(&m);
        str.seekp(-1, std::ios_base::cur);
        lastType = m.typeHash;
        continue;
      }

      str.seekp(-3, std::ios_base::cur);
      str << ",\n\t\t";
      PrintVarName(str, m.name->string.c_str());

      if (subDesc && subDesc->type == ADFDescriptorType::InlineArray &&
          (subDesc->elementTypeHash != 0x7515A207 || subDesc->elementSize < 2 ||
           subDesc->elementSize > 4)) {
        str << '[' << subDesc->elementSize << ']';
        break;
      }

      str << ";\n";
    } else {
      if (subDesc && subDesc->type == ADFDescriptorType::BitField) {
        bitFields.push_back({});
        (*(bitFields.end() - 1)).push_back(&m);
        str << "esFlags<";

        switch (subDesc->size) {
        case 1:
          str << "char";
          break;
        case 2:
          str << "short";
          break;
        case 4:
          str << "int";
          break;
        case 8:
          str << "int64";
          break;
        }

        str << ", " << main->name->string << "_flags" << bitFields.size() - 1
            << "> flags" << bitFields.size() - 1 << ";\n";
        lastType = m.typeHash;
        continue;
      }

      bool alreadyWritten =
          GetTypeName(m.typeHash, main, str, m.name->string.c_str());

      if (!alreadyWritten) {
        PrintVarName(str << ' ', m.name->string.c_str()) << ";\n";
      }
    }

    lastType = m.typeHash;
  }

  str << "\n\tstatic const ApexHash HASH = 0x" << std::hex << std::uppercase
      << main->nameHash << std::dec << ";\n};\n\nstatic_assert(sizeof("
      << main->name->string << ") == " << main->size
      << ", \"Check assumptions\");\n\n";

  settings.oreg.emplace_back(str.str());

  int currentBitField = 0;

  for (auto &f : bitFields) {
    str = std::stringstream();
    str << "enum " << main->name->string << "Flags" << currentBitField
        << " {\n";

    for (auto &b : f) {
      PrintVarName(str << '\t', b->name->string.c_str()) << ",\n";
    }

    str << "};\n\n";
    currentBitField++;
    settings.oreg.emplace_back(str.str());
  }
}
