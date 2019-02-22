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
#include "datas\masterprinter.hpp"
#include "ADF.h"
#include "AmfModel.h"
#include "AmfMesh.h"
#include "AdfRegistry.h"

void RBMVegetationFoliage3::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMVegetationFoliage3, flt, null));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMVegetationFoliage3, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 12;
	const uint currentStrideSecondary = 8;
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

	mesh.streamAttributes.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE, 1);
	}
}

void RBMFoliageBark2::Load(BinReader * rd)
{
	rd->Read(vertexScale, getBlockSize(RBMFoliageBark2, vertexScale, endflt));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMFoliageBark2, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 12;
	const uint currentStrideSecondary = 8;
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

	mesh.streamAttributes.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;
	
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}
}

void RBMGeneralSimple::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMGeneralSimple, flt, unkend));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMGeneralSimple, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 8;
	const uint currentStrideSecondary = 20;
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

	mesh.streamAttributes.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
	}
}

void RBMWaterHull::Load(BinReader * rd)
{
	rd->Read(flt);
	rd->Read(wireScale, getBlockSize(RBMGeneralSimple, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 12;
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

	mesh.streamAttributes.resize(1);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}
}

void RBMBavariumShiled::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMBavariumShiled, flt, endflt));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMBavariumShiled, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 28;
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

	mesh.streamAttributes.resize(4);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
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
}

void RBMWindow1::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMWindow1, flt, unk));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMWindow1, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 40;
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

void RBMLayered::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMLayered, flt, endflt));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMLayered, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 8;
	const uint currentStrideSecondary = 20;
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

	mesh.streamAttributes.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
	}
}

void RBMLandmark::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMLandmark, flt, endunk));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMLandmark, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 8;
	const uint currentStrideSecondary = 8;
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

	mesh.streamAttributes.resize(4);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
	}
}

void RBMGeneralMK3::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMGeneralMK3, flt, unk03));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMGeneralMK3, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	bool skinned = (flags & 0x20) != 0;
	bool singleskin = (flags & 0x8000) != 0;

	uint currentStride = skinned ? 16 : 8;
	const uint currentStrideSecondary = 20;
	const uint vBufferSize = numVertices * currentStride + numVertices * currentStrideSecondary + 4;

	rd->SavePos();
	rd->Skip(vBufferSize);

	if (skinned || singleskin)
		ReadRemaps(rd);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer, currentStrideSecondary);
	mesh.meshProperties = ADFPropsStorage[GeneralMeshConstants::HASH]();
	GeneralMeshConstants *cn = static_cast<GeneralMeshConstants*>(mesh.meshProperties->GetProperties());
	cn->flags(GeneralMeshConstantsFlags::isDestructionMesh, singleskin);
	cn->flags(GeneralMeshConstantsFlags::isSkinnedMesh, skinned);

	rd->ReadBuffer(cBuffer->buffer, vBufferSize);

	if (skinned || singleskin)
		ReadRemaps(rd, &mesh);

	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(skinned ? 9 : 7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}
	if (singleskin)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R16_SINT, 0);
	}
	else
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	if (skinned)
	{
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM, 0);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT, 0);
		}
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
	}
}

void RBMGeneral6::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMGeneral6, flt, bbox));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMGeneral6, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 8;
	const uint currentStrideSecondary = 20;
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

	mesh.streamAttributes.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
	}
}

void RBMCarLight::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMCarLight, flt, endflt));
	rd->Skip(1024);
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMCarLight, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 12;
	const uint currentStrideSecondary = 24;
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

	mesh.streamAttributes.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}
}

void RBMCarPaint14::Load(BinReader * rd)
{
	std::vector<int> deformTable;
	
	rd->Read(flags, getBlockSize(RBMCarPaint14, flags, endflt));
	rd->ReadContainer(deformTable, 256);
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMCarPaint14, wireScale, textureDensities));

	bool deformable = (flags & 0x1000) != 0;
	bool skinned = (flags & 0x2000) != 0;
	bool uv3 = ((flags & 0x20) | (flags & 0x40)) != 0;

	AdfProperties *props = ADFPropsStorage[CarPaintMeshConstants::HASH]();
	CarPaintMeshConstants *carPaintProps = static_cast<CarPaintMeshConstants*>(props->GetProperties());
	carPaintProps->flags(CarPaintMeshConstantsFlags::deformable, deformable);
	carPaintProps->flags(CarPaintMeshConstantsFlags::skinned, skinned);

	if (deformable && skinned)
	{
		printwarning("[RBMCarPaint14]: Cannot have deformable and skinned flags at the same time, check me!")
	}

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 12 + (deformable ? 12 : 0) + (skinned ? 4 : 0);
	const uint currentStrideSecondary = deformable ? 32 : 24;
	const uint uv3Stride = 8;
	const uint vBufferSize = numVertices * currentStride + numVertices * currentStrideSecondary + 4 + (uv3 ? numVertices * uv3Stride + 4 : 0);

	rd->SavePos();
	rd->Skip(vBufferSize);

	if (skinned)
		ReadRemaps(rd);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer, currentStrideSecondary);
	mesh.meshProperties = props;

	if (deformable)
	{
		mesh.boneIndexLookup.resize(256);

		int currentDeformIndex = 0;

		for (auto &b : mesh.boneIndexLookup)
		{
			b = deformTable[currentDeformIndex] - 1;
			currentDeformIndex++;
		}
	}

	if (uv3)
	{
		mesh.vertexStreamOffsets.push_back(mesh.vertexStreamOffsets.back() + numVertices * currentStrideSecondary + 4);
		mesh.vertexStreamStrides.push_back(uv3Stride);
		mesh.vertexBufferIndices.push_back(mesh.vertexBufferIndices.back());
	}

	rd->ReadBuffer(cBuffer->buffer, vBufferSize);

	if (skinned)
		ReadRemaps(rd, &mesh);

	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(5 + (deformable ? 2 : 0) + (skinned ? 1 : 0) + (uv3 ? 1 : 0));

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	if (deformable)
	{
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_DeformNormal_c, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0); 
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_DeformPoints_c, AmfFormat_R16G16B16A16_SNORM, 0);
		}
	}

	if (skinned)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R32_UINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	if (uv3)
	{
		currentBufferOffset = 0;
		currentStride = uv3Stride;

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 2);
		}
	}
}

void RBMGeneral3::Load(BinReader * rd)
{
	rd->Read(flt, getBlockSize(RBMGeneral3, flt, endunk));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMGeneral3, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 8;
	const uint currentStrideSecondary = 20;
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

	mesh.streamAttributes.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
	}
}

void RBMCharacter9::Load(BinReader * rd)
{
	rd->Read(flags, getBlockSize(RBMCharacter9, flags, endflt));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMCharacter9, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	const uint currentStride = 24;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);
	ReadRemaps(rd);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	ReadRemaps(rd, &mesh);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE, 0);
	}
}

void RBMCharacter6::Load(BinReader * rd)
{
	rd->Read(flags, getBlockSize(RBMCharacter6, flags, endflt));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMCharacter6, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	bool uv2 = (flags & 2) != 0;

	const uint currentStride = uv2 ? 28 : 24;
	const uint vBufferSize = numVertices * currentStride;

	rd->SavePos();
	rd->Skip(vBufferSize);
	ReadRemaps(rd);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	ReadRemaps(rd, &mesh);
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(uv2 ? 7 : 6);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT, 0);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	if (uv2)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 0);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE, 0);
	}
}

void RBMRoad::Load(BinReader * rd)
{
	rd->Read(unk00, getBlockSize(RBMRoad, unk00, endunk));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMRoad, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	bool skinned = (flags & 0x20) != 0;

	uint currentStride = skinned ? 16 : 8;
	const uint currentStrideSecondary = 20;
	const uint vBufferSize = numVertices * currentStride + numVertices * currentStrideSecondary + 4;

	rd->SavePos();
	rd->Skip(vBufferSize);

	if (skinned)
		ReadRemaps(rd);

	uint numFaces;
	rd->Read(numFaces);
	rd->RestorePos();

	const uint bufferSize = 2 * numFaces + vBufferSize;

	AmfBuffer *cBuffer;
	AmfMesh &mesh = LoadDependencies(bufferSize, numVertices, currentStride, cBuffer, currentStrideSecondary);
	rd->ReadBuffer(cBuffer->buffer, vBufferSize);
	
	if (skinned)
		ReadRemaps(rd, &mesh);
	
	LoadFaces(rd, mesh, vBufferSize, cBuffer);

	mesh.streamAttributes.resize(skinned ? 9 : 7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	if (skinned)
	{	
		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM, 0);
		}

		{
			RBM_NEW_DESCRIPTOR(AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT, 0);
		}
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
	}
	
}

void RBMGeneralSimple3::Load(BinReader * rd)
{
	rd->Read(unk, getBlockSize(RBMGeneralSimple3, unk, bbox));
	ReadTextures(rd);
	rd->Read(wireScale, getBlockSize(RBMGeneralSimple3, wireScale, textureDensities));

	uint numVertices;
	rd->Read(numVertices);

	uint currentStride = 8;
	const uint currentStrideSecondary = 20;
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

	mesh.streamAttributes.resize(7);

	int currentBufferOffset = 0;
	int currentDesc = 0;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R16G16B16_SNORM, 0);
		*reinterpret_cast<float*>(descr.Header.packingData) = vertexScale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Unspecified, AmfFormat_R16_SINT, 0);
	}

	currentBufferOffset = 0;
	currentStride = currentStrideSecondary;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV1Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr.Header.packingData) = UV2Scale;
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
	}
}
