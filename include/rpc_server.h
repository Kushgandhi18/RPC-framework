#ifndef RPC_SERVER_H
#define RPC_SERVER_H

int rpc_server_init(int port, const char *lib_path);
int rpc_server_register_function(const char *func_name);
void rpc_server_start();
void rpc_server_shutdown();
void rpc_handle_client(int client_socket);

#endif