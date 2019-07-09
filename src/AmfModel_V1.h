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
#include "AmfMesh.h"
#include "AdfBaseObject.h"

struct AmfMaterial_V1
{
	ApexHash name;
	ApexHash renderBlockID;
private:
	union
	{
		AdfDeferred attributes;
		struct 
		{
			int pad[3];
			/*Hiding materialType inside of AdfDeferred's structure padding
			This is custom value btw...*/
			AmfMaterialType materialType;
		}materialType;
	}attributes;
public:
	AdfArray<char*> textures;

	ES_FORCEINLINE AdfDeferred &Attributes() { return attributes.attributes; }
	ES_FORCEINLINE AmfMaterialType &MaterialType() { return attributes.materialType.materialType; }
	ES_FORCEINLINE void Fixup(char *masterBuffer) { Attributes().item.Fixup(masterBuffer); }
};

struct AmfModel_V1
{
	ApexHash meshPath;
	AdfArray<uchar> lodSlots;
	int memoryTag;
	float lodFactor;
	AdfArray<AmfMaterial_V1> materials;

	ES_FORCEINLINE void Fixup(char *masterBuffer)
	{
		lodSlots.items.Fixup(masterBuffer);
		materials.items.Fixup(masterBuffer);

		for (auto &m : materials)
			m.Fixup(masterBuffer);
	}
};