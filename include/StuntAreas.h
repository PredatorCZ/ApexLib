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
#include "AdfBaseObject.h"
struct AxisAlignedBoundingBox
{
	float min_x, max_x, 
		min_y, max_y, 
		min_z, max_z;
	ES_FORCEINLINE operator AdfBBOX() { return AdfBBOX{ {min_x, min_y, min_z}, {max_x, max_y, max_z} }; }
};

struct StuntArea
{
	AdfString name;
	ApexHash nameHash;
	AdfString partName;
	ApexHash partHash;
	uint partIndex;
	uint deformPoints[16];
	uchar edgeValidity[16];
	ushort numDeformPoints,
		active;
	Vector vertices[16];
	UCVector faces[14];
	ushort numFaces;
	AxisAlignedBoundingBox BBOX;
	Vector center;
};

static_assert(sizeof(StuntArea) == 392, "Check assumptions");

struct StuntAreaWeldingInfo
{
	short aIndex, edgeAIndex, bIndex, edgeBIndex;
};

struct StuntAreas
{
	StuntArea stuntAreas[32];
	uchar numStuntAreas;
	StuntAreaWeldingInfo weldingInfos[64];
	uchar numWeldingInfos;
};

static_assert(sizeof(StuntAreas) == 13064, "Check assumptions");

struct ADFStuntAreas : ADFInstance, StuntAreas
{
	int Load(BinReader *rd, ADF *linker);
	void Link(ADF *) {};
	std::string *RequestsFile() { return nullptr; };
	void Merge(ADFInstance *externalInstance) {}
	static const ApexHash HASH = 0x9327DF87;
};