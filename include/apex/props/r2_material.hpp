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
#include "common_flags.hpp"
#include "datas/flags.hpp"
#include "datas/jenkinshash3.hpp"
#include "datas/vectors.hpp"

REFLECTOR_CREATE(CharacterSkinConstantsFlags_R2, ENUM, 2, CLASS, 16,
                 blendUseUV2, useTint, doubleSided, useAlphaMask, useWrinkleMap,
                 useFur, useGibAlbedo, useGibDetail, triangleAdjacency);

struct CharacterSkinConstants_R2
    : ReflectorInterface<CharacterSkinConstants_R2> {
  static constexpr auto GetHash() { return JenHash3(0x3C710AD8); }

  float transmissionModulator, //
      emissiveScale,           //
      cameraStrength,          //
      cameraSpecular,          //
      dirtFactor,              //
      furLength,               //
      furThickness,            //
      furRoughness,            //
      furGravity,              //
      furSize,                 //
      gibAlbedoUVScale,        //
      gibDetailUVScale,        //
      gibSpecGloss,            //
      gibSoftDetailEdge;
  Vector tintColor1, //
      tintColor2,    //
      tintColor3,    //
      tintColor4;
  float detailUVmult1,               //
      detailUVmult2,                 //
      detailUVmult3,                 //
      detailUVmult4,                 //
      blendUVMultiplier1,            //
      blendMaskBias1,                //
      blendMaskBreakup1,             //
      blendMaskContrast1,            //
      wrinkleStrength,               //
      wrinkleOffsetBrowLeft,         //
      wrinkleOffsetBrowMid,          //
      wrinkleOffsetBrowRight,        //
      wrinkleOffsetUpcheekLeft,      //
      wrinkleOffsetNoseLeft,         //
      wrinkleOffsetNoseRight,        //
      wrinkleOffsetUpcheekRight,     //
      wrinkleOffsetJawLeft,          //
      wrinkleOffsetMouthbottomLeft,  //
      wrinkleOffsetMouthbottomRight, //
      wrinkleOffsetJawRight,         //
      wrinkleOffsetNeckStretchLeft,  //
      wrinkleOffsetNeckStretchRight, //
      wrinkleOffsetJawDownLeft,      //
      wrinkleOffsetJawDownRight;
  es::Flags<CharacterSkinConstantsFlags_R2> flags;
};

static_assert(sizeof(CharacterSkinConstants_R2) == 204, "Check assumptions");

REFLECTOR_CREATE(GeneralR2Constants_R2_flags0, ENUM, 2, CLASS, 32,
                 objectSpaceNormal, useEmissive, emissiveOnlyTransparent,
                 emissiveTextureHasColor, useEmissiveLightColor, doubleSided,
                 decalBlend, alphaTest, detailUV2, useAlbedoDetail,
                 albedoDetailAlphaGloss, useNormalDetail);

REFLECTOR_CREATE(GeneralR2Constants_R2_flags1, ENUM, 2, CLASS, 32,
                 useTextureBlend1, animateTexture, useVertexAnimations,
                 useRigidVertexAnimations, useSoftVertexAnimations,
                 useFluidVertexAnimations);

REFLECTOR_CREATE(GeneralR2Constants_R2_flags2, ENUM, 2, CLASS, 32,
                 vertexAnimLoops, directional, fur, HDRRef, useTextureBlend2);

struct GeneralR2Constants_R2 : ReflectorInterface<GeneralR2Constants_R2> {
  static constexpr auto GetHash() { return JenHash3(0x5449DC72); }

  float depthBias,           //
      detailRepeatU,         //
      detailRepeatV,         //
      terrainColorFactor,    //
      terrainTopProjection,  //
      blendMaskContrast1,    //
      blendMaskContrast2,    //
      blendUVMultiplier1,    //
      blendUVMultiplier2,    //
      blendMaskBias1,        //
      blendMaskBias2,        //
      blendMaskBreakup1,     //
      blendMaskBreakup2,     //
      emissiveScale,         //
      emissiveExposureAdapt, //
      emissiveRollOff;
  Vector tintColor1, //
      tintColor2,    //
      tintColor3,    //
      tintColor4;
  float tintBreakup, //
      tintContrast;
  Vector decalAlphaWeights;
  float dirtUVMultiplier;
  es::Flags<GeneralR2Constants_R2_flags0> flags0;
  float useTint;
  bool tintUV2;
  float tintOrder;
  es::Flags<GeneralR2Constants_R2_flags1> flags1;
  float vertexAnimBBoxMin, //
      vertexAnimBBoxMax;
  bool vertexAnimSwizzle;
  float vertexAnimPhase;
  uint vertexAnimFrames;
  es::Flags<GeneralR2Constants_R2_flags2> flags2;
  float dirtEnabled;
  Vector dirtColor;
  float dirtAmount,  //
      dirtRoughness, //
      dirtBias,      //
      dirtBreakup,   //
      dirtContrast;
  Vector debugColor;
};

static_assert(sizeof(GeneralR2Constants_R2) == 228, "Check assumptions");

struct HairConstants_R2 : ReflectorInterface<HairConstants_R2> {
  static constexpr auto GetHash() { return JenHash3(0xD5C4F848); }

  float specularGloss,       //
      transmissionIntensity, //
      specularFresnel,       //
      diffuseWrap,           //
      diffuseRoughness,      //
      anisotropicStrength,   //
      anisotropicX,          //
      anisotropicY,          //
      rimStrength,           //
      ringStrength,          //
      ringAngle,             //
      ringOffset;
  es::Flags<HairConstantsFlags_GZ> flags;
};

REFLECTOR_CREATE(WindowConstantsFlags_R2, ENUM, 2, CLASS, 8, simple, oneSided,
                 skinned, dirtLayerEnable);

struct WindowConstants_R2 : ReflectorInterface<WindowConstants_R2> {
  static constexpr auto GetHash() { return JenHash3(0xD275AA25); }

  Vector baseTransmission;
  float maxRoughness,         //
      baseBreakup,            //
      baseContrast,           //
      specularFresnel,        //
      normalMapStrength,      //
      damagedRoughness,       //
      damagedSpecularFresnel, //
      thickness,              //
      damageUVScale;
  Vector dirtAlbedo;
  float dirtSpecularFresnel, //
      dirtUVScale,           //
      dirtBreakup,           //
      dirtContrast,          //
      dirtMaxTransmission;
  es::Flags<WindowConstantsFlags_R2> flags;
  float UVAnimSpeedX, //
      UVAnimSpeedY;
  bool useAnim;
};

static_assert(sizeof(WindowConstants_R2) == 96, "Check assumptions");

REFLECTOR_CREATE(BarkConstantsFlags0_R2, ENUM, 2, CLASS, 8, useObjectNormal,
                 useTextureBlend1);

REFLECTOR_CREATE(BarkConstantsFlags1_R2, ENUM, 2, CLASS, 8, noFade, useWaterFog,
                 lowResShadows);

struct BarkConstants_R2 : ReflectorInterface<BarkConstants_R2> {
  static constexpr auto GetHash() { return JenHash3(0x7DAEE004); }

  es::Flags<BarkConstantsFlags0_R2> flags0;
  float blendUpInfluence1,       //
      blendUpNormal1,            //
      blendUpContrast1,          //
      blendUpShift1,             //
      blendMaskBias1,            //
      blendMaskBreakup1,         //
      blendMaskContrast1,        //
      blendUvMultiplier1,        //
      overlayHeightInfluence,    //
      overlayHeightMapInfluence, //
      overlayMaskInfluence,      //
      overlayShift;
  Vector overlayColor;
  float overlayBrightness, //
      overlayGloss,        //
      overlayMetallic,     //
      overlayReflectivity, //
      overlayRoughness,    //
      overlayDiffuseWrap,  //
      overlayEmissive,     //
      overlayTransmission, //
      overlayClearCoat,    //
      overlayUpInfluence,  //
      placedInstanceTerrainTintAmount;
  es::Flags<BarkConstantsFlags1_R2> flags1;
};

static_assert(sizeof(BarkConstants_R2) == 112, "Check assumptions");

struct HologramConstants_R2 : ReflectorInterface<HologramConstants_R2> {
  static constexpr auto GetHash() { return JenHash3(0xE0DE5D23); }

  float rasterHorizontalFreq,    //
      rasterHorizontalStrength,  //
      rasterVerticalFreq,        //
      rasterVerticalStrength,    //
      distortionHorizontalSpeed, //
      distortionVerticalSpeed,   //
      maxSeparation,             //
      horizontalDistortion,      //
      verticalDistortion,        //
      noiseStrength,             //
      noiseBandThreshold,        //
      brightness,                //
      exposureAdaptation,        //
      patternHorizontalSpeed,    //
      patternVerticalSpeed,      //
      type;
  Vector baseColor, //
      primaryColor, //
      secondaryColor;
  Vector4 edgeFade;
};

static_assert(sizeof(HologramConstants_R2) == 116, "Check assumptions");

REFLECTOR_CREATE(FoliageConstantsFlags_R2, ENUM, 2, CLASS, 8, renderTransparent,
                 objectSpaceNormalMap, useInteractionDisplacement,
                 useInteractionFlattening, useCharacterInteractionFlattening,
                 positiveBackfaceNormals);

struct FoliageConstants_R2 : ReflectorInterface<FoliageConstants_R2> {
  static constexpr auto GetHash() { return JenHash3(0x65CCA378); }

  Vector4 diffuseModulator;
  float specularGloss,                //
      emissionIntensity,              //
      transmissionIntensity,          //
      diffuseWrap,                    //
      reflectivity,                   //
      specularFresnel,                //
      sphereNormalStrength,           //
      oneOverSubpixelDetailFadeRange, //
      placedInstanceTerrainTintAmount;
  es::Flags<FoliageConstantsFlags_R2> flags;
};

static_assert(sizeof(FoliageConstants_R2) == 56, "Check assumptions");
