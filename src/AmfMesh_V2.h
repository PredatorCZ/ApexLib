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
#include "AmfMesh_V1.h"

struct AmfSubMesh_V2
{
	ApexHash subMeshID;
	int indexCount;
	AdfBBOX boundingBox;
};

struct AmfMesh_V2
{
	ApexHash meshTypeId;
	uchar indexBufferStride,
		mergedBufferIndex;
	int	indexCount,
		vertexCount;
	AdfArray<uchar> vertexStreamStrides;
	AdfArray<int> vertexStreamOffsets;
	Vector textureDensities;
	AdfDeferred meshProperties;
	AdfArray<short> boneIndexLookup;
	AdfArray<AmfSubMesh_V2> subMeshes;
	AdfArray<AmfStreamAttribute> streamAttributes;

	ES_FORCEINLINE void Fixup(char *masterBuffer)
	{
		vertexStreamStrides.items.Fixup(masterBuffer);
		vertexStreamOffsets.items.Fixup(masterBuffer);
		boneIndexLookup.items.Fixup(masterBuffer);
		subMeshes.items.Fixup(masterBuffer);
		streamAttributes.items.Fixup(masterBuffer);
		meshProperties.item.Fixup(masterBuffer);
	}
};

struct AmfLodGroup_V2
{
	int index;
	AdfArray<AmfMesh_V2> meshes;

	ES_FORCEINLINE void Fixup(char *masterBuffer)
	{
		meshes.items.Fixup(masterBuffer);

		for (auto &m : meshes)
			m.Fixup(masterBuffer);
	}
};

struct AmfMeshHeader_V2
{
	AdfBBOX boundingBox;
	unsigned int memoryTag;
	AdfArray<AmfLodGroup_V2> lodGroups;
	ApexHash highLod;

	ES_FORCEINLINE void Fixup(char *masterBuffer)
	{
		lodGroups.items.Fixup(masterBuffer);

		for (auto &l : lodGroups)
			l.Fixup(masterBuffer);
	}
};

struct AmfMeshBuffers_V2
{
	int memoryTag;
	AdfArray<uint> indexOffsets;
	AdfArray<uint> vertexOffsets;
	AmfBuffer_V1 mergedBuffer;

	ES_FORCEINLINE void Fixup(char *masterBuffer) 
	{
		indexOffsets.items.Fixup(masterBuffer);
		vertexOffsets.items.Fixup(masterBuffer);
		mergedBuffer.Fixup(masterBuffer);
	}
};

