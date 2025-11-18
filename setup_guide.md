# Mini RPC Framework - Complete Setup Guide

This guide will walk you through setting up and running the Mini RPC Framework project step-by-step.

## 📋 Table of Contents

1. [Prerequisites](#prerequisites)
2. [Project Structure Setup](#project-structure-setup)
3. [File Organization](#file-organization)
4. [Building the Project](#building-the-project)
5. [Running the Application](#running-the-application)
6. [Testing](#testing)
7. [Troubleshooting](#troubleshooting)
8. [Next Steps](#next-steps)

---

## 1. Prerequisites

### System Requirements

**Operating System:**
- Linux (Ubuntu 20.04+, Debian 10+, CentOS 8+)
- macOS 10.15+
- Any Unix-like system

**Required Software:**
```bash
# Check if you have GCC installed
gcc --version
# Should show: gcc version 7.0 or higher

# Check if you have make installed
make --version
# Should show: GNU Make

# Check if pthread is available (should compile without errors)
echo '#include <pthread.h>
int main() { return 0; }' > test.c && gcc -pthread test.c && rm test.c a.out
```

### Installing Prerequisites

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential
```

**CentOS/RHEL:**
```bash
sudo yum groupinstall "Development Tools"
```

**macOS:**
```bash
xcode-select --install
```

---

## 2. Project Structure Setup

### Step 1: Create Project Directory

```bash
# Create main project directory
mkdir mini-rpc
cd mini-rpc

# Create subdirectories
mkdir src include obj bin tests docs
```

Your directory structure should look like this:
```
mini-rpc/
├── src/          (source files will go here)
├── include/      (header files will go here)
├── obj/          (object files - auto-generated)
├── bin/          (executables - auto-generated)
├── tests/        (test scripts)
├── docs/         (documentation)
├── Makefile      (build configuration)
└── README.md     (project documentation)
```

---

## 3. File Organization

### Step 2: Create All Header Files

Navigate to the `include/` directory and create these files:

#### include/protocol.h
```bash
cd include
nano protocol.h  # or use vim, gedit, etc.
```
Copy the content from the `protocol.h` artifact into this file.

#### include/registry.h
```bash
nano registry.h
```
Copy the content from the `registry.h` artifact.

#### include/rpc_server.h
```bash
nano rpc_server.h
```
Copy the content from the `rpc_server.h` artifact.

#### include/rpc_client.h
```bash
nano rpc_client.h
```
Copy the content from the `rpc_client.h` artifact.

### Step 3: Create All Source Files

Navigate to the `src/` directory:

```bash
cd ../src
```

Create these files in order:

#### src/protocol.c
```bash
nano protocol.c
```
Copy the content from the `protocol.c` artifact.

#### src/registry.c
```bash
nano registry.c
```
Copy the content from the `registry.c` artifact.

#### src/rpc_server.c
```bash
nano rpc_server.c
```
Copy the content from the `rpc_server.c` artifact.

#### src/rpc_client.c
```bash
nano rpc_client.c
```
Copy the content from the `rpc_client.c` artifact.

#### src/demo_server.c
```bash
nano demo_server.c
```
Copy the content from the `demo_server.c` artifact.

#### src/demo_client.c
```bash
nano demo_client.c
```
Copy the content from the `demo_client.c` artifact.

### Step 4: Create Makefile

Navigate back to project root and create Makefile:

```bash
cd ..
nano Makefile
```
Copy the content from the `Makefile` artifact.

**Important**: Make sure there are TABS (not spaces) before the commands in the Makefile!

### Step 5: Create Documentation Files

#### README.md
```bash
nano README.md
```
Copy the content from the `README.md` artifact.

#### SETUP_GUIDE.md (this file)
```bash
nano SETUP_GUIDE.md
```
You're reading it now!

### Verification Checklist

Before proceeding, verify you have all these files:

```bash
# Check directory structure
tree -L 2  # or use: ls -R

# Expected output:
# .
# ├── Makefile
# ├── README.md
# ├── SETUP_GUIDE.md
# ├── bin/
# ├── docs/
# ├── include/
# │   ├── protocol.h
# │   ├── registry.h
# │   ├── rpc_client.h
# │   └── rpc_server.h
# ├── obj/
# ├── src/
# │   ├── demo_client.c
# │   ├── demo_server.c
# │   ├── protocol.c
# │   ├── registry.c
# │   ├── rpc_client.c
# │   └── rpc_server.c
# └── tests/
```

---

## 4. Building the Project

### Step 1: Clean Previous Builds (if any)

```bash
make clean
```

Expected output:
```
rm -rf obj bin
Cleaned build files
```

### Step 2: Build Everything

```bash
make all
```

Expected output:
```
gcc -Wall -Wextra -pthread -I./include -c src/protocol.c -o obj/protocol.o
gcc -Wall -Wextra -pthread -I./include -c src/registry.c -o obj/registry.o
gcc -Wall -Wextra -pthread -I./include -c src/rpc_server.c -o obj/rpc_server.o
gcc -Wall -Wextra -pthread -I./include -c src/demo_server.c -o obj/demo_server.o
gcc -pthread -o bin/rpc_server obj/protocol.o obj/registry.o obj/rpc_server.o obj/demo_server.o
Server built successfully!
gcc -Wall -Wextra -pthread -I./include -c src/rpc_client.c -o obj/rpc_client.o
gcc -Wall -Wextra -pthread -I./include -c src/demo_client.c -o obj/demo_client.o
gcc -pthread -o bin/rpc_client obj/protocol.o obj/registry.o obj/rpc_client.o obj/demo_client.o
Client built successfully!
```

### Step 3: Verify Build

```bash
# Check if executables were created
ls -lh bin/

# Expected output:
# -rwxr-xr-x 1 user user 45K Nov 12 10:00 rpc_client
# -rwxr-xr-x 1 user user 48K Nov 12 10:00 rpc_server
```

### Build Troubleshooting

**Error: "No rule to make target"**
```bash
# Make sure Makefile has correct paths
# Check that all source files exist in src/
# Ensure Makefile uses TABS not SPACES for indentation
```

**Error: "pthread.h: No such file"**
```bash
# Install pthread development files
sudo apt-get install libc6-dev
```

**Error: Permission denied**
```bash
# Make sure you're not trying to run files in bin/ before building
chmod +x bin/rpc_server bin/rpc_client
```

---

## 5. Running the Application

### Quick Test

#### Terminal 1: Start the Server

```bash
./bin/rpc_server
```

Expected output:
```
=== Mini RPC Framework - Demo Server ===
Starting server on port 8080...

RPC Server initialized on port 8080
Registering RPC functions...

Registered functions:
  - add(int, int) -> int
  - multiply(int, int) -> int
  - concat(string, string) -> string
  - square(int) -> int
  - factorial(int) -> int
  - is_prime(int) -> int
  - uppercase(string) -> string

Server ready!

RPC Server started. Waiting for connections...
```

**Leave this terminal open!** The server is now running and waiting for clients.

#### Terminal 2: Run the Client

Open a **new terminal** in the same directory:

```bash
./bin/rpc_client
```

Expected output:
```
=== Mini RPC Framework - Demo Client ===
Connecting to 127.0.0.1:8080...
Connected to RPC server at 127.0.0.1:8080

=== Running Automated Tests ===

=== Testing add(5, 3) ===
Result: 8

=== Testing multiply(7, 6) ===
Result: 42

=== Testing concat("Hello, ", "World!") ===
Result: Hello, World!

=== Testing square(9) ===
Result: 81

=== Testing factorial(5) ===
Result: 120

=== Testing is_prime(17) ===
Result: true

=== Testing uppercase("hello world") ===
Result: HELLO WORLD

=== All Tests Completed ===
Disconnected from RPC server
```

### Interactive Mode

Try the interactive mode for manual testing:

```bash
./bin/rpc_client --interactive
```

Example session:
```
=== Interactive Mode ===
Available functions:
  1. add(int, int)
  2. multiply(int, int)
  3. concat(string, string)
  4. square(int)
  5. factorial(int)
  6. is_prime(int)
  7. uppercase(string)
  0. Exit

Choose function (0-7): 1
Enter two integers: 10 20
Result: 30

Choose function (0-7): 7
Enter string: systems
Result: SYSTEMS

Choose function (0-7): 0
```

### Custom Server/Port

**Start server on custom port:**
```bash
./bin/rpc_server 9000
```

**Connect client to custom server:**
```bash
./bin/rpc_client --host 127.0.0.1 --port 9000
```

### Stopping the Server

In the server terminal, press:
```
Ctrl + C
```

The server will shut down gracefully.

---

## 6. Testing

### Automated Tests

The client includes built-in automated tests:
```bash
./bin/rpc_client
```

### Stress Testing

Create a stress test script:

```bash
nano stress_test.sh
```

Add this content:
```bash
#!/bin/bash
echo "Running stress test with 10 concurrent clients..."
for i in {1..10}; do
    ./bin/rpc_client &
done
wait
echo "Stress test complete!"
```

Make it executable and run:
```bash
chmod +x stress_test.sh
./stress_test.sh
```

### Performance Testing

Test latency:
```bash
time ./bin/rpc_client
```

### Multiple Concurrent Clients

```bash
# Terminal 1: Start server
./bin/rpc_server

# Terminal 2: Run multiple clients
./bin/rpc_client &
./bin/rpc_client &
./bin/rpc_client &
wait
```

---

## 7. Troubleshooting

### Common Issues and Solutions

#### Issue 1: "Address already in use"

**Problem**: Port 8080 is already being used.

**Solution:**
```bash
# Find what's using port 8080
lsof -i :8080

# Kill the process
kill -9 <PID>

# Or use different port
./bin/rpc_server 9000
```

#### Issue 2: "Connection refused"

**Problem**: Server is not running.

**Solution:**
```bash
# Check if server is running
ps aux | grep rpc_server

# Start the server first
./bin/rpc_server
```

#### Issue 3: "Cannot find -lpthread"

**Problem**: Pthread library not found.

**Solution:**
```bash
# Ubuntu/Debian
sudo apt-get install libc6-dev

# Verify installation
ldconfig -p | grep pthread
```

#### Issue 4: Segmentation Fault

**Problem**: Memory error in code.

**Solution:**
```bash
# Run with debugger
gdb ./bin/rpc_server
(gdb) run
(gdb) backtrace

# Check for memory leaks
valgrind --leak-check=full ./bin/rpc_server
```

#### Issue 5: "Permission denied"

**Problem**: Executable doesn't have execute permissions.

**Solution:**
```bash
chmod +x bin/rpc_server bin/rpc_client
```

### Getting Help

If you encounter issues:

1. **Check the README.md** for detailed documentation
2. **Review error messages** carefully
3. **Verify all files** are in correct locations
4. **Check system logs**: `dmesg | tail`
5. **Enable debug output** by adding printf statements

---

## 8. Next Steps

### What to Do Next

1. **Read the Full Documentation**
   ```bash
   cat README.md | less
   ```

2. **Explore the Code**
   - Start with `demo_server.c` and `demo_client.c`
   - Understand the protocol in `protocol.c`
   - Study concurrency in `rpc_server.c`

3. **Add Your Own Functions**
   
   Edit `demo_server.c` and add:
   ```c
   void my_function(void *arg1, void *result) {
       // Your implementation
   }
   
   // In main():
   uint8_t args[] = {TYPE_INT};
   rpc_server_register(&server, "my_func", 
                      my_function, 1, args, TYPE_INT);
   ```

4. **Test Different Scenarios**
   - Multiple clients
   - Large data transfers
   - Error conditions
   - Network delays

5. **Optimize Performance**
   - Measure with `time` command
   - Profile with `gprof`
   - Analyze with `perf`

### Project Deliverables

For your semester project submission:

1. ✅ **Source Code** - All .c and .h files
2. ✅ **Makefile** - Build system
3. ✅ **README.md** - Project documentation
4. ✅ **Demo Video** - Record terminal session
5. ✅ **Project Report** - Use PROJECT_REPORT.md template
6. ✅ **Presentation** - 10-15 minute slides

### Demo Preparation

For your project demonstration:

1. **Practice the demo flow**:
   - Start server (show registration)
   - Run automated tests
   - Show interactive mode
   - Demonstrate concurrent clients
   - Show error handling

2. **Prepare to explain**:
   - Architecture design
   - Protocol format
   - Concurrency model
   - Challenge you faced

3. **Have backup plan**:
   - Pre-recorded video
   - Screenshots of working system
   - Code walkthrough slides

---

## Quick Reference Card

### Essential Commands

```bash
# Build
make clean && make all

# Run server
./bin/rpc_server [port]

# Run client
./bin/rpc_client [-h host] [-p port] [-i]

# Stop server
Ctrl + C  (in server terminal)
# or
pkill rpc_server

# Check if running
ps aux | grep rpc_server

# View server output
./bin/rpc_server 2>&1 | tee server.log

# Multiple clients
for i in {1..5}; do ./bin/rpc_client & done; wait
```

### File Locations

```
Source Files:    src/*.c
Headers:         include/*.h
Executables:     bin/rpc_server, bin/rpc_client
Documentation:   README.md, SETUP_GUIDE.md
```

### Default Configuration

```
Server Port:     8080
Server IP:       127.0.0.1 (localhost)
Max Clients:     10 (configurable in code)
Protocol:        TCP/IP
```

---

## Checklist for Submission

Before submitting your project, verify:

- [ ] All source files compile without errors
- [ ] All source files compile without warnings
- [ ] Server starts successfully
- [ ] Client connects and runs tests
- [ ] All 7 RPC functions work correctly
- [ ] Multiple clients can connect simultaneously
- [ ] Error handling works (test invalid function)
- [ ] README.md is complete
- [ ] Project report is written
- [ ] Code is well-commented
- [ ] Makefile works correctly
- [ ] No memory leaks (tested with valgrind)
- [ ] Demo is practiced and ready
- [ ] Presentation slides prepared

---

## Success Criteria

Your project is complete when:

✅ Server and client compile cleanly  
✅ All automated tests pass  
✅ 10+ concurrent clients work  
✅ No crashes or hangs observed  
✅ Documentation is comprehensive  
✅ Demo runs smoothly  

---

## Contact and Support

For issues specific to this implementation:
- Check the troubleshooting section above
- Review the README.md for API details
- Examine the source code comments

For course-related questions:
- Contact your course instructor
- Visit office hours
- Post on course forum

---

**Good luck with your project! 🚀**

Remember: Start early, test often, and document everything!

---

*Last Updated: November 2025*