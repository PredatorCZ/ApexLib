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

struct AmfSubMesh
{
	struct {
		ApexHash subMeshID;
		int indexCount,
			indexStreamOffset;
		AdfBBOX boundingBox;
	}Header;

	const char *buffer;
	StringHash *meshName;
	int Load(BinReader *rd, ADF *linker);
	ES_FORCEINLINE void GetFace(int at, USVector &out) { out = *reinterpret_cast<const USVector*>(buffer + (static_cast<intptr_t>(at) * 6)); }
};

struct AmfStreamAttribute
{
	struct {
		AmfUsage usage;
		AmfFormat format;
		unsigned char streamIndex,
			streamOffset,
			streamStride;
		unsigned char packingData[8];
	}Header;

	const char *buffer;
	void (*Evaluate)(AmfStreamAttribute *that, int id, void *data);
	int Load(BinReader *rd, ADF *linker);
	void AssignEvaluator(AmfFormat format);
	ES_FORCEINLINE void AssignEvaluator() { AssignEvaluator(Header.format); }
};

struct GeneralMeshConstants
{
	DECLARE_REFLECTOR;
	int pristineIndexCount;
	esFlags<char, GeneralMeshConstantsFlags> flags;
	static const ApexHash HASH = 0x15EEC9DE;
};

struct FoliageMeshConstants
{
	DECLARE_REFLECTOR;
	AdfBBOX boundingBoxDimensions;
	static const ApexHash HASH = 0xA7CACE80;
};

struct CarPaintMeshConstants
{
	DECLARE_REFLECTOR;
	esFlags<char, CarPaintMeshConstantsFlags> flags;
	static const ApexHash HASH = 0x1C363162;
};

struct AmfMesh
{
	struct {
		ApexHash MeshTypeId;
		int	indexCount,
			vertexCount;
		unsigned char indexBufferIndex,
			indexBufferStride;
		int indexBufferOffset;
		AdfArray vertexBufferIndices,
			vertexStreamStrides;
		AdfArray vertexStreamOffsets;
		Vector textureDensities;
		AdfDeferred meshProperties;
		AdfArray boneIndexLookup;
		AdfArray subMeshes;
		AdfArray streamAttributes;
	}Header;

	std::vector<unsigned char> vertexBufferIndices,
		vertexStreamStrides;
	std::vector<int> vertexStreamOffsets;
	std::vector<short> boneIndexLookup;
	std::vector<AmfSubMesh> subMeshes;
	std::vector<AmfStreamAttribute> streamAttributes;
	std::vector<Vector> spritePositions;
	StringHash *meshType;
	AdfProperties *meshProperties;
	bool properlyLinked;
	int Load(BinReader *rd, ADF *linker);
	void Link(ADF *linker);
	~AmfMesh();
};

struct AmfLodGroup
{
	struct {
		int index;
		AdfArray Meshes;
	}Header;

	std::vector<AmfMesh> meshes;

	int Load(BinReader *rd, ADF *linker);
};

struct AmfMeshHeader : ADFInstance
{
	struct {
		AdfBBOX boundingBox;
		unsigned int MemoryTag;
		AdfArray LodGroups;
		int HighLodPath;
	}Header;

	std::vector<AmfLodGroup> lodGroups;
	StringHash *highLODPath;
	int Load(BinReader *rd, ADF *linker);
	void Link(ADF *linker);
	ES_INLINE std::string *RequestsFile() { return &highLODPath->string; }
	void Merge(ADFInstance *) {};
	static const ApexHash HASH = 0xEA60065D;
};

struct AmfBuffer
{
	struct
	{
		AdfArray info;
		bool createSRV;
	}Header;
	
	char *buffer;

	int Load(BinReader *rd);
	~AmfBuffer();
};

struct AmfMeshBuffers : ADFInstance
{
	struct {
		int memoryTag;
		AdfArray indexBuffers;
		AdfArray vertexBuffers;
	}Header;

	std::vector<AmfBuffer*> indexBuffers;
	std::vector<AmfBuffer*> vertexBuffers;

	int Load(BinReader *rd, ADF *linker);
	void Link(ADF *) {};
	std::string *RequestsFile() { return nullptr; };
	void Merge(ADFInstance *externalInstance);
	static const ApexHash HASH = 0x67B3A453;
	~AmfMeshBuffers();
};

struct AmfMeshBuffers_TheHunter : AmfMeshBuffers
{
	static const ApexHash HASH = 0xe6834477;
};