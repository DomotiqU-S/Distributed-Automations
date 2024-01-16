//
// Created by talgarr on 08/01/24.
//

#ifndef SERVER_S3_DISTRIBUTEDDEVICE_H
#define SERVER_S3_DISTRIBUTEDDEVICE_H

#include "Automation.h"
#include "../library/cvector.h"

typedef struct DistributedDevice
{
    cvector_vector_type(Automation) automations;
}DistributedDevice;


// Network (received)
bool DistributedDevice_AddAutomation(DistributedDevice *this, Automation automation);
bool DistributedDevice_RemoveAutomation(DistributedDevice *this, char* automation_alias);

// Storage
void DistributedDevice_UpdateAutomations(DistributedDevice *this);

#endif // SERVER_S3_DISTRIBUTEDDEVICE_H
