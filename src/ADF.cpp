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
#include "datas/masterprinter.hpp"
#include "lookup3.h"

#define ADFFOURCC 0x41444620

ADFInstance *ADF::FindInstance(ApexHash hash, int numSkips)
{
	int currentSkip = 0;

	for (auto &i : instances)
		if (i->typeHash == hash || (i->instance && i->instance->GetSuperClass() == hash))
		{
			if (currentSkip == numSkips)
				return i->instance;
			else
				currentSkip++;
		}


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

	if (instanceBuffer)
		free(instanceBuffer);
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
			i.main = this;
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

			if (InstanceContructoreExits(typehash))
			{
				rd->Seek(i->offset);
				i->instanceBuffer = static_cast<char*>(malloc(i->size));
				rd->ReadBuffer(i->instanceBuffer, i->size);
				i->instance = ConstructInstance(typehash, i->instanceBuffer);
				i->instance->Fixup(i->instanceBuffer);
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
	}

	return 0;
}

int ADF::Descriptor::Load(BinReader *rd, ADF *base)
{

	rd->Read(type, getBlockSize(ADF::Descriptor, type, elementSize));

	name = base->names[static_cast<size_t>(nameIndex)];

	if (type == ADFDescriptorType::Structure)
		descriptorData = new DescriptorStructure();
	else if (type == ADFDescriptorType::Enumeration)
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

	for (insIt it = adf->instances.begin(); it != adf->instances.end(); it++)
	{
		insIt::value_type &i = *it;

		if (!i->instance)
			continue;

		const char *req = i->instance->RequestsFile();

		if (!req)
			continue;

		_FileInfo_t<T> reqPath(static_cast<UniString<T>>(esString(req)));
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

					if (exi->instance)
						exi->instance->ReplaceReferences(adf);

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
	pugi::xml_node master = node.append_child("Definitions");

	for (auto &d : descriptors)
		d.XMLDump(&master);

	if (numInstances)
	{
		pugi::xml_node instNode = node.append_child("Instances");

		for (auto &i : instances)
		{
			pugi::xml_node subinstNode = instNode.append_child(i->name->string.c_str());
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
		pugi::xml_node hashNode = node.append_child("Strings");

		for (auto &h : hashes)
		{
			pugi::xml_node substrNode = hashNode.append_child("String");
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
		pugi::xml_node node = master->append_child(m.name->string.c_str());

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

	pugi::xml_node node = master->append_child(_typeName);
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

/************************************************************************/
/******************************* CPP ************************************/
/************************************************************************/

static const std::map<ApexHash, const char *> cpptypes = 
{
	{ 0x8955583E, "AdfString" },
	{ 0xDEFE88ED, "AdfDeferred" },
};

int ADF::ExportDefinitionsToCPP(std::ostream &str) const
{
	CPPRegistry classes;

	for (auto &d : descriptors)
		d.CPPDump(classes);

	bool useBitFields = false;

	for (auto &d : descriptors)
		if (d.type == ADFDescriptorType::BitField)
		{
			useBitFields = true;
			break;
		}

	str << "/*ApexLib ADF generated header file.*/\n\n#pragma once\n#include \"AdfBaseObject.h\"\n";

	if (useBitFields)
		str << "#include \"datas/flags.hpp\"\n\n";

	for (CPPRegistry::reverse_iterator it = classes.rbegin(); it != classes.rend(); it++)
		str << **it;

	return 0;
}

int ADF::ExportDefinitionsToCPP(const char *fileName) const
{
	std::ofstream str(fileName);
	ExportDefinitionsToCPP(str);
	return 0;
}

int ADF::ExportDefinitionsToCPP(const wchar_t *fileName) const
{
	std::ofstream str(
#if UNICODE
		fileName
#else
	esStringConvert<char>(fileName)
#endif
		);
	ExportDefinitionsToCPP(str);
	return 0;
}

void ADF::Descriptor::CPPDump(CPPRegistry &classes) const
{
	descriptorData->CPPDump(this, classes);
}

enum __testEnum {};

void ADF::DescriptorExplicitEnum::CPPDump(const Descriptor *main, CPPRegistry &classes) const
{
	std::stringstream str;

	str << "enum " << main->name->string;

	if (sizeof(__testEnum) != main->size)
	{
		switch (main->size)
		{
		case 1:
			str << " : char";
			break;
		case 2:
			str << " : short";
			break;
		case 4:
			str << " : int";
			break;
		case 8:
			str << " : int64";
			break;
		}
	}
	
	str << "\n{\n";

	short cNumber = -1, sNumber = 0;

	for (auto &m : members)
	{
		if (cNumber < 0)
		{
			cNumber = m.value;
			sNumber = cNumber;
		}
		else if (m.value == cNumber + 1)
			cNumber++;
		else
		{
			cNumber = -1;
			break;
		}
	}

	cNumber = ~cNumber; //isLinear

	for (auto &m : members)
	{
		str << '\t' << m.name->string;

		if (!cNumber || sNumber)
		{
			str << " = " << m.value;

			if (sNumber)
				sNumber = 0;
		}

		str << ",\n";
	}

	str << "};\n";

	classes.push_back(new std::string(str.str()));
}

void ADF::DescriptorBase::CPPDump(const Descriptor *main, CPPRegistry &classes) const
{
}

bool GetTypeName(const ApexHash hash, const ADF::Descriptor *main, std::ostream &str, const char *varName = nullptr)
{
	for (auto &c : cpptypes)
		if (c.first == hash)
		{
			str << c.second;
			return false;
		}

	for (auto &t : types)
		if (t.first == hash)
		{
			str << t.second;
			return false;
		}

	for (auto &d : main->main->descriptors)
		if (d.nameHash == hash)
		{
			switch (d.type)
			{
			case ADFDescriptorType::Array:
				str << "AdfArray<";
				GetTypeName(d.elementTypeHash, main, str);
				str << '>';
				return false;
			case ADFDescriptorType::StringHash:
				str << "ApexHash";
				return false;
			case ADFDescriptorType::String:
				str << "AdfString";
				return false;
			case ADFDescriptorType::Structure:
			{
				for (auto &_d : main->main->descriptors)
					if (_d.nameHash == hash)
					{
						str << _d.name->string;
						return false;
					}

					break;
			}
			case ADFDescriptorType::InlineArray:
			{
				if (d.elementTypeHash == 0x7515A207 && d.elementSize > 1 && d.elementSize < 5) //float
				{
					str << "Vector";

					if(d.elementSize != 3)
						str << d.elementSize;

					if (varName)
						str << ' ' << varName;
					
					str << ";\n";
				}
				else
				{
					GetTypeName(d.elementTypeHash, main, str);

					if (varName)
						str << ' ' << varName;

					str << '[' << d.elementSize << "];\n";
				}
			
				return varName != nullptr;
			}
			}
		}
	return false;
}

void ADF::DescriptorStructure::CPPDump(const Descriptor *main, CPPRegistry &classes) const
{
	std::stringstream str;

	str << "struct " << main->name->string << "\n{\n";

	ApexHash lastType = 0;
	std::map<ADF::Descriptor *, std::vector<const Member *>> bitFields;

	for (auto &m : members)
	{
		str << '\t';
		
		ADF::Descriptor *subDesc = nullptr;

		for (auto &d : main->main->descriptors)
			if (d.nameHash == m.typeHash)
			{
				subDesc = &d;
				break;
			}

		if (m.typeHash == lastType)
		{
			
			if (subDesc && subDesc->type == ADFDescriptorType::BitField)
			{
				if (bitFields.count(subDesc))
					bitFields.at(subDesc).push_back(&m);

				lastType = m.typeHash;
				continue;
			}

			str.seekp(-3, std::ios_base::cur);
			str << ",\n\t\t" << m.name->string;
			
			if (subDesc && subDesc->type == ADFDescriptorType::InlineArray &&
			(subDesc->elementTypeHash != 0x7515A207 || subDesc->elementSize < 2 || subDesc->elementSize > 4))
			{
				str << '[' << subDesc->elementSize << ']';
				break;
			}
			
			str << ";\n";
		}
		else
		{
			if (subDesc && subDesc->type == ADFDescriptorType::BitField)
			{
				bitFields[subDesc].push_back(&m);
				str << "esFlags<";

				switch (subDesc->size)
				{
				case 1:
					str << "char";
					break;
				case 2:
					str << "short";
					break;
				case 4:
					str << "int";
					break;
				case 8:
					str << "int64";
					break;
				}

				str << ", " << main->name->string << "_flags" << bitFields.size() - 1 << 
					"> flags" << bitFields.size() - 1 << ";\n";
				lastType = m.typeHash;
				continue;
			}

			bool alreadyWritten = GetTypeName(m.typeHash, main, str, m.name->string.c_str());

			if(!alreadyWritten)
				str << ' ' << m.name->string << ";\n";
		}
		
		lastType = m.typeHash;
	}

	str << "\n\tstatic const ApexHash HASH = 0x" << std::hex << std::uppercase << 
	main->nameHash << std::dec << ";\n};\n\nstatic_assert(sizeof(" << 
	main->name->string << ") == " << main->size << ", \"Check assumptions\");\n\n";

	classes.push_back(new std::string(str.str()));

	int currentBitField = 0;
	

	for (auto &f : bitFields)
	{
		str = std::stringstream();
		str << "enum " << main->name->string << "_flags" << currentBitField << "\n{\n";

		for (auto &b : f.second)
			str << '\t' << b->name->string << ",\n";

		str << "};\n\n";
		currentBitField++;
		classes.push_back(new std::string(str.str()));
	}	
}