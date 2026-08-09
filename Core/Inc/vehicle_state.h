#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdint.h>

typedef struct
{
    uint16_t speed_kmh;
    uint16_t rpm;
    uint8_t  fuel_percent;
    int16_t  temperature_c;
} VehicleState;

void VehicleState_Init(void);
//void VehicleState_Update(void);
VehicleState *VehicleState_Get(void);
//void VehicleState_SetTemperature(int16_t temperature_c);
void VehicleState_SetFromCAN(
    uint16_t speed_kmh,
    uint16_t rpm,
    uint8_t fuel_percent,
    int16_t temperature_c
);

#endif
