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
#include "datas/reflector.hpp"
#include "datas/vectors.hpp"
#include <map>
#include "AdfBaseObject.h"

struct AmfMesh;
struct AmfBuffer;

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

struct AmfMaterial;

struct RBMMasterBlock : AdfProperties, Reflector
{
	RBMHash hash;
	AmfMaterial *material;
	ADF *master;
	int meshID;
	void *GetProperties() { return this; };
	void ReadTextures(BinReader *rd	, uint numTextures = 0);
	virtual const char *GetClassname() = 0;
	void Link(ADF *base);
	AmfMesh &LoadDependencies(const uint bufferSize, const uint numVertices, const uint currentStride, AmfBuffer *&cBuffer, const uint currentStrideSecondary = 0);
	static void LoadFaces(BinReader *rd, AmfMesh &mesh, uint vBufferSize, AmfBuffer *cBuffer);
	static void ReadRemaps(BinReader *rd, AmfMesh *mesh = nullptr);
	static RBMMasterBlock *ConstructClass(uint64 classHash);
	RBMMasterBlock();
};

#define RBMCONSTRUCTOR(classname, shash) static const ApexHash ADFHASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 HASH = shash;\
classname(){typeHash = ADFHASH; hash.data = HASH; ConstructReflection();} const char *GetClassname() {return #classname;}

#define RBMCONSTRUCTOR_NOREFL(classname, shash) static const ApexHash ADFHASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 HASH = shash;\
classname(){typeHash = ADFHASH; hash.data = HASH;} const char *GetClassname() {return #classname;}

#define RBM_NEW_DESCRIPTOR(_usage, _format, _streamIndex) AmfStreamAttribute &descr = mesh.streamAttributes[currentDesc++];\
descr.Header.usage = _usage;\
descr.Header.format = _format;\
descr.AssignEvaluator();\
descr.Header.streamIndex = _streamIndex;\
descr.Header.streamOffset = currentBufferOffset;\
descr.Header.streamStride = currentStride;\
currentBufferOffset += AmfFormatStrides[_format];

#define RBMREFLECTOR_FROM_PARENT(parentClass) ES_INLINE void ConstructReflection() \
{\
	_nTypes = parentClass::nTypes;\
	_typeNames = parentClass::typeNames;\
	_types = parentClass::types;\
	thisAddr = reinterpret_cast<char*>(this);\
}
