#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "main.h"

void InputManager_Init(void);
uint8_t InputManager_IsTurnSignalEvent(void);
void InputManager_ClearTurnSignalEvent(void);

#endif
