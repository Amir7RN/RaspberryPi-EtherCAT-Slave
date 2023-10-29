# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Project definition for the 'GetSensorData' project
project(GetSensorData C CXX)

# Set the C standard to C11 and C++ standard to C++17
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# If the C++ compiler ID matches GNU or Clang, add compile options
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        $<$<COMPILE_LANGUAGE:CXX>:-Wall>
        $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-unused-parameter>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-ignored-qualifiers>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-conversion>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-reorder>
    )
endif()

# Create a static library named 'getSensorData_lib' from 'getSensorData.cpp'
add_library(getSensorData_lib STATIC getSensorData.cpp)

# Find the 'MSCL_LIBRARY' and set the search path to '/usr/share/c++-mscl'
find_library(MSCL_LIBRARY mscl PATHS "/usr/share/c++-mscl")

# Include directories for header files
include_directories(
	/usr/share/c++-mscl
	/usr/share/c++-mscl/source
	/usr/share/c++-mscl/Boost
	/usr/share/c++-mscl/Boost/include/boost
	/usr/share/c++-mscl/Boost/lib
	/usr/share/c++-mscl/source/mscl
)


# Create an executable named 'GetSensorData' from 'main.c' and 'slave_objectlist.c'
add_executable (GetSensorData
  main.c
  slave_objectlist.c
  )

  # Link the necessary libraries and dependencies to the 'GetSensorData' executable
target_link_libraries(GetSensorData PRIVATE soes bcm2835 getSensorData_lib ${MSCL_LIBRARY} stdc++ pthread)

# Link the 'MSCL_LIBRARY' to the 'GetSensorData' executable
target_link_libraries(GetSensorData PRIVATE -L/usr/share/c++-mscl -lmscl)

# Install the 'GetSensorData' executable to the 'sbin' directory
install (TARGETS GetSensorData DESTINATION sbin)

# Install the 'S60soes' program to the '/etc/init.d' directory
install (PROGRAMS S60soes DESTINATION /etc/init.d)

# Install the 'GetSensorData' executable to the 'bin' directory
install(TARGETS GetSensorData DESTINATION bin)
