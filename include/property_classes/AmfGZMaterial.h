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

struct GeneralR2Constants
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0x8BB29AA0;
	float depthBias,
		detailRepeatU,
		detailRepeatV,
		terrainColorFactor,
		terrainTopProjection,
		blendMaskContrast1,
		blendMaskContrast2;
	esFlags<uint, GeneralR2ConstantsFlags> flags;
};

static_assert(sizeof(GeneralR2Constants) == 32, "Check assumptions");

struct GeneralMkIIIConstants
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0xD01A8371;
	float normalStrength,
		reflectivity_1,
		roughness_1,
		diffuseWrap_1,
		emissive_1,
		transmission_1,
		clearCoat_1,
		roughness_2,
		diffuseWrap_2,
		emissive_2,
		transmission_2,
		reflectivity_2,
		clearCoat_2,
		roughness_3,
		diffuseWrap_3,
		emissive_3,
		transmission_3,
		reflectivity_3,
		clearCoat_3,
		roughness_4,
		diffuseWrap_4,
		emissive_4,
		transmission_4,
		reflectivity_4,
		clearCoat_4,
		layeredHeightMapUVScale,
		layeredUVScale,
		layeredHeight1Influence,
		layeredHeight2Influence,
		layeredHeightMapInfluence,
		layeredMaskInfluence,
		layeredShift,
		layeredRoughness,
		layeredDiffuseWrap,
		layeredEmissive,
		layeredTransmission,
		layeredReflectivity,
		layeredClearCoat,
		decalBlend,
		decalBlendNormal,
		decalReflectivity,
		decalRoughness,
		decalDiffuseWrap,
		decalEmissive,
		decalTransmission,
		decalClearCoat,
		overlayHeightInfluence,
		overlayHeightMapInfluence,
		overlayMaskInfluence,
		overlayShift,
		overlayColorR,
		overlayColorG,
		overlayColorB,
		overlayBrightness,
		overlayGloss,
		overlayMetallic,
		overlayReflectivity,
		overlayRoughness,
		overlayDiffuseWrap,
		overlayEmissive,
		overlayTransmission,
		overlayClearCoat,
		damageReflectivity,
		damageRoughness,
		damageDiffuseWrap,
		damageEmissive,
		damageTransmission,
		damageHeightInfluence,
		damageMaskInfluence,
		damageClearCoat,
		depthBias,
		hardwareDepthBias,
		hardwareSlopeBias,
		minTimeOfDayEmissive,
		startFadeOutDistanceEmissiveSq,
		gIEmissionModulator,
		rippleAngle,
		rippleSpeed,
		rippleMagnitude;
	esFlags<uint, GeneralMkIIIConstantsFlags> flags;
};

static_assert(sizeof(GeneralMkIIIConstants) == 320, "Check assumptions");

struct CharacterConstants_GZ
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0xCE6A3748;
	Vector2 detailTilingFactorUV;
	float specularGloss,
		transmissionIntensity,
		diffuseRoughness,
		emissiveIntensity,
		nightVisibility,
		rimFrontStrength,
		cameraStrength,
		cameraSpecular,
		rimStrength,
		dirtFactor;
	esFlags<int, CharacterConstantsFlags_GZ> flags;
};

static_assert(sizeof(CharacterConstants_GZ) == 52, "Check assumptions");

struct HairConstants_GZ
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0x55204F03;
	float specularGloss,
		transmissionIntensity,
		specularFresnel,
		diffuseWrap,
		diffuseRoughness,
		anisotropicStrength,
		anisotropicX,
		anisotropicY,
		rimStrength,
		ringStrength,
		ringAngle,
		ringOffset;
	esFlags<short, HairConstantsFlags_GZ> flags;
};

static_assert(sizeof(HairConstants_GZ) == 52, "Check assumptions");

struct CharacterSkinConstants_GZ
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0xA5A7B4D5;
	Vector2 detailTilingFactorUV;
	float diffuseRoughness,
		transmissionModulator,
		cameraStrength,
		cameraSpecular,
		dirtFactor,
		furLength,
		furThickness,
		furRoughness,
		furGravity,
		furSize;
	esFlags<short, CharacterSkinConstantsFlags_GZ> flags;
};

static_assert(sizeof(CharacterSkinConstants_GZ) == 52, "Check assumptions");

struct WindowConstants_GZ
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0x943EA98D;
	float specGloss,
		specFresnel,
		diffuseRoughness,
		tintPower,
		tintMultiplier,
		minAlpha,
		UVScale,
		chromaticAberration,
		refractionStrength;
	esFlags<short, WindowConstantsFlags_GZ> flags;
};

static_assert(sizeof(WindowConstants_GZ) == 40, "Check assumptions");

struct BarkConstants_GZ
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0xF5BBB286;
	float glossiness,
		normalStrength,
		diffuseWrap,
		fresnel;
	Vector4 diffuseModulator;
	float layeredHeightMapUVScale,
		layeredUVScale,
		layeredHeight1Influence,
		layeredHeight2Influence,
		layeredHeightMapInfluence,
		layeredMaskInfluence,
		layeredShift,
		layeredRoughness,
		layeredDiffuseWrap,
		layeredEmissive,
		layeredTransmission,
		layeredReflectivity,
		layeredClearCoat,
		layeredUpInfluence,
		overlayHeightInfluence,
		overlayHeightMapInfluence,
		overlayMaskInfluence,
		overlayShift;
	Vector overlayColor;
	float overlayBrightness,
		overlayGloss,
		overlayMetallic,
		overlayReflectivity,
		overlayRoughness,
		overlayDiffuseWrap,
		overlayEmissive,
		overlayTransmission,
		overlayClearCoat,
		overlayUpInfluence;
	esFlags<short, BarkConstantsFlags_GZ> flags;
};

static_assert(sizeof(BarkConstants_GZ) == 160, "Check assumptions");

struct FoliageConstants_GZ
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0xD32674C9;
	Vector4 diffuseModulator;
	float specularGloss,
		emissionIntensity,
		transmissionIntensity,
		diffuseWrap,
		reflectivity,
		specularFresnel,
		sphereNormalStrength,
		oneOverSubpixelDetailFadeRange;
	esFlags<short, FoliageConstantsFlags> flags;
};

static_assert(sizeof(FoliageConstants_GZ) == 52, "Check assumptions");

struct CarLightConstants_GZ
{
	DECLARE_REFLECTOR;
	static const ApexHash HASH = 0xFB2F8330;
	Vector4 diffuseModulator;
	Vector2 detailTiling;
	float specularGloss,
		reflectivity,
		emissiveHead,
		emissiveBlinker,
		emissiveBrake,
		emissiveReverse,
		specularFresnel;
	bool doubleSided;
};

static_assert(sizeof(CarLightConstants_GZ) == 56, "Check assumptions");
