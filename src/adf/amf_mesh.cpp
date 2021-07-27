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

#include "amf_mesh.hpp"
#include "adf.hpp"
#include "amf_codec.hpp"
#include "amf_mesh_v1.hpp"
#include "amf_mesh_v2.hpp"
#include "uni/list_vector.hpp"

template <class C> class AmfPrimitiveWrap : public uni::Primitive {
public:
  const char *indexBuffer;
  const char *vertexBuffers[4];
  C *data;
  size_t numIndices, numVBO;
  const std::string *name;

  const char *RawIndexBuffer() const override { return indexBuffer; }
  const char *RawVertexBuffer(size_t id) const override {
    return vertexBuffers[id];
  }
  uni::PrimitiveDescriptorsConst Descriptors() const override {
    auto desc = new AmfCodecs;

    for (auto &a : data->streamAttributes) {
      AmfCodec cCod;
      cCod.attr = a;
      cCod.vertexBuffer = vertexBuffers[a.streamIndex] +
                          data->vertexStreamOffsets[a.streamIndex] +
                          a.streamOffset;

      desc->storage.emplace_back(cCod);
    }

    return uni::PrimitiveDescriptorsConst{desc};
  }
  IndexType_e IndexType() const override { return IndexType_e::Triangle; }
  size_t IndexSize() const override { return 2; }
  size_t NumVertices() const override { return data->vertexCount; }
  size_t NumVertexBuffers() const override { return numVBO; }
  size_t NumIndices() const override { return numIndices; }
  const std::string &Name() const override { return *name; }
};

class AmfMesh_V1_wrap : public AmfMesh {
  AmfMesh_V1 *data;
  AmfMeshBuffers *buffers;
  char *indexBuffer;
  ADFInternal *main;
  std::vector<AmfPrimitiveWrap<AmfMesh_V1>> storage;

public:
  AmfMesh_V1_wrap(AmfMesh_V1 *imesh, ADFInternal *base,
                  AmfMeshBuffers *buffers_)
      : data(imesh), main(base), buffers(buffers_) {
    char *indexBuffer = nullptr;

    if (buffers) {
      indexBuffer = buffers->GetIndexBuffer(data->indexBufferIndex) +
                    data->indexBufferOffset;
    }

    for (auto &s : data->subMeshes) {
      AmfPrimitiveWrap<AmfMesh_V1> cPrim;
      cPrim.indexBuffer = indexBuffer + s.indexStreamOffset;
      cPrim.numIndices = s.indexCount;
      cPrim.name = &main->FindString(s.subMeshID);
      cPrim.data = data;
      if (buffers) {
        cPrim.numVBO = data->vertexBufferIndices.count;

        for (size_t v = 0; v < cPrim.numVBO; v++) {
          cPrim.vertexBuffers[v] =
              buffers->GetVertexBuffer(data->vertexBufferIndices[v]);
        }
      }

      storage.emplace_back(std::move(cPrim));
    }
  }

  size_t GetNumTotalIndices() const override { return data->indexCount; }
  const std::string &GetMeshTypeName() const override {
    return main->FindString(data->MeshTypeId);
  }
  bool IsValid() const override {
    if (!buffers || data->indexBufferIndex >= buffers->GetNumIndexBuffers()) {
      return false;
    }

    for (auto &a : data->streamAttributes) {
      if (data->vertexBufferIndices[a.streamIndex] >=
          buffers->GetNumVertexBuffers()) {
        return false;
      }
    }

    return true;
  }
  AmfMeshRemapType GetRemapType() const override { return REMAP_TYPE_SHORT; }
  size_t GetNumRemaps() const override { return data->boneIndexLookup.count; }
  size_t GetRemap(size_t id) const override {
    return data->boneIndexLookup[id];
  }
  const void *GetRemaps() const override { return data->boneIndexLookup.items; }
  refptr GetReflectedAttributes() const override {
    return data->meshProperties.GetReflected();
  }

  size_t Size() const override { return storage.size(); }
  const_type At(size_t id) const override { return {&storage.at(id), false}; }
};

AmfMeshHeader_V1_wrap::AmfMeshHeader_V1_wrap(void *data_, ADFInternal *main_)
    : data(static_cast<AmfMeshHeader_V1 *>(data_)), main(main_), buffers() {}

size_t AmfMeshHeader_V1_wrap::GetNumLODs() const {
  return data->lodGroups.count;
}
size_t AmfMeshHeader_V1_wrap::GetLodIndex(size_t id) const {
  return data->lodGroups.items[id].index;
}
size_t AmfMeshHeader_V1_wrap::GetNumLODMeshes(size_t LODIndex) const {
  return data->lodGroups.items[LODIndex].meshes.count;
}
AmfMesh::Ptr AmfMeshHeader_V1_wrap::GetLODMesh(size_t LODIndex,
                                               size_t meshIndex) const {
  if (!buffers) {
    AmfMeshBuffers *bufWrap = main->FindInstance<AmfMeshBuffers>();

    if (bufWrap) {
      buffers = bufWrap;
    }
  }

  return AmfMesh::Ptr{new AmfMesh_V1_wrap(
      &data->lodGroups.items[LODIndex].meshes.items[meshIndex], main, buffers)};
}

void AmfMeshHeader_V1_wrap::Fixup(char *masterBuffer) {
  data->Fixup(masterBuffer);
}
es::string_view AmfMeshHeader_V1_wrap::RequestsFile() const {
  return main->FindString(data->highLod);
}

AmfMeshBuffers_V1_wrap::AmfMeshBuffers_V1_wrap(void *data_, ADFInternal *)
    : data(static_cast<AmfMeshBuffers_V1 *>(data_)) {}
void AmfMeshBuffers_V1_wrap::Fixup(char *masterBuffer) {
  data->Fixup(masterBuffer);
}

void AmfMeshBuffers_V1_wrap::Merge(ADFInstance *externalInstance) {
  AmfMeshBuffers_V1_wrap *inst =
      static_cast<AmfMeshBuffers_V1_wrap *>(externalInstance);
  AmfMeshBuffers_V1 *thisData = Data();

  thisData->indexBuffers.Merge(inst->Data()->indexBuffers);
  thisData->vertexBuffers.Merge(inst->Data()->vertexBuffers);
}

char *AmfMeshBuffers_V1_wrap::GetVertexBuffer(size_t id) const {
  return data->vertexBuffers[id].buffer.items;
}
char *AmfMeshBuffers_V1_wrap::GetIndexBuffer(size_t id) const {
  return data->indexBuffers[id].buffer.items;
}
size_t AmfMeshBuffers_V1_wrap::GetNumIndexBuffers() const {
  return data->indexBuffers.count;
}
size_t AmfMeshBuffers_V1_wrap::GetNumVertexBuffers() const {
  return data->vertexBuffers.count;
}

void AmfMeshHeader_V1_wrap::ReplaceReferences(ADFInternal *newMain) {
  main = newMain;
}

AmfMeshBuffers_V2_wrap::AmfMeshBuffers_V2_wrap(void *data_, ADFInternal *)
    : data01(static_cast<AmfMeshBuffers_V2 *>(data_)), data02(nullptr) {}

void AmfMeshBuffers_V2_wrap::Fixup(char *masterBuffer) {
  data01->Fixup(masterBuffer);
}

void AmfMeshBuffers_V2_wrap::Merge(ADFInstance *externalInstance) {
  AmfMeshBuffers_V2_wrap *inst =
      static_cast<AmfMeshBuffers_V2_wrap *>(externalInstance);
  data02 = inst->Data01();
}

void AmfMeshHeader_V2_wrap::ReplaceReferences(ADFInternal *newMain) {
  main = newMain;
}

AmfMeshBuffers_V1_5_wrap::AmfMeshBuffers_V1_5_wrap(void *data_, ADFInternal *)
    : data(static_cast<AmfMeshBuffers_V1_5 *>(data_)) {}
void AmfMeshBuffers_V1_5_wrap::Fixup(char *masterBuffer) {
  data->Fixup(masterBuffer);
}
char *AmfMeshBuffers_V1_5_wrap::GetVertexBuffer(size_t id) const {
  return data->vertexBuffers[id].items;
}
char *AmfMeshBuffers_V1_5_wrap::GetIndexBuffer(size_t id) const {
  return data->indexBuffers[id].items;
}
size_t AmfMeshBuffers_V1_5_wrap::GetNumIndexBuffers() const {
  return data->indexBuffers.count;
}
size_t AmfMeshBuffers_V1_5_wrap::GetNumVertexBuffers() const {
  return data->vertexBuffers.count;
}

class AmfMesh_V2_wrap : public AmfMesh {
  AmfMesh_V2 *data;
  char *indexBuffer;
  ADFInternal *main;
  std::vector<AmfPrimitiveWrap<AmfMesh_V2>> storage;

public:
  AmfMesh_V2_wrap(AmfMesh_V2 *imesh, ADFInternal *base,
                  AmfMeshBuffers_V2 *buffers_[2])
      : data(imesh), main(base), indexBuffer(nullptr) {
    if (!*buffers_) {
      return;
    }

    AmfMeshBuffers_V2 *buffers = nullptr;
    int index = data->mergedBufferIndex;

    if (data->mergedBufferIndex < buffers_[0]->indexOffsets.count) {
      buffers = buffers_[0];
    } else if (buffers_[1]) {
      buffers = buffers_[1];
      index -= buffers_[0]->indexOffsets.count;
    }

    if (!buffers) {
      return;
    }

    for (auto &s : data->subMeshes) {
      AmfPrimitiveWrap<AmfMesh_V2> cPrim;
      cPrim.indexBuffer =
          buffers->mergedBuffer.GetBuffer() + buffers->indexOffsets[index] * 2;
      cPrim.numIndices = s.indexCount;
      cPrim.name = &main->FindString(s.subMeshID);
      cPrim.data = data;
      cPrim.numVBO = 1;
      cPrim.vertexBuffers[0] =
          buffers->mergedBuffer.GetBuffer() + buffers->vertexOffsets[index];

      storage.emplace_back(std::move(cPrim));
    }
  }

  size_t GetNumTotalIndices() const override { return data->indexCount; }
  const std::string &GetMeshTypeName() const override {
    return main->FindString(data->meshTypeId);
  }
  bool IsValid() const override { return indexBuffer != nullptr; }
  AmfMeshRemapType GetRemapType() const override { return REMAP_TYPE_SHORT; }
  size_t GetNumRemaps() const override { return data->boneIndexLookup.count; }
  size_t GetRemap(size_t id) const override {
    return data->boneIndexLookup[id];
  }
  const void *GetRemaps() const override { return data->boneIndexLookup.items; }
  refptr GetReflectedAttributes() const override {
    return data->meshProperties.GetReflected();
  }

  size_t Size() const override { return storage.size(); }
  const_type At(size_t id) const override { return {&storage.at(id), false}; }
};

AmfMeshHeader_V2_wrap::AmfMeshHeader_V2_wrap(void *data_, ADFInternal *main_)
    : data(static_cast<AmfMeshHeader_V2 *>(data_)), main(main_), buffers() {}

size_t AmfMeshHeader_V2_wrap::GetNumLODs() const {
  return data->lodGroups.count;
}
size_t AmfMeshHeader_V2_wrap::GetLodIndex(size_t id) const {
  return data->lodGroups.items[id].index;
}
size_t AmfMeshHeader_V2_wrap::GetNumLODMeshes(size_t LODIndex) const {
  return data->lodGroups.items[LODIndex].meshes.count;
}
AmfMesh::Ptr AmfMeshHeader_V2_wrap::GetLODMesh(size_t LODIndex,
                                               size_t meshIndex) const {
  if (!*buffers) {
    AmfMeshBuffers_V2_wrap *bufWrap =
        main->FindInstance<AmfMeshBuffers_V2_wrap>();

    if (bufWrap) {
      buffers[0] = bufWrap->Data01();
      buffers[1] = bufWrap->Data02();
    }
  }

  return AmfMesh::Ptr(new AmfMesh_V2_wrap(
      &data->lodGroups.items[LODIndex].meshes.items[meshIndex], main, buffers));
}

void AmfMeshHeader_V2_wrap::Fixup(char *masterBuffer) {
  data->Fixup(masterBuffer);
}
es::string_view AmfMeshHeader_V2_wrap::RequestsFile() const {
  return main->FindString(data->highLod);
}
