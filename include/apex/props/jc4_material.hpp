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

REFLECTOR_CREATE(GeneralConstantsFlags, ENUM, 2, CLASS, 32, backfaceCulling,
                 alphaBlend, alphaTest, dynamicEmissive, worldSpaceNormals,
                 roadJunction, useVertexAnimation, anisotropicFiltering,
                 useCustomEmissiveHue, useMPMChannelInput, useDiffuseRoughness,
                 useSpecularAniso, useTransmission, useClearCoat, wireAA,
                 HDRReference, layeredUseLayering, overlayUseOverlay,
                 useEmissive, useEmissiveLightColor, roadDepthBias);

struct GeneralConstants : ReflectorInterface<GeneralConstants> {
  static constexpr auto GetHash() { return JenHash3(0x1B12D103); }

  Vector overlayColor;
  float roughnessModulator,           //
      metallicModulator,              //
      dielectricReflectance,          //
      emissiveIntensity,              //
      emissiveScale,                  //
      emissiveExposureAdapt,          //
      layeredHeightOffset,            //
      layeredContrast,                //
      layeredOpacity,                 //
      layeredBottomHeightInfluence,   //
      layeredTopHeightInfluence,      //
      layeredMaskInfluence,           //
      overlayHeightOffset,            //
      overlayContrast,                //
      overlayOpacity,                 //
      overlayBottomHeightInfluence,   //
      overlayTopHeightInfluence,      //
      overlayMaskInfluence,           //
      diffuseRoughness,               //
      specularAniso,                  //
      transmission,                   //
      clearCoat,                      //
      detailNormalModulator,          //
      detailNormalTileU,              //
      detailNormalTileV,              //
      depthBias,                      //
      hardwareDepthBias,              //
      hardwareSlopeBias,              //
      minTimeOfDayEmissive,           //
      startFadeOutDistanceEmissiveSq, //
      gIEmissionModulator,            //
      HDRReferenceMultiplier,         //
      rippleAngle,                    //
      rippleSpeed,                    //
      rippleMagnitude;
  es::Flags<GeneralConstantsFlags> flags;
};

struct CarLightConstants : ReflectorInterface<CarLightConstants> {
  static constexpr auto GetHash() { return JenHash3(0x948AE239); }

  Vector4 diffuseModulator;
  Vector2 detailTiling;
  float roughnessModulator,  //
      dielectricReflectance, //
      emissiveHead,          //
      emissiveBlinker,       //
      emissiveBrake,         //
      emissiveReverse;
  bool doubleSided;
};

REFLECTOR_CREATE(WindowConstantsFlags, ENUM, 2, CLASS, 8, simple, oneSided);

struct WindowConstants : ReflectorInterface<WindowConstants> {
  static constexpr auto GetHash() { return JenHash3(0x58D9967A); }

  float roughnessModulator,  //
      dielectricReflectance, //
      tintPower,             //
      minAlpha,              //
      UVScale;
  es::Flags<WindowConstantsFlags> flags;
};

struct CarPaintStaticConstants : ReflectorInterface<CarPaintStaticConstants> {
  static constexpr auto GetHash() { return JenHash3(0xE513D12B); }

  Vector4 dirtParams, //
      dirtBlend,      //
      dirtColor,      //
      decalCount,     //
      decalWidth,     //
      decal1Color,    //
      decal2Color,    //
      decal3Color,    //
      decal4Color,    //
      decalBlend,     //
      damage,         //
      damageBlend,    //
      damageColor;
  float roughnessModulator,  //
      metallicModulator,     //
      dielectricReflectance, //
      emissiveIntensity,     //
      diffuseRoughness,      //
      specularAniso,         //
      transmission,          //
      supportDecals,         //
      supportDmgBlend,       //
      supportRotating,       //
      supportScrolling,      //
      supportDirt,           //
      supportSoftTint,       //
      useLayeredBaseColor;
};

struct CarPaintDynamicConstants : ReflectorInterface<CarPaintDynamicConstants> {
  static constexpr auto GetHash() { return JenHash3(0xCD2C3428); }

  Vector4 tintColorR, //
      tintColorG,     //
      tintColorB,     //
      tecalIndex;
};

REFLECTOR_CREATE(CarPaintConstantsFlags0, ENUM, 2, CLASS, 16, decals,
                 useDamageBlend, dirt, tint, tintSoftBlend, twoSided,
                 alphaBlend, alphaTest, rotating, scrolling);

REFLECTOR_CREATE(CarPaintConstantsFlags1, ENUM, 2, CLASS, 32,
                 useCustomEmissiveHue, useMPMChannelInput);

REFLECTOR_CREATE(CarPaintConstantsFlags2, ENUM, 2, CLASS, 16,
                 useCustomDiffuseRoughness, useSpecularAniso, useTransmission,
                 useClearcoat);

struct CarPaintConstants : ReflectorInterface<CarPaintConstants> {
  static constexpr auto GetHash() { return JenHash3(0x73375A05); }

  CarPaintStaticConstants staticAttributes;
  CarPaintDynamicConstants dynamicAttributes;
  float gIEmissionModulator;
  es::Flags<CarPaintConstantsFlags0> flags0;
  es::Flags<CarPaintConstantsFlags1> flags1;
  es::Flags<CarPaintConstantsFlags2> flags2;
};

REFLECTOR_CREATE(CharacterSkinConstantsFlags, ENUM, 2, CLASS, 16, doubleSided,
                 useAlphaMask, useWrinkleMap, useFur, useMPMChannelInput,
                 useCustomDiffuseRoughness, useTransmission, headMaterial);

struct CharacterSkinConstants : ReflectorInterface<CharacterSkinConstants> {
  static constexpr auto GetHash() { return JenHash3(0xD8749464); }

  Vector2 detailTilingFactorUV;
  float roughnessModulator,  //
      transmissionModulator, //
      diffuseRoughness,      //
      transmission,          //
      dirtFactor,            //
      furLength,             //
      furThickness,          //
      furRoughness,          //
      furGravity,            //
      furSize;
  es::Flags<CharacterSkinConstantsFlags> flags;
};

REFLECTOR_CREATE(CharacterConstantsFlags, ENUM, 2, CLASS, 32, doubleSided,
                 alphaTest, alphaBlending, useDetail, useDecal, useTint,
                 useTintSoftBlend, useWrinkleMap, useCustomEmissiveHue,
                 useMPMChannelInput, useCustomDiffuseRoughness,
                 useSpecularAniso, useTransmission);

struct CharacterConstants : ReflectorInterface<CharacterConstants> {
  static constexpr auto GetHash() { return JenHash3(0x25970695); }

  Vector2 detailTilingFactorUV, //
      decalBlendFactors;
  float roughnessModulator,  //
      metallicModulator,     //
      dielectricReflectance, //
      diffuseRoughness,      //
      specularAniso,         //
      transmission,          //
      emissiveIntensity,     //
      dirtFactor;
  es::Flags<CharacterConstantsFlags> flags;
};

REFLECTOR_CREATE(EyeGlossConstantsFlags, ENUM, 2, CLASS, 16,
                 customEyeReflectionCube);

struct EyeGlossConstants : ReflectorInterface<EyeGlossConstants> {
  static constexpr auto GetHash() { return JenHash3(0x1BAC0639); }

  float eyeGlossiness,      //
      eyeSpecularIntensity, //
      eyeReflectIntensity,  //
      eyeReflectThreshold,  //
      eyeGlossShadowIntensity;
  es::Flags<EyeGlossConstantsFlags> flags;
};

REFLECTOR_CREATE(HairConstantsFlags, ENUM, 2, CLASS, 16, doubleSided, alphaTest,
                 alphaBlending);

struct HairConstants : ReflectorInterface<HairConstants> {
  static constexpr auto GetHash() { return JenHash3(0x342303CE); }

  float roughnessModulator, //
      specularMultiplier,   //
      scatteringMultiplier, //
      shiftFactor,          //
      dielectricReflectance;
  es::Flags<HairConstantsFlags> flags;
};

REFLECTOR_CREATE(BarkConstantsFlags, ENUM, 2, CLASS, 32, useMPMChannelInput,
                 useCustomDiffuseRoughness, detailNormalUseUV2,
                 useNewAnimation);

struct BarkConstants : ReflectorInterface<BarkConstants> {
  static constexpr auto GetHash() { return JenHash3(0x60A5C450); }

  float roughnessModulator,    //
      dielectricReflectance,   //
      diffuseRoughness,        //
      normalStrength,          //
      detailNormalModulator,   //
      detailNormalTileU,       //
      detailNormalTileV,       //
      isGrass,                 //
      maxWindRotation,         //
      distanceAtRotationStart, //
      distanceAtMaxRotation,   //
      windSpeedForMaxRotation, //
      leafStiffness,           //
      windProperty7,           //
      windProperty8;
  es::Flags<BarkConstantsFlags> flags;
};

struct FoliageConstants : ReflectorInterface<FoliageConstants> {
  static constexpr auto GetHash() { return JenHash3(0xA37CA160); }

  Vector4 diffuseModulator;
  float roughnessModulator,           //
      transmissionModulator,          //
      dielectricReflectance,          //
      sphereNormalStrength,           //
      transmission,                   //
      oneOverSubpixelDetailFadeRange, //
      ssGrass,                        //
      maxWindRotation,                //
      distanceAtRotationStart,        //
      distanceAtMaxRotation,          //
      windSpeedForMaxRotation,        //
      leafStiffness,                  //
      windProperty7,                  //
      windProperty8;
  es::Flags<FoliageConstantsFlags> flags;
};

struct HologramConstants : ReflectorInterface<HologramConstants> {
  static constexpr auto GetHash() { return JenHash3(0x75AF78A); }

  Vector emissiveColor;
  float emissiveIntensity, //
      blinkIntensity;
  Vector scanlineColor;
  float cloudIntensity,          //
      cloudTiling,               //
      cloudSpeedX,               //
      cloudSpeedY,               //
      scanline01Tiling,          //
      scanline01Speed,           //
      scanline01Thickness,       //
      scanline01Intensity,       //
      scanline01DetailTiling,    //
      scanline01DetailIntensity, //
      scanline02Tiling,          //
      scanline02Speed,           //
      scanline02Thickness,       //
      scanline02Intensity,       //
      meshlineTiling,            //
      meshlineSpeed,             //
      meshlineIntensity;
};

struct LandmarkConstants : ReflectorInterface<LandmarkConstants> {
  static constexpr auto GetHash() { return JenHash3(0xE73F3C81); }

  float specularGloss, //
      reflectivity,    //
      emissive,        //
      specularFresnel;
  Vector diffuseModulator;
  float diffuseWrap,                //
      backLight,                    //
      minTimeOfDayEmissive,         //
      startFadeOutDistanceEmissive, //
      depthBias;
};

struct EmissiveUIConstants : ReflectorInterface<EmissiveUIConstants> {
  static constexpr auto GetHash() { return JenHash3(0x669097B7); }

  Vector primaryColor, //
      secondaryColor;
  float bias,       //
      power,        //
      intensity,    //
      opacity,      //
      usePanning,   //
      panningSpeed, //
      panningScale;
};
