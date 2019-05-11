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
#include <vector>
#include "datas/reflector.hpp"
#include "AdfBaseObject.h"

namespace pugi 
{
	class xml_node;
};

REFLECTOR_ENUM(ADFDescriptorType,
	Primitive,
	Structure,
	Pointer,
	Array,
	InlineArray,
	String,
	BitField,
	Enumeration,
	ExplicitEnumeration)

class ADF : public IADF
{
public:
	struct Instance
	{
		ApexHash nameHash;
		ApexHash typeHash;
		int offset;
		int size;
		__int64 nameIndex;

		StringHash *name;
		ADFInstance *instance;
		~Instance();
	};

	struct DescriptorBase
	{
		int numMembers;
		virtual int Load(BinReader *rd, ADF *base);
		virtual void XMLDump(pugi::xml_node *master) const;
		virtual ~DescriptorBase() {}
	};

	struct DescriptorStructure : DescriptorBase
	{
		struct Member
		{
			__int64 nameIndex;
			ApexHash typeHash;
			int	size;
			short offset;
			char pad, bitOffset;
			ApexHash defType;
			__int64 defValue;

			StringHash *name;
		};
		std::vector<Member> members;
		int Load(BinReader *rd, ADF *base);
		void XMLDump(pugi::xml_node *master) const;
	};

	struct DescriptorExplicitEnum : DescriptorBase
	{
		struct Member 
		{
			__int64 nameIndex;
			int value;
			StringHash *name;
		};
		std::vector<Member> members;
		int Load(BinReader *rd, ADF *base);
		void XMLDump(pugi::xml_node *master) const;
	};


	struct Descriptor
	{
		ADFDescriptorType type;
		int size,
			allignemt;
		ApexHash nameHash;
		__int64 nameIndex;
		int flags;
		ApexHash elementTypeHash;
		int elementSize;

		StringHash *name;
		DescriptorBase *descriptorData;

		int Load(BinReader *rd, ADF *base);
		void XMLDump(pugi::xml_node *node) const;
		~Descriptor();
	};

	int ID;
	int version;
	int numInstances;
	int instancesOffset;
	int numDefinitions;
	int definitionsOffset;
	int numHashes;
	int hashesOffset;
	int numNames;
	int namesOffset;
	int fileSize;
	int null[5];
	std::string comment;

	std::vector<StringHash*> hashes;
	std::vector<StringHash*> names;
	typedef std::vector<Instance*> Instances_type;
	Instances_type instances;
	std::vector<Descriptor> descriptors;
public:
	int Load(BinReader *rd, bool supressErrors = false);
	int LoadAsRenderBlockModel(BinReader *rd, bool supressErrors = false);
	int DumpDefinitions(const char *fileName) const;
	int DumpDefinitions(const wchar_t *fileName) const;
	int DumpDefinitions(pugi::xml_node &node) const;
	ADFInstance *FindInstance(ApexHash hash);
	using IADF::FindInstance;
	StringHash *AddStringHash(const char* input);
	ES_FORCEINLINE StringHash *AddStringHash(const std::string input) { return AddStringHash(input.c_str()); }
	std::string *FindString(ApexHash hash);
	StringHash *FindStringHash(ApexHash hash);
	void AddInstance(ADFInstance *instance, ApexHash hash);
	~ADF();
	ADF();
	static ADFInstance *ConstructInstance(ApexHash classHash);
};