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

#include "rbm.hpp"
#include "../adf/adf.hpp"
#include "datas/binreader_stream.hpp"
#include "datas/except.hpp"

struct PrecalcBuffer {
  size_t offset;
  size_t size;

  PrecalcBuffer() = default;
  PrecalcBuffer(size_t offset_, size_t size_) : offset(offset_), size(size_) {}
};

static const StringHash RBSDLName("RBSDL");
static const StringHash RBNDLName("RBNDL");
static const StringHash RBMDLName("RBMDL");
static const StringHash RBMSHName("RBMSH");

void LoadRBSDL(ADFInternal *master, BinReaderRef rd) {
  RBMHeader hdr;
  rd.Read(hdr);

  auto meshHeader = std::make_unique<RBSMeshHeader>();

  std::vector<PrecalcBuffer> buffers;
  buffers.reserve(hdr.numblocks * 2);
  size_t totalBufferSize = 0;

  for (uint32 b = 0; b < hdr.numblocks; b++) {
    auto nMesh = std::make_unique<RBSMesh>();

    rd.Read(nMesh->blockHash.innerData.hash);
    rd.Read(nMesh->blockHash.innerData.version);
    rd.Read(nMesh->numVBO);

    for (uint32 b = 0; b < nMesh->numVBO; b++) {
      rd.Read(nMesh->vtBuffersStrides[b]);
      rd.Read(nMesh->numVertices);
      rd.ApplyPadding(8);

      const uint32 vtBufSize = nMesh->vtBuffersStrides[b] * nMesh->numVertices;
      buffers.emplace_back(rd.Tell(), vtBufSize);
      totalBufferSize += vtBufSize;
      rd.Skip(vtBufSize);
    }

    rd.Skip(4);
    rd.Read(nMesh->numIndices);
    rd.ApplyPadding(8);
    const size_t bSize = nMesh->numIndices * sizeof(uint16);
    buffers.emplace_back(rd.Tell(), bSize);
    totalBufferSize += bSize;
    rd.Skip(bSize);

    JenHash3 endHash;
    rd.Read(endHash);

    if (endHash != 0x456bcdef) {
      throw std::runtime_error("Unexpected end of block at: " +
                               std::to_string(rd.Tell() - 4));
    }

    meshHeader->meshes.emplace_back(std::move(nMesh));
  }

  size_t curBuffer = 0;
  meshHeader->masterBuffer.resize(totalBufferSize);
  char *buff = &meshHeader->masterBuffer[0];

  for (auto &m : meshHeader->meshes) {
    auto mm = static_cast<RBSMesh *>(m.get());

    for (uint32 v = 0; v < mm->numVBO; v++) {
      auto &bufPart = buffers[curBuffer++];
      rd.Seek(bufPart.offset);
      rd.ReadBuffer(buff, bufPart.size);
      mm->vtBuffers[v] = buff;
      buff += bufPart.size;
    }

    mm->indexBuffer = buff;
    auto &bufPart = buffers[curBuffer++];
    rd.Seek(bufPart.offset);
    rd.ReadBuffer(buff, bufPart.size);
    buff += bufPart.size;
  }

  master->AddInstance(std::move(meshHeader), RBSDLName);
}

void LoadRBMDL(ADFInternal *master, BinReaderRef rd) {
  RBMHeader hdr;
  rd.Read(hdr);

  if (hdr.versionminor > 13) {
    rd.Skip(4);
  }

  auto cModel = std::make_unique<RBMModel>();
  auto meshHeader = std::make_unique<RBMMeshHeader>();
  std::vector<PrecalcBuffer> buffers;
  buffers.reserve(hdr.numblocks * 4);
  size_t totalBufferSize = 0;

  for (uint32 b = 0; b < hdr.numblocks; b++) {
    RBMHash hash = {};
    rd.Read(hash.innerData.hash);
    rd.Read(hash.innerData.version);

    RBMMaterial *cMat = RBMMaterial::ConstructClass(hash.data);
    RBMMesh *cMesh = RBMMesh::ConstructClass(hash.data);

    if (!cMesh || !cMat) {
      throw std::runtime_error("Unregistered render block model " +
                               std::to_string(hash.innerData.hash) +
                               " version " +
                               std::to_string(hash.innerData.version) +
                               " at: " + std::to_string(rd.Tell() - 4));
    }

    cModel->materials.emplace_back(cMat);
    meshHeader->meshes.emplace_back(cMesh);
    cMat->materialType =
        hdr.versionminor < 14 ? MaterialType_Traditional : MaterialType_PBR;

    const size_t attributtesSize = cMat->GetPropertiesSize();
    const size_t numTextures = cMat->GetNumTexturesToRead();
    const size_t meshAttributtesSize = cMesh->GetPropertiesSize();

    buffers.emplace_back(rd.Tell(), attributtesSize);
    rd.Skip(attributtesSize);
    totalBufferSize += attributtesSize + GetPadding(attributtesSize, 4);

    cMat->ReadTextures(rd, numTextures);

    buffers.emplace_back(rd.Tell(), meshAttributtesSize);
    rd.Skip(meshAttributtesSize);
    totalBufferSize += meshAttributtesSize + GetPadding(meshAttributtesSize, 4);
    rd.ApplyPadding(8);

    // cMat->ReadRBM(rd, *cMesh);

    cMesh->meshType = cMat->GetRenderBlockName();

    std::string noName = std::to_string(b);
    std::string fullName = "Object000";
    fullName.replace(9 - noName.size(), noName.size(), noName);
    cMat->name = fullName;
    cMesh->meshName.string = std::move(fullName);
    cMesh->meshName.hash = cMat->name.hash;

    JenHash3 endHash;
    rd.Read(endHash);

    if (endHash != 0x89ABCDEF) {
      throw std::runtime_error("Unexpected end of block at: " +
                               std::to_string(rd.Tell() - 4));
    }
  }

  master->AddInstance(std::move(cModel), RBMDLName);
  master->AddInstance(std::move(meshHeader), RBMSHName);
}

void LoadRBNDL(ADFInternal *master, BinReaderRef rd) {
  RBNHeader hdr;
  rd.Read(hdr);

  auto cModel = std::make_unique<RBNModel>();

  rd.ReadContainer(cModel->meshFile);
  rd.ApplyPadding(8);

  std::vector<PrecalcBuffer> buffers;
  buffers.reserve(hdr.numblocks * 4);
  size_t totalBufferSize = 0;

  for (uint32 b = 0; b < hdr.numblocks; b++) {
    RBMHash hash = {};
    rd.Read(hash.innerData.hash);
    rd.Read(hash.innerData.version);

    RBMMaterial *cMat = RBMMaterial::ConstructClass(hash.data);

    if (!cMat) {
      throw std::runtime_error("Unregistered render block model " +
                               std::to_string(hash.innerData.hash) +
                               " version " +
                               std::to_string(hash.innerData.version) +
                               " at: " + std::to_string(rd.Tell() - 4));
    }

    const size_t attributtesSize = cMat->GetPropertiesSize();

    cModel->materials.emplace_back(cMat);
    buffers.emplace_back(rd.Tell(), attributtesSize);
    rd.Skip(attributtesSize);
    totalBufferSize += attributtesSize + GetPadding(attributtesSize, 4);
    cMat->ReadTextures(rd);
    rd.Skip(8); // rbsHash + meshIndex

    std::string noName = std::to_string(b);
    std::string fullName = "Object000";
    fullName.replace(9 - noName.size(), noName.size(), noName);
    cMat->name = fullName;
    cMat->materialType = MaterialType_PBR;

    JenHash3 endHash;
    rd.Read(endHash);

    if (endHash != 0x123bcdef) {
      throw std::runtime_error("Unexpected end of block at: " +
                               std::to_string(rd.Tell() - 4));
    }
  }

  size_t curBuffer = 0;
  cModel->masterBuffer.resize(totalBufferSize);
  char *buff = &cModel->masterBuffer[0];

  for (auto &m : cModel->materials) {
    auto &bufPart = buffers[curBuffer++];
    rd.Seek(bufPart.offset);
    rd.ReadBuffer(buff, bufPart.size);
    m->properties.item = buff;
    buff += bufPart.size;
  }

  master->AddInstance(std::move(cModel), RBNDLName);
}

void ADFInternal::LoadAsRenderBlockModel(BinReaderRef rd) {
  uint32 numChars;
  rd.Read(numChars);

  if (numChars != 5) {
    throw es::InvalidHeaderError(numChars);
  }

  char ID[6]{};
  rd.ReadBuffer(ID, 5);
  es::string_view id = ID;

  if (id == RBMDLName.string) {
    LoadRBMDL(this, rd);
  } else if (id == RBSDLName.string) {
    LoadRBSDL(this, rd);
  } else if (id == RBNDLName.string) {
    LoadRBNDL(this, rd);
  } else {
    throw es::InvalidHeaderError(id);
  }
}

void RBMMaterial::ReadTextures(BinReaderRef rd, uint32 numTextures) {
  if (!numTextures) {
    rd.Read(numTextures);
  }

  rd.ReadContainerLambda(textures, numTextures,
                         [](auto rd, auto &item) { rd.ReadContainer(item); });

  rd.ApplyPadding(8);
}
