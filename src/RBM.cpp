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

static const char *IDS[] = { "RBMDL", "RBSDL", "RBNDL" };

#define RBSENDHASH 0x456bcdef

int LoadRBSDL(ADF *master, BinReader *rd)
{
	RBMHeader hdr;
	rd->Read(hdr);

	const uint numBlocks = hdr.numblocks;
	const size_t fileSize = rd->GetSize() - rd->Tell();
	RBSMeshHeader *meshHeader = master->AddUniqueInstance<RBSMeshHeader>();

	meshHeader->data.voidBuffer = malloc(fileSize);
	char *curBuffer = meshHeader->data.masterBuffer;

	for (uint b = 0; b < numBlocks; b++)
	{
		int numVBuffers;
		RBSMesh *nMesh = new RBSMesh();

		rd->Read(nMesh->blockHash.innerData.hash);
		rd->Read(nMesh->blockHash.innerData.version);
		rd->Read(numVBuffers);
		meshHeader->meshes.push_back(nMesh);

		for (int b = 0; b < numVBuffers; b++)
		{
			rd->Read(nMesh->vtBuffersStrides[b]);
			rd->Read(nMesh->numVertices);
			ApplyPadding(curBuffer);
			nMesh->vtBuffers[b] = curBuffer;
			const int vtBufSize = nMesh->vtBuffersStrides[b] * nMesh->numVertices;
			rd->ReadBuffer(curBuffer, vtBufSize);	
			curBuffer += vtBufSize;
		}

		rd->Read(numVBuffers);
		rd->Read(nMesh->numIndices);
		ApplyPadding(curBuffer);
		nMesh->indexBuffer = reinterpret_cast<ushort *>(curBuffer);
		rd->ReadBuffer(curBuffer, nMesh->numIndices * 2);
		curBuffer += nMesh->numIndices * 2;

		ApexHash endHash;
		rd->Read(endHash);

		if (endHash != RBSENDHASH)
		{
			printerror("[RBS] Unexpected end of block: 0x", << std::hex << nMesh->blockHash.innerData.hash << 
				std::dec << " version: " << nMesh->blockHash.innerData.version << " at: " << rd->Tell(false) - 4);
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
	const size_t fileSize = rd->GetSize() - rd->Tell();
	RBMMeshHeader *meshHeader = master->AddUniqueInstance<RBMMeshHeader>();
	RBMModel *cModel = master->AddUniqueInstance<RBMModel>();

	cModel->data.voidBuffer = malloc(fileSize);
	char *curBuffer = cModel->data.masterBuffer;	

	for (uint b = 0; b < numBlocks; b++)
	{
		RBMHash hash = {};
		rd->Read(hash.innerData.hash);
		rd->Read(hash.innerData.version);

		RBMMaterial *cMat = RBMMaterial::ConstructClass(hash.data);
		RBMMesh *cMesh = RBMMesh::ConstructClass(hash.data);

		if (cMat && cMesh)
		{
			cModel->materials.push_back(cMat);
			meshHeader->meshes.push_back(cMesh);
			cMat->materialType = hdr.versionminor < 14 ? MaterialType_Traditional : MaterialType_PBR;

			const int attributtesSize = cMat->GetPropertiesSize();
			const int numTextures = cMat->GetNumTexturesToRead();
			const int meshAttributtesSize = cMesh->GetPropertiesSize();

			cMat->properties.item.vPtr = curBuffer;
			rd->ReadBuffer(curBuffer, attributtesSize);
			curBuffer += attributtesSize;

			if (numTextures >= 0)
				cMat->ReadTextures(rd, curBuffer, numTextures);

			cMesh->properties.item.vPtr = curBuffer;
			rd->ReadBuffer(curBuffer, meshAttributtesSize);
			curBuffer += meshAttributtesSize;
			ApplyPadding(curBuffer);

			cMat->ReadRBM(rd, curBuffer, *cMesh);

			cMesh->meshType = cMat->GetRenderBlockName();

			std::string noName = std::to_string(b);
			cMat->name.string = "Object000";
			cMat->name.string.replace(9 - noName.size(), noName.size(), noName);
			cMat->name.Generate();
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

	const uint numBlocks = hdr.numblocks;
	const size_t fileSize = rd->GetSize() - rd->Tell();
	RBNModel *cModel = master->AddUniqueInstance<RBNModel>();

	cModel->data.voidBuffer = malloc(fileSize);
	char *curBuffer = cModel->data.masterBuffer;

	int textSize;
	rd->Read(textSize);
	rd->ReadBuffer(curBuffer, textSize);
	curBuffer += textSize;
	*curBuffer = 0;
	curBuffer++;
	ApplyPadding(curBuffer);

	for (uint b = 0; b < numBlocks; b++)
	{
		RBMHash hash = {};
		rd->Read(hash.innerData.hash);
		rd->Read(hash.innerData.version);

		RBMMaterial *cMat = RBMMaterial::ConstructClass(hash.data);

		if (cMat)
		{
			const int attributtesSize = cMat->GetPropertiesSize();

			cModel->materials.push_back(cMat);
			cMat->properties.item.vPtr = curBuffer;
			rd->ReadBuffer(curBuffer, attributtesSize);
			curBuffer += attributtesSize;
			
			cMat->ReadTextures(rd, curBuffer);
			rd->Read(textSize); //rbsHash
			rd->Read(textSize); //meshIndex

			std::string noName = std::to_string(b);
			cMat->name.string = "Object000";
			cMat->name.string.replace(9 - noName.size(), noName.size(), noName);
			cMat->name.Generate();
			cMat->materialType = MaterialType_PBR;
		}
		else
		{
			printerror("[RBN] Unhandled model hash: 0x", << std::hex << hash.innerData.hash << 
				std::dec << " or version: " << hash.innerData.version << " at: " << rd->Tell(false) - 4);
			return 1;
		}

		ApexHash endHash;
		rd->Read(endHash);

		if (endHash != RBNENDHASH)
		{
			printerror("[RBN] Unexpected end of block: 0x", << std::hex << hash.innerData.hash << 
				std::dec << " version: " << hash.innerData.version << " at: " << rd->Tell(false) - 4);
			return 2;
		}
	}

	return 0;
}

RBMMeshHeader::~RBMMeshHeader()
{
	for (auto &m : meshes)
		delete m;
}

RBSMeshHeader::~RBSMeshHeader()
{
	if (data.voidBuffer)
		free(data.voidBuffer);
}

RBMModel::~RBMModel()
{
	if (data.voidBuffer)
		free(data.voidBuffer);
	
	for (auto &m : materials)
		delete m;
}

RBMMaterial::~RBMMaterial()
{
	if(properties.item.vPtr)
		delete properties.item.cPtr;
}

RBMMesh::~RBMMesh()
{
	if(properties.item.vPtr)
		delete properties.item.cPtr;
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

void RBMMaterial::ReadTextures(BinReader *rd, char *&innerBuffer, uint numTextures)
{
	if (!numTextures)
		rd->Read(numTextures);

	for (uint t = 0; t < numTextures; t++)
	{
		int textSize;
		rd->Read(textSize);
		textures.push_back(innerBuffer);
		rd->ReadBuffer(innerBuffer, textSize);
		innerBuffer += textSize;
		*innerBuffer = 0;
		innerBuffer++;
	}
	
	ApplyPadding(innerBuffer);
}