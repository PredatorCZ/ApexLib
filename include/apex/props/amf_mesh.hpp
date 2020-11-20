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
#include "apex/adf_bbox.hpp"
#include "datas/flags.hpp"

REFLECTOR_CREATE(GeneralMeshConstantsFlags, ENUM, 2, CLASS, 8,
                 isDestructionMesh, isSkinnedMesh);

struct GeneralMeshConstants : ReflectorInterface<GeneralMeshConstants> {
  static constexpr auto GetHash() { return JenHash3(0x15EEC9DE); }

  uint32 pristineIndexCount;
  es::Flags<GeneralMeshConstantsFlags> flags;
};

struct FoliageMeshConstants : ReflectorInterface<FoliageMeshConstants> {
  static constexpr auto GetHash() { return JenHash3(0xA7CACE80); }

  AdfBBOX boundingBoxDimensions;
};

REFLECTOR_CREATE(CarPaintMeshConstantsFlags, ENUM, 2, CLASS, 8, deformable,
                 skinned);

struct CarPaintMeshConstants : ReflectorInterface<CarPaintMeshConstants> {
  static constexpr auto GetHash() { return JenHash3(0x1C363162); }

  es::Flags<CarPaintMeshConstantsFlags> flags;
};
