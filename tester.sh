#!/bin/bash

PING_CMD="./ft_ping"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

passed_tests=0
total_tests=0

if [ "$EUID" -ne 0 ]; then
    echo -e "${RED}Error:${NC} This script must be run as root."
    exit 1
fi

echo -e "\n${YELLOW}   __ _             _               _            _            
  / _| |           (_)             | |          | |           
 | |_| |_     _ __  _ _ __   __ _  | |_ ___  ___| |_ ___ _ __ 
 |  _| __|   | '_ \| | '_ \ / _\` | | __/ _ \/ __| __/ _ \ '__|
 | | | |_    | |_) | | | | | (_| | | ||  __/\__ \ ||  __/ |   
 |_|  \__|   | .__/|_|_| |_|\__, |  \__\___||___/\__\___|_|   
       ____  | |             __/ |                            
      |____| |_|            |___/                ${NC}by ffarkas\n\n"

run_test() {
    local description="$1"
    local command="$2"
    local expected_output="$3"

    total_tests=$((total_tests + 1))

    echo -e "${YELLOW}TEST ${total_tests}:${NC} $description"
    echo -e "${YELLOW}COMMAND:${NC} $command"

    output=$(eval "$command" 2>&1)
    echo -e "$output"

    if echo "$output" | grep -q "$expected_output"; then
        echo -e "\n${GREEN}[✓ ${total_tests}/30] PASSED${NC}\n"
        passed_tests=$((passed_tests + 1))
    else
        echo -e "\n${RED}[x ${total_tests}/30] FAILED${NC}\n"
        echo -e "${RED}expected: $expected_output${NC}"
        echo -e "${RED}got: $output${NC}\n"
    fi
}

run_test "Ping valid IP #1" "$PING_CMD 8.8.8.8 -c 2" "2 packets received"
run_test "Ping valid IP #2" "$PING_CMD 1.1.1.1 -c 2" "2 packets received"
run_test "Verbose ping valid IP #3" "$PING_CMD 127.0.0.1 -c 2 -v" "2 packets received"

run_test "Ping reserved IP" "$PING_CMD 192.0.2.1 -c 2" "100% packet loss"
run_test "Ping IP reserved for broadcast" "$PING_CMD 192.168.255.255 -c 2" "100% packet loss"
run_test "Verbose ping private IP" "$PING_CMD 192.168.0.1 -c 2 -v" "100% packet loss"
run_test "Ping invalid IP #1" "$PING_CMD 999.999.999.999 -c 2" "unknown host"
run_test "Ping invalid IP #2" "$PING_CMD 256.0.0.1 -c 2" "unknown host"

run_test "Ping valid hostname #1" "$PING_CMD google.com -c 2" "2 packets received"
run_test "Ping valid hostname #2" "$PING_CMD github.com -c 2" "2 packets received"
run_test "Verbose ping valid hostname #3" "$PING_CMD 42prague.com -c 2 -v" "2 packets received"

run_test "Ping invalid hostname #1" "$PING_CMD invalid_hostname -c 2" "unknown host"
run_test "Ping invalid hostname #2" "$PING_CMD hashtag#.com -c 2" "unknown host"

run_test "Ping valid hostname with low TTL #1" "$PING_CMD google.com -c 2 --ttl=1" "Time to live exceeded"
run_test "Verbose ping valid hostname with low TTL #2" "$PING_CMD facebook.com -c 2 --ttl=1 -v" "4500 0054"


run_test "Quiet ping valid IP" "$PING_CMD 8.8.8.8 -c 2 -q" "0% packet loss"

run_test "Verbose valid IP with 5 packets" "$PING_CMD 1.1.1.1 -c 5 -v" "5 packets received"
run_test "Ping valid IP with invalid packet count" "$PING_CMD 1.1.1.1 -c fortytwo" "invalid value"
run_test "Ping valid IP with empty packet count" "$PING_CMD 1.1.1.1 -c" "requires an argument -- 'c'"

run_test "Ping valid hostname with 3 packets and 2s delay" "$PING_CMD wikipedia.org -c 3 -i 2" "0% packet loss"
run_test "Ping valid hostname with invalid delay" "$PING_CMD wikipedia.org -c 3 -i -42" "value too small"

run_test "Verbose ping valid hostname with 100 data bytes" "$PING_CMD google.org -c 2 -s 100 -v" "108 bytes from"
run_test "Ping valid hostname with invalid data bytes" "$PING_CMD google.org -c 2 -s -100" "value too big"

run_test "Ping valid IP with invalid TTL" "$PING_CMD 1.1.1.1 --ttl=1000" "value too big"
run_test "Ping valid IP with empty TTL" "$PING_CMD 1.1.1.1 --ttl" "requires an argument"

run_test "Ping 2 IPs (both valid)" "$PING_CMD 1.1.1.1 127.0.0.1 -c 2" "127.0.0.1 ping statistics"
run_test "Ping 2 hostnames (both valid)" "$PING_CMD google.com facebook.com -c 2" "PING facebook.com"
run_test "Ping 2 IPs (1 invalid)" "$PING_CMD 1.1.1.1 350.0.0.1 -c 3" "unknown host"
run_test "Ping 2 hostnames (1 invalid)" "$PING_CMD google.com gogeloglo.com -c 4" "unknown host"
run_test "Ping 2 hostnames with low TTL" "$PING_CMD google.com localhost.com -c 2 --ttl=10" "0% packet loss"

echo -e "\n${YELLOW}SUMMARY:${NC} $passed_tests out of $total_tests tests passed.\n"
