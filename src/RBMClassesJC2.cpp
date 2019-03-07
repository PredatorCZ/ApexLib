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

#include "RBMClassesJC2.h"
#include "datas/binreader.hpp"
#include "datas\masterprinter.hpp"
#include "ADF.h"
#include "AmfModel.h"
#include "AmfMesh.h"

REFLECTOR_START_WNAMES(RBMCarPaintSimple, twoToneColor1, twoToneColor2, specularPower, depthBias, reflectionMultiplier, flags);

void RBMCarPaintSimple::Load(BinReader * rd)
{
	rd->Read(twoToneColor1, getBlockSize(RBMCarPaintSimple, twoToneColor1, flags));

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 32;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}
}

void RBMFoliageBark::Load(BinReader * rd)
{
	rd->Read(flags);

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	bool secondaryUVS = (flags & 4) == 0;

	const uint currentStride = secondaryUVS ? 40 : 32;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(secondaryUVS ? 6 : 5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	if (secondaryUVS)
	{
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
		}
		
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c, 0);
		}
	}
	else
	{
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
		}
	}
}

REFLECTOR_START_WNAMES(RBMVegetationFoliage, specularIntensity, specularPower, translucencyColorMask);

void RBMVegetationFoliage::Load(BinReader * rd)
{
	rd->Read(specularIntensity, getBlockSize(RBMVegetationFoliage, specularIntensity, flags));

	ReadTextures(rd, 8);
	rd->Read(unk);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 40;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}
}

struct _BillboardFoliage_vsh
{
	Vector center;
	Vector2 uv;
	float offset[2];
};

struct _BillboardFoliage_vshOut
{
	Vector pos;
	Vector2 uv;
	int spriteID;
};

void RBMBillboardFoliage::Load(BinReader * rd)
{
	ReadTextures(rd, 8);
	rd->Read(unk);

	uint numVertices;
	rd->Read(numVertices);

	const uint oldStride = sizeof(_BillboardFoliage_vsh);
	const uint currentStride = sizeof(_BillboardFoliage_vshOut);
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
	_BillboardFoliage_vsh *tempBuffer = static_cast<_BillboardFoliage_vsh*>(malloc(vBufferSize));
	rd->ReadBuffer(reinterpret_cast<char*>(tempBuffer), vBufferSize);
	LoadFaces(rd, mesh, modVBufferSize, cBuffer);

	mesh.spritePositions.reserve(numVertices / 4);

	for (uint v = 0; v < numVertices; v++)
	{
		bool found = false;

		for (auto &sv : mesh.spritePositions)
			if (sv == tempBuffer[v].center)
			{
				found = true;
				break;
			}

		if (!found)
			mesh.spritePositions.push_back(tempBuffer[v].center);
	}

	_BillboardFoliage_vshOut *oBuffer = reinterpret_cast<_BillboardFoliage_vshOut*>(cBuffer->buffer);

	for (uint v = 0; v < numVertices; v++)
	{
		_BillboardFoliage_vsh &inBuffer = tempBuffer[v];
		_BillboardFoliage_vshOut &currOutBuffer = *reinterpret_cast<_BillboardFoliage_vshOut*>(cBuffer->buffer + (currentStride * v));

		int boneID = 0;
		for (auto &sv : mesh.spritePositions)
		{
			if (sv == inBuffer.center)
				break;

			boneID++;
		}

		currOutBuffer.spriteID = boneID;
		currOutBuffer.pos = inBuffer.center + Vector(inBuffer.offset[0], inBuffer.offset[1], 0.0f);
		currOutBuffer.uv = inBuffer.uv;
	}

	free(tempBuffer);

	mesh.streamAttributes.resize(3);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R32_UINT, 0);
	}
}

struct _Halo_vsh
{
	Vector center;
	UCVector2 way,
		size;
	UCVector4 color;
};

struct _Halo_vshOut
{
	Vector pos;
	SVector2 uv;
	UCVector4 color;
	int spriteID;
};
void RBMHalo::Load(BinReader * rd)
{
	ReadTextures(rd, 8);
	rd->Read(unk);

	uint numVertices;
	rd->Read(numVertices);

	const uint oldStride = sizeof(_Halo_vsh);
	const uint currentStride = sizeof(_Halo_vshOut);
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
	_Halo_vsh *tempBuffer = static_cast<_Halo_vsh*>(malloc(vBufferSize));
	rd->ReadBuffer(reinterpret_cast<char*>(tempBuffer), vBufferSize);
	LoadFaces(rd, mesh, modVBufferSize, cBuffer);

	mesh.spritePositions.reserve(numVertices / 4);

	for (uint v = 0; v < numVertices; v++)
	{
		bool found = false;

		for (auto &sv : mesh.spritePositions)
			if (sv == tempBuffer[v].center)
			{
				found = true;
				break;
			}

		if (!found)
			mesh.spritePositions.push_back(tempBuffer[v].center);
	}

	_Halo_vshOut *oBuffer = reinterpret_cast<_Halo_vshOut*>(cBuffer->buffer);

	for (uint v = 0; v < numVertices; v++)
	{
		_Halo_vsh &inBuffer = tempBuffer[v];
		_Halo_vshOut &currOutBuffer = *reinterpret_cast<_Halo_vshOut*>(cBuffer->buffer + (currentStride * v));

		int boneID = 0;
		for (auto &sv : mesh.spritePositions)
		{
			if (sv == inBuffer.center)
				break;

			boneID++;
		}

		currOutBuffer.spriteID = boneID;
		Vector2 UV = (inBuffer.way.Convert<float>() * (1.0f / 255.0f));
		UCVector bounds(inBuffer.size.X, inBuffer.size.Y, 0);
		float boundsScale = static_cast<float>(*reinterpret_cast<ushort*>(&inBuffer.size)) * (1.0f / USHRT_MAX);
		currOutBuffer.pos = inBuffer.center + bounds.Convert<float>() * (Vector(UV.X, UV.Y, 0.0f) - 0.5f) * boundsScale;
		currOutBuffer.uv = (UV * SHRT_MAX).Convert<short>();
		currOutBuffer.color = inBuffer.color;
	}

	free(tempBuffer);

	mesh.streamAttributes.resize(4);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);

		*reinterpret_cast<Vector2*>(descr.Header.packingData) = Vector2(1.0f, 1.0f);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R8G8B8A8_UNORM, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R32_UINT, 0);
	}
}

void RBMLambert::Load(BinReader * rd)
{
	rd->Read(shaderType, getBlockSize(RBMLambert, shaderType, endunk));

	ReadTextures(rd, 8);
	rd->Read(unk2);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 28;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);

		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);

		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 0);
	}	
	
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);

		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}
}

REFLECTOR_START_WNAMES(RBMGeneral, channelMask, channelAoMask, depthBias, specularPower, flags);

void RBMGeneral::Load(BinReader * rd)
{
	rd->Read(channelMask, getBlockSize(RBMGeneral, channelMask, endunk));

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 28;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);

		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);

		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);

		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}
}

REFLECTOR_START_WNAMES(RBMFacade, channelMask, channelDirtMask, emissiveMultiplier, depthBias, specularPower, flags);

void RBMFacade::Load(BinReader * rd)
{
	rd->Read(channelMask, getBlockSize(RBMFacade, channelMask, unk1));

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 40;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);

		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SNORM, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 0);
	}

	/*
	following float: 
		v8 = frac(data);
		v9 = floor(data) / 2048;
		// rest is handled in pixel shader
	*/
}

REFLECTOR_START_WNAMES(RBMWindow, specularPower);

void RBMWindow::Load(BinReader * rd)
{
	rd->Read(specularPower, getBlockSize(RBMWindow, specularPower, flags));

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 40;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 0);
	}
}

void RBMCarPaint::Load(BinReader * rd)
{
	rd->Read(twoToneColor1, getBlockSize(RBMCarPaint, twoToneColor1, flags));

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 24;
	const uint currentStrideSecondary = 28;
	const uint vBufferSize = numVertices * currentStride + numVertices * currentStrideSecondary + 4;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer, currentStrideSecondary);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(9);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformNormal_c, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformPoints_c, AmfFormat_R16G16B16A16_SNORM, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	mesh.boneIndexLookup.resize(256);

	for (auto &b : mesh.boneIndexLookup)
	{
		uint data;
		rd->Read(data);
		b = reinterpret_cast<short&>(data);
	}
}

void RBMDeformWindow::Load(BinReader * rd)
{
	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 48;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(8);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformNormal_c, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformPoints_c, AmfFormat_R16G16B16A16_SNORM, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	mesh.boneIndexLookup.resize(256);

	for (auto &b : mesh.boneIndexLookup)
	{
		uint data;
		rd->Read(data);
		b = reinterpret_cast<short&>(data);
	}

	uint pad;
	rd->Read(pad);
}

void RBMMerged::Load(BinReader * rd)
{

	ReadTextures(rd, 8);
	rd->Read(unk);
	rd->Read(useVertexBuffer);
	rd->Read(unk2);

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = useVertexBuffer ? 24 : 52;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);

	if (!useVertexBuffer)
	{
		rd->Skip(-4);
		meshID = -1;
		printline("[RBM]: Merged block doesn't contain vertex data, skipping.");
		return;
	}

	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(4);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_FLOAT, 0);
	}
}

REFLECTOR_START_WNAMES(RBMSkinnedGeneral, flags.f.flags, flags.f.technique, specularPower, rimIntensity, rimPower, rimWeights)

void RBMSkinnedGeneral::Load(BinReader * rd)
{
	rd->Read(flags, getBlockSize(RBMSkinnedGeneral, flags, rimWeights));

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const bool useWideWeights = flags.f.flags[RBMSkinnedGeneralFlags::WideBoneWeights];

	uint currentStride = useWideWeights ? 28 : 20;
	const uint currentStrideSecondary = 20;
	const uint vBufferSize = numVertices * currentStride + numVertices * currentStrideSecondary + 4;

	rd->SavePos();
	rd->Skip(vBufferSize);
	ReadRemaps(rd);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer, currentStrideSecondary);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	ReadRemaps(rd, &mesh);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(useWideWeights ? 9 : 7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM, 0);
	}

	if (useWideWeights)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT, 0);
	}

	if (useWideWeights)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}

}

void RBMSkinnedGeneralDecal::Load(BinReader * rd)
{
	rd->Read(flags, getBlockSize(RBMSkinnedGeneralDecal, flags, rimWeights));

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 20;
	const uint currentStrideSecondary = 28;
	const uint vBufferSize = numVertices * currentStride + numVertices * currentStrideSecondary + 4;

	rd->SavePos();
	rd->Skip(vBufferSize);
	ReadRemaps(rd);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer, currentStrideSecondary);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	ReadRemaps(rd, &mesh);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(8);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}
}

void RBMGeneral0::Load(BinReader * rd)
{
	rd->Read(channelMask, getBlockSize(RBMGeneral0, channelMask, flags));

	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 40;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 0);
	}
}

void RBMFacade0::Load(BinReader * rd)
{
	ReadTextures(rd, 8);
	rd->Read(type);

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 44;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);
	rd->Read(channelMask, getBlockSize(RBMFacade0, channelMask, flags));

	mesh.streamAttributes.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 0);
	}

	/*
	following float:
	v8 = frac(data);
	v9 = floor(data) / 2048;
	// rest is handled in pixel shader
	*/
}
