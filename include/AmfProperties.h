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
#include "ApexApi.h"
#include "AmfEnums.h"
#include "AdfBaseObject.h"
#include "datas/flags.hpp"
#include "datas/vectors.hpp"

#include "property_classes/AmfMeshProperties.h"
#include "property_classes/AmfJC4Material.h"
#include "property_classes/AmfHUMaterial.h"
#include "property_classes/AmfGZMaterial.h"
#include "property_classes/AmfR2Material.h"

#define DEFINE_PROPERTY(classname) static const ApexHash HASH = JenkinsHash(#classname, sizeof(#classname) - 1);
#define RBMREFLECTOR_FROM_PARENT(parentClass) \
const reflectorInstanceConst _rfRetreive() const { return { parentClass::__rfPtrStatic, this }; }\
const reflectorInstance _rfRetreive() { return { parentClass::__rfPtrStatic, this }; }

#include "property_classes/RbmJC2Material.h"
#include "property_classes/RbnMaterial.h"
#include "property_classes/RbmJC3Material.h"
