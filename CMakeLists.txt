cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 98)
set(PROJECT_NAME bio_feedback_xr)

set(${PROJECT_NAME}_BOARD unowifi)
# set(ARDUINO_CPU)
project(${PROJECT_NAME})

# Define additional source and header files or default arduino sketch files
set(${PROJECT_NAME}_SRCS bio_feedback_xr.ino BluetoothService.cpp DisplayManager.cpp ConnectionCallbacks.cpp
        ECGReader.cpp)
set(${PROJECT_NAME}_HDRS BluetoothService.h DisplayManager.h ECGReader.h)

### Additional static libraries to include in the target.
# set(${PROJECT_NAME}_LIBS)

### Main sketch file
# set(${PROJECT_NAME}_SKETCH bio_feedback_xr.ino)

### Add project directories into the build
# add_subdirectory()

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

# For nested library sources replace ${LIB_NAME} with library name for each library
# set(_RECURSE true)

#### Additional settings for programmer. From programmers.txt
set(${PROJECT_NAME}_PROGRAMMER avrisp)
set(${PROJECT_NAME}_PORT /dev/cu.Bluetooth-Incoming-Port)
set(unowifi.upload.speed 9600)

## Verbose build process
set(${PROJECT_NAME}_AFLAGS -v)

set(LIB_PATHS
        "/Users/jtanaka/Documents/Arduino/libraries/TFT_eSPI"
        "/Users/jtanaka/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/libraries/BLE/src/"
        )

add_compile_definitions(CONFIG_BT_ENABLED)

function(set_custom_libs)
 set(TMP "")
 foreach(arg IN LISTS ARGV)
  set(TMP "${TMP} -I\"${arg}\"")
 endforeach()
 set(CUSTOM_LIBS "${TMP}" PARENT_SCOPE)
endfunction()

set_custom_libs(${LIB_PATHS})

generate_arduino_firmware(${PROJECT_NAME})


#print_board_list()
#print_programmer_list()
