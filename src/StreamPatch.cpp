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

#include "StreamPatch.h"
#include "datas/binreader.hpp"
#include "ADF.h"
#include "zstd.h"

int StreamPatchFileHeader::Load(BinReader * rd, ADF * linker)
{
	rd->Read(Header);
	return 0;
}

int StreamPatchBlockHeader::Load(BinReader *rd, ADF *linker)
{
	rd->Read(Header);
	return 0;
}

struct COMP
{
	static const int ID = 0x504d4f43;
	int id;
	char vars[4]; // 01 03 01 00
	uint64 uncompressedSize;
};

int CompressedData::Load(BinReader *rd, ADF *linker)
{
	int result = 0;

	rd->Read(Header);
	rd->SavePos();
	rd->Seek(Header.data.offset);

	const size_t dataCount = static_cast<size_t>(Header.data.count);
	char *compressedData = static_cast<char*>(malloc(dataCount));
	data = static_cast<char *>(malloc(Header.uncompressedSize));
	
	rd->ReadBuffer(compressedData, dataCount);

	COMP *comp = reinterpret_cast<COMP *>(compressedData);

	if (comp->id == COMP::ID && comp->vars[0] == 1)
	{
		size_t ZSTD_result = ZSTD_decompress(data, Header.uncompressedSize, compressedData + sizeof(COMP), dataCount);

		result = ZSTD_isError(ZSTD_result);
	}
	else
	{
		result = 2;
	}
	
	free(compressedData);
	rd->RestorePos();

	return result;
}

CompressedData::~CompressedData()
{
	if (data)
		free(data);
}

int TerrainMesh::Load(BinReader *rd, ADF *linker)
{
	rd->Read(boundingBox);
	indices.Load(rd, linker);
	rd->Read(indexTypeSize);
	rd->Skip(4);
	vertices.Load(rd, linker);
	vertices2.Load(rd, linker);
	quadInfos.Load(rd, linker);
	triangleIndices.Load(rd, linker);
	groupTriIndices.Load(rd, linker);

	return 0;
}

int TerrainTexture::Load(BinReader *rd, ADF *linker)
{
	rd->Read(static_cast<TerrainTexture_base &>(*this));
	data.Load(rd, linker);
	return 0;
}


int TerrainPatch::Load(BinReader *rd, ADF *linker)
{
	terrainMesh.Load(rd, linker);
	AdfArray terrainPrimitive;
	rd->Read(terrainPrimitive);

	terrainDisplacementTexture.Load(rd, linker);
	terrainNormalTexture.Load(rd, linker);
	terrainTriangleMapTexture.Load(rd, linker);
	terrainMaterialDuplexTexture.Load(rd, linker);
	terrainColorTexture.Load(rd, linker);
	terrainQualityTexture.Load(rd, linker);
	terrainIndirectionTexture.Load(rd, linker);
	terrainSSDFAtlas.Load(rd, linker);
	rd->Read(flags);

	rd->Seek(terrainPrimitive.offset);
	terrainPrimitives.resize(terrainPrimitive.count);

	for (auto &t : terrainPrimitives)
		rd->Read(t);

	return 0;
}

