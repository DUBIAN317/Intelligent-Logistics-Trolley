//
// Created by Pan Jianyu on 24-9-6.
//

#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f3xx_hal.h"

// 初始化舵机
void Servo_Init(void);

// 设置舵机角度，angle的范围通常是0到180度
void Servo_SetAngle(uint8_t servo, uint16_t angle);

#endif /* __SERVO_H */


#endif //SERVO_CONTROL_H
