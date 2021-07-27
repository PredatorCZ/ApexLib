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

#include "amf_codec.hpp"
#include "uni/internal/format_full.hpp"
#include <cstring>
#include <map>

using ut = uni::FormatType;
using ud = uni::DataType;

static const std::map<AmfFormat, uni::FormatDescr> formatRemaps{
    {AmfFormat_R32G32B32A32_FLOAT, {ut::FLOAT, ud::R32G32B32A32}},
    {AmfFormat_R32G32B32A32_UINT, {ut::UINT, ud::R32G32B32A32}},
    {AmfFormat_R32G32B32A32_SINT, {ut::INT, ud::R32G32B32A32}},
    {AmfFormat_R32G32B32_FLOAT, {ut::FLOAT, ud::R32G32B32}},
    {AmfFormat_R32G32B32_UINT, {ut::UINT, ud::R32G32B32}},
    {AmfFormat_R32G32B32_SINT, {ut::INT, ud::R32G32B32}},
    {AmfFormat_R16G16B16A16_FLOAT, {ut::FLOAT, ud::R16G16B16A16}},
    {AmfFormat_R16G16B16A16_UNORM, {ut::UNORM, ud::R16G16B16A16}},
    {AmfFormat_R16G16B16A16_UINT, {ut::UINT, ud::R16G16B16A16}},
    {AmfFormat_R16G16B16A16_SNORM, {ut::NORM, ud::R16G16B16A16}},
    {AmfFormat_R16G16B16A16_SINT, {ut::INT, ud::R16G16B16A16}},
    {AmfFormat_R16G16B16_FLOAT, {ut::FLOAT, ud::R16G16B16}},
    {AmfFormat_R16G16B16_UNORM, {ut::UNORM, ud::R16G16B16}},
    {AmfFormat_R16G16B16_UINT, {ut::UINT, ud::R16G16B16}},
    {AmfFormat_R16G16B16_SNORM, {ut::NORM, ud::R16G16B16}},
    {AmfFormat_R16G16B16_SINT, {ut::INT, ud::R16G16B16}},
    {AmfFormat_R32G32_FLOAT, {ut::FLOAT, ud::R32G32}},
    {AmfFormat_R32G32_UINT, {ut::UINT, ud::R32G32}},
    {AmfFormat_R32G32_SINT, {ut::INT, ud::R32G32}},
    {AmfFormat_R10G10B10A2_UNORM, {ut::UNORM, ud::R10G10B10A2}},
    {AmfFormat_R10G10B10A2_UINT, {ut::UINT, ud::R10G10B10A2}},
    {AmfFormat_R11G11B10_FLOAT, {ut::FLOAT, ud::R11G11B10}},
    {AmfFormat_R8G8B8A8_UNORM, {ut::UNORM, ud::R8G8B8A8}},
    {AmfFormat_R8G8B8A8_UNORM_SRGB, {ut::UNORM, ud::R8G8B8A8}},
    {AmfFormat_R8G8B8A8_UINT, {ut::UINT, ud::R8G8B8A8}},
    {AmfFormat_R8G8B8A8_SNORM, {ut::NORM, ud::R8G8B8A8}},
    {AmfFormat_R8G8B8A8_SINT, {ut::INT, ud::R8G8B8A8}},
    {AmfFormat_R16G16_FLOAT, {ut::FLOAT, ud::R16G16}},
    {AmfFormat_R16G16_UNORM, {ut::UNORM, ud::R16G16}},
    {AmfFormat_R16G16_UINT, {ut::UINT, ud::R16G16}},
    {AmfFormat_R16G16_SNORM, {ut::NORM, ud::R16G16}},
    {AmfFormat_R16G16_SINT, {ut::INT, ud::R16G16}},
    {AmfFormat_R32_FLOAT, {ut::FLOAT, ud::R32}},
    {AmfFormat_R32_UINT, {ut::UINT, ud::R32}},
    {AmfFormat_R32_SINT, {ut::INT, ud::R32}},
    {AmfFormat_R8G8_UNORM, {ut::UNORM, ud::R8G8}},
    {AmfFormat_R8G8_UINT, {ut::UINT, ud::R8G8}},
    {AmfFormat_R8G8_SNORM, {ut::NORM, ud::R8G8}},
    {AmfFormat_R8G8_SINT, {ut::INT, ud::R8G8}},
    {AmfFormat_R16_FLOAT, {ut::FLOAT, ud::R16}},
    {AmfFormat_R16_UNORM, {ut::UNORM, ud::R16}},
    {AmfFormat_R16_UINT, {ut::UINT, ud::R16}},
    {AmfFormat_R16_SNORM, {ut::NORM, ud::R16}},
    {AmfFormat_R16_SINT, {ut::INT, ud::R16}},
    {AmfFormat_R8_UNORM, {ut::UNORM, ud::R8}},
    {AmfFormat_R8_UINT, {ut::UINT, ud::R8}},
    {AmfFormat_R8_SNORM, {ut::NORM, ud::R8}},
    {AmfFormat_R8_SINT, {ut::INT, ud::R8}},
    {AmfFormat_R8G8B8A8_TANGENT_SPACE, {ut::NORM, ud::CUSTOM}},
    {AmfFormat_R32_UNIT_VEC_AS_FLOAT, {ut::NORM, ud::CUSTOM}},
    {AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, {ut::UNORM, ud::CUSTOM}},
    {AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c, {ut::UNORM, ud::CUSTOM}},
    {AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, {ut::NORM, ud::CUSTOM}},
};

class PolarTBN : public uni::FormatCodec {
public:
  typedef uni::FormatCodec_t<ut::NORM, ud::R8G8B8A8> parent;
  static Vector4A16 GetValue(const char *input) {
    auto out = parent::GetValue(input) * 3.1415926f;
    // TODO fully simd this
    float reflector = out.W < 0.0f ? 1.f : -1.f;
    out.W = fabs(out.W);
    const Vector4 sval(sinf(out.X), sinf(out.Y), sinf(out.Z), sinf(out.W));
    const Vector4 cval(cosf(out.X), cosf(out.Y), cosf(out.Z), cosf(out.W));

    const Vector4A16 tp0(sval.W, sval.W, cval.W, 0);
    const Vector4A16 tp1(cval.Z, sval.Z, 1, 0);
    const Vector4A16 tp2(sval.Y, sval.Y, cval.Y, 0);
    const Vector4A16 tp3(cval.X, sval.X, 1, 0);

    const auto tangent = tp0 * tp1;
    const auto bitangent = tp2 * tp3;
    // TODO calculate rotation around normal as w comp
    return tangent.Cross(bitangent) * reflector;
  }

  void GetValue(Vector4A16 &out, const char *input) const override {
    out = GetValue(input);
  }

  void Sample(fvec &out, const char *input, size_t count,
              size_t stride) const override {
    _uni_::_fmtSampler<PolarTBN, ud::R8G8B8A8>(out, input, count, stride);
  }
};

class FloatUVec3 : public uni::FormatCodec {
public:
  static Vector4A16 GetValue(const char *input) {
    const float var = *reinterpret_cast<const float *>(input);
    const Vector4A16 temp0(var);
    const Vector4A16 temp1(1, GetFraction(8), GetFraction(16), 0);
    const auto retVal = temp0 * temp1;

    return retVal - _mm_floor_ps(retVal._data);
  }

  void GetValue(Vector4A16 &out, const char *input) const override {
    out = GetValue(input);
  }

  void Sample(fvec &out, const char *input, size_t count,
              size_t stride) const override {
    _uni_::_fmtSampler<FloatUVec3, ud::R32>(out, input, count, stride);
  }
};

class FloatVec3 : public FloatUVec3 {
public:
  static Vector4A16 GetValue(const char *input) {
    const auto retVal = FloatUVec3::GetValue(input);

    return (retVal * 2.f) - 1.f;
  }

  void GetValue(Vector4A16 &out, const char *input) const override {
    out = GetValue(input);
  }

  void Sample(fvec &out, const char *input, size_t count,
              size_t stride) const override {
    _uni_::_fmtSampler<FloatVec3, ud::R32>(out, input, count, stride);
  }
};

class FloatUVec4 : public uni::FormatCodec {
public:
  static Vector4A16 GetValue(const char *input) {
    const float var = *reinterpret_cast<const float *>(input);
    const Vector4A16 temp0(var);
    const Vector4A16 temp1(1, GetFraction(6), GetFraction(12), GetFraction(18));
    const auto retVal = temp0 * temp1;

    return retVal - _mm_floor_ps(retVal._data);
  }

  void GetValue(Vector4A16 &out, const char *input) const override {
    out = GetValue(input);
  }

  void Sample(fvec &out, const char *input, size_t count,
              size_t stride) const override {
    _uni_::_fmtSampler<FloatUVec4, ud::R32>(out, input, count, stride);
  }
};

class UVec4Norm : public uni::FormatCodec {
public:
  typedef uni::FormatCodec_t<ut::UNORM, ud::R8G8B8A8> parent;

  static Vector4A16 GetValue(const char *input) {
    auto var = parent::GetValue(input);
    return (var - 0.5f) * 2.0f;
  }

  void GetValue(Vector4A16 &out, const char *input) const override {
    out = GetValue(input);
  }

  void Sample(fvec &out, const char *input, size_t count,
              size_t stride) const override {
    _uni_::_fmtSampler<FloatUVec4, ud::R32>(out, input, count, stride);
  }
};

// This class holds vtable for each custom codec.
// Huge gamble, but there is no better way. (for C++14)
// TODO: maybe use std::any for C++17
class variant {
  mutable uint64 vtdata;

public:
  template <class C> variant(C cted) {
    static_assert(sizeof(decltype(cted)) <= sizeof(vtdata), "Invalid class!");
    vtdata = reinterpret_cast<uint64 &>(cted);
  }

  variant(const variant &) = default;
  variant(variant &&) = default;

  operator uni::FormatCodec &() const {
    return reinterpret_cast<uni::FormatCodec &>(vtdata);
  }
};

static const std::map<AmfFormat, variant> additionalRegistry{
    {AmfFormat_R8G8B8A8_TANGENT_SPACE, variant(PolarTBN{})},
    {AmfFormat_R32_UNIT_VEC_AS_FLOAT, variant(FloatVec3{})},
    {AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, variant(FloatUVec4{})},
    {AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c, variant(FloatUVec3{})},
    {AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, variant(UVec4Norm{})},
};

using pu = uni::PrimitiveDescriptor::Usage_e;

static const std::map<AmfUsage, pu> usageRemaps{
    {AmfUsage_Position, pu::Position},
    {AmfUsage_TextureCoordinate, pu::TextureCoordiante},
    {AmfUsage_Normal, pu::Normal},
    {AmfUsage_Tangent, pu::Tangent},
    {AmfUsage_BiTangent, pu::BiTangent},
    {AmfUsage_TangentSpace, pu::Normal},
    {AmfUsage_BoneIndex, pu::BoneIndices},
    {AmfUsage_BoneWeight, pu::BoneWeights},
    {AmfUsage_Color, pu::VertexColor},
    {AmfUsage_DeformNormal_c, pu::PositionDelta},
};

const char *AmfCodec::RawBuffer() const { return vertexBuffer; }
size_t AmfCodec::Offset() const { return attr.streamOffset; }
size_t AmfCodec::Stride() const { return attr.streamStride; }
size_t AmfCodec::Index() const { return attr.streamIndex; }
uni::FormatDescr AmfCodec::Type() const { return formatRemaps.at(attr.format); }
uni::BBOX AmfCodec::UnpackData() const {
  uni::BBOX retVal;
  Vector2 pData;
  memcpy(&pData, attr.packingData, sizeof(pData));

  if (attr.usage == AmfUsage_Position) {
    retVal.min = Vector4A16{pData.X};
  } else if (attr.usage == AmfUsage_TextureCoordinate) {
    retVal.min = Vector4A16{pData.X, pData.Y, 0, 0};
  } else if (!pData.X || !pData.Y) {
    // WARN
  }

  return retVal;
}

AmfCodec::UnpackDataType_e AmfCodec::UnpackDataType() const {
  int64 pData;
  memcpy(&pData, attr.packingData, sizeof(pData));
  auto cType = Type();

  if ((cType.outType == ut::NORM || cType.outType == ut::UNORM) && pData) {
    return UnpackDataType_e::Mul;
  }

  return UnpackDataType_e::None;
}

AmfCodec::Usage_e AmfCodec::Usage() const {
  auto found = usageRemaps.find(attr.usage);

  if (es::IsEnd(usageRemaps, found)) {
    return pu::Undefined;
  }

  return found->second;
}

uni::FormatCodec &AmfCodec::Codec() const {
  auto foundExtra = additionalRegistry.find(attr.format);

  if (!es::IsEnd(additionalRegistry, foundExtra)) {
    return uni::FormatCodec::Get(Type());
  }

  return foundExtra->second;
}
