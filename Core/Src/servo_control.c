#include "servo_control.h"

// 定义 PWM 信号周期和脉宽范围
#define SERVO_TIM_HANDLE    htim1
#define SERVO_CHANNEL_1     TIM_CHANNEL_1
#define SERVO_CHANNEL_2     TIM_CHANNEL_2
#define SERVO_CHANNEL_3     TIM_CHANNEL_3

#define SERVO_MIN_PULSE_WIDTH 1000   // 最小脉宽 (us)
#define SERVO_MAX_PULSE_WIDTH 2000   // 最大脉宽 (us)
#define SERVO_PULSE_PERIOD    20000  // PWM 周期 (us) 对应 50Hz

static TIM_HandleTypeDef htim1; // 定时器句柄

void Servo_Init(void) {
    // 使能 TIM1 时钟
    __HAL_RCC_TIM1_CLK_ENABLE();

    // 配置 TIM1 定时器
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 0; // 不分频
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = SERVO_PULSE_PERIOD - 1; // PWM 周期
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim1);

    // 配置 PWM 通道
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // 配置通道 1 (舵机 1)
    sConfigOC.Pulse = 0; // 初始脉宽
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, SERVO_CHANNEL_1);

    // 配置通道 2 (舵机 2)
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, SERVO_CHANNEL_2);

    // 配置通道 3 (舵机 3)
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, SERVO_CHANNEL_3);

    // 启动 PWM 输出
    HAL_TIM_PWM_Start(&htim1, SERVO_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, SERVO_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, SERVO_CHANNEL_3);
}

void Servo_SetAngle(uint8_t servo, uint16_t angle) {
    if (angle > 180) angle = 180; // 确保角度在 0 到 180 度之间

    // 计算脉宽 (us)
    uint16_t pulse_width = SERVO_MIN_PULSE_WIDTH + (angle * (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH) / 180);

    // 计算定时器的比较值
    uint32_t compare_value = (pulse_width * (SERVO_PULSE_PERIOD)) / 10000; // 转换为定时器的计数值

    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = compare_value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // 根据舵机编号选择对应的通道
    if (servo == 1) {
        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, SERVO_CHANNEL_1);
    } else if (servo == 2) {
        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, SERVO_CHANNEL_2);
    } else if (servo == 3) {
        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, SERVO_CHANNEL_3);
    }

    // 更新 PWM 信号
    HAL_TIM_PWM_Start(&htim1, SERVO_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, SERVO_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, SERVO_CHANNEL_3);
}