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
#include <climits>
#include "AmfMesh.h"
#include "Units.h"


template<class OutputFormat> ES_INLINE void AmfFormatEval(const AmfVertexDescriptor_internal *that, int at, void *data)
{
	OutputFormat &out = *static_cast<OutputFormat*>(data);
	out = *reinterpret_cast<const OutputFormat*>(that->buffer + (at * that->streamStride));
}

template<AmfFormat, class OutputFormat> class tVertexDescriptor : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		AmfFormatEval<OutputFormat>(this, at, data);
	}
};

template<>class tVertexDescriptor<AmfFormat_R16G16B16A16_UNORM, Vector4> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector4 &out = *static_cast<Vector4*>(data);
		USVector4 sub = {};
		AmfFormatEval<USVector4>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(USHRT_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R16G16B16_UNORM, Vector> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector &out = *static_cast<Vector*>(data);
		USVector sub = {};
		AmfFormatEval<USVector>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(USHRT_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R16G16B16_SNORM, Vector> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector &out = *static_cast<Vector*>(data);
		SVector sub = {};
		AmfFormatEval<SVector>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(SHRT_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R16G16_UNORM, Vector2> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector2 &out = *static_cast<Vector2*>(data);
		USVector2 sub = {};
		AmfFormatEval<USVector2>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(USHRT_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R16G16_SNORM, Vector2> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector2 &out = *static_cast<Vector2*>(data);
		SVector2 sub = {};
		AmfFormatEval<SVector2>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(SHRT_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R16_UNORM, float> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		float &out = *static_cast<float*>(data);
		unsigned short sub = 0;
		AmfFormatEval<unsigned short>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(USHRT_MAX);
		out = static_cast<float>(sub) * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R16_SNORM, float> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		float &out = *static_cast<float*>(data);
		short sub = 0;
		AmfFormatEval<short>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(SHRT_MAX);
		out = static_cast<float>(sub) * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R8G8B8A8_SNORM, Vector4> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector4 &out = *static_cast<Vector4*>(data);
		CVector4 sub = {};
		AmfFormatEval<CVector4>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(CHAR_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R8G8B8A8_UNORM, Vector4> : public AmfVertexDescriptor_internal
{
protected:
	void Evaluate(int at, void *data) const
	{
		Vector4 &out = *static_cast<Vector4*>(data);
		UCVector4 sub = {};
		AmfFormatEval<UCVector4>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(UCHAR_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R8G8B8A8_UNORM_SRGB, Vector4> : 
	public tVertexDescriptor<AmfFormat_R8G8B8A8_UNORM, Vector4>{};

template<>class tVertexDescriptor<AmfFormat_R8G8_SNORM, Vector2> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector2 &out = *static_cast<Vector2*>(data);
		CVector2 sub = {};
		AmfFormatEval<CVector2>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(CHAR_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R8G8_UNORM, Vector2> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector2 &out = *static_cast<Vector2*>(data);
		UCVector2 sub = {};
		AmfFormatEval<UCVector2>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(UCHAR_MAX);
		out = sub.Convert<float>() * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R8_SNORM, float> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		float &out = *static_cast<float*>(data);
		char sub = 0;
		AmfFormatEval<char>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(CHAR_MAX);
		out = static_cast<float>(sub) * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R8_UNORM, float> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		float &out = *static_cast<float*>(data);
		unsigned char sub = 0; sub = {};
		AmfFormatEval<unsigned char>(this, at, &sub);
		constexpr float divider = 1.f / static_cast<float>(UCHAR_MAX);
		out = static_cast<float>(sub) * divider;
	}
};

template<>class tVertexDescriptor<AmfFormat_R16G16B16A16_FLOAT, Vector4> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector4 &out = *static_cast<Vector4*>(data);
		HVector4 sub = {};
		AmfFormatEval<HVector4>(this, at, &sub);
		out = sub.Convert<float>();
	}
};

template<>class tVertexDescriptor<AmfFormat_R16G16B16_FLOAT, Vector> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector &out = *static_cast<Vector*>(data);
		HVector sub = {};
		AmfFormatEval<HVector>(this, at, &sub);
		out = sub.Convert<float>();
	}
};

template<>class tVertexDescriptor<AmfFormat_R16G16_FLOAT, Vector2> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector2 &out = *static_cast<Vector2*>(data);
		HVector2 sub = {};
		AmfFormatEval<HVector2>(this, at, &sub);
		out = sub.Convert<float>();
	}
};

template<>class tVertexDescriptor<AmfFormat_R16_FLOAT, float> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		float &out = *static_cast<float*>(data);
		float16 sub = {};
		AmfFormatEval<float16>(this, at, &sub);
		out = static_cast<float>(sub);
	}
};

template<>class tVertexDescriptor<AmfFormat_R10G10B10A2_UNORM, Vector4> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector4 &out = *static_cast<Vector4*>(data);
		packedInt32 sub = {};
		AmfFormatEval<packedInt32>(this, at, &sub);
		out = sub.ToVector4().Convert<float>();
	}
};

template<>class tVertexDescriptor<AmfFormat_R10G10B10A2_UINT, UIVector4> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		UIVector4 &out = *static_cast<UIVector4*>(data);
		packedInt32 sub = {};
		AmfFormatEval<packedInt32>(this, at, &sub);
		out = sub.ToUIVector4();
	}
};

template<>class tVertexDescriptor<AmfFormat_R11G11B10_FLOAT, Vector> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector &out = *static_cast<Vector*>(data);
		packedInt32 sub = {};
		AmfFormatEval<packedInt32>(this, at, &sub);
		out = sub.ToVector().Convert<float>();
	}
};

template<>class tVertexDescriptor<AmfFormat_R32_UNIT_VEC_AS_FLOAT, Vector> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector &out = *static_cast<Vector*>(data);
		float sub = 0.f;
		AmfFormatEval<float>(this, at, &sub);
		out = PackedFloatToVector(sub);
	}
};

template<>class tVertexDescriptor<AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c, Vector> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector &out = *static_cast<Vector*>(data);
		float sub = 0.f;
		AmfFormatEval<float>(this, at, &sub);
		out = PackedFloatToUVector(sub);
	}
};

template<>class tVertexDescriptor<AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, Vector4> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector4 &out = *static_cast<Vector4*>(data);
		float sub = 0.f;
		AmfFormatEval<float>(this, at, &sub);
		out = PackedFloatToColor(sub);
	}
};

template<>class tVertexDescriptor<AmfFormat_R8G8B8A8_TANGENT_SPACE, Vector> : public AmfVertexDescriptor_internal
{
	void Evaluate(int at, void *data) const
	{
		Vector &out = *static_cast<Vector*>(data);
		UCVector4 sub;
		AmfFormatEval<float>(this, at, &sub);
		out = PolarTBNToVector(sub);
	}
};

template<>class tVertexDescriptor<AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, Vector4> : 
	public tVertexDescriptor<AmfFormat_R8G8B8A8_UNORM, Vector4>
{
	typedef tVertexDescriptor<AmfFormat_R8G8B8A8_UNORM, Vector4> parent_class;
protected:
	void Evaluate(int at, void *data) const
	{
		Vector4 &out = *static_cast<Vector4*>(data);
		parent_class::Evaluate(at, &out);
		out = (out - 0.5f) * 2.0f;
	}
};

template<>class tVertexDescriptor<AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, Vector> : 
	public tVertexDescriptor<AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, Vector4> 
{
	typedef tVertexDescriptor<AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, Vector4> parent_class;

	void Evaluate(int at, void *data) const
	{
		Vector &out = *static_cast<Vector*>(data);
		Vector4 sub = {};
		parent_class::Evaluate(at, &sub);
		out = reinterpret_cast<Vector&>(sub);
	}
};