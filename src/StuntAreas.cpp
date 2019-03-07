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

#include "StuntAreas.h"
#include "datas/binreader.hpp"
#include "ADF.h"

int ADFStuntAreas::Load(BinReader * rd, ADF * linker)
{
	rd->Read(static_cast<StuntAreas&>(*this));
	
	for (int a = 0; a < 32; a++)
	{
		StuntArea &ar = stuntAreas[a];
		AdfString &str = ar.name;
		rd->Seek(str.offset);
		std::string name;
		rd->ReadString(name);
		str.str = linker->AddStringHash(name);
		name.clear();

		AdfString &str2 = ar.partName;
		rd->Seek(str2.offset);
		rd->ReadString(name);
		str2.str = linker->AddStringHash(name);
	}

	return 0;
}
