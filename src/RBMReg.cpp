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

#include "RBNClasses.h"
#include "RBSClasses.h"
#include "RBMClassesJC2.h"
#include "RBMClassesJC3.h"
#include "RBMClassesHU.h"
#include "datas/reflectorRegistry.hpp"

RBMPropsMapper RBMClassStorage;

template<class C> RBMMasterBlock *RBMCreateClass() { return new C{}; }

#define ADFRegisterClass(classname) RBMClassStorage[classname::HASH] = &RBMCreateClass<classname>;

#define ADFRegisterClassID(classname) const ApexHash classname::ADFHASH = JenkinsHash(#classname, sizeof(#classname) - 1);

ADFRegisterClassID(RBNGeneral);
ADFRegisterClassID(RBNCarPaint);
ADFRegisterClassID(RBNCharacter);
ADFRegisterClassID(RBNWindow);
ADFRegisterClassID(RBNXXXX);

ADFRegisterClassID(RBSGeneral);
ADFRegisterClassID(RBSCarPaint);
ADFRegisterClassID(RBSCharacter);
ADFRegisterClassID(RBSWindow);
ADFRegisterClassID(RBSXXXX);

ADFRegisterClassID(RBMCarPaintSimple);
ADFRegisterClassID(RBMFoliageBark);
ADFRegisterClassID(RBMVegetationFoliage);
ADFRegisterClassID(RBMBillboardFoliage);
ADFRegisterClassID(RBMHalo);
ADFRegisterClassID(RBMLambert);
ADFRegisterClassID(RBMGeneral);
ADFRegisterClassID(RBMFacade);
ADFRegisterClassID(RBMCarPaint);
ADFRegisterClassID(RBMWindow);
ADFRegisterClassID(RBMDeformWindow);
ADFRegisterClassID(RBMMerged);
ADFRegisterClassID(RBMSkinnedGeneral);

ADFRegisterClassID(RBMFoliageBark2);
ADFRegisterClassID(RBMVegetationFoliage3);
ADFRegisterClassID(RBMGeneralSimple);
ADFRegisterClassID(RBMWaterHull);
ADFRegisterClassID(RBMSimpleGeometry);
ADFRegisterClassID(RBMBavariumShiled);
ADFRegisterClassID(RBMLayered);
ADFRegisterClassID(RBMWindow1);
ADFRegisterClassID(RBMLandmark);
ADFRegisterClassID(RBMGeneralMK3);
ADFRegisterClassID(RBMGeneral6);
ADFRegisterClassID(RBMCarLight);
ADFRegisterClassID(RBMCarPaint14);
ADFRegisterClassID(RBMGeneral3);
ADFRegisterClassID(RBMCharacter6);
ADFRegisterClassID(RBMCharacter9);
ADFRegisterClassID(RBMRoad);
ADFRegisterClassID(RBMGeneralSimple3);

ADFRegisterClassID(RBMSkinnedGeneral0);
ADFRegisterClassID(RBMGeneral0);
ADFRegisterClassID(RBMUIOverlay);
ADFRegisterClassID(RBMScope);
ADFRegisterClassID(RBMSkinnedGeneralDecal);
ADFRegisterClassID(RBMFacade0);

void InitRBMRegistry()
{
	REGISTER_ENUM(RBMCarPaintSimpleFlags);
	REGISTER_ENUM(RBMGeneralFlags);
	REGISTER_ENUM(RBMFacadeFlags);
	REGISTER_ENUM(RBMSkinnedGeneralFlags);
	REGISTER_ENUM(RBMSkinnedGeneralTechnique);

	ADFRegisterClass(RBNGeneral);
	ADFRegisterClass(RBNCarPaint);
	ADFRegisterClass(RBNCharacter);
	ADFRegisterClass(RBNWindow);
	ADFRegisterClass(RBNXXXX);

	ADFRegisterClass(RBSGeneral);
	ADFRegisterClass(RBSCarPaint);
	ADFRegisterClass(RBSCharacter);
	ADFRegisterClass(RBSWindow);
	ADFRegisterClass(RBSXXXX);

	ADFRegisterClass(RBMCarPaintSimple);
	ADFRegisterClass(RBMFoliageBark);
	ADFRegisterClass(RBMVegetationFoliage);
	ADFRegisterClass(RBMBillboardFoliage);
	ADFRegisterClass(RBMHalo);
	ADFRegisterClass(RBMLambert);
	ADFRegisterClass(RBMGeneral);
	ADFRegisterClass(RBMFacade);
	ADFRegisterClass(RBMCarPaint);
	ADFRegisterClass(RBMWindow);
	ADFRegisterClass(RBMDeformWindow);
	ADFRegisterClass(RBMMerged);
	ADFRegisterClass(RBMSkinnedGeneral);

	ADFRegisterClass(RBMFoliageBark2);
	ADFRegisterClass(RBMVegetationFoliage3);
	ADFRegisterClass(RBMGeneralSimple);
	ADFRegisterClass(RBMWaterHull);
	ADFRegisterClass(RBMSimpleGeometry);
	ADFRegisterClass(RBMBavariumShiled);
	ADFRegisterClass(RBMLayered);
	ADFRegisterClass(RBMWindow1);
	ADFRegisterClass(RBMLandmark);
	ADFRegisterClass(RBMGeneralMK3);
	ADFRegisterClass(RBMGeneral6);
	ADFRegisterClass(RBMCarLight);
	ADFRegisterClass(RBMCarPaint14);
	ADFRegisterClass(RBMGeneral3);
	ADFRegisterClass(RBMCharacter6);
	ADFRegisterClass(RBMCharacter9);
	ADFRegisterClass(RBMRoad);
	ADFRegisterClass(RBMGeneralSimple3);

	ADFRegisterClass(RBMSkinnedGeneral0);
	ADFRegisterClass(RBMGeneral0);
	ADFRegisterClass(RBMUIOverlay);
	ADFRegisterClass(RBMScope);
	ADFRegisterClass(RBMSkinnedGeneralDecal);
	ADFRegisterClass(RBMFacade0);
}