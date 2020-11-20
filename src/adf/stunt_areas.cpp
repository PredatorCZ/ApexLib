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

#include "apex/stunt_areas.hpp"

void StuntArea::Fixup(char *masterBuffer) {
  name.string.Fixup(masterBuffer);
  partName.string.Fixup(masterBuffer);
}

void StuntAreas::Fixup(char *masterBuffer) {
  for (auto &s : stuntAreas) {
    s.Fixup(masterBuffer);
  }
}

StuntAreas_wrap::StuntAreas_wrap(void *data_, ADFInternal *)
    : data(static_cast<StuntAreas *>(data_)) {}
void StuntAreas_wrap::Fixup(char *masterBuffer) { data->Fixup(masterBuffer); }
