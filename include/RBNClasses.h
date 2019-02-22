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

struct RBNGeneral : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBNGeneral, 0x1070826f6ee);

	//PSH
	uint unk[2];
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	Vector2 UV3Scale;
	float flt1[3];
	uint additionalUVSets;
	float flt2[7];
	float fltend;

	//VSH
	uint rbshash;

	void Load(BinReader *rd);
	void Link(ADF *base);
};

struct RBNCharacter : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBNCharacter, 0x10d9d6e332a);

	//PSH
	uint flags; //0x10000 = 2 boneWeights
	float vertexScale;
	float flt1[11];
	uint additionalUVSets;
	float flt2[17];
	float fltend;

	//VSH
	uint rbshash;

	void Load(BinReader *rd);
	void Link(ADF *base);
};

struct RBNCarPaint : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBNCarPaint, 0x104483304d6);

	//PSH
	uint unk;
	float flt1[2];
	uint flags; //0x8 deformable
	float flt2;
	float fltend;

	//VSH
	uint rbshash;

	void Load(BinReader *rd);
	void Link(ADF *base);
};

struct RBNWindow : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBNWindow, 0x1055b2003f6);

	//PSH
	float flt1[3];
	uint unk;

	//VSH
	uint rbshash;

	void Load(BinReader *rd);
	void Link(ADF *base);
};

struct RBNXXXX : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBNXXXX, 0x104ed8b5331);

	//PSH
	uint unk;
	float vertexScale;
	Vector2 UV1Scale;
	float fltend;

	//VSH
	uint rbshash;

	void Load(BinReader *rd);
	void Link(ADF *base);
};

