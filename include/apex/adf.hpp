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
#include "datas/bincore_fwd.hpp"
#include "datas/pugi_fwd.hpp"
#include <memory>

class ADFInstance;
class StringHash;
class JenHash3;

struct ADFCPPGenSettings {
  char indentType = ' ';
  char numIndents = 2;
  bool enumClass = false;
  bool reflected = false;
};

class ADF {
public:
  using ptr = std::unique_ptr<ADF>;

  virtual void Load(BinReaderRef rd) = 0;
  virtual void LoadAsRenderBlockModel(BinReaderRef rd) = 0;
  virtual void SaveDefinitions(const std::string &fileName) const = 0;
  virtual void SaveDefinitions(pugi::xml_node node) const = 0;
  virtual void GenerateCPP(const std::string &fileName,
                           ADFCPPGenSettings settings) const = 0;
  virtual void GenerateCPP(std::ostream &str,
                           ADFCPPGenSettings settings) const = 0;
  virtual ADFInstance *FindInstance(JenHash3 hash, size_t numSkips = 0) = 0;
  virtual void AddInstance(std::unique_ptr<ADFInstance> &&instance,
                           const StringHash &hash) = 0;
  virtual ~ADF() = default;

  template <class C> C *FindInstance(size_t numSkips = 0) {
    return static_cast<C *>(FindInstance(C::GetHash(), numSkips));
  }
  template <class C> C *AddUniqueInstance();

  static ptr Create(const std::string &fileName);
};

template <class C> C *ADF::AddUniqueInstance() {
  C *foundInstance = FindInstance<C>();

  if (!foundInstance) {
    foundInstance = new C();
    AddInstance(foundInstance, C::HASH);
  }

  return foundInstance;
}
