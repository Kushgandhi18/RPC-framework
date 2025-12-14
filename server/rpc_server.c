#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "rpc_server.h"
#include "server.h"
#include "message_handler.h"

#define BUFFER_SIZE 4096

extern void *dl_handler;
extern struct RegisteryList *funcs;

int function_table_init(const char *lib_path);
int add_function(const char *func_name);
void *get_function(char *s_name);
void destroy_registery();

void rpc_handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        
        int bytes_received = server_receive(client_socket, buffer, BUFFER_SIZE);
        
        if (bytes_received <= 0) {
            break;
        }
        
        Message *request = deserialize_message(buffer);
        if (request == NULL) {
            printf("[RPC Server] Failed to deserialize message\n");
            continue;
        }
        
        printf("[RPC Server] Received call for function: %s\n", request->func_name);
        
        void *func_ptr = get_function((char*)request->func_name);
        
        if (func_ptr == NULL) {
            printf("[RPC Server] Function '%s' not found\n", request->func_name);
            
            Message error_response;
            error_response.func_name = "ERROR";
            error_response.params = "Function not found";
            
            char *error_buffer = serialize_message(&error_response);
            if (error_buffer != NULL) {
                int name_len = strlen(error_response.func_name);
                int params_len = strlen(error_response.params);
                int total_size = (2 * sizeof(uint32_t)) + name_len + params_len;
                
                server_send(client_socket, error_buffer, total_size);
                free(error_buffer);
            }
            
            free(request->func_name);
            if (request->params != NULL) free(request->params);
            free(request);
            continue;
        }
        
        typedef char* (*rpc_func)(const char*);
        rpc_func func = (rpc_func)func_ptr;
        
        char *result = func(request->params);
        
        Message response;
        response.func_name = "RESPONSE";
        response.params = result != NULL ? result : "NULL";
        
        char *response_buffer = serialize_message(&response);
        if (response_buffer != NULL) {
            int name_len = strlen(response.func_name);
            int params_len = strlen(response.params);
            int total_size = (2 * sizeof(uint32_t)) + name_len + params_len;
            
            server_send(client_socket, response_buffer, total_size);
            free(response_buffer);
        }
        
        if (result != NULL && result != request->params) {
            free(result);
        }
        free(request->func_name);
        if (request->params != NULL) free(request->params);
        free(request);
    }
}

int rpc_server_init(int port, const char *lib_path) {
    if (function_table_init(lib_path) != 0) {
        printf("[RPC Server] Failed to initialize function registry\n");
        return -1;
    }
    
    if (server_init(port) != 0) {
        printf("[RPC Server] Failed to initialize server\n");
        return -1;
    }
    
    printf("[RPC Server] Initialized successfully\n");
    return 0;
}

int rpc_server_register_function(const char *func_name) {
    return add_function(func_name);
}

void rpc_server_start() {
    printf("[RPC Server] Starting server...\n");
    server_accept_clients(rpc_handle_client);
}

void rpc_server_shutdown() {
    printf("[RPC Server] Shutting down...\n");
    server_shutdown();
    destroy_registery();
}