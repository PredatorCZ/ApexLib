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
#include "RBM.h"
#include "AmfProperties.h"

#define RBMCONSTRUCTOR(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = classname##Constants::HASH; renderBlockHash = JenkinsLookup3(#classname); }\
int GetPropertiesSize() const { return sizeof(classname##Constants); }\
void ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh);\
int GetNumTexturesToRead() const { return 8; }

#define RBMCONSTRUCTOR_NO_PROPS(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = 0; renderBlockHash = JenkinsLookup3(#classname); }\
void ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh);\
int GetPropertiesSize() const { return 0; }\
int GetNumTexturesToRead() const { return 8; }

#define RBMCONSTRUCTOR_WPARENT(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = 0; renderBlockHash = JenkinsLookup3(#classname); }\
int GetPropertiesSize() const { return 0; }\
int GetNumTexturesToRead() const { return 8; }

#define RBMCONSTRUCTOR_NO_PROPS_WPARENT(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = 0; renderBlockHash = JenkinsLookup3(#classname); }\
int GetPropertiesSize() const { return 0; }\
int GetNumTexturesToRead() const { return 8; }

struct RBMCarPaintSimple : RBMMaterial
{
	RBMCONSTRUCTOR(RBMCarPaintSimple, 0x181938490);
};

struct RBMFoliageBark : RBMMaterial
{
	RBMCONSTRUCTOR(RBMFoliageBark, 0xb1f9133d);
};

struct RBMVegetationFoliage : RBMMaterial
{
	RBMCONSTRUCTOR(RBMVegetationFoliage, 0xd79884c6);
};

struct RBMBillboardFoliage : RBMMaterial
{
	RBMCONSTRUCTOR_NO_PROPS(RBMBillboardFoliage, 0xad529e70);
};

struct RBMHalo : RBMMaterial
{
	RBMCONSTRUCTOR_NO_PROPS(RBMHalo, 0x65d9b5b2);
};

struct RBMLambert : RBMMaterial
{
	RBMCONSTRUCTOR(RBMLambert, 0x4d5d78ae0);
};

struct RBMGeneral : RBMMaterial
{
	RBMCONSTRUCTOR(RBMGeneral, 0x3a7583b2b);
};

struct RBMFacade : RBMMaterial
{
	RBMCONSTRUCTOR(RBMFacade, 0x1ce39d7bf);
};

struct RBMWindow : RBMMaterial
{
	RBMCONSTRUCTOR(RBMWindow, 0x5b2003f6);
};

struct RBMCarPaint : RBMCarPaintSimple
{
	RBMCONSTRUCTOR(RBMCarPaint, 0x3CD931E75);
};

struct RBMDeformWindow : RBMMaterial
{
	RBMCONSTRUCTOR_NO_PROPS(RBMDeformWindow, 0x106B1F602);
};

struct RBMMerged : RBMMaterial
{
	RBMCONSTRUCTOR_NO_PROPS(RBMMerged, 0x9185A4C3);
};

struct RBMSkinnedGeneral : RBMMaterial
{
	RBMCONSTRUCTOR(RBMSkinnedGeneral, 0x35e657f20);
};

struct RBMSkinnedGeneral0 : RBMSkinnedGeneral
{
	RBMCONSTRUCTOR_WPARENT(RBMSkinnedGeneral0, 0x5e657f20);
};

struct RBMSkinnedGeneralDecal : RBMSkinnedGeneral
{
	RBMCONSTRUCTOR(RBMSkinnedGeneralDecal, 0x60ff47a7);
};

struct RBMGeneral0 : RBMGeneral
{
	RBMCONSTRUCTOR(RBMGeneral0, 0xa7583b2b);
};

struct RBMFacade0 : RBMFacade
{
	RBMCONSTRUCTOR(RBMFacade0, 0xce39d7bf);
};

struct RBMUIOverlay : RBMMaterial
{
	RBMCONSTRUCTOR_NO_PROPS(RBMUIOverlay, 0xd7af3bee);
};

struct RBMScope : RBMUIOverlay
{
	RBMCONSTRUCTOR_NO_PROPS_WPARENT(RBMScope, 0x7e407c92);
};

//VSH
#define RBMCONSTRUCTOR_MESH(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = RBMApex2MeshConstants::HASH; }\
int GetPropertiesSize() const { return sizeof(RBMApex2MeshConstants); }

#define RBMCONSTRUCTOR_MESH_UNIQUE(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = classname##Constants::HASH; }\
int GetPropertiesSize() const { return sizeof(classname##Constants); }

struct RBMCarPaintSimpleMesh : RBMMesh
{
	RBMCONSTRUCTOR_MESH(RBMCarPaintSimpleMesh, 0x181938490);

	int GetNumRemaps() const { return 0; }
	int GetRemap(int id) const { return 0; }
	const void *GetRemaps() const { return nullptr; }
	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_CHAR; }
};

struct RBMFoliageBarkMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMFoliageBarkMesh, 0xb1f9133d);
};

struct RBMVegetationFoliageMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMVegetationFoliageMesh, 0xd79884c6);
};

struct RBMBillboardFoliageMesh : RBMMesh
{
	RBMCONSTRUCTOR_MESH(RBMBillboardFoliageMesh, 0xad529e70);

	std::vector<Vector> spritePositions;

	int GetNumRemaps() const { return static_cast<int>(spritePositions.size()); }
	int GetRemap(int id) const { return 0; }
	const void *GetRemaps() const { return spritePositions.data(); }
	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_SPRITE; }
};

struct RBMHaloMesh : RBMBillboardFoliageMesh
{
	RBMCONSTRUCTOR_MESH(RBMHaloMesh, 0x65d9b5b2);
};

struct RBMLambertMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMLambertMesh, 0x4d5d78ae0);
};

struct RBMGeneralMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMGeneralMesh, 0x3a7583b2b);
};

struct RBMFacadeMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMFacadeMesh, 0x1ce39d7bf);
};

struct RBMWindowMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMWindowMesh, 0x5b2003f6);
};

struct RBMCarPaintMesh : RBMMesh
{
	RBMCONSTRUCTOR_MESH(RBMCarPaintMesh, 0x3CD931E75);

	const int *remaps;
	static const int numRemaps = 256;

	int GetNumRemaps() const { return numRemaps; }
	int GetRemap(int id) const { return remaps[id]; }
	const void *GetRemaps() const { return remaps; }
	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_INT; }
};

struct RBMDeformWindowMesh : RBMCarPaintMesh
{
	RBMCONSTRUCTOR_MESH(RBMDeformWindowMesh, 0x106B1F602);
};

struct RBMMergedMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH_UNIQUE(RBMMergedMesh, 0x9185A4C3);
};

struct RBMSkinnedGeneralMesh : RBMMesh
{
	RBMCONSTRUCTOR_MESH(RBMSkinnedGeneralMesh, 0x35e657f20);

	RBMRemapHeader remapHdr;
	const ushort *remaps;

	int GetNumRemaps() const { return remapHdr.numRemaps; }
	int GetRemap(int id) const { return remaps[id]; }
	const void *GetRemaps() const { return remaps; }
	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_SHORT; }
};

struct RBMSkinnedGeneral0Mesh : RBMSkinnedGeneralMesh
{
	RBMCONSTRUCTOR_MESH(RBMSkinnedGeneral0Mesh, 0x5e657f20);
};

struct RBMSkinnedGeneralDecalMesh : RBMSkinnedGeneralMesh
{
	RBMCONSTRUCTOR_MESH(RBMSkinnedGeneralDecalMesh, 0x60ff47a7);
};

struct RBMGeneral0Mesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMGeneral0Mesh, 0xa7583b2b);
};

struct RBMFacade0Mesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMFacade0Mesh, 0xce39d7bf);
};

struct RBMUIOverlayMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMUIOverlayMesh, 0xd7af3bee);
};

struct RBMScopeMesh : RBMCarPaintSimpleMesh
{
	RBMCONSTRUCTOR_MESH(RBMScopeMesh, 0x7e407c92);
};