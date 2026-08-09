#include "vehicle_state.h"

static VehicleState vehicleState;

void VehicleState_Init(void)
{
    vehicleState.speed_kmh = 0;
    vehicleState.rpm = 0;
    vehicleState.fuel_percent = 100;
    vehicleState.temperature_c = 25;
}

//void VehicleState_Update(void)
//{
//    static int8_t direction = 1;
//
//    if (direction > 0)
//    {
//        if (vehicleState.speed_kmh < 120)
//        {
//            vehicleState.speed_kmh++;
//        }
//        else
//        {
//            direction = -1;
//        }
//    }
//    else
//    {
//        if (vehicleState.speed_kmh > 0)
//        {
//            vehicleState.speed_kmh--;
//        }
//        else
//        {
//            direction = 1;
//        }
//    }
//
//    vehicleState.rpm = 800 + (vehicleState.speed_kmh * 30);
//
//    if (vehicleState.speed_kmh > 0 &&
//        vehicleState.fuel_percent > 0)
//    {
//        /* Simulated fuel consumption */
//    }
//}

VehicleState *VehicleState_Get(void)
{
    return &vehicleState;
}

//void VehicleState_SetTemperature(int16_t temperature_c)
//{
//    vehicleState.temperature_c = temperature_c;
//}

void VehicleState_SetFromCAN(
    uint16_t speed_kmh,
    uint16_t rpm,
    uint8_t fuel_percent,
    int16_t temperature_c)
{
    vehicleState.speed_kmh = speed_kmh;
    vehicleState.rpm = rpm;
    vehicleState.fuel_percent = fuel_percent;
    vehicleState.temperature_c = temperature_c;
}
