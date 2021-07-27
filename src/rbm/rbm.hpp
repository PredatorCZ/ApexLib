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

#pragma once
#include "../adf/amf_codec.hpp"
#include "apex/adf_deferred.hpp"
#include "apex/adf_string.hpp"
#include "apex/amf.hpp"
#include "datas/bincore_fwd.hpp"

union RBMHash {
  uint64 data;
  struct {
    uint32 hash;
    uint8 version;
    uint8 shaderType;
  } innerData;
};

struct RBMBBOX {
  Vector max, min;
};

struct RBMHeader {
  uint32 versionmajor;
  uint32 versionminor;
  uint32 revision;
  RBMBBOX bbox;
  uint32 numblocks;
};

struct RBNHeader {
  uint32 versionmajor;
  uint32 versionminor;
  uint32 revision;
  uint32 numblocks;
  uint32 rbshash;
};

struct RBMRemapHeader {
  uint32 numTables, numFaces, null, numRemaps;
};

class RBMMesh : public AmfMesh, public uni::Primitive {
public:
  uint32 numVertices, numIndices;
  char *indexBuffer;
  AmfCodecs descriptors;
  StringHash meshName;
  AdfDeferred properties;
  std::string meshType;

  RBMMesh() : numVertices(), numIndices(), indexBuffer(), meshType() {}

  size_t GetNumTotalIndices() const override { return numIndices; }
  const std::string &GetMeshTypeName() const override { return meshType; }
  bool IsValid() const override { return true; }
  size_t Size() const override { return 1; }
  const_type At(size_t id) const override { return {this, false}; }
  size_t GetNumRemaps() const override { return 0; }
  size_t GetRemap(size_t id) const override { return 0; }
  const void *GetRemaps() const override { return nullptr; }
  AmfMeshRemapType GetRemapType() const override { return REMAP_TYPE_CHAR; }
  refptr GetReflectedAttributes() const override {
    return properties.GetReflected();
  }

  const char *RawIndexBuffer() const override { return indexBuffer; }
  uni::PrimitiveDescriptorsConst Descriptors() const override {
    return {&descriptors, false};
  }
  IndexType_e IndexType() const override { return IndexType_e::Triangle; }
  size_t IndexSize() const override { return 2; }
  size_t NumVertices() const override { return numVertices; }
  size_t NumIndices() const override { return numIndices; }
  const std::string &Name() const override { return meshName.string; }

  virtual size_t GetPropertiesSize() const { return 0; }

  static RBMMesh *ConstructClass(uint64 classHash);
  const char *AddDescriptor(AmfStreamAttribute &attr, const char *buffer) {
    AmfCodec cCod;
    cCod.attr = attr;
    cCod.vertexBuffer = buffer;
    descriptors.storage.emplace_back(std::move(cCod));
    return buffer + AmfFormatStrides[cCod.attr.format];
  }
};

class RBSMesh : public RBMMesh {
public:
  char *vtBuffers[3];
  uint32 vtBuffersStrides[3];
  uint32 numVBO;
  RBMHash blockHash;
  std::vector<uint8> boneIndexLookup;

  RBSMesh() : vtBuffers(), vtBuffersStrides() {}

  size_t GetNumRemaps() const override { return boneIndexLookup.size(); }
  size_t GetRemap(size_t id) const override { return boneIndexLookup[id]; }
  const void *GetRemaps() const override { return boneIndexLookup.data(); }
  const char *RawVertexBuffer(size_t id) const override {
    return vtBuffers[id];
  }
  size_t NumVertexBuffers() const override { return numVBO; }
};

class RBMMeshHeader : public AmfMeshHeader {
public:
  std::vector<std::unique_ptr<RBMMesh>> meshes;

  void Fixup(char *) override {}
  JenHash3 GetSuperClass() const override { return AmfMeshHeader::GetHash(); }

  size_t GetNumLODs() const override { return 1; }
  size_t GetLodIndex(size_t id) const override { return 0; }
  size_t GetNumLODMeshes(size_t LODIndex) const override {
    return meshes.size();
  }
  AmfMesh::Ptr GetLODMesh(size_t LODIndex, size_t meshIndex) const override {
    return {meshes[meshIndex].get(), false};
  }
  void ReplaceReferences(ADFInternal *newMain) override;
};

class RBSMeshHeader : public RBMMeshHeader {
public:
  std::string masterBuffer;
};

class RBMMaterial : public AmfMaterial {
public:
  std::vector<std::string> textures;
  AmfMaterialType materialType;
  StringHash name;
  mutable AdfDeferred properties;
  StringHash meshType;

  RBMMaterial();

  AmfMaterialType MaterialType() const override { return materialType; }
  void MaterialType(AmfMaterialType ntype) override { materialType = ntype; }
  const std::string &GetName() const override { return name.string; }
  const std::string &GetRenderBlockName() const override {
    return meshType.string;
  }
  JenHash3 GetNameHash() const override { return name.hash; }
  JenHash3 GetRenderBlockNameHash() const override { return meshType.hash; }
  refptr GetReflectedAttributes() const override {
    return properties.GetReflected();
  }
  void *GetRawAttributes() const override { return properties.item; }
  JenHash3 GetAttributesHash() const override { return properties.objectHash; }
  size_t GetNumTextures() const override { return textures.size(); }
  const std::string &GetTexture(size_t id) const override {
    return textures.at(id);
  }

  void ReadTextures(BinReaderRef rd, uint32 numTextures = 0);

  virtual size_t GetPropertiesSize() const { return 0; }
  virtual size_t GetNumTexturesToRead() const { return 0; }
  virtual void ReadRBM(BinReaderRef rd, char *&curBuffer, RBMMesh &mesh) = 0;

  static RBMMaterial *ConstructClass(uint64 classHash);
};

class RBMModel : public AmfModel {
public:
  std::string masterBuffer;

  std::vector<std::unique_ptr<RBMMaterial>> materials;

  size_t GetNumMaterials() const override { return materials.size(); }
  AmfMaterial::Ptr GetMaterial(size_t id) const override {
    return {materials[id].get(), false};
  }

  void Fixup(char *) override {}
  JenHash3 GetSuperClass() const override { return AmfModel::GetHash(); }
};

class RBNModel : public RBMModel {
public:
  std::string meshFile;
  es::string_view RequestsFile() const override { return meshFile; }
};

inline void ApplyPadding(char *&buffer, size_t alignment = 8) {
  buffer += GetPadding(reinterpret_cast<uintptr_t>(buffer), alignment);
}
