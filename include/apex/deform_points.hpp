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
#include "adf_string.hpp"
#include "adf_array.hpp"
#include "adf_instance.hpp"
#include "datas/vectors.hpp"

struct ADFMatrix4x4 {
  Vector4 rows[4];
};

struct DeformPoint {
  AdfString name;
  JenHash3 nameHash;
  AdfString fromPart;
  JenHash3 fromPartHash;
  uint32 fromPartIndex;
  AdfString skinnedToPart;
  JenHash3 skinnedToPartHash;
  uint32 skinnedToPartIndex;
  uint32 shapeKey;
  uint8 hasCustomEnd;
  AdfHashString deformPointType;
  ADFMatrix4x4 startTransform;
  ADFMatrix4x4 endTransform;
  uint16 vertexIndices[4];
  float vertexWeights[4];

  void Fixup(char *masterBuffer);
};

static_assert(sizeof(DeformPoint) == 224, "Check assumptions");

struct DeformPoints {
  AdfArray<DeformPoint> points;
  AdfArray<uint16> constraintIndices, lightIndices, wheelIndices,
      nonDeformablePartsIndices, haulingHitchIndices, trailingHitchIndices;

  void Fixup(char *masterBuffer);
};

static_assert(sizeof(DeformPoints) == 112, "Check assumptions");

class DeformPoints_wrap : public ADFInstance {
  DeformPoints *data;

  void Fixup(char *masterBuffer);

public:
  static constexpr auto GetHash() { return JenHash3(0xBA022EDF); }

  DeformPoints_wrap(void *data_, ADFInternal *main_);
  DeformPoints *Data() { return data; }

  JenHash3 GetSuperClass() const { return -1; }
};
