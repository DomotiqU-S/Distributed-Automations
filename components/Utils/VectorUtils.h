//
// Created by talgarr on 29/01/24.
//

#ifndef DISTRIBUTED_SERVER_VECTORUTILS_H
#define DISTRIBUTED_SERVER_VECTORUTILS_H

#include "../Library/cJSON.h"
#include "../Library/cvector.h"

cJSON * VectorUtils_AddCvector2Cjson(cvector_vector_type(char *) vector_in, cJSON* json_out, const char *key);
char ** VectorUtils_CjsonArray2Cvector(cJSON *json_array_in);

#endif //DISTRIBUTED_SERVER_VECTORUTILS_H
