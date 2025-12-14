#ifndef SERVER_H
#define SERVER_H

#include <stddef.h>

typedef void (*client_handler_func)(int client_socket);

int server_init(int port);
int server_accept_clients(client_handler_func handler);
int server_send(int client_socket, const char* data, size_t len);
int server_receive(int client_socket, char* buffer, size_t buffer_size);
void server_shutdown();

#endif