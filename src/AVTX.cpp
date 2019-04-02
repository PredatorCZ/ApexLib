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

#include "AVTX.h"
#include "datas/binreader.hpp"
#include "datas/masterprinter.hpp"

int AVTX::BufferSize() const
{
	int fullSize = 0;

	for (int t = 0; t < numEntries; t++)
		if (entries[t].flags[Entry::Flag_Used])
			fullSize += entries[t].size;

	return fullSize;
}

int AVTX::Load(const TSTRING filename, bool noBuffers)
{
	BinReader rd(filename);

	if (!rd.IsValid())
	{
		printerror("Could not open AVTX file.");
		return 1;
	}

	rd.Read(*this);

	if (magic != ID)
	{
		printerror("[AVTX] Invalid format.");
		return 2;
	}

	if (noBuffers)
		return 0;

	char externalCollection = 0;
	int totalBufferSize = 0;

	for (int e = 0; e < numEntries; e++)
		if (entries[e].flags[Entry::Flag_Used])
			externalCollection |= 1 << entries[e].externalID;

	size_t lastDot = filename.find_last_of('.');

	if (lastDot == filename.npos)
	{
		printwarning("[AVTX] Invalid file extension, external buffers won't be read.");

		buffer = static_cast<char *>(malloc(entries[0].size));
		rd.ReadBuffer(buffer, entries[0].size);

		if (externalCollection > 1)
			for (int t = 0; t < numEntries; t++)
				if (entries[t].externalID)
				{
					width /= 2;
					height /= 2;
				}

		return 0;
	}

	std::ifstream ioBuffs[7];

	for (int t = 1; t < 8; t++)
	{
		const int externalMask = (1 << t);
		const bool possibleLegacy = (t == 1 && externalCollection == 3);

		if (!(externalCollection & externalMask))
			continue;

		std::wstring externalName = filename.substr(0, lastDot);
		std::ifstream & currentBuffer = ioBuffs[t - 1];
		currentBuffer.setstate(std::ios::failbit);

		if (possibleLegacy)
			currentBuffer.open(externalName + L".hmddsc", std::ios::in | std::ios::binary);

		if (currentBuffer.fail())
		{
			externalName.append(L".atx") += std::to_wstring(t);
			currentBuffer.open(externalName, std::ios::in | std::ios::binary);
		}

		if (currentBuffer.fail())
		{
			if (possibleLegacy)
			{
				printwarning("[AVTX] Couldn't load external buffer for: ", << filename << _T(" (hmddsc or atx1)."));
			}
			else
			{
				printwarning("[AVTX] Couldn't load external buffer: ", << externalName);
			}
		}
	}

	//Compute buffer size, tier 1
	char lastKnownMipEntry = 0;
	int currentBufferPos = 0;
	mipCount = headerMipCount;

	for (int e = 0; e < numEntries; e++)
		if (entries[e].flags[Entry::Flag_Used])
		{
			if (!entries[e].externalID)
				totalBufferSize += entries[e].size;
			else
			{
				if (ioBuffs[entries[e].externalID - 1].fail())
				{
					entries[e].flags(Entry::Flag_Used, false);
					continue;
				}
				mipCount++;
				totalBufferSize += entries[e].size;
				lastKnownMipEntry = static_cast<char>(e);
			}
		}

	for (int e = lastKnownMipEntry + 1; e < numEntries; e++)
		if (entries[e].size)
		{
			width /= 2;
			height /= 2;
		}

	//Sequencial error handle, tier 2
	for (int e = lastKnownMipEntry; e >= 0; e--)
		if (!entries[e].flags[Entry::Flag_Used])
		{
			buffer = static_cast<char *>(malloc(entries[lastKnownMipEntry].size));

			if (!entries[lastKnownMipEntry].externalID)
			{
				rd.ReadBuffer(buffer, entries[lastKnownMipEntry].size);
			}
			else
			{
				std::ifstream &currentBuffer = ioBuffs[entries[lastKnownMipEntry].externalID - 1];
				currentBuffer.seekg(entries[lastKnownMipEntry].offset);
				currentBuffer.read(buffer, entries[lastKnownMipEntry].size);
			}

			for (int t = lastKnownMipEntry + 1; t < numEntries; t++)
				if (entries[t].size)
				{
					width /= 2;
					height /= 2;
				}

			currentBufferPos = entries[lastKnownMipEntry].size;
			memset(entries, 0, sizeof(Entry) * numEntries);
			entries[0].size = currentBufferPos;
			entries[0].flags(Entry::Flag_Used, true);
			mipCount = 1;
			headerMipCount = 1;

			return 0;
		}

	buffer = static_cast<char *>(malloc(totalBufferSize));

	for (int t = numEntries - 1; t >= 0; t--)
		if (entries[t].flags[Entry::Flag_Used])
		{
			if (!entries[t].externalID)
			{
				entries[t].offset = currentBufferPos;
				rd.ReadBuffer(buffer + currentBufferPos, entries[t].size);
				currentBufferPos += entries[t].size;
				continue;
			}

			std::ifstream &currentBuffer = ioBuffs[entries[t].externalID - 1];
			currentBuffer.seekg(entries[t].offset);
			currentBuffer.read(buffer + currentBufferPos, entries[t].size);
			entries[t].offset = currentBufferPos;
			currentBufferPos += entries[t].size;
		}

	return 0;
}