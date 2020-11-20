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

REFLECTOR_CREATE(RBMCarPaintSimpleFlags, ENUM, 2, CLASS, 32, NoCulling, Alpha,
                 TwoTone, IgnorePalette, NoDirt, Decal, MaskWater, AlphaTest);

struct RBMCarPaintSimpleConstants
    : ReflectorInterface<RBMCarPaintSimpleConstants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMCarPaintSimpleConstants");
  }

  Vector twoToneColor1;
  Vector twoToneColor2;
  float specularPower;
  float depthBias;
  float reflectionMultiplier;
  float unk[4];
  es::Flags<RBMCarPaintSimpleFlags> flags;
};

struct RBMFoliageBarkConstants : ReflectorInterface<RBMFoliageBarkConstants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMFoliageBarkConstants");
  }

  uint32 flags;
};

struct RBMVegetationFoliageConstants
    : ReflectorInterface<RBMVegetationFoliageConstants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMVegetationFoliageConstants");
  }

  float specularIntensity;
  float specularPower;
  Vector translucencyColorMask;
  uint32 flags;
};

struct RBMLambertConstants : ReflectorInterface<RBMLambertConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMLambertConstants"); }

  uint32 shaderType;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  uint32 unk[4];
  uint32 endunk;
};

REFLECTOR_CREATE(RBMGeneralFlags, ENUM, 2, CLASS, 32, NoCulling, Alpha,
                 AdditiveAlpha, _null00, _null01, ChannelMask, UseSnow,
                 AnimatedTexture, AlphaTest, UseChannelAO);

struct RBMGeneralConstants : ReflectorInterface<RBMGeneralConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMGeneralConstants"); }

  Vector4 channelMask;
  Vector4 channelAoMask;
  float depthBias;
  float specularPower;
  es::Flags<RBMGeneralFlags> flags;
  float vertexScale;
  Vector2 UV1Scale;
  Vector2 UV2Scale;
  uint32 unk[2];
  uint32 endunk;
};

REFLECTOR_CREATE(RBMFacadeFlags, ENUM, 2, CLASS, 32, NoCulling, Alpha, _null00,
                 _null01, UseChannelAO, UseChannelTextures, UseSnow);

struct RBMFacadeConstants : ReflectorInterface<RBMFacadeConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMFacadeConstants"); }

  Vector4 channelMask;
  Vector channelDirtMask;
  Vector emissiveMultiplier;
  float depthBias;
  float specularPower;
  es::Flags<RBMFacadeFlags> flags;
  float vertexScale;
  uint32 unk1;
};

struct RBMWindowConstants : ReflectorInterface<RBMWindowConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMWindowConstants"); }

  float specularPower;
  uint32 flags;
};

struct RBMCarPaintConstants : RBMCarPaintSimpleConstants {
  static constexpr auto GetHash() { return JenHash3("RBMCarPaintConstants"); }
};

REFLECTOR_CREATE(RBMSkinnedGeneralTechnique, ENUM, 2, CLASS, 16, Skin, Hair,
                 Cloth, Metal, EyeGloss, SkinAlphaToCoverage);

REFLECTOR_CREATE(RBMSkinnedGeneralFlags, ENUM, 2, CLASS, 16, NoCulling,
                 AlphaTest, NoShadowCasting, WideBoneWeights);

struct RBMSkinnedGeneralConstants
    : ReflectorInterface<RBMSkinnedGeneralConstants> {
  static constexpr auto GetHash() {
    return JenHash3("RBMSkinnedGeneralConstants");
  }

  RBMSkinnedGeneralTechnique technique;
  es::Flags<RBMSkinnedGeneralFlags> flags;
  float specularPower;
  float rimIntensity;
  float rimPower;
  Vector rimWeights;
};

struct RBMSkinnedGeneral0Constants : RBMSkinnedGeneralConstants {
  static constexpr auto GetHash() {
    return JenHash3("RBMSkinnedGeneral0Constants");
  }
};

struct RBMSkinnedGeneralDecalConstants : RBMSkinnedGeneralConstants {
  static constexpr auto GetHash() {
    return JenHash3("RBMSkinnedGeneralDecalConstants");
  }
};

struct RBMGeneral0Constants : RBMGeneralConstants {
  static constexpr auto GetHash() { return JenHash3("RBMGeneral0Constants"); }
};

struct RBMFacade0Constants : RBMFacadeConstants {
  static constexpr auto GetHash() { return JenHash3("RBMFacade0Constants"); }
};

struct RBMBillboardFoliageConstants {
  static constexpr auto GetHash() {
    return JenHash3("RBMBillboardFoliageConstants");
  }
};

struct RBMHaloConstants {
  static constexpr auto GetHash() { return JenHash3("RBMHaloConstants"); }
};

struct RBMDeformWindowConstants {
  static constexpr auto GetHash() {
    return JenHash3("RBMDeformWindowConstants");
  }
};

struct RBMMergedConstants {
  static constexpr auto GetHash() { return JenHash3("RBMMergedConstants"); }
};

struct RBMUIOverlayConstants {
  static constexpr auto GetHash() { return JenHash3("RBMUIOverlayConstants"); }
};

struct RBMScopeConstants {
  static constexpr auto GetHash() { return JenHash3("RBMScopeConstants"); }
};

// VSH
struct RBMApex2MeshConstants : ReflectorInterface<RBMApex2MeshConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMApex2MeshConstants"); }

  uint32 flags;
};

struct RBMMergedMeshConstants : ReflectorInterface<RBMMergedMeshConstants> {
  static constexpr auto GetHash() { return JenHash3("RBMMergedMeshConstants"); }

  uint32 unk;
  bool useVertexBuffer;
  uint32 unk2;
};
