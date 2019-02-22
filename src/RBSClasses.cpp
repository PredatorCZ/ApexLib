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

#include "RBSClasses.h"
#include "datas/binreader.hpp"
#include "ADF.h"
#include "AmfMesh.h"

void RBSGeneral::Load(BinReader * rd)
{
	int bufferOffset = 0;
	int bufferSize = 0;
	int numVBuffers;
	rd->Read(numVBuffers);	
	rd->SavePos();

	for (int b = 0; b < numVBuffers; b++)
	{
		int vertexStride;
		int numVerts;
		rd->Read(vertexStride);
		rd->Read(numVerts);
		bufferOffset += vertexStride * numVerts;
		rd->Skip(vertexStride * numVerts);
	}

	int faceBuffUnknown;	
	int numFaces;

	rd->Read(faceBuffUnknown);
	rd->Read(numFaces);
	rd->RestorePos();
	bufferOffset += numFaces * 2;

	AmfMeshBuffers *buffers = master->AddUniqueInstance<AmfMeshBuffers>();
	AmfBuffer *cBuffer = new AmfBuffer();
	cBuffer->buffer = static_cast<char*>(malloc(bufferOffset));
	buffers->vertexBuffers.push_back(cBuffer);
	bufferOffset = 0;

	AmfMeshHeader *hdr = master->FindInstance<AmfMeshHeader>();
	hdr->lodGroups[0].meshes.resize(hdr->lodGroups[0].meshes.size() + 1);

	AmfMesh &msh = hdr->lodGroups[0].meshes.back();

	for (int b = 0; b < numVBuffers; b++)
	{
		int vertexStride;

		rd->Read(vertexStride);
		rd->Read(msh.Header.vertexCount);

		msh.vertexStreamOffsets.push_back(bufferOffset);
		msh.vertexStreamStrides.push_back(vertexStride);
		msh.vertexBufferIndices.push_back(static_cast<int>(buffers->vertexBuffers.size() - 1));

		bufferSize = vertexStride * msh.Header.vertexCount;
		rd->ReadBuffer(cBuffer->buffer + bufferOffset, bufferSize);
		bufferOffset += bufferSize;
	}

	msh.subMeshes.resize(1);
	rd->Read(faceBuffUnknown);
	rd->Read(msh.subMeshes[0].Header.indexCount);
	msh.Header.indexCount = numFaces;
	bufferSize = numFaces * 2;
	rd->ReadBuffer(cBuffer->buffer + bufferOffset, bufferSize);	
	msh.subMeshes[0].buffer = cBuffer->buffer + bufferOffset;
}