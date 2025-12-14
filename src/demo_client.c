#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rpc_client.h"

#define DEFAULT_SERVER "127.0.0.1"
#define DEFAULT_PORT 8080

void print_separator() {
    printf("-------------------------------------------\n");
}

int main(int argc, char *argv[]) {
    char *server_ip = DEFAULT_SERVER;
    int port = DEFAULT_PORT;
    
    if (argc > 1) {
        server_ip = argv[1];
    }
    if (argc > 2) {
        port = atoi(argv[2]);
        if (port <= 0 || port > 65535) {
            printf("Invalid port number. Using default port %d\n", DEFAULT_PORT);
            port = DEFAULT_PORT;
        }
    }
    
    printf("===========================================\n");
    printf("    Mini RPC Framework - Demo Client\n");
    printf("===========================================\n\n");
    
    printf("[Demo Client] Connecting to %s:%d...\n", server_ip, port);
    if (rpc_client_init(server_ip, port) != 0) {
        fprintf(stderr, "[Demo Client] Failed to connect to server\n");
        return EXIT_FAILURE;
    }
    
    printf("[Demo Client] Connected successfully!\n\n");
    print_separator();
    
    printf("Test 1: Calling 'hello' function\n");
    char *result1 = rpc_call("hello", "World");
    if (result1 != NULL) {
        printf("Result: %s\n", result1);
        free(result1);
    } else {
        printf("Error: Call failed\n");
    }
    print_separator();
    
    printf("Test 2: Calling 'echo' function\n");
    char *result2 = rpc_call("echo", "This is a test message!");
    if (result2 != NULL) {
        printf("Result: %s\n", result2);
        free(result2);
    } else {
        printf("Error: Call failed\n");
    }
    print_separator();
    
    printf("Test 3: Calling 'reverse' function\n");
    char *result3 = rpc_call("reverse", "RPC Framework");
    if (result3 != NULL) {
        printf("Result: %s\n", result3);
        free(result3);
    } else {
        printf("Error: Call failed\n");
    }
    print_separator();
    
    printf("Test 4: Calling 'uppercase' function\n");
    char *result4 = rpc_call("uppercase", "hello world");
    if (result4 != NULL) {
        printf("Result: %s\n", result4);
        free(result4);
    } else {
        printf("Error: Call failed\n");
    }
    print_separator();
    
    printf("Test 5: Calling non-existent function\n");
    char *result5 = rpc_call("nonexistent", "test");
    if (result5 != NULL) {
        printf("Result: %s\n", result5);
        free(result5);
    } else {
        printf("Error: Call failed\n");
    }
    print_separator();
    
    printf("\n[Demo Client] Disconnecting...\n");
    rpc_client_disconnect();
    
    printf("[Demo Client] Tests completed!\n");
    return EXIT_SUCCESS;
}