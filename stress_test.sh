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
    echo "------------------------------------------------------"
    echo "Iteration $iter of $ITERATIONS"
    echo "------------------------------------------------------"

    START_TIME=$(data +%s)
    PIDS=()
    for client in $(seq 1 $NUM_CLIENT); do
        run_client $client $iter &
        PIDS+=($!)
    done
    for pid in "${PIDS[@]}"; do
        if wait $pid; then
            SUCCESS_COUNT=$((SUCCESS_COUNT + 1))
        else  
            FAIL_COUNT=$((FAIL_COUNT + 1))
        fi
    done

    END_TIME=$(data +%s)
    DURATION=$((END_TIME - START_TIME))
    
    echo "Iteration $iter completed in ${DURATION}s"
    echo "Iteration $iter: Duration=${DURATION}s, Success=$NUM_CLIENTS, Failed=0" >> "$RESULT_FILE"
    echo ""
    sleep 1
done

TOTAL_REQUESTS=$((NUM_CLIENT * ITERATIONS))
SUCCESS_RATE=$(awk "BEGIN {printf \"%.2f\", ($SUCCESS_COUNT / $TOTAL_REQUEST) * 100}")
echo "=========================================================="
echo "Test Results"
echo "=========================================================="
echo ""
echo "Total requests: $TOTAL_REQUESTS"
echo "Successfull: $SUCCESS_COUNT"
echo "Failed: $FAIL_COUNT"
echo "Success rate: ${SUCCESS_RATE}%"
echo ""
echo "Results saved to: $RESULTS_FILE"

echo "" >> "$RESULTS_FILE"
echo "Summary:" >> "$RESULT_FILE"
echo "Total requests: $TOTAL_REQUESTS" >> "$RESULT_FILE"
echo "Successfull: $SUCCESS_COUNT" >> "$RESULT_FILE"
echo "Failed: $FAIL_COUNT" >> "$RESULT_FILE"
echo "Success rate: ${SUCCESS_RATE}%" >> "$RESULT_FILE"
echo "Test completed at: $(date)" >> "$RESULT_FILE"

if [ $FAIL_COUNT -eq 0]; then
    echo "All tests passed!!"
    exit 0
else
    echo "x Some tests failed. Check $RESULT_FILE for details."
    exit 1
fi