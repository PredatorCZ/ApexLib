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
#include <vector>
#include <memory>
#include "AmfEnums.h"
#include "datas/deleter_hybrid.hpp"

#define REGISTER_ADF_INSTANCE(classname) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1);

class BinReader;
class ADF;

typedef unsigned int ApexHash;
typedef std::unique_ptr<Reflector> ReflectorPtr;

struct ADFInstance
{
	virtual void Fixup(char *) = 0;
	virtual const char *RequestsFile() const = 0;
	virtual void Merge(ADFInstance *externalInstance) {}
	virtual void ReplaceReferences(ADF *newMain) {}
	virtual ApexHash GetSuperClass() const = 0;
	virtual ~ADFInstance() {}
};

struct AmfStreamAttribute
{
	AmfUsage usage;
	AmfFormat format;
	unsigned char streamIndex,
		streamOffset,
		streamStride;
	char packingData[8];
};

class AmfVertexDescriptor : public AmfStreamAttribute
{
public:
	typedef std::unique_ptr<AmfVertexDescriptor, std::deleter_hybrid> Ptr;

	virtual void Evaluate(int at, void *data) const = 0;
	virtual ~AmfVertexDescriptor() {}
	static AmfVertexDescriptor *Create(AmfFormat format);
	void operator =(AmfStreamAttribute &input) { static_cast<AmfStreamAttribute &>(*this) = input; }
};

enum AmfMeshRemapType
{
	REMAP_TYPE_CHAR,
	REMAP_TYPE_SHORT,
	REMAP_TYPE_INT,
	REMAP_TYPE_SPRITE
};

class AmfMesh
{
public:
	typedef std::unique_ptr<AmfMesh, std::deleter_hybrid> Ptr;
	typedef std::vector<AmfVertexDescriptor::Ptr> DescriptorCollection;

	virtual int GetNumSubMeshes() const = 0;
	virtual int GetNumIndices(int subMeshIndex) const = 0;
	virtual int GetNumIndices() const = 0;
	virtual int GetNumVertices() const = 0;
	virtual ushort *GetIndicesBuffer(int subMeshIndex) const = 0;
	virtual DescriptorCollection GetDescriptors() const = 0;
	virtual const char *GetMeshType() const = 0;
	virtual const char *GetSubMeshName(int id) const = 0;
	virtual ApexHash GetSubMeshNameHash(int id) const = 0;
	virtual bool IsValid() const = 0;
	virtual AmfMeshRemapType GetRemapType() const = 0;
	virtual int GetNumRemaps() const = 0;
	virtual int GetRemap(int id) const = 0;
	virtual const void *GetRemaps() const = 0;

	template<class C> ES_FORCEINLINE C *GetRemapsAs() const { return reinterpret_cast<C *>(GetRemaps()); }

	virtual ~AmfMesh() {}
};

class AmfMeshHeader : public ADFInstance
{
public:
	REGISTER_ADF_INSTANCE(AmfMeshHeader)

	typedef std::unique_ptr<AmfMeshHeader> Ptr;

	virtual int GetNumLODs() const = 0;
	virtual int GetLodIndex(int id) const = 0;
	virtual int GetNumLODMeshes(int LODIndex) const = 0;
	virtual AmfMesh::Ptr GetLODMesh(int LODIndex, int meshIndex) const = 0;
};

enum AmfMaterialType
{
	MaterialType_Traditional,
	MaterialType_PBR
};

class AmfMaterial
{
public:
	typedef std::unique_ptr<AmfMaterial, std::deleter_hybrid> Ptr;

	virtual AmfMaterialType GetMaterialType() const = 0;
	virtual AmfMaterialType &MaterialType() = 0;
	virtual const char *GetName() const = 0;
	virtual const char *GetRenderBlockName() const = 0;
	virtual ApexHash GetNameHash() const = 0;
	virtual ApexHash GetRenderBlockNameHash() const = 0;
	virtual ReflectorPtr GetReflectedAttributes() const = 0;
	virtual void *GetRawAttributes() const = 0;
	virtual ApexHash GetAttributesHash() const = 0;
	virtual int GetNumTextures() const = 0;
	virtual const char *GetTexture(int id) const = 0;

	template<class C> ES_FORCEINLINE C *GetAttributes() const { return static_cast<C *>(GetRawAttributes()); }

	virtual ~AmfMaterial() {}
};

class AmfModel : public ADFInstance
{
public:
	REGISTER_ADF_INSTANCE(AmfModel)
	typedef std::unique_ptr<AmfModel> Ptr;

	virtual int GetNumMaterials() const = 0;
	virtual AmfMaterial::Ptr GetMaterial(int id) const = 0;
};

class IADF
{
public:
	virtual int Load(BinReader *rd, bool supressErrors = false) = 0;
	virtual int LoadAsRenderBlockModel(BinReader *rd, bool supressErrors = false) = 0;
	virtual int DumpDefinitions(const char *fileName) const = 0;
	virtual int DumpDefinitions(const wchar_t *fileName) const = 0;
	virtual int ExportDefinitionsToCPP(const char *fileName) const = 0;
	virtual int ExportDefinitionsToCPP(const wchar_t *fileName) const = 0;
	virtual ADFInstance *FindInstance(ApexHash hash, int numSkips = 0) = 0;
	virtual ~IADF() {};
	template<class C> ES_FORCEINLINE C *FindInstance(int numSkips = 0) { return static_cast<C*>(FindInstance(C::HASH, numSkips)); }
	template<class C> ES_FORCEINLINE C *AddUniqueInstance();
	virtual void AddInstance(ADFInstance *instance, ApexHash hash) = 0;
	static IADF *Create(const char *fileName);
	static IADF *Create(const wchar_t *fileName);
};

template<class C>
ES_INLINE C *IADF::AddUniqueInstance()
{
	C *foundInstance = FindInstance<C>();

	if (!foundInstance)
	{
		foundInstance = new C();
		AddInstance(foundInstance, C::HASH);
	}

	return foundInstance;
}


