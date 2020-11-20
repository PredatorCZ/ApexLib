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
#include "apex/adf_bbox.hpp"
#include "apex/adf_deferred.hpp"
#include "amf_buffer.hpp"
#include "amf_stream_attribute.hpp"
#include "apex/props/amf_mesh.hpp"

struct AmfSubMesh_V1 {
  JenHash3 subMeshID;
  uint32 indexCount, indexStreamOffset;
  AdfBBOX boundingBox;
};

struct AmfMesh_V1 {
  JenHash3 MeshTypeId;
  uint32 indexCount, vertexCount;
  uint8 indexBufferIndex, indexBufferStride;
  uint32 indexBufferOffset;
  AdfArray<uint8> vertexBufferIndices, vertexStreamStrides;
  AdfArray<uint32> vertexStreamOffsets;
  Vector textureDensities;
  AdfDeferred meshProperties;
  AdfArray<int16> boneIndexLookup;
  AdfArray<AmfSubMesh_V1> subMeshes;
  AdfArray<AmfStreamAttribute> streamAttributes;

  void Fixup(char *masterBuffer) {
    vertexBufferIndices.items.Fixup(masterBuffer);
    vertexStreamStrides.items.Fixup(masterBuffer);
    vertexStreamOffsets.items.Fixup(masterBuffer);
    boneIndexLookup.items.Fixup(masterBuffer);
    subMeshes.items.Fixup(masterBuffer);
    streamAttributes.items.Fixup(masterBuffer);
    meshProperties.item.Fixup(masterBuffer);

    if (meshProperties.objectHash == CarPaintMeshConstants::GetHash()) {
      CarPaintMeshConstants *props =
          meshProperties.GetItem<CarPaintMeshConstants>();

      if (streamAttributes[1].usage == AmfUsage_Unspecified &&
          streamAttributes[1].format == AmfFormat_R32_UNIT_VEC_AS_FLOAT) {
        streamAttributes[1].usage = AmfUsage_DeformNormal_c;
      }
      if (streamAttributes[2].usage == AmfUsage_Unspecified &&
          streamAttributes[2].format == AmfFormat_R16G16B16A16_SINT) {
        streamAttributes[2].usage = AmfUsage_DeformPoints_c;
        streamAttributes[2].format = AmfFormat_R16G16B16A16_SNORM;
      }
    }
  }
};

struct AmfLodGroup_V1 {
  uint32 index;
  AdfArray<AmfMesh_V1> meshes;

  void Fixup(char *masterBuffer) {
    meshes.items.Fixup(masterBuffer);

    for (auto &m : meshes) {
      m.Fixup(masterBuffer);
    }
  }
};

struct AmfMeshHeader_V1 {
  AdfBBOX boundingBox;
  uint32 memoryTag;
  AdfArray<AmfLodGroup_V1> lodGroups;
  JenHash3 highLod;

  void Fixup(char *masterBuffer) {
    lodGroups.items.Fixup(masterBuffer);

    for (auto &l : lodGroups) {
      l.Fixup(masterBuffer);
    }
  }
};

struct AmfMeshBuffers_V1 {
  uint32 memoryTag;
  AdfArray<AmfBuffer> indexBuffers;
  AdfArray<AmfBuffer> vertexBuffers;

  void Fixup(char *masterBuffer) {
    indexBuffers.items.Fixup(masterBuffer);
    vertexBuffers.items.Fixup(masterBuffer);

    for (auto &i : indexBuffers) {
      i.Fixup(masterBuffer);
    }

    for (auto &v : vertexBuffers) {
      v.Fixup(masterBuffer);
    }
  }
};

struct AmfMeshBuffers_V1_5 {
  uint32 memoryTag;
  AdfArray<AdfArray<char>> indexBuffers;
  AdfArray<AdfArray<char>> vertexBuffers;

  void Fixup(char *masterBuffer) {
    indexBuffers.items.Fixup(masterBuffer);
    vertexBuffers.items.Fixup(masterBuffer);

    for (auto &i : indexBuffers) {
      i.items.Fixup(masterBuffer);
    }

    for (auto &v : vertexBuffers) {
      v.items.Fixup(masterBuffer);
    }
  }
};
