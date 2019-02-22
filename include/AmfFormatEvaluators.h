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

#pragma once
#include "AmfEnums.h"
#include "Units.h"

template<AmfFormat, class OutputFormat> ES_INLINE void AmfFormatEval(AmfStreamAttribute *that, int at, void *data)
{
	OutputFormat &out = *static_cast<OutputFormat*>(data);
	out = *reinterpret_cast<const OutputFormat*>(that->buffer + (at*that->Header.streamStride));
}

template<>void AmfFormatEval<AmfFormat_R16G16B16A16_UNORM, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	USVector4 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, USVector4>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(USHRT_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R16G16B16A16_SNORM, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	SVector4 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, SVector4>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(SHRT_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R16G16B16_UNORM, Vector>(AmfStreamAttribute *that, int at, void *data)
{
	Vector &out = *static_cast<Vector*>(data);
	USVector sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, USVector>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(USHRT_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R16G16B16_SNORM, Vector>(AmfStreamAttribute *that, int at, void *data)
{
	Vector &out = *static_cast<Vector*>(data);
	SVector sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, SVector>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(SHRT_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R16G16_UNORM, Vector2>(AmfStreamAttribute *that, int at, void *data)
{
	Vector2 &out = *static_cast<Vector2*>(data);
	USVector2 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, USVector2>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(USHRT_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R16G16_SNORM, Vector2>(AmfStreamAttribute *that, int at, void *data)
{
	Vector2 &out = *static_cast<Vector2*>(data);
	SVector2 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, SVector2>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(SHRT_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R16_UNORM, float>(AmfStreamAttribute *that, int at, void *data)
{
	float &out = *static_cast<float*>(data);
	unsigned short sub = 0;
	AmfFormatEval<AmfFormat_R8_SINT, unsigned short>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(USHRT_MAX);
	out = static_cast<float>(sub) * divider;
}

template<>void AmfFormatEval<AmfFormat_R16_SNORM, float>(AmfStreamAttribute *that, int at, void *data)
{
	float &out = *static_cast<float*>(data);
	short sub = 0;
	AmfFormatEval<AmfFormat_R8_SINT, short>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(SHRT_MAX);
	out = static_cast<float>(sub) * divider;
}

template<>void AmfFormatEval<AmfFormat_R8G8B8A8_SNORM, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	CVector4 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, CVector4>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(CHAR_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R8G8B8A8_UNORM, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	UCVector4 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, UCVector4>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(UCHAR_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R8G8B8A8_UNORM_SRGB, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	AmfFormatEval<AmfFormat_R8G8B8A8_UNORM, Vector4>(that, at, &out);
}

template<>void AmfFormatEval<AmfFormat_R8G8_SNORM, Vector2>(AmfStreamAttribute *that, int at, void *data)
{
	Vector2 &out = *static_cast<Vector2*>(data);
	CVector2 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, CVector2>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(CHAR_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R8G8_UNORM, Vector2>(AmfStreamAttribute *that, int at, void *data)
{
	Vector2 &out = *static_cast<Vector2*>(data);
	UCVector2 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, UCVector2>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(UCHAR_MAX);
	out = sub.Convert<float>() * divider;
}

template<>void AmfFormatEval<AmfFormat_R8_SNORM, float>(AmfStreamAttribute *that, int at, void *data)
{
	float &out = *static_cast<float*>(data);
	char sub = 0;
	AmfFormatEval<AmfFormat_R8_SINT, char>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(CHAR_MAX);
	out = static_cast<float>(sub) * divider;
}

template<>void AmfFormatEval<AmfFormat_R8_UNORM, float>(AmfStreamAttribute *that, int at, void *data)
{
	float &out = *static_cast<float*>(data);
	unsigned char sub = 0; sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, unsigned char>(that, at, &sub);
	constexpr float divider = 1.f / static_cast<float>(UCHAR_MAX);
	out = static_cast<float>(sub) * divider;
}

template<>void AmfFormatEval<AmfFormat_R16G16B16A16_FLOAT, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	HVector4 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, HVector4>(that, at, &sub);
	out = sub.Convert<float>();
}

template<>void AmfFormatEval<AmfFormat_R16G16B16_FLOAT, Vector>(AmfStreamAttribute *that, int at, void *data)
{
	Vector &out = *static_cast<Vector*>(data);
	HVector sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, HVector>(that, at, &sub);
	out = sub.Convert<float>();
}

template<>void AmfFormatEval<AmfFormat_R16G16_FLOAT, Vector2>(AmfStreamAttribute *that, int at, void *data)
{
	Vector2 &out = *static_cast<Vector2*>(data);
	HVector2 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, HVector2>(that, at, &sub);
	out = sub.Convert<float>();
}

template<>void AmfFormatEval<AmfFormat_R16_FLOAT, float>(AmfStreamAttribute *that, int at, void *data)
{
	float &out = *static_cast<float*>(data);
	float16 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, float16>(that, at, &sub);
	out = static_cast<float>(sub);
}

template<>void AmfFormatEval<AmfFormat_R10G10B10A2_UNORM, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	packedInt32 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, packedInt32>(that, at, &sub);
	out = sub.ToVector4().Convert<float>();
}

template<>void AmfFormatEval<AmfFormat_R10G10B10A2_UINT, UIVector4>(AmfStreamAttribute *that, int at, void *data)
{
	UIVector4 &out = *static_cast<UIVector4*>(data);
	packedInt32 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, packedInt32>(that, at, &sub);
	out = sub.ToUIVector4();
}


template<>void AmfFormatEval<AmfFormat_R11G11B10_FLOAT, Vector>(AmfStreamAttribute *that, int at, void *data)
{
	Vector &out = *static_cast<Vector*>(data);
	packedInt32 sub = {};
	AmfFormatEval<AmfFormat_R8_SINT, packedInt32>(that, at, &sub);
	out = sub.ToVector().Convert<float>();
}

template<>void AmfFormatEval<AmfFormat_R32_UNIT_VEC_AS_FLOAT, Vector>(AmfStreamAttribute *that, int at, void *data)
{
	Vector &out = *static_cast<Vector*>(data);
	float sub = 0.f;
	AmfFormatEval<AmfFormat_R8_SINT, float>(that, at, &sub);
	out = PackedFloatToVector(sub);
}

template<>void AmfFormatEval<AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c, Vector>(AmfStreamAttribute *that, int at, void *data)
{
	Vector &out = *static_cast<Vector*>(data);
	float sub = 0.f;
	AmfFormatEval<AmfFormat_R8_SINT, float>(that, at, &sub);
	out = PackedFloatToUVector(sub);
}

template<>void AmfFormatEval<AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	float sub = 0.f;
	AmfFormatEval<AmfFormat_R8_SINT, float>(that, at, &sub);
	out = PackedFloatToColor(sub);
}

template<>void AmfFormatEval<AmfFormat_R8G8B8A8_TANGENT_SPACE, Vector>(AmfStreamAttribute *that, int at, void *data)
{
	Vector &out = *static_cast<Vector*>(data);
	UCVector4 sub;
	AmfFormatEval<AmfFormat_R8_SINT, float>(that, at, &sub);
	out = PolarTBNToVector(sub);
}

template<>void AmfFormatEval<AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, Vector4>(AmfStreamAttribute *that, int at, void *data)
{
	Vector4 &out = *static_cast<Vector4*>(data);
	AmfFormatEval<AmfFormat_R8G8B8A8_UNORM, Vector4>(that, at, &out);
	out = (out - 0.5f) * 2.0f;
}

template<>void AmfFormatEval<AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, Vector>(AmfStreamAttribute *that, int at, void *data)
{
	Vector &out = *static_cast<Vector*>(data);
	Vector4 sub = {};
	AmfFormatEval<AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, Vector4>(that, at, &sub);
	out = reinterpret_cast<Vector&>(sub);
}

