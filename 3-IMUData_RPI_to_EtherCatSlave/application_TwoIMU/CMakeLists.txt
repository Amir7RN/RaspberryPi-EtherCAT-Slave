cmake_minimum_required(VERSION 3.12)
project(GetSensorData C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

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

add_library(getSensorData_lib STATIC getSensorData.cpp)

find_library(MSCL_LIBRARY mscl PATHS "/usr/share/c++-mscl")

include_directories(
	/usr/share/c++-mscl
	/usr/share/c++-mscl/source
	/usr/share/c++-mscl/Boost
	/usr/share/c++-mscl/Boost/include/boost
	/usr/share/c++-mscl/Boost/lib
	/usr/share/c++-mscl/source/mscl
)


add_executable (GetSensorData
  main.c
  slave_objectlist.c
  )
target_link_libraries(GetSensorData PRIVATE soes bcm2835 getSensorData_lib ${MSCL_LIBRARY} stdc++ pthread)
target_link_libraries(GetSensorData PRIVATE -L/usr/share/c++-mscl -lmscl)

install (TARGETS GetSensorData DESTINATION sbin)
install (PROGRAMS S60soes DESTINATION /etc/init.d)
install(TARGETS GetSensorData DESTINATION bin)
