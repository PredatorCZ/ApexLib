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

#include "amf_model.hpp"
#include "adf.hpp"
#include "amf_model_v1.hpp"

class AmfMaterial_V1_wrap : public AmfMaterial {
  AmfMaterial_V1 *data;
  ADFInternal *main;

public:
  AmfMaterial_V1_wrap(AmfMaterial_V1 *data_, ADFInternal *main_)
      : data(data_), main(main_) {}

  AmfMaterialType MaterialType() const override {
    return static_cast<AmfMaterialType>(data->attributes.hiddenData);
  }
  void MaterialType(AmfMaterialType ntype) override {
    data->attributes.hiddenData = ntype;
  }
  const std::string &GetName() const override {
    return main->FindString(data->name);
  }
  const std::string &GetRenderBlockName() const override {
    return main->FindString(data->renderBlockID);
  }
  JenHash3 GetNameHash() const override { return data->name; }
  JenHash3 GetRenderBlockNameHash() const override {
    return data->renderBlockID;
  }
  refptr GetReflectedAttributes() const override {
    return data->attributes.GetReflected();
  }
  void *GetRawAttributes() const override { return data->attributes.item; }
  JenHash3 GetAttributesHash() const override {
    return data->attributes.objectHash;
  }
  size_t GetNumTextures() const override { return data->textures.count; }
  const std::string &GetTexture(size_t id) const override {
    return main->FindString(data->textures[id]);
  }
};

void AmfModel_V1_wrap::Fixup(char *masterBuffer) { data->Fixup(masterBuffer); }

es::string_view AmfModel_V1_wrap::RequestsFile() const {
  return main->FindString(data->meshPath);
}

size_t AmfModel_V1_wrap::GetNumMaterials() const {
  return data->materials.count;
}

AmfMaterial::Ptr AmfModel_V1_wrap::GetMaterial(int id) const {
  auto made = std::make_unique<AmfMaterial_V1_wrap>(&data->materials[id], main);
  return {made.release(), true};
}

AmfModel_V1_wrap::AmfModel_V1_wrap(void *data_, ADFInternal *main_)
    : data(static_cast<AmfModel_V1 *>(data_)), main(main_) {}
