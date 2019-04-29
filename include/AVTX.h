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
#include "datas/flags.hpp"
#include "datas/esstring.h"

class BinReader;

struct AVTX
{
	static const int ID = CompileFourCC("AVTX");
	static const int numEntries = 8;

	struct Entry
	{
		enum Flags
		{
			Flag_Used = 4,
		};

		int offset,
			size;
		esFlags<short, Flags> flags;
		uchar _pad,
			externalID;
	};

	enum Flags
	{
		Flag_ExternalBuffers = 0,
		Flag_NoTiling = 3,
		Flag_CubeMap = 6,
	};

	int magic;
	short version;
	uchar group; // title dependent texture grouping, (structure, weapon, character, effect, etc...)
	uchar dimension;
	int format;
	ushort width,
		height,
		numArrayElements;
	esFlags<ushort, Flags> flags;
	uchar mipCount,
		headerMipCount;
	ushort _pad;
	_declspec(align(8)) char *buffer;

	Entry entries[numEntries];
	
	int Load(const char *fileName, bool noBuffers = false);
	int Load(const wchar_t *fileName, bool noBuffers = false);
	int Load(const char *fileName, BinReader *rd, bool noBuffers = false);
	int Load(const wchar_t *fileName, BinReader *rd, bool noBuffers = false);

	int BufferSize() const;
	
	AVTX() : magic(ID), version(1), group(0), dimension(2), numArrayElements(1), buffer(nullptr), headerMipCount(0), entries(), _pad(0) {}
	~AVTX();

private:
	template<class _Ty0>
	//typedef wchar_t _Ty0;
	int _Load(const _Ty0 *fileName, BinReader *rd, bool noBuffers = false);
	template<class _Ty1>
	//typedef wchar_t _Ty1;
	int _Load(const _Ty1 *fileName, bool noBuffers = false);
};

static_assert(sizeof(AVTX) == 128, "Check assumptions");