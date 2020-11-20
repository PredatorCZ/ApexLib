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
#include "adf_array.hpp"
#include "adf_instance.hpp"
#include "adf_bbox.hpp"

struct StreamPatchFileHeader {
  uint32 version, size, dynamicMemoryRequirements;
  IVector2 patchPosition;
  uint32 patchLod;
};

static_assert(sizeof(StreamPatchFileHeader) == 24, "Check assumptions");

class StreamPatchFileHeader_wrap : public ADFInstance {
  StreamPatchFileHeader *data;

  void Fixup(char *masterBuffer) {}

public:
  static constexpr auto GetHash() { return JenHash3(0x852D0D20); }

  StreamPatchFileHeader_wrap(void *data_, ADFInternal *main_);
  StreamPatchFileHeader *Data() { return data; }

  JenHash3 GetSuperClass() const { return -1; }
};

enum StreamPatchMemoryType {
  STREAM_PATCH_STATIC_POOL,
  STREAM_PATCH_DYNAMIC,
  STREAM_PATCH_USER
};

struct StreamPatchBlockHeader {
  uint32 version;
  StreamPatchMemoryType memoryType;
  uint32 memorySize;
  IVector2 patchPosition;
  uint32 patchLod;
};

static_assert(sizeof(StreamPatchBlockHeader) == 24, "Check assumptions");

class StreamPatchBlockHeader_wrap : public ADFInstance {
  StreamPatchBlockHeader *data;

  void Fixup(char *masterBuffer) {}

public:
  static constexpr auto GetHash() { return JenHash3(0x78CB76FD); }

  StreamPatchBlockHeader_wrap(void *data_, ADFInternal *main_);
  StreamPatchBlockHeader *Data() { return data; }

  JenHash3 GetSuperClass() const { return -1; }
};

enum MemAllocator {
  E_MEMALLOCATOR_CPU,
  E_MEMALLOCATOR_SHARED,
  E_MEMALLOCATOR_GPU
};

struct CompressedData {
  uint32 uncompressedSize;
  AdfArray<char> data;
  MemAllocator uncompressAllocator;

  void Fixup(char *masterBuffer);
  char *Decompress() const;
};

static_assert(sizeof(CompressedData) == 32, "Check assumptions");

struct TerrainMesh {
  AdfBBOX boundingBox;
  CompressedData indices;
  uint32 indexTypeSize;
  CompressedData vertices, vertices2, quadInfos, triangleIndices,
      groupTriIndices;

  void Fixup(char *masterBuffer);
};

enum BlockCompressionType {
  E_BLOCKCOMPRESSIONTYPE_NONE,
  E_BLOCKCOMPRESSIONTYPE_BC3,
  E_BLOCKCOMPRESSIONTYPE_BC7
};

enum TerrainTexture_flags : uint32 {
  TerrainTexture_Tiled,
  TerrainTexture_SRGB
};
struct TerrainTexture {
  uint32 width, height;
  BlockCompressionType blockCompressionType;
  es::Flags<TerrainTexture_flags> flags;
  CompressedData data;

  void Fixup(char *masterBuffer);
};

enum TerrainPatch_flags : uint32 { TerrainPatch_DisplacementDownsampled };

struct TerrainPrimitive {
  AdfBBOX AABB;
  Vector2 W;
};

struct TerrainPatch {
  TerrainMesh terrainMesh;
  AdfArray<TerrainPrimitive> terrainPrimitives;
  TerrainTexture terrainDisplacementTexture, terrainNormalTexture,
      terrainTriangleMapTexture, terrainMaterialDuplexTexture,
      terrainColorTexture, terrainQualityTexture, terrainIndirectionTexture,
      terrainSSDFAtlas;
  es::Flags<TerrainPatch_flags> flags;

  void Fixup(char *masterBuffer);
};

class TerrainPatch_wrap : public ADFInstance {
  TerrainPatch *data;

  void Fixup(char *masterBuffer);

public:
  static constexpr auto GetHash() { return JenHash3(0xFD31E1DB); }

  TerrainPatch_wrap(void *data_, ADFInternal *main_);
  TerrainPatch *Data() { return data; }

  JenHash3 GetSuperClass() const { return -1; }
};
