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

#include "AVTX.h"
#include "datas/binreader.hpp"
#include "datas/except.hpp"
#include "datas/master_printer.hpp"
#include "datas/tchar.hpp"

AVTX::~AVTX() {
  if (buffer) {
    free(buffer);
  }
}

size_t AVTX::BufferSize() const {
  size_t fullSize = 0;

  for (auto &e : entries) {
    if (e.flags[Entry::Flag::Used]) {
      fullSize += e.size;
    }
  }

  return fullSize;
}

void AVTX::Load(const std::string &fileName, BinReaderRef rd, bool noBuffers) {
  rd.Read(*this);

  if (magic != ID) {
    throw es::InvalidHeaderError(magic);
  }

  buffer = nullptr;

  if (noBuffers) {
    return;
  }

  uint8 externalCollection = 0;

  for (auto &e : entries) {
    if (e.flags[Entry::Flag::Used]) {
      externalCollection |= 1 << e.externalID;
    }
  }

  size_t lastDot = fileName.find_last_of('.');

  if (lastDot == fileName.npos) {
    printwarning(
        "[AVTX] Invalid file extension, external buffers won't be read.");

    buffer = static_cast<char *>(malloc(entries[0].size));
    rd.ReadBuffer(buffer, entries[0].size);

    if (externalCollection > 1) {
      for (auto &e : entries)
        if (e.externalID) {
          width /= 2;
          height /= 2;
        }
    }

    return;
  }

  std::ifstream ioBuffs[7];

  for (size_t t = 1; t < numEntries; t++) {
    const uint32 externalMask = (1 << t);
    const bool possibleLegacy = (t == 1 && externalCollection == 3);

    if (!(externalCollection & externalMask)) {
      continue;
    }

    auto externalName = fileName.substr(0, lastDot);
    std::ifstream &currentBuffer = ioBuffs[t - 1];
    currentBuffer.setstate(std::ios::failbit);

    if (possibleLegacy) {
      auto externalName_ = externalName + ".hmddsc";
      currentBuffer.open(ToTSTRING(externalName_),
                         std::ios::in | std::ios::binary);
    }

    if (currentBuffer.fail()) {
      auto externalName_ = externalName + ".atx" + std::to_string(t);
      currentBuffer.open(ToTSTRING(externalName_),
                         std::ios::in | std::ios::binary);
    }

    if (currentBuffer.fail()) {
      if (possibleLegacy) {
        printwarning("[AVTX] Couldn't load external buffer for: "
                     << fileName << " (hmddsc or atx1).");
      } else {
        printwarning("[AVTX] Couldn't load external buffer: " << externalName);
      }
    }
  }

  // Compute buffer size, tier 1
  Entry *lastKnownMipEntry = entries;
  Entry *lastEntry = entries + numEntries - 1;
  size_t totalBufferSize = 0;
  mipCount = headerMipCount;

  for (auto &e : entries) {
    if (e.flags[Entry::Flag::Used]) {
      if (!e.externalID) {
        totalBufferSize += e.size;
      } else {
        if (ioBuffs[e.externalID - 1].fail()) {
          e.flags -= Entry::Flag::Used;
          continue;
        }

        mipCount++;
        totalBufferSize += e.size;
        lastKnownMipEntry = &e;
      }
    }
  }

  for (Entry *e = std::next(lastKnownMipEntry); e != lastEntry; e++) {
    if (e->size) {
      width /= 2;
      height /= 2;
    }
  }

  // Sequencial error handle, tier 2
  size_t currentBufferPos = 0;

  for (Entry *e = lastKnownMipEntry; e >= entries; e--) {
    if (e->flags[Entry::Flag::Used]) {
      continue;
    }

    buffer = static_cast<char *>(malloc(lastKnownMipEntry->size));

    if (!lastKnownMipEntry->externalID) {
      rd.ReadBuffer(buffer, lastKnownMipEntry->size);
    } else {
      std::ifstream &currentBuffer = ioBuffs[lastKnownMipEntry->externalID - 1];
      currentBuffer.seekg(lastKnownMipEntry->offset);
      currentBuffer.read(buffer, lastKnownMipEntry->size);
    }

    for (Entry *e = std::next(lastKnownMipEntry); e != lastEntry; e++) {
      if (e->size) {
        width /= 2;
        height /= 2;
      }
    }

    currentBufferPos = lastKnownMipEntry->size;
    memset(entries, 0, sizeof(Entry) * numEntries);
    entries[0].size = currentBufferPos;
    entries[0].flags += Entry::Flag::Used;
    mipCount = 1;
    headerMipCount = 1;

    return;
  }

  buffer = static_cast<char *>(malloc(totalBufferSize));

  for (Entry *e = lastEntry; e >= entries; e--) {
    if (e->flags[Entry::Flag::Used]) {
      if (!e->externalID) {
        e->offset = currentBufferPos;
        rd.ReadBuffer(buffer + currentBufferPos, e->size);
        currentBufferPos += e->size;
        continue;
      }

      std::ifstream &currentBuffer = ioBuffs[e->externalID - 1];
      currentBuffer.seekg(e->offset);
      currentBuffer.read(buffer + currentBufferPos, e->size);
      e->offset = currentBufferPos;
      currentBufferPos += e->size;
    }
  }

  return;
}

void AVTX::Load(const std::string &fileName, bool noBuffers) {
  BinReader rd(fileName);

  if (!rd.IsValid()) {
    throw es::FileNotFoundError(fileName);
  }

  Load(fileName, rd, noBuffers);
}
