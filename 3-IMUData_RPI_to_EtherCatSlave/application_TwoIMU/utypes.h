#ifndef __UTYPES_H__
#define __UTYPES_H__

#include "cc.h"

/* Object dictionary storage */

typedef struct {
    /* Identity */

    uint32_t serial;

    /* Inputs */

    struct {
        int16_t IMU1_Pitch;
        int16_t IMU1_Roll;
        int16_t IMU1_Yaw;
        int16_t IMU1_GyroX;
        int16_t IMU1_GyroY;
        int16_t IMU1_GyroZ;
        int16_t IMU1_AccelX;
        int16_t IMU1_AccelY;
        int16_t IMU1_AccelZ;
        int16_t IMU1_Quat0;
        int16_t IMU1_Quat1;
        int16_t IMU1_Quat2;
        int16_t IMU1_Quat3;
        int16_t IMU1_add0;
        int16_t IMU1_add1;
        int16_t IMU1_add2;
        int16_t IMU2_Pitch;
        int16_t IMU2_Roll;
        int16_t IMU2_Yaw;
        int16_t IMU2_GyroX;
        int16_t IMU2_GyroY;
        int16_t IMU2_GyroZ;
        int16_t IMU2_AccelX;
        int16_t IMU2_AccelY;
        int16_t IMU2_AccelZ;
        int16_t IMU2_Quat0;
        int16_t IMU2_Quat1;
        int16_t IMU2_Quat2;
        int16_t IMU2_Quat3;
        int16_t IMU2_add0;
        int16_t IMU2_add1;
        int16_t IMU2_add2;
        int16_t IMU3_Pitch;
        int16_t IMU3_Roll;
        int16_t IMU3_Yaw;
        int16_t IMU3_GyroX;
        int16_t IMU3_GyroY;
        int16_t IMU3_GyroZ;
        int16_t IMU3_AccelX;
        int16_t IMU3_AccelY;
        int16_t IMU3_AccelZ;
        int16_t IMU3_Quat0;
        int16_t IMU3_Quat1;
        int16_t IMU3_Quat2;
        int16_t IMU3_Quat3;
        int16_t IMU3_add0;
        int16_t IMU3_add1;
        int16_t IMU3_add2;
        int16_t IMU4_Pitch;
        int16_t IMU4_Roll;
        int16_t IMU4_Yaw;
        int16_t IMU4_GyroX;
        int16_t IMU4_GyroY;
        int16_t IMU4_GyroZ;
        int16_t IMU4_AccelX;
        int16_t IMU4_AccelY;
        int16_t IMU4_AccelZ;
        int16_t IMU4_Quat0;
        int16_t IMU4_Quat1;
        int16_t IMU4_Quat2;
        int16_t IMU4_Quat3;
        int16_t IMU4_add0;
        int16_t IMU4_add1;
        int16_t IMU4_add2;        
        uint8_t digital_40;
        uint8_t digital_41;
        uint8_t digital_42;
        uint8_t digital_43;
        uint8_t digital_44;
        uint8_t digital_45;
        uint8_t digital_46;
        uint8_t digital_47;
        uint8_t digital_48;
        uint8_t digital_49;
        uint8_t digital_50;
        uint8_t digital_51;
        uint8_t digital_52;
        uint8_t digital_53;
        uint8_t digital_54;
        uint8_t digital_55;
        uint8_t digital_56;
        uint8_t digital_57;
        uint8_t digital_58;
        uint8_t digital_59;
        uint8_t digital_60;
        uint8_t digital_61;
        uint8_t digital_62;
        uint8_t digital_63;
        float analog_0;
        float analog_1;
        float analog_2;
        float analog_3;
        float analog_4;
        float analog_5;
        int32_t integer_0;
        int32_t integer_1;
    } in;

    /* Outputs */

    struct {
        uint32_t machine_status_word;
        uint32_t active_fault;
        uint32_t fault_history;
        uint32_t heartbeat;
        uint16_t joint_0_statusword;
        uint16_t joint_1_statusword;
        uint16_t joint_2_statusword;
        uint16_t joint_3_statusword;
        uint16_t joint_4_statusword;
        uint16_t joint_5_statusword;
        uint16_t joint_6_statusword;
        uint16_t joint_7_statusword;
        uint16_t joint_8_statusword;
        uint16_t joint_9_statusword;
        int32_t joint_0_actual_position;
        int32_t joint_1_actual_position;
        int32_t joint_2_actual_position;
        int32_t joint_3_actual_position;
        int32_t joint_4_actual_position;
        int32_t joint_5_actual_position;
        int32_t joint_6_actual_position;
        int32_t joint_7_actual_position;
        int32_t joint_8_actual_position;
        int32_t joint_9_actual_position;
        uint8_t digital_0;
        uint8_t digital_1;
        uint8_t digital_2;
        uint8_t digital_3;
        uint8_t digital_4;
        uint8_t digital_5;
        uint8_t digital_6;
        uint8_t digital_7;
        uint8_t digital_8;
        uint8_t digital_9;
        uint8_t digital_10;
        uint8_t digital_11;
        uint8_t digital_12;
        uint8_t digital_13;
        uint8_t digital_14;
        uint8_t digital_15;
        uint8_t digital_16;
        uint8_t digital_17;
        uint8_t digital_18;
        uint8_t digital_19;
        uint8_t digital_20;
        uint8_t digital_21;
        uint8_t digital_22;
        uint8_t digital_23;
        uint8_t digital_24;
        uint8_t digital_25;
        uint8_t digital_26;
        uint8_t digital_27;
        uint8_t digital_28;
        uint8_t digital_29;
        uint8_t digital_30;
        uint8_t digital_31;
        uint8_t digital_32;
        uint8_t digital_33;
        uint8_t digital_34;
        uint8_t digital_35;
        uint8_t digital_36;
        uint8_t digital_37;
        uint8_t digital_38;
        uint8_t digital_39;
        uint8_t digital_40;
        uint8_t digital_41;
        uint8_t digital_42;
        uint8_t digital_43;
        uint8_t digital_44;
        uint8_t digital_45;
        uint8_t digital_46;
        uint8_t digital_47;
        uint8_t digital_48;
        uint8_t digital_49;
        uint8_t digital_50;
        uint8_t digital_51;
        uint8_t digital_52;
        uint8_t digital_53;
        uint8_t digital_54;
        uint8_t digital_55;
        uint8_t digital_56;
        uint8_t digital_57;
        uint8_t digital_58;
        uint8_t digital_59;
        uint8_t digital_60;
        uint8_t digital_61;
        uint8_t digital_62;
        uint8_t digital_63;
        float analog_0;
        float analog_1;
        float analog_2;
        float analog_3;
        float analog_4;
        float analog_5;
        int32_t integer_0;
        int32_t integer_1;
    } out;

    /* Parameters */

    struct {
        uint32_t Multiplier;
    } Parameters;

    struct {
        uint32_t SyncErrorCounterLimit;
    }ErrorSettings;
} _Objects;

extern _Objects Obj;


/* Manufacturer specific data */

typedef struct
{
    struct
    {
        uint16_t SyncType;
        uint32_t CycleTime;
        uint32_t ShiftTime;
        uint16_t SyncTypeSupport;
        uint32_t MinCycleTime;
        uint32_t CalcCopyTime;
        uint32_t MinDelayTime;
        uint16_t GetCycleTime;
        uint32_t DelayTime;
        uint32_t Sync0CycleTime;
        uint16_t SMEventMissedCnt;
        uint16_t CycleTimeTooSmallCnt;
        uint16_t ShiftTimeTooSmallCnt;
        uint16_t RxPDOToggleFailed;
        uint32_t MinCycleDist;
        uint32_t MaxCycleDist;
        uint32_t MinSMSYNCDist;
        uint32_t MaxSMSYNCDist;
        uint8_t Reserved0x18;
        uint8_t Reserved0x1C;
        uint8_t Reserved0x1D;
        uint8_t Reserved0x1E;
        uint8_t Reserved0x1F;
        uint8_t SyncError;
    }  SyncMgrParam;

}  _Mbuffer;





extern _Mbuffer Mb;


#endif /* __UTYPES_H__ */
