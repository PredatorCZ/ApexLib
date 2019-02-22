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

#include "datas/binreader.hpp"
#include "AmfMesh.h"
#include "AdfRegistry.h"
#include "AmfModel.h"
#include "AmfFormatEvaluators.h"
#include "datas/reflectorRegistry.hpp"
#include "datas/disabler.hpp"

ADFClassMapper ADFClassStorage;
ADFPropsMapper ADFPropsStorage;
AmfFormatMapper AmfFormatStorage;
struct RBMMasterBlock;
typedef std::map<_ULONGLONG, RBMMasterBlock*(*)()> RBMPropsMapper;
extern RBMPropsMapper RBMClassStorage;

template<class C> ADFInstance *ADFCreateDerivedClass() { return new C{}; }
template<class C> AdfProperties *ADFCreatePropClass() { return new C{}; }

#define ADFRegisterClass(classname) ADFClassStorage[classname::HASH] = &ADFCreateDerivedClass<classname>;

template<class C> struct AdfProperties_t : Reflector, AdfProperties
{
	typedef C value_type;
	C properties;

	ADD_DISABLERS(C, noReflection);
	enabledFunction(noReflection, void) ES_INLINE ConstructReflection() { _nTypes = C::nTypes; _typeNames = C::typeNames; _types = C::types; thisAddr = reinterpret_cast<char*>(&properties); }
	disabledFunction(noReflection, void) ES_INLINE ConstructReflection() {}
 
	AdfProperties_t<C>() { typeHash = C::HASH; ConstructReflection(); }
	void Load(BinReader *rd) { rd->Read(properties); }
	void *GetProperties() { return &properties; }
};

#define ADFRegisterProps(classname) ADFPropsStorage[AdfProperties_t<classname>::value_type::HASH] = &ADFCreatePropClass<AdfProperties_t<classname>>;

#define ADFRegisterFormat(format, outType) AmfFormatStorage[format] = AmfFormatEval<format, outType>;
void InitRBMRegistry();
void InitAdfRegistry()
{
	ADFRegisterClass(AmfMeshHeader);
	ADFRegisterClass(AmfMeshBuffers);
	ADFRegisterClass(AmfModel);
	ADFRegisterClass(AmfMeshBuffers_TheHunter);

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

	ADFRegisterProps(GeneralMeshConstants);
	ADFRegisterProps(FoliageMeshConstants);
	ADFRegisterProps(CarPaintMeshConstants);
	ADFRegisterProps(GeneralConstants);
	ADFRegisterProps(CarLightConstants);
	ADFRegisterProps(WindowConstants);
	ADFRegisterProps(CarPaintStaticConstants);
	ADFRegisterProps(CarPaintDynamicConstants);
	ADFRegisterProps(CarPaintConstants);
	ADFRegisterProps(CharacterSkinConstants);
	ADFRegisterProps(CharacterConstants);
	ADFRegisterProps(EyeGlossConstants);
	ADFRegisterProps(HairConstants);
	ADFRegisterProps(BarkConstants);
	ADFRegisterProps(FoliageConstants);
	ADFRegisterProps(HologramConstants);
	ADFRegisterProps(LandmarkConstants);
	ADFRegisterProps(EmissiveUIConstants);

	ADFRegisterFormat(AmfFormat_R32G32B32A32_FLOAT, Vector4);
	ADFRegisterFormat(AmfFormat_R32G32B32A32_SINT, IVector4);
	ADFRegisterFormat(AmfFormat_R32G32B32A32_UINT, UIVector4);

	ADFRegisterFormat(AmfFormat_R32G32B32_FLOAT, Vector);
	ADFRegisterFormat(AmfFormat_R32G32B32_SINT, IVector);
	ADFRegisterFormat(AmfFormat_R32G32B32_UINT, UIVector);

	ADFRegisterFormat(AmfFormat_R16G16B16A16_FLOAT, Vector4);
	ADFRegisterFormat(AmfFormat_R16G16B16A16_SINT, SVector4);
	ADFRegisterFormat(AmfFormat_R16G16B16A16_UINT, USVector4);
	ADFRegisterFormat(AmfFormat_R16G16B16A16_UNORM, Vector4);
	ADFRegisterFormat(AmfFormat_R16G16B16A16_SNORM, Vector4);

	ADFRegisterFormat(AmfFormat_R16G16B16_FLOAT, Vector);
	ADFRegisterFormat(AmfFormat_R16G16B16_SINT, SVector);
	ADFRegisterFormat(AmfFormat_R16G16B16_UINT, USVector);
	ADFRegisterFormat(AmfFormat_R16G16B16_UNORM, Vector);
	ADFRegisterFormat(AmfFormat_R16G16B16_SNORM, Vector);

	ADFRegisterFormat(AmfFormat_R32G32_FLOAT, Vector2);
	ADFRegisterFormat(AmfFormat_R32G32_SINT, IVector2);
	ADFRegisterFormat(AmfFormat_R32G32_UINT, UIVector2);

	ADFRegisterFormat(AmfFormat_R8G8B8A8_SINT, CVector4);
	ADFRegisterFormat(AmfFormat_R8G8B8A8_UINT, UCVector4);
	ADFRegisterFormat(AmfFormat_R8G8B8A8_UNORM, Vector4);
	ADFRegisterFormat(AmfFormat_R8G8B8A8_SNORM, Vector4);

	ADFRegisterFormat(AmfFormat_R8G8B8A8_UNORM_SRGB, Vector4);

	ADFRegisterFormat(AmfFormat_R16G16_FLOAT, Vector2);
	ADFRegisterFormat(AmfFormat_R16G16_SINT, SVector2);
	ADFRegisterFormat(AmfFormat_R16G16_UINT, USVector2);
	ADFRegisterFormat(AmfFormat_R16G16_UNORM, Vector2);
	ADFRegisterFormat(AmfFormat_R16G16_SNORM, Vector2);

	ADFRegisterFormat(AmfFormat_R32_FLOAT, float);
	ADFRegisterFormat(AmfFormat_R32_SINT, int);
	ADFRegisterFormat(AmfFormat_R32_UINT, unsigned int);

	ADFRegisterFormat(AmfFormat_R8G8_SINT, CVector2);
	ADFRegisterFormat(AmfFormat_R8G8_UINT, UCVector2);
	ADFRegisterFormat(AmfFormat_R8G8_UNORM, Vector2);
	ADFRegisterFormat(AmfFormat_R8G8_SNORM, Vector2);

	ADFRegisterFormat(AmfFormat_R16_FLOAT, float);
	ADFRegisterFormat(AmfFormat_R16_SINT, short);
	ADFRegisterFormat(AmfFormat_R16_UINT, unsigned short);
	ADFRegisterFormat(AmfFormat_R16_UNORM, float);
	ADFRegisterFormat(AmfFormat_R16_SNORM, float);

	ADFRegisterFormat(AmfFormat_R8_SINT, char);
	ADFRegisterFormat(AmfFormat_R8_UINT, unsigned char);
	ADFRegisterFormat(AmfFormat_R8_UNORM, float);
	ADFRegisterFormat(AmfFormat_R8_SNORM, float);

	ADFRegisterFormat(AmfFormat_R10G10B10A2_UNORM, Vector4);
	ADFRegisterFormat(AmfFormat_R10G10B10A2_UINT, UIVector4);
	ADFRegisterFormat(AmfFormat_R11G11B10_FLOAT, Vector);

	ADFRegisterFormat(AmfFormat_R32_UNIT_VEC_AS_FLOAT, Vector);
	ADFRegisterFormat(AmfFormat_R32_R8G8B8A8_UNORM_AS_FLOAT, Vector4);
	ADFRegisterFormat(AmfFormat_R8G8B8A8_TANGENT_SPACE, Vector);

	ADFRegisterFormat(AmfFormat_R32_UNIT_UNSIGNED_VEC_AS_FLOAT_c, Vector);
	ADFRegisterFormat(AmfFormat_R8G8B8A8_UNSIGNED_SNORM_c, Vector);

	InitRBMRegistry();
}

void ReleaseAdfRegistry()
{
	ADFClassStorage.clear();
	ADFPropsStorage.clear();
	AmfFormatStorage.clear();
	RBMClassStorage.clear();
}
