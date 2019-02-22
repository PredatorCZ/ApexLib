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
#include "datas/binreader.hpp"
#include "ADF.h"
#include "AdfRegistry.h"

REFLECTOR_START_WNAMES(GeneralConstants, overlayColor, roughnessModulator, metallicModulator, dielectricReflectance, emissiveIntensity, 
	emissiveScale, emissiveExposureAdapt, layeredHeightOffset, layeredContrast, layeredOpacity, layeredBottomHeightInfluence, layeredTopHeightInfluence, 
	layeredMaskInfluence, overlayHeightOffset, overlayContrast, overlayOpacity, overlayBottomHeightInfluence, overlayTopHeightInfluence, overlayMaskInfluence, 
	diffuseRoughness, specularAniso, transmission, clearCoat, detailNormalModulator, detailNormalTileU, detailNormalTileV, depthBias, hardwareDepthBias, hardwareSlopeBias, 
	minTimeOfDayEmissive, startFadeOutDistanceEmissiveSq, gIEmissionModulator, HDRReferenceMultiplier, rippleAngle, rippleSpeed, rippleMagnitude, flags);

REFLECTOR_START_WNAMES(CarLightConstants, diffuseModulator, detailTiling, roughnessModulator, dielectricReflectance, 
	emissiveHead, emissiveBlinker, emissiveBrake, emissiveReverse, doubleSided);

REFLECTOR_START_WNAMES(WindowConstants, roughnessModulator, dielectricReflectance,
	tintPower, minAlpha, UVScale, flags);

REFLECTOR_START_WNAMES(CarPaintStaticConstants, dirtParams, dirtBlend, dirtColor, decalCount, decalWidth, decal1Color, 
	decal2Color, decal3Color, decal4Color, decalBlend, damage, damageBlend, damageColor, roughnessModulator, metallicModulator, 
	dielectricReflectance, emissiveIntensity, diffuseRoughness, specularAniso, transmission, supportDecals, supportDmgBlend, 
	supportRotating, supportScrolling, supportDirt, supportSoftTint, useLayeredBaseColor);

REFLECTOR_START_WNAMES(CarPaintDynamicConstants, tintColorR, tintColorG, tintColorB, tecalIndex);

REFLECTOR_START_WNAMES(CarPaintConstants, staticAttributes.dirtParams, staticAttributes.dirtBlend, staticAttributes.dirtColor, staticAttributes.decalCount, 
	staticAttributes.decalWidth, staticAttributes.decal1Color, staticAttributes.decal2Color, staticAttributes.decal3Color, staticAttributes.decal4Color, 
	staticAttributes.decalBlend, staticAttributes.damage, staticAttributes.damageBlend, staticAttributes.damageColor, staticAttributes.roughnessModulator, 
	staticAttributes.metallicModulator, staticAttributes.dielectricReflectance, staticAttributes.emissiveIntensity, staticAttributes.diffuseRoughness, 
	staticAttributes.specularAniso, staticAttributes.transmission, staticAttributes.supportDecals, staticAttributes.supportDmgBlend, staticAttributes.supportRotating, 
	staticAttributes.supportScrolling, staticAttributes.supportDirt, staticAttributes.supportSoftTint, staticAttributes.useLayeredBaseColor, dynamicAttributes.tintColorR, 
	dynamicAttributes.tintColorG, dynamicAttributes.tintColorB, dynamicAttributes.tecalIndex, gIEmissionModulator, flags0, flags1, flags2);

REFLECTOR_START_WNAMES(CharacterSkinConstants, detailTilingFactorUV, roughnessModulator, transmissionModulator, 
	diffuseRoughness, transmission, dirtFactor, furLength, furThickness, furRoughness, furGravity, furSize, flags);

REFLECTOR_START_WNAMES(CharacterConstants, detailTilingFactorUV, decalBlendFactors, roughnessModulator, metallicModulator, 
	dielectricReflectance, diffuseRoughness, specularAniso, transmission, emissiveIntensity, dirtFactor, flags);

REFLECTOR_START_WNAMES(EyeGlossConstants, eyeGlossiness, eyeSpecularIntensity, eyeReflectIntensity, eyeReflectThreshold, 
	eyeGlossShadowIntensity, flags);

REFLECTOR_START_WNAMES(HairConstants, roughnessModulator, specularMultiplier, scatteringMultiplier, shiftFactor, dielectricReflectance, flags);

REFLECTOR_START_WNAMES(BarkConstants, roughnessModulator, dielectricReflectance, diffuseRoughness, normalStrength, detailNormalModulator,
	detailNormalTileU, detailNormalTileV, isGrass, maxWindRotation, distanceAtRotationStart, distanceAtMaxRotation, windSpeedForMaxRotation,
	leafStiffness, windProperty7, windProperty8, flags);

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

AmfMaterial * AmfModel::FindMaterial(StringHash * str)
{
	for (auto &m : materials)
		if (m->name == str)
			return m;

	return nullptr;
}

int AmfModel::Load(BinReader * rd, ADF * linker)
{
	rd->Read(Header);
	meshPath = linker->FindStringHash(Header.meshPath);

	rd->Seek(Header.lodSlots.offset);
	
	rd->ReadContainer(lodSlots, Header.lodSlots.count);

	rd->Seek(Header.materials.offset);
	materials.resize(Header.materials.count);

	for (auto &l : materials)
	{
		l = new AmfMaterial();
		l->Load(rd, linker);
	}

	return 0;
}

void AmfModel::Link(ADF * linker)
{
	for (auto &m : materials)
		if (m->attributes)
			m->attributes->Link(linker);
}

AmfModel::~AmfModel()
{
	for (auto &m : materials)
		delete m;
}

int AmfMaterial::Load(BinReader * rd, ADF * linker)
{
	rd->Read(Header);
	rd->SavePos();
	name = linker->FindStringHash(Header.name);
	renderBlockID = linker->FindStringHash(Header.renderBlockID);

	rd->Seek(Header.attributes.offset);

	if (ADFPropsStorage.count(static_cast<ApexHash>(Header.attributes.objectHash)))
	{
		attributes = ADFPropsStorage[static_cast<ApexHash>(Header.attributes.objectHash)]();
		attributes->Load(rd);
	}

	rd->Seek(Header.textures.offset);
	textures.resize(Header.textures.count);

	for (auto &l : textures)
	{
		ApexHash hash;
		rd->Read(hash);
		l = linker->FindStringHash(hash);
	}

	rd->RestorePos();

	return 0;
}

AmfMaterial::~AmfMaterial()
{
	if (attributes)
		delete attributes;
}
