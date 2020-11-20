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

struct AmfMeshHeader_V1;
struct AmfMeshHeader_V2;
struct AmfMeshBuffers_V1;
struct AmfMeshBuffers_V1_5;
struct AmfMeshBuffers_V2;
class AmfMeshBuffers;
class ADFInternal;

class AmfMeshHeader_V1_wrap : public AmfMeshHeader {
  AmfMeshHeader_V1 *data;
  ADFInternal *main;
  mutable AmfMeshBuffers *buffers;

public:
  static constexpr auto GetHash() { return JenHash3(0xEA60065D); }

  AmfMeshHeader_V1_wrap(void *data_, ADFInternal *main_);
  size_t GetNumLODs() const override;
  size_t GetLodIndex(size_t id) const override;
  size_t GetNumLODMeshes(size_t LODIndex) const override;
  AmfMesh::Ptr GetLODMesh(size_t LODIndex, size_t meshIndex) const override;
  void Fixup(char *masterBuffer) override;
  es::string_view RequestsFile() const override;
  void ReplaceReferences(ADFInternal *newMain) override;
  JenHash3 GetSuperClass() const override { return AmfMeshHeader::GetHash(); }
};

class AmfMeshHeader_V2_wrap : public AmfMeshHeader {
  AmfMeshHeader_V2 *data;
  ADFInternal *main;
  mutable AmfMeshBuffers_V2 *buffers[2];

public:
  static constexpr auto GetHash() { return JenHash3(0x7A2C9B73); }

  AmfMeshHeader_V2_wrap(void *data_, ADFInternal *main_);
  size_t GetNumLODs() const override;
  size_t GetLodIndex(size_t id) const override;
  size_t GetNumLODMeshes(size_t LODIndex) const override;
  AmfMesh::Ptr GetLODMesh(size_t LODIndex, size_t meshIndex) const override;
  void Fixup(char *masterBuffer) override;
  es::string_view RequestsFile() const override;
  void ReplaceReferences(ADFInternal *newMain) override;
  JenHash3 GetSuperClass() const override { return AmfMeshHeader::GetHash(); }
};

class AmfMeshBuffers : public ADFInstance {
public:
  static constexpr auto GetHash() { return JenHash3(0x67B3A453); }

  virtual char *GetVertexBuffer(size_t id) const = 0;
  virtual char *GetIndexBuffer(size_t id) const = 0;
  virtual size_t GetNumIndexBuffers() const = 0;
  virtual size_t GetNumVertexBuffers() const = 0;
};

class AmfMeshBuffers_V1_wrap : public AmfMeshBuffers {
  AmfMeshBuffers_V1 *data;

  void Fixup(char *masterBuffer) override;
  void Merge(ADFInstance *externalInstance) override;

public:
  AmfMeshBuffers_V1_wrap(void *data_, ADFInternal *main_);
  AmfMeshBuffers_V1 *Data() { return data; }

  JenHash3 GetSuperClass() const override { return -1; }
  char *GetVertexBuffer(size_t id) const override;
  char *GetIndexBuffer(size_t id) const override;
  size_t GetNumIndexBuffers() const override;
  size_t GetNumVertexBuffers() const override;
};

class AmfMeshBuffers_V1_5_wrap : public AmfMeshBuffers {
  AmfMeshBuffers_V1_5 *data;

  void Fixup(char *masterBuffer) override;

public:
  static constexpr auto GetHash() { return JenHash3(0xe6834477); }

  AmfMeshBuffers_V1_5_wrap(void *data_, ADFInternal *main_);
  AmfMeshBuffers_V1_5 *Data() { return data; }

  JenHash3 GetSuperClass() const override { return AmfMeshBuffers::GetHash(); }
  char *GetVertexBuffer(size_t id) const override;
  char *GetIndexBuffer(size_t id) const override;
  size_t GetNumIndexBuffers() const override;
  size_t GetNumVertexBuffers() const override;
};

class AmfMeshBuffers_V2_wrap : public ADFInstance {
  AmfMeshBuffers_V2 *data01, *data02;

  void Fixup(char *masterBuffer) override;
  void Merge(ADFInstance *externalInstance) override;

public:
  static constexpr auto GetHash() { return JenHash3(0xE1C0800); }

  AmfMeshBuffers_V2_wrap(void *data_, ADFInternal *main_);
  AmfMeshBuffers_V2 *Data01() { return data01; }
  AmfMeshBuffers_V2 *Data02() { return data02; }

  JenHash3 GetSuperClass() const override { return -1; }
};
