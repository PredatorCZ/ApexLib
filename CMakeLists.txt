cmake_minimum_required(VERSION 3.3)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  message(FATAL_ERROR "X86 architecture is not supported!")
endif()

project(ApexLib)

# ~~~
# Valid targets:
#  - ApexLibStatic: if BUILD_STATIC then it's target for static library,
#                    otherwise this target will contain objects for static libraries or non-PIE executables
#  - ApexLib: objects for shared libraries or PIE executables
#
# NOTE: ApexLibStatic and ApexLib are same for WIN
# ~~~

option(USE_PIC "HavokLib target will use PIC." OFF)
option(BUILD_STATIC "Builds HavokLibStatic as a static library." OFF)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(3rd_party/PreCore)

include(${PRECORE_SOURCE_DIR}/cmake/targetex.cmake)
include(${PRECORE_SOURCE_DIR}/cmake/chartype.cmake)

set(STATIC_TYPE OBJECT)

if(BUILD_STATIC)
  set(STATIC_TYPE STATIC)
endif()

add_subdirectory(src)
