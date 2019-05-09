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
#include "ApexApi.h"
#include <string>

__declspec(align(8)) struct AdfArray
{
	int offset,
		unk01,
		count,
		unk02;
};

struct AdfBBOX
{
	Vector Min;
	Vector Max;
}; //0x8E31707

struct AdfDeferred
{
	int offset,
		unk;
	__int64	objectHash;
};

struct AdfProperties
{
	ApexHash typeHash;
	virtual void Load(BinReader *rd) = 0;
	virtual void Link(ADF *) {};
	virtual void *GetProperties() = 0;
	virtual ~AdfProperties() {}
	AdfProperties() : typeHash(0) {};
	static AdfProperties *ConstructProperty(ApexHash propHash);
};

struct StringHash
{
	std::string string;
	ApexHash hash;
	void Generate();
};

__declspec(align(8)) union AdfString
{
	uint offset;
	StringHash *str;
};

struct AdfHashString
{
	AdfString string;
	ApexHash hash;

	operator StringHash*() { return string.str; }
};

class BinReader;
class ADF;