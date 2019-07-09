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

#include "RBMClassesJC3.h"
#include "datas/binreader.hpp"
#include "datas/masterprinter.hpp"

void RBMVegetationFoliage3::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMVegetationFoliage3Constants *atts = properties.GetItem<RBMVegetationFoliage3Constants>();

	rd->Read(mesh.numVertices);

	uint currentStride = 12;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV1Scale;
	}

	currentBufferOffset = 0;
	currentStride = 8;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE);
	}

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMFoliageBark2::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMFoliageBark2Constants *atts = properties.GetItem<RBMFoliageBark2Constants>();

	rd->Read(mesh.numVertices);

	uint currentStride = 12;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE);
	}

	currentBufferOffset = 0;
	currentStride = 8;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV2Scale;
	}

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMGeneralSimple::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMGeneralSimpleConstants *atts = properties.GetItem<RBMGeneralSimpleConstants>();

	rd->Read(mesh.numVertices);

	uint currentStride = 8;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	currentBufferOffset = 0;
	currentStride = 20;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMWaterHull::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	uint currentStride = 12;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(1);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}
}

void RBMBavariumShiled::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	uint currentStride = 28;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	rd->Read(mesh.numIndices);
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
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
	}
}

void RBMWindow1::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	rd->Read(mesh.numVertices);

	uint currentStride = 40;
	uint vBufferSize = mesh.numVertices * currentStride;
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

void RBMLayered::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMLayeredConstants *atts = properties.GetItem<RBMLayeredConstants>();

	rd->Read(mesh.numVertices);

	uint currentStride = 8;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	currentBufferOffset = 0;
	currentStride = 20;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMLandmark::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMLandmarkConstants *atts = properties.GetItem<RBMLandmarkConstants>();

	rd->Read(mesh.numVertices);

	const uint currentStride = 8;
	const uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(4);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	currentBufferOffset = 0;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT);
	}

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMGeneralMK3::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMGeneralMK3Constants *atts = properties.GetItem<RBMGeneralMK3Constants>();

	bool skinned = (atts->flags & 0x20) != 0;
	bool singleskin = (atts->flags & 0x8000) != 0;

	GeneralMeshConstants *cn = new GeneralMeshConstants();
	cn->flags(GeneralMeshConstantsFlags::isDestructionMesh, singleskin);
	cn->flags(GeneralMeshConstantsFlags::isSkinnedMesh, skinned);
	mesh.properties.item.vPtr = cn;
	mesh.properties.objectHash = GeneralMeshConstants::HASH;

	rd->Read(mesh.numVertices);

	uint currentStride = skinned ? 16 : 8;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(skinned ? 9 : 7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}
	if (singleskin)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R16_SINT);
	}
	else
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	if (skinned)
	{
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT);
		}
	}

	currentBufferOffset = 0;
	currentStride = 20;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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

	if (skinned || singleskin)
	{
		RBMGeneralMK3Mesh *cMesh = static_cast<RBMGeneralMK3Mesh *>(&mesh);
		rd->Read(cMesh->remapHdr);
		cMesh->remaps = reinterpret_cast<ushort *>(curBuffer);
		rd->ReadBuffer(curBuffer, cMesh->remapHdr.numRemaps);
		curBuffer += cMesh->remapHdr.numRemaps;
		ApplyPadding(curBuffer, 2);
	}

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMGeneral6::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMGeneral6Constants *atts = properties.GetItem<RBMGeneral6Constants>();

	rd->Read(mesh.numVertices);

	uint currentStride = 8;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	currentBufferOffset = 0;
	currentStride = 20;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMCarLight::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMCarLightConstants *atts = properties.GetItem<RBMCarLightConstants>();
	RBMCarLightMesh *msh = static_cast<RBMCarLightMesh*>(&mesh);

	msh->remaps = atts->remapTable;

	rd->Read(mesh.numVertices);

	uint currentStride = 12;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	currentBufferOffset = 0;
	currentStride = 24;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMCarPaint14::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMCarPaint14Constants *atts = properties.GetItem<RBMCarPaint14Constants>();
	RBMCarPaint14Mesh *msh = static_cast<RBMCarPaint14Mesh*>(&mesh);

	bool deformable = (atts->flags & 0x1000) != 0;
	bool skinned = (atts->flags & 0x2000) != 0;
	bool uv3 = ((atts->flags & 0x20) | (atts->flags & 0x40)) != 0;

	msh->deformRemaps = atts->remapTable;

	CarPaintMeshConstants *cn = new CarPaintMeshConstants();
	cn->flags(CarPaintMeshConstantsFlags::deformable, deformable);
	cn->flags(CarPaintMeshConstantsFlags::skinned, skinned);
	mesh.properties.item.vPtr = cn;
	mesh.properties.objectHash = CarPaintMeshConstants::HASH;

	if (deformable && skinned)
	{
		printwarning("[RBMCarPaint14]: Cannot have deformable and skinned flags at the same time, check me!")
	}

	rd->Read(mesh.numVertices);

	uint currentStride = 12 + (deformable ? 12 : 0) + (skinned ? 4 : 0);
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(5 + (deformable ? 2 : 0) + (skinned ? 1 : 0) + (uv3 ? 1 : 0));

	int currentBufferOffset = 0;
	int currentDesc = 0;

	const uint currentStrideSecondary = deformable ? 32 : 24;
	const uint uv3Stride = 8;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT);
	}

	if (deformable)
	{
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_DeformNormal_c, AmfFormat_R32_UNIT_VEC_AS_FLOAT);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_DeformPoints_c, AmfFormat_R16G16B16A16_SNORM);
		}
	}

	if (skinned)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R32_UINT);
	}

	currentBufferOffset = 0;
	currentStride = deformable ? 32 : 24;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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

	if (uv3)
	{
		currentBufferOffset = 0;
		currentStride = 8;
		rd->Read(mesh.numVertices);
		vtBuffer = curBuffer;
		vBufferSize = mesh.numVertices * currentStride;
		rd->ReadBuffer(curBuffer, vBufferSize);
		curBuffer += vBufferSize;

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT);
		}
	}

	if (skinned)
	{
		rd->Read(msh->remapHdr);
		msh->remaps = reinterpret_cast<ushort *>(curBuffer);
		rd->ReadBuffer(curBuffer, msh->remapHdr.numRemaps);
		curBuffer += msh->remapHdr.numRemaps;
		ApplyPadding(curBuffer, 2);
	}

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMGeneral3::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMGeneral3Constants *atts = properties.GetItem<RBMGeneral3Constants>();

	rd->Read(mesh.numVertices);

	uint currentStride = 8;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;
	mesh.descriptors.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;
	
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	currentBufferOffset = 0;
	currentStride = 20;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMCharacter9::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMCharacter9Constants *atts = properties.GetItem<RBMCharacter9Constants>();
	RBMCharacter9Mesh *msh = static_cast<RBMCharacter9Mesh*>(&mesh);

	rd->Read(mesh.numVertices);

	uint currentStride = 24;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	rd->Read(msh->remapHdr);
	msh->remaps = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, msh->remapHdr.numRemaps);
	curBuffer += msh->remapHdr.numRemaps;
	ApplyPadding(curBuffer, 2);
	
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE);
	}
}

void RBMCharacter6::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMCharacter6Constants *atts = properties.GetItem<RBMCharacter6Constants>();
	RBMCharacter6Mesh *msh = static_cast<RBMCharacter6Mesh*>(&mesh);

	bool uv2 = (atts->flags & 2) != 0;

	rd->Read(mesh.numVertices);

	uint currentStride = uv2 ? 28 : 24;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;

	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	rd->Read(msh->remapHdr);
	msh->remaps = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, msh->remapHdr.numRemaps);
	curBuffer += msh->remapHdr.numRemaps;
	ApplyPadding(curBuffer, 2);
	
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);

	mesh.descriptors.resize(uv2 ? 7 : 6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV1Scale;
	}

	if (uv2)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
		*reinterpret_cast<Vector2*>(descr.packingData) = atts->UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE);
	}
}

void RBMRoad::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMRoadConstants *atts = properties.GetItem<RBMRoadConstants>();
	bool skinned = (atts->flags & 0x20) != 0;

	rd->Read(mesh.numVertices);

	uint currentStride = skinned ? 16 : 8;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	mesh.descriptors.resize(skinned ? 9 : 7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	if (skinned)
	{	
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT);
		}
	}

	currentBufferOffset = 0;
	currentStride = 20;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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
	
	if(skinned)
	{
		RBMRoadMesh *msh = static_cast<RBMRoadMesh*>(&mesh);
		rd->Read(msh->remapHdr);
		msh->remaps = reinterpret_cast<ushort *>(curBuffer);
		rd->ReadBuffer(curBuffer, msh->remapHdr.numRemaps);
		curBuffer += msh->remapHdr.numRemaps;
		ApplyPadding(curBuffer, 2);
	}
	
	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}

void RBMGeneralSimple3::ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh)
{
	RBMGeneralSimple3Constants *atts = properties.GetItem<RBMGeneralSimple3Constants>();

	rd->Read(mesh.numVertices);

	uint currentStride = 8;
	uint vBufferSize = mesh.numVertices * currentStride;
	const char *vtBuffer = curBuffer;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

	mesh.descriptors.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr.packingData) = atts->vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	currentBufferOffset = 0;
	currentStride = 20;
	rd->Read(mesh.numVertices);
	vtBuffer = curBuffer;
	vBufferSize = mesh.numVertices * currentStride;
	rd->ReadBuffer(curBuffer, vBufferSize);
	curBuffer += vBufferSize;

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

	rd->Read(mesh.numIndices);
	mesh.indexBuffer = reinterpret_cast<ushort *>(curBuffer);
	rd->ReadBuffer(curBuffer, mesh.numIndices * 2);
	curBuffer += mesh.numIndices * 2;
	ApplyPadding(curBuffer);
}
