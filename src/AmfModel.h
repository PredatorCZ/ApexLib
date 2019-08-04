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
#include "AmfProperties.h"

struct AmfModel_V1;
struct AmfMaterial_V1;
class ADF;

class AmfModel_V1_wrap : public AmfModel
{
	AmfModel_V1 *data;
	ADF *main;

	void Fixup(char *masterBuffer);
	const char *RequestsFile() const;
	void Merge(ADFInstance *externalInstance) {}
public:
	static const ApexHash HASH = 0xF7C20A69;

	AmfModel_V1_wrap(void *_data, ADF *_main);

	int GetNumMaterials() const;
	AmfMaterial::Ptr GetMaterial(int id) const;

	ApexHash GetSuperClass() const { return AmfModel::HASH; }
};