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
#include "datas/flags.hpp"

struct RBMUIOverlay : RBMMasterBlock
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMUIOverlay, 0xd7af3bee);

	//VSH
	uint type;

	void Load(BinReader *rd);
};

struct RBMScope : RBMUIOverlay
{
	DECLARE_REFLECTOR_EMPTY;
	RBMCONSTRUCTOR(RBMScope, 0x7e407c92);
};