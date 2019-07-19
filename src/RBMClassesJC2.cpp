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

#include <cmath>
#include <climits>
#include "RBMClassesJC2.h"
#include "datas/binreader.hpp"
#include "datas/masterprinter.hpp"
#include "ADF.h"

REFLECTOR_START_WNAMES(RBMCarPaintSimpleConstants, twoToneColor1, twoToneColor2, specularPower, depthBias, reflectionMultiplier, flags);
REFLECTOR_START_WNAMES(RBMVegetationFoliageConstants, specularIntensity, specularPower, translucencyColorMask);
REFLECTOR_START_WNAMES(RBMGeneralConstants, channelMask, channelAoMask, depthBias, specularPower, flags);
REFLECTOR_START_WNAMES(RBMFacadeConstants, channelMask, channelDirtMask, emissiveMultiplier, depthBias, specularPower, flags);
REFLECTOR_START_WNAMES(RBMWindowConstants, specularPower);
REFLECTOR_START_WNAMES(RBMSkinnedGeneralConstants, flags, technique, specularPower, rimIntensity, rimPower, rimWeights);

void RBMCarPaintSimple::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint currentStride = 32;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}
}

void RBMFoliageBark::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMFoliageBarkConstants *atts = properties.GetItem<RBMFoliageBarkConstants>();

	rd->Read(mesh.numVertices);

	bool secondaryUVS = (atts->flags & 4) == 0;

	const uint currentStride = secondaryUVS ? 40 : 32;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(secondaryUVS ? 6 : 5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	if (secondaryUVS)
	{
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
		}
		
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c);
		}
	}
	else
	{
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
		}
	}
}

void RBMVegetationFoliage::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint currentStride = 40;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
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

void RBMBillboardFoliage::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint oldStride = sizeof(_BillboardFoliage_vsh);
	const uint currentStride = sizeof(_BillboardFoliage_vshOut);
	const uint vBufferSize = mesh.numVertices * oldStride;
	const uint modVBufferSize = mesh.numVertices * currentStride;

	_BillboardFoliage_vsh *tempBuffer = static_cast<_BillboardFoliage_vsh *>(malloc(vBufferSize));
	rd->ReadBuffer(reinterpret_cast<char *>(tempBuffer), vBufferSize);

	RBMBillboardFoliageMesh *cMesh = static_cast<RBMBillboardFoliageMesh *>(&mesh);
	cMesh->spritePositions.reserve(mesh.numVertices / 4);

	for (int v = 0; v < mesh.numVertices; v++)
	{
		bool found = false;

		for (auto &sv : cMesh->spritePositions)
			if (sv == tempBuffer[v].center)
			{
				found = true;
				break;
			}

		if (!found)
			cMesh->spritePositions.push_back(tempBuffer[v].center);
	}

	_BillboardFoliage_vshOut *oBuffer = reinterpret_cast<_BillboardFoliage_vshOut*>(curBuffer);
	const char *vtBuffer = curBuffer;

	for (int v = 0; v < mesh.numVertices; v++, oBuffer++)
	{
		_BillboardFoliage_vsh &inBuffer = tempBuffer[v];

		int boneID = 0;
		for (auto &sv : cMesh->spritePositions)
		{
			if (sv == inBuffer.center)
				break;

			boneID++;
		}

		oBuffer->spriteID = boneID;
		oBuffer->pos = inBuffer.center + Vector(inBuffer.offset[0], inBuffer.offset[1], 0.0f);
		oBuffer->uv = inBuffer.uv;
	}

	free(tempBuffer);

	curBuffer += modVBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(3);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R32_UINT);
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
	SVector pos;
	SVector2 uv;
	UCVector4 color;
	int spriteID;
};

void RBMHalo::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint currentStride = sizeof(_Halo_vshOut);
	const uint vBufferSize = mesh.numVertices * currentStride;
	_Halo_vsh *tempBuffer = static_cast<_Halo_vsh*>(malloc(vBufferSize));
	rd->ReadBuffer(reinterpret_cast<char*>(tempBuffer), vBufferSize);

	RBMBillboardFoliageMesh *cMesh = static_cast<RBMBillboardFoliageMesh *>(&mesh);
	cMesh->spritePositions.reserve(mesh.numVertices / 4);

	float vectorScale = 0.0f;
	_Halo_vshOut *oBuffer = reinterpret_cast<_Halo_vshOut*>(curBuffer);
	const char *vtBuffer = curBuffer;
	curBuffer += vBufferSize;

	std::vector<Vector> tmpPoses(mesh.numVertices);

	for (int v = 0; v < mesh.numVertices; v++)
	{
		_Halo_vsh &inBuffer = tempBuffer[v];

		bool found = false;

		for (auto &sv : cMesh->spritePositions)
			if (sv == tempBuffer[v].center)
			{
				found = true;
				break;
			}

		if (!found)
			cMesh->spritePositions.push_back(tempBuffer[v].center);

		Vector2 UV = (inBuffer.way.Convert<float>() * (1.0f / 255.0f));

		oBuffer[v].uv = (UV * SHRT_MAX).Convert<short>();
		oBuffer[v].color = inBuffer.color;

		UCVector bounds(inBuffer.size.X, inBuffer.size.Y, 0);
		float boundsScale = static_cast<float>(*reinterpret_cast<ushort *>(&inBuffer.size)) * (1.0f / USHRT_MAX);

		tmpPoses[v] = inBuffer.center + bounds.Convert<float>() * (Vector(UV.X, UV.Y, 0.0f) - 0.5f) * boundsScale;

		for (int b = 0; b < 3; b++)
		{
			float cVal = fabsf(tmpPoses[v][b]);

			if (cVal > vectorScale)
				vectorScale = cVal;
		}

	}

	const float vectorScaleFrac = 1.0f / vectorScale;

	for (int v = 0; v < mesh.numVertices; v++, oBuffer++)
	{
		_Halo_vsh &inBuffer = tempBuffer[v];
		
		int boneID = 0;
		for (auto &sv : cMesh->spritePositions)
		{
			if (sv == inBuffer.center)
				break;

			boneID++;
		}

		oBuffer->spriteID = boneID;
		oBuffer->pos = (tmpPoses[v] * vectorScaleFrac * SHRT_MAX).Convert<short>();
	}

	free(tempBuffer);

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(4);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float *>(descr.packingData) = vectorScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);

		*reinterpret_cast<Vector2*>(descr.packingData) = Vector2(1.0f, 1.0f);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R8G8B8A8_UNORM);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R32_UINT);
	}
}

void RBMLambert::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMLambertConstants *atts = properties.GetItem<RBMLambertConstants>();

	rd->Read(mesh.numVertices);

	const uint currentStride = 28;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);

		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);

		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT);
	}	
	
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);

		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}
}

void RBMGeneral::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMGeneralConstants *atts = properties.GetItem<RBMGeneralConstants>();

	rd->Read(mesh.numVertices);

	const uint currentStride = 28;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);

		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);

		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);

		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}
}

void RBMFacade::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMFacadeConstants *atts = properties.GetItem<RBMFacadeConstants>();

	rd->Read(mesh.numVertices);

	const uint currentStride = 40;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);

		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SNORM);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT);
	}

	/*
	following float: 
		v8 = frac(data);
		v9 = floor(data) / 2048;
		// rest is handled in pixel shader
	*/
}

void RBMWindow::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint currentStride = 40;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT);
	}
}

void RBMCarPaint::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	uint currentStride = 24;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(9);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformNormal_c, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformPoints_c, AmfFormat_R16G16B16A16_SNORM);
	}

	currentBufferOffset = 0;
	currentStride = 28;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer, 4);

	RBMCarPaintMesh *cMesh = static_cast<RBMCarPaintMesh *>(&mesh);
	
	cMesh->remaps = reinterpret_cast<int *>(curBuffer);
	rd->ReadBuffer(curBuffer, 1024);
	curBuffer += 1024;
}

void RBMDeformWindow::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint currentStride = 48;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer, 4);
	mesh.descriptors.resize(8);
	
	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformNormal_c, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformPoints_c, AmfFormat_R16G16B16A16_SNORM);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	RBMCarPaintMesh *cMesh = static_cast<RBMCarPaintMesh *>(&mesh);

	cMesh->remaps = reinterpret_cast<int *>(curBuffer);
	rd->ReadBuffer(curBuffer, 1024);
	curBuffer += 1024;

	rd->Skip(4);
}

void RBMMerged::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMMergedMeshConstants *mAtts = mesh.properties.GetItem<RBMMergedMeshConstants>();

	rd->Read(mesh.numVertices);

	const uint currentStride = mAtts->useVertexBuffer ? 24 : 52;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	if (!mAtts->useVertexBuffer)
	{
		printline("[RBM]: Merged block doesn't contain vertex data, skipping.");

		rd->Skip(vBufferSize);
	}
	else
	{
		rd->ReadBuffer(curBuffer, vBufferSize);
		curBuffer += vBufferSize;
	}

	rd->Read(mesh.numIndices);

	if (!mAtts->useVertexBuffer)
	{
		rd->Skip(mesh.numIndices * 2);
		return;
	}

	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(4);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_FLOAT);
	}
}

void RBMSkinnedGeneral::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMSkinnedGeneralConstants *atts = properties.GetItem<RBMSkinnedGeneralConstants>();
	const bool useWideWeights = atts->flags[RBMSkinnedGeneralFlags::WideBoneWeights];

	rd->Read(mesh.numVertices);

	uint currentStride = useWideWeights ? 28 : 20;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(useWideWeights ? 9 : 7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM);
	}

	if (useWideWeights)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT);
	}

	if (useWideWeights)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT);
	}

	currentBufferOffset = 0;
	currentStride = 20;	
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	RBMSkinnedGeneralMesh *cMesh = static_cast<RBMSkinnedGeneralMesh *>(&mesh);
	rd->Read(cMesh->remapHdr);
	cMesh->remaps = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, cMesh->remapHdr.numRemaps * 2);
	curBuffer += cMesh->remapHdr.numRemaps * 2;
	ApplyPadding(curBuffer, 2);
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMSkinnedGeneralDecal::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	uint currentStride = 20;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(8);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT);
	}

	currentBufferOffset = 0;
	currentStride = 28;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BiTangent, AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	RBMSkinnedGeneralMesh *cMesh = static_cast<RBMSkinnedGeneralMesh *>(&mesh);
	rd->Read(cMesh->remapHdr);
	cMesh->remaps = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, cMesh->remapHdr.numRemaps * 2);
	curBuffer += cMesh->remapHdr.numRemaps * 2;
	ApplyPadding(curBuffer, 2);
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMGeneral0::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint currentStride = 40;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
	mesh.descriptors.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT);
	}
}

void RBMFacade0::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint currentStride = 44;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
	mesh.descriptors.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT);
	}

	/*
	following float:
	v8 = frac(data);
	v9 = floor(data) / 2048;
	// rest is handled in pixel shader
	*/
}

void RBMUIOverlay::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	const uint currentStride = 16;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
	mesh.descriptors.resize(2);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}
}
