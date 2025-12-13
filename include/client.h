#ifndef CLIENT_H
#define CLIENT_H

#include <stddef.h>

int client_connect(const char* server_ip, int port);
int client_send(const char* data, size_t len);
int client_receive(char* buffer, size_t buffer_size);
void client_disconnect();
int client_get_socket();

#endif