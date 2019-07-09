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
struct AmfMeshBuffers_V1;
struct AmfMeshBuffers_V2;
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
	mutable AmfMeshBuffers_V1 *buffers;
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

class AmfMeshBuffers_V1_wrap : public ADFInstance
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
};

class AmfMeshBuffers_TheHunter_wrap : public AmfMeshBuffers_V1_wrap
{
public:
	static const ApexHash HASH = 0xe6834477;

	AmfMeshBuffers_TheHunter_wrap(void *_data, ADF *_main) : AmfMeshBuffers_V1_wrap(_data, _main) {}
};

class AmfMeshBuffers_V2_wrap : public ADFInstance
{
	AmfMeshBuffers_V2 *data;

	void Fixup(char *masterBuffer);
	const char *RequestsFile() const { return nullptr; }
public:
	static const ApexHash HASH = 0xE1C0800;

	AmfMeshBuffers_V2_wrap(void *_data, ADF *_main);
	ES_FORCEINLINE AmfMeshBuffers_V2 *Data() { return data; }

	ApexHash GetSuperClass() const { return -1; }
};
