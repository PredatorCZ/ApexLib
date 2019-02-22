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

struct RBMVegetationFoliage3 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMVegetationFoliage3, 0x3d79884c6);

	//PSH
	float flt[11];
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	uint flags;
	AdfBBOX bbox;
	uint null;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMFoliageBark2 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMFoliageBark2, 0x2b1f9133d);

	//PSH
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	float flt00;
	AdfBBOX bbox;
	float flt[38];
	float endflt;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMGeneralSimple : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMGeneralSimple, 0x62ee0f4a9);

	//PSH
	float flt[13];
	uint flags;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk[2];
	int unkend;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMWaterHull : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMWaterHull, 0x1f99c72a1);

	//PSH
	float flt;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMSimpleGeometry : RBMWaterHull
{
	RBMCONSTRUCTOR(RBMSimpleGeometry, 0x190fe086c);
};

struct RBMBavariumShiled : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMBavariumShiled, 0x1a5d24ccd);

	//PSH
	float flt[3];
	float endflt;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMWindow1 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMWindow1, 0x15b2003f6);

	//PSH
	float flt[9];
	uint unk;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMLayered: RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMLayered, 0x1c7021ee3);

	//PSH
	float flt[3];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
	float flt00[23];
	float endflt;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMLandmark : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMLandmark, 0x73b630e6d);

	//PSH
	float flt[13];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[2];
	int endunk;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMGeneralMK3 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMGeneralMK3, 0x52cec5ad5);

	//PSH
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

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMGeneral6 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMGeneral6, 0x6a7583b2b);

	//PSH
	float flt[2];
	uint unk;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
	AdfBBOX bbox;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMCarLight : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMCarLight, 0x1db948bf1);

	//PSH
	float flt[14];
	float endflt;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMCarPaint14 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMCarPaint14, 0xE483304d6);

	//PSH
	int flags; // 0x1000 = deformable, 0x2000 = skinned, 0x20 | 0x40 = uv3
	float flt[98];
	float endflt;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMGeneral3 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMGeneral3, 0x304894ecd);

	//PSH
	float flt[64];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[2];
	int endunk;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMCharacter9 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMCharacter9, 0x99d6e332a);

	//PSH
	int flags;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	float flt[20];
	float endflt;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMCharacter6 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMCharacter6, 0x6626f5e3b);

	//PSH
	int flags; //0x2 = 2uv
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	float flt[7];
	float endflt;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMRoad : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMRoad, 0x1566dce92);

	//PSH
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
	int unk05[6];
	int endunk;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};

struct RBMGeneralSimple3 : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMGeneralSimple3, 0x335bf53d5);

	//PSH
	uint unk;
	float flt[25];
	uint unk00;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	int unk01[3];
	AdfBBOX bbox;

	//VSH
	float wireScale;
	Vector textureDensities;

	void Load(BinReader *rd);
};
