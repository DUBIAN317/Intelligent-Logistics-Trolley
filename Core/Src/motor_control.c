//
// Created by Pan Jianyu on 24-9-6.
//

#include "motor_control.h"

// 定义 PWM 信号周期和脉宽范围
#define MOTOR_TIM_HANDLE1    htim2
#define MOTOR_TIM_HANDLE2    htim3
#define MOTOR_CHANNEL_1     TIM_CHANNEL_1
#define MOTOR_CHANNEL_2     TIM_CHANNEL_2
#define MOTOR_CHANNEL_3     TIM_CHANNEL_3
#define MOTOR_CHANNEL_4     TIM_CHANNEL_4

#define MOTOR_MIN_PULSE_WIDTH 1000   // 最小脉宽 (us)
#define MOTOR_MAX_PULSE_WIDTH 2000   // 最大脉宽 (us)
#define MOTOR_PULSE_PERIOD    20000  // PWM 周期 (us) 对应 50Hz

static TIM_HandleTypeDef htim2;
static TIM_HandleTypeDef htim3;

void Motor_Init(void) {
    // 使能 TIM2 和 TIM3 时钟
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();

    // 配置 TIM2
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0; // 不分频
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = MOTOR_PULSE_PERIOD - 1; // PWM 周期
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim2);

    // 配置 TIM3
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 0; // 不分频
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = MOTOR_PULSE_PERIOD - 1; // PWM 周期
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim3);

    // 配置 TIM2 PWM 通道
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // 配置通道 1 和 2 (电机 1 和 电机 2)
    sConfigOC.Pulse = 0; // 初始脉宽
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, MOTOR_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, MOTOR_CHANNEL_2);

    // 配置 TIM3 PWM 通道
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, MOTOR_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, MOTOR_CHANNEL_4);

    // 启动 PWM 输出
    HAL_TIM_PWM_Start(&htim2, MOTOR_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, MOTOR_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, MOTOR_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, MOTOR_CHANNEL_4);
}

void Motor_SetSpeed(uint8_t motor, int16_t speed) {
    // 速度范围 0 到 100
    if (speed < 0) speed = 0;
    if (speed > 100) speed = 100;

    // 计算脉宽 (us)
    uint16_t pulse_width = MOTOR_MIN_PULSE_WIDTH + (speed * (MOTOR_MAX_PULSE_WIDTH - MOTOR_MIN_PULSE_WIDTH) / 100);

    // 计算定时器的比较值
    uint32_t compare_value = (pulse_width * (MOTOR_PULSE_PERIOD)) / 10000; // 转换为定时器的计数值

    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = compare_value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // 根据电机编号选择对应的通道
    if (motor == 1) {
        HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, MOTOR_CHANNEL_1);
    } else if (motor == 2) {
        HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, MOTOR_CHANNEL_2);
    } else if (motor == 3) {
        HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, MOTOR_CHANNEL_3);
    } else if (motor == 4) {
        HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, MOTOR_CHANNEL_4);
    }

    // 更新 PWM 信号
    HAL_TIM_PWM_Start(&htim2, MOTOR_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, MOTOR_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, MOTOR_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, MOTOR_CHANNEL_4);
}

void Motor_MoveForward(uint8_t speed) {
    Motor_SetSpeed(1, speed);
    Motor_SetSpeed(2, speed);
    Motor_SetSpeed(3, speed);
    Motor_SetSpeed(4, speed);
}

void Motor_MoveBackward(uint8_t speed) {
    Motor_SetSpeed(1, -speed);
    Motor_SetSpeed(2, -speed);
    Motor_SetSpeed(3, -speed);
    Motor_SetSpeed(4, -speed);
}

void Motor_MoveLeft(uint8_t speed) {
    Motor_SetSpeed(1, -speed);
    Motor_SetSpeed(2, speed);
    Motor_SetSpeed(3, speed);
    Motor_SetSpeed(4, -speed);
}

void Motor_MoveRight(uint8_t speed) {
    Motor_SetSpeed(1, speed);
    Motor_SetSpeed(2, -speed);
    Motor_SetSpeed(3, -speed);
    Motor_SetSpeed(4, speed);
}

void Motor_RotateClockwise(uint8_t speed) {
    Motor_SetSpeed(1, speed);
    Motor_SetSpeed(2, -speed);
    Motor_SetSpeed(3, speed);
    Motor_SetSpeed(4, -speed);
}

void Motor_RotateCounterclockwise(uint8_t speed) {
    Motor_SetSpeed(1, -speed);
    Motor_SetSpeed(2, speed);
    Motor_SetSpeed(3, -speed);
    Motor_SetSpeed(4, speed);
}
