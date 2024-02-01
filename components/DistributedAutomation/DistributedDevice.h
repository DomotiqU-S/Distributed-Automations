//
// Created by talgarr on 08/01/24.
//

#ifndef SERVER_S3_DISTRIBUTEDDEVICE_H
#define SERVER_S3_DISTRIBUTEDDEVICE_H

#include "Automation/Automation.h"
#include "../Library/cvector.h"
#include <stdbool.h>

typedef struct DistributedDevice
{
    cvector_vector_type(Automation) automations;
} DistributedDevice;

void DistributedDevice_Init(DistributedDevice *this);
void DistributedDevice_Free(DistributedDevice *this);
void DistributedDevice_Run(DistributedDevice *this);

// Network (received)
bool DistributedDevice_AddAutomation(DistributedDevice *this, Automation automation);
bool DistributedDevice_RemoveAutomation(DistributedDevice *this, char *automation_alias);
void DistributedDevice_Wrapper(DistributedDevice *this, void (*f)() );

// Storage
void DistributedDevice_UpdateAutomations(DistributedDevice *this);

#endif // SERVER_S3_DISTRIBUTEDDEVICE_H
