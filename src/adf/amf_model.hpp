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
#include "apex/amf.hpp"

struct AmfModel_V1;
struct AmfMaterial_V1;
class ADFInstance;
class ADFInternal;

class AmfModel_V1_wrap : public AmfModel {
  AmfModel_V1 *data;
  ADFInternal *main;

  void Fixup(char *masterBuffer) override;
  es::string_view RequestsFile() const override;
  void Merge(ADFInstance *externalInstance) override {}

public:
  static constexpr auto GetHash() { return 0xF7C20A69; }

  AmfModel_V1_wrap(void *data_, ADFInternal *main_);

  AmfMaterial::Ptr GetMaterial(int id) const;

  JenHash3 GetSuperClass() const override { return AmfModel::GetHash(); }
  size_t GetNumMaterials() const override;
};
