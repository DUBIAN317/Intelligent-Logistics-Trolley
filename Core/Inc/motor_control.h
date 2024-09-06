//
// Created by Pan Jianyu on 24-9-6.
//

#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H

#include "stm32f3xx_hal.h"

// 初始化电机控制系统
void Motor_Init(void);

// 设置电机速度和方向，speed 为电机速度，范围通常为 0 到 100
void Motor_SetSpeed(uint8_t motor, int16_t speed);

// 控制小车前进
void Motor_MoveForward(uint8_t speed);

// 控制小车后退
void Motor_MoveBackward(uint8_t speed);

// 控制小车左平移
void Motor_MoveLeft(uint8_t speed);

// 控制小车右平移
void Motor_MoveRight(uint8_t speed);

// 控制小车顺时针旋转
void Motor_RotateClockwise(uint8_t speed);

// 控制小车逆时针旋转
void Motor_RotateCounterclockwise(uint8_t speed);

#endif /* __MOTOR_CONTROL_H */

