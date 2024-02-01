//
// Created by talgarr on 08/01/24.
//

#include "DistributedServer.h"
#include "../DistributedAutomation/DistributedServer.hpp"


void DistributedServer_Init(DistributedServer *this) {
    this->devices_alias = NULL;
    this->automations_by_devices = NULL;

    DistributedServer_ReadAutomations(this);
    DistributedMatterAPI_GetDevices(this->devices_alias);
    DistributedServer_FetchAutomationsFromAllDevices(this);
}

void DistributedServer_Free(DistributedServer *this) {
    cvector_free(this->devices_alias);
    size_t i;
    for (i = 0; i < cvector_size(this->automations_by_devices); ++i) {
        for (size_t j = 0; j < cvector_size(this->automations_by_devices[i]); ++j) {
            Automation_Free(&this->automations_by_devices[i][j]);
        }
        cvector_free(this->automations_by_devices[i]);
    }
}


// Network
bool DistributedServer_AddDevice(DistributedServer *this, char *alias) {
    if (cvector_size(this->devices_alias) >= MAX_NUMBER_OF_DEVICES)
        return false;

    size_t i;
    for (i = 0; i < cvector_size(this->devices_alias); ++i)
        if (strcmp(this->devices_alias[i], alias) == 0)
            return false;


    cvector_push_back(this->devices_alias, alias);
    cvector_push_back(this->automations_by_devices, NULL);

    return DistributedServer_FetchAutomationsFromDevice(this, alias);
}

/**
 * @brief Check if alias exists, then add automation to device.
 *
 * @param alias The alias of the device
 * @param automation The automation to add
 * @return true Successful addition to the device.
 * @return false The alias does not exist or the device did not accept the automation.
 */
bool DistributedServer_AddAutomationToDevice(DistributedServer *this, char *alias, Automation automation) {
    size_t index_found = -1;
    for (size_t i = 0; i < cvector_size(this->devices_alias); ++i) {
        if (strcmp(this->devices_alias[i], alias) == 0) {
            if (cvector_size(this->automations_by_devices[i]) >= MAX_NUMBER_OF_AUTOMATIONS)
                return false;

            for (size_t j = 0; j < cvector_size(this->automations_by_devices[i]); ++j)
                if (strcmp(this->automations_by_devices[i][j].alias, automation.alias) == 0)
                    return false;

            index_found = i;
            break;
        }
    }

    if (index_found == -1)
        return false;


    char *message = cJSON_PrintUnformatted(Automation_GetJSON(&automation));
    if (strcmp(DistributedMatterAPI_SendMessage(alias, message), "OK") == 0) {
        cvector_push_back(this->automations_by_devices[index_found], automation);
        return true;
    } else {
        return false;
    }
}

bool DistributedServer_RemoveAutomationFromDevice(DistributedServer *this, char *alias, char *automation_alias) {
    size_t index_found = -1;

    for (size_t i = 0; i < cvector_size(this->devices_alias); ++i) {
        if (strcmp(this->devices_alias[i], alias) == 0) {
            index_found = i;
            break;
        }
    }

    if (index_found == -1)
        return false;

    for (size_t i = 0; i < cvector_size(this->automations_by_devices[index_found]); ++i) {
        if (strcmp(this->automations_by_devices[index_found][i].alias, automation_alias) == 0) {
            char *api_call = "remove automation: ";
            char message[strlen(this->automations_by_devices[index_found][i].alias) + strlen(api_call) + 1];
            strcpy(message, api_call);
            strcat(message, automation_alias);
            if (strcmp(DistributedMatterAPI_SendMessage(alias, message), "OK") == 0) {
                cvector_erase(this->automations_by_devices[index_found], i);
                return true;
            } else
                return false;
        }
    }

    return false;
}

/**
 * @brief Fetch all automations from all known devices.
 *
 */
void DistributedServer_FetchAutomationsFromAllDevices(DistributedServer *this) {
    for (size_t i = 0; i < cvector_size(this->devices_alias); ++i)
        DistributedServer_FetchAutomationsFromDevice(this, this->devices_alias[i]);
}

bool DistributedServer_FetchAutomationsFromDevice(DistributedServer *this, char *alias) {
    for (size_t i = 0; i < cvector_size(this->devices_alias); ++i) {
        if (strcmp(this->devices_alias[i], alias) == 0) {
            cJSON *automations = cJSON_Parse(DistributedMatterAPI_GetAutomations(alias));
            if (automations != NULL) {
                if (cJSON_IsArray(automations)) {
                    for (size_t j = 0; j < cvector_size(this->automations_by_devices[i]); ++j)
                        Automation_Free(&this->automations_by_devices[i][j]);
                    cvector_clear(this->automations_by_devices[i]);
                    int size = cJSON_GetArraySize(automations);
                    for (int j = 0; j < size; i++) {
                        cJSON *automation_json = cJSON_GetArrayItem(automations, j);
                        Automation automation;
                        Automation_InitFromJSON(&automation, automation_json);
                        cvector_push_back(this->automations_by_devices[i], automation);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// Storage
/**
 * @brief Write the file with the automation.
 *
 */
void DistributedServer_WriteAutomations(DistributedServer *this) {
    return;
}


/**
 * @brief Read the automation from the file.
 *
 */
void DistributedServer_ReadAutomations(DistributedServer *this) {
    return;
}

DistributedServer::DistributedServer() {

}
