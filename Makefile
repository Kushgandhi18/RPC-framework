# ======================================================
# Mini RPC Framework - Makefile
# ======================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -pthread -I./include
LDFLAGS = -pthread

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# ------------------------------------------------------
# Object files
# ------------------------------------------------------

COMMON_OBJ = \
	$(OBJ_DIR)/protocol.o \
	$(OBJ_DIR)/dl_handler.o \
	$(OBJ_DIR)/message_handler.o \
	$(OBJ_DIR)/server.o \
	$(OBJ_DIR)/client.o

SERVER_OBJ = \
	$(OBJ_DIR)/rpc_server.o \
	$(OBJ_DIR)/demo_server.o

CLIENT_OBJ = \
	$(OBJ_DIR)/rpc_client.o \
	$(OBJ_DIR)/demo_client.o

# ------------------------------------------------------
# Binaries
# ------------------------------------------------------

SERVER_BIN = $(BIN_DIR)/rpc_server
CLIENT_BIN = $(BIN_DIR)/rpc_client

# ------------------------------------------------------
# Phony targets
# ------------------------------------------------------

.PHONY: all server client clean run-server run-client install help

# ------------------------------------------------------
# Default target
# ------------------------------------------------------

all: server client

# ------------------------------------------------------
# Build rules
# ------------------------------------------------------

server: $(SERVER_BIN)
client: $(CLIENT_BIN)

$(SERVER_BIN): $(COMMON_OBJ) $(SERVER_OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "✔ Server built"

$(CLIENT_BIN): $(COMMON_OBJ) $(CLIENT_OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "✔ Client built"

# Compile any .c file in src/ into obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------------------------------
# Directories
# ------------------------------------------------------

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# ------------------------------------------------------
# Utility targets
# ------------------------------------------------------

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "✔ Cleaned build files"

run-server: server
	$(SERVER_BIN)

run-client: client
	$(CLIENT_BIN)
