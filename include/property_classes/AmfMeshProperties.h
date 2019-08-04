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

struct GeneralMeshConstants
{
	DECLARE_REFLECTOR;
	int pristineIndexCount;
	esFlags<char, GeneralMeshConstantsFlags> flags;
	static const ApexHash HASH = 0x15EEC9DE;
};

struct FoliageMeshConstants
{
	DECLARE_REFLECTOR;
	AdfBBOX boundingBoxDimensions;
	static const ApexHash HASH = 0xA7CACE80;
};

struct CarPaintMeshConstants
{
	DECLARE_REFLECTOR;
	esFlags<char, CarPaintMeshConstantsFlags> flags;
	static const ApexHash HASH = 0x1C363162;
};