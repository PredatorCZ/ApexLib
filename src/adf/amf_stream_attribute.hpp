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
#include "datas/reflector.hpp"

REFLECTOR_CREATE(AmfUsage, ENUM, 0,
                 AmfUsage_Unspecified,       //
                 AmfUsage_Position,          //
                 AmfUsage_TextureCoordinate, //
                 AmfUsage_Normal,            //
                 AmfUsage_Tangent,           //
                 AmfUsage_BiTangent,         //
                 AmfUsage_TangentSpace,      //
                 AmfUsage_BoneIndex,         //
                 AmfUsage_BoneWeight,        //
                 AmfUsage_Color,             //
                 AmfUsage_WireRadius,        //
                 AmfUsage_DeformNormal_c,    //
                 AmfUsage_DeformPoints_c     //
);

static constexpr int AmfFormatStrides[] = {
    16, 16, 16, 12, 12, 12, 8, 8, 8, 8, 8, 6, 6, 6, 6, 6, 8, 8,
    8,  4,  4,  4,  4,  4,  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
    2,  2,  2,  2,  2,  2,  2, 2, 1, 1, 1, 1, 4, 4, 4, 4, 4};

REFLECTOR_CREATE(AmfFormat, ENUM, 0,
                 AmfFormat_R32G32B32A32_FLOAT,               //
                 AmfFormat_R32G32B32A32_UINT,                //
                 AmfFormat_R32G32B32A32_SINT,                //
                 AmfFormat_R32G32B32_FLOAT,                  //
                 AmfFormat_R32G32B32_UINT,                   //
                 AmfFormat_R32G32B32_SINT,                   //
                 AmfFormat_R16G16B16A16_FLOAT,               //
                 AmfFormat_R16G16B16A16_UNORM,               //
                 AmfFormat_R16G16B16A16_UINT,                //
                 AmfFormat_R16G16B16A16_SNORM,               //
                 AmfFormat_R16G16B16A16_SINT,                //
                 AmfFormat_R16G16B16_FLOAT,                  //
                 AmfFormat_R16G16B16_UNORM,                  //
                 AmfFormat_R16G16B16_UINT,                   //
                 AmfFormat_R16G16B16_SNORM,                  //
                 AmfFormat_R16G16B16_SINT,                   //
                 AmfFormat_R32G32_FLOAT,                     //
                 AmfFormat_R32G32_UINT,                      //
                 AmfFormat_R32G32_SINT,                      //
                 AmfFormat_R10G10B10A2_UNORM,                //
                 AmfFormat_R10G10B10A2_UINT,                 //
                 AmfFormat_R11G11B10_FLOAT,                  //
                 AmfFormat_R8G8B8A8_UNORM,                   //
                 AmfFormat_R8G8B8A8_UNORM_SRGB,              //
                 AmfFormat_R8G8B8A8_UINT,                    //
                 AmfFormat_R8G8B8A8_SNORM,                   //
                 AmfFormat_R8G8B8A8_SINT,                    //
                 AmfFormat_R16G16_FLOAT,                     //
                 AmfFormat_R16G16_UNORM,                     //
                 AmfFormat_R16G16_UINT,                      //
                 AmfFormat_R16G16_SNORM,                     //
                 AmfFormat_R16G16_SINT,                      //
                 AmfFormat_R32_FLOAT,                        //
                 AmfFormat_R32_UINT,                         //
                 AmfFormat_R32_SINT,                         //
                 AmfFormat_R8G8_UNORM,                       //
                 AmfFormat_R8G8_UINT,                        //
                 AmfFormat_R8G8_SNORM,                       //
                 AmfFormat_R8G8_SINT,                        //
                 AmfFormat_R16_FLOAT,                        //
                 AmfFormat_R16_UNORM,                        //
                 AmfFormat_R16_UINT,                         //
                 AmfFormat_R16_SNORM,                        //
                 AmfFormat_R16_SINT,                         //
                 AmfFormat_R8_UNORM,                         //
                 AmfFormat_R8_UINT,                          //
                 AmfFormat_R8_SNORM,                         //
                 AmfFormat_R8_SINT,                          //
                 AmfFormat_R32_UNIT_VEC_AS_FLOAT,            //
                 AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT,      //
                 AmfFormat_R8G8B8A8_TANGENT_SPACE,           //
                 AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c, //
                 AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c         //
);

ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R32G32B32A32_SINT] == 16);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R32G32B32_FLOAT] == 12);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R32G32B32_SINT] == 12);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R16G16B16A16_FLOAT] == 8);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R16G16B16A16_SINT] == 8);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R16G16B16_FLOAT] == 6);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R16G16B16_SINT] == 6);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R32G32_FLOAT] == 8);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R32G32_SINT] == 8);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R10G10B10A2_UNORM] == 4);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R32_SINT] == 4);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R8G8_UNORM] == 2);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R16_SINT] == 2);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R8_UNORM] == 1);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R8_SINT] == 1);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R32_UNIT_VEC_AS_FLOAT] == 4);
ES_STATIC_ASSERT(AmfFormatStrides[AmfFormat_R8G8B8A8_TANGENT_SPACE] == 4);

struct AmfStreamAttribute {
  AmfUsage usage;
  AmfFormat format;
  uint8 streamIndex, streamOffset, streamStride;
  char packingData[8];
};
