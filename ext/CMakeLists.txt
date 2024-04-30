
# Compile as UNIX
add_compile_definitions(-DUNIX=1)

find_package(Boost
  1.74.0
  REQUIRED
  COMPONENTS filesystem system date_time chrono thread
  )
find_package(PkgConfig REQUIRED)
pkg_check_modules(
  libusb REQUIRED libusb-1.0
  hidapi-libusb REQUIRED
  )

# Source files
file(GLOB SRC
  "DLL430_v3/src/TI/DLL430/EEM/CycleCounter.cpp"
  "DLL430_v3/src/*.cpp"
  "DLL430_v3/src/TI/DLL430/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/BreakpointManager/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/CycleCounter/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/EemRegisters/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/EmulationManager/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/Exceptions/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/Sequencer/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/SoftwareBreakpoints/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/StateStorage430/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/Trace/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/Trigger/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/TriggerCondition/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/TriggerManager/*.cpp"
  "DLL430_v3/src/TI/DLL430/EM/VariableWatch/*.cpp"
  "DLL430_v3/src/TI/DLL430/EnergyTrace_TSPA/*.cpp"
  "DLL430_v3/src/TI/DLL430/logging/*.cpp"
  "DLL430_v3/src/TI/DLL430/TemplateDeviceDb/*.cpp"
  "DLL430_v3/src/TI/DLL430/DeviceDb/*.cpp"
  "DLL430_v3/src/TI/DLL430/MSP432/*.cpp"
  "DLL430_v3/src/TI/DLL430/warnings/*.cpp"
  "ThirdParty/src/*.cpp"
  "ThirdParty/BSL430_DLL/BSL430_DLL/Connections/*.cpp"
  "ThirdParty/BSL430_DLL/BSL430_DLL/Utility_Classes/*.cpp"
  "ThirdParty/BSL430_DLL/BSL430_DLL/Packet_Handlers/*.cpp"
  "ThirdParty/BSL430_DLL/BSL430_DLL/*.cpp"
  "ThirdParty/BSL430_DLL/BSL430_DLL/Physical_Interfaces/*.cpp"
  )
  
add_library(msp430 SHARED ${SRC})

#set(CMAKE_CXX_COMPILER "g++")
set(COMPILE_FLAGS -std=c++0x -fvisibility=hidden -fvisibility-inlines-hidden -I/usr/include/hidapi)
set(LINK_FLAGS -Wl,-soname,-Wl,-Bdynamic)

# Set compilation and link flags
target_compile_options(msp430 BEFORE PRIVATE "$<$<CONFIG:DEBUG>:${COMPILE_FLAGS}>")
target_compile_options(msp430 BEFORE PRIVATE "$<$<CONFIG:RELEASE>:${COMPILE_FLAGS}>")
target_link_options(msp430 BEFORE PRIVATE "$<$<CONFIG:DEBUG>:${LINK_FLAGS}>")
target_link_options(msp430 BEFORE PRIVATE "$<$<CONFIG:RELEASE>:${LINK_FLAGS}>")

#include headers
target_include_directories(msp430 PUBLIC
  DLL430_v3/src/TI/DLL430
  DLL430_v3/include
  DLL430_v3/src/TI/DLL430/EnergyTrace_TSPA
  Bios/include
  ThirdParty/include
  ThirdParty/BSL430_DLL
  ThirdParty/BSL430_DLL/BSL430_DLL/Connections
  ThirdParty/BSL430_DLL/BSL430_DLL/Packet_Handlers
  ThirdParty/BSL430_DLL/BSL430_DLL/Physical_Interfaces
  ThirdParty/BSL430_DLL/BSL430_DLL/Utility_Classes
  )

target_include_directories(msp430 PRIVATE
  ${Boost_INCLUDE_DIRS}
  )

target_link_libraries(msp430
  PRIVATE
  #${Boost_LIBARIES}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_DATE_TIME_LIBRARY}
  ${Boost_CHRONO_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  #${libusb-1.0_LIBRARIES}
  #${hidapi-libusb_LIBRARIES}
  usb-1.0
  hidapi-libusb
  rt
  pthread
  )

