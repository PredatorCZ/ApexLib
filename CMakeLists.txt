cmake_minimum_required(VERSION 3.3)

project(ApexLib)

if(NOT TARGETEX_LOCATION)
	set(TARGETEX_LOCATION 3rd_party/PreCore/cmake)
	include(${TARGETEX_LOCATION}/targetex.cmake)
	include(${TARGETEX_LOCATION}/chartype.cmake)
endif()

set(CMAKE_CXX_STANDARD 11)

build_target(
	TYPE STATIC
	SOURCES
		3rd_party/PreCore/datas/MasterPrinter.cpp
		3rd_party/PreCore/datas/reflector.cpp
		3rd_party/pugixml/src/pugixml.cpp
		3rd_party/zstd/lib/common/debug.c
		3rd_party/zstd/lib/common/entropy_common.c
		3rd_party/zstd/lib/common/error_private.c
		3rd_party/zstd/lib/common/fse_decompress.c
		3rd_party/zstd/lib/common/pool.c
		3rd_party/zstd/lib/common/threading.c
		3rd_party/zstd/lib/common/xxhash.c
		3rd_party/zstd/lib/common/zstd_common.c
		3rd_party/zstd/lib/compress/fse_compress.c
		3rd_party/zstd/lib/compress/hist.c
		3rd_party/zstd/lib/compress/huf_compress.c
		3rd_party/zstd/lib/compress/zstdmt_compress.c
		3rd_party/zstd/lib/compress/zstd_compress.c
		3rd_party/zstd/lib/compress/zstd_double_fast.c
		3rd_party/zstd/lib/compress/zstd_fast.c
		3rd_party/zstd/lib/compress/zstd_lazy.c
		3rd_party/zstd/lib/compress/zstd_ldm.c
		3rd_party/zstd/lib/compress/zstd_opt.c
		3rd_party/zstd/lib/decompress/huf_decompress.c
		3rd_party/zstd/lib/decompress/zstd_ddict.c
		3rd_party/zstd/lib/decompress/zstd_decompress.c
		3rd_party/zstd/lib/decompress/zstd_decompress_block.c
		src/ADF.cpp
		src/ADFReg.cpp
		src/AmfMesh.cpp
		src/AmfModel.cpp
		src/AVTX.cpp
		src/DeformPoints.cpp
		src/lookup3.c
		src/RBM.cpp
		src/RBMClassesJC2.cpp
		src/RBMClassesJC3.cpp
		src/RBMReg.cpp
		src/RBNClasses.cpp
		src/StreamPatch.cpp
		src/StuntAreas.cpp
	INCLUDES
		src
		include
		3rd_party/PreCore
		3rd_party/pugixml/src
		3rd_party/zstd/lib
		3rd_party/zstd/lib/common
	NO_PROJECT_H
	NO_VERINFO
)

if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")
endif()