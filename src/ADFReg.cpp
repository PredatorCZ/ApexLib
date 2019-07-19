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
#include <map>
#include "ADF.h"
#include "AdfBaseObject.h"
#include "AmfModel.h"
#include "AmfMesh.h"
#include "AmfFormatEvaluators.h"
#include "DeformPoints.h"
#include "StuntAreas.h"
#include "StreamPatch.h"
#include "datas/macroLoop.hpp"
#include "datas/binreader.hpp"
#include "datas/reflectorRegistry.hpp"
#include "datas/disabler.hpp"

/**************************************************/
/*******************AdfDeferred********************/
/**************************************************/

template<class C> Reflector *ADFCreatePropClass(void *data) { return new ReflectorWrap<C>(static_cast<C*>(data)); }

#define ADFRegisterProps(classname) {classname::HASH, &ADFCreatePropClass<classname>},

static const std::map<ApexHash, Reflector *(*)(void *)> ADFPropsStorage =
{
	StaticFor(ADFRegisterProps, 
	GeneralMeshConstants,
	FoliageMeshConstants,
	CarPaintMeshConstants,
	GeneralConstants,
	CarLightConstants,
	WindowConstants,
	CarPaintStaticConstants,
	CarPaintDynamicConstants,
	CarPaintConstants,
	CharacterSkinConstants,
	CharacterConstants,
	EyeGlossConstants,
	HairConstants,
	BarkConstants,
	FoliageConstants,
	HologramConstants,
	LandmarkConstants,
	EmissiveUIConstants,
	GeneralR2Constants,
	GeneralMkIIIConstants,
	WindowConstants_GZ,
	CharacterSkinConstants_GZ,
	HairConstants_GZ,
	CharacterConstants_GZ,
	BarkConstants_GZ,
	FoliageConstants_GZ,
	CarLightConstants_GZ,

	RBMCarPaintSimpleConstants,
	RBMVegetationFoliageConstants,
	RBMGeneralConstants,
	RBMFacadeConstants,
	RBMWindowConstants,
	RBMSkinnedGeneralConstants,
	RBMCarPaintConstants,
	
	RBMSkinnedGeneral0Constants,
	RBMSkinnedGeneralDecalConstants,
	RBMGeneral0Constants,
	RBMFacade0Constants/*,
	GeneralR2Constants_HU,
	CharacterConstants_HU,
	GeneralConstants_HU,
	PropConstants_HU,
	CarPaintMMConstants_HU,
	GeneralJC3Constants_HU*/
	)
};

Reflector *AdfDeferred::GetReflected() const
{
	return ADFPropsStorage.count(objectHash) ? ADFPropsStorage.at(objectHash)(item.vPtr) : nullptr;
}

Reflector *AdfDeferred::GetReflected()
{
	return ADFPropsStorage.count(objectHash) ? ADFPropsStorage.at(objectHash)(item.vPtr) : nullptr;
}

/**************************************************/
/*********************AmfFormat********************/
/**************************************************/

template<AmfFormat t_format, class OutType> AmfVertexDescriptor *AmfFormatEvalDummy()
{
	return new tVertexDescriptor<t_format, OutType>();
}

#define ADFRegisterFormat(unused, format, outType) \
{static_cast<AmfFormat>(format), AmfFormatEvalDummy<static_cast<AmfFormat>(format), outType>},

static const std::map
<
	AmfFormat,
	AmfVertexDescriptor *(*)()
> AmfFormatStorage =
{
	StaticForArgID(ADFRegisterFormat,
		unused,
		/*AmfFormat_R32G32B32A32_FLOAT*/ Vector4,
		/*AmfFormat_R32G32B32A32_UINT*/ UIVector4,
		/*AmfFormat_R32G32B32A32_SINT*/ IVector4,

		/*AmfFormat_R32G32B32_FLOAT*/ Vector,
		/*AmfFormat_R32G32B32_UINT*/ UIVector,
		/*AmfFormat_R32G32B32_SINT*/ IVector,

		/*AmfFormat_R16G16B16A16_FLOAT*/ Vector4,
		/*AmfFormat_R16G16B16A16_UNORM*/ Vector4,
		/*AmfFormat_R16G16B16A16_UINT*/ USVector4,
		/*AmfFormat_R16G16B16A16_SNORM*/ Vector4,
		/*AmfFormat_R16G16B16A16_SINT*/ SVector4,

		/*AmfFormat_R16G16B16_FLOAT*/ Vector,
		/*AmfFormat_R16G16B16_UNORM*/ Vector,
		/*AmfFormat_R16G16B16_UINT*/ USVector,
		/*AmfFormat_R16G16B16_SNORM*/ Vector,
		/*AmfFormat_R16G16B16_SINT*/ SVector,

		/*AmfFormat_R32G32_FLOAT*/ Vector2,
		/*AmfFormat_R32G32_UINT*/ UIVector2,
		/*AmfFormat_R32G32_SINT*/ IVector2,

		/*AmfFormat_R10G10B10A2_UNORM*/ Vector4,
		/*AmfFormat_R10G10B10A2_UINT*/ UIVector4,
		/*AmfFormat_R11G11B10_FLOAT*/ Vector,

		/*AmfFormat_R8G8B8A8_UNORM*/ Vector4,
		/*AmfFormat_R8G8B8A8_UNORM_SRGB*/ Vector4,
		/*AmfFormat_R8G8B8A8_UINT*/ UCVector4,
		/*AmfFormat_R8G8B8A8_SNORM*/ Vector4,
		/*AmfFormat_R8G8B8A8_SINT*/ CVector4,

		/*AmfFormat_R16G16_FLOAT*/ Vector2,
		/*AmfFormat_R16G16_UNORM*/ Vector2,
		/*AmfFormat_R16G16_UINT*/ USVector2,
		/*AmfFormat_R16G16_SNORM*/ Vector2,
		/*AmfFormat_R16G16_SINT*/ SVector2,

		/*AmfFormat_R32_FLOAT*/ float,
		/*AmfFormat_R32_UINT*/ unsigned int,
		/*AmfFormat_R32_SINT*/ int,

		/*AmfFormat_R8G8_UNORM*/ Vector2,
		/*AmfFormat_R8G8_UINT*/ UCVector2,
		/*AmfFormat_R8G8_SNORM*/ Vector2,
		/*AmfFormat_R8G8_SINT*/ CVector2,

		/*AmfFormat_R16_FLOAT*/ float,
		/*AmfFormat_R16_UNORM*/ float,
		/*AmfFormat_R16_UINT*/ unsigned short,
		/*AmfFormat_R16_SNORM*/ float,
		/*AmfFormat_R16_SINT*/ short,

		/*AmfFormat_R8_UNORM*/ float,
		/*AmfFormat_R8_UINT*/ unsigned char,
		/*AmfFormat_R8_SNORM*/ float,
		/*AmfFormat_R8_SINT*/ char,

		/*AmfFormat_R32_UNIT_VEC_AS_FLOAT*/ Vector,
		/*AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT*/ Vector4,
		/*AmfFormat_R8G8B8A8_TANGENT_SPACE*/ Vector,

		/*AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c*/ Vector,
		/*AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c*/ Vector
	)
};

AmfVertexDescriptor *AmfVertexDescriptor::Create(AmfFormat format)
{
	return AmfFormatStorage.count(format) ? AmfFormatStorage.at(format)() : nullptr;
}

/**************************************************/
/*******************ADF Instance*******************/
/**************************************************/

template<class C> ADFInstance *ADFCreateDerivedClass(void *_data, ADF *_main) { return new C(_data, _main); }
#define ADFRegisterClass(classname) {classname::HASH, &ADFCreateDerivedClass<classname>},

static const std::map<ApexHash, ADFInstance *(*)(void *, ADF *)> ADFClassStorage =
{
	StaticFor(ADFRegisterClass,
	AmfMeshHeader_V1_wrap,
	AmfMeshBuffers_V1_wrap,
	AmfModel_V1_wrap,
	AmfMeshBuffers_V1_5_wrap,
	AmfMeshBuffers_V2_wrap,
	StuntAreas_wrap,
	DeformPoints_wrap,
	StreamPatchFileHeader_wrap,
	StreamPatchBlockHeader_wrap,
	TerrainPatch_wrap,
	AmfMeshHeader_V2_wrap
	)
};

static int EnumBuilded = 0;

bool ADF::InstanceContructoreExits(ApexHash classHash)
{
	return ADFClassStorage.count(classHash) != 0;
}

ADFInstance *ADF::ConstructInstance(ApexHash classHash, void *data)
{
	return ADFClassStorage.count(classHash) ? ADFClassStorage.at(classHash)(data, this) : nullptr;
}

ADF::ADF()
{
	if (EnumBuilded)
		return;

	REGISTER_ENUM(GeneralMeshConstantsFlags);
	REGISTER_ENUM(CarPaintMeshConstantsFlags);
	REGISTER_ENUM(GeneralConstantsFlags);
	REGISTER_ENUM(WindowConstantsFlags);
	REGISTER_ENUM(CarPaintConstantsFlags0);
	REGISTER_ENUM(CarPaintConstantsFlags1);
	REGISTER_ENUM(CarPaintConstantsFlags2);
	REGISTER_ENUM(CharacterSkinConstantsFlags);
	REGISTER_ENUM(CharacterConstantsFlags);
	REGISTER_ENUM(EyeGlossConstantsFlags);
	REGISTER_ENUM(HairConstantsFlags);
	REGISTER_ENUM(BarkConstantsFlags);
	REGISTER_ENUM(FoliageConstantsFlags);
	REGISTER_ENUM(CharacterConstantsFlags_GZ);
	REGISTER_ENUM(HairConstantsFlags_GZ);
	REGISTER_ENUM(CharacterSkinConstantsFlags_GZ);
	REGISTER_ENUM(WindowConstantsFlags_GZ);
	REGISTER_ENUM(BarkConstantsFlags_GZ);
	EnumBuilded = 0xff;
}