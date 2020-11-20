/*  Apex Engine Format Library
    Copyright(C) 2014-2020 Lukas Cone

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
#include "datas/reflector.hpp"

REFLECTOR_CREATE(FoliageConstantsFlags, ENUM, 2, CLASS, 8, renderTransparent,
                 objectSpaceNormalMap, useInteractionDisplacement,
                 useInteractionFlattening, useCharacterInteractionFlattening,
                 useMPMChannelInput, useTransmission, useNewAnimation);

REFLECTOR_CREATE(HairConstantsFlags_GZ, ENUM, 2, CLASS, 16, doubleSided,
                 alphaTest, alphaBlending, useColorMask);
