#include <stdio.h>
#include "ecat_slv.h"
#include "utypes.h"
#include <bcm2835.h>
#include <unistd.h>
#include <stdlib.h>
#include "getSensorData.h"
#include <pthread.h>
#include <string.h>
#include "lan9252_spi.c"

/* Application variables */
_Objects Obj;
_Mbuffer Mb;

// SPI Constants


void cb_get_inputs(void) {
}


void GPIO_init(void) {
    bcm2835_init();
}

int IMU1_Pitch, IMU1_Roll, IMU1_Yaw, IMU1_GyroX, IMU1_GyroY, IMU1_GyroZ, IMU1_AccelX, IMU1_AccelY, IMU1_AccelZ;
int IMU2_Pitch, IMU2_Roll, IMU2_Yaw, IMU2_GyroX, IMU2_GyroY, IMU2_GyroZ, IMU2_AccelX, IMU2_AccelY, IMU2_AccelZ;
int sensorData[18];

void* Thread(void* arg) {
    int* sensorData = (int*)arg;
    int* IMU1_Pitch = &sensorData[0];
    int* IMU1_Roll = &sensorData[1];
    int* IMU1_Yaw = &sensorData[2];
    int* IMU1_GyroX = &sensorData[3];
    int* IMU1_GyroY = &sensorData[4];
    int* IMU1_GyroZ = &sensorData[5];
    int* IMU1_AccelX = &sensorData[6];
    int* IMU1_AccelY = &sensorData[7];
    int* IMU1_AccelZ = &sensorData[8];
    
    int* IMU2_Pitch = &sensorData[9];
    int* IMU2_Roll = &sensorData[10];
    int* IMU2_Yaw = &sensorData[11];
    int* IMU2_GyroX = &sensorData[12];
    int* IMU2_GyroY = &sensorData[13];
    int* IMU2_GyroZ = &sensorData[14];
    int* IMU2_AccelX = &sensorData[15];
    int* IMU2_AccelY = &sensorData[16];
    int* IMU2_AccelZ = &sensorData[17];

    

    while (1) {
        usleep(10);
        getSensorData(IMU1_Pitch, IMU1_Roll, IMU1_Yaw, IMU1_GyroX, IMU1_GyroY, IMU1_GyroZ, IMU1_AccelX, IMU1_AccelY, IMU1_AccelZ,
        IMU2_Pitch, IMU2_Roll, IMU2_Yaw, IMU2_GyroX, IMU2_GyroY, IMU2_GyroZ, IMU2_AccelX, IMU2_AccelY, IMU2_AccelZ); 
              
    }

    return NULL;
}


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

int Received_data[18];

void cb_set_outputs(int IMU1_Pitch, int IMU1_Roll, int IMU1_Yaw, int IMU1_GyroX, int IMU1_GyroY, int IMU1_GyroZ, int IMU1_AccelX, int IMU1_AccelY, int IMU1_AccelZ,
                    int IMU2_Pitch, int IMU2_Roll, int IMU2_Yaw, int IMU2_GyroX, int IMU2_GyroY, int IMU2_GyroZ, int IMU2_AccelX, int IMU2_AccelY, int IMU2_AccelZ)
{

    int transmit_data[18] = {
        IMU1_Pitch, IMU1_Roll, IMU1_Yaw, IMU1_GyroX, IMU1_GyroY, IMU1_GyroZ, IMU1_AccelX, IMU1_AccelY, IMU1_AccelZ,
        IMU2_Pitch, IMU2_Roll, IMU2_Yaw, IMU2_GyroX, IMU2_GyroY, IMU2_GyroZ, IMU2_AccelX, IMU2_AccelY, IMU2_AccelZ
    };
    
    for (int i = 0; i < 18; i++) {
        
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
    
    Obj.in.IMU2_Pitch = (int16_t)(Received_data[9]);
    Obj.in.IMU2_Roll = (int16_t)(Received_data[10]);
    Obj.in.IMU2_Yaw = (int16_t)(Received_data[11]);
    Obj.in.IMU2_GyroX = (int16_t)(Received_data[12]);
    Obj.in.IMU2_GyroY = (int16_t)(Received_data[13]);
    Obj.in.IMU2_GyroZ = (int16_t)(Received_data[14]);
    Obj.in.IMU2_AccelX = (int16_t)(Received_data[15]);
    Obj.in.IMU2_AccelY = (int16_t)(Received_data[16]);
    Obj.in.IMU2_AccelZ = (int16_t)(Received_data[17]);

}


int main_run (void * arg)
{
   static esc_cfg_t config =
   {
      .user_arg = "rpi4,cs1",
      .use_interrupt = 0,
      .watchdog_cnt = 150,
      .set_defaults_hook = NULL,
      .pre_state_change_hook = NULL,
      .post_state_change_hook = NULL,
      .application_hook = NULL,
      .safeoutput_override = NULL,
      .pre_object_download_hook = NULL,
      .post_object_download_hook = NULL,
      .rxpdo_override = NULL,
      .txpdo_override = NULL,
      .esc_hw_interrupt_enable = NULL,
      .esc_hw_interrupt_disable = NULL,
      .esc_hw_eep_handler = NULL,
      .esc_check_dc_handler = NULL,
   };

   GPIO_init();
   ecat_slv_init (&config);
   
   
    pthread_t thread;
    int sensorData[18]; // Array to hold sensor values

    pthread_create(&thread, NULL, Thread, sensorData);
    
   while (1)
    {
        ecat_slv();
        usleep(10);
        printf("sensorDataIMU1: %d\n", sensorData[0]);
        printf("TransferredIMU1: %d\n", Obj.in.IMU1_Pitch);
        printf("sensorDataIMU2: %d\n", sensorData[9]);
        printf("TransferredIMU2: %d\n", Obj.in.IMU2_Pitch);
        cb_set_outputs(sensorData[0],sensorData[1],sensorData[2],sensorData[3],sensorData[4],sensorData[5],sensorData[6],sensorData[7],
                        sensorData[8],sensorData[9],sensorData[10],sensorData[11],sensorData[12],sensorData[13],sensorData[14],sensorData[15],sensorData[16],
        sensorData[17]);    
    }
    
    pthread_join(thread, NULL);

    return 0;

}

int main (void)
{
   
   main_run (NULL);
   return 0;
}

