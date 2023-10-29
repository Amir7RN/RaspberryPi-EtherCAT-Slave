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
