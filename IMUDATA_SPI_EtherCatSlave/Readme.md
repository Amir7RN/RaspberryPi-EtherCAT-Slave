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


add the created header to main.c file which is needed for trasmitting data using spi:
Directory: IMUDATA_SPI_EtherCatSlave/applications/raspberry_lan9252demo/main.c

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

send SPI transferred data to the allocated memmory of LAN 9252, can be tracked in xml file in the master PC:
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


