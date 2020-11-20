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
#include "datas/flags.hpp"
#include "datas/pointer.hpp"

template <class C> struct AdfArray_Iterator {
  C *iterPos;

  AdfArray_Iterator(C *input) : iterPos(input) {}

  AdfArray_Iterator &operator++() {
    iterPos++;
    return *this;
  }
  AdfArray_Iterator operator++(int) {
    AdfArray_Iterator retval = *this;
    ++(*this);
    return retval;
  }
  bool operator==(AdfArray_Iterator input) const {
    return iterPos == input.iterPos;
  }
  bool operator!=(AdfArray_Iterator input) const {
    return iterPos != input.iterPos;
  }

  C &operator*() { return *iterPos; }
};

template <class C> struct AdfArray {
private:
  enum Flags_e : uint16 {
    F_DYNAMIC_ALLOC,
  };

public:
  typedef AdfArray_Iterator<C> iterator;

  esPointerX64<C> items;
  uint32 count;
  uint16 capacity;
  es::Flags<Flags_e> flags;

  iterator begin() { return iterator(items); }
  iterator end() { return iterator(items + count); }

  iterator begin() const { return iterator(items); }
  iterator end() const { return iterator(items + count); }

  C &operator[](const size_t index) { return items[index]; }

private:
  size_t capacity_() { return sizeof(C) * capacity; }
  size_t size_() { return sizeof(C) * count; }
  static const int nextCapacity = sizeof(C) * 4;

public:
  void Append(C &item) {
    if (count + 1 > capacity) {
      if (flags[F_DYNAMIC_ALLOC]) {
        void *oldPtr = items.vPtr;
        items.vPtr = realloc(oldPtr, size_() + nextCapacity);

        if (oldPtr != items.vPtr) {
          free(oldPtr);
        }
      } else {
        char *oldPtr = items.cPtr;
        items.vPtr = malloc(size_() + nextCapacity);
        memcpy(items.vPtr, oldPtr, size_());
        flags(F_DYNAMIC_ALLOC, true);
      }

      capacity = count + nextCapacity;
    }

    items[count++] = item;
  }

  void Merge(const AdfArray &arr) {
    const int arrSize = sizeof(C) * arr.count;

    if (arr.count + count > capacity) {
      if (flags[F_DYNAMIC_ALLOC]) {
        void *oldPtr = items;
        items = static_cast<C *>(realloc(oldPtr, size_() + arrSize));

        if (oldPtr != items) {
          free(oldPtr);
        }
      } else {
        C *oldPtr = items;
        items = static_cast<C *>(malloc(size_() + arrSize));
        memcpy(items, oldPtr, size_());
        flags += F_DYNAMIC_ALLOC;
      }

      capacity = arr.count + count;
    }

    memcpy(items + size_(), arr.items, arrSize);

    count += arr.count;
  }

  ~AdfArray() {
    if (items.vPtr && flags[F_DYNAMIC_ALLOC]) {
      free(items.vPtr);
    }
  }
};
