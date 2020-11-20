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
#include "datas/flags.hpp"
#include "datas/jenkinshash3.hpp"
#include "datas/reflector.hpp"
#include "datas/vectors.hpp"

struct RBNGeneralConstants : ReflectorInterface<RBNGeneralConstants> {
  static constexpr auto GetHash() { return JenHash3("RBNGeneralConstants"); }

  uint32 unk[2];
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  Vector2 UV3Scale;
  float flt1[3];
  uint32 additionalUVSets;
  float flt2[7];
  float fltend;
};

REFLECTOR_CREATE(RBNCharacterConstantsFlags, ENUM, 2, CLASS, 32,
                 HalfWeights = 16);

struct RBNCharacterConstants : ReflectorInterface<RBNCharacterConstants> {
  static constexpr auto GetHash() { return JenHash3("RBNCharacterConstants"); }

  es::Flags<RBNCharacterConstantsFlags> flags;
  float vertexScale;
  float flt1[11];
  uint32 additionalUVSets;
  float flt2[17];
  float fltend;
};

REFLECTOR_CREATE(RBNCarPaintConstantsFlags, ENUM, 2, CLASS, 32, Deformable = 3);

struct RBNCarPaintConstants : ReflectorInterface<RBNCarPaintConstants> {
  static constexpr auto GetHash() { return JenHash3("RBNCarPaintConstants"); }

  uint32 unk;
  float flt1[2];
  es::Flags<RBNCarPaintConstantsFlags> flags;
  float flt2;
  float fltend;
};

struct RBNWindowConstants : ReflectorInterface<RBNWindowConstants> {
  static constexpr auto GetHash() { return JenHash3("RBNWindowConstants"); }

  float flt1[3];
  uint32 unk;
};

struct RBNXXXXConstants : ReflectorInterface<RBNXXXXConstants> {
  static constexpr auto GetHash() { return JenHash3("RBNXXXXConstants"); }

  uint32 unk;
  float vertexScale;
  Vector2 UV1Scale;
  float fltend;
};
