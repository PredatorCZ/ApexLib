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

#include "AmfModel.h"
#include "AmfModel_V1.h"
#include "datas/binreader.hpp"
#include "datas/masterprinter.hpp"
#include "ADF.h"

REFLECTOR_START_WNAMES(GeneralConstants, overlayColor, roughnessModulator, metallicModulator, dielectricReflectance, emissiveIntensity, 
	emissiveScale, emissiveExposureAdapt, layeredHeightOffset, layeredContrast, layeredOpacity, layeredBottomHeightInfluence, 
	layeredTopHeightInfluence, layeredMaskInfluence, overlayHeightOffset, overlayContrast, overlayOpacity, overlayBottomHeightInfluence, 
	overlayTopHeightInfluence, overlayMaskInfluence, diffuseRoughness, specularAniso, transmission, clearCoat, detailNormalModulator, 
	detailNormalTileU, detailNormalTileV, depthBias, hardwareDepthBias, hardwareSlopeBias, minTimeOfDayEmissive, 
	startFadeOutDistanceEmissiveSq, gIEmissionModulator, HDRReferenceMultiplier, rippleAngle, rippleSpeed, rippleMagnitude, flags);

REFLECTOR_START_WNAMES(CarLightConstants, diffuseModulator, detailTiling, roughnessModulator, dielectricReflectance, 
	emissiveHead, emissiveBlinker, emissiveBrake, emissiveReverse, doubleSided);

REFLECTOR_START_WNAMES(WindowConstants, roughnessModulator, dielectricReflectance,
	tintPower, minAlpha, UVScale, flags);

REFLECTOR_START_WNAMES(CarPaintStaticConstants, dirtParams, dirtBlend, dirtColor, decalCount, decalWidth, decal1Color, 
	decal2Color, decal3Color, decal4Color, decalBlend, damage, damageBlend, damageColor, roughnessModulator, metallicModulator, 
	dielectricReflectance, emissiveIntensity, diffuseRoughness, specularAniso, transmission, supportDecals, supportDmgBlend, 
	supportRotating, supportScrolling, supportDirt, supportSoftTint, useLayeredBaseColor);

REFLECTOR_START_WNAMES(CarPaintDynamicConstants, tintColorR, tintColorG, tintColorB, tecalIndex);

REFLECTOR_START_WNAMES(CarPaintConstants, staticAttributes.dirtParams, staticAttributes.dirtBlend, staticAttributes.dirtColor, 
	staticAttributes.decalCount, staticAttributes.decalWidth, staticAttributes.decal1Color, staticAttributes.decal2Color, 
	staticAttributes.decal3Color, staticAttributes.decal4Color, staticAttributes.decalBlend, staticAttributes.damage, 
	staticAttributes.damageBlend, staticAttributes.damageColor, staticAttributes.roughnessModulator, staticAttributes.metallicModulator, 
	staticAttributes.dielectricReflectance, staticAttributes.emissiveIntensity, staticAttributes.diffuseRoughness, 
	staticAttributes.specularAniso, staticAttributes.transmission, staticAttributes.supportDecals, staticAttributes.supportDmgBlend, 
	staticAttributes.supportRotating, staticAttributes.supportScrolling, staticAttributes.supportDirt, staticAttributes.supportSoftTint, 
	staticAttributes.useLayeredBaseColor, dynamicAttributes.tintColorR, dynamicAttributes.tintColorG, dynamicAttributes.tintColorB, 
	dynamicAttributes.tecalIndex, gIEmissionModulator, flags0, flags1, flags2);

REFLECTOR_START_WNAMES(CharacterSkinConstants, detailTilingFactorUV, roughnessModulator, transmissionModulator, 
	diffuseRoughness, transmission, dirtFactor, furLength, furThickness, furRoughness, furGravity, furSize, flags);

REFLECTOR_START_WNAMES(CharacterConstants, detailTilingFactorUV, decalBlendFactors, roughnessModulator, metallicModulator, 
	dielectricReflectance, diffuseRoughness, specularAniso, transmission, emissiveIntensity, dirtFactor, flags);

REFLECTOR_START_WNAMES(EyeGlossConstants, eyeGlossiness, eyeSpecularIntensity, eyeReflectIntensity, eyeReflectThreshold, 
	eyeGlossShadowIntensity, flags);

REFLECTOR_START_WNAMES(HairConstants, roughnessModulator, specularMultiplier, scatteringMultiplier, shiftFactor, dielectricReflectance, 
	flags);

REFLECTOR_START_WNAMES(BarkConstants, roughnessModulator, dielectricReflectance, diffuseRoughness, normalStrength, 
	detailNormalModulator, detailNormalTileU, detailNormalTileV, isGrass, maxWindRotation, distanceAtRotationStart, 
	distanceAtMaxRotation, windSpeedForMaxRotation, leafStiffness, windProperty7, windProperty8, flags);

REFLECTOR_START_WNAMES(FoliageConstants, diffuseModulator, roughnessModulator, transmissionModulator, dielectricReflectance,
	sphereNormalStrength, transmission, oneOverSubpixelDetailFadeRange, ssGrass, maxWindRotation, distanceAtRotationStart,
	distanceAtMaxRotation, windSpeedForMaxRotation, leafStiffness, windProperty7, windProperty8, flags);

REFLECTOR_START_WNAMES(HologramConstants, emissiveColor, emissiveIntensity, blinkIntensity, scanlineColor, cloudIntensity,
	cloudTiling, cloudSpeedX, cloudSpeedY, scanline01Tiling, scanline01Speed, scanline01Thickness, scanline01Intensity,
	scanline01DetailTiling, scanline01DetailIntensity, scanline02Tiling, scanline02Speed, scanline02Thickness, scanline02Intensity,
	meshlineTiling, meshlineSpeed, meshlineIntensity);

REFLECTOR_START_WNAMES(LandmarkConstants, specularGloss, reflectivity, emissive, specularFresnel, diffuseModulator,
	diffuseWrap, backLight, minTimeOfDayEmissive, startFadeOutDistanceEmissive, depthBias);

REFLECTOR_START_WNAMES(EmissiveUIConstants, primaryColor, secondaryColor, bias, power, intensity,
	opacity, usePanning, panningSpeed, panningScale);

REFLECTOR_START_WNAMES(GeneralR2Constants, depthBias, detailRepeatU, detailRepeatV, terrainColorFactor,
	terrainTopProjection, blendMaskContrast1, blendMaskContrast2, flags);

REFLECTOR_START_WNAMES(GeneralMkIIIConstants, normalStrength, reflectivity_1, roughness_1, diffuseWrap_1, emissive_1, transmission_1, 
	clearCoat_1, roughness_2, diffuseWrap_2, emissive_2, transmission_2, reflectivity_2, clearCoat_2, roughness_3, diffuseWrap_3, 
	emissive_3, transmission_3, reflectivity_3, clearCoat_3, roughness_4, diffuseWrap_4, emissive_4, transmission_4, reflectivity_4, 
	clearCoat_4, layeredHeightMapUVScale, layeredUVScale, layeredHeight1Influence, layeredHeight2Influence, layeredHeightMapInfluence, 
	layeredMaskInfluence, layeredShift, layeredRoughness, layeredDiffuseWrap, layeredEmissive, layeredTransmission, layeredReflectivity, 
	layeredClearCoat, decalBlend, decalBlendNormal, decalReflectivity, decalRoughness, decalDiffuseWrap, decalEmissive, 
	decalTransmission, decalClearCoat, overlayHeightInfluence, overlayHeightMapInfluence, overlayMaskInfluence, overlayShift, 
	overlayColorR, overlayColorG, overlayColorB, overlayBrightness, overlayGloss, overlayMetallic, overlayReflectivity, 
	overlayRoughness, overlayDiffuseWrap, overlayEmissive, overlayTransmission, overlayClearCoat, damageReflectivity, damageRoughness, 
	damageDiffuseWrap, damageEmissive, damageTransmission, damageHeightInfluence, damageMaskInfluence, damageClearCoat, depthBias, 
	hardwareDepthBias, hardwareSlopeBias, minTimeOfDayEmissive, startFadeOutDistanceEmissiveSq, gIEmissionModulator, rippleAngle, 
	rippleSpeed, rippleMagnitude, flags);

REFLECTOR_START_WNAMES(CharacterConstants_GZ, detailTilingFactorUV, specularGloss, transmissionIntensity, diffuseRoughness,
	emissiveIntensity, nightVisibility, rimFrontStrength, cameraStrength, cameraSpecular, rimStrength, dirtFactor, flags);

REFLECTOR_START_WNAMES(HairConstants_GZ, specularGloss, transmissionIntensity, specularFresnel, diffuseWrap, diffuseRoughness,
	anisotropicStrength, anisotropicX, anisotropicY, rimStrength, ringStrength, ringAngle, ringOffset, flags);

REFLECTOR_START_WNAMES(CharacterSkinConstants_GZ, detailTilingFactorUV, diffuseRoughness, transmissionModulator, cameraStrength,
	cameraSpecular, dirtFactor, furLength, furThickness, furRoughness, furGravity, furSize, flags);

REFLECTOR_START_WNAMES(WindowConstants_GZ, specGloss, specFresnel, diffuseRoughness, tintPower, tintMultiplier, minAlpha,
	UVScale, chromaticAberration, refractionStrength, flags);

REFLECTOR_START_WNAMES(BarkConstants_GZ, glossiness, normalStrength, diffuseWrap, fresnel, diffuseModulator, layeredHeightMapUVScale,
	layeredUVScale, layeredHeight1Influence, layeredHeight2Influence, layeredHeightMapInfluence, layeredMaskInfluence, layeredShift,
	layeredRoughness, layeredDiffuseWrap, layeredEmissive, layeredTransmission, layeredReflectivity, layeredClearCoat, 
	layeredUpInfluence, overlayHeightInfluence, overlayHeightMapInfluence, overlayMaskInfluence, overlayShift, overlayColor, 
	overlayBrightness, overlayGloss, overlayMetallic, overlayReflectivity, overlayRoughness, overlayDiffuseWrap, overlayEmissive, 
	overlayTransmission, overlayClearCoat, overlayUpInfluence, flags);

REFLECTOR_START_WNAMES(FoliageConstants_GZ, diffuseModulator, specularGloss, emissionIntensity, transmissionIntensity, diffuseWrap,
	reflectivity, specularFresnel, sphereNormalStrength, oneOverSubpixelDetailFadeRange, flags);

REFLECTOR_START_WNAMES(CarLightConstants_GZ, diffuseModulator, detailTiling, specularGloss, reflectivity, emissiveHead,
	emissiveBlinker, emissiveBrake, emissiveReverse, specularFresnel, doubleSided);

REFLECTOR_START_WNAMES(CharacterSkinConstants_R2, transmissionModulator, emissiveScale, cameraStrength, cameraSpecular, dirtFactor,
	furLength, furThickness, furRoughness, furGravity, furSize, gibAlbedoUVScale, gibDetailUVScale, gibSpecGloss, gibSoftDetailEdge,
	tintColor1, tintColor2, tintColor3, tintColor4, detailUVmult1, detailUVmult2, detailUVmult3, detailUVmult4, blendUVMultiplier1,
	blendMaskBias1, blendMaskBreakup1, blendMaskContrast1, wrinkleStrength, wrinkleOffsetBrowLeft, wrinkleOffsetBrowMid,
	wrinkleOffsetBrowRight, wrinkleOffsetUpcheekLeft, wrinkleOffsetNoseLeft, wrinkleOffsetNoseRight, wrinkleOffsetUpcheekRight,
	wrinkleOffsetJawLeft, wrinkleOffsetMouthbottomLeft, wrinkleOffsetMouthbottomRight, wrinkleOffsetJawRight, wrinkleOffsetNeckStretchLeft,
	wrinkleOffsetNeckStretchRight, wrinkleOffsetJawDownLeft, wrinkleOffsetJawDownRight, flags);

REFLECTOR_START_WNAMES(GeneralR2Constants_R2, depthBias, detailRepeatU, detailRepeatV, terrainColorFactor, terrainTopProjection,
	blendMaskContrast1, blendMaskContrast2, blendUVMultiplier1, blendUVMultiplier2, blendMaskBias1, blendMaskBias2,
	blendMaskBreakup1, blendMaskBreakup2, emissiveScale, emissiveExposureAdapt, emissiveRollOff, tintColor1,
	tintColor2, tintColor3, tintColor4, tintBreakup, tintContrast, decalAlphaWeights, dirtUVMultiplier, flags0,
	useTint, tintUV2, tintOrder, flags1, vertexAnimBBoxMin, vertexAnimBBoxMax, vertexAnimSwizzle, vertexAnimPhase, vertexAnimFrames,
	flags2, dirtEnabled, dirtColor, dirtAmount, dirtRoughness, dirtBias, dirtBreakup, dirtContrast, debugColor);

REFLECTOR_START_WNAMES(WindowConstants_R2, baseTransmission, maxRoughness, baseBreakup, baseContrast, specularFresnel,
	normalMapStrength, damagedRoughness, damagedSpecularFresnel, thickness, damageUVScale, dirtAlbedo, dirtSpecularFresnel,
	dirtUVScale, dirtBreakup, dirtContrast, dirtMaxTransmission, flags, UVAnimSpeedX, UVAnimSpeedY, useAnim);


REFLECTOR_START_WNAMES(BarkConstants_R2, flags0, blendUpInfluence1, blendUpNormal1, blendUpContrast1, blendUpShift1,
	blendMaskBias1, blendMaskBreakup1, blendMaskContrast1, blendUvMultiplier1, overlayHeightInfluence,
	overlayHeightMapInfluence, overlayMaskInfluence, overlayShift, overlayColor, overlayBrightness, overlayGloss,
	overlayMetallic, overlayReflectivity, overlayRoughness, overlayDiffuseWrap, overlayEmissive, overlayTransmission,
	overlayClearCoat, overlayUpInfluence, placedInstanceTerrainTintAmount, flags1);

REFLECTOR_START_WNAMES(HologramConstants_R2, rasterHorizontalFreq, rasterHorizontalStrength, rasterVerticalFreq,
	rasterVerticalStrength, distortionHorizontalSpeed, distortionVerticalSpeed, maxSeparation, horizontalDistortion,
	verticalDistortion, noiseStrength, noiseBandThreshold, brightness, exposureAdaptation, patternHorizontalSpeed,
	patternVerticalSpeed, type, baseColor, primaryColor, secondaryColor, edgeFade);

REFLECTOR_START_WNAMES(FoliageConstants_R2, diffuseModulator, specularGloss, emissionIntensity, transmissionIntensity,
	diffuseWrap, reflectivity, specularFresnel, sphereNormalStrength, oneOverSubpixelDetailFadeRange,
	placedInstanceTerrainTintAmount, flags);

class AmfMaterial_V1_wrap : public AmfMaterial
{
	AmfMaterial_V1 *data;
	ADF *main;
public:
	AmfMaterial_V1_wrap(AmfMaterial_V1 *_data, ADF *_main) :
		data(_data), main(_main) {}

	AmfMaterialType GetMaterialType() const { return data->MaterialType(); }
	AmfMaterialType &MaterialType() { return data->MaterialType(); }
	const char *GetName() const { return main->FindString(data->name)->c_str(); }
	const char *GetRenderBlockName() const { return main->FindString(data->renderBlockID)->c_str(); }
	ApexHash GetNameHash() const { return data->name; }
	ApexHash GetRenderBlockNameHash() const { return data->renderBlockID; }
	ReflectorPtr GetReflectedAttributes() const { return ReflectorPtr(data->Attributes().GetReflected()); }
	void *GetRawAttributes() const { return data->Attributes().item.vPtr; }
	ApexHash GetAttributesHash() const { return data->Attributes().objectHash; }
	int GetNumTextures() const { return data->textures.count; }
	const char *GetTexture(int id) const { return main->FindString(data->textures[id])->c_str(); }
};

void AmfModel_V1_wrap::Fixup(char *masterBuffer) { data->Fixup(masterBuffer); }

const char *AmfModel_V1_wrap::RequestsFile() const
{ return main->FindString(data->meshPath)->c_str(); }

int AmfModel_V1_wrap::GetNumMaterials() const { return data->materials.count; }

AmfMaterial::Ptr AmfModel_V1_wrap::GetMaterial(int id) const
{ return AmfMaterial::Ptr(new AmfMaterial_V1_wrap(&data->materials[id], main)); }

AmfModel_V1_wrap::AmfModel_V1_wrap(void *_data, ADF *_main)
: data(static_cast<AmfModel_V1*>(_data)), main(_main) {}