#!/bin/bash

CHESSGAME_TEST_EXECUTABLE="../build/test/TestChess"

if [ -e "$CHESSGAME_TEST_EXECUTABLE" ]; then
    # Check if the executable exists
    $CHESSGAME_TEST_EXECUTABLE
else
    echo "Error: $CHESSGAME_TEST_EXECUTABLE does not exist. Build the executable before running this script (build.sh)."
fi
