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
#include "apex/adf_instance.hpp"
#include "datas/jenkinshash3.hpp"
#include "uni/model.hpp"

class Reflector;

enum AmfMeshRemapType {
  REMAP_TYPE_CHAR,
  REMAP_TYPE_SHORT,
  REMAP_TYPE_INT,
  REMAP_TYPE_SPRITE, // Vector3
};

class AmfMesh : public uni::List<uni::Primitive> {
public:
  using Ptr = uni::Element<AmfMesh>;

  virtual size_t GetNumTotalIndices() const = 0;
  virtual const std::string &GetMeshTypeName() const = 0;
  virtual bool IsValid() const = 0;
  virtual AmfMeshRemapType GetRemapType() const = 0;
  virtual size_t GetNumRemaps() const = 0;
  virtual size_t GetRemap(size_t id) const = 0;
  virtual const void *GetRemaps() const = 0;
  // virtual JenHash3 GetPropertyHash() const = 0;

  template <class C> C *GetRemapsAs() const {
    return reinterpret_cast<C *>(GetRemaps());
  }
};

class AmfMeshHeader : public ADFInstance {
public:
  using Ptr = uni::Element<AmfMeshHeader>;

  static constexpr auto GetHash() { return JenHash3("AmfMeshHeader"); }

  virtual size_t GetNumLODs() const = 0;
  virtual size_t GetLodIndex(size_t id) const = 0;
  virtual size_t GetNumLODMeshes(size_t LODIndex) const = 0;
  virtual AmfMesh::Ptr GetLODMesh(size_t LODIndex, size_t meshIndex) const = 0;
};

enum AmfMaterialType { MaterialType_Traditional, MaterialType_PBR };

class AmfMaterial {
public:
  using Ptr = uni::Element<AmfMaterial>;
  using refptr = std::unique_ptr<const Reflector>;

  virtual AmfMaterialType MaterialType() const = 0;
  virtual void MaterialType(AmfMaterialType ntype) = 0;
  virtual const std::string &GetName() const = 0;
  virtual const std::string &GetRenderBlockName() const = 0;
  virtual JenHash3 GetNameHash() const = 0;
  virtual JenHash3 GetRenderBlockNameHash() const = 0;
  virtual refptr GetReflectedAttributes() const = 0;
  virtual void *GetRawAttributes() const = 0;
  virtual JenHash3 GetAttributesHash() const = 0;
  virtual size_t GetNumTextures() const = 0;
  virtual const std::string &GetTexture(size_t id) const = 0;

  template <class C> C *GetAttributes() const {
    return static_cast<C *>(GetRawAttributes());
  }

  virtual ~AmfMaterial() = default;
};

class AmfModel : public ADFInstance {
public:
  using Ptr = uni::Element<AmfModel>;
  static constexpr auto GetHash() { return JenHash3("AmfModel"); }

  virtual size_t GetNumMaterials() const = 0;
  virtual AmfMaterial::Ptr GetMaterial(size_t id) const = 0;
};
