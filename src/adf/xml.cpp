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

#include "../adf.hpp"
#include "datas/pugiex.hpp"

const std::map<JenHash3, es::string_view> types = {
    {0x580D0A62, "int8"},      //
    {0x0CA2821D, "uint8"},     //
    {0xD13FCF93, "int16"},     //
    {0x86D152BD, "uint16"},    //
    {0x192FE633, "int32"},     //
    {0x075E4E4F, "uint32"},    //
    {0xAF41354F, "int64"},     //
    {0xA139E01F, "uint64"},    //
    {0x7515A207, "float"},     //
    {0xC609F663, "double"},    //
    {0x8955583E, "AdfString"}, //
    {0xDEFE88ED, "AdfDeferred"},
    /*{ 0xC0C76FDA, "bitArray8" },//
    { 0x61FAD529, "bitArray16" },//
    { 0xF0587325, "bitArray32" },*/
};

void ADFInternal::SaveDefinitions(pugi::xml_node node) const {
  pugi::xml_node master = node.append_child("definitions");

  for (auto &d : descriptors) {
    d.second.Save(master);
  }

  if (numHashes) {
    pugi::xml_node hashNode = node.append_child("strings");

    for (auto &h : hashes) {
      pugi::xml_node substrNode = hashNode.append_child("item");
      substrNode.append_buffer(h.string.data(), h.string.size());
      substrNode.append_attribute("hash").set_value(h.hash);
    }
  }

  if (numInstances) {
    pugi::xml_node instNode = node.append_child("instances");

    for (auto &i : instances) {
      pugi::xml_node subinstNode = instNode.append_child(i.name->string.data());
      subinstNode.append_attribute("hash").set_value(i.nameHash);

      std::string typeName = std::to_string(i.typeHash);

      if (types.count(i.typeHash)) {
        typeName = types.at(i.typeHash);
      }

      subinstNode.append_attribute("type").set_value(typeName.data());
    }
  }
}

void ADFInternal::SaveDefinitions(const std::string &fileName) const {
  pugi::xml_document doc = {};
  SaveDefinitions(doc);
  XMLToFile(fileName, doc);
}

void ADFDescriptorExplicitEnum::Save(pugi::xml_node node) const {
  ADFDescriptorBase::Save(node);

  for (auto &m : members) {
    node.append_child(m.name->string.data())
        .append_attribute("=")
        .set_value(m.value);
  }
}

void ADFDescriptorStructure::Save(pugi::xml_node node) const {
  ADFDescriptorBase::Save(node);

  for (auto &m : members) {
    pugi::xml_node memNode = node.append_child(m.name->string.data());
    std::string typeName = std::to_string(m.typeHash);

    if (types.count(m.typeHash)) {
      typeName = types.at(m.typeHash);
    }

    memNode.append_attribute("type").set_value(typeName.data());
    memNode.append_attribute("offset").set_value(m.offset);
    memNode.append_attribute("size").set_value(m.size);
    memNode.append_attribute("bitOffset").set_value(m.bitOffset);
    memNode.append_attribute("alignment").set_value(m.pad);
  }
}

void ADFDescriptorBase::Save(pugi::xml_node node) const {
  node.append_attribute("numMembers").set_value(numMembers);
}

void ADFDescriptor::Save(pugi::xml_node node) const {
  es::string_view typeName_ = "__unknown__";
  auto renum = GetReflectedEnum<ADFDescriptorType>();
  auto iType = static_cast<size_t>(type);

  if (iType < renum.size()) {
    typeName_ = renum[iType];
  }

  auto typeName__ = typeName_.to_string();
  pugi::xml_node typeNode = node.append_child(typeName__.data());
  typeNode.append_attribute("type").set_value(nameHash);
  typeNode.append_attribute("name").set_value(name->string.data());
  typeNode.append_attribute("size").set_value(size);

  std::string typeName = std::to_string(elementTypeHash);

  if (types.count(elementTypeHash)) {
    typeName = types.at(elementTypeHash);
  }

  node.append_attribute("elementType").set_value(typeName.data());
  polyData->Save(typeNode);
}
