#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "rpc_client.h"
#include "client.h"
#include "message_handler.h"

#define BUFFER_SIZE 4096

int rpc_client_init(const char *server_ip, int port) {
    if (client_connect(server_ip, port) != 0) {
        printf("[RPC Client] Failed to connect to server\n");
        return -1;
    }
    
    printf("[RPC Client] Connected to RPC server\n");
    return 0;
}

char* rpc_call(const char *func_name, const char *params) {
    if (func_name == NULL) {
        printf("[RPC Client] Function name cannot be NULL\n");
        return NULL;
    }
    
    Message request;
    request.func_name = strdup(func_name);

    request.params = (char*)params;
    
    char *request_buffer = serialize_message(&request);
    if (request_buffer == NULL) {
        printf("[RPC Client] Failed to serialize request\n");
        return NULL;
    }
    
    int name_len = strlen(func_name);
    int params_len = params != NULL ? strlen(params) : 0;
    int total_size = (2 * sizeof(uint32_t)) + name_len + params_len;
    
    if (client_send(request_buffer, total_size) < 0) {
        printf("[RPC Client] Failed to send request\n");
        free(request_buffer);
        return NULL;
    }
    
    free(request_buffer);
    
    char response_buffer[BUFFER_SIZE];
    memset(response_buffer, 0, BUFFER_SIZE);
    
    int bytes_received = client_receive(response_buffer, BUFFER_SIZE);
    if (bytes_received <= 0) {
        printf("[RPC Client] Failed to receive response\n");
        return NULL;
    }
    
    Message *response = deserialize_message(response_buffer);
    if (response == NULL) {
        printf("[RPC Client] Failed to deserialize response\n");
        return NULL;
    }
    
    if (strcmp(response->func_name, "ERROR") == 0) {
        printf("[RPC Client] Server error: %s\n", response->params);
        char *error_copy = response->params != NULL ? strdup(response->params) : NULL;
        free(response->func_name);
        if (response->params != NULL) free(response->params);
        free(response);
        return error_copy;
    }
    
    char *result = response->params != NULL ? strdup(response->params) : NULL;
    
    free(response->func_name);
    if (response->params != NULL) free(response->params);
    free(response);
    
    return result;
}

void rpc_client_disconnect() {
    client_disconnect();
    printf("[RPC Client] Disconnected\n");
}