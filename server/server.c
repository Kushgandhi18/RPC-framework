#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include "server.h"
#include "message_handler.h"

#define MAX_PENDING_CONNECTIONS 10
#define BUFFER_SIZE 4096

static int server_socket = -1;
static int is_running = 0;
pthread_mutex_t server_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int client_socket;
    struct sockaddr_in client_addr;
    client_handler_func handler;
} client_thread_args;

void* client_thread(void* arg) {
    client_thread_args* args = (client_thread_args*)arg;
    int client_sock = args->client_socket;
    client_handler_func handler = args->handler;
    
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(args->client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    printf("[Server] Client connected from %s:%d\n", client_ip, ntohs(args->client_addr.sin_port));
    
    free(args);
    
    if (handler != NULL) {
        handler(client_sock);
    }
    
    close(client_sock);
    printf("[Server] Client %s disconnected\n", client_ip);
    
    return NULL;
}

int server_init(int port) {
    struct sockaddr_in server_addr;
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        return -1;
    }
    
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Error setting socket options");
        close(server_socket);
        return -1;
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(server_socket);
        return -1;
    }
    
    if (listen(server_socket, MAX_PENDING_CONNECTIONS) < 0) {
        perror("Error listening on socket");
        close(server_socket);
        return -1;
    }
    
    is_running = 1;
    printf("[Server] Initialized on port %d\n", port);
    
    return 0;
}

int server_accept_clients(client_handler_func handler) {
    if (server_socket < 0 || !is_running) {
        printf("Error: Server not initialized\n");
        return -1;
    }
    
    printf("[Server] Waiting for client connections...\n");
    
    while (is_running) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_sock = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        
        if (client_sock < 0) {
            if (errno == EINTR || !is_running) {
                break;
            }
            perror("Error accepting client");
            continue;
        }
        
        client_thread_args* args = malloc(sizeof(client_thread_args));
        if (args == NULL) {
            printf("Error allocating memory for client thread\n");
            close(client_sock);
            continue;
        }
        
        args->client_socket = client_sock;
        args->client_addr = client_addr;
        args->handler = handler;
        
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, client_thread, args) != 0) {
            perror("Error creating thread");
            free(args);
            close(client_sock);
            continue;
        }
        
        pthread_detach(thread_id);
    }
    
    return 0;
}

int server_send(int client_socket, const char* data, size_t len) {
    if (client_socket < 0 || data == NULL || len == 0) {
        return -1;
    }
    
    size_t total_sent = 0;
    while (total_sent < len) {
        ssize_t sent = send(client_socket, data + total_sent, len - total_sent, 0);
        if (sent < 0) {
            perror("Error sending data");
            return -1;
        }
        total_sent += sent;
    }
    
    return total_sent;
}

int server_receive(int client_socket, char* buffer, size_t buffer_size) {
    if (client_socket < 0 || buffer == NULL || buffer_size == 0) {
        return -1;
    }
    
    ssize_t received = recv(client_socket, buffer, buffer_size, 0);
    if (received < 0) {
        perror("Error receiving data");
        return -1;
    }
    
    return received;
}

void server_shutdown() {
    pthread_mutex_lock(&server_mutex);
    is_running = 0;
    pthread_mutex_unlock(&server_mutex);
    
    if (server_socket >= 0) {
        close(server_socket);
        server_socket = -1;
    }
    
    printf("[Server] Shutdown complete\n");
}