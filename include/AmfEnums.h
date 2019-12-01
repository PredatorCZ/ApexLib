/*      Apex Engine Format Library
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

#pragma once
#include "datas/reflector.hpp"

REFLECTOR_CREATE(AmfUsage, ENUM, 0, AmfUsage_Unspecified, AmfUsage_Position,
                 AmfUsage_TextureCoordinate, AmfUsage_Normal, AmfUsage_Tangent,
                 AmfUsage_BiTangent, AmfUsage_TangentSpace, AmfUsage_BoneIndex,
                 AmfUsage_BoneWeight, AmfUsage_Color, AmfUsage_WireRadius,
                 AmfUsage_DeformNormal_c, AmfUsage_DeformPoints_c);

static constexpr int AmfFormatStrides[] = {
    16, 16, 16, 12, 12, 12, 8, 8, 8, 8, 8, 6, 6, 6, 6, 6, 8, 8,
    8,  4,  4,  4,  4,  4,  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
    2,  2,  2,  2,  2,  2,  2, 2, 1, 1, 1, 1, 4, 4, 4, 4, 4};

REFLECTOR_CREATE(AmfFormat, ENUM, 0, AmfFormat_R32G32B32A32_FLOAT,
                 AmfFormat_R32G32B32A32_UINT, AmfFormat_R32G32B32A32_SINT,
                 AmfFormat_R32G32B32_FLOAT, AmfFormat_R32G32B32_UINT,
                 AmfFormat_R32G32B32_SINT, AmfFormat_R16G16B16A16_FLOAT,
                 AmfFormat_R16G16B16A16_UNORM, AmfFormat_R16G16B16A16_UINT,
                 AmfFormat_R16G16B16A16_SNORM, AmfFormat_R16G16B16A16_SINT,
                 AmfFormat_R16G16B16_FLOAT, AmfFormat_R16G16B16_UNORM,
                 AmfFormat_R16G16B16_UINT, AmfFormat_R16G16B16_SNORM,
                 AmfFormat_R16G16B16_SINT, AmfFormat_R32G32_FLOAT,
                 AmfFormat_R32G32_UINT, AmfFormat_R32G32_SINT,
                 AmfFormat_R10G10B10A2_UNORM, AmfFormat_R10G10B10A2_UINT,
                 AmfFormat_R11G11B10_FLOAT, AmfFormat_R8G8B8A8_UNORM,
                 AmfFormat_R8G8B8A8_UNORM_SRGB, AmfFormat_R8G8B8A8_UINT,
                 AmfFormat_R8G8B8A8_SNORM, AmfFormat_R8G8B8A8_SINT,
                 AmfFormat_R16G16_FLOAT, AmfFormat_R16G16_UNORM,
                 AmfFormat_R16G16_UINT, AmfFormat_R16G16_SNORM,
                 AmfFormat_R16G16_SINT, AmfFormat_R32_FLOAT, AmfFormat_R32_UINT,
                 AmfFormat_R32_SINT, AmfFormat_R8G8_UNORM, AmfFormat_R8G8_UINT,
                 AmfFormat_R8G8_SNORM, AmfFormat_R8G8_SINT, AmfFormat_R16_FLOAT,
                 AmfFormat_R16_UNORM, AmfFormat_R16_UINT, AmfFormat_R16_SNORM,
                 AmfFormat_R16_SINT, AmfFormat_R8_UNORM, AmfFormat_R8_UINT,
                 AmfFormat_R8_SNORM, AmfFormat_R8_SINT,
                 AmfFormat_R32_UNIT_VEC_AS_FLOAT,
                 AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT,
                 AmfFormat_R8G8B8A8_TANGENT_SPACE,
                 AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c,
                 AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c);

static_assert(AmfFormatStrides[AmfFormat_R32G32B32A32_SINT] == 16,
              "AmfFormatStrides AmfFormat_R32G32B32A32_FLOAT");
static_assert(AmfFormatStrides[AmfFormat_R32G32B32_FLOAT] == 12,
              "AmfFormatStrides AmfFormat_R32G32B32_FLOAT");
static_assert(AmfFormatStrides[AmfFormat_R32G32B32_SINT] == 12,
              "AmfFormatStrides AmfFormat_R32G32B32_SINT");
static_assert(AmfFormatStrides[AmfFormat_R16G16B16A16_FLOAT] == 8,
              "AmfFormatStrides AmfFormat_R16G16B16A16_FLOAT");
static_assert(AmfFormatStrides[AmfFormat_R16G16B16A16_SINT] == 8,
              "AmfFormatStrides AmfFormat_R16G16B16A16_SINT");
static_assert(AmfFormatStrides[AmfFormat_R16G16B16_FLOAT] == 6,
              "AmfFormatStrides AmfFormat_R16G16B16_FLOAT");
static_assert(AmfFormatStrides[AmfFormat_R16G16B16_SINT] == 6,
              "AmfFormatStrides AmfFormat_R16G16B16_SINT");
static_assert(AmfFormatStrides[AmfFormat_R32G32_FLOAT] == 8,
              "AmfFormatStrides AmfFormat_R32G32_FLOAT");
static_assert(AmfFormatStrides[AmfFormat_R32G32_SINT] == 8,
              "AmfFormatStrides AmfFormat_R32G32_SINT");
static_assert(AmfFormatStrides[AmfFormat_R10G10B10A2_UNORM] == 4,
              "AmfFormatStrides AmfFormat_R10G10B10A2_UNORM");
static_assert(AmfFormatStrides[AmfFormat_R32_SINT] == 4,
              "AmfFormatStrides AmfFormat_R32_SINT");
static_assert(AmfFormatStrides[AmfFormat_R8G8_UNORM] == 2,
              "AmfFormatStrides AmfFormat_R8G8_UNORM");
static_assert(AmfFormatStrides[AmfFormat_R16_SINT] == 2,
              "AmfFormatStrides AmfFormat_R16_SINT");
static_assert(AmfFormatStrides[AmfFormat_R8_UNORM] == 1,
              "AmfFormatStrides AmfFormat_R8_UNORM");
static_assert(AmfFormatStrides[AmfFormat_R8_SINT] == 1,
              "AmfFormatStrides AmfFormat_R8_SINT");
static_assert(AmfFormatStrides[AmfFormat_R32_UNIT_VEC_AS_FLOAT] == 4,
              "AmfFormatStrides AmfFormat_R32_UNIT_VEC_AS_FLOAT");
static_assert(AmfFormatStrides[AmfFormat_R8G8B8A8_TANGENT_SPACE] == 4,
              "AmfFormatStrides AmfFormat_R8G8B8A8_TANGENT_SPACE");

REFLECTOR_CREATE(GeneralMeshConstantsFlags, ENUM, 1, CLASS, isDestructionMesh,
                 isSkinnedMesh);
REFLECTOR_CREATE(CarPaintMeshConstantsFlags, ENUM, 1, CLASS, deformable,
                 skinned);

REFLECTOR_CREATE(GeneralConstantsFlags, ENUM, 1, CLASS, backfaceCulling,
                 alphaBlend, alphaTest, dynamicEmissive, worldSpaceNormals,
                 roadJunction, useVertexAnimation, anisotropicFiltering,
                 useCustomEmissiveHue, useMPMChannelInput, useDiffuseRoughness,
                 useSpecularAniso, useTransmission, useClearCoat, wireAA,
                 HDRReference, layeredUseLayering, overlayUseOverlay,
                 useEmissive, useEmissiveLightColor, roadDepthBias);

REFLECTOR_CREATE(WindowConstantsFlags, ENUM, 1, CLASS, simple, oneSided);

REFLECTOR_CREATE(CarPaintConstantsFlags0, ENUM, 1, CLASS, decals,
                 useDamageBlend, dirt, tint, tintSoftBlend, twoSided,
                 alphaBlend, alphaTest, rotating, scrolling);

REFLECTOR_CREATE(CarPaintConstantsFlags1, ENUM, 1, CLASS, useCustomEmissiveHue,
                 useMPMChannelInput);

REFLECTOR_CREATE(CarPaintConstantsFlags2, ENUM, 1, CLASS,
                 useCustomDiffuseRoughness, useSpecularAniso, useTransmission,
                 useClearcoat);

REFLECTOR_CREATE(CharacterSkinConstantsFlags, ENUM, 1, CLASS, doubleSided,
                 useAlphaMask, useWrinkleMap, useFur, useMPMChannelInput,
                 useCustomDiffuseRoughness, useTransmission, headMaterial);

REFLECTOR_CREATE(CharacterConstantsFlags, ENUM, 1, CLASS, doubleSided,
                 alphaTest, alphaBlending, useDetail, useDecal, useTint,
                 useTintSoftBlend, useWrinkleMap, useCustomEmissiveHue,
                 useMPMChannelInput, useCustomDiffuseRoughness,
                 useSpecularAniso, useTransmission);

REFLECTOR_CREATE(EyeGlossConstantsFlags, ENUM, 1, CLASS,
                 customEyeReflectionCube);

REFLECTOR_CREATE(HairConstantsFlags, ENUM, 1, CLASS, doubleSided, alphaTest,
                 alphaBlending);

REFLECTOR_CREATE(BarkConstantsFlags, ENUM, 1, CLASS, useMPMChannelInput,
                 useCustomDiffuseRoughness, detailNormalUseUV2,
                 useNewAnimation);

REFLECTOR_CREATE(FoliageConstantsFlags, ENUM, 1, CLASS, renderTransparent,
                 objectSpaceNormalMap, useInteractionDisplacement,
                 useInteractionFlattening, useCharacterInteractionFlattening,
                 useMPMChannelInput, useTransmission, useNewAnimation);

REFLECTOR_CREATE(GeneralR2ConstantsFlags, ENUM, 1, CLASS, objectSpaceNormal,
                 useEmissive, emissiveTextureHasColor, useEmissiveLightColor,
                 doubleSided, decalBlend, alphaTest, detailUV2, useAlbedoDetail,
                 albedoDetailAlphaGloss, useNormalDetail, useTint, tintUV2,
                 useTextureBlend1, animateTexture, useVertexAnimations, fur,
                 useTextureBlend2, UISurface, useColorMask);

REFLECTOR_CREATE(GeneralMkIIIConstantsFlags, ENUM, 1, CLASS, dynamicEmissive,
                 alphaBlend, alphaTest, backfaceCulling, worldSpaceNormals,
                 usePropertyMasking, useLayered, useOverlay, useDecal,
                 useDamage, useVertexAnimation, roadDepthBias,
                 anisotropicFiltering, wireAA);

REFLECTOR_CREATE(CharacterConstantsFlags_GZ, ENUM, 1, CLASS, doubleSided,
                 alphaTest, alphaBlending, featureMapTint, wrinkleMap,
                 cameraLightingEnable);

REFLECTOR_CREATE(HairConstantsFlags_GZ, ENUM, 1, CLASS, doubleSided, alphaTest,
                 alphaBlending, useColorMask);

REFLECTOR_CREATE(CharacterSkinConstantsFlags_GZ, ENUM, 1, CLASS, doubleSided,
                 useAlphaMask, useFeatureTintMap, useWrinkleMap, useFur);

REFLECTOR_CREATE(WindowConstantsFlags_GZ, ENUM, 1, CLASS, simple, oneSided,
                 lensOcclusion);

REFLECTOR_CREATE(BarkConstantsFlags_GZ, ENUM, 1, CLASS, noFade, useWaterFog,
                 lowResShadows, useLayered, useOverlay, ignoreColorTint);

REFLECTOR_CREATE(CharacterSkinConstantsFlags_R2, ENUM, 1, CLASS, blendUseUV2,
                 useTint, doubleSided, useAlphaMask, useWrinkleMap, useFur,
                 useGibAlbedo, useGibDetail, triangleAdjacency);

REFLECTOR_CREATE(GeneralR2Constants_R2_flags0, ENUM, 1, CLASS,
                 objectSpaceNormal, useEmissive, emissiveOnlyTransparent,
                 emissiveTextureHasColor, useEmissiveLightColor, doubleSided,
                 decalBlend, alphaTest, detailUV2, useAlbedoDetail,
                 albedoDetailAlphaGloss, useNormalDetail);

REFLECTOR_CREATE(GeneralR2Constants_R2_flags1, ENUM, 1, CLASS, useTextureBlend1,
                 animateTexture, useVertexAnimations, useRigidVertexAnimations,
                 useSoftVertexAnimations, useFluidVertexAnimations);

REFLECTOR_CREATE(GeneralR2Constants_R2_flags2, ENUM, 1, CLASS, vertexAnimLoops,
                 directional, fur, HDRRef, useTextureBlend2);

REFLECTOR_CREATE(WindowConstantsFlags_R2, ENUM, 1, CLASS, simple, oneSided,
                 skinned, dirtLayerEnable);

REFLECTOR_CREATE(BarkConstantsFlags0_R2, ENUM, 1, CLASS, useObjectNormal,
                 useTextureBlend1);

REFLECTOR_CREATE(BarkConstantsFlags1_R2, ENUM, 1, CLASS, noFade, useWaterFog,
                 lowResShadows);

REFLECTOR_CREATE(FoliageConstantsFlags_R2, ENUM, 1, CLASS, renderTransparent,
                 objectSpaceNormalMap, useInteractionDisplacement,
                 useInteractionFlattening, useCharacterInteractionFlattening,
                 positiveBackfaceNormals);
