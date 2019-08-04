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
#include "zstd.h"
#include "datas/masterprinter.hpp"

ES_INLINE void TerrainTexture::Fixup(char *masterBuffer)
{
	data.Fixup(masterBuffer);
}

ES_INLINE void CompressedData::Fixup(char *masterBuffer)
{
	data.items.Fixup(masterBuffer);
}

ES_INLINE void TerrainMesh::Fixup(char *masterBuffer)
{
	indices.Fixup(masterBuffer);
	vertices.Fixup(masterBuffer);
	vertices2.Fixup(masterBuffer);
	quadInfos.Fixup(masterBuffer);
	triangleIndices.Fixup(masterBuffer);
	groupTriIndices.Fixup(masterBuffer);
}

ES_INLINE void TerrainPatch::Fixup(char *masterBuffer)
{
	terrainMesh.Fixup(masterBuffer);
	terrainPrimitives.items.Fixup(masterBuffer);
	terrainDisplacementTexture.Fixup(masterBuffer);
	terrainNormalTexture.Fixup(masterBuffer);
	terrainTriangleMapTexture.Fixup(masterBuffer);
	terrainMaterialDuplexTexture.Fixup(masterBuffer);
	terrainColorTexture.Fixup(masterBuffer);
	terrainQualityTexture.Fixup(masterBuffer);
	terrainIndirectionTexture.Fixup(masterBuffer);
	terrainSSDFAtlas.Fixup(masterBuffer);
}

TerrainPatch_wrap::TerrainPatch_wrap(void *_data, ADF *_main): data(static_cast<TerrainPatch*>(_data)) {}
void TerrainPatch_wrap::Fixup(char *masterBuffer) { data->Fixup(masterBuffer); }

StreamPatchFileHeader_wrap::StreamPatchFileHeader_wrap(void *_data, ADF *_main): data(static_cast<StreamPatchFileHeader*>(_data)) {}

StreamPatchBlockHeader_wrap::StreamPatchBlockHeader_wrap(void *_data, ADF *_main): data(static_cast<StreamPatchBlockHeader*>(_data)) {}

struct COMP
{
	static const int ID = 0x504d4f43;
	int id;
	char vars[4]; // 01 03 01 00
	uint64 uncompressedSize;
};

char *CompressedData::Decompress() const
{
	char *cData = data.items.cPtr;
	COMP *header = reinterpret_cast<COMP*>(cData);

	if (header->id != COMP::ID || header->vars[0] != 1)
	{
		printerror("[COMP] Invalid compressed chunk.");
		return nullptr;
	}

	char *decompBuffer = static_cast<char *>(malloc(uncompressedSize));
	size_t ZSTD_result = ZSTD_decompress(decompBuffer, uncompressedSize, cData + sizeof(COMP), data.count);
	int result = ZSTD_isError(ZSTD_result);

	if (result)
	{
		printerror("[COMP] Decompression error: ", << result);
		free(decompBuffer);
		return nullptr;
	}

	return decompBuffer;
}
