cmake_minimum_required(VERSION 3.15...3.27)
project(python_mspfet)
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

set(CMAKE_CXX_COMPILER "g++")

include_directories(
  )

# Add compile definitions
add_compile_definitions(-DUNIX=1)

# Compile msp430 into library
add_subdirectory(ext)

# Use separate definitions below to allow for linking in libmsp430.
nanobind_add_module(mspfet NOMINSIZE bindings/mspfet.cpp)
target_link_libraries(mspfet PRIVATE msp430)
