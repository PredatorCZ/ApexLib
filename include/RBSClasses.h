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

struct RBSGeneral : RBMMasterBlock
{
	RBMCONSTRUCTOR(RBSGeneral, 0x70826f6ee);
	void Load(BinReader *rd);
};


struct RBSCharacter : RBSGeneral
{
	RBMCONSTRUCTOR(RBSCharacter, 0xd9d6e332a);
};

struct RBSCarPaint : RBSGeneral
{
	RBMCONSTRUCTOR(RBSCarPaint, 0x4483304d6);
};

struct RBSWindow : RBSGeneral
{
	RBMCONSTRUCTOR(RBSWindow, 0x55b2003f6);
};

struct RBSXXXX : RBSGeneral
{
	RBMCONSTRUCTOR(RBSXXXX, 0x4ed8b5331);
};