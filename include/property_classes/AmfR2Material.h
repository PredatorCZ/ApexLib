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

struct CharacterSkinConstants_R2
{
	DECLARE_REFLECTOR;
	float transmissionModulator,
		emissiveScale,
		cameraStrength,
		cameraSpecular,
		dirtFactor,
		furLength,
		furThickness,
		furRoughness,
		furGravity,
		furSize,
		gibAlbedoUVScale,
		gibDetailUVScale,
		gibSpecGloss,
		gibSoftDetailEdge;
	Vector tintColor1,
		tintColor2,
		tintColor3,
		tintColor4;
	float detailUVmult1,
		detailUVmult2,
		detailUVmult3,
		detailUVmult4,
		blendUVMultiplier1,
		blendMaskBias1,
		blendMaskBreakup1,
		blendMaskContrast1,
		wrinkleStrength,
		wrinkleOffsetBrowLeft,
		wrinkleOffsetBrowMid,
		wrinkleOffsetBrowRight,
		wrinkleOffsetUpcheekLeft,
		wrinkleOffsetNoseLeft,
		wrinkleOffsetNoseRight,
		wrinkleOffsetUpcheekRight,
		wrinkleOffsetJawLeft,
		wrinkleOffsetMouthbottomLeft,
		wrinkleOffsetMouthbottomRight,
		wrinkleOffsetJawRight,
		wrinkleOffsetNeckStretchLeft,
		wrinkleOffsetNeckStretchRight,
		wrinkleOffsetJawDownLeft,
		wrinkleOffsetJawDownRight;
	esFlags<short, CharacterSkinConstantsFlags_R2> flags;

	static const ApexHash HASH = 0x3C710AD8;
};

static_assert(sizeof(CharacterSkinConstants_R2) == 204, "Check assumptions");

struct GeneralR2Constants_R2
{
	DECLARE_REFLECTOR;
	float depthBias,
		detailRepeatU,
		detailRepeatV,
		terrainColorFactor,
		terrainTopProjection,
		blendMaskContrast1,
		blendMaskContrast2,
		blendUVMultiplier1,
		blendUVMultiplier2,
		blendMaskBias1,
		blendMaskBias2,
		blendMaskBreakup1,
		blendMaskBreakup2,
		emissiveScale,
		emissiveExposureAdapt,
		emissiveRollOff;
	Vector tintColor1,
		tintColor2,
		tintColor3,
		tintColor4;
	float tintBreakup,
		tintContrast;
	Vector decalAlphaWeights;
	float dirtUVMultiplier;
	esFlags<int, GeneralR2Constants_R2_flags0> flags0;
	float useTint;
	bool tintUV2;
	float tintOrder;
	esFlags<int, GeneralR2Constants_R2_flags1> flags1;
	float vertexAnimBBoxMin,
		vertexAnimBBoxMax;
	bool vertexAnimSwizzle;
	float vertexAnimPhase;
	uint vertexAnimFrames;
	esFlags<int, GeneralR2Constants_R2_flags2> flags2;
	float dirtEnabled;
	Vector dirtColor;
	float dirtAmount,
		dirtRoughness,
		dirtBias,
		dirtBreakup,
		dirtContrast;
	Vector debugColor;

	static const ApexHash HASH = 0x5449DC72;
};

static_assert(sizeof(GeneralR2Constants_R2) == 228, "Check assumptions");

struct HairConstants_R2 : HairConstants_GZ 
{
	static const ApexHash HASH = 0xD5C4F848;
};

struct WindowConstants_R2
{
	DECLARE_REFLECTOR;
	Vector baseTransmission;
	float maxRoughness,
		baseBreakup,
		baseContrast,
		specularFresnel,
		normalMapStrength,
		damagedRoughness,
		damagedSpecularFresnel,
		thickness,
		damageUVScale;
	Vector dirtAlbedo;
	float dirtSpecularFresnel,
		dirtUVScale,
		dirtBreakup,
		dirtContrast,
		dirtMaxTransmission;
	esFlags<char, WindowConstantsFlags_R2> flags;
	float UVAnimSpeedX,
		UVAnimSpeedY;
	bool useAnim;

	static const ApexHash HASH = 0xD275AA25;
};

static_assert(sizeof(WindowConstants_R2) == 96, "Check assumptions");

struct BarkConstants_R2
{
	DECLARE_REFLECTOR;
	esFlags<char, BarkConstantsFlags0_R2> flags0;
	float blendUpInfluence1,
		blendUpNormal1,
		blendUpContrast1,
		blendUpShift1,
		blendMaskBias1,
		blendMaskBreakup1,
		blendMaskContrast1,
		blendUvMultiplier1,
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
		overlayUpInfluence,
		placedInstanceTerrainTintAmount;
	esFlags<char, BarkConstantsFlags1_R2> flags1;

	static const ApexHash HASH = 0x7DAEE004;
};

static_assert(sizeof(BarkConstants_R2) == 112, "Check assumptions");

struct HologramConstants_R2
{
	DECLARE_REFLECTOR;
	float rasterHorizontalFreq,
		rasterHorizontalStrength,
		rasterVerticalFreq,
		rasterVerticalStrength,
		distortionHorizontalSpeed,
		distortionVerticalSpeed,
		maxSeparation,
		horizontalDistortion,
		verticalDistortion,
		noiseStrength,
		noiseBandThreshold,
		brightness,
		exposureAdaptation,
		patternHorizontalSpeed,
		patternVerticalSpeed,
		type;
	Vector baseColor,
		primaryColor,
		secondaryColor;
	Vector4 edgeFade;

	static const ApexHash HASH = 0xE0DE5D23;
};

static_assert(sizeof(HologramConstants_R2) == 116, "Check assumptions");

struct FoliageConstants_R2
{
	DECLARE_REFLECTOR;
	Vector4 diffuseModulator;
	float specularGloss,
		emissionIntensity,
		transmissionIntensity,
		diffuseWrap,
		reflectivity,
		specularFresnel,
		sphereNormalStrength,
		oneOverSubpixelDetailFadeRange,
		placedInstanceTerrainTintAmount;
	esFlags<char, FoliageConstantsFlags_R2> flags;

	static const ApexHash HASH = 0x65CCA378;
};

static_assert(sizeof(FoliageConstants_R2) == 56, "Check assumptions");