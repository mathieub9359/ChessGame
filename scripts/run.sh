#!/bin/bash

CHESSGAME_EXECUTABLE="../build/ChessGame"

if [ -e "$CHESSGAME_EXECUTABLE" ]; then
    # Check if the executable exists
    $CHESSGAME_EXECUTABLE
else
    echo "Error: $CHESSGAME_EXECUTABLE does not exist. Build the executable before running this script (build.sh)."
fi
