#ifndef _CAN_BUS_PROCESS_H_
#define _CAN_BUS_PROCESS_H_

#include "stdint.h"
#include "stdbool.h"
#include "hal.h"
#include "string.h"
#include "adis16265.h"

#define GIMBAL_MOTOR_NUM  2U
#define CHASSIS_MOTOR_NUM 4U
#define EXTRA_MOTOR_NUM   4U
#define UWB_NUM           1U

/* CAN Bus standard ID for motors  */
#define CAN_CHASSIS_FL_FEEDBACK_MSG_ID              0x202
#define CAN_CHASSIS_FR_FEEDBACK_MSG_ID              0x201
#define CAN_CHASSIS_BL_FEEDBACK_MSG_ID              0x203
#define CAN_CHASSIS_BR_FEEDBACK_MSG_ID              0x204
#define CAN_GIMBAL_YAW_FEEDBACK_MSG_ID              0x205
#define CAN_GIMBAL_PITCH_FEEDBACK_MSG_ID            0x206

/* CAN Bus standard ID for UWB module*/
#define CAN_UWB_MSG_ID                              0x259

/* CAN Bus standard ID for board to board communication */
#define CAN_CHASSIS_BOARD_ID                        0x101
#define CAN_GIMBAL_BOARD_ID                         0x102

#define CAN_ENCODER_RANGE           8192            // 0x2000
#define CAN_ENCODER_RADIAN_RATIO    7.669904e-4f    // 2*M_PI / 0x2000

typedef enum
{
    GIMBAL_YAW = 0,
    GIMBAL_PITCH
} gimbal_num_t;

typedef enum
{
    FRONT_LEFT = 1,
    FRONT_RIGHT = 0,
    BACK_LEFT = 2,
    BACK_RIGHT = 3
} chassis_num_t;

typedef struct
{
    uint16_t raw_angle;
    int16_t raw_current;
    int16_t current_setpoint;

    uint16_t last_raw_angle;
    uint16_t offset_raw_angle;
    int32_t round_count;
    int32_t total_ecd;
    float radian_angle; // Continuous

    bool updated;
} GimbalEncoder_canStruct;

typedef struct
{
    uint16_t raw_angle;
    int16_t raw_speed;
    int16_t act_current;
    uint8_t temperature;

    uint16_t last_raw_angle;
    uint16_t offset_raw_angle;
    uint32_t msg_count;
    int32_t round_count;
    int32_t total_ecd;
    float radian_angle; // Continuous

    bool updated;
} ChassisEncoder_canStruct;

typedef struct
{
    int16_t x_world_cm;
    int16_t y_world_cm;
    uint16_t theta;
} UWB_canStruct;

volatile GimbalEncoder_canStruct *can_getGimbalMotor(void);

volatile ChassisEncoder_canStruct *can_getChassisMotor(void);

volatile ChassisEncoder_canStruct *can_getExtraMotor(void);

volatile UWB_canStruct *can_getUWB(void);

void can_processInit(void);

void can_motorSetCurrent(CANDriver *const CANx,
                         const uint16_t EID,
                         const int16_t cm1_iq,
                         const int16_t cm2_iq,
                         const int16_t cm3_iq,
                         const int16_t cm4_iq);


#endif