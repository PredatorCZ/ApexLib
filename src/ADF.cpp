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

#include <codecvt>
#include <algorithm>
#include <map>
#include "ADF.h"
#include "datas/binreader.hpp"
#include "pugixml.hpp"
#include "datas/esstring.h"
#include "datas/fileinfo.hpp"
#include "datas/MasterPrinter.hpp"
#include "lookup3.h"

#define ADFFOURCC 0x41444620

ADFInstance *ADF::FindInstance(ApexHash hash)
{
	for (auto &i : instances)
		if (i->typeHash == hash)
			return i->instance;

	return nullptr;
}

StringHash *ADF::AddStringHash(const char *input)
{
	ApexHash hash = JenkinsLookup3(input);
	StringHash *foundString = FindStringHash(hash);

	if (!foundString)
	{
		foundString = new StringHash();
		foundString->hash = hash;
		foundString->string = input;
		hashes.push_back(foundString);
	}

	return foundString;
}

std::string *ADF::FindString(ApexHash hash)
{
	for (auto &n : hashes)
		if (n->hash == hash)
			return &n->string;

	return nullptr;
}

StringHash * ADF::FindStringHash(ApexHash hash)
{
	for (auto &n : hashes)
		if (n->hash == hash)
			return n;

	return nullptr;
}

void ADF::AddInstance(ADFInstance *instance, ApexHash hash)
{
	ADF::Instance *cInstance = new ADF::Instance();
	cInstance->instance = instance;
	cInstance->typeHash = hash;
	instances.push_back(cInstance);
}

ADF::~ADF()
{
	for (auto &i : instances)
		delete i;

	for (auto &n : hashes)
		delete n;

	for (auto &n : names)
		delete n;
}

ADF::Descriptor::~Descriptor()
{
	if (descriptorData)
		delete descriptorData;
}

ADF::Instance::~Instance()
{
	if (instance)
		delete instance;
}

void StringHash::Generate()
{
	if (!string.size())
		return;
	hash = JenkinsLookup3(string.c_str());
}

/************************************************************************/
/***************************** LOADING **********************************/
/************************************************************************/

int ADF::DescriptorBase::Load(BinReader *rd, ADF *base)
{
	rd->Read(numMembers);
	return numMembers;
}

int ADF::DescriptorStructure::Load(BinReader *rd, ADF *base)
{
	DescriptorBase::Load(rd, base);
	members.resize(numMembers);

	for (auto &m : members)
	{
		rd->Read(m, offsetof(ADF::DescriptorStructure::Member, defValue) + 8 - offsetof(ADF::DescriptorStructure::Member, nameIndex));
		m.name = base->names[static_cast<size_t>(m.nameIndex)];
	}

	return 0;
}

int ADF::DescriptorExplicitEnum::Load(BinReader * rd, ADF * base)
{
	DescriptorBase::Load(rd, base);
	members.resize(numMembers);

	for (auto &m : members)
	{
		rd->Read(m, 12);
		m.name = base->names[static_cast<size_t>(m.nameIndex)];
	}

	return 0;
}

int ADF::Load(BinReader *rd, bool supressErrors)
{
	rd->SavePos();
	rd->Read(ID, offsetof(ADF, comment) - offsetof(ADF, ID));

	if (ID != ADFFOURCC)
	{
		if (!supressErrors)
		{
			printerror("Invalid ADF file.")
		}
		rd->RestorePos();
		return 1;
	}

	rd->ReadString(comment);

	if (hashesOffset)
	{
		rd->Seek(hashesOffset);
		hashes.resize(numHashes);

		for (auto &h : hashes)
		{
			h = new StringHash;
			rd->ReadString(h->string);
			rd->Read(h->hash);
			rd->Skip<int>();
		}
	}

	if (namesOffset)
	{
		rd->Seek(namesOffset + numNames);
		names.resize(numNames);

		for (auto &n : names)
		{
			n = new StringHash;
			rd->ReadString(n->string);
			n->Generate();
		}
	}

	if (definitionsOffset)
	{
		rd->Seek(definitionsOffset);
		descriptors.resize(numDefinitions);

		for (auto &i : descriptors)
		{
			int result = i.Load(rd, this);

			if (result)
			{
				printerror("[ADF] Could load descriptor: ",
					<< i.name->string.c_str() << " type: "
					<< (i.type < _EnumWrap<ADFDescriptorType>::_reflectedSize ? _EnumWrap<ADFDescriptorType>{}._reflected[i.type] : "Undefined"));
				break;
			}
		}
	}

	if (instancesOffset)
	{
		rd->Seek(instancesOffset);
		instances.resize(numInstances);

		for (auto &i : instances)
		{
			i = new Instance();
			rd->Read(*i, offsetof(ADF::Instance, nameIndex) + 8 - offsetof(ADF::Instance, nameHash));
			i->name = names[static_cast<size_t>(i->nameIndex)];
		}

		for (auto &i : instances)
		{
			const ApexHash typehash = i->typeHash;
			i->instance = ConstructInstance(typehash);

			if (i->instance)
			{
				rd->SetRelativeOrigin(i->offset);
				i->instance->Load(rd, this);
			}
			else
			{
				std::string *clname = nullptr;

				for (auto &d : descriptors)
					if (d.nameHash == typehash)
					{
						clname = &d.name->string;
						break;
					}

				printwarning("[ADF] Uregistered class: ",
					<< (clname ? esString(*clname) : _T(""))
					<< _T(" (0x") << std::hex << typehash << std::dec << ')'
				)
			}
		}

		rd->ResetRelativeOrigin();
	}

	return 0;
}

int ADF::Descriptor::Load(BinReader *rd, ADF *base)
{

	rd->Read(type, getBlockSize(ADF::Descriptor, type, elementSize));

	name = base->names[static_cast<size_t>(nameIndex)];

	if (type == ADFDescriptorType::Structure)
		descriptorData = new DescriptorStructure();
	else if (type == ADFDescriptorType::ExplicitEnumeration)
		descriptorData = new DescriptorExplicitEnum();
	else
		descriptorData = new DescriptorBase();

	return descriptorData->Load(rd, base);
}

template<class T>
IADF *CreateADF(const T *fileName)
{
	BinReader rd(fileName);
	ADF *adf = new ADF();

	if (!rd.IsValid())
	{
		printerror("Couldn't open file: ", << fileName);
		delete adf;
		return nullptr;
	}

	int evalError = 0;

	if (evalError = adf->Load(&rd, true))
	{
		if (evalError = adf->LoadAsRenderBlockModel(&rd, true))
		{
			if (evalError & 0xf)
			{
				printerror("Couldn't detect file: ", << fileName);
			}

			delete adf;
			return nullptr;
		}
	}

	_FileInfo_t<T> selfPath(fileName);

	typedef ADF::Instances_type::iterator insIt;

	for (insIt &it = adf->instances.begin(); it != adf->instances.end(); it++)
	{
		insIt::value_type &i = *it;

		if (!i->instance)
			continue;

		std::string *req = i->instance->RequestsFile();

		if (!req)
			continue;

		_FileInfo_t<T> reqPath(static_cast<UniString<T>>(esString(*req)));
		UniString<T> rPath = reqPath.CatchBranch(selfPath.GetPath());
		ADF *exAdf = static_cast<ADF *>(CreateADF(rPath.c_str()));

		if (exAdf)
		{
			for (auto &exi : exAdf->instances)
			{
				ADFInstance *exins = adf->FindInstance(exi->typeHash);

				if (exins)
				{
					exins->Merge(exi->instance);
				}
				else
				{
					it = adf->instances.insert(adf->instances.end(), exi);
					adf->names.insert(adf->names.end(), exi->name);
					std::remove(exAdf->names.begin(), exAdf->names.end(), exi->name);

					if (exAdf->names.size())
						exAdf->names.resize(exAdf->names.size() - 1);
				}
			}

			adf->hashes.insert(adf->hashes.end(), exAdf->hashes.begin(), exAdf->hashes.end());
			exAdf->hashes.clear();
			exAdf->instances.clear();
		}

		delete exAdf;
	}

	for (auto &i : adf->instances)
		if (i->instance)
			i->instance->Link(adf);

	return adf;
}

IADF *IADF::Create(const char *fileName)
{
	return CreateADF(fileName);
}

IADF *IADF::Create(const wchar_t *fileName)
{
#ifdef UNICODE
	return CreateADF(fileName);
#else
	return CreateADF(esStringConvert<char>(fileName).c_str());
#endif
}

/************************************************************************/
/******************************* XML ************************************/
/************************************************************************/

static const std::map<ApexHash, const char *> types = {
	{ 0x580D0A62, "char"},
	{ 0x0CA2821D, "uchar" },
	{ 0xD13FCF93, "short" },
	{ 0x86D152BD, "ushort" },
	{ 0x192FE633, "int" },
	{ 0x075E4E4F, "uint" },
	{ 0xAF41354F, "int64" },
	{ 0xA139E01F, "uint64" },
	{ 0x7515A207, "float" },
	{ 0xC609F663, "double" },
	{ 0x8955583E, "string" },
	{ 0xDEFE88ED, "deferred" },
	/*{ 0xC0C76FDA, "bitArray8" },
	{ 0x61FAD529, "bitArray16" },
	{ 0xF0587325, "bitArray32" },*/
};

int ADF::DumpDefinitions(pugi::xml_node &node) const
{
	pugi::xml_node &master = node.append_child("Definitions");

	for (auto &d : descriptors)
		d.XMLDump(&master);

	if (numInstances)
	{
		pugi::xml_node &instNode = node.append_child("Instances");

		for (auto &i : instances)
		{
			pugi::xml_node &subinstNode = instNode.append_child(i->name->string.c_str());
			subinstNode.append_attribute("hash").set_value(i->nameHash);

			std::string strTypename = std::to_string(i->typeHash);
			const char *typeName = strTypename.c_str();

			if (types.count(i->typeHash))
			{
				typeName = types.at(i->typeHash);
			}

			subinstNode.append_attribute("type").set_value(typeName);
			subinstNode.append_attribute("offset").set_value(i->offset);
			subinstNode.append_attribute("size").set_value(i->size);
		}
	}

	if (numHashes)
	{
		pugi::xml_node &hashNode = node.append_child("Strings");

		for (auto &h : hashes)
		{
			pugi::xml_node &substrNode = hashNode.append_child("String");
			substrNode.append_attribute("string").set_value(h->string.c_str());
			substrNode.append_attribute("hash").set_value(h->hash);
		}
	}

	return 0;
}

int ADF::DumpDefinitions(const char *fileName) const
{
	pugi::xml_document doc = {};
	DumpDefinitions(doc);

	if (!doc.save_file(fileName, "\t", pugi::format_write_bom | pugi::format_indent))
		printerror("[ADF] Couldn't save XML file: ", << fileName);

	return 0;
}

int ADF::DumpDefinitions(const wchar_t *fileName) const
{
	pugi::xml_document doc = {};
	DumpDefinitions(doc);

	if (!doc.save_file(fileName, "\t", pugi::format_write_bom | pugi::format_indent))
		printerror("[ADF] Couldn't save XML file: ", << fileName);

	return 0;
}

void ADF::DescriptorExplicitEnum::XMLDump(pugi::xml_node *master) const
{
	DescriptorBase::XMLDump(master);

	for (auto &m : members)
		master->append_child(m.name->string.c_str()).append_attribute("=").set_value(m.value);
}

void ADF::DescriptorStructure::XMLDump(pugi::xml_node *master) const
{
	DescriptorBase::XMLDump(master);

	for (auto &m : members)
	{
		pugi::xml_node &node = master->append_child(m.name->string.c_str());

		std::string strTypename = std::to_string(m.typeHash);
		const char *typeName = strTypename.c_str();

		if (types.count(m.typeHash))
		{
			typeName = types.at(m.typeHash);
		}

		node.append_attribute("type").set_value(typeName);
		node.append_attribute("offset").set_value(m.offset);
		node.append_attribute("size").set_value(m.size);
		node.append_attribute("bitOffset").set_value(m.bitOffset);
	}
}

void ADF::DescriptorBase::XMLDump(pugi::xml_node *master) const
{
	master->append_attribute("numMembers").set_value(numMembers);
}

void ADF::Descriptor::XMLDump(pugi::xml_node *master) const
{
	const char *_typeName = "Unknown";

	_EnumWrap<ADFDescriptorType> ewrap;

	if (type < ewrap._reflectedSize)
		_typeName = ewrap._reflected[type];

	pugi::xml_node &node = master->append_child(_typeName);
	node.append_attribute("type").set_value(nameHash);
	node.append_attribute("name").set_value(name->string.c_str());
	node.append_attribute("size").set_value(size);

	std::string strTypename = std::to_string(elementTypeHash);
	const char *typeName = strTypename.c_str();

	if (types.count(elementTypeHash))
	{
		typeName = types.at(elementTypeHash);
	}

	node.append_attribute("elementType").set_value(typeName);
	descriptorData->XMLDump(&node);
}