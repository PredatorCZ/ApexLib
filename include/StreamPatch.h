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
#include "AmfEnums.h"
#include "AdfBaseObject.h"
#include "ApexApi.h"
#include <vector>
#include "datas/flags.hpp"

struct StreamPatchFileHeader : ADFInstance
{
	struct
	{
		uint version,
			size,
			dynamicMemoryRequirements;
		IVector2 patchPosition;
		int patchLod;
	}Header;

	int Load(BinReader *rd, ADF *linker);
	void Link(ADF *linker) {};
	std::string *RequestsFile() { return  nullptr; }
	void Merge(ADFInstance *) {};
	static const ApexHash HASH = 0x852D0D20;
};

static_assert(sizeof(StreamPatchFileHeader::Header) == 24, "Check assumptions");

enum StreamPatchMemoryType
{
	STREAM_PATCH_STATIC_POOL,
	STREAM_PATCH_DYNAMIC,
	STREAM_PATCH_USER
};

struct StreamPatchBlockHeader : ADFInstance
{
	struct
	{
		uint version;
		StreamPatchMemoryType memoryType;
		int memorySize;
		IVector2 patchPosition;
		int patchLod;
	}Header;

	int Load(BinReader *rd, ADF *linker);
	void Link(ADF *linker) {};
	std::string *RequestsFile() { return  nullptr; }
	void Merge(ADFInstance *) {};
	static const ApexHash HASH = 0x78CB76FD;
};

static_assert(sizeof(StreamPatchBlockHeader::Header) == 24, "Check assumptions");

enum MemAllocator
{
	E_MEMALLOCATOR_CPU,
	E_MEMALLOCATOR_SHARED,
	E_MEMALLOCATOR_GPU
};

struct CompressedData
{
	struct
	{
		uint uncompressedSize;
		AdfArray data;
		MemAllocator uncompressAllocator;
	}Header;

	char *data;
	int Load(BinReader *rd, ADF *linker);
	CompressedData() :data(nullptr) {}
	~CompressedData();
};

static_assert(sizeof(CompressedData::Header) == 32, "Check assumptions");

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

	int Load(BinReader *rd, ADF *linker);
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
struct TerrainTexture_base
{
	uint width,
		height;
	BlockCompressionType blockCompressionType;
	esFlags<uint, TerrainTexture_flags> flags;
};

struct TerrainTexture : TerrainTexture_base
{
	CompressedData data;

	int Load(BinReader *rd, ADF *linker);
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

struct TerrainPatch : ADFInstance
{
	TerrainMesh terrainMesh;
	std::vector<TerrainPrimitive> terrainPrimitives;
	TerrainTexture terrainDisplacementTexture,
		terrainNormalTexture,
		terrainTriangleMapTexture,
		terrainMaterialDuplexTexture,
		terrainColorTexture,
		terrainQualityTexture,
		terrainIndirectionTexture,
		terrainSSDFAtlas;
	esFlags<uint, TerrainPatch_flags> flags;
	
	int Load(BinReader *rd, ADF *linker);
	void Link(ADF *linker) {};
	std::string *RequestsFile() { return  nullptr; }
	void Merge(ADFInstance *) {};
	static const ApexHash HASH = 0xFD31E1DB;
};
