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

struct RBMVegetationFoliage3Constants
    : ReflectorInterface<RBMVegetationFoliage3Constants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMVegetationFoliage3Constants");
  }

  float flt[11];
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  uint32 flags;
  AdfBBOX bbox;
  uint32 null;
};

struct RBMFoliageBark2Constants : ReflectorInterface<RBMFoliageBark2Constants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMFoliageBark2Constants");
  }

  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  float flt00;
  AdfBBOX bbox;
  float flt[39];
};

struct RBMGeneralSimpleConstants
    : ReflectorInterface<RBMGeneralSimpleConstants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMGeneralSimpleConstants");
  }

  float flt[13];
  uint32 flags;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  int32 unk[3];
};

struct RBMWaterHullConstants : ReflectorInterface<RBMWaterHullConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMWaterHullConstants"); }

  float flt;
};

struct RBMSimpleGeometryConstants : RBMWaterHullConstants {
  static constexpr auto GetHash() {
    return JenHash3("RBMSimpleGeometryConstants");
  }
};

struct RBMBavariumShiledConstants
    : ReflectorInterface<RBMBavariumShiledConstants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMBavariumShiledConstants");
  }

  float flt[4];
};

struct RBMWindow1Constants : ReflectorInterface<RBMWindow1Constants> {
  static constexpr auto GetHash() { return JenHash3("RBMWindow1Constants"); }

  float flt[9];
  uint32 unk;
};

struct RBMLayeredConstants : ReflectorInterface<RBMLayeredConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMLayeredConstants"); }

  float flt[3];
  uint32 unk00;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  int32 unk01[3];
  float flt00[24];
};

struct RBMLandmarkConstants : ReflectorInterface<RBMLandmarkConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMLandmarkConstants"); }

  float flt[13];
  uint32 unk00;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  int32 unk01[3];
};

REFLECTOR_CREATE(RBMGeneralMK3ConstantsFlags, ENUM, 2, CLASS, 32,
                 Skinned = 5,       //
                 UseDecals = 9,     //
                 NoSkinWeights = 15 //
);

struct RBMGeneralMK3Constants : ReflectorInterface<RBMGeneralMK3Constants> {
  static constexpr auto GetHash() { return JenHash3("RBMGeneralMK3Constants"); }

  float flt[9];
  uint32 unk00;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  int32 unk01[3];
  es::Flags<RBMGeneralMK3ConstantsFlags> flags;
  AdfBBOX bbox;
  int32 unk02;
  float flt2[69];
  uint32 unk03;
};

struct RBMGeneral6Constants : ReflectorInterface<RBMGeneral6Constants> {
  static constexpr auto GetHash() { return JenHash3("RBMGeneral6Constants"); }

  float flt[2];
  uint32 unk;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  int32 unk01[3];
  AdfBBOX bbox;
};

struct RBMCarLightConstants : ReflectorInterface<RBMCarLightConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMCarLightConstants"); }

  float flt[15];
  int32 remapTable[256];
};

REFLECTOR_CREATE(RBMCarPaint14ConstantsFlags, ENUM, 2, CLASS, 32,
                 UV3_0 = 5,       //
                 UV3_1,           //
                 Deformable = 12, //
                 Skinned          //
);

struct RBMCarPaint14Constants : ReflectorInterface<RBMCarPaint14Constants> {
  static constexpr auto GetHash() { return JenHash3("RBMCarPaint14Constants"); }
  es::Flags<RBMCarPaint14ConstantsFlags> flags;
  float flt[99];
  int32 remapTable[256];
};

struct RBMGeneral3Constants : ReflectorInterface<RBMGeneral3Constants> {
  static constexpr auto GetHash() { return JenHash3("RBMGeneral3Constants"); }

  float flt[64];
  uint32 unk00;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  int32 unk01[3];
};

struct RBMCharacter9Constants : ReflectorInterface<RBMCharacter9Constants> {
  static constexpr auto GetHash() { return JenHash3("RBMCharacter9Constants"); }

  int32 flags;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  float flt[21];
};

REFLECTOR_CREATE(RBMCharacter6ConstantsFlags, ENUM, 2, CLASS, 32, UV2 = 1);

struct RBMCharacter6Constants : ReflectorInterface<RBMCharacter6Constants> {
  static constexpr auto GetHash() { return JenHash3("RBMCharacter6Constants"); }

  es::Flags<RBMCharacter6ConstantsFlags> flags;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  float flt[8];
};

REFLECTOR_CREATE(RBMRoadConstantsFlags, ENUM, 2, CLASS, 32, Skinned = 5);

struct RBMRoadConstants : ReflectorInterface<RBMRoadConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMRoadConstants"); }

  uint32 unk00[2];
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  int32 unk01[2];
  es::Flags<RBMRoadConstantsFlags> flags;
  AdfBBOX bbox;
  float flt00;
  int32 unk02[2];
  float flt01;
  int32 unk03;
  float flt02[2];
  int32 unk04[4];
  float flt03[29];
  int32 unk05[7];
};

struct RBMGeneralSimple3Constants
    : ReflectorInterface<RBMGeneralSimple3Constants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMGeneralSimple3Constants");
  }

  uint32 unk;
  float flt[25];
  uint32 unk00;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  int32 unk01[3];
  AdfBBOX bbox;
};

// VSH
struct RBMApex3MeshConstants : ReflectorInterface<RBMApex3MeshConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMApex3MeshConstants"); }

  float wireScale;
  Vector textureDensities;
};
