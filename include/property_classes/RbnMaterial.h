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

struct RBNGeneralConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBNGeneralConstants);

	uint unk[2];
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	Vector2 UV3Scale;
	float flt1[3];
	uint additionalUVSets;
	float flt2[7];
	float fltend;

};

struct RBNCharacterConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBNCharacterConstants);

	uint flags; //0x10000 = 2 boneWeights
	float vertexScale;
	float flt1[11];
	uint additionalUVSets;
	float flt2[17];
	float fltend;
};

struct RBNCarPaintConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBNCarPaintConstants);

	uint unk;
	float flt1[2];
	uint flags; //0x8 deformable
	float flt2;
	float fltend;
};

struct RBNWindowConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBNWindowConstants);

	float flt1[3];
	uint unk;
};

struct RBNXXXXConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBNXXXXConstants);

	uint unk;
	float vertexScale;
	Vector2 UV1Scale;
	float fltend;
};
