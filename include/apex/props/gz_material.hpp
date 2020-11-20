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

REFLECTOR_CREATE(GeneralR2ConstantsFlags, ENUM, 2, CLASS, 32, objectSpaceNormal,
                 useEmissive, emissiveTextureHasColor, useEmissiveLightColor,
                 doubleSided, decalBlend, alphaTest, detailUV2, useAlbedoDetail,
                 albedoDetailAlphaGloss, useNormalDetail, useTint, tintUV2,
                 useTextureBlend1, animateTexture, useVertexAnimations, fur,
                 useTextureBlend2, UISurface, useColorMask);

struct GeneralR2Constants : ReflectorInterface<GeneralR2Constants> {
  static constexpr auto GetHash() { return JenHash3(0x8BB29AA0); }

  float depthBias,          //
      detailRepeatU,        //
      detailRepeatV,        //
      terrainColorFactor,   //
      terrainTopProjection, //
      blendMaskContrast1,   //
      blendMaskContrast2;
  es::Flags<GeneralR2ConstantsFlags> flags;
};

static_assert(sizeof(GeneralR2Constants) == 32, "Check assumptions");

REFLECTOR_CREATE(GeneralMkIIIConstantsFlags, ENUM, 1, CLASS, dynamicEmissive,
                 alphaBlend, alphaTest, backfaceCulling, worldSpaceNormals,
                 usePropertyMasking, useLayered, useOverlay, useDecal,
                 useDamage, useVertexAnimation, roadDepthBias,
                 anisotropicFiltering, wireAA);

struct GeneralMkIIIConstants : ReflectorInterface<GeneralMkIIIConstants> {
  static constexpr auto GetHash() { return JenHash3(0xD01A8371); }

  float normalStrength,               //
      reflectivity_1,                 //
      roughness_1,                    //
      diffuseWrap_1,                  //
      emissive_1,                     //
      transmission_1,                 //
      clearCoat_1,                    //
      roughness_2,                    //
      diffuseWrap_2,                  //
      emissive_2,                     //
      transmission_2,                 //
      reflectivity_2,                 //
      clearCoat_2,                    //
      roughness_3,                    //
      diffuseWrap_3,                  //
      emissive_3,                     //
      transmission_3,                 //
      reflectivity_3,                 //
      clearCoat_3,                    //
      roughness_4,                    //
      diffuseWrap_4,                  //
      emissive_4,                     //
      transmission_4,                 //
      reflectivity_4,                 //
      clearCoat_4,                    //
      layeredHeightMapUVScale,        //
      layeredUVScale,                 //
      layeredHeight1Influence,        //
      layeredHeight2Influence,        //
      layeredHeightMapInfluence,      //
      layeredMaskInfluence,           //
      layeredShift,                   //
      layeredRoughness,               //
      layeredDiffuseWrap,             //
      layeredEmissive,                //
      layeredTransmission,            //
      layeredReflectivity,            //
      layeredClearCoat,               //
      decalBlend,                     //
      decalBlendNormal,               //
      decalReflectivity,              //
      decalRoughness,                 //
      decalDiffuseWrap,               //
      decalEmissive,                  //
      decalTransmission,              //
      decalClearCoat,                 //
      overlayHeightInfluence,         //
      overlayHeightMapInfluence,      //
      overlayMaskInfluence,           //
      overlayShift,                   //
      overlayColorR,                  //
      overlayColorG,                  //
      overlayColorB,                  //
      overlayBrightness,              //
      overlayGloss,                   //
      overlayMetallic,                //
      overlayReflectivity,            //
      overlayRoughness,               //
      overlayDiffuseWrap,             //
      overlayEmissive,                //
      overlayTransmission,            //
      overlayClearCoat,               //
      damageReflectivity,             //
      damageRoughness,                //
      damageDiffuseWrap,              //
      damageEmissive,                 //
      damageTransmission,             //
      damageHeightInfluence,          //
      damageMaskInfluence,            //
      damageClearCoat,                //
      depthBias,                      //
      hardwareDepthBias,              //
      hardwareSlopeBias,              //
      minTimeOfDayEmissive,           //
      startFadeOutDistanceEmissiveSq, //
      gIEmissionModulator,            //
      rippleAngle,                    //
      rippleSpeed,                    //
      rippleMagnitude;
  es::Flags<GeneralMkIIIConstantsFlags> flags;
};

static_assert(sizeof(GeneralMkIIIConstants) == 320, "Check assumptions");

REFLECTOR_CREATE(CharacterConstantsFlags_GZ, ENUM, 2, CLASS, 32, doubleSided,
                 alphaTest, alphaBlending, featureMapTint, wrinkleMap,
                 cameraLightingEnable);

struct CharacterConstants_GZ : ReflectorInterface<CharacterConstants_GZ> {
  static constexpr auto GetHash() { return JenHash3(0xCE6A3748); }

  Vector2 detailTilingFactorUV;
  float specularGloss,       //
      transmissionIntensity, //
      diffuseRoughness,      //
      emissiveIntensity,     //
      nightVisibility,       //
      rimFrontStrength,      //
      cameraStrength,        //
      cameraSpecular,        //
      rimStrength,           //
      dirtFactor;
  es::Flags<CharacterConstantsFlags_GZ> flags;
};

static_assert(sizeof(CharacterConstants_GZ) == 52, "Check assumptions");

struct HairConstants_GZ : ReflectorInterface<HairConstants_GZ> {
  static constexpr auto GetHash() { return JenHash3(0x55204F03); }

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

static_assert(sizeof(HairConstants_GZ) == 52, "Check assumptions");

REFLECTOR_CREATE(CharacterSkinConstantsFlags_GZ, ENUM, 2, CLASS, 16,
                 doubleSided, useAlphaMask, useFeatureTintMap, useWrinkleMap,
                 useFur);

struct CharacterSkinConstants_GZ
    : ReflectorInterface<CharacterSkinConstants_GZ> {
  static constexpr auto GetHash() { return JenHash3(0xA5A7B4D5); }

  Vector2 detailTilingFactorUV;
  float diffuseRoughness,    //
      transmissionModulator, //
      cameraStrength,        //
      cameraSpecular,        //
      dirtFactor,            //
      furLength,             //
      furThickness,          //
      furRoughness,          //
      furGravity,            //
      furSize;
  es::Flags<CharacterSkinConstantsFlags_GZ> flags;
};

static_assert(sizeof(CharacterSkinConstants_GZ) == 52, "Check assumptions");

REFLECTOR_CREATE(WindowConstantsFlags_GZ, ENUM, 2, CLASS, 16, simple, oneSided,
                 lensOcclusion);

struct WindowConstants_GZ : ReflectorInterface<WindowConstants_GZ> {
  static constexpr auto GetHash() { return JenHash3(0x943EA98D); }

  float specGloss,         //
      specFresnel,         //
      diffuseRoughness,    //
      tintPower,           //
      tintMultiplier,      //
      minAlpha,            //
      UVScale,             //
      chromaticAberration, //
      refractionStrength;
  es::Flags<WindowConstantsFlags_GZ> flags;
};

static_assert(sizeof(WindowConstants_GZ) == 40, "Check assumptions");

REFLECTOR_CREATE(BarkConstantsFlags_GZ, ENUM, 2, CLASS, 16, noFade, useWaterFog,
                 lowResShadows, useLayered, useOverlay, ignoreColorTint);

struct BarkConstants_GZ : ReflectorInterface<BarkConstants_GZ> {
  static constexpr auto GetHash() { return JenHash3(0xF5BBB286); }

  float glossiness,   //
      normalStrength, //
      diffuseWrap,    //
      fresnel;
  Vector4 diffuseModulator;
  float layeredHeightMapUVScale, //
      layeredUVScale,            //
      layeredHeight1Influence,   //
      layeredHeight2Influence,   //
      layeredHeightMapInfluence, //
      layeredMaskInfluence,      //
      layeredShift,              //
      layeredRoughness,          //
      layeredDiffuseWrap,        //
      layeredEmissive,           //
      layeredTransmission,       //
      layeredReflectivity,       //
      layeredClearCoat,          //
      layeredUpInfluence,        //
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
      overlayUpInfluence;
  es::Flags<BarkConstantsFlags_GZ> flags;
};

static_assert(sizeof(BarkConstants_GZ) == 160, "Check assumptions");

struct FoliageConstants_GZ : ReflectorInterface<FoliageConstants_GZ> {
  static constexpr auto GetHash() { return JenHash3(0xD32674C9); }

  Vector4 diffuseModulator;
  float specularGloss,       //
      emissionIntensity,     //
      transmissionIntensity, //
      diffuseWrap,           //
      reflectivity,          //
      specularFresnel,       //
      sphereNormalStrength,  //
      oneOverSubpixelDetailFadeRange;
  es::Flags<FoliageConstantsFlags, uint16> flags;
};

static_assert(sizeof(FoliageConstants_GZ) == 52, "Check assumptions");

struct CarLightConstants_GZ : ReflectorInterface<CarLightConstants_GZ> {
  static constexpr auto GetHash() { return JenHash3(0xFB2F8330); }

  Vector4 diffuseModulator;
  Vector2 detailTiling;
  float specularGloss, //
      reflectivity,    //
      emissiveHead,    //
      emissiveBlinker, //
      emissiveBrake,   //
      emissiveReverse, //
      specularFresnel;
  bool doubleSided;
};

static_assert(sizeof(CarLightConstants_GZ) == 56, "Check assumptions");
