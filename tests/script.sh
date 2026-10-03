#!/bin/bash

PROGRAM="./cub3D"

PASSED=0
FAILED=0

run_test() {
    MAP="$1"
    EXPECTED="$2"

    "$PROGRAM" "$MAP" >/tmp/cub3d_test_output 2>&1
    RESULT=$?

    if [ "$RESULT" -eq "$EXPECTED" ]; then
        printf "\033[32m[PASS]\033[0m %s\n" "$MAP"
        PASSED=$((PASSED + 1))
    else
        printf "\033[31m[FAIL]\033[0m %s\n" "$MAP"
        printf "       expected exit code: %d\n" "$EXPECTED"
        printf "       actual exit code:   %d\n" "$RESULT"
        FAILED=$((FAILED + 1))
    fi
}

echo "=============================="
echo "        cub3D tests"
echo "=============================="
echo

echo "Invalid Identifiers:"
for map in ../tests/identifiers/invalid/*.cub; do
    [ -f "$map" ] || continue
    run_test "$map" 1
done

echo
echo "Invalid maps:"
for map in ../tests/map/invalid/*.cub; do
    [ -f "$map" ] || continue
    run_test "$map" 1
done

echo
echo "=============================="
printf "Passed: \033[32m%d\033[0m\n" "$PASSED"
printf "Failed: \033[31m%d\033[0m\n" "$FAILED"
echo "=============================="

if [ "$FAILED" -eq 0 ]; then
    exit 0
else
    exit 1
fi
