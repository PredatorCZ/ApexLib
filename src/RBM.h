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
#include <map>
#include "datas/reflector.hpp"
#include "datas/vectors.hpp"
#include "ApexApi.h"
#include "AdfBaseObject.h"
#include "lookup3.h"
#include "AmfMesh.h"

union RBMHash
{
	uint64 data;
	struct
	{
		uint hash;
		uchar version;
		uchar shaderType;
	}innerData;
};

struct RBMBBOX
{
	Vector max,
		min;
};

struct RBMHeader
{
	uint versionmajor;
	uint versionminor;
	uint revision;
	RBMBBOX bbox;
	uint numblocks;
};

struct RBNHeader
{
	uint versionmajor;
	uint versionminor;
	uint revision;
	uint numblocks;
	uint rbshash;
};

struct RBMRemapHeader
{
	int numTables,
		numFaces,
		null,
		numRemaps;
};

class RBMMesh : public AmfMesh
{
public:
	int numVertices,
		numIndices;
	ushort *indexBuffer;
	DescriptorCollection descriptors;
	StringHash meshName;
	AdfDeferred properties;
	const char *meshType;

	RBMMesh() : numVertices(0), numIndices(0), indexBuffer(nullptr), meshType(nullptr) {}

	int GetNumSubMeshes() const { return 1; }
	int GetNumIndices(int) const { return numIndices; }
	int GetNumIndices() const { return numIndices; }
	int GetNumVertices() const { return numVertices; }
	ushort *GetIndicesBuffer(int) const { return indexBuffer; }
	DescriptorCollection GetDescriptors() const 
	{
		DescriptorCollection nCol;

		for (auto &d : descriptors)
			nCol.push_back(DescriptorCollection::value_type(d.get(), DescriptorCollection::value_type::deleter_type(false)));

		return nCol;	
	}
	const char *GetMeshType() const { return meshType; }
	const char *GetSubMeshName(int) const { return meshName.string.c_str(); }
	ApexHash GetSubMeshNameHash(int) const { return meshName.hash; }
	bool IsValid() const { return true; }
	int GetNumRemaps() const { return 0; }

	virtual int GetPropertiesSize() const = 0;

	static RBMMesh *ConstructClass(uint64 classHash);
};

class RBSMesh : public RBMMesh
{
public:
	char *vtBuffers[3];
	int vtBuffersStrides[3];
	RBMHash blockHash;
	std::vector<uchar> boneIndexLookup;

	RBSMesh() : vtBuffers(), vtBuffersStrides() {}

	const char *GetMeshType() const { return meshType; }
	int GetNumRemaps() const { return static_cast<int>(boneIndexLookup.size()); }
	int GetRemap(int id) const { return boneIndexLookup[id]; }
	const void *GetRemaps() const { return boneIndexLookup.data(); }
	int GetPropertiesSize() const { return 0; };

	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_CHAR; }
};

class RBMMeshHeader : public AmfMeshHeader
{
public:
	std::vector<RBMMesh *> meshes;

	void Fixup(char *) {}
	const char *RequestsFile() const { return nullptr; }
	ApexHash GetSuperClass() const { return AmfMeshHeader::HASH; }

	int GetNumLODs() const { return 1; }
	int GetLodIndex(int id) const { return 0; }
	int GetNumLODMeshes(int LODIndex) const { return static_cast<int>(meshes.size()); }
	AmfMesh::Ptr GetLODMesh(int LODIndex, int meshIndex) const 
	{ return AmfMesh::Ptr(meshes[meshIndex], AmfMesh::Ptr::deleter_type(false)); }

	void ReplaceReferences(ADF *newMain);

	~RBMMeshHeader();
};

class RBSMeshHeader : public RBMMeshHeader
{
public:
	union
	{
		char *masterBuffer;
		void *voidBuffer;
	}data;

	~RBSMeshHeader();
};

class RBMMaterial : public AmfMaterial
{
public:

	std::vector<const char *> textures;
	AmfMaterialType materialType;
	StringHash name;
	AdfDeferred properties;
	ApexHash renderBlockHash;

	AmfMaterialType GetMaterialType() const { return materialType; }
	AmfMaterialType &MaterialType() { return materialType; }
	const char *GetName() const { return name.string.c_str(); }
	ApexHash GetNameHash() const { return name.hash; }
	ApexHash GetRenderBlockNameHash() const { return renderBlockHash; }
	ReflectorPtr GetReflectedAttributes() const { return ReflectorPtr(properties.GetReflected()); }
	ApexHash GetAttributesHash() const { return properties.objectHash; }
	void *GetRawAttributes() const { return properties.item.vPtr; }
	int GetNumTextures() const { return static_cast<int>(textures.size()); }
	const char *GetTexture(int id) const { return textures[id]; }
	void ReadTextures(BinReader *rd, char *&innerBuffer, uint numTextures = 0);

	virtual int GetPropertiesSize() const = 0;
	virtual int GetNumTexturesToRead() const { return 0; }
	virtual void ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh) = 0;

	static RBMMaterial *ConstructClass(uint64 classHash);
	RBMMaterial();
};

class RBMModel : public AmfModel
{
public:
	union
	{
		char *masterBuffer;
		void *voidBuffer;
	}data;

	std::vector<RBMMaterial *> materials;

	int GetNumMaterials() const { return static_cast<int>(materials.size()); }
	AmfMaterial::Ptr GetMaterial(int id) const { return AmfMaterial::Ptr(materials[id], AmfMaterial::Ptr::deleter_type(false)); }

	void Fixup(char *) {}
	const char *RequestsFile() const { return nullptr; }
	ApexHash GetSuperClass() const { return AmfModel::HASH; }
	~RBMModel();
};

class RBNModel : public RBMModel
{
	const char *RequestsFile() const { return data.masterBuffer; }
};

ES_INLINE AmfVertexDescriptor *RBMNewDescriptor(RBMMesh &mesh, int &currentDesc, int &currentBufferOffset, int bufferStride, AmfUsage usage, AmfFormat format, const char *buffer)
{
	mesh.descriptors[currentDesc] = AmfVertexDescriptor::Ptr(AmfVertexDescriptor::Create(format));
	AmfVertexDescriptor_internal *descr = static_cast<AmfVertexDescriptor_internal *>(mesh.descriptors[currentDesc++].get());
	descr->usage = usage;
	descr->format = format;
	descr->streamOffset = currentBufferOffset;
	descr->streamStride = bufferStride;
	descr->buffer = buffer + currentBufferOffset;
	currentBufferOffset += AmfFormatStrides[format];
	return descr;
}

#define RBM_NEW_DESCRIPTOR(_usage, _format) AmfVertexDescriptor &descr = *RBMNewDescriptor(mesh, currentDesc, currentBufferOffset, currentStride, _usage, _format, vtBuffer);

ES_INLINE void ApplyPadding(char *&buffer, int alignment = 8)
{
	const size_t iterPos = reinterpret_cast<esIntPtr>(buffer);
	const size_t result = iterPos & (alignment - 1);

	if (!result)
		return;

	buffer += alignment - result;
}