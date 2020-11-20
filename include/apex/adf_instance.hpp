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
#include "datas/string_view.hpp"

class ADFInternal;
class JenHash3;

struct ADFInstance {
  virtual void Fixup(char *) = 0;
  virtual es::string_view RequestsFile() const { return {}; }
  virtual void Merge(ADFInstance *externalInstance) {}
  virtual void ReplaceReferences(ADFInternal *newMain) {}
  virtual JenHash3 GetSuperClass() const = 0;
  virtual ~ADFInstance() = default;
};
