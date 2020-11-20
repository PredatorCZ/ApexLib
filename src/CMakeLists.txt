# Get ZSTD
set(ZSTD_PATH ${PROJECT_SOURCE_DIR}/3rd_party/zstd/lib)
file(GLOB ZSTDCommonSources ${ZSTD_PATH}/common/*.c)
file(GLOB ZSTDCompressSources ${ZSTD_PATH}/compress/*.c)
file(GLOB ZSTDDecompressSources ${ZSTD_PATH}/decompress/*.c)
file(GLOB ZSTDDictBuilderSources ${ZSTD_PATH}/dictBuilder/*.c)
file(GLOB ZSTDDeprecatedSources ${ZSTD_PATH}/deprecated/*.c)
# Get pugi
set(PUGI_PATH ${PROJECT_SOURCE_DIR}/3rd_party/pugixml/src)

file(GLOB_RECURSE CORE_SOURCE_FILES *.cpp)

build_target(
  NAME
  ApexLibStatic
  TYPE
  ${STATIC_TYPE}
  SOURCES
  ${CORE_SOURCE_FILES}
  ${PUGI_PATH}/pugixml.cpp
  ${ZSTDCommonSources}
  ${ZSTDDecompressSources}
  NO_VERINFO
  NO_PROJECT_H)

target_include_directories(ApexLibStatic PUBLIC ${PROJECT_SOURCE_DIR}/include
                                                ${PUGI_PATH} ${ZSTD_PATH})

set_precore_sources(ApexLibStatic master_printer reflector reflector_xml
                    uni_format)

if(USE_PIC AND _is_cool_compiler)
  build_target(
    NAME
    ApexLib
    TYPE
    OBJECT
    SOURCES
    ${CORE_SOURCE_FILES}
    ${PUGI_PATH}/pugixml.cpp
    ${ZSTDCommonSources}
    ${ZSTDDecompressSources}
    POSITION_INDEPENDENT_CODE
    ON
    NO_VERINFO
    NO_PROJECT_H)

  target_include_directories(ApexLibStatic PUBLIC ${PROJECT_SOURCE_DIR}/include
                                                  ${PUGI_PATH} ${ZSTD_PATH})

  set_precore_sources(ApexLib master_printer reflector reflector_xml uni_format)
else()
  add_library(ApexLib ALIAS ApexLibStatic)
endif()
