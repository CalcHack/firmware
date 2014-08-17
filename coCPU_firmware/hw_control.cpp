#include "hw_control.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"



void HW_CONTROL_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
     
    GPIO_InitStructure.GPIO_Pin = ENABLE_CALC | SHORT_BACKUPBATT | VIBRATE | ON_KEY;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    HW_CONTROL_RELEASE_ON_KEY();
}

void HW_CONTROL_ENABLE_CALC(void)
{
    GPIOA->Bset = ENABLE_CALC;
}

void HW_CONTROL_DISABLE_CALC(void)
{
    GPIOA->Breset = ENABLE_CALC;
}

void HW_CONTROL_PRESS_ON_KEY(void)
{
    GPIOA->Breset = ON_KEY;
}

void HW_CONTROL_RELEASE_ON_KEY(void)
{
    GPIOA->Bset = ON_KEY;
}

void HW_CONTROL_CLICK_ON_KEY(void)
{
    HW_CONTROL_PRESS_ON_KEY();
    for(volatile int delaycount = 0; delaycount < 1000000; delaycount ++);
    HW_CONTROL_RELEASE_ON_KEY();
}