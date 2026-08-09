#include "sensor_manager.h"

extern ADC_HandleTypeDef hadc1;

void SensorManager_Init(void)
{
}

uint16_t SensorManager_ReadADC(void)
{
    uint16_t adcValue = 0;

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        adcValue = HAL_ADC_GetValue(&hadc1);
    }

    HAL_ADC_Stop(&hadc1);

    return adcValue;
}

int16_t SensorManager_ReadTemperature(void)
{
    uint16_t adcValue = SensorManager_ReadADC();

    int16_t temperature =
        (int32_t)adcValue * 120 / 4095;

    return temperature;
}
