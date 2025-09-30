#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_pipex.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 16:00:00 by cadenegr          #+#    #+#              #
#    Updated: 2025/09/30 16:00:00 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Test counters
TESTS_RUN=0
TESTS_PASSED=0
TESTS_FAILED=0

# Function to print test header
print_header() {
    echo -e "${BLUE}╔════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║                         PIPEX TEST SUITE                      ║${NC}"
    echo -e "${BLUE}║                    Testing Enhanced Pipex                     ║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════════════════════════════╝${NC}"
    echo ""
}

# Function to print test section
print_section() {
    echo -e "${CYAN}📁 $1${NC}"
    echo -e "${CYAN}════════════════════════════════════════════════════════${NC}"
}

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_exit_code="${3:-0}"
    local description="$4"
    
    TESTS_RUN=$((TESTS_RUN + 1))
    
    echo -e "${YELLOW}🧪 Test $TESTS_RUN: $test_name${NC}"
    if [ ! -z "$description" ]; then
        echo -e "   📝 $description"
    fi
    echo -e "   🔧 Command: $command"
    
    # Run the command and capture exit code
    eval "$command" 2>/dev/null 1>/dev/null
    local actual_exit_code=$?
    
    if [ $actual_exit_code -eq $expected_exit_code ]; then
        echo -e "   ✅ ${GREEN}PASSED${NC} (exit code: $actual_exit_code)"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo -e "   ❌ ${RED}FAILED${NC} (expected: $expected_exit_code, got: $actual_exit_code)"
        TESTS_FAILED=$((TESTS_FAILED + 1))
    fi
    echo ""
}

# Function to run test with output comparison
run_test_with_output() {
    local test_name="$1"
    local pipex_cmd="$2"
    local shell_cmd="$3"
    local description="$4"
    
    TESTS_RUN=$((TESTS_RUN + 1))
    
    echo -e "${YELLOW}🧪 Test $TESTS_RUN: $test_name${NC}"
    if [ ! -z "$description" ]; then
        echo -e "   📝 $description"
    fi
    echo -e "   🔧 Pipex: $pipex_cmd"
    echo -e "   🐚 Shell: $shell_cmd"
    
    # Run pipex command
    eval "$pipex_cmd" 2>/dev/null
    local pipex_exit=$?
    
    # Run shell equivalent
    eval "$shell_cmd" 2>/dev/null
    local shell_exit=$?
    
    # Compare outputs if both commands succeeded
    if [ $pipex_exit -eq 0 ] && [ $shell_exit -eq 0 ]; then
        local pipex_output=$(cat pipex_output.txt 2>/dev/null)
        local shell_output=$(cat shell_output.txt 2>/dev/null)
        
        if [ "$pipex_output" = "$shell_output" ]; then
            echo -e "   ✅ ${GREEN}PASSED${NC} (outputs match)"
            TESTS_PASSED=$((TESTS_PASSED + 1))
        else
            echo -e "   ❌ ${RED}FAILED${NC} (outputs differ)"
            echo -e "      Pipex: '$pipex_output'"
            echo -e "      Shell: '$shell_output'"
            TESTS_FAILED=$((TESTS_FAILED + 1))
        fi
    elif [ $pipex_exit -eq $shell_exit ]; then
        echo -e "   ✅ ${GREEN}PASSED${NC} (both failed with same exit code)"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo -e "   ❌ ${RED}FAILED${NC} (different exit codes: pipex=$pipex_exit, shell=$shell_exit)"
        TESTS_FAILED=$((TESTS_FAILED + 1))
    fi
    
    # Cleanup
    rm -f pipex_output.txt shell_output.txt
    echo ""
}

# Function to print final results
print_results() {
    echo -e "${BLUE}╔════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║                          TEST RESULTS                         ║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════════════════════════════╝${NC}"
    echo -e "${CYAN}📊 Total Tests: $TESTS_RUN${NC}"
    echo -e "${GREEN}✅ Passed: $TESTS_PASSED${NC}"
    echo -e "${RED}❌ Failed: $TESTS_FAILED${NC}"
    
    if [ $TESTS_FAILED -eq 0 ]; then
        echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
        echo -e "${GREEN}🏆 Pipex is working perfectly!${NC}"
    else
        echo -e "${RED}⚠️  Some tests failed. Review the output above.${NC}"
    fi
    echo ""
}

# Setup test environment
setup_tests() {
    echo -e "${PURPLE}🔧 Setting up test environment...${NC}"
    
    # Build pipex
    make re > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Failed to build pipex!${NC}"
        exit 1
    fi
    
    # Create test files
    echo "Hello World" > test_file.txt
    echo -e "Line 1\nLine 2\nLine 3" > multi_line.txt
    echo "Numbers: 1 2 3 4 5" > numbers.txt
    
    echo -e "${GREEN}✅ Test environment ready!${NC}"
    echo ""
}

# Cleanup test environment
cleanup_tests() {
    echo -e "${PURPLE}🧹 Cleaning up test files...${NC}"
    rm -f test_file.txt multi_line.txt numbers.txt
    rm -f test_output_*.txt pipex_output.txt shell_output.txt
    echo -e "${GREEN}✅ Cleanup complete!${NC}"
}

# Main test execution
main() {
    print_header
    setup_tests
    
    # Test 1: Error Handling Tests
    print_section "Error Handling Tests"
    run_test "No arguments" "./pipex" 1 "Should show usage information"
    run_test "Too few arguments" "./pipex file1 cmd1" 1 "Should require exactly 4 arguments"
    run_test "Nonexistent input file" "./pipex nonexistent.txt 'cat' 'wc -l' output.txt" 1 "Should handle missing input file"
    run_test "Invalid command" "./pipex test_file.txt 'invalidcommand123' 'cat' output.txt" 1 "Should handle invalid commands"
    
    # Test 2: Basic Functionality Tests
    print_section "Basic Functionality Tests"
    run_test_with_output "Basic word count" \
        "./pipex test_file.txt 'cat' 'wc -w' pipex_output.txt" \
        "< test_file.txt cat | wc -w > shell_output.txt" \
        "Compare basic pipeline with shell equivalent"
    
    run_test_with_output "Line count" \
        "./pipex multi_line.txt 'cat' 'wc -l' pipex_output.txt" \
        "< multi_line.txt cat | wc -l > shell_output.txt" \
        "Count lines through pipeline"
    
    run_test_with_output "Character count" \
        "./pipex test_file.txt 'cat' 'wc -c' pipex_output.txt" \
        "< test_file.txt cat | wc -c > shell_output.txt" \
        "Count characters through pipeline"
    
    # Test 3: Advanced Pipeline Tests
    print_section "Advanced Pipeline Tests"
    run_test_with_output "Grep and count" \
        "./pipex multi_line.txt 'cat' 'grep Line' pipex_output.txt" \
        "< multi_line.txt cat | grep Line > shell_output.txt" \
        "Filter lines with grep"
    
    run_test_with_output "Sort numbers" \
        "./pipex numbers.txt 'cat' 'sort' pipex_output.txt" \
        "< numbers.txt cat | sort > shell_output.txt" \
        "Sort file content"
    
    # Test 4: Edge Cases
    print_section "Edge Case Tests"
    run_test "Empty input file" "./pipex /dev/null 'cat' 'wc -l' test_output_empty.txt" 0 "Handle empty input"
    run_test "Output to /dev/null" "./pipex test_file.txt 'cat' 'cat' /dev/null" 0 "Output to /dev/null"
    
    # Test 5: Performance Test
    print_section "Performance Tests"
    echo -e "${YELLOW}🚀 Performance Test: Large file processing${NC}"
    echo "Creating large test file..."
    seq 1 10000 > large_file.txt
    start_time=$(date +%s.%N)
    ./pipex large_file.txt 'cat' 'wc -l' large_output.txt 2>/dev/null
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc -l 2>/dev/null || echo "N/A")
    
    if [ -f large_output.txt ] && [ "$(cat large_output.txt)" = "10000" ]; then
        echo -e "   ✅ ${GREEN}PASSED${NC} (processed 10,000 lines in ${execution_time}s)"
        TESTS_PASSED=$((TESTS_PASSED + 1))
    else
        echo -e "   ❌ ${RED}FAILED${NC} (large file processing failed)"
        TESTS_FAILED=$((TESTS_FAILED + 1))
    fi
    TESTS_RUN=$((TESTS_RUN + 1))
    rm -f large_file.txt large_output.txt
    echo ""
    
    print_results
    cleanup_tests
    
    # Exit with appropriate code
    if [ $TESTS_FAILED -eq 0 ]; then
        exit 0
    else
        exit 1
    fi
}

# Run the test suite
main