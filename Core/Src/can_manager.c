#include "can_manager.h"
#include "vehicle_state.h"

extern CAN_HandleTypeDef hcan1;

static CAN_RxHeaderTypeDef rxHeader;
static uint8_t rxData[8];
static volatile uint8_t canMessagePending = 0;

static void CanManager_ConfigFilter(void)
{
    CAN_FilterTypeDef filter = {0};

    filter.FilterBank = 0;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;

    filter.FilterIdHigh = 0x100 << 5;
    filter.FilterIdLow = 0x0000;

    filter.FilterMaskIdHigh = 0x7FF << 5;
    filter.FilterMaskIdLow = 0x0000;

    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterActivation = ENABLE;
    filter.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan1, &filter) != HAL_OK)
    {
        Error_Handler();
    }
}

void CanManager_Init(void)
{
    CanManager_ConfigFilter();

    if (HAL_CAN_Start(&hcan1) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(
            &hcan1,
            CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance == CAN1)
    {
        if (HAL_CAN_GetRxMessage(
                hcan,
                CAN_RX_FIFO0,
                &rxHeader,
                rxData) != HAL_OK)
        {
            Error_Handler();
        }

        canMessagePending = 1;
    }
}

void CanManager_Process(void)
{
    if (!canMessagePending)
    {
        return;
    }

    canMessagePending = 0;

    if (rxHeader.StdId == 0x100 &&
        rxHeader.DLC == 8)
    {
        uint16_t speed =
            (uint16_t)rxData[0] |
            ((uint16_t)rxData[1] << 8);

        uint16_t rpm =
            (uint16_t)rxData[2] |
            ((uint16_t)rxData[3] << 8);

        uint8_t fuel =
            rxData[4];

        int16_t temperature =
            (int16_t)((uint16_t)rxData[5] |
                      ((uint16_t)rxData[6] << 8));

        VehicleState_SetFromCAN(
                    speed,
                    rpm,
                    fuel,
                    temperature);
    }
}
