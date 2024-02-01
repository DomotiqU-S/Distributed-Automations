//
// Created by talgarr on 29/01/24.
//

#include "VectorUtils.h"

cJSON * VectorUtils_Cvector2CjsonArray(cvector_vector_type(char *) vector_in) {
    cJSON *json = cJSON_CreateArray();
    for (int i = 0; i < cvector_size(vector_in); ++i)
        cJSON_AddItemToArray(json, cJSON_CreateString(vector_in[i]));
    return json;
}

cJSON * VectorUtils_AddCvector2Cjson(cvector_vector_type(char *) vector_in, cJSON *json_out, const char *key) {
    cJSON* json_array = VectorUtils_Cvector2CjsonArray(vector_in);
    cJSON_AddItemToObject(json_out, key, json_array);
    return json_out;
}

char ** VectorUtils_CjsonArray2Cvector(cJSON *json_array_in){
    cvector_vector_type(char *)vector_out = NULL;
    for (int i = 0; i < cJSON_GetArraySize(json_array_in); ++i)
        cvector_push_back(vector_out, cJSON_GetArrayItem(json_array_in, i)->valuestring);
    return vector_out;
}