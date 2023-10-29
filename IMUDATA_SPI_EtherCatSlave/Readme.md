Stream IMU data to RPI and then Transmit to LAN 9252 using SPI communication

Using the following instruction the IMU data can be transfereed using ethercat and monitored in TwinCat.

SPI tranmist is restricted by C and IMU data is streamed using C++ code, So we need to add a wrapper for the C++ and make it as a C library:

add the following lines to the IMU c++ code (StreamData_to_RPI directory):
extern "C" {
void getSensorData(int* Pitch,int* Roll,int* Yaw,int* GyroX,int* GyroY,int* GyroZ,int* AccelX,int* AccelY,int* AccelZ) {
}

full code can be found in IMUDATA_SPI_EtherCatSlave/application/raspberry_lan9252demo/getSensorData.cpp

make the header for c++ code (IMUDATA_SPI_EtherCatSlave/application/raspberry_lan9252demo/getSensorData.h):
```
#ifndef GETSENSORDATA_H
#define GETSENSORDATA_H

#ifdef __cplusplus
extern "C" {
#endif

void getSensorData(int* IMU1_Pitch,int* IMU1_Roll,int* IMU1_Yaw,int* IMU1_GyroX,int* IMU1_GyroY,int* IMU1_GyroZ,int* IMU1_AccelX,int* IMU1_AccelY,int* IMU1_AccelZ);

#ifdef __cplusplus
}
#endif

#endif```


add the created header to main.c file which is needed for transmitting data using spi:
Check directory IMUDATA_SPI_EtherCatSlave/applications/raspberry_lan9252demo/main.c for comments and details

```#include "getSensorData.h"```

other required libraries are:
```#include <unistd.h>
#include <stdlib.h>
#include "getSensorData.h"
#include <pthread.h>
#include <string.h>
#include "lan9252_spi.c"```

GetSensor Data that is streaming from c++ code:
```

int Pitch, Roll, Yaw, GyroX, GyroY, GyroZ, AccelX, AccelY, AccelZ;
int sensorData[9];

void* Thread(void* arg) {
    int* sensorData = (int*)arg;
    int* Pitch = &sensorData[0];
    int* Roll = &sensorData[1];
    int* Yaw = &sensorData[2];
    int* GyroX = &sensorData[3];
    int* GyroY = &sensorData[4];
    int* GyroZ = &sensorData[5];
    int* AccelX = &sensorData[6];
    int* AccelY = &sensorData[7];
    int* AccelZ = &sensorData[8];

    

    while (1) {
        usleep(10);
        getSensorData(Pitch, Roll, Yaw, GyroX, GyroY, GyroZ, AccelX, AccelY, AccelZ); 
              
    }

    return NULL;
}
```

then Trasnfer it via SPI:
It is recommended to use bcm2835_spi_transfernb rather than bcm2835_spi_transmit to accurately transmit data, in order to do so I copied the ecat_slv.c content to a new .c file (lan9252_spi.c) and add it as a library to main.c code:

```
#include "lan9252_spi.c"
```
change the spi mode to mode 3 in the lan9252_spi.c (line 478)
keep the clock divider as 32 (line 484)

```
int16_t received_data = 0;

int16_t SPI_transmit_int(int data)
{
   
    int16_t spi_data[2];
    spi_data[0] = ESC_CMD_SERIAL_WRITE;
    spi_data[1] = (int16_t)(((data >> 8) & 0xFF));
    spi_data[2] = (int16_t)(data & 0xFF);
    
    
    
    bcm2835_spi_transfernb((char*)spi_data, (char*)spi_data, sizeof(spi_data));
    
    usleep(10);
    
    spi_data[0] = ESC_CMD_SERIAL_READ;
    
    bcm2835_spi_transfernb((char*)spi_data, (char*)spi_data, sizeof(spi_data));
    
    
    
    int16_t received_data_unit = (int16_t)(((int32_t)spi_data[1] << 8) | (int32_t)spi_data[2]);
    received_data = received_data_unit;
    return received_data;
    //printf("received_dataf: %d\n", received_dataf);
}
```

send SPI transferred data to the allocated memory of LAN 9252, can be tracked in xml file in the master PC:
```
int Received_data[9];

void cb_set_outputs(int Pitch, int Roll, int Yaw, int GyroX, int GyroY, int GyroZ, int AccelX, int AccelY, int AccelZ)
{

    int transmit_data[9] = {
        Pitch, Roll, Yaw, GyroX, GyroY, GyroZ, AccelX, AccelY, AccelZ
    };
    
    for (int i = 0; i < 9; i++) {
        
        if ((int)(transmit_data[i]) == 56 ) {
            Received_data[i] = SPI_transmit_int(55);
        } 
        else {
            Received_data[i] = SPI_transmit_int(transmit_data[i]);
        }
        
    }
   
    Obj.in.IMU1_Pitch = (int16_t)(Received_data[0]);
    Obj.in.IMU1_Roll = (int16_t)(Received_data[1]);
    Obj.in.IMU1_Yaw = (int16_t)(Received_data[2]);
    Obj.in.IMU1_GyroX = (int16_t)(Received_data[3]);
    Obj.in.IMU1_GyroY = (int16_t)(Received_data[4]);
    Obj.in.IMU1_GyroZ = (int16_t)(Received_data[5]);
    Obj.in.IMU1_AccelX = (int16_t)(Received_data[6]);
    Obj.in.IMU1_AccelY = (int16_t)(Received_data[7]);
    Obj.in.IMU1_AccelZ = (int16_t)(Received_data[8]);

}
```

the main_run block of c code (starting from line 114; focus on 140):
```
pthread_t thread;
    int sensorData[18]; // Array to hold sensor values

    pthread_create(&thread, NULL, Thread, sensorData);
    
   while (1)
    {
        ecat_slv();
        usleep(10);
        printf("sensorData: %d\n", sensorData[0]);
        printf("Transferred: %d\n", Obj.in.IMU1_Pitch);
        cb_set_outputs(sensorData[0],sensorData[1],sensorData[2],sensorData[3],sensorData[4],sensorData[5],sensorData[6],sensorData[7],
                        sensorData[8]);    
    }
    
    pthread_join(thread, NULL);
```

Adjust the required properties for your specific application in line 118:

```
.user_arg = "rpi4,cs1",
```

Afterward by modifying the C and C++ code (main.c and getSensorData.cpp), the CMakeList should be adjusted as follows (check IMUDATA_SPI_EtherCatSlave/applications/raspberry_lan9252demo
/CMakeLists.txt for comments and details):

```
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
```

Modify cb_set_outputs of ecat_slv.c in IMUDATA_SPI_EtherCatSlave/soes/ecat_slv.c line 226
```
void cb_set_outputs(int IMU1_Pitch, int IMU1_Roll, int IMU1_Yaw, int IMU1_GyroX, int IMU1_GyroY, int IMU1_GyroZ, int IMU1_AccelX, int IMU1_AccelY, int IMU1_AccelZ);
```

for making the executable, navigate to the directory:
```../../../IMUDATA_SPI_EtherCatSlave```

and run:
```cmake -B build -DRPI_VARIANT=ON```

```and then do cmake --build build```

run the executable in IMUDATA_SPI_EtherCatSlave/build/applications/raspberry_lan9252demo

```sudo ./GetSensorData```

Data should be stream from RPI to LAN9252 EtherCat Slave.

Copy gb_lan9252.xml file to the "C:\TwinCAT\3.1\Config\Io\EtherCAT"
and then scan the IO in the TwinCat, EtherCat Slave shoud be detected with the name "Box 5(generic)", green LED should be fixed showing the data is streamed.
