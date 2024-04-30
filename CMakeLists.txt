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

include_directories(
  )

# Use separate definitions below to allow for linking in libmsp430.
#nanobind_add_module(python_mspfet NOMINSIZE python_mspfet.cpp)

# Add compile definitions
add_compile_definitions(-DUNIX=1)

# Compile msp430 into library
add_subdirectory(ext)

# Build the core parts of nanobind once
nanobind_build_library(nanobind SHARED)

# Compile an extension library
add_library(mspfet MODULE mspfet.cpp)

# .. and link it against the nanobind parts
target_link_libraries(mspfet PRIVATE nanobind msp430)

# .. enable size optimizations
nanobind_opt_size(mspfet)

# .. enable link time optimization
nanobind_lto(mspfet)

# .. set the default symbol visibility to 'hidden'
nanobind_set_visibility(mspfet)

# .. strip unneeded symbols and debug info from the binary (only active in release builds)
nanobind_strip(mspfet)

# .. disable the stack protector
nanobind_disable_stack_protector(mspfet)

# .. set the Python extension suffix
nanobind_extension(mspfet)

# .. set important compilation flags
nanobind_compile_options(mspfet)

# .. set important linker flags
nanobind_link_options(mspfet)
