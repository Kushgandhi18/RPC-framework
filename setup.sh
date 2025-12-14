#!/bin/bash

set -e

echo "=========================================================="
echo "Mini RPC Framework - Setup Script"
echo "=========================================================="
echo ""

RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[1;33m'
NC = '\033[0m'

print_success()
{
    echo -e "${GREEN}✓${NC} $1"
}
print_error()
{
    echo -e "${RED}x${NC} $1"
}
print_info()
{
    echo -e "${YELLOW}i${NC} $1"
}
if [["$OSTYPE" != "linux-gnu"*]] && [["$OSTYPE" != "darwin"*]]; then print_error "This script is designed for Linux/Uinx systems"
exit 1
fi
print_info "Checking system requirements..."
if command -v gcc &> /dev/null; then 
    GCC_VERSION = $(gcc --version | head -n1)
    print_success "GCC found: $GCC_VERSION"
else
    print_error "GCC not found. Please install GCC:"
    echo "Ubuntu/Debian: sudo apt-get install build-essential"
    echo "CentOS/RHEL: sudo yum install gcc"
    echo "macOS: xcode-select --install"
    exit 1
fi

print_info "Checking for pthread library..."
cat > /tmp.test_pthread.c << EOF
#include <pthread.h>
int main () {return 0;}
EOF

if gcc -pthread /tmp/test_pthread.c -o /tmp/test_pthread 2>/dev/null; 
then print_success "pthread library found"
    rm -f /tmp/test_pthread.c /tmp/test_pthread
else
    print_error "pthread library not found"
    exit 1
fi
echo ""
print-info "Creating directory structure..."

mkdir -p src
mkdir -p include
mkdir -p obj
mkdir -p bin
mkdir -p tests
mkdir -p docs

print_success "Directory structure created" 

echo ""
print_info "Checking source files..."

REQUIRED_HEADERS=("protocol.h" "registry.h" "rpc_server.h" "rpc_client.h")
REQUIRED_HEADERS=("protocol.c" "registry.c" "rpc_client.c" "demo_server.c" "demo_client.c")
MISSING_FILES=0
for header in "${REQUIRED_HEADERS[@]}"; do
    if [! if "include/$header"]; then
    print_error "Missing: include/$header"
    MISSING_FILES=$((MISSING_FILES + 1))
    fi
done
if [$MISSING_FILES -gt 0]; then
    echo ""
    print_error "$MISSING_FILES file(s) missing. Please ensure all sources file are in place."
    echo ""
    echo "Expected structure:"
    echo "  include/"
    for header in "${REQUIRED_HEADERS[@]}"; do
        echo "  -$header"
    done
    exit 1
fi
print_success "All source files found"
echo ""
print_info "Building project..."
if make all; then
    echo ""
    print_success "Build successful"
else
    echo ""
    print_error "Build failed. Please check the eorror messages above."
    exit 1
fi
echo ""
print_info "Verifying executables..."
if [ -f "bin/rpc_server"] && [ -x "bin/rpc_server"]; then
    print_success "Server executable created"
else 
    print_error "Server executable not founf or not executable"
    exit 1
fi
if [-f "bin/rpc_client"] && [ - x "bin/rpc_client"]; then
    print_success "Client executables created"
else
    print_error "Client executable not found or not executable"
    exit 1
fi
echo ""
echo "========================================================="
echo "Setup Complete!"
echo "========================================================="
echo ""
echo "You can now run:"
echo ""
echo " 1. Start the server:"
echo "  ./bin/rpc_server"
echo ""
echo "2. Run the client (in another terminal):"
echo "  ./bin/rpc_client"
echo ""
echo "3. Interactive mode:"
echo "  ./bin/rpc_client --interactive"
echo ""
echo "4. Run tests:"
echo "  make run-client"
echo ""
echo "FOr more information, see README.md"
echo ""

cat > run_demo.sh << 'EOF'
#!/bin/bash

echo "Starting RPC Server in background..."
./bin/rpc_server &
SERVER_PID=$!

sleep 2

echo "Running client tests..."
./bin/rpc_client

echo ""
echo "Stopping server..."
kill $SERVER_PID

echo "Demo complete!"
EOF

chmod +x run_demo.sh
print_success "Created run_demo.sh for quick testing"

echo ""
print_info "Quick test: Run './run_demo.sh' to test the system"
echo ""