#include "input_manager.h"

static volatile uint8_t turnSignalEvent = 0;

void InputManager_Init(void)
{
    turnSignalEvent = 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == TURN_SIGNAL_INPUT_Pin)
    {
        turnSignalEvent = 1;
    }
}

uint8_t InputManager_IsTurnSignalEvent(void)
{
    return turnSignalEvent;
}

void InputManager_ClearTurnSignalEvent(void)
{
    turnSignalEvent = 0;
}
