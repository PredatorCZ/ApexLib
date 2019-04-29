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
#include <xstring>
#include "datas/supercore.hpp"
class BinReader;
class ADF;

typedef unsigned int ApexHash;

struct ADFInstance
{
	virtual int Load(BinReader *rd, ADF *linker) = 0;
	virtual void Link(ADF *linker) = 0;
	virtual std::string *RequestsFile() = 0;
	virtual void Merge(ADFInstance *externalInstance) = 0;
	virtual ~ADFInstance() {};
};

class IADF
{
public:
	virtual int Load(BinReader *rd, bool supressErrors = false) = 0;
	virtual int LoadAsRenderBlockModel(BinReader *rd, bool supressErrors = false) = 0;
	virtual int DumpDefinitions(const char *fileName) const = 0;
	virtual int DumpDefinitions(const wchar_t *fileName) const = 0;
	virtual ADFInstance *FindInstance(ApexHash hash) = 0;
	virtual ~IADF() {};
	template<class C> ES_FORCEINLINE C *FindInstance() { return static_cast<C*>(FindInstance(C::HASH)); }
	template<class C> ES_FORCEINLINE C *AddUniqueInstance();
	virtual void AddInstance(ADFInstance *instance, ApexHash hash) = 0;
	static IADF *Create(const char *fileName);
	static IADF *Create(const wchar_t *fileName);
};

template<class C>
ES_INLINE C *IADF::AddUniqueInstance()
{
	C *foundInstance = FindInstance<C>();

	if (!foundInstance)
	{
		foundInstance = new C();
		AddInstance(foundInstance, C::HASH);
	}

	return foundInstance;
}
