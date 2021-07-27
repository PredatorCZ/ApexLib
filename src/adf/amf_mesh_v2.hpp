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
#include "amf_buffer.hpp"
#include "apex/adf_bbox.hpp"
#include "apex/adf_deferred.hpp"
#include "amf_stream_attribute.hpp"

struct AmfSubMesh_V2 {
  JenHash3 subMeshID;
  uint32 indexCount;
  AdfBBOX boundingBox;
};

struct AmfMesh_V2 {
  JenHash3 meshTypeId;
  uint8 indexBufferStride, mergedBufferIndex;
  uint32 indexCount, vertexCount;
  AdfArray<uint8> vertexStreamStrides;
  AdfArray<uint32> vertexStreamOffsets;
  Vector textureDensities;
  AdfDeferred meshProperties;
  AdfArray<int16> boneIndexLookup;
  AdfArray<AmfSubMesh_V2> subMeshes;
  AdfArray<AmfStreamAttribute> streamAttributes;

  void Fixup(char *masterBuffer) {
    vertexStreamStrides.items.Fixup(masterBuffer);
    vertexStreamOffsets.items.Fixup(masterBuffer);
    boneIndexLookup.items.Fixup(masterBuffer);
    subMeshes.items.Fixup(masterBuffer);
    streamAttributes.items.Fixup(masterBuffer);
    meshProperties.item.Fixup(masterBuffer);
  }
};

struct AmfLodGroup_V2 {
  uint32 index;
  AdfArray<AmfMesh_V2> meshes;

  void Fixup(char *masterBuffer) {
    meshes.items.Fixup(masterBuffer);

    for (auto &m : meshes) {
      m.Fixup(masterBuffer);
    }
  }
};

struct AmfMeshHeader_V2 {
  AdfBBOX boundingBox;
  uint32 memoryTag;
  AdfArray<AmfLodGroup_V2> lodGroups;
  JenHash3 highLod;

  void Fixup(char *masterBuffer) {
    lodGroups.items.Fixup(masterBuffer);

    for (auto &l : lodGroups) {
      l.Fixup(masterBuffer);
    }
  }
};

struct AmfMeshBuffers_V2 {
  int memoryTag;
  AdfArray<uint> indexOffsets;
  AdfArray<uint> vertexOffsets;
  AmfBuffer mergedBuffer;

  void Fixup(char *masterBuffer) {
    indexOffsets.items.Fixup(masterBuffer);
    vertexOffsets.items.Fixup(masterBuffer);
    mergedBuffer.Fixup(masterBuffer);
  }
};
