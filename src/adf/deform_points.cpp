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

#include "apex/deform_points.hpp"

void DeformPoint::Fixup(char *masterBuffer) {
  name.string.Fixup(masterBuffer);
  fromPart.string.Fixup(masterBuffer);
  skinnedToPart.string.Fixup(masterBuffer);
  deformPointType.string.string.Fixup(masterBuffer);
}

void DeformPoints::Fixup(char *masterBuffer) {
  points.items.Fixup(masterBuffer);
  constraintIndices.items.Fixup(masterBuffer);
  lightIndices.items.Fixup(masterBuffer);
  wheelIndices.items.Fixup(masterBuffer);
  nonDeformablePartsIndices.items.Fixup(masterBuffer);
  haulingHitchIndices.items.Fixup(masterBuffer);
  trailingHitchIndices.items.Fixup(masterBuffer);

  for (auto &p : points) {
    p.Fixup(masterBuffer);
  }
}

DeformPoints_wrap::DeformPoints_wrap(void *data_, ADFInternal *)
    : data(static_cast<DeformPoints *>(data_)) {}
void DeformPoints_wrap::Fixup(char *masterBuffer) { data->Fixup(masterBuffer); }
