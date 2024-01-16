//
// Created by talgarr on 08/01/24.
//

#include "DistributedDevice.h"

/**
 * @brief Add an automation to this device.
 *
 * @param automation
 * @return true
 * @return false
 */
bool DistributedDevice_AddAutomation(DistributedDevice *this, Automation automation)
{
    for (size_t i = 0; i < cvector_size(this->automations); ++i)
        if (strcmp(this->automations[i].alias, automation.alias) == 0)
            return false;

    cvector_push_back(this->automations, automation);
    return true;
}

/**
 * @brief Remove an automation from the device using its alias.
 *
 * @param automation_alias String alias of the automation to remove.
 * @return true if the automation was found and removed.
 * @return false if the automation was not found.
 */
bool DistributedDevice_RemoveAutomation(DistributedDevice *this, char* automation_alias)
{
    for (size_t i = 0; i < cvector_size(this->automations); ++i)
        if (strcmp(this->automations[i].alias, automation_alias) == 0) {
            cvector_erase(this->automations, i);
            return true;
        }

    return false;
}

void DistributedDevice_UpdateAutomations(DistributedDevice *this)
{
}
