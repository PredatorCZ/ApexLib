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
#include "datas/jenkinshash3.hpp"
#include "datas/pointer.hpp"
#include <functional>
#include <string>

struct ADFInternal;

struct AdfString {
  esPointerX64<char> string;
};

struct AdfHashString {
  AdfString string;
  JenHash3 hash;

  operator es::string_view() const { return es::string_view(string.string); }
  bool operator<(const AdfHashString &o) const { return hash < o.hash; }
  bool operator<(JenHash3 o) const { return hash < o; }
};

struct StringHash {
  mutable std::string string;
  JenHash3 hash;
  size_t index;

  StringHash() = default;
  explicit StringHash(JenHash3 ihsh, size_t index_ = 0)
      : hash(ihsh), index(index_) {}
  StringHash(const std::string &istr, size_t index_ = 0)
      : hash(istr), string(istr), index(index_) {}

  bool operator<(const StringHash &o) const { return hash < o.hash; }
  bool operator<(JenHash3 o) const { return hash < o; }
  bool operator<(size_t i) const { return index < i; }

  bool operator==(const StringHash &o) const { return o.hash == hash; }
  bool operator==(JenHash3 h) const { return h == hash; }

  bool operator!=(const StringHash &o) const { return !(*this == o); }
  bool operator!=(JenHash3 h) const { return !(*this == h); }

  friend bool operator<(size_t i, const StringHash &s) { return s.index > i; }
  friend bool operator<(JenHash3 h, const StringHash &s) { return s.hash > h; }
};

struct AdfExternalString {
  union {
    int64 externalIndex = 0;
    std::reference_wrapper<const StringHash> sh;
  };

  AdfExternalString() {}
  AdfExternalString(const StringHash &sh_) : sh(sh_) {}

  const StringHash &operator *() const { return sh.get(); }
  const StringHash *operator->() const { return &sh.get(); }

  void Fixup(ADFInternal &);
};
