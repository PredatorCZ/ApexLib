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

#pragma once
#include "AmfProperties.h"

struct AmfMeshHeader_V1;
struct AmfMeshHeader_V2;
struct AmfMeshBuffers_V1;
struct AmfMeshBuffers_V1_5;
struct AmfMeshBuffers_V2;
class AmfMeshBuffers;
class ADF;

class AmfVertexDescriptor_internal : public AmfVertexDescriptor
{
public:
	const char *buffer;
};

class AmfMeshHeader_V1_wrap : public AmfMeshHeader
{
	AmfMeshHeader_V1 *data;
	ADF *main;
	mutable AmfMeshBuffers *buffers;
public:
	static const ApexHash HASH = 0xEA60065D;

	AmfMeshHeader_V1_wrap(void *_data, ADF *_main);	
	int GetNumLODs() const;
	int GetLodIndex(int id) const;
	int GetNumLODMeshes(int LODIndex) const;
	AmfMesh::Ptr GetLODMesh(int LODIndex, int meshIndex) const;
	void Fixup(char *masterBuffer);
	const char *RequestsFile() const;
	void ReplaceReferences(ADF *newMain);
	ApexHash GetSuperClass() const { return  AmfMeshHeader::HASH; }
};

class AmfMeshHeader_V2_wrap : public AmfMeshHeader
{
	AmfMeshHeader_V2 *data;
	ADF *main;
	mutable AmfMeshBuffers_V2 *buffers[2];
public:
	static const ApexHash HASH = 0x7A2C9B73;

	AmfMeshHeader_V2_wrap(void *_data, ADF *_main);
	int GetNumLODs() const;
	int GetLodIndex(int id) const;
	int GetNumLODMeshes(int LODIndex) const;
	AmfMesh::Ptr GetLODMesh(int LODIndex, int meshIndex) const;
	void Fixup(char *masterBuffer);
	const char *RequestsFile() const;
	void ReplaceReferences(ADF *newMain);
	ApexHash GetSuperClass() const { return  AmfMeshHeader::HASH; }
};

class AmfMeshBuffers : public ADFInstance
{
public:
	static const ApexHash HASH = 0x67B3A453;
	virtual char *GetVertexBuffer(int id) const = 0;
	virtual char *GetIndexBuffer(int id) const = 0;
	virtual int GetNumIndexBuffers() const = 0;
	virtual int GetNumVertexBuffers() const = 0;
};

class AmfMeshBuffers_V1_wrap : public AmfMeshBuffers
{
	AmfMeshBuffers_V1 *data;

	void Fixup(char *masterBuffer);
	const char *RequestsFile() const { return nullptr; }
	void Merge(ADFInstance *externalInstance);
public:
	static const ApexHash HASH = 0x67B3A453;

	AmfMeshBuffers_V1_wrap(void *_data, ADF *_main);
	ES_FORCEINLINE AmfMeshBuffers_V1 *Data() { return data; }

	ApexHash GetSuperClass() const { return -1; }
	char *GetVertexBuffer(int id) const;
	char *GetIndexBuffer(int id) const;
	int GetNumIndexBuffers() const;
	int GetNumVertexBuffers() const;
};

class AmfMeshBuffers_V1_5_wrap : public AmfMeshBuffers
{
	AmfMeshBuffers_V1_5 *data;

	void Fixup(char *masterBuffer);
	const char *RequestsFile() const { return nullptr; }
public:
	static const ApexHash HASH = 0xe6834477;

	AmfMeshBuffers_V1_5_wrap(void *_data, ADF *_main);
	ES_FORCEINLINE AmfMeshBuffers_V1_5 *Data() { return data; }

	ApexHash GetSuperClass() const { return AmfMeshBuffers::HASH; }
	char *GetVertexBuffer(int id) const;
	char *GetIndexBuffer(int id) const;
	int GetNumIndexBuffers() const;
	int GetNumVertexBuffers() const;
};

class AmfMeshBuffers_V2_wrap : public ADFInstance
{
	AmfMeshBuffers_V2 *data01, *data02;

	void Fixup(char *masterBuffer);
	void Merge(ADFInstance *externalInstance);
	const char *RequestsFile() const { return nullptr; }
public:
	static const ApexHash HASH = 0xE1C0800;

	AmfMeshBuffers_V2_wrap(void *_data, ADF *_main);
	ES_FORCEINLINE AmfMeshBuffers_V2 *Data01() { return data01; }
	ES_FORCEINLINE AmfMeshBuffers_V2 *Data02() { return data02; }

	ApexHash GetSuperClass() const { return -1; }
};
