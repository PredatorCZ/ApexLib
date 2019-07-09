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

struct ADFMatrix4x4
{
	Vector4 rows[4];
};

struct DeformPoint
{
	AdfString name;
	ApexHash nameHash;
	AdfString fromPart;
	ApexHash fromPartHash;
	uint fromPartIndex;
	AdfString skinnedToPart;
	ApexHash skinnedToPartHash;
	uint skinnedToPartIndex;
	uint shapeKey;
	uchar hasCustomEnd;
	AdfHashString deformPointType;
	ADFMatrix4x4 startTransform;
	ADFMatrix4x4 endTransform;
	ushort vertexIndices[4];
	float vertexWeights[4];

	void Fixup(char *masterBuffer);
};

static_assert(sizeof(DeformPoint) == 224, "Check assumptions");

struct DeformPoints
{
	AdfArray<DeformPoint> points;
	AdfArray<ushort> constraintIndices,
		lightIndices,
		wheelIndices,
		nonDeformablePartsIndices,
		haulingHitchIndices,
		trailingHitchIndices;

	void Fixup(char *masterBuffer);
};

static_assert(sizeof(DeformPoints) == 112, "Check assumptions");

class DeformPoints_wrap : public ADFInstance
{
	DeformPoints *data;

	void Fixup(char *masterBuffer);
	const char *RequestsFile() const { return nullptr; }
public:
	static const ApexHash HASH = 0xBA022EDF;

	DeformPoints_wrap(void *_data, ADF *_main);
	ES_FORCEINLINE DeformPoints *Data() { return data; }

	ApexHash GetSuperClass() const { return -1; }
};
