# Stream IMU data to RPI and then Transmit to LAN 9252 using SPI communication

This guide explains how to transmit IMU data via EtherCAT and monitor it in TwinCat. The SPI transmission is limited to C, so we create a C library to wrap the C++ code for streaming IMU data. 

## Modify the IMU C++ Code
Add the following lines to the IMU C++ code (found in the "StreamData_to_RPI" directory):

```
extern "C" {
void getSensorData(int* Pitch, int* Roll, int* Yaw, int* GyroX, int* GyroY, int* GyroZ, int* AccelX, int* AccelY, int* AccelZ) {
}
```

You can find the full code in "IMUDATA_SPI_EtherCatSlave/application/raspberry_lan9252demo/getSensorData.cpp."

## Create a Header for the C++ Code
Create a header file for the C++ code (named "getSensorData.h") with the following content:


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

#endif
```


Add this header to your main C code, which is needed for transmitting data using SPI. Include it in the "main.c" file (The source code can be found in the SOES GitHub repository.):

Check directory IMUDATA_SPI_EtherCatSlave/applications/raspberry_lan9252demo/main.c for comments and details

```
#include "getSensorData.h"
```

Make sure to include other required libraries, such as "unistd.h," "stdlib.h".


## Stream Sensor Data from C++

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

## Transmit Data via SPI
Use SPI to transfer data from the Raspberry Pi to the allocated memory of the LAN 9252.
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

## Sending SPI Transferred Data to LAN 9252 Memory

This section explains how to send data transferred via SPI to the allocated memory of the LAN 9252 device. This data can be monitored and tracked in the gb_lan.xml file on the master PC (The original gb_lan9252.XML and objectlist.c were downloaded from https://www.github.com/glowbuzzer/gblan9252_soes).

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
The cb_set_outputs function takes sensor data (Pitch, Roll, Yaw, GyroX, GyroY, GyroZ, AccelX, AccelY, AccelZ) and processes it to be transmitted via SPI to the LAN 9252 memory. This process ensures data synchronization between devices.



## Main Program Execution
In the main C code, from line 114 and onwards, a dedicated thread is created to handle the sensor data. This thread is responsible for retrieving data and managing its transmission.
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

This code block ensures the continuous execution of the EtherCAT slave's functionality while concurrently handling sensor data. Please adjust the parameters in line 118 (.user_arg = "rpi4,cs1") to match your specific application requirements.


## CMake Configuration
To compile and build the project, the CMakeLists file needs to be configured correctly. Be sure to adjust it as follows in the IMUDATA_SPI_EtherCatSlave/applications/raspberry_lan9252demo/CMakeLists.txt file:

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

## Building the Executable
To create the executable, navigate to the "IMUDATA_SPI_EtherCatSlave" directory and run the following commands:

```cmake -B build -DRPI_VARIANT=ON```

```and then do cmake --build build```

## Running the Application
Run the executable located in "IMUDATA_SPI_EtherCatSlave/build/applications/raspberry_lan9252demo" using the following command:

```sudo ./GetSensorData```

Data should now be streamed from the Raspberry Pi to the LAN 9252 EtherCAT Slave.


## Configuration in TwinCAT
Copy the "gb_lan9252.xml" file to "C:\TwinCAT\3.1\Config\Io\EtherCAT" and scan the I/O in TwinCAT. The EtherCAT Slave should be detected with the name "Box 5(generic)," and the green LED should be fixed, indicating that data is being streamed.


