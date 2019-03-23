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

#include "RBNClasses.h"
#include "datas/binreader.hpp"
#include "datas\masterprinter.hpp"
#include "ADF.h"
#include "AmfModel.h"

void RBNGeneral::Load(BinReader * rd)
{
	rd->Read(unk[0], getBlockSize(RBNGeneral, unk[0], fltend));

	ReadTextures(rd);

	rd->Read(rbshash);
	rd->Read(meshID);
}

void RBNGeneral::Link(ADF *base)
{
	RBMMasterBlock::Link(base);
	AmfMeshHeader *mHeader = base->FindInstance<AmfMeshHeader>();
	AmfMeshBuffers *mBuffers = base->FindInstance<AmfMeshBuffers>();

	if (!mHeader)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshHeader instance."));
		return;
	}

	if (!mBuffers)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshBuffers instance."));
		return;
	}
	
	AmfMesh &mesh = mHeader->lodGroups[0].meshes[meshID];

	mesh.streamAttributes.resize(6 + additionalUVSets);

	int currentBufferOffset = 0;
	int currentDesc = 0;
	int currentStride = 8;

	AmfStreamAttribute *descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
	*reinterpret_cast<float*>(descr->Header.packingData) = vertexScale;
	
	
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Unspecified, AmfFormat_R16_SINT);

	currentStride = (4 * (additionalUVSets + 1)) + 12;
	currentBufferOffset = 0;

	for (uint u = 0; u <= additionalUVSets; u++)
	{
		Vector2 *uvScale = nullptr;

		switch (u)
		{
		case 0:
			uvScale = &UV1Scale;
			break;
		case 1:
			uvScale = &UV2Scale;
			break;
		case 2:
			uvScale = &UV3Scale;
			break;
		default:
		{
			printwarning("[ADF ", <<_T(__FUNCTION__) << _T("]: unhandled UV set ") << u);
			break; 
		}
		}

		descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);

		if (uvScale)
			*reinterpret_cast<Vector2*>(descr->Header.packingData) = *uvScale;

	}

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);	
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);	
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, 1);
}

void RBNCharacter::Load(BinReader * rd)
{
	rd->Read(flags, getBlockSize(RBNCharacter, flags, fltend));

	ReadTextures(rd);

	rd->Read(rbshash);
	rd->Read(meshID);
}

void RBNCharacter::Link(ADF * base)
{
	RBMMasterBlock::Link(base);
	AmfMeshHeader *mHeader = base->FindInstance<AmfMeshHeader>();
	AmfMeshBuffers *mBuffers = base->FindInstance<AmfMeshBuffers>();

	if (!mHeader)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshHeader instance."));
		return;
	}

	if (!mBuffers)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshBuffers instance."));
		return;
	}

	AmfMesh &mesh = mHeader->lodGroups[0].meshes[meshID];

	mesh.streamAttributes.resize(6 + additionalUVSets);

	bool trimmedWeights = (flags & 0x10000) != 0;
	int currentBufferOffset = 0;
	int currentDesc = 0;
	const int currentStride = 8 + (trimmedWeights ? 4 : 8) + (4 * (additionalUVSets + 1)) + 4;

	AmfStreamAttribute *descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
	*reinterpret_cast<float*>(descr->Header.packingData) = vertexScale;
	
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Unspecified, AmfFormat_R16_SINT);

	if (trimmedWeights)
	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_BoneWeight, AmfFormat_R8G8_UNORM);
		descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_BoneIndex, AmfFormat_R8G8_UINT);
	}
	else
	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM);
		descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT);
	}

	{
		std::vector<bool> idxs(256);
		const int numItems = trimmedWeights ? 2 : 4;
		int numRemaps = 0;

		for (int t = 0; t < mesh.Header.vertexCount; t++)
		{
			const uchar *boneIndicies = reinterpret_cast<uchar *>(mBuffers->vertexBuffers[0]->buffer + (t * currentStride) + descr->Header.streamOffset);

			for (int i = 0; i < numItems; i++)
			{
				const uchar cIndex = *(boneIndicies + i);

				if (!idxs[cIndex])
				{
					idxs[cIndex] = true;
					numRemaps++;
				}
			}
		}

		mesh.boneIndexLookup.reserve(numRemaps);
		std::vector<uchar> invertedLookups(256);

		for (int t = 0; t < 256; t++)
			if (idxs[t])
			{
				mesh.boneIndexLookup.push_back(t);
				invertedLookups[t] = mesh.boneIndexLookup.size() - 1;
			}

		for (int t = 0; t < mesh.Header.vertexCount; t++)
		{
			uchar *boneIndicies = reinterpret_cast<uchar *>(mBuffers->vertexBuffers[0]->buffer + (t * currentStride) + descr->Header.streamOffset);

			for (int i = 0; i < numItems; i++)
			{
				uchar &cIndex = *(boneIndicies + i);

				cIndex = invertedLookups[cIndex];
			}
		}

	}

	for (uint u = 0; u <= additionalUVSets; u++)
	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM);
	}

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE);
}

void RBNCarPaint::Load(BinReader * rd)
{
	rd->Read(unk, getBlockSize(RBNCarPaint, unk, fltend));

	ReadTextures(rd);

	rd->Read(rbshash);
	rd->Read(meshID);
}

void RBNCarPaint::Link(ADF * base)
{
	RBMMasterBlock::Link(base);
	AmfMeshHeader *mHeader = base->FindInstance<AmfMeshHeader>();
	AmfMeshBuffers *mBuffers = base->FindInstance<AmfMeshBuffers>();

	if (!mHeader)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshHeader instance."));
		return;
	}

	if (!mBuffers)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshBuffers instance."));
		return;
	}

	AmfMesh &mesh = mHeader->lodGroups[0].meshes[meshID];
	bool deformable = (flags & 0x8) != 0;

	mesh.streamAttributes.resize(5 + (deformable ? 3 : 0));

	int currentBufferOffset = 0;
	int currentDesc = 0;
	int currentStride = 12 + (deformable ? 4 : 0);

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	if (deformable)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_DeformNormal_c, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 0);
	}

	currentStride = 24 + (deformable ? 8 : 0);
	currentBufferOffset = 0;

	for (uint u = 0; u < 2; u++)
	{
		RBM_NEW_DESCRIPTOR(AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, 1);
	}

	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}
}

void RBNWindow::Load(BinReader * rd)
{
	rd->Read(flt1, 16);

	ReadTextures(rd);

	rd->Read(rbshash);
	rd->Read(meshID);
}

void RBNWindow::Link(ADF * base)
{
	RBMMasterBlock::Link(base);
	AmfMeshHeader *mHeader = base->FindInstance<AmfMeshHeader>();
	AmfMeshBuffers *mBuffers = base->FindInstance<AmfMeshBuffers>();

	if (!mHeader)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshHeader instance."));
		return;
	}

	if (!mBuffers)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshBuffers instance."));
		return;
	}

	AmfMesh &mesh = mHeader->lodGroups[0].meshes[meshID];

	mesh.streamAttributes.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;
	const int currentStride = 40;

	{
		RBM_NEW_DESCRIPTOR(AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, 0);
	}

	for (uint u = 0; u < 2; u++)
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

void RBNXXXX::Load(BinReader * rd)
{
	rd->Read(unk, getBlockSize(RBNXXXX, unk, fltend));

	ReadTextures(rd);

	rd->Read(rbshash);
	rd->Read(meshID);
}

void RBNXXXX::Link(ADF * base)
{
	RBMMasterBlock::Link(base);
	AmfMeshHeader *mHeader = base->FindInstance<AmfMeshHeader>();
	AmfMeshBuffers *mBuffers = base->FindInstance<AmfMeshBuffers>();

	if (!mHeader)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshHeader instance."));
		return;
	}

	if (!mBuffers)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find MeshBuffers instance."));
		return;
	}

	AmfMesh &mesh = mHeader->lodGroups[0].meshes[meshID];

	mesh.streamAttributes.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;
	int currentStride = 8;

	{
		AmfStreamAttribute *descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Position, AmfFormat_R16G16B16_SNORM);
		*reinterpret_cast<float*>(descr->Header.packingData) = vertexScale;
	}

	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Unspecified, AmfFormat_R16_SINT);
	}

	currentStride = 12;
	currentBufferOffset = 0;

	{
		AmfStreamAttribute *descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, 1);
		*reinterpret_cast<Vector2*>(descr->Header.packingData) = UV1Scale;
	}

	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}

	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, 1);
	}
}
