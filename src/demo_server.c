#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../include/rpc_server.h"

#define DEFAULT_PORT 8080
#define LIB_PATH "./bin/libexample.so"

volatile sig_atomic_t keep_running = 1;

void signal_handler(int signum) {
    printf("\n[Demo Server] Received signal %d, shutting down...\n", signum);
    keep_running = 0;
    rpc_server_shutdown();
}

int main(int argc, char *argv[]) {
    int port = DEFAULT_PORT;
    
    if (argc > 1) {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            printf("Invalid port number. Using default port %d\n", DEFAULT_PORT);
            port = DEFAULT_PORT;
        }
    }
    
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    printf("===========================================\n");
    printf("    Mini RPC Framework - Demo Server\n");
    printf("===========================================\n\n");
    
    if (rpc_server_init(port, LIB_PATH) != 0) {
        fprintf(stderr, "[Demo Server] Failed to initialize RPC server\n");
        return EXIT_FAILURE;
    }
    
    printf("[Demo Server] Registering functions...\n");
    
    if (rpc_server_register_function("hello") != 0) {
        fprintf(stderr, "[Demo Server] Failed to register function 'hello'\n");
    } else {
        printf("[Demo Server] Registered: hello\n");
    }
    
    if (rpc_server_register_function("echo") != 0) {
        fprintf(stderr, "[Demo Server] Failed to register function 'echo'\n");
    } else {
        printf("[Demo Server] Registered: echo\n");
    }
    
    if (rpc_server_register_function("reverse") != 0) {
        fprintf(stderr, "[Demo Server] Failed to register function 'reverse'\n");
    } else {
        printf("[Demo Server] Registered: reverse\n");
    }
    
    if (rpc_server_register_function("uppercase") != 0) {
        fprintf(stderr, "[Demo Server] Failed to register function 'uppercase'\n");
    } else {
        printf("[Demo Server] Registered: uppercase\n");
    }
    
    printf("\n[Demo Server] Server ready on port %d\n", port);
    printf("[Demo Server] Press Ctrl+C to stop\n\n");
    
    rpc_server_start();
    
    printf("\n[Demo Server] Cleaning up...\n");
    rpc_server_shutdown();
    
    printf("[Demo Server] Server stopped\n");
    return EXIT_SUCCESS;
}