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
#include "datas/masterprinter.hpp"
#include "ADF.h"

void RBNGeneral_Link(ADF *base, RBSMesh &cMesh, RBMMaterial *cMat)
{
	RBNGeneralConstants *atts = cMat->GetAttributes<RBNGeneralConstants>();

	cMesh.descriptors.resize(6 + atts->additionalUVSets);

	int currentBufferOffset = 0;
	int currentDesc = 0;
	int currentStride = cMesh.vtBuffersStrides[0];

	AmfStreamAttribute *descr = RBMNewDescriptor(cMesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Position, AmfFormat_R16G16B16_SNORM, cMesh.vtBuffers[0]);
	*reinterpret_cast<float*>(descr->packingData) = atts->vertexScale;
	
	
	RBMNewDescriptor(cMesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Unspecified, AmfFormat_R16_SINT, cMesh.vtBuffers[0]);

	currentStride = cMesh.vtBuffersStrides[1];
	currentBufferOffset = 0;

	for (uint u = 0; u <= atts->additionalUVSets; u++)
	{
		Vector2 *uvScale = nullptr;

		switch (u)
		{
		case 0:
			uvScale = &atts->UV1Scale;
			break;
		case 1:
			uvScale = &atts->UV2Scale;
			break;
		case 2:
			uvScale = &atts->UV3Scale;
			break;
		default:
		{
			printwarning("[ADF ", <<_T(__FUNCTION__) << _T("]: unhandled UV set ") << u);
			break; 
		}
		}

		descr = RBMNewDescriptor(cMesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, cMesh.vtBuffers[1]);

		if (uvScale)
			*reinterpret_cast<Vector2*>(descr->packingData) = *uvScale;

	}

	RBMNewDescriptor(cMesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, cMesh.vtBuffers[1]);
	RBMNewDescriptor(cMesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, cMesh.vtBuffers[1]);
	RBMNewDescriptor(cMesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, cMesh.vtBuffers[1]);
}

void RBNCharacter_Link(ADF * base, RBSMesh &mesh, RBMMaterial *cMat)
{
	RBNCharacterConstants *atts = cMat->GetAttributes<RBNCharacterConstants>();

	mesh.descriptors.resize(6 + atts->additionalUVSets);

	bool trimmedWeights = (atts->flags & 0x10000) != 0;
	int currentBufferOffset = 0;
	int currentDesc = 0;
	const int currentStride = mesh.vtBuffersStrides[0];

	AmfStreamAttribute *descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Position, AmfFormat_R16G16B16_SNORM, mesh.vtBuffers[0]);
	*reinterpret_cast<float*>(descr->packingData) = atts->vertexScale;
	
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Unspecified, AmfFormat_R16_SINT, mesh.vtBuffers[0]);

	if (trimmedWeights)
	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_BoneWeight, AmfFormat_R8G8_UNORM, mesh.vtBuffers[0]);
		descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_BoneIndex, AmfFormat_R8G8_UINT, mesh.vtBuffers[0]);
	}
	else
	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_BoneWeight, AmfFormat_R8G8B8A8_UNORM, mesh.vtBuffers[0]);
		descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_BoneIndex, AmfFormat_R8G8B8A8_UINT, mesh.vtBuffers[0]);
	}

	{
		std::vector<bool> idxs(256);
		const int numItems = trimmedWeights ? 2 : 4;
		int numRemaps = 0;

		for (int t = 0; t < mesh.numVertices; t++)
		{
			const uchar *boneIndicies = reinterpret_cast<const uchar *>(mesh.vtBuffers[0] + (t * currentStride) + descr->streamOffset);

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
				invertedLookups[t] = static_cast<uchar>(mesh.boneIndexLookup.size() - 1);
			}

		for (int t = 0; t < mesh.numVertices; t++)
		{
			uchar *boneIndicies = reinterpret_cast<uchar *>(mesh.vtBuffers[0] + (t * currentStride) + descr->streamOffset);

			for (int i = 0; i < numItems; i++)
			{
				uchar &cIndex = *(boneIndicies + i);

				cIndex = invertedLookups[cIndex];
			}
		}
	}

	for (uint u = 0; u <= atts->additionalUVSets; u++)
	{
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, mesh.vtBuffers[0]);
	}

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TangentSpace, AmfFormat_R8G8B8A8_TANGENT_SPACE, mesh.vtBuffers[0]);
}

void RBNCarPaint_Link(ADF * base, RBSMesh &mesh, RBMMaterial *cMat)
{
	RBNCarPaintConstants *atts = cMat->GetAttributes<RBNCarPaintConstants>();
	bool deformable = (atts->flags & 0x8) != 0;

	mesh.descriptors.resize(5 + (deformable ? 3 : 0));

	int currentBufferOffset = 0;
	int currentDesc = 0;
	int currentStride = mesh.vtBuffersStrides[0];

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, mesh.vtBuffers[0]);

	if (deformable)
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_DeformNormal_c, AmfFormat_R32_UNIT_VEC_AS_FLOAT, mesh.vtBuffers[0]);

	currentStride = mesh.vtBuffersStrides[1];
	currentBufferOffset = 0;

	for (uint u = 0; u < 2; u++)
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, mesh.vtBuffers[1]);

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, mesh.vtBuffers[1]);
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, mesh.vtBuffers[1]);
}

void RBNWindow_Link(ADF * base, RBSMesh &mesh, RBMMaterial *cMat)
{
	mesh.descriptors.resize(6);

	int currentBufferOffset = 0;
	int currentDesc = 0;
	const int currentStride = mesh.vtBuffersStrides[0];

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Position, AmfFormat_R32G32B32_FLOAT, mesh.vtBuffers[0]);

	for (uint u = 0; u < 2; u++)
		RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TextureCoordinate, AmfFormat_R32G32_FLOAT, mesh.vtBuffers[0]);
	
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, mesh.vtBuffers[0]);
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, mesh.vtBuffers[0]);
	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Color, AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, mesh.vtBuffers[0]);
}

void RBNXXXX_Link(ADF * base, RBSMesh &mesh, RBMMaterial *cMat)
{
	RBNXXXXConstants *atts = cMat->GetAttributes<RBNXXXXConstants>();
	mesh.descriptors.resize(5);

	int currentBufferOffset = 0;
	int currentDesc = 0;
	int currentStride = mesh.vtBuffersStrides[0];

	AmfStreamAttribute *descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Position, AmfFormat_R16G16B16_SNORM, mesh.vtBuffers[0]);
	*reinterpret_cast<float*>(descr->packingData) = atts->vertexScale;

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Unspecified, AmfFormat_R16_SINT, mesh.vtBuffers[0]);

	currentStride = mesh.vtBuffersStrides[1];
	currentBufferOffset = 0;

	descr = RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_TextureCoordinate, AmfFormat_R16G16_SNORM, mesh.vtBuffers[1]);
	*reinterpret_cast<Vector2*>(descr->packingData) = atts->UV1Scale;

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Normal, AmfFormat_R32_UNIT_VEC_AS_FLOAT, mesh.vtBuffers[1]);

	RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, AmfUsage_Tangent, AmfFormat_R32_UNIT_VEC_AS_FLOAT, mesh.vtBuffers[1]);
}

#define RBSLikerEval(x) {x::RBMHASH, x##_Link},

static const std::map<uint64, void (*)(ADF *, RBSMesh &, RBMMaterial *)> RBSLinkers =
{
	StaticFor(RBSLikerEval, RBNGeneral, RBNCharacter, RBNCarPaint, RBNWindow, RBNXXXX)
};

void RBMMeshHeader::ReplaceReferences(ADF *newMain)
{
	RBNModel *cModel = newMain->FindInstance<RBNModel>();

	if (!cModel)
	{
		printerror("[ADF ", << _T(__FUNCTION__) << _T("]: Cannot find RBNModel instance."));
		return;
	}

	int curMesh = 0;

	for (auto &m : meshes)
	{
		RBMMaterial *cMat = cModel->materials[curMesh++];
		RBSMesh *cMesh = static_cast<RBSMesh *>(m);
		RBSLinkers.at(static_cast<RBSMesh *>(m)->blockHash.data)(newMain, *cMesh, cMat);
		cMesh->meshName = cMat->name;
		cMesh->meshType = cMat->GetRenderBlockName();
	}
}