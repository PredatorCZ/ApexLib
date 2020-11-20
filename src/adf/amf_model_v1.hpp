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
#include "apex/adf_deferred.hpp"
#include "apex/adf_array.hpp"

struct AmfMaterial_V1 {
  JenHash3 name;
  JenHash3 renderBlockID;
  AdfDeferred attributes;
  AdfArray<JenHash3> textures;

  void Fixup(char *masterBuffer) {
    attributes.item.Fixup(masterBuffer);
    textures.items.Fixup(masterBuffer);
  }
};

struct AmfModel_V1 {
  JenHash3 meshPath;
  AdfArray<uint8> lodSlots;
  uint32 memoryTag;
  float lodFactor;
  AdfArray<AmfMaterial_V1> materials;

  void Fixup(char *masterBuffer) {
    lodSlots.items.Fixup(masterBuffer);
    materials.items.Fixup(masterBuffer);

    for (auto &m : materials) {
      m.Fixup(masterBuffer);
    }
  }
};
