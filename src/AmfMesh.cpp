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

#include "ADF.h"
#include "AmfMesh_V2.h"
#include "datas/binreader.hpp"
#include "datas/masterprinter.hpp"
#include "datas/esstring.h"

REFLECTOR_START_WNAMES(GeneralMeshConstants, pristineIndexCount, flags);
REFLECTOR_START_WNAMES(FoliageMeshConstants, boundingBoxDimensions.Min, boundingBoxDimensions.Max);
REFLECTOR_START_WNAMES(CarPaintMeshConstants, flags);

class AmfMesh_V1_wrap : public AmfMesh
{
	AmfMesh_V1 *data;
	AmfMeshBuffers_V1 *buffers;
	char *indexBuffer;
	ADF *main;

public:
	AmfMesh_V1_wrap(AmfMesh_V1 *imesh, ADF *base, AmfMeshBuffers_V1 *_buffers)
	: data(imesh), main(base), buffers(_buffers)
	{
		if (buffers)
			indexBuffer = buffers->indexBuffers[data->indexBufferIndex].buffer.items.cPtr +
				data->indexBufferOffset;
	}

	int GetNumSubMeshes() const { return data->subMeshes.count; }
	int GetNumIndices() const { return data->indexCount; }
	int GetNumVertices() const { return data->vertexCount; }
	int GetNumIndices(int subMeshIndex) const { return data->subMeshes[subMeshIndex].indexCount; }
	ushort *GetIndicesBuffer(int subMeshIndex) const
	{ return reinterpret_cast<ushort *>(indexBuffer + data->subMeshes[subMeshIndex].indexStreamOffset); }

	DescriptorCollection GetDescriptors() const
	{
		DescriptorCollection ncollection;

		for (auto &a : data->streamAttributes)
		{
			AmfVertexDescriptor *newDescRaw = AmfVertexDescriptor::Create(a.format);
			AmfVertexDescriptor_internal *newDesc = static_cast<AmfVertexDescriptor_internal *>(newDescRaw);

			if (!newDesc)
				continue;

			*newDescRaw = a;

			newDesc->buffer = buffers->vertexBuffers[data->vertexBufferIndices[a.streamIndex]].buffer.items.cPtr +
				data->vertexStreamOffsets[a.streamIndex] + a.streamOffset;

			ncollection.push_back(DescriptorCollection::value_type(newDesc));
		}

		return ncollection;
	}

	const char *GetMeshType() const { return main->FindString(data->MeshTypeId)->c_str(); }
	const char *GetSubMeshName(int id) const { return main->FindString(data->subMeshes[id].subMeshID)->c_str(); }
	ApexHash GetSubMeshNameHash(int id) const { return data->subMeshes[id].subMeshID; }
	const void *GetRemaps() const { return data->boneIndexLookup.items.vPtr; }
	int GetNumRemaps() const { return data->boneIndexLookup.count; }
	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_SHORT; }
	int GetRemap(int id) const { return data->boneIndexLookup[id]; }

	bool IsValid() const
	{
		if (!buffers || data->indexBufferIndex >= buffers->indexBuffers.count)
			return false;

		for (auto &a : data->streamAttributes)
			if (data->vertexBufferIndices[a.streamIndex] >= buffers->vertexBuffers.count)
				return false;

		return true;
	}
};

AmfMeshHeader_V1_wrap::AmfMeshHeader_V1_wrap(void *_data, ADF *_main)
: data(static_cast<AmfMeshHeader_V1*>(_data)), main(_main) {}

int AmfMeshHeader_V1_wrap::GetNumLODs() const { return data->lodGroups.count; }
int AmfMeshHeader_V1_wrap::GetLodIndex(int id) const { return data->lodGroups.items[id].index; }
int AmfMeshHeader_V1_wrap::GetNumLODMeshes(int LODIndex) const { return data->lodGroups.items[LODIndex].meshes.count; }
AmfMesh::Ptr AmfMeshHeader_V1_wrap::GetLODMesh(int LODIndex, int meshIndex) const
{
	if (!buffers)
	{
		AmfMeshBuffers_V1_wrap *bufWrap = main->FindInstance<AmfMeshBuffers_V1_wrap>();

		if (bufWrap)
			buffers = bufWrap->Data();
	}

	return AmfMesh::Ptr(new AmfMesh_V1_wrap(&data->lodGroups.items[LODIndex].meshes.items[meshIndex], main, buffers)); 
}

void AmfMeshHeader_V1_wrap::Fixup(char *masterBuffer) { data->Fixup(masterBuffer); }
const char *AmfMeshHeader_V1_wrap::RequestsFile() const { return main->FindString(data->highLod)->c_str(); }

AmfMeshBuffers_V1_wrap::AmfMeshBuffers_V1_wrap(void *_data, ADF *_main): data(static_cast<AmfMeshBuffers_V1*>(_data)) {}
void AmfMeshBuffers_V1_wrap::Fixup(char *masterBuffer) { data->Fixup(masterBuffer); }

void AmfMeshBuffers_V1_wrap::Merge(ADFInstance *externalInstance)
{
	AmfMeshBuffers_V1_wrap *inst = static_cast<AmfMeshBuffers_V1_wrap *>(externalInstance);
	AmfMeshBuffers_V1 *thisData = Data();

	thisData->indexBuffers.Merge(inst->Data()->indexBuffers);
	thisData->vertexBuffers.Merge(inst->Data()->vertexBuffers);
}

AmfMeshBuffers_V2_wrap::AmfMeshBuffers_V2_wrap(void *_data, ADF *_main): data(static_cast<AmfMeshBuffers_V2*>(_data)) {}
void AmfMeshBuffers_V2_wrap::Fixup(char *masterBuffer) { data->Fixup(masterBuffer); }

void AmfMeshHeader_V1_wrap::ReplaceReferences(ADF *newMain)
{
	main = newMain;
}