#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "client.h"

#define BUFFER_SIZE 4096

static int client_socket = -1;

int client_connect(const char* server_ip, int port) {
    struct sockaddr_in server_addr;
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        return -1;
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(client_socket);
        client_socket = -1;
        return -1;
    }
    
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_socket);
        client_socket = -1;
        return -1;
    }
    
    printf("[Client] Connected to %s:%d\n", server_ip, port);
    
    return 0;
}

int client_send(const char* data, size_t len) {
    if (client_socket < 0) {
        printf("Error: Client not connected\n");
        return -1;
    }
    
    if (data == NULL || len == 0) {
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

int client_receive(char* buffer, size_t buffer_size) {
    if (client_socket < 0) {
        printf("Error: Client not connected\n");
        return -1;
    }
    
    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }
    
    ssize_t received = recv(client_socket, buffer, buffer_size, 0);
    if (received < 0) {
        perror("Error receiving data");
        return -1;
    }
    
    if (received == 0) {
        printf("[Client] Connection closed by server\n");
    }
    
    return received;
}

void client_disconnect() {
    if (client_socket >= 0) {
        close(client_socket);
        client_socket = -1;
        printf("[Client] Disconnected\n");
    }
}

int client_get_socket() {
    return client_socket;
}