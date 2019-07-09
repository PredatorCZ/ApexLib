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

