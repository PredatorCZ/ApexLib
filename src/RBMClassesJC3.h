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

#define RBMCONSTRUCTOR2(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = classname##Constants::HASH; renderBlockHash = JenkinsLookup3(#classname); }\
int GetPropertiesSize() const { return sizeof(classname##Constants); }\
void ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh);\
int GetNumTexturesToRead() const { return 0; }

#define RBMCONSTRUCTOR2_WPARENT(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = classname##Constants::HASH; renderBlockHash = JenkinsLookup3(#classname); }\
int GetPropertiesSize() const { return sizeof(classname##Constants); }\

struct RBMVegetationFoliage3 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMVegetationFoliage3, 0x3d79884c6);
};

struct RBMFoliageBark2 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMFoliageBark2, 0x2b1f9133d);
};

struct RBMGeneralSimple : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMGeneralSimple, 0x62ee0f4a9);
};

struct RBMWaterHull : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMWaterHull, 0x1f99c72a1);
};

struct RBMSimpleGeometry : RBMWaterHull
{
	RBMCONSTRUCTOR2_WPARENT(RBMSimpleGeometry, 0x190fe086c);
};

struct RBMBavariumShiled : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMBavariumShiled, 0x1a5d24ccd);
};

struct RBMWindow1 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMWindow1, 0x15b2003f6);
};

struct RBMLayered: RBMMaterial
{
	RBMCONSTRUCTOR2(RBMLayered, 0x1c7021ee3);
};

struct RBMLandmark : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMLandmark, 0x73b630e6d);
};

struct RBMGeneralMK3 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMGeneralMK3, 0x52cec5ad5);
};

struct RBMGeneral6 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMGeneral6, 0x6a7583b2b);
};

struct RBMCarLight : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMCarLight, 0x1db948bf1);
};

struct RBMCarPaint14 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMCarPaint14, 0xE483304d6);
};

struct RBMGeneral3 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMGeneral3, 0x304894ecd);
};

struct RBMCharacter9 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMCharacter9, 0x99d6e332a);
};

struct RBMCharacter6 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMCharacter6, 0x6626f5e3b);
};

struct RBMRoad : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMRoad, 0x1566dce92);
};

struct RBMGeneralSimple3 : RBMMaterial
{
	RBMCONSTRUCTOR2(RBMGeneralSimple3, 0x335bf53d5);
};

//VSH
#define RBMCONSTRUCTOR2_MESH2(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = RBMApex3MeshConstants::HASH; }\
int GetPropertiesSize() const { return sizeof(RBMApex3MeshConstants); }

#define RBMCONSTRUCTOR2_MESH3(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() : remapHdr() { properties.objectHash = RBMApex3MeshConstants::HASH; }\
int GetPropertiesSize() const { return sizeof(RBMApex3MeshConstants); }

struct RBMVegetationFoliage3Mesh : RBMMesh
{
	RBMCONSTRUCTOR2_MESH2(RBMVegetationFoliage3Mesh, 0x3d79884c6);

	int GetNumRemaps() const { return 0; }
	int GetRemap(int id) const { return 0; }
	const void *GetRemaps() const { return nullptr; }
	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_CHAR; }
};

struct RBMFoliageBark2Mesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMFoliageBark2Mesh, 0x2b1f9133d);
};

struct RBMGeneralSimpleMesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMGeneralSimpleMesh, 0x62ee0f4a9);
};

struct RBMWaterHullMesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMWaterHullMesh, 0x1f99c72a1);
};

struct RBMSimpleGeometryMesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMSimpleGeometryMesh, 0x190fe086c);
};

struct RBMBavariumShiledMesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMBavariumShiledMesh, 0x1a5d24ccd);
};

struct RBMWindow1Mesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMWindow1Mesh, 0x15b2003f6);
};

struct RBMLayeredMesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMLayeredMesh, 0x1c7021ee3);
};

struct RBMLandmarkMesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMLandmarkMesh, 0x73b630e6d);
};

struct RBMGeneralMK3Mesh : RBMMesh
{
	RBMCONSTRUCTOR2_MESH3(RBMGeneralMK3Mesh, 0x52cec5ad5);

	RBMRemapHeader remapHdr;
	const ushort *remaps;

	int GetNumRemaps() const { return remapHdr.numRemaps; }
	int GetRemap(int id) const { return remaps[id]; }
	const void *GetRemaps() const { return remaps; }
	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_SHORT; }
};

struct RBMGeneral6Mesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMGeneral6Mesh, 0x6a7583b2b);
};

struct RBMCarLightMesh : RBMMesh
{
	RBMCONSTRUCTOR2_MESH2(RBMCarLightMesh, 0x1db948bf1);
	
	const int *remaps;
	static const int numRemaps = 256;

	int GetNumRemaps() const { return numRemaps; }
	int GetRemap(int id) const { return remaps[id]; }
	const void *GetRemaps() const { return remaps; }
	AmfMeshRemapType GetRemapType() const { return REMAP_TYPE_INT; }
};

struct RBMCarPaint14Mesh : RBMMesh
{
	RBMCONSTRUCTOR2_MESH3(RBMCarPaint14Mesh, 0xE483304d6);

	const int *deformRemaps;
	static const int numRemaps = 256;
	RBMRemapHeader remapHdr;
	const ushort *remaps;

	int GetNumRemaps() const { return !remapHdr.numFaces ? numRemaps : remapHdr.numRemaps; }
	int GetRemap(int id) const { return !remapHdr.numFaces ? deformRemaps[id] : remaps[id]; }
	const void *GetRemaps() const 
	{ return !remapHdr.numFaces ? static_cast<const void*>(deformRemaps) : static_cast<const void*>(remaps); }
	AmfMeshRemapType GetRemapType() const { return !remapHdr.numFaces ? REMAP_TYPE_INT : REMAP_TYPE_SHORT; }

};

struct RBMGeneral3Mesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMGeneral3Mesh, 0x304894ecd);
};

struct RBMCharacter9Mesh : RBMGeneralMK3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMCharacter9Mesh, 0x99d6e332a);
};

struct RBMCharacter6Mesh : RBMGeneralMK3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMCharacter6Mesh, 0x6626f5e3b);
};

struct RBMRoadMesh : RBMGeneralMK3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMRoadMesh, 0x1566dce92);
};

struct RBMGeneralSimple3Mesh : RBMVegetationFoliage3Mesh
{
	RBMCONSTRUCTOR2_MESH2(RBMGeneralSimple3Mesh, 0x335bf53d5);
};
