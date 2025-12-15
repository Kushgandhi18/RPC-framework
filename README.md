# Mini RPC Framework

A lightweight Remote Procedure Call (RPC) framework implemented in C for Unix/Linux systems. This project demonstrates advanced systems programming concepts including socket programming, inter-process communication (IPC), concurrency, and network protocols.

## 📋 Table of Contents

- [Features](#features)
- [System Requirements](#system-requirements)
- [Project Structure](#project-structure)
- [Quick Start](#quick-start)
- [Usage Guide](#usage-guide)
- [Architecture](#architecture)
- [Troubleshooting](#troubleshooting)
- [Contributions](#contributions)

## ✨ Features

### Core Features
- ✅ **TCP Socket Communication** - Reliable client-server connection
- ✅ **Function Registration System** - Dynamic RPC function registry using dlopen/dlsym
- ✅ **Multi-client Support** - Concurrent client handling with threads
- ✅ **Error Handling** - Comprehensive error detection and reporting
- ✅ **Serialization/Deserialization** - Custom message protocol
- ✅ **Thread-Safe Operations** - Mutex-protected shared resources

### Demo Functions
- 🔹 **hello(name)** - Returns personalized greeting
- 🔹 **echo(message)** - Echoes back the input message
- 🔹 **reverse(string)** - Reverses a string
- 🔹 **uppercase(string)** - Converts string to uppercase

## 🖥️ System Requirements

### Operating System
- Linux (Ubuntu 20.04+, Debian, CentOS, etc.)
- macOS 10.15+
- Any Unix-like system with POSIX support

### Software Dependencies
- GCC 7.0+ or Clang 6.0+
- GNU Make
- pthread library (usually pre-installed)
- dl library (for dynamic loading)
- Standard C library with socket support

### Hardware Requirements
- Minimum: 512MB RAM, 1 CPU core
- Recommended: 2GB RAM, 2+ CPU cores

## 📁 Project Structure

```
mini-rpc/
├── src/
│   ├── client.c              # TCP client implementation
│   ├── server.c              # TCP server with threading
│   ├── protocol.c            # Message protocol (unused in current version)
│   ├── message_handler.c     # Message serialization/deserialization
│   ├── dl_handler.c          # Dynamic library loading
│   ├── rpc_server.c          # RPC server logic
│   ├── rpc_client.c          # RPC client interface
│   ├── demo_server.c         # Server demo application
│   ├── demo_client.c         # Client demo application
│   └── example_functions.c   # RPC function implementations
├── include/
│   ├── client.h              # Client API
│   ├── server.h              # Server API
│   ├── protocol.h            # Protocol definitions (unused)
│   ├── message_handler.h     # Message structures
│   ├── dl_handler.h          # Dynamic loading interface
│   ├── rpc_server.h          # RPC server API
│   └── rpc_client.h          # RPC client API
├── obj/                      # Object files (generated)
├── bin/                      # Executables (generated)
├── Makefile                  # Build system
├── setup.sh                  # Setup script
├── stress_test.sh            # Stress testing script
└── README.md                 # This file
```

## 🎯 Quick Start

### Terminal 1: Start the Server

```bash
./bin/rpc_server
```

**Expected Output:**
```
===========================================
    Mini RPC Framework - Demo Server
===========================================

[RPC Server] Initialized successfully
[RPC Server] Registered: hello
[RPC Server] Registered: echo
[RPC Server] Registered: reverse
[RPC Server] Registered: uppercase

[Demo Server] Server ready on port 8080
[Demo Server] Press Ctrl+C to stop

[Server] Initialized on port 8080
[RPC Server] Starting server...
[Server] Waiting for client connections...
```

⚠️ **Keep this terminal open!** The server is now running.

### Terminal 2: Run the Client

```bash
./bin/rpc_client
```

**Expected Output:**
```
===========================================
    Mini RPC Framework - Demo Client
===========================================

[Demo Client] Connecting to 127.0.0.1:8080...
[Client] Connected to 127.0.0.1:8080
[RPC Client] Connected to RPC server
[Demo Client] Connected successfully!

-------------------------------------------
Test 1: Calling 'hello' function
Result: Hello, World!
-------------------------------------------
Test 2: Calling 'echo' function
Result: This is a test message!
-------------------------------------------
Test 3: Calling 'reverse' function
Result: krowemarF CPR
-------------------------------------------
Test 4: Calling 'uppercase' function
Result: HELLO WORLD
-------------------------------------------
Test 5: Calling non-existent function
Error: Call failed (expected behavior)
-------------------------------------------

[Demo Client] Disconnecting...
[Demo Client] Tests completed!
```

### Quick Demo Script

```bash
# Run automated demo
./run_demo.sh
```

This script:
1. Starts server in background
2. Runs client tests
3. Stops server automatically

## 📖 Usage Guide

### Running the Server

#### Basic Usage
```bash
./bin/rpc_server [port]
```

**Arguments:**
- `port` (optional): Port number to listen on (default: 8080)

#### Examples
```bash
# Default port (8080)
./bin/rpc_server

# Custom port
./bin/rpc_server 9000

# Run in background
./bin/rpc_server 8080 &

# Stop server
pkill rpc_server
# or press Ctrl+C in server terminal
```

### Running the Client

#### Basic Usage
```bash
./bin/rpc_client [server_ip] [port]
```

**Arguments:**
- `server_ip` (optional): Server IP address (default: 127.0.0.1)
- `port` (optional): Server port (default: 8080)

#### Examples

**Local server:**
```bash
./bin/rpc_client
```

**Remote server:**
```bash
./bin/rpc_client 192.168.1.100 9000
```

### Testing Multiple Clients

```bash
# Terminal 1: Start server
./bin/rpc_server

# Terminal 2: Run multiple clients concurrently
./bin/rpc_client &
./bin/rpc_client &
./bin/rpc_client &
wait

# Or use a loop
for i in {1..10}; do
    ./bin/rpc_client &
done
wait
```

## 🏗️ Architecture

### System Overview

```
┌────────────────────────────────────────────┐
│         CLIENT APPLICATION                 │
│  ┌──────────────────────────────────────┐  │
│  │   demo_client.c (User Interface)     │  │
│  └──────────────────────────────────────┘  │
│  ┌──────────────────────────────────────┐  │
│  │   rpc_client.c (RPC API)             │  │
│  └──────────────────────────────────────┘  │
│  ┌──────────────────────────────────────┐  │
│  │   client.c (TCP Socket)              │  │
│  └──────────────────────────────────────┘  │
│  ┌──────────────────────────────────────┐  │
│  │   message_handler.c (Serialization)  │  │
│  └──────────────────────────────────────┘  │
└────────────────────────────────────────────┘
                     ↕
              TCP Socket (Port 8080)
                     ↕
┌────────────────────────────────────────────┐
│         SERVER APPLICATION                 │
│  ┌──────────────────────────────────────┐  │
│  │   message_handler.c (Deserialization)│  │
│  └──────────────────────────────────────┘  │
│  ┌──────────────────────────────────────┐  │
│  │   rpc_server.c (Request Handler)     │  │
│  └──────────────────────────────────────┘  │
│  ┌──────────────────────────────────────┐  │
│  │   server.c (Multi-threaded)          │  │
│  └──────────────────────────────────────┘  │
│  ┌──────────────────────────────────────┐  │
│  │   dl_handler.c (Function Registry)   │  │
│  └──────────────────────────────────────┘  │
│  ┌──────────────────────────────────────┐  │
│  │   libexample.so (RPC Functions)      │  │
│  └──────────────────────────────────────┘  │
└────────────────────────────────────────────┘
```

### Message Format

**Serialized Message Structure:**
```
┌─────────────┬──────────────┬─────────────┬──────────────┐
│ func_name   │ func_name    │ params_len  │ params       │
│ _len (4B)   │ (variable)   │ (4B)        │ (variable)   │
└─────────────┴──────────────┴─────────────┴──────────────┘
```

All integers are in network byte order (big-endian).

### Concurrency Model

The server uses a **thread-per-client** model:

1. Main thread accepts new connections
2. Each client gets a dedicated worker thread
3. Worker threads handle requests independently
4. Function registry is protected by mutex
5. Threads are detached for automatic cleanup

### Thread Safety

**Protected Resources:**
- Function registry (mutex lock in dl_handler.c)
- Socket operations (inherently thread-safe at OS level)

## 🧪 Testing

### Manual Testing

#### Test 1: Basic Connection
```bash
# Terminal 1
./bin/rpc_server

# Terminal 2
./bin/rpc_client
```
**Expected**: Client successfully connects and runs 5 tests (4 pass, 1 error)

#### Test 2: Multiple Clients
```bash
# Terminal 1
./bin/rpc_server

# Terminal 2
for i in {1..5}; do ./bin/rpc_client & done; wait
```
**Expected**: All 5 clients complete successfully

### Debug Mode

Add debug output to track execution:

```c
// In message_handler.c or rpc_server.c
printf("[DEBUG] Function: %s, Params: %s\n", func_name, params);
```

### Network Debugging

```bash
# Monitor network traffic
sudo tcpdump -i lo -X port 8080

# Check socket states
netstat -an | grep 8080

# Test connectivity
telnet 127.0.0.1 8080
```

## 📊 Performance

### Benchmarks

Tested on: Ubuntu 22.04, Intel i7, 16GB RAM

| Metric | Value |
|--------|-------|
| Latency (local) | ~0.5ms |
| Throughput (1 client) | ~2,000 req/s |
| Throughput (10 clients) | ~8,000 req/s |
| Max concurrent clients tested | 100+ |
| Memory per client | ~8KB |


## 📝 Build Commands Reference

```bash
# Clean build
make clean

# Build everything
make all

# Build library only
make lib

# Build server only
make server

# Build client only
make client

# Run server
make run-server

# Run client
make run-client

# Automated test
make test

# Show help
make help
```
## 👥 Contributions

- Helly Gandhi: rpc_client.h, client, demo_client, protocol.c, rpc_client.c
- Kush Gandhi: rpc_server.h, server, demo_server, registry.c, rpc_server.c
- Ruslan Radetskiy: project plan, protocal.h, demo_client.c, registry.h, serialize
- Aditya Prakash: Makefile, Readme, demo_server.c, Setup Guide, project report

## 🙏 Acknowledgments

- Course: Operating Systems Programming
- Instructor: Prof. Xin Zhang
- TAs: Xindi Guo, Jacob Helhoski
- References:
  - Unix Network Programming by W. Richard Stevens
  - Beej's Guide to Network Programming
  - POSIX Threads Programming tutorial

---
**Date:** December 15, 2025
