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
#include "RBM.h"
#include "datas/flags.hpp"

REFLECTOR_ENUM(RBMCarPaintSimpleFlags,
	NoCulling,
	Alpha,
	TwoTone,
	IgnorePalette,
	NoDirt,
	Decal,
	MaskWater,
	AlphaTest);

struct RBMCarPaintSimple : RBMMasterBlock
{
	DECLARE_REFLECTOR;
	RBMCONSTRUCTOR(RBMCarPaintSimple, 0x181938490);

	//PSH
	Vector twoToneColor1;
	Vector twoToneColor2;
	float specularPower;
	float depthBias;
	float reflectionMultiplier;
	float unk[4];
	esFlags<uint, RBMCarPaintSimpleFlags> flags;

	//VSH
	uint type;

	void Load(BinReader *rd);
};

struct RBMFoliageBark : RBMMasterBlock
{
	RBMCONSTRUCTOR(RBMFoliageBark, 0xb1f9133d);

	//PSH
	uint flags;

	//VSH
	uint type;

	void Load(BinReader *rd);
};

struct RBMVegetationFoliage : RBMMasterBlock
{
	DECLARE_REFLECTOR;
	RBMCONSTRUCTOR(RBMVegetationFoliage, 0xd79884c6);

	//PSH
	float specularIntensity;
	float specularPower;
	Vector translucencyColorMask;
	uint flags;

	//VSH
	uint unk;

	void Load(BinReader *rd);
};

struct RBMBillboardFoliage : RBMMasterBlock
{
	RBMCONSTRUCTOR(RBMBillboardFoliage, 0xad529e70);

	//VSH
	uint unk;

	void Load(BinReader *rd);
};

struct RBMHalo : RBMMasterBlock
{
	RBMCONSTRUCTOR(RBMHalo, 0x65d9b5b2);

	//VSH
	uint unk;

	void Load(BinReader *rd);
};

struct RBMLambert : RBMMasterBlock
{
	RBMCONSTRUCTOR(RBMLambert, 0x4d5d78ae0);

	//PSH
	uint shaderType;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	uint unk[4];
	uint endunk;

	//VSH
	uint unk2;

	void Load(BinReader *rd);
};

REFLECTOR_ENUM(RBMGeneralFlags,
	NoCulling,
	Alpha,
	AdditiveAlpha,
	_null00,
	_null01,
	ChannelMask,
	UseSnow,
	AnimatedTexture,
	AlphaTest,
	UseChannelAO);

struct RBMGeneral : RBMMasterBlock
{
	DECLARE_REFLECTOR;
	RBMCONSTRUCTOR(RBMGeneral, 0x3a7583b2b);

	//PSH
	Vector4 channelMask;
	Vector4 channelAoMask;
	float depthBias;
	float specularPower;
	esFlags<uint, RBMGeneralFlags> flags;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	uint unk[2];
	uint endunk;

	//VSH
	uint type;

	void Load(BinReader *rd);
};

REFLECTOR_ENUM(RBMFacadeFlags,
	NoCulling,
	Alpha,
	_null00,
	_null01,
	UseChannelAO,
	UseChannelTextures,
	UseSnow);

struct RBMFacade : RBMMasterBlock
{
	DECLARE_REFLECTOR;
	RBMCONSTRUCTOR(RBMFacade, 0x1ce39d7bf);

	//PSH
	Vector4 channelMask;
	Vector channelDirtMask;
	Vector emissiveMultiplier;
	float depthBias;
	float specularPower;
	esFlags<uint, RBMFacadeFlags> flags;
	float vertexScale;
	uint unk1;

	//VSH
	uint type;

	void Load(BinReader *rd);
};

struct RBMWindow : RBMMasterBlock
{
	DECLARE_REFLECTOR;
	RBMCONSTRUCTOR(RBMWindow, 0x5b2003f6);

	//PSH
	float specularPower;
	uint flags;

	//VSH
	uint type;

	void Load(BinReader *rd);
};

struct RBMCarPaint : RBMCarPaintSimple
{
	RBMREFLECTOR_FROM_PARENT(RBMCarPaintSimple)
	RBMCONSTRUCTOR(RBMCarPaint, 0x3CD931E75);

	void Load(BinReader *rd);
};

struct RBMDeformWindow : RBMMasterBlock
{
	RBMCONSTRUCTOR(RBMDeformWindow, 0x106B1F602);

	//VSH
	uint type;

	void Load(BinReader *rd);
};

struct RBMMerged : RBMMasterBlock
{
	RBMCONSTRUCTOR(RBMMerged, 0x9185A4C3);

	//VSH
	uint unk;
	bool useVertexBuffer;
	uint unk2;

	void Load(BinReader *rd);
};

REFLECTOR_ENUM(RBMSkinnedGeneralTechnique,
	Skin,
	Hair,
	Cloth,
	Metal,
	EyeGloss,
	SkinAlphaToCoverage);

REFLECTOR_ENUM(RBMSkinnedGeneralFlags,
	NoCulling,
	AlphaTest,
	NoShadowCasting,
	WideBoneWeights);

struct RBMSkinnedGeneral : RBMMasterBlock
{
	DECLARE_REFLECTOR;
	RBMCONSTRUCTOR(RBMSkinnedGeneral, 0x35e657f20);

	//PSH
	union _Flags
	{
		uint d;
		struct 
		{
			esEnum<uchar, RBMSkinnedGeneralTechnique> technique;
			esFlags<uchar, RBMSkinnedGeneralFlags> flags;
			short null;
		} f;
		_Flags() : d(0) {}
	}flags;

	float specularPower;
	float rimIntensity;
	float rimPower;
	Vector rimWeights;

	//VSH
	uint type;

	void Load(BinReader *rd);
};

struct RBMSkinnedGeneral0 : RBMSkinnedGeneral
{
	RBMREFLECTOR_FROM_PARENT(RBMSkinnedGeneral);
	RBMCONSTRUCTOR(RBMSkinnedGeneral0, 0x5e657f20);
};

struct RBMSkinnedGeneralDecal : RBMSkinnedGeneral
{
	RBMREFLECTOR_FROM_PARENT(RBMSkinnedGeneral);
	RBMCONSTRUCTOR(RBMSkinnedGeneralDecal, 0x60ff47a7);

	void Load(BinReader *rd);
};

struct RBMGeneral0 : RBMGeneral
{
	RBMREFLECTOR_FROM_PARENT(RBMGeneral);
	RBMCONSTRUCTOR(RBMGeneral0, 0xa7583b2b);

	void Load(BinReader *rd);
};

struct RBMFacade0 : RBMFacade
{
	RBMREFLECTOR_FROM_PARENT(RBMFacade);
	RBMCONSTRUCTOR(RBMFacade0, 0xce39d7bf);

	void Load(BinReader *rd);
};