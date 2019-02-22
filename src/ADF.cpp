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

#include "ADF.h"
#include "datas/binreader.hpp"
#include "pugixml.hpp"
#include "AdfRegistry.h"
#include "datas/esstring.h"
#include "datas/fileinfo.hpp"
#include "datas/MasterPrinter.hpp"
#include <algorithm>
#include "lookup3.h"

#define ADFFOURCC 0x41444620

std::map<ApexHash, const char*> types = {
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

int ADF::Load(BinReader * rd, bool supressErrors)
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
					<< esString(i.name->string) << _T(" type: ")
					<< (i.type < i.Type_e_reflectedSize ? esString(i.Type_e_reflected[i.type]) : _T("Undefined")));
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
			i = new Instance;
			rd->Read(*i, offsetof(ADF::Instance, nameIndex) + 8 - offsetof(ADF::Instance, nameHash));
			i->name = names[static_cast<size_t>(i->nameIndex)];
		}

		for (auto &i : instances)
		{
			const ApexHash typehash = i->typeHash;

			if (ADFClassStorage.count(typehash))
			{
				i->instance = ADFClassStorage[typehash]();
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

int ADF::DumpDefinitions(const wchar_t * fileName)
{
	pugi::xml_document doc = {};
	pugi::xml_node &master = doc.append_child("Definitions");

	for (auto &d : descriptors)
		d.XMLDump(&master);

	if (numInstances)
	{
		pugi::xml_node &instNode = doc.append_child("Instances");

		for (auto &i : instances)
		{
			pugi::xml_node &subinstNode = instNode.append_child(i->name->string.c_str());
			subinstNode.append_attribute("hash").set_value(std::to_string(i->nameHash).c_str());
			
			std::string strTypename = std::to_string(i->typeHash);
			const char *typeName = strTypename.c_str();

			if (types.count(i->typeHash))
			{
				typeName = types[i->typeHash];
			} 
			
			subinstNode.append_attribute("type").set_value(typeName);
			subinstNode.append_attribute("offset").set_value(std::to_string(i->offset).c_str());
			subinstNode.append_attribute("size").set_value(std::to_string(i->size).c_str());
		}
	}

	if (numHashes)
	{
		pugi::xml_node &hashNode = doc.append_child("Strings");

		for (auto &h : hashes)
		{
			pugi::xml_node &substrNode = hashNode.append_child("String");
			substrNode.append_attribute("string").set_value(h->string.c_str());
			substrNode.append_attribute("hash").set_value(std::to_string(h->hash).c_str());
		}
	}

	doc.save_file(fileName, "\t", pugi::format_write_bom | pugi::format_indent);
	return 0;
}

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

std::string * ADF::FindString(ApexHash hash)
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

int ADF::Descriptor::Load(BinReader * rd, ADF *base)
{

	rd->Read(type, offsetof(ADF::Descriptor, elementSize) + 4 - offsetof(ADF::Descriptor, type));

	name = base->names[static_cast<size_t>(nameIndex)];

	if (type == Type_e::Structure)
		descriptorData = new DescriptorStructure();
	else if (type == Type_e::ExplicitEnumeration)
		descriptorData = new DescriptorExplicitEnum();
	else
		descriptorData = new DescriptorBase();

	return descriptorData->Load(rd, base);
}


#define xmlAppAttr(_name_) append_attribute(#_name_).set_value(std::to_string(_name_).c_str());

void ADF::Descriptor::XMLDump(pugi::xml_node * master)
{
	const char *_typeName = "Unknown";

	if (type < Type_e_reflectedSize)
		_typeName = Type_e_reflected[type];

	pugi::xml_node &node = master->append_child(_typeName);
	node.append_attribute("type").set_value(std::to_string(nameHash).c_str());
	node.append_attribute("name").set_value(name->string.c_str());
	node.append_attribute("size").set_value(std::to_string(size).c_str());

	std::string strTypename = std::to_string(elementTypeHash);
	const char *typeName = strTypename.c_str();

	if (types.count(elementTypeHash))
	{
		typeName = types[elementTypeHash];
	}

	node.append_attribute("elementType").set_value(typeName);
	descriptorData->XMLDump(&node);
}

ADF::Descriptor::~Descriptor()
{
	if (descriptorData)
		delete descriptorData;
}

int ADF::DescriptorBase::Load(BinReader * rd, ADF *base)
{
	rd->Read(numMembers);
	return numMembers;
}

void ADF::DescriptorBase::XMLDump(pugi::xml_node * master)
{
	master->xmlAppAttr(numMembers);
}

int ADF::DescriptorStructure::Load(BinReader * rd, ADF *base)
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

void ADF::DescriptorStructure::XMLDump(pugi::xml_node * master)
{
	DescriptorBase::XMLDump(master);

	for (auto &m : members)
	{
		pugi::xml_node &node = master->append_child(m.name->string.c_str());

		std::string strTypename = std::to_string(m.typeHash);
		const char *typeName = strTypename.c_str();

		if (types.count(m.typeHash))
		{
			typeName = types[m.typeHash];
		}

		node.append_attribute("type").set_value(typeName);
		node.append_attribute("offset").set_value(std::to_string(m.offset).c_str());
		node.append_attribute("size").set_value(std::to_string(m.size).c_str());
		node.append_attribute("bitOffset").set_value(std::to_string(m.bitOffset).c_str());
	}


}

int ADF::DescriptorExplicitEnum::Load(BinReader * rd, ADF *base)
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

void ADF::DescriptorExplicitEnum::XMLDump(pugi::xml_node * master)
{
	DescriptorBase::XMLDump(master);

	for (auto &m : members)
		master->append_child(m.name->string.c_str()).append_attribute("=").set_value(std::to_string(m.value).c_str());
}

IADF *IADF::Create(const wchar_t *filePath)
{
	BinReader rd(filePath);
	ADF *adf = new ADF();

	if (!rd.IsValid())
	{
		//printerror("Couldn't open file: ", << filePath);
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
				printerror("Couldn't detect file: ", << filePath);
			}

			delete adf;
			return nullptr;
		}
	}

	TFileInfo selfPath(filePath);

	typedef ADF::Instances_type::iterator insIt;

	for (insIt &it = adf->instances.begin(); it != adf->instances.end(); it++)
	{
		insIt::value_type &i = *it;

		std::string *req = i->instance->RequestsFile();

		if (!req)
			continue;

		TFileInfo reqPath(static_cast<std::wstring>(esString(*req)));

		TFileInfo::_vecType exVC = {};
		reqPath.Explode(exVC);

		TFileInfo::_strType rPath = reqPath.CatchBranch(selfPath.GetPath());
		ADF *exAdf = static_cast<ADF*>(IADF::Create(rPath.c_str()));

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
		i->instance->Link(adf);

	return adf;
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