CC = gcc
CFLAGS = -Wall -Wextra -pthread -I./include
LDFLAGS = -pthread

SRC_DIR = src 
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

COMMAN_SRC = $(SRC_DIR)/protocol.c $(SRC_DIR)/registry.c
SERVER_SRC = $(SRC_DIR)/rpc_server.c $(SRC_DIR)/demo_server.c
CLIENT_SRC = $(SRC_DIR)/rpc_client.c $(SRC_DIR)/demo_client.c

COMMON_OBJ = $(OBJ_DIR)/protocol.o $(OBJ_DIR)/registry.o
SERVER_OBJ = $(OBJ_DIR)/rpc_server.o $(OBJ_DIR)/demo_server.o
CLIENT_OBJ = $(OBJ_DIR)/rpc_client.o $(OBJ_DIR)/demo_client.o

SERVER_BIN = $(BIN_DIR)/rpc_server
CLIENT_BIN = $(BIN_DIR)/rpc_client

.PHONY: all clean server client directories

all: directories server client
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)
server: $(SERVER_BIN)
client: $(CLIENT_BIN)

$(SERVER_BIN): $(COMMON_OBJ) $(SERVER_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Server built successfully!"
$(CLIENT_BIN): $(COMMON_OBJ) $(CLIENT_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Client built successfully"
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned build files"
install all:
	@echo "Installing to /usr/local/bin..."
	@sudo cp $(SERVER_BIN) /usr/local/bin/
	@sudo cp #(CLIENT_BIN) /usr/local/bin/
	@echo "Installing complete!"

run-server: server
	$(SERVER_BIN)
run-client: client
	$(CLIENT_BIN)
help:
	@echo "Mint RPC Framework - Makefile"
	@echo ""
	@echo "Targets:"
	@echo "all - 		Build both server and client (default)"
	@echo "server - 	Build server only"
	@echo "client - 	Build client only"
	@echo "clean -		Remove build artifacts"
	@echo "run-server - Build and run server"
	@echo "run-client - Build and run client"
	@echo "install - 	Intall binaries to /usr/local/bin"
	@echo "help - 		Show this help message"