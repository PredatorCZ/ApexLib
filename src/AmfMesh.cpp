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

#include "AmfMesh.h"
#include "datas/binreader.hpp"
#include "ADF.h"
#include "datas/masterprinter.hpp"
#include "datas/esstring.h"

REFLECTOR_START_WNAMES(GeneralMeshConstants, pristineIndexCount, flags);
REFLECTOR_START_WNAMES(FoliageMeshConstants, boundingBoxDimensions.Min, boundingBoxDimensions.Max);
REFLECTOR_START_WNAMES(CarPaintMeshConstants, flags);

int AmfMeshHeader::Load(BinReader * rd, ADF *linker)
{
	rd->Read(Header);
	highLODPath = linker->FindStringHash(Header.HighLodPath);
	rd->Seek(Header.LodGroups.offset);
	lodGroups.resize(static_cast<size_t>(Header.LodGroups.count));

	for (auto &l : lodGroups)
		l.Load(rd, linker);

	return 0;
}

void AmfMeshHeader::Link(ADF * linker)
{
	for (auto &l : lodGroups)
		for (auto &m : l.meshes)
			m.Link(linker);
}

int AmfLodGroup::Load(BinReader * rd, ADF *linker)
{
	rd->Read(Header);
	rd->SavePos();
	rd->Seek(Header.Meshes.offset);
	meshes.resize(static_cast<size_t>(Header.Meshes.count));

	for (auto &l : meshes)
		l.Load(rd, linker);

	rd->RestorePos();

	return 0;
}

int AmfMesh::Load(BinReader * rd, ADF *linker)
{
	rd->Read(Header);
	meshType = linker->FindStringHash(Header.MeshTypeId);

	size_t savepos = rd->Tell();

	rd->Seek(Header.vertexBufferIndices.offset);
	rd->ReadContainer(vertexBufferIndices, static_cast<size_t>(Header.vertexBufferIndices.count));

	rd->Seek(Header.vertexStreamStrides.offset);
	rd->ReadContainer(vertexStreamStrides, static_cast<size_t>(Header.vertexStreamStrides.count));

	rd->Seek(Header.vertexStreamOffsets.offset);
	rd->ReadContainer(vertexStreamOffsets, static_cast<size_t>(Header.vertexStreamOffsets.count));

	rd->Seek(Header.boneIndexLookup.offset);
	rd->ReadContainer(boneIndexLookup, static_cast<size_t>(Header.boneIndexLookup.count));

	rd->Seek(Header.subMeshes.offset);
	subMeshes.resize(static_cast<size_t>(Header.subMeshes.count));

	for (auto &l : subMeshes)
		l.Load(rd, linker);

	rd->Seek(Header.streamAttributes.offset);
	streamAttributes.resize(static_cast<size_t>(Header.streamAttributes.count));

	for (auto &l : streamAttributes)
		l.Load(rd, linker);

	rd->Seek(Header.meshProperties.offset);

	const ApexHash propsHash = static_cast<ApexHash>(Header.meshProperties.objectHash);
	meshProperties = AdfProperties::ConstructProperty(propsHash);

	if (meshProperties)
		meshProperties->Load(rd);
	else if (propsHash)
	{
		std::string *fName = linker->FindString(Header.MeshTypeId);
		printwarning("[ADF] Couldn't find AmfMesh property: ", << (fName ? fName->c_str() : 0) << '[' << std::hex << std::uppercase << propsHash << ']');
	}

	if (propsHash == CarPaintMeshConstants::HASH)
	{
		CarPaintMeshConstants &props = *static_cast<CarPaintMeshConstants*>(meshProperties->GetProperties());

		if (props.flags[CarPaintMeshConstantsFlags::deformable])
		{
			if (streamAttributes[1].Header.usage == AmfUsage_Unspecified && streamAttributes[1].Header.format == AmfFormat_R32_UNIT_VEC_AS_FLOAT)
				streamAttributes[1].Header.usage = AmfUsage_DeformNormal_c;
			if (streamAttributes[2].Header.usage == AmfUsage_Unspecified && streamAttributes[2].Header.format == AmfFormat_R16G16B16A16_SINT)
			{
				streamAttributes[2].Header.usage = AmfUsage_DeformPoints_c;
				streamAttributes[2].Header.format = AmfFormat_R16G16B16A16_SNORM;
				streamAttributes[2].AssignEvaluator(AmfFormat_R16G16B16A16_SNORM);
			}
		}
	}

	rd->Seek(savepos);
	return 0;
}

void AmfMesh::Link(ADF * linker)
{
	AmfMeshBuffers *buff = static_cast<IADF*>(linker)->FindInstance<AmfMeshBuffers>();

	if (!buff)
		buff = static_cast<IADF *>(linker)->FindInstance<AmfMeshBuffers_TheHunter>();

	bool linkError = false;

	if (buff)
	{
		for (auto &l : streamAttributes)
		{
			const int bufferIndex = vertexBufferIndices[l.Header.streamIndex];

			if (bufferIndex < static_cast<int>(buff->vertexBuffers.size()))
				l.buffer = buff->vertexBuffers[bufferIndex]->buffer + vertexStreamOffsets[l.Header.streamIndex] + l.Header.streamOffset;
			else if (!linkError)
				linkError = true;		
		}

		for (auto &l : subMeshes)
		{
			if (Header.indexBufferIndex < buff->indexBuffers.size())
				l.buffer = buff->indexBuffers[Header.indexBufferIndex]->buffer + Header.indexBufferOffset + l.Header.indexStreamOffset;
			else if (!linkError)
				linkError = true;
		}

		if (linkError)
			printerror("[ADF] Buffer links for \"", << esString(subMeshes[0].meshName->string) << _T(" \" are missing."))
	}
	else
	{
		printerror("[ADF] Could't find buffer instance.")
	}
	properlyLinked = !linkError;
}

AmfMesh::~AmfMesh()
{
	if (meshProperties)
		delete meshProperties;
}

int AmfMeshBuffers::Load(BinReader * rd, ADF *linker)
{
	rd->Read(Header);
	size_t savepos = rd->Tell();

	rd->Seek(Header.indexBuffers.offset);
	indexBuffers.resize(static_cast<size_t>(Header.indexBuffers.count));

	for (auto &l : indexBuffers)
	{
		AmfBuffer *nBuf = new AmfBuffer;
		nBuf->Load(rd);
		l = nBuf;
	}

	rd->Seek(Header.vertexBuffers.offset);
	vertexBuffers.resize(static_cast<size_t>(Header.vertexBuffers.count));

	for (auto &l : vertexBuffers)
	{
		AmfBuffer *nBuf = new AmfBuffer;
		nBuf->Load(rd);
		l = nBuf;
	}

	rd->Seek(savepos);

	return 0;
}

void AmfMeshBuffers::Merge(ADFInstance * externalInstance)
{
	AmfMeshBuffers *externalInstanceCasted = static_cast<AmfMeshBuffers*>(externalInstance);
	indexBuffers.insert(indexBuffers.end(), externalInstanceCasted->indexBuffers.begin(), externalInstanceCasted->indexBuffers.end());
	vertexBuffers.insert(vertexBuffers.end(), externalInstanceCasted->vertexBuffers.begin(), externalInstanceCasted->vertexBuffers.end());
}

AmfMeshBuffers::~AmfMeshBuffers()
{
	for (auto &l : indexBuffers)
		delete l;
	for (auto &l : vertexBuffers)
		delete l;
}

int AmfBuffer::Load(BinReader * rd)
{
	rd->Read(Header);
	size_t savepos = rd->Tell();

	rd->Seek(Header.info.offset);
	buffer = static_cast<char*>(malloc(static_cast<size_t>(Header.info.count)));
	rd->ReadBuffer(buffer, static_cast<size_t>(Header.info.count));

	rd->Seek(savepos);

	return 0;
}

AmfBuffer::~AmfBuffer()
{
	if (buffer)
		free(buffer);
}

int AmfSubMesh::Load(BinReader * rd, ADF * linker)
{
	rd->Read(Header);
	meshName = linker->FindStringHash(Header.subMeshID);
	return 0;
}

int AmfStreamAttribute::Load(BinReader * rd, ADF * linker)
{
	rd->Read(Header);
	AssignEvaluator();
	return 0;
}
