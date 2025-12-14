#!/bin/bash
echo "========================================================="
echo "Mini RPC Framework - Stree Test"
echo "========================================================="
echo ""

if ! pgrep -x "rpc_server" > /dev/null; then
    echo "Error: RPC server is not running!"
    echo "Please start the server first: ./bin.rpc_server"
    exit 1
fi
NUM_CLIENT=20
ITERATIONS=5

echo "Configuration:"
echo "Number of concurrent clients: $NUM_CLIENTS"
echo "Iterantions: $ITERATIONS"
echo ""

mkdir -p test_results 
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
RESULT_FILE="test_results/stree_test_${TIMESTAMP}.txt"

echo "Test started at: $(date)" > "$RESULT_FILE"
echo "Configuration: $NUM_CLIENTS clients, $ITERATIONS interations" >> "$RESULT_FILE"
echo "" >> "$RESULTS_FILE"

echo "Starting stress test..."
echo ""

SUCCESS_COUNT=0
FAIL_COUNT=0

run_client()
{
    local client_id=$1
    local iter=$2

    if ./bin/rpc_client > /dev/null 2>&1; then  
        echo "Client $client_id (iternation $iter): success"
        return 0
    else 
        echo "Client $client_id (iterations $iter): FAILED"
        return 1
    fi
}
for iter in $(seq 1 $ITERATIONS); do
    