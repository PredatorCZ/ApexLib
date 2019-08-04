/*  Apex Engine Format Library
	Copyright(C) 2014-2019 Lukas Cone

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
#include "AdfBaseObject.h"
#include "datas/flags.hpp"

struct StreamPatchFileHeader
{
	uint version,
		size,
		dynamicMemoryRequirements;
	IVector2 patchPosition;
	int patchLod;
};

static_assert(sizeof(StreamPatchFileHeader) == 24, "Check assumptions");

class StreamPatchFileHeader_wrap : public ADFInstance
{
	StreamPatchFileHeader *data;

	void Fixup(char *masterBuffer) {}
	const char *RequestsFile() const { return nullptr; }
public:
	static const ApexHash HASH = 0x852D0D20;

	StreamPatchFileHeader_wrap(void *_data, ADF *_main);
	ES_FORCEINLINE StreamPatchFileHeader *Data() { return data; }

	ApexHash GetSuperClass() const { return -1; }
};

enum StreamPatchMemoryType
{
	STREAM_PATCH_STATIC_POOL,
	STREAM_PATCH_DYNAMIC,
	STREAM_PATCH_USER
};

struct StreamPatchBlockHeader
{
	uint version;
	StreamPatchMemoryType memoryType;
	int memorySize;
	IVector2 patchPosition;
	int patchLod;
};

static_assert(sizeof(StreamPatchBlockHeader) == 24, "Check assumptions");


class StreamPatchBlockHeader_wrap : public ADFInstance
{
	StreamPatchBlockHeader *data;

	void Fixup(char *masterBuffer) {}
	const char *RequestsFile() const { return nullptr; }
public:
	static const ApexHash HASH = 0x78CB76FD;

	StreamPatchBlockHeader_wrap(void *_data, ADF *_main);
	ES_FORCEINLINE StreamPatchBlockHeader *Data() { return data; }

	ApexHash GetSuperClass() const { return -1; }
};

enum MemAllocator
{
	E_MEMALLOCATOR_CPU,
	E_MEMALLOCATOR_SHARED,
	E_MEMALLOCATOR_GPU
};

struct CompressedData
{
	uint uncompressedSize;
	AdfArray<char> data;
	MemAllocator uncompressAllocator;

	void Fixup(char *masterBuffer);
	char *Decompress() const;
};

static_assert(sizeof(CompressedData) == 32, "Check assumptions");

struct TerrainMesh
{
	AdfBBOX boundingBox;
	CompressedData indices;
	uint indexTypeSize;
	CompressedData vertices,
		vertices2,
		quadInfos,
		triangleIndices,
		groupTriIndices;

	void Fixup(char *masterBuffer);
};

enum BlockCompressionType
{
	E_BLOCKCOMPRESSIONTYPE_NONE,
	E_BLOCKCOMPRESSIONTYPE_BC3,
	E_BLOCKCOMPRESSIONTYPE_BC7
};

enum TerrainTexture_flags
{
	TerrainTexture_Tiled,
	TerrainTexture_SRGB
};
struct TerrainTexture
{
	uint width,
		height;
	BlockCompressionType blockCompressionType;
	esFlags<uint, TerrainTexture_flags> flags;
	CompressedData data;

	void Fixup(char *masterBuffer);
};

enum TerrainPatch_flags
{
	TerrainPatch_DisplacementDownsampled
};

struct TerrainPrimitive
{
	AdfBBOX AABB;
	Vector2 W;
};

struct TerrainPatch
{
	TerrainMesh terrainMesh;
	AdfArray<TerrainPrimitive> terrainPrimitives;
	TerrainTexture terrainDisplacementTexture,
		terrainNormalTexture,
		terrainTriangleMapTexture,
		terrainMaterialDuplexTexture,
		terrainColorTexture,
		terrainQualityTexture,
		terrainIndirectionTexture,
		terrainSSDFAtlas;
	esFlags<uint, TerrainPatch_flags> flags;

	void Fixup(char *masterBuffer);
};

class TerrainPatch_wrap : public ADFInstance
{
	TerrainPatch *data;

	void Fixup(char *masterBuffer);
	const char *RequestsFile() const { return nullptr; }
public:
	static const ApexHash HASH = 0xFD31E1DB;

	TerrainPatch_wrap(void *_data, ADF *_main);
	ES_FORCEINLINE TerrainPatch *Data() { return data; }

	ApexHash GetSuperClass() const { return -1; }
};
