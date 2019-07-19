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
#include "AmfMesh.h"
#include "AdfBaseObject.h"

struct AmfSubMesh_V1
{
	ApexHash subMeshID;
	int indexCount,
		indexStreamOffset;
	AdfBBOX boundingBox;
};

struct AmfMesh_V1
{
	ApexHash MeshTypeId;
	int	indexCount,
		vertexCount;
	unsigned char indexBufferIndex,
		indexBufferStride;
	int indexBufferOffset;
	AdfArray<uchar> vertexBufferIndices,
		vertexStreamStrides;
	AdfArray<int> vertexStreamOffsets;
	Vector textureDensities;
	AdfDeferred meshProperties;
	AdfArray<short> boneIndexLookup;
	AdfArray<AmfSubMesh_V1> subMeshes;
	AdfArray<AmfStreamAttribute> streamAttributes;

	ES_FORCEINLINE void Fixup(char *masterBuffer)
	{
		vertexBufferIndices.items.Fixup(masterBuffer);
		vertexStreamStrides.items.Fixup(masterBuffer);
		vertexStreamOffsets.items.Fixup(masterBuffer);
		boneIndexLookup.items.Fixup(masterBuffer);
		subMeshes.items.Fixup(masterBuffer);
		streamAttributes.items.Fixup(masterBuffer);
		meshProperties.item.Fixup(masterBuffer);

		if (meshProperties.objectHash == CarPaintMeshConstants::HASH)
		{
			CarPaintMeshConstants *props = meshProperties.GetItem<CarPaintMeshConstants>();

			if (streamAttributes[1].usage == AmfUsage_Unspecified && streamAttributes[1].format == AmfFormat_R32_UNIT_VEC_AS_FLOAT)
				streamAttributes[1].usage = AmfUsage_DeformNormal_c;
			if (streamAttributes[2].usage == AmfUsage_Unspecified && streamAttributes[2].format == AmfFormat_R16G16B16A16_SINT)
			{
				streamAttributes[2].usage = AmfUsage_DeformPoints_c;
				streamAttributes[2].format = AmfFormat_R16G16B16A16_SNORM;
			}
		}
	}
};

struct AmfLodGroup_V1
{
	int index;
	AdfArray<AmfMesh_V1> meshes;

	ES_FORCEINLINE void Fixup(char *masterBuffer)
	{
		meshes.items.Fixup(masterBuffer);

		for (auto &m : meshes)
			m.Fixup(masterBuffer);
	}
};

struct AmfMeshHeader_V1
{
	AdfBBOX boundingBox;
	unsigned int memoryTag;
	AdfArray<AmfLodGroup_V1> lodGroups;
	ApexHash highLod;

	ES_FORCEINLINE void Fixup(char *masterBuffer)
	{
		lodGroups.items.Fixup(masterBuffer);

		for (auto &l : lodGroups)
			l.Fixup(masterBuffer);
	}
};

struct AmfBuffer_V1
{
	AdfArray<char> buffer;
	bool createSRV;

	ES_FORCEINLINE char *GetBuffer() { return buffer.items.cPtr; }
	ES_FORCEINLINE void Fixup(char *masterBuffer) { buffer.items.Fixup(masterBuffer); }
};

struct AmfMeshBuffers_V1
{
	int memoryTag;
	AdfArray<AmfBuffer_V1> indexBuffers;
	AdfArray<AmfBuffer_V1> vertexBuffers;

	ES_FORCEINLINE void Fixup(char *masterBuffer) 
	{ 
		indexBuffers.items.Fixup(masterBuffer);
		vertexBuffers.items.Fixup(masterBuffer);

		for (auto &i : indexBuffers)
			i.Fixup(masterBuffer);

		for (auto &v : vertexBuffers)
			v.Fixup(masterBuffer);
	}
};

struct AmfMeshBuffers_V1_5
{
	int memoryTag;
	AdfArray<AdfArray<char>> indexBuffers;
	AdfArray<AdfArray<char>> vertexBuffers;

	ES_FORCEINLINE void Fixup(char *masterBuffer)
	{
		indexBuffers.items.Fixup(masterBuffer);
		vertexBuffers.items.Fixup(masterBuffer);

		for (auto &i : indexBuffers)
			i.items.Fixup(masterBuffer);

		for (auto &v : vertexBuffers)
			v.items.Fixup(masterBuffer);
	}
};

