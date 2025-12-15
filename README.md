# Mini RPC Framework

## Overview

The Mini RPC Framework is a lightweight Remote Procedure Call system implemented in C for Unix-based operating systems. The project demonstrates core operating systems concepts such as TCP socket programming, inter-process communication, multi-threading using POSIX threads, and dynamic function loading. The framework enables a client program to invoke functions on a remote server as if they were local calls.

This project was developed as a semester-end project for the Operating Systems Programming course.

---

## System Requirements

### Operating System

The framework is designed for Unix-like systems and has been tested on Linux and macOS platforms that support POSIX system calls.

### Software Dependencies

The project requires a C compiler such as GCC or Clang, GNU Make for building the project, the pthread library for concurrency, support for dynamic linking using `dlopen` and `dlsym`, and standard socket libraries.

---

## Project Structure

### Source Files

All implementation files are located in the `src` directory.  
Client-side networking logic is implemented in `client.c`.  
Server-side networking and threading logic is implemented in `server.c`.  
The RPC abstraction layers are implemented in `rpc_client.c` and `rpc_server.c`.  
Message serialization and deserialization are handled in `message_handler.c`.  
Dynamic loading of RPC functions is implemented in `dl_handler.c`.  
The demo programs are implemented in `demo_client.c` and `demo_server.c`.  
Example RPC-callable functions are implemented in `example_functions.c`.

### Header Files

All header files are located in the `include` directory.  
This includes interface definitions for the client, server, RPC layers, protocol handling, message handling, and dynamic loading modules.

### Build and Output Files

The `obj` directory contains intermediate object files generated during compilation.  
The `bin` directory contains compiled executables and shared libraries, including the RPC server, RPC client, and the example shared library.

---

## Build Instructions

### Building the Project

To build the entire project, navigate to the project root directory and execute the following commands.

make clean
make
   
This will compile all source files and generate the required binaries inside the `bin` directory.

### Building Individual Components

The server and client can also be built separately.

make server
make client

### Building the Shared Library

The server dynamically loads RPC-callable functions from a shared library. This library must be built before running the server.

make lib


---

## Running the Project

### Running the Server

The server must be started before running the client. By default, it listens on port 8080 and loads the shared library containing the RPC functions.

./bin/rpc_server


The server continues running until it is terminated manually using Ctrl+C.

### Running the Client

The client connects to the server and executes a sequence of RPC calls to demonstrate functionality and error handling.

./bin/rpc_client


### Required Terminals

Two terminal windows are required. One terminal is used to run the server, and the second terminal is used to run the client.

---

## Usage Guidelines

The server must always be running before any client attempts to connect.  
The client communicates with the server using serialized RPC messages sent over a TCP connection.  
Each request specifies a function name and its parameters, which are resolved dynamically on the server.  
Invalid function requests are handled gracefully by returning error responses instead of crashing the server.

The framework supports multiple concurrent clients.

---

## Architecture Overview

### Client Side

The demo client interacts with the RPC client layer, which formats RPC requests and sends them through the TCP client module. Message serialization is performed before data transmission.

### Server Side

The server accepts incoming connections and spawns a separate thread for each client. Incoming requests are deserialized, validated, and dispatched through the RPC server layer. Functions are resolved dynamically from the shared library and executed on behalf of the client.

---

## Testing

### Manual Testing

The project can be tested by running the server and client in separate terminals. The demo client performs multiple RPC calls and prints the results to standard output.

### Concurrency Testing

Multiple client instances can be executed simultaneously to verify correct handling of concurrent connections.

---

## Build Command Reference

The Makefile provides the following commonly used targets.

make clean
make all
make server
make client
make lib
make run-server
make run-client
make test


---

## Team Contributions

### Helly Gandhi

Implemented all client-side components including the TCP client module, RPC client abstraction, and demo client program.

### Kush Gandhi

Implemented all server-side components including the TCP server, RPC server logic, and the multi-threaded demo server.

### Ruslan Radetskiy

Implemented message serialization and deserialization, dynamic library handling, and unit testing for message processing.

### Aditya Prakash

Designed the communication protocol, implemented the Makefile, wrote the README and project report, and assisted with system integration.

---

## Conclusion

The Mini RPC Framework demonstrates a complete and functional RPC system built using fundamental operating systems concepts. The project integrates networking, concurrency, dynamic linking, and structured communication into a cohesive framework suitable for educational purposes.

---

## Acknowledgments

This project was completed as part of the Operating Systems Programming course and was guided by standard systems programming references and course materials.
