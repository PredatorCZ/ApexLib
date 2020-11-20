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

#define RBNCONSTRUCTOR(classname, shash) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1); static const uint64 RBMHASH = shash;\
const char *GetRenderBlockName() const { return #classname; } \
classname() { properties.objectHash = classname##Constants::HASH; renderBlockHash = JenkinsLookup3(#classname); }\
int GetPropertiesSize() const { return sizeof(classname##Constants); }\
void ReadRBM(BinReader *rd, char *&curBuffer, RBMMesh &mesh) {}

struct RBNGeneral : RBMMaterial
{
	RBNCONSTRUCTOR(RBNGeneral, 0x70826f6ee);
};

struct RBNCharacter : RBMMaterial
{
	RBNCONSTRUCTOR(RBNCharacter, 0xd9d6e332a);
};

struct RBNCarPaint : RBMMaterial
{
	RBNCONSTRUCTOR(RBNCarPaint, 0x4483304d6);
};

struct RBNWindow : RBMMaterial
{
	RBNCONSTRUCTOR(RBNWindow, 0x55b2003f6);
};

struct RBNXXXX : RBMMaterial
{
	RBNCONSTRUCTOR(RBNXXXX, 0x4ed8b5331);
};

