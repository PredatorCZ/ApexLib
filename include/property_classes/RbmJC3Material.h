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

struct RBMVegetationFoliage3Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMVegetationFoliage3Constants);

	float flt[11];
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	uint flags;
	AdfBBOX bbox;
	uint null;
};

struct RBMFoliageBark2Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMFoliageBark2Constants);

	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	float flt00;
	AdfBBOX bbox;
	float flt[39];
};

struct RBMGeneralSimpleConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMGeneralSimpleConstants);

	float flt[13];
	uint flags;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk[3];
};

struct RBMWaterHullConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMWaterHullConstants);

	float flt;
};

struct RBMSimpleGeometryConstants : RBMWaterHullConstants
{
	RBMREFLECTOR_FROM_PARENT(RBMWaterHullConstants);
	DEFINE_PROPERTY(RBMSimpleGeometryConstants);
};

struct RBMBavariumShiledConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMBavariumShiledConstants);

	float flt[4];
};

struct RBMWindow1Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMWindow1Constants);

	float flt[9];
	uint unk;
};

struct RBMLayeredConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMLayeredConstants);

	float flt[3];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
	float flt00[24];
};

struct RBMLandmarkConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMLandmarkConstants);

	float flt[13];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
};

struct RBMGeneralMK3Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMGeneralMK3Constants);

	float flt[9];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
	int flags; // 0x20 = skinned, 0x200 = usedecals, 0x8000 = singleskin
	AdfBBOX bbox;
	int unk02;
	float flt2[69];
	uint unk03;
};

struct RBMGeneral6Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMGeneral6Constants);

	float flt[2];
	uint unk;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
	AdfBBOX bbox;
};

struct RBMCarLightConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMCarLightConstants);

	float flt[15];
	int remapTable[256];
};

struct RBMCarPaint14Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMCarPaint14Constants);

	int flags; // 0x1000 = deformable, 0x2000 = skinned, 0x20 | 0x40 = uv3
	float flt[99];
	int remapTable[256];
};

struct RBMGeneral3Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMGeneral3Constants);

	float flt[64];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
};

struct RBMCharacter9Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMCharacter9Constants);

	int flags;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	float flt[21];
};

struct RBMCharacter6Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMCharacter6Constants);

	int flags; //0x2 = 2uv
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	float flt[8];
};

struct RBMRoadConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMRoadConstants);

	uint unk00[2];
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[2];
	int flags; //0x20 = skinned
	AdfBBOX bbox;
	float flt00;
	int unk02[2];
	float flt01;
	int unk03;
	float flt02[2];
	int unk04[4];
	float flt03[29];
	int unk05[7];
};

struct RBMGeneralSimple3Constants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMGeneralSimple3Constants);

	uint unk;
	float flt[25];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
	AdfBBOX bbox;
};

//VSH
struct RBMApex3MeshConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMApex3MeshConstants);

	float wireScale;
	Vector textureDensities;
};
