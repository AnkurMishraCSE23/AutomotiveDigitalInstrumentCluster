#ifndef CLUSTER_COMM_H
#define CLUSTER_COMM_H

#include "main.h"
#include "vehicle_state.h"

void ClusterComm_Init(void);
void ClusterComm_SendState(const VehicleState *state);

#endif
