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
#include "datas/binreader_stream.hpp"
#include "datas/flags.hpp"
#include "datas/pointer.hpp"

struct AVTX {
  static constexpr uint32 ID = CompileFourCC("AVTX");
  static constexpr size_t numEntries = 8;

  struct Entry {
    enum class Flag : uint16 {
      Used = 4,
    };

    uint32 offset, size;
    es::Flags<Flag> flags;
    uint8 pad_, externalID;
  };

  enum class Flag : uint16 {
    ExternalBuffers = 0,
    NoTiling = 3,
    CubeMap = 6,
  };

  uint32 magic;
  uint16 version;
  uint8 group; // title dependent texture grouping, (structure, weapon,
               // character, effect, etc...)
  uint8 dimension;
  uint32 format;
  uint16 width, height, numArrayElements;
  es::Flags<Flag> flags;
  uint8 mipCount, headerMipCount;
  esPointerX64<char> buffer;
  Entry entries[numEntries];

  void Load(const std::string &fileName, bool noBuffers = false);
  void Load(const std::string &fileName, BinReaderRef rd,
            bool noBuffers = false);

  size_t BufferSize() const;

  AVTX()
      : magic(ID), version(1), group(), dimension(2), numArrayElements(1),
        buffer(), headerMipCount(), entries() {}
  ~AVTX();
};

static_assert(sizeof(AVTX) == 128, "Check assumptions");
