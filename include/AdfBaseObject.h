/*  Apex Engine Format Library
	Copyright(C) 2014-2019 Lukas Cone

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
#include "datas/vectors.hpp"
#include "datas/flags.hpp"
#include "ApexApi.h"
#include <string>

template<class C> union AdfPointer
{
	C *ptr;
	char *cPtr;
	void *vPtr;
	int ptrVal;
	int64 fullPtr;

	void Fixup(char *masterBuffer) 
	{
		if (!ptrVal)
			return;

		cPtr = masterBuffer + ptrVal;
	}

	template<class _C = C>
	typename std::enable_if<!std::is_void<_C>::value, _C>::type &operator *() { return *ptr; }

	template<class _C = C>
	typename std::enable_if<std::is_void<_C>::value, void>::type operator *() {}

	template<class _C = C>
	typename std::enable_if<!std::is_void<_C>::value, _C>::type &operator [](const size_t index) { return ptr[index]; }

	template<class _C = C>
	typename std::enable_if<std::is_void<_C>::value, void>::type operator [](const size_t index) {}

	C *operator->() { return ptr; }
};

template<class C> struct AdfArray_Iterator
{
	C *iterPos;

	AdfArray_Iterator(C *input): iterPos(input) {}

	AdfArray_Iterator &operator++() { iterPos++; return *this; }
	AdfArray_Iterator operator++(int) { AdfArray_Iterator retval = *this; ++(*this); return retval; }
	bool operator==(AdfArray_Iterator input) const { return iterPos == input.iterPos; }
	bool operator!=(AdfArray_Iterator input) const { return iterPos != input.iterPos; }

	C &operator*() { return *iterPos; }
};

template<class C> struct alignas(8) AdfArray
{
private:
	enum Flags_e
	{
		F_DYNAMIC_ALLOC,
	};
public:
	typedef AdfArray_Iterator<C> iterator;

	AdfPointer<C> items;
	int count;
	short capacity;
	esFlags<short, Flags_e> flags;

	iterator begin() { return iterator(items.ptr); }
	iterator end() { return iterator(items.ptr + count); }

	C &operator [](const size_t index) { return items[index]; }
private:
	size_t _capacity() { return sizeof(C) * capacity; }
	size_t _size() { return sizeof(C) * count; }
	static const int nextCapacity = sizeof(C) * 4;
public:
	void Append(C &item)
	{
		if (count + 1 > capacity)
		{
			if (flags[F_DYNAMIC_ALLOC])
			{
				void *oldPtr = items.vPtr;
				items.vPtr = realloc(oldPtr, _size() + nextCapacity);

				if (oldPtr != items.vPtr)
					free(oldPtr);
			}
			else
			{
				char *oldPtr = items.cPtr;
				items.vPtr = malloc(_size() + nextCapacity);
				memcpy(items.vPtr, oldPtr, _size());
				flags(F_DYNAMIC_ALLOC, true);
			}

			capacity = count + nextCapacity;
		}

		items[count++] = item;
	}

	void Merge(const AdfArray &arr)
	{
		const int arrSize = sizeof(C) * arr.count;

		if (arr.count + count > capacity)
		{
			if (flags[F_DYNAMIC_ALLOC])
			{
				void *oldPtr = items.vPtr;
				items.vPtr = realloc(oldPtr, _size() + arrSize);

				if (oldPtr != items.vPtr)
					free(oldPtr);
			}
			else
			{
				char *oldPtr = items.cPtr;
				items.vPtr = malloc(_size() + arrSize);
				memcpy(items.vPtr, oldPtr, _size());
				flags(F_DYNAMIC_ALLOC, true);
			}

			capacity = arr.count + count;
		}

		memcpy(items.cPtr + _size(), arr.items.vPtr, arrSize);

		count += arr.count;
	}

	~AdfArray()
	{
		if (items.vPtr && flags[F_DYNAMIC_ALLOC])
			free(items.vPtr);
	}
};

struct AdfBBOX
{
	Vector Min;
	Vector Max;
}; //0x8E31707

struct alignas(8) AdfDeferred
{
	AdfPointer<void> item;
	ApexHash objectHash;

	Reflector *GetReflected() const;
	Reflector *GetReflected();

	template<class C> ES_FORCEINLINE C *GetItem() { return static_cast<C*>(item.ptr); }
};

struct StringHash
{
	std::string string;
	ApexHash hash;
	void Generate();
};

union alignas(8) AdfString
{
	uint offset;
	AdfPointer<char> string;
};

struct AdfHashString
{
	AdfString string;
	ApexHash hash;

	operator char*() { return string.string.cPtr; }
};