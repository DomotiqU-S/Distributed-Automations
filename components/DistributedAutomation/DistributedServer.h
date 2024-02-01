//
// Created by talgarr on 08/01/24.
//

#ifndef SERVER_S3_DISTRIBUTEDSERVER_H
#define SERVER_S3_DISTRIBUTEDSERVER_H

#include "Automation/Automation.h"
#include "../Library/cvector.h"
#include "DistributedMatterAPI.h"
#include <stdbool.h>

#define MAX_NUMBER_OF_DEVICES 128
#define MAX_NUMBER_OF_AUTOMATIONS 8

typedef struct DistributedServer
{
    cvector_vector_type(char*) devices_alias;
    cvector_vector_type(cvector_vector_type(Automation)) automations_by_devices;
}DistributedServer;

void DistributedServer_Init(DistributedServer *this);
void DistributedServer_Free(DistributedServer *this);
void DistributedServer_Run(DistributedServer *this);

// Network
bool DistributedServer_AddDevice(DistributedServer *this, char* alias);
bool DistributedServer_AddAutomationToDevice(DistributedServer *this, char* alias, Automation automation);
bool DistributedServer_RemoveAutomationFromDevice(DistributedServer *this, char* alias, char* automation_alias);
bool DistributedServer_FetchAutomationsFromDevice(DistributedServer *this, char* alias);
void DistributedServer_FetchAutomationsFromAllDevices(DistributedServer *this);

// Storage
void DistributedServer_WriteAutomations(DistributedServer *this);
void DistributedServer_ReadAutomations(DistributedServer *this);

#endif // SERVER_S3_DISTRIBUTEDSERVER_H
