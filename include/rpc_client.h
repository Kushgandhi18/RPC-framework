#ifndef RPC_CLIENT_H
#define RPC_CLIENT_H

int rpc_client_init(const char *server_ip, int port);
char* rpc_call(const char *func_name, const char *params);
void rpc_client_disconnect();

#endif