#include "cluster_comm.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart2;

void ClusterComm_Init(void)
{
}

void ClusterComm_SendState(const VehicleState *state)
{
    char buffer[100];

    int length = snprintf(
        buffer,
        sizeof(buffer),
        "SPEED=%u,RPM=%u,FUEL=%u,TEMP=%d\r\n",
        state->speed_kmh,
        state->rpm,
        state->fuel_percent,
        state->temperature_c
    );

    HAL_UART_Transmit(
            &huart2,
            (uint8_t *)buffer,
            (uint16_t)length,
            100
        );
}
