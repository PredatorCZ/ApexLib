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

#include "RBM.h"
#include "ApexApi.h"
#include "ADF.h"
#include "datas/binreader.hpp"
#include "datas/masterprinter.hpp"
#include "AmfModel.h"
#include "AmfMesh.h"

static const char *IDS[] = { "RBMDL", "RBSDL", "RBNDL" };
#define RBSENDHASH 0x456bcdef

int LoadRBSDL(ADF *master, BinReader *rd)
{
	RBMHeader hdr;
	rd->Read(hdr);

	const uint numBlocks = hdr.numblocks;

	AmfMeshHeader *meshHeader = master->AddUniqueInstance<AmfMeshHeader>();
	meshHeader->lodGroups.resize(1);
	meshHeader->lodGroups[0].meshes.reserve(numBlocks);

	for (uint b = 0; b < numBlocks; b++)
	{
		RBMHash hash = {};
		rd->Read(hash.innerData.hash);
		rd->Read(hash.innerData.version);

		if (RBMClassStorage.count(hash.data))
		{
			RBMMasterBlock *block = RBMClassStorage[hash.data]();
			block->material = nullptr;
			block->master = master;
			block->Load(rd);
		}
		else
		{
			printerror("[RBS] Unhandled model hash: 0x", << std::hex << hash.innerData.hash << std::dec << " or version: " << hash.innerData.version << " at: " << rd->Tell(false) - 4);
			return 1;
		}

		ApexHash endHash;
		rd->Read(endHash);

		if (endHash != RBSENDHASH)
		{
			printerror("[RBS] Unexpected end of block: 0x", << std::hex << hash.innerData.hash << std::dec << " version: " << hash.innerData.version << " at: " << rd->Tell(false) - 4);
			return 2;
		}
	}

	return 0;
}

#define RBMENDHASH 0x89ABCDEF

int LoadRBMDL(ADF *master, BinReader *rd)
{
	RBMHeader hdr;
	rd->Read(hdr);

	if (hdr.versionminor > 13)
	{
		uint unk;
		rd->Read(unk);
	}

	const uint numBlocks = hdr.numblocks;

	AmfModel *cModel = master->AddUniqueInstance<AmfModel>();

	AmfMeshHeader *meshHeader = master->AddUniqueInstance<AmfMeshHeader>();
	meshHeader->lodGroups.resize(1);
	meshHeader->lodGroups[0].meshes.reserve(numBlocks);

	for (uint b = 0; b < numBlocks; b++)
	{
		RBMHash hash = {};
		rd->Read(hash.innerData.hash);
		rd->Read(hash.innerData.version);

		AmfMaterial *cMat = new AmfMaterial();
		cModel->materials.push_back(cMat);

		if (hdr.versionminor < 14)
			cMat->materialType = AmfMaterial::MaterialType_Traditional;

		if (RBMClassStorage.count(hash.data))
		{
			RBMMasterBlock *block = RBMClassStorage[hash.data]();
			block->material = cMat;
			block->master = master;
			block->Load(rd);
			cMat->attributes = block;
			cMat->renderBlockID = master->AddStringHash(block->GetClassname());

			std::string noName = std::to_string(b);
			std::string uniqueName = "Object000";
			uniqueName.replace(9 - noName.size(), noName.size(), noName);
			cMat->name = master->AddStringHash(uniqueName);

		}
		else
		{
			printerror("[RBM] Unhandled model hash: 0x", << std::hex << hash.innerData.hash << std::dec << " or version: " << hash.innerData.version << " at: " << rd->Tell(false) - 4);
			return 1;
		}

		ApexHash endHash;
		rd->Read(endHash);

		if (endHash != RBMENDHASH)
		{
			printerror("[RBM] Unexpected end of block: 0x", << std::hex << hash.innerData.hash << std::dec << " version: " << hash.innerData.version << " at: " << rd->Tell(false) - 4);
			return 2;
		}
	}
	return 0;
}

#define RBNENDHASH 0x123bcdef

int LoadRBNDL(ADF *master, BinReader *rd)
{
	RBNHeader hdr;
	rd->Read(hdr);

	StringHash *rbsPath = new StringHash();
	rbsPath->hash = hdr.rbshash;
	rd->ReadContainer(rbsPath->string);
	master->hashes.push_back(rbsPath);

	AmfModel *cModel = master->AddUniqueInstance<AmfModel>();
	cModel->meshPath = rbsPath;
	
	const uint numBlocks = hdr.numblocks;

	for (uint b = 0; b < numBlocks; b++)
	{
		RBMHash hash = {};
		rd->Read(hash.innerData.hash);
		rd->Read(hash.innerData.version);
		hash.innerData.shaderType = 1;

		AmfMaterial *cMat = new AmfMaterial();
		cModel->materials.push_back(cMat);

		if (RBMClassStorage.count(hash.data))
		{
			RBMMasterBlock *block = RBMClassStorage[hash.data]();
			block->material = cMat;
			block->master = master;
			block->Load(rd);
			cMat->attributes = block;
			cMat->renderBlockID = master->AddStringHash(block->GetClassname());
			
			std::string noName = std::to_string(b);
			std::string uniqueName = "Object000";
			uniqueName.replace(9 - noName.size(), noName.size(), noName);
			cMat->name = master->AddStringHash(uniqueName);
		}
		else
		{
			printerror("[RBN] Unhandled model hash: 0x", << std::hex << hash.innerData.hash << std::dec << " or version: " << hash.innerData.version << " at: " << rd->Tell(false) - 4);
			return 1;
		}

		ApexHash endHash;
		rd->Read(endHash);

		if (endHash != RBNENDHASH)
		{
			printerror("[RBN] Unexpected end of block: 0x", << std::hex << hash.innerData.hash << std::dec << " version: " << hash.innerData.version << " at: " << rd->Tell(false) - 4);
			return 2;
		}
	}

	return 0;
}

int ADF::LoadAsRenderBlockModel(BinReader *rd, bool supressErrors)
{
	int numChars;
	rd->Read(numChars);

	if (numChars != 5)
	{
		if (!supressErrors)
		{
			printerror("[RBM] Invalid file.");
		}

		return 1;
	}

	char ID[6];
	rd->ReadBuffer(ID, 5);
	ID[5] = 0;

	int type = -1;

	for (int t = 0; t < 3; t++)
		if (!strcmp(ID, IDS[t]))
		{
			type = t;
			break;
		}

	switch (type)
	{
	case 0:
		return LoadRBMDL(this, rd) << 8;
	case 1:
		return LoadRBSDL(this, rd) << 8;
	case 2:
		return LoadRBNDL(this, rd) << 8;
	default:
	{
		if (!supressErrors)
		{
			printerror("[RBM] Invalid signature: ", << ID);
		}

		return 2;
	}
		
	}

	return 0;
}

void RBMMasterBlock::ReadTextures(BinReader *rd, uint numTextures)
{
	if (!numTextures)
		rd->Read(numTextures);

	for (uint t = 0; t < numTextures; t++)
	{
		StringHash *tex = new StringHash();
		rd->ReadContainer(tex->string);
		tex->Generate();
		StringHash* fnd = master->FindStringHash(tex->hash);

		if (fnd)
		{
			delete tex;
			tex = fnd;
		}
		else
		{
			master->hashes.push_back(tex);
		}

		material->textures.push_back(tex);
	}
}

void RBMMasterBlock::Link(ADF *base)
{
	AmfMeshHeader *mHeader = base->FindInstance<AmfMeshHeader>();

	if (!mHeader || meshID < 0)
		return;

	AmfMesh &mesh = mHeader->lodGroups[0].meshes[meshID];

	mesh.subMeshes[0].meshName = material->name;
	mesh.meshType = material->renderBlockID;
}

AmfMesh &RBMMasterBlock::LoadDependencies(const uint bufferSize, const uint numVertices, const uint currentStride, AmfBuffer *&cBuffer, const uint currentStrideSecondary)
{
	AmfMeshBuffers *buffers = master->AddUniqueInstance<AmfMeshBuffers>();
	cBuffer = new AmfBuffer();
	cBuffer->buffer = static_cast<char*>(malloc(bufferSize));
	buffers->vertexBuffers.push_back(cBuffer);

	AmfMeshHeader *hdr = master->FindInstance<AmfMeshHeader>();
	hdr->lodGroups[0].meshes.resize(hdr->lodGroups[0].meshes.size() + 1);

	AmfMesh &mesh = hdr->lodGroups[0].meshes.back();
	meshID = static_cast<uint>(hdr->lodGroups[0].meshes.size() - 1);

	mesh.Header.vertexCount = numVertices;
	mesh.vertexStreamOffsets.push_back(0);
	mesh.vertexStreamStrides.push_back(currentStride);
	mesh.vertexBufferIndices.push_back(static_cast<uchar>(buffers->vertexBuffers.size() - 1));

	if (currentStrideSecondary)
	{
		mesh.vertexStreamOffsets.push_back((numVertices * currentStride) + 4);
		mesh.vertexStreamStrides.push_back(currentStrideSecondary);
		mesh.vertexBufferIndices.push_back(static_cast<uchar>(buffers->vertexBuffers.size() - 1));
	}
	
	return mesh;
}

struct _RemapHeader
{
	int numTables,
		numFaces,
		null;
};

void RBMMasterBlock::ReadRemaps(BinReader *rd, AmfMesh *mesh)
{
	_RemapHeader rhdr = {};
	rd->Read(rhdr);

	if (mesh)
		rd->ReadContainer(mesh->boneIndexLookup);	
	else
	{
		rd->Read(rhdr.null);
		rd->Skip(rhdr.null * 2);
	}
}

void RBMMasterBlock::LoadFaces(BinReader *rd, AmfMesh &mesh, uint vBufferSize, AmfBuffer *cBuffer)
{
	uint numFaces;
	mesh.subMeshes.resize(1);
	rd->Read(numFaces);
	mesh.subMeshes[0].Header.indexCount = numFaces;
	mesh.Header.indexCount = numFaces;
	numFaces *= 2;
	rd->ReadBuffer(cBuffer->buffer + vBufferSize, numFaces);
	mesh.subMeshes[0].buffer = cBuffer->buffer + vBufferSize;
}
