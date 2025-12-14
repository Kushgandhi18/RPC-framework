#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "message_handler.h"

//TODO: first pass need to lens to network byte order
char* serialize_message(Message *mes){
    if(mes == NULL){
        printf("Message cannot be NULL\n");
        return NULL;
    }

    if(mes->func_name == NULL){
        printf("Message requires Function name and serialized parameters\n");
        return NULL;
    }

    int func_name_len = strlen(mes->func_name);
    int params_len = mes->params != NULL? strlen(mes->params): 0;
    char *buffer = malloc((sizeof(uint32_t ) * 2) + func_name_len + params_len);
    
    if(buffer == NULL){
        printf("Unable to allocate memory to buffer!\n");
        return NULL;
    }
    uint32_t net_order_func_name_len = htonl(func_name_len);
    memcpy(buffer, &net_order_func_name_len, sizeof(uint32_t ));
    memcpy(buffer + sizeof(uint32_t ), mes->func_name, func_name_len);

    uint32_t net_order_params_len = htonl(params_len);
    memcpy(buffer + (sizeof(uint32_t ) + func_name_len), &net_order_params_len, sizeof(uint32_t ));
    if(mes->params != NULL){
        memcpy(buffer + ((sizeof(uint32_t ) * 2) + func_name_len), mes->params, params_len);
    }

    return buffer;
}

Message* deserialize_message(char *buffer){
    if(buffer == NULL){
        printf("Buffer is NULL!\n");
        return NULL;
    }
    
    uint32_t func_name_len = 0;
    uint32_t params_len = 0;

    char *func_name = NULL;
    char *params = NULL;

    memcpy(&func_name_len, buffer, sizeof(uint32_t));
    func_name_len = ntohl(func_name_len);
    func_name = malloc(func_name_len);
    if(func_name == NULL){
        printf("Unable to allocate memory to func_name!\n");
        return NULL;
    }
    memcpy(func_name, buffer + sizeof(uint32_t), func_name_len);
    
    memcpy(&params_len, (buffer + (sizeof(uint32_t) + func_name_len)), sizeof(uint32_t));
    params_len = ntohl(params_len);
    if(params_len){
        params = malloc(params_len);
        if(params == NULL){
            printf("Unable to allocate memory to params!\n");
            return NULL;
        }
        memcpy(params, (buffer + ((sizeof(uint32_t) * 2) + func_name_len)), params_len);
    }

    Message *ret_item = malloc(sizeof(Message));

    ret_item->func_name = func_name;
    ret_item->params = params;
    
    return ret_item;
}