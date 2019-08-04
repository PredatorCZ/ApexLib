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

REFLECTOR_ENUM(RBMCarPaintSimpleFlags,
	NoCulling,
	Alpha,
	TwoTone,
	IgnorePalette,
	NoDirt,
	Decal,
	MaskWater,
	AlphaTest);

struct RBMCarPaintSimpleConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMCarPaintSimpleConstants);

	Vector twoToneColor1;
	Vector twoToneColor2;
	float specularPower;
	float depthBias;
	float reflectionMultiplier;
	float unk[4];
	esFlags<uint, RBMCarPaintSimpleFlags> flags;
};

struct RBMFoliageBarkConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMFoliageBarkConstants);

	uint flags;
};

struct RBMVegetationFoliageConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMVegetationFoliageConstants);

	float specularIntensity;
	float specularPower;
	Vector translucencyColorMask;
	uint flags;
};

struct RBMLambertConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMLambertConstants);

	uint shaderType;
	float vertexScale;
	Vector2 UV1Scale;
	Vector2 UV2Scale;
	uint unk[4];
	uint endunk;
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

struct RBMGeneralConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMGeneralConstants);

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
};

REFLECTOR_ENUM(RBMFacadeFlags,
	NoCulling,
	Alpha,
	_null00,
	_null01,
	UseChannelAO,
	UseChannelTextures,
	UseSnow);

struct RBMFacadeConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMFacadeConstants);

	Vector4 channelMask;
	Vector channelDirtMask;
	Vector emissiveMultiplier;
	float depthBias;
	float specularPower;
	esFlags<uint, RBMFacadeFlags> flags;
	float vertexScale;
	uint unk1;
};

struct RBMWindowConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMWindowConstants);

	float specularPower;
	uint flags;
};

struct RBMCarPaintConstants : RBMCarPaintSimpleConstants
{
	DEFINE_PROPERTY(RBMCarPaintConstants);
	RBMREFLECTOR_FROM_PARENT(RBMCarPaintSimpleConstants);
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

struct RBMSkinnedGeneralConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMSkinnedGeneralConstants);

	esEnum<ushort, RBMSkinnedGeneralTechnique> technique;
	esFlags<ushort, RBMSkinnedGeneralFlags> flags;
	float specularPower;
	float rimIntensity;
	float rimPower;
	Vector rimWeights;
};

struct RBMSkinnedGeneral0Constants : RBMSkinnedGeneralConstants
{
	DEFINE_PROPERTY(RBMSkinnedGeneral0Constants);
	RBMREFLECTOR_FROM_PARENT(RBMSkinnedGeneralConstants);
};

struct RBMSkinnedGeneralDecalConstants : RBMSkinnedGeneralConstants
{
	DEFINE_PROPERTY(RBMSkinnedGeneralDecalConstants);
	RBMREFLECTOR_FROM_PARENT(RBMSkinnedGeneralConstants);
};

struct RBMGeneral0Constants : RBMGeneralConstants
{
	DEFINE_PROPERTY(RBMGeneral0Constants);
	RBMREFLECTOR_FROM_PARENT(RBMGeneralConstants);
};

struct RBMFacade0Constants : RBMFacadeConstants
{
	DEFINE_PROPERTY(RBMFacade0Constants);
	RBMREFLECTOR_FROM_PARENT(RBMFacadeConstants);
};

struct RBMBillboardFoliageConstants
{
	DEFINE_PROPERTY(RBMBillboardFoliageConstants);
};

struct RBMHaloConstants
{
	DEFINE_PROPERTY(RBMHaloConstants);
};

struct RBMDeformWindowConstants
{
	DEFINE_PROPERTY(RBMDeformWindowConstants);
};

struct RBMMergedConstants
{
	DEFINE_PROPERTY(RBMMergedConstants);
};

struct RBMUIOverlayConstants
{
	DEFINE_PROPERTY(RBMUIOverlayConstants);
};

struct RBMScopeConstants
{
	DEFINE_PROPERTY(RBMScopeConstants);
};

//VSH
struct RBMApex2MeshConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMApex2MeshConstants);

	int flags;
};

struct RBMMergedMeshConstants
{
	DECLARE_REFLECTOR;
	DEFINE_PROPERTY(RBMMergedMeshConstants);

	uint unk;
	bool useVertexBuffer;
	uint unk2;
};