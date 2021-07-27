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

#include "adf.hpp"
#include "amf_stream_attribute.hpp"
#include "apex/adf_deferred.hpp"
#include "apex/props/amf_mesh.hpp"
#include "apex/props/gz_material.hpp"
#include "apex/props/hu_material.hpp"
#include "apex/props/jc2_material.hpp"
#include "apex/props/jc3_material.hpp"
#include "apex/props/jc4_material.hpp"
#include "apex/props/mm_material.hpp"
#include "apex/props/r2_material.hpp"
#include <map>

template <class C> struct f_ {
  static AdfDeferred::refptr_const makeConst(const void *data) {
    return std::make_unique<ReflectorWrapConst<C>>(
        static_cast<const ReflectorInterface<C> *>(data));
  }
  static AdfDeferred::refptr make(void *data) {
    return std::make_unique<ReflectorWrap<C>>(
        static_cast<ReflectorInterface<C> *>(data));
  }
};

struct PropMakerData {
  decltype(&f_<void>::makeConst) makeConst;
  decltype(&f_<void>::make) make;
};

template <class C> auto MakePair() {
  return std::make_pair(C::GetHash(),
                        PropMakerData{f_<C>::makeConst, f_<C>::make});
}

static const std::map<JenHash3, PropMakerData> propsReg{
    // AMF
    MakePair<GeneralMeshConstants>(),
    MakePair<FoliageMeshConstants>(),
    MakePair<CarPaintMeshConstants>(),

    // JC4
    MakePair<GeneralConstants>(),
    MakePair<CarLightConstants>(),
    MakePair<WindowConstants>(),
    MakePair<CarPaintStaticConstants>(),
    MakePair<CarPaintDynamicConstants>(),
    MakePair<CarPaintConstants>(),
    MakePair<CharacterSkinConstants>(),
    MakePair<CharacterConstants>(),
    MakePair<EyeGlossConstants>(),
    MakePair<HairConstants>(),
    MakePair<BarkConstants>(),
    MakePair<FoliageConstants>(),
    MakePair<HologramConstants>(),
    MakePair<LandmarkConstants>(),
    MakePair<EmissiveUIConstants>(),

    // GZ
    MakePair<GeneralR2Constants>(),
    MakePair<GeneralMkIIIConstants>(),
    MakePair<CharacterConstants_GZ>(),
    MakePair<HairConstants_GZ>(),
    MakePair<CharacterSkinConstants_GZ>(),
    MakePair<WindowConstants_GZ>(),
    MakePair<BarkConstants_GZ>(),
    MakePair<FoliageConstants_GZ>(),
    MakePair<CarLightConstants_GZ>(),

    // JC2
    MakePair<RBMCarPaintSimpleConstants>(),
    // MakePair<RBMFoliageBarkConstants>(),
    MakePair<RBMVegetationFoliageConstants>(),
    // MakePair<RBMLambertConstants>(),
    MakePair<RBMGeneralConstants>(),
    MakePair<RBMFacadeConstants>(),
    MakePair<RBMWindowConstants>(),
    MakePair<RBMCarPaintConstants>(),
    MakePair<RBMSkinnedGeneralConstants>(),
    MakePair<RBMSkinnedGeneral0Constants>(),
    MakePair<RBMSkinnedGeneralDecalConstants>(),
    MakePair<RBMGeneral0Constants>(),
    MakePair<RBMFacade0Constants>(),
    // MakePair<RBMBillboardFoliageConstants>(),
    // MakePair<RBMHaloConstants>(),
    // MakePair<RBMDeformWindowConstants>(),
    // MakePair<RBMMergedConstants>(),
    // MakePair<RBMUIOverlayConstants>(),
    // MakePair<RBMScopeConstants>(),
    // MakePair<RBMApex2MeshConstants>(),
    // MakePair<RBMMergedMeshConstants>(),

    // JC3
    // MakePair<RBMVegetationFoliage3Constants>(),
    // MakePair<RBMFoliageBark2Constants>(),
    // MakePair<RBMGeneralSimpleConstants>(),
    // MakePair<RBMWaterHullConstants>(),
    // MakePair<RBMSimpleGeometryConstants>(),
    // MakePair<RBMBavariumShiledConstants>(),
    // MakePair<RBMWindow1Constants>(),
    // MakePair<RBMLayeredConstants>(),
    // MakePair<RBMLandmarkConstants>(),
    // MakePair<RBMGeneralMK3Constants>(),
    // MakePair<RBMGeneral6Constants>(),
    // MakePair<RBMCarLightConstants>(),
    // MakePair<RBMCarPaint14Constants>(),
    // MakePair<RBMGeneral3Constants>(),
    // MakePair<RBMCharacter9Constants>(),
    // MakePair<RBMCharacter6Constants>(),
    // MakePair<RBMRoadConstants>(),
    // MakePair<RBMGeneralSimple3Constants>(),
    // MakePair<RBMApex3MeshConstants>(),

    // MM
    // MakePair<RBNGeneralConstants>(),
    // MakePair<RBNCharacterConstants>(),
    // MakePair<RBNCarPaintConstants>(),
    // MakePair<RBNWindowConstants>(),
    // MakePair<RBNXXXXConstants>(),

    // R2
    MakePair<CharacterSkinConstants_R2>(),
    MakePair<GeneralR2Constants_R2>(),
    MakePair<HairConstants_R2>(),
    MakePair<WindowConstants_R2>(),
    MakePair<BarkConstants_R2>(),
    MakePair<HologramConstants_R2>(),
    MakePair<FoliageConstants_R2>(),
};

AdfDeferred::refptr_const AdfDeferred::GetReflected() const {
  auto found = propsReg.find(objectHash);

  if (es::IsEnd(propsReg, found)) {
    return {};
  }

  return found->second.makeConst(item);
}

AdfDeferred::refptr AdfDeferred::GetReflected() {
  auto found = propsReg.find(objectHash);

  if (es::IsEnd(propsReg, found)) {
    return {};
  }

  return found->second.make(item);
}

ADFInternal::ADFInternal() {
  RegisterReflectedTypes<
      // AMF
      GeneralMeshConstantsFlags,  //
      CarPaintMeshConstantsFlags, //

      // common
      FoliageConstantsFlags, //
      HairConstantsFlags_GZ, //

      // GZ
      GeneralR2ConstantsFlags,        //
      GeneralMkIIIConstantsFlags,     //
      CharacterConstantsFlags_GZ,     //
      CharacterSkinConstantsFlags_GZ, //
      WindowConstantsFlags_GZ,        //
      BarkConstantsFlags_GZ,          //

      // JC2
      RBMCarPaintSimpleFlags,     //
      RBMGeneralFlags,            //
      RBMFacadeFlags,             //
      RBMSkinnedGeneralTechnique, //
      RBMSkinnedGeneralFlags,     //

      // JC3
      // RBMGeneralMK3ConstantsFlags, //
      // RBMCarPaint14ConstantsFlags, //
      // RBMCharacter6ConstantsFlags, //
      // RBMRoadConstantsFlags,       //

      // JC4
      GeneralConstantsFlags,       //
      WindowConstantsFlags,        //
      CarPaintConstantsFlags0,     //
      CarPaintConstantsFlags1,     //
      CarPaintConstantsFlags2,     //
      CharacterSkinConstantsFlags, //
      CharacterConstantsFlags,     //
      EyeGlossConstantsFlags,      //
      HairConstantsFlags,          //
      BarkConstantsFlags,          //
      CarPaintStaticConstants,     //
      CarPaintDynamicConstants,    //

      // MM
      // RBNCharacterConstantsFlags, //
      // RBNCarPaintConstantsFlags,  //

      // R2
      CharacterSkinConstantsFlags_R2, //
      GeneralR2Constants_R2_flags0,   //
      GeneralR2Constants_R2_flags1,   //
      GeneralR2Constants_R2_flags2,   //
      WindowConstantsFlags_R2,        //
      BarkConstantsFlags0_R2,         //
      BarkConstantsFlags1_R2,         //
      FoliageConstantsFlags_R2        //
      >();
}

REFLECTOR_CREATE(AdfBBOX, 1, VARNAMES, min, max);

// AMF
REFLECTOR_CREATE(GeneralMeshConstants, 1, VARNAMES, pristineIndexCount, flags);
REFLECTOR_CREATE(FoliageMeshConstants, 1, VARNAMES, boundingBoxDimensions);
REFLECTOR_CREATE(CarPaintMeshConstants, 1, VARNAMES, flags);

// JC4
REFLECTOR_CREATE(GeneralConstants, 1, VARNAMES, overlayColor,
                 roughnessModulator, metallicModulator, dielectricReflectance,
                 emissiveIntensity, emissiveScale, emissiveExposureAdapt,
                 layeredHeightOffset, layeredContrast, layeredOpacity,
                 layeredBottomHeightInfluence, layeredTopHeightInfluence,
                 layeredMaskInfluence, overlayHeightOffset, overlayContrast,
                 overlayOpacity, overlayBottomHeightInfluence,
                 overlayTopHeightInfluence, overlayMaskInfluence,
                 diffuseRoughness, specularAniso, transmission, clearCoat,
                 detailNormalModulator, detailNormalTileU, detailNormalTileV,
                 depthBias, hardwareDepthBias, hardwareSlopeBias,
                 minTimeOfDayEmissive, startFadeOutDistanceEmissiveSq,
                 gIEmissionModulator, HDRReferenceMultiplier, rippleAngle,
                 rippleSpeed, rippleMagnitude, flags);

REFLECTOR_CREATE(CarLightConstants, 1, VARNAMES, diffuseModulator, detailTiling,
                 roughnessModulator, dielectricReflectance, emissiveHead,
                 emissiveBlinker, emissiveBrake, emissiveReverse, doubleSided);

REFLECTOR_CREATE(WindowConstants, 1, VARNAMES, roughnessModulator,
                 dielectricReflectance, tintPower, minAlpha, UVScale, flags);

REFLECTOR_CREATE(CarPaintStaticConstants, 1, VARNAMES, dirtParams, dirtBlend,
                 dirtColor, decalCount, decalWidth, decal1Color, decal2Color,
                 decal3Color, decal4Color, decalBlend, damage, damageBlend,
                 damageColor, roughnessModulator, metallicModulator,
                 dielectricReflectance, emissiveIntensity, diffuseRoughness,
                 specularAniso, transmission, supportDecals, supportDmgBlend,
                 supportRotating, supportScrolling, supportDirt,
                 supportSoftTint, useLayeredBaseColor);

REFLECTOR_CREATE(CarPaintDynamicConstants, 1, VARNAMES, tintColorR, tintColorG,
                 tintColorB, tecalIndex);

REFLECTOR_CREATE(CarPaintConstants, 1, VARNAMES, staticAttributes,
                 dynamicAttributes, gIEmissionModulator, flags0, flags1,
                 flags2);

REFLECTOR_CREATE(CharacterSkinConstants, 1, VARNAMES, detailTilingFactorUV,
                 roughnessModulator, transmissionModulator, diffuseRoughness,
                 transmission, dirtFactor, furLength, furThickness,
                 furRoughness, furGravity, furSize, flags);

REFLECTOR_CREATE(CharacterConstants, 1, VARNAMES, detailTilingFactorUV,
                 decalBlendFactors, roughnessModulator, metallicModulator,
                 dielectricReflectance, diffuseRoughness, specularAniso,
                 transmission, emissiveIntensity, dirtFactor, flags);

REFLECTOR_CREATE(EyeGlossConstants, 1, VARNAMES, eyeGlossiness,
                 eyeSpecularIntensity, eyeReflectIntensity, eyeReflectThreshold,
                 eyeGlossShadowIntensity, flags);

REFLECTOR_CREATE(HairConstants, 1, VARNAMES, roughnessModulator,
                 specularMultiplier, scatteringMultiplier, shiftFactor,
                 dielectricReflectance, flags);

REFLECTOR_CREATE(BarkConstants, 1, VARNAMES, roughnessModulator,
                 dielectricReflectance, diffuseRoughness, normalStrength,
                 detailNormalModulator, detailNormalTileU, detailNormalTileV,
                 isGrass, maxWindRotation, distanceAtRotationStart,
                 distanceAtMaxRotation, windSpeedForMaxRotation, leafStiffness,
                 windProperty7, windProperty8, flags);

REFLECTOR_CREATE(FoliageConstants, 1, VARNAMES, diffuseModulator,
                 roughnessModulator, transmissionModulator,
                 dielectricReflectance, sphereNormalStrength, transmission,
                 oneOverSubpixelDetailFadeRange, ssGrass, maxWindRotation,
                 distanceAtRotationStart, distanceAtMaxRotation,
                 windSpeedForMaxRotation, leafStiffness, windProperty7,
                 windProperty8, flags);

REFLECTOR_CREATE(HologramConstants, 1, VARNAMES, emissiveColor,
                 emissiveIntensity, blinkIntensity, scanlineColor,
                 cloudIntensity, cloudTiling, cloudSpeedX, cloudSpeedY,
                 scanline01Tiling, scanline01Speed, scanline01Thickness,
                 scanline01Intensity, scanline01DetailTiling,
                 scanline01DetailIntensity, scanline02Tiling, scanline02Speed,
                 scanline02Thickness, scanline02Intensity, meshlineTiling,
                 meshlineSpeed, meshlineIntensity);

REFLECTOR_CREATE(LandmarkConstants, 1, VARNAMES, specularGloss, reflectivity,
                 emissive, specularFresnel, diffuseModulator, diffuseWrap,
                 backLight, minTimeOfDayEmissive, startFadeOutDistanceEmissive,
                 depthBias);

REFLECTOR_CREATE(EmissiveUIConstants, 1, VARNAMES, primaryColor, secondaryColor,
                 bias, power, intensity, opacity, usePanning, panningSpeed,
                 panningScale);

// GZ
REFLECTOR_CREATE(GeneralR2Constants, 1, VARNAMES, depthBias, detailRepeatU,
                 detailRepeatV, terrainColorFactor, terrainTopProjection,
                 blendMaskContrast1, blendMaskContrast2, flags);

REFLECTOR_CREATE(
    GeneralMkIIIConstants, 1, VARNAMES, normalStrength, reflectivity_1,
    roughness_1, diffuseWrap_1, emissive_1, transmission_1, clearCoat_1,
    roughness_2, diffuseWrap_2, emissive_2, transmission_2, reflectivity_2,
    clearCoat_2, roughness_3, diffuseWrap_3, emissive_3, transmission_3,
    reflectivity_3, clearCoat_3, roughness_4, diffuseWrap_4, emissive_4,
    transmission_4, reflectivity_4, clearCoat_4, layeredHeightMapUVScale,
    layeredUVScale, layeredHeight1Influence, layeredHeight2Influence,
    layeredHeightMapInfluence, layeredMaskInfluence, layeredShift,
    layeredRoughness, layeredDiffuseWrap, layeredEmissive, layeredTransmission,
    layeredReflectivity, layeredClearCoat, decalBlend, decalBlendNormal,
    decalReflectivity, decalRoughness, decalDiffuseWrap, decalEmissive,
    decalTransmission, decalClearCoat, overlayHeightInfluence,
    overlayHeightMapInfluence, overlayMaskInfluence, overlayShift,
    overlayColorR, overlayColorG, overlayColorB, overlayBrightness,
    overlayGloss, overlayMetallic, overlayReflectivity, overlayRoughness,
    overlayDiffuseWrap, overlayEmissive, overlayTransmission, overlayClearCoat,
    damageReflectivity, damageRoughness, damageDiffuseWrap, damageEmissive,
    damageTransmission, damageHeightInfluence, damageMaskInfluence,
    damageClearCoat, depthBias, hardwareDepthBias, hardwareSlopeBias,
    minTimeOfDayEmissive, startFadeOutDistanceEmissiveSq, gIEmissionModulator,
    rippleAngle, rippleSpeed, rippleMagnitude, flags);

REFLECTOR_CREATE(CharacterConstants_GZ, 1, VARNAMES, detailTilingFactorUV,
                 specularGloss, transmissionIntensity, diffuseRoughness,
                 emissiveIntensity, nightVisibility, rimFrontStrength,
                 cameraStrength, cameraSpecular, rimStrength, dirtFactor,
                 flags);

REFLECTOR_CREATE(HairConstants_GZ, 1, VARNAMES, specularGloss,
                 transmissionIntensity, specularFresnel, diffuseWrap,
                 diffuseRoughness, anisotropicStrength, anisotropicX,
                 anisotropicY, rimStrength, ringStrength, ringAngle, ringOffset,
                 flags);

REFLECTOR_CREATE(CharacterSkinConstants_GZ, 1, VARNAMES, detailTilingFactorUV,
                 diffuseRoughness, transmissionModulator, cameraStrength,
                 cameraSpecular, dirtFactor, furLength, furThickness,
                 furRoughness, furGravity, furSize, flags);

REFLECTOR_CREATE(WindowConstants_GZ, 1, VARNAMES, specGloss, specFresnel,
                 diffuseRoughness, tintPower, tintMultiplier, minAlpha, UVScale,
                 chromaticAberration, refractionStrength, flags);

REFLECTOR_CREATE(BarkConstants_GZ, 1, VARNAMES, glossiness, normalStrength,
                 diffuseWrap, fresnel, diffuseModulator,
                 layeredHeightMapUVScale, layeredUVScale,
                 layeredHeight1Influence, layeredHeight2Influence,
                 layeredHeightMapInfluence, layeredMaskInfluence, layeredShift,
                 layeredRoughness, layeredDiffuseWrap, layeredEmissive,
                 layeredTransmission, layeredReflectivity, layeredClearCoat,
                 layeredUpInfluence, overlayHeightInfluence,
                 overlayHeightMapInfluence, overlayMaskInfluence, overlayShift,
                 overlayColor, overlayBrightness, overlayGloss, overlayMetallic,
                 overlayReflectivity, overlayRoughness, overlayDiffuseWrap,
                 overlayEmissive, overlayTransmission, overlayClearCoat,
                 overlayUpInfluence, flags);

REFLECTOR_CREATE(FoliageConstants_GZ, 1, VARNAMES, diffuseModulator,
                 specularGloss, emissionIntensity, transmissionIntensity,
                 diffuseWrap, reflectivity, specularFresnel,
                 sphereNormalStrength, oneOverSubpixelDetailFadeRange, flags);

REFLECTOR_CREATE(CarLightConstants_GZ, 1, VARNAMES, diffuseModulator,
                 detailTiling, specularGloss, reflectivity, emissiveHead,
                 emissiveBlinker, emissiveBrake, emissiveReverse,
                 specularFresnel, doubleSided);
// JC2
REFLECTOR_CREATE(RBMCarPaintSimpleConstants, 1, VARNAMES, twoToneColor1,
                 twoToneColor2, specularPower, depthBias, reflectionMultiplier,
                 flags);
REFLECTOR_CREATE(RBMVegetationFoliageConstants, 1, VARNAMES, specularIntensity,
                 specularPower, translucencyColorMask);
REFLECTOR_CREATE(RBMGeneralConstants, 1, VARNAMES, channelMask, channelAoMask,
                 depthBias, specularPower, flags);
REFLECTOR_CREATE(RBMFacadeConstants, 1, VARNAMES, channelMask, channelDirtMask,
                 emissiveMultiplier, depthBias, specularPower, flags);
REFLECTOR_CREATE(RBMWindowConstants, 1, VARNAMES, specularPower);
REFLECTOR_CREATE(RBMSkinnedGeneralConstants, 1, VARNAMES, flags, technique,
                 specularPower, rimIntensity, rimPower, rimWeights);

// R2
REFLECTOR_CREATE(CharacterSkinConstants_R2, 1, VARNAMES, transmissionModulator,
                 emissiveScale, cameraStrength, cameraSpecular, dirtFactor,
                 furLength, furThickness, furRoughness, furGravity, furSize,
                 gibAlbedoUVScale, gibDetailUVScale, gibSpecGloss,
                 gibSoftDetailEdge, tintColor1, tintColor2, tintColor3,
                 tintColor4, detailUVmult1, detailUVmult2, detailUVmult3,
                 detailUVmult4, blendUVMultiplier1, blendMaskBias1,
                 blendMaskBreakup1, blendMaskContrast1, wrinkleStrength,
                 wrinkleOffsetBrowLeft, wrinkleOffsetBrowMid,
                 wrinkleOffsetBrowRight, wrinkleOffsetUpcheekLeft,
                 wrinkleOffsetNoseLeft, wrinkleOffsetNoseRight,
                 wrinkleOffsetUpcheekRight, wrinkleOffsetJawLeft,
                 wrinkleOffsetMouthbottomLeft, wrinkleOffsetMouthbottomRight,
                 wrinkleOffsetJawRight, wrinkleOffsetNeckStretchLeft,
                 wrinkleOffsetNeckStretchRight, wrinkleOffsetJawDownLeft,
                 wrinkleOffsetJawDownRight, flags);

REFLECTOR_CREATE(GeneralR2Constants_R2, 1, VARNAMES, depthBias, detailRepeatU,
                 detailRepeatV, terrainColorFactor, terrainTopProjection,
                 blendMaskContrast1, blendMaskContrast2, blendUVMultiplier1,
                 blendUVMultiplier2, blendMaskBias1, blendMaskBias2,
                 blendMaskBreakup1, blendMaskBreakup2, emissiveScale,
                 emissiveExposureAdapt, emissiveRollOff, tintColor1, tintColor2,
                 tintColor3, tintColor4, tintBreakup, tintContrast,
                 decalAlphaWeights, dirtUVMultiplier, flags0, useTint, tintUV2,
                 tintOrder, flags1, vertexAnimBBoxMin, vertexAnimBBoxMax,
                 vertexAnimSwizzle, vertexAnimPhase, vertexAnimFrames, flags2,
                 dirtEnabled, dirtColor, dirtAmount, dirtRoughness, dirtBias,
                 dirtBreakup, dirtContrast, debugColor);

REFLECTOR_CREATE(WindowConstants_R2, 1, VARNAMES, baseTransmission,
                 maxRoughness, baseBreakup, baseContrast, specularFresnel,
                 normalMapStrength, damagedRoughness, damagedSpecularFresnel,
                 thickness, damageUVScale, dirtAlbedo, dirtSpecularFresnel,
                 dirtUVScale, dirtBreakup, dirtContrast, dirtMaxTransmission,
                 flags, UVAnimSpeedX, UVAnimSpeedY, useAnim);

REFLECTOR_CREATE(BarkConstants_R2, 1, VARNAMES, flags0, blendUpInfluence1,
                 blendUpNormal1, blendUpContrast1, blendUpShift1,
                 blendMaskBias1, blendMaskBreakup1, blendMaskContrast1,
                 blendUvMultiplier1, overlayHeightInfluence,
                 overlayHeightMapInfluence, overlayMaskInfluence, overlayShift,
                 overlayColor, overlayBrightness, overlayGloss, overlayMetallic,
                 overlayReflectivity, overlayRoughness, overlayDiffuseWrap,
                 overlayEmissive, overlayTransmission, overlayClearCoat,
                 overlayUpInfluence, placedInstanceTerrainTintAmount, flags1);

REFLECTOR_CREATE(HologramConstants_R2, 1, VARNAMES, rasterHorizontalFreq,
                 rasterHorizontalStrength, rasterVerticalFreq,
                 rasterVerticalStrength, distortionHorizontalSpeed,
                 distortionVerticalSpeed, maxSeparation, horizontalDistortion,
                 verticalDistortion, noiseStrength, noiseBandThreshold,
                 brightness, exposureAdaptation, patternHorizontalSpeed,
                 patternVerticalSpeed, type, baseColor, primaryColor,
                 secondaryColor, edgeFade);

REFLECTOR_CREATE(FoliageConstants_R2, 1, VARNAMES, diffuseModulator,
                 specularGloss, emissionIntensity, transmissionIntensity,
                 diffuseWrap, reflectivity, specularFresnel,
                 sphereNormalStrength, oneOverSubpixelDetailFadeRange,
                 placedInstanceTerrainTintAmount, flags);
