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

#include "DeformPoints.h"
#include "datas/binreader.hpp"
#include "ADF.h"

int ADFDeformPoints::Load(BinReader *rd, ADF *linker)
{
	rd->Read(Header);
	rd->Seek(Header.points.offset);
	points.resize(static_cast<size_t>(Header.points.count));

	for (auto &p : points)
		rd->Read(p);

	rd->Seek(Header.constraintIndices.offset);
	constraintIndices.resize(static_cast<size_t>(Header.constraintIndices.count));

	for (auto &i : constraintIndices)
		rd->Read(i);

	rd->Seek(Header.lightIndices.offset);
	lightIndices.resize(static_cast<size_t>(Header.lightIndices.count));

	for (auto &i : lightIndices)
		rd->Read(i);

	rd->Seek(Header.wheelIndices.offset);
	wheelIndices.resize(static_cast<size_t>(Header.wheelIndices.count));

	for (auto &i : wheelIndices)
		rd->Read(i);

	rd->Seek(Header.nonDeformablePartsIndices.offset);
	nonDeformablePartsIndices.resize(static_cast<size_t>(Header.nonDeformablePartsIndices.count));

	for (auto &i : nonDeformablePartsIndices)
		rd->Read(i);

	rd->Seek(Header.haulingHitchIndices.offset);
	haulingHitchIndices.resize(static_cast<size_t>(Header.haulingHitchIndices.count));

	for (auto &i : haulingHitchIndices)
		rd->Read(i);

	rd->Seek(Header.trailingHitchIndices.offset);
	trailingHitchIndices.resize(static_cast<size_t>(Header.trailingHitchIndices.count));

	for (auto &i : trailingHitchIndices)
		rd->Read(i);

	for (auto &p : points)
	{
		AdfString &str = p.name;
		rd->Seek(str.offset);
		std::string name;
		rd->ReadString(name);
		str.str = linker->AddStringHash(name);
		name.clear();

		AdfString &str2 = p.fromPart;
		rd->Seek(str2.offset);
		rd->ReadString(name);
		str2.str = linker->AddStringHash(name);
		name.clear();

		AdfString &str3 = p.skinnedToPart;
		rd->Seek(str3.offset);
		rd->ReadString(name);
		str3.str = linker->AddStringHash(name);
		name.clear();

		AdfString &str4 = p.deformPointType.string;
		rd->Seek(str4.offset);
		rd->ReadString(name);
		str4.str = linker->AddStringHash(name);
	}

	return 0;
}
