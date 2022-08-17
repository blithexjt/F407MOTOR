#ifndef MOTOR_H
#define MOTOR_H

#include "sys.h"
#include "timer.h"

#define MOTORX_DIR_Forward()	    GPIO_SetBits( DIR_X_port, Dir_X_pin);
#define MOTORX_DIR_Backward()	  GPIO_ResetBits( DIR_X_port, Dir_X_pin);

#define MOTORY_DIR_Forward()	    GPIO_SetBits( DIR_Y_port, Dir_Y_pin);
#define MOTORY_DIR_Backward()	  GPIO_ResetBits( DIR_Y_port, Dir_Y_pin);
#define DRV8889  1

#define Move_3_2_CM   (200*100*(3.2))

 static u32 g_positionx = 0;
 static u32 g_positiony = 0;

 static u32 g_speed = 0;

 static u32 g_pulsex = 0;
 static u32 g_pulsey = 0;

 static s32 g_stepx = 0;
 static s32 g_stepy = 0;

 static u8 g_HoldCurrent = 0;
 

typedef enum
{
    HoldCurrent_en = 0,
    HoldCurrent_non,
}HoldCurrent;



void MotorStart(u8 MotorNum,double current);
void MotorStop(u8 MotorNum,double current);
void MotorInit(void);


void MotorSetSpeed(u8 motor,double speed);
void MotorSetCurrent(u8 Motor, u8 current);



void MoveBackward(u8 Motor, u32 step);
void MoveForward(u8 Motor, u32 step);


void MotorRun(u8 Motor, u32 current,double speed, float length);


 
 #endif
