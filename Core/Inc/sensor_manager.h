#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "main.h"

void SensorManager_Init(void);
uint16_t SensorManager_ReadADC(void);
int16_t SensorManager_ReadTemperature(void);

#endif
