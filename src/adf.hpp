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
#include "apex/adf.hpp"
#include "apex/adf_instance.hpp"
#include "apex/adf_string.hpp"
#include "datas/reflector.hpp"
#include <list>
#include <set>
#include <vector>
#include <map>

struct ADFDescriptor;
struct ADFInternal;
struct CPPSettingsInternal;

REFLECTOR_CREATE(ADFDescriptorType, ENUM, 1, CLASS, Primitive, Structure,
                 Pointer, Array, InlineArray, String, UnknownType, BitField,
                 Enumeration, StringHash)

struct ADFInstanceInternalData {
  JenHash3 nameHash;
  JenHash3 typeHash;
  uint32 offset;
  uint32 size;
  AdfExternalString name;

  ADFInstanceInternalData() = default;
  ADFInstanceInternalData(const StringHash &sh) : name(sh) {}
};

class ADFInstanceInternal : public ADFInstanceInternalData {
public:
  using ptr = std::unique_ptr<ADFInstanceInternal>;
  std::unique_ptr<ADFInstance> instance;
  std::string instanceBuffer;

  ADFInstanceInternal() = default;
  ADFInstanceInternal(const StringHash &sh, decltype(instance) &&instance_)
      : ADFInstanceInternalData(sh), instance(std::move(instance_)) {}
};

struct ADFDescriptorBase {
  uint32 numMembers;
  virtual void Load(BinReaderRef rd, ADFInternal &base);
  virtual void Save(pugi::xml_node node) const;
  virtual void Save(const ADFDescriptor *main, CPPSettingsInternal &classes) const;
  virtual ~ADFDescriptorBase() {}
};

struct ADFDescriptorStructure : ADFDescriptorBase {
  struct Member {
    AdfExternalString name;
    JenHash3 typeHash;
    uint32 size;
    uint16 offset;
    uint8 pad, bitOffset;
    JenHash3 defType;
    int64 defValue;
  };

  std::vector<Member> members;
  void Load(BinReaderRef rd, ADFInternal &base);
  void Save(pugi::xml_node node) const;
  void Save(const ADFDescriptor *main, CPPSettingsInternal &classes) const;
};

struct ADFDescriptorExplicitEnum : ADFDescriptorBase {
  struct Member {
    AdfExternalString name;
    uint32 value;
  };

  std::vector<Member> members;
  void Load(BinReaderRef rd, ADFInternal &base);
  void Save(pugi::xml_node node) const;
  void Save(const ADFDescriptor *main, CPPSettingsInternal &classes) const;
};

struct ADFDescriptorData {
  ADFDescriptorType type;
  uint32 size, allignemt;
  JenHash3 nameHash;
  AdfExternalString name;
  uint32 flags;
  JenHash3 elementTypeHash;
  uint32 elementSize;
};

struct ADFDescriptor : ADFDescriptorData {
  using base_ptr = std::unique_ptr<ADFDescriptorBase>;

  ADFInternal &main;
  base_ptr polyData;

  ADFDescriptor(ADFInternal &main_) : main(main_) {}

  void Load(BinReaderRef rd);
  void Save(pugi::xml_node node) const;
  void Save(CPPSettingsInternal &classes) const;
};

struct ADFData {
  uint32 ID;
  uint32 version;
  uint32 numInstances;
  uint32 instancesOffset;
  uint32 numDefinitions;
  uint32 definitionsOffset;
  uint32 numHashes;
  uint32 hashesOffset;
  uint32 numNames;
  uint32 namesOffset;
  uint32 fileSize;
  uint32 null[5];
};

class ADFInternal : public ADF, public ADFData {
public:
  std::string comment;

  std::set<StringHash, std::less<>> hashes;
  std::set<StringHash, std::less<>> names;
  std::list<ADFInstanceInternal> instances;
  std::map<JenHash3, ADFDescriptor> descriptors;

public:
  void Load(BinReaderRef rd) override;
  void LoadAsRenderBlockModel(BinReaderRef rd) override;
  void SaveDefinitions(const std::string &fileName) const override;
  void SaveDefinitions(pugi::xml_node node) const override;
  void GenerateCPP(const std::string &fileName,
                   ADFCPPGenSettings settings) const override;
  void GenerateCPP(std::ostream &str,
                   ADFCPPGenSettings settings) const override;
  ADFInstance *FindInstance(JenHash3 hash, size_t numSkips = 0) override;
  void AddInstance(std::unique_ptr<ADFInstance> &&instance,
                   const StringHash &hash) override;

  ADFInstanceInternal *FindRawInstance(JenHash3 hash, size_t numSkips = 0);
  using ADF::FindInstance;
  const StringHash &AddStringHash(es::string_view input);
  const std::string &FindString(JenHash3 hash);
  const StringHash &FindStringHash(JenHash3 hash);

  ADFInternal();

  std::unique_ptr<ADFInstance> ConstructInstance(JenHash3 classHash,
                                                 void *data);
  bool InstanceContructoreExits(JenHash3 classHash);
};
