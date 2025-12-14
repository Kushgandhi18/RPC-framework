CC = gcc
CFLAGS = -Wall -Wextra -pthread -I./include
LDFLAGS = -pthread

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Core objects used by both server and client
COMMON_OBJ = \
	$(OBJ_DIR)/protocol.o \
	$(OBJ_DIR)/dl_handler.o \
	$(OBJ_DIR)/message_handler.o

# Server/client objects
SERVER_OBJ = \
	$(OBJ_DIR)/rpc_server.o \
	$(OBJ_DIR)/demo_server.o

CLIENT_OBJ = \
	$(OBJ_DIR)/rpc_client.o \
	$(OBJ_DIR)/demo_client.o

SERVER_BIN = $(BIN_DIR)/rpc_server
CLIENT_BIN = $(BIN_DIR)/rpc_client

.PHONY: all clean server client directories install run-server run-client help

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
	@echo "Client built successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned build files"

install:
	@echo "Installing to /usr/local/bin..."
	@sudo cp $(SERVER_BIN) /usr/local/bin/
	@sudo cp $(CLIENT_BIN) /usr/local/bin/
	@echo "Installation complete!"

run-server: server
	$(SERVER_BIN)

run-client: client
	$(CLIENT_BIN)

help:
	@echo "Targets: all, server, client, clean, install, run-server, run-client, help"
