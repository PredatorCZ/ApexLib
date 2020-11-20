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
#include "adf_instance.hpp"
#include "adf_bbox.hpp"

struct AxisAlignedBoundingBox {
  float min_x, max_x, min_y, max_y, min_z, max_z;
  operator AdfBBOX() {
    return AdfBBOX{{min_x, min_y, min_z}, {max_x, max_y, max_z}};
  }
};

struct StuntArea {
  AdfString name;
  JenHash3 nameHash;
  AdfString partName;
  JenHash3 partHash;
  uint32 partIndex;
  uint32 deformPoints[16];
  uint8 edgeValidity[16];
  uint16 numDeformPoints, active;
  Vector vertices[16];
  UCVector faces[14];
  uint16 numFaces;
  AxisAlignedBoundingBox BBOX;
  Vector center;

  void Fixup(char *masterBuffer);
};

static_assert(sizeof(StuntArea) == 392, "Check assumptions");

struct StuntAreaWeldingInfo {
  int16 aIndex, edgeAIndex, bIndex, edgeBIndex;
};

struct StuntAreas {
  StuntArea stuntAreas[32];
  uint8 numStuntAreas;
  StuntAreaWeldingInfo weldingInfos[64];
  uint8 numWeldingInfos;

  void Fixup(char *masterBuffer);
};

static_assert(sizeof(StuntAreas) == 13064, "Check assumptions");

class StuntAreas_wrap : public ADFInstance {
  StuntAreas *data;

  void Fixup(char *masterBuffer);

public:
  static constexpr auto GetHash() { return JenHash3(0x9327DF87); }

  StuntAreas_wrap(void *data_, ADFInternal *main_);
  StuntAreas *Data() { return data; }

  JenHash3 GetSuperClass() const { return -1; }
};
