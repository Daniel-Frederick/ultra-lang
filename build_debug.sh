#!/bin/bash

# Store the current directory
CURRENT_DIR=$(pwd)

# Create the debug build directory if it doesn't exist
mkdir -p build/debug

# Navigate to the build/debug directory without changing the original directory
cd build/debug

# Run CMake for the debug build
echo "**** Running CMake for Debug build ****"
cmake -DCMAKE_BUILD_TYPE=Debug "$CURRENT_DIR"

# Build the project
echo
echo "**** Building project in Debug mode ****"
cmake --build .

# Optionally, run the executable
echo
echo "**** Running the Debug executable ****"
./ultra ./src/test.ultra

# Return to the original directory
cd "$CURRENT_DIR"
