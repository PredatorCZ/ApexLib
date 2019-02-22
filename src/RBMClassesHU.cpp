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

#include "RBMClassesHU.h"
#include "datas/binreader.hpp"
#include "datas\masterprinter.hpp"
#include "ADF.h"
#include "AmfModel.h"
#include "AmfMesh.h"
#include "AdfRegistry.h"

struct _UIOverlay_vsh
{
	Vector2 pos;
	Vector2 uv;
};

struct _UIOverlay_vshOut
{
	Vector pos;
	Vector2 uv;
};

void RBMUIOverlay::Load(BinReader * rd)
{
	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const uint oldStride = sizeof(_UIOverlay_vsh);
	const uint currentStride = sizeof(_UIOverlay_vshOut);
	const uint vBufferSize = numVertices * oldStride;
	const uint modVBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + modVBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	
	_UIOverlay_vsh *tempBuffer = static_cast<_UIOverlay_vsh*>(malloc(vBufferSize));
	rd->ReadBuffer(reinterpret_cast<char*>(tempBuffer), vBufferSize);
	
	LoadFaces(rd, mesh, modVBufferSize, cBuffer);

	_UIOverlay_vshOut *oBuffer = reinterpret_cast<_UIOverlay_vshOut*>(cBuffer->buffer);

	for (uint v = 0; v < numVertices; v++)
	{
		_UIOverlay_vsh &inBuffer = tempBuffer[v];
		_UIOverlay_vshOut &currOutBuffer = *reinterpret_cast<_UIOverlay_vshOut*>(cBuffer->buffer + (currentStride * v));

		currOutBuffer.pos = Vector(inBuffer.pos.X, inBuffer.pos.Y, 0.0f);
		currOutBuffer.uv = inBuffer.uv;
	}

	free(tempBuffer);

	mesh.streamAttributes.resize(2);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}
}
