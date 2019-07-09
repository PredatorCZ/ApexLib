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
#include <cmath>
#include "datas/halfFloat.hpp"

typedef t_Vector4<float16> HVector4;
typedef t_Vector2<float16> HVector2;
typedef t_Vector<float16> HVector;

class packedInt32
{
	unsigned int Data;
public:
	static const unsigned int mask = 0x3ff;

	UIVector4 ToUIVector4() const
	{
		UIVector4 out;
		out.X = Data & mask;
		out.Y = (Data >> 10) & mask;
		out.Z = (Data >> 20) & mask;
		out.W = (Data >> 30) & 3;
		return out;
	}

	Vector4 ToVector4() const
	{
		constexpr float divider = 1.f / mask;
		return ToUIVector4().Convert<float>() * divider;
	}

	UIVector ToUIVector() const
	{
		UIVector out;
		out.X = Data & 0x7FF;
		out.Y = (Data >> 11) & 0x7FF;
		out.Z = (Data >> 22) & 0x3FF;
		return out;
	}

	Vector ToVector() const
	{
		constexpr float div1 = 1.f / 0x7FF;
		constexpr float div2 = 1.f / 0x3FF;

		return ToUIVector().Convert<float>() * Vector(div1, div1, div2);
	}
};

ES_INLINE Vector PackedFloatToUVector(float input)
{
	Vector out(
		input,
		input * (1.f / 256.f),
		input * (1.f / 65536.f)
	);

	out -= Vector(
		floorf(out.X),
		floorf(out.Y),
		floorf(out.Z)
	);

	return out;
}

ES_INLINE Vector PackedFloatToVector(float input)
{
	Vector out = PackedFloatToUVector(input);

	out *= 2.f;
	out -= 1.f;
	return out;
}

ES_INLINE Vector4 PackedFloatToColor(float input)
{
	Vector4 out(
		input,
		input * (1.f / 64.f),
		input * (1.f / 4096.f),
		input * (1.f / 262144.f)
	);

	return out - Vector4(
		floorf(out.X),
		floorf(out.Y),
		floorf(out.Z),
		floorf(out.W)
	);
}

ES_INLINE Vector PolarTBNToVector(UCVector4 input)
{
	Vector4 qval = input.Convert<float>() - 127.f;
	qval *= (1.0f / 128.0f) * 3.1415926f;
	float reflector = qval.W < 0.0f ? 1.f : -1.f;
	qval.W = abs(qval.W);
	const Vector4 sval(sinf(qval.X), sinf(qval.Y), sinf(qval.Z), sinf(qval.W));
	const Vector4 cval(cosf(qval.X), cosf(qval.Y), cosf(qval.Z), cosf(qval.W));

	const Vector tangent(sval.W*cval.Z, sval.W*sval.Z, cval.W);
	const Vector bitangent(sval.Y*cval.X, sval.Y*sval.X, cval.Y);
	const Vector normal = tangent.Cross(bitangent) * reflector;
	return normal;
}
