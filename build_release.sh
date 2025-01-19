#!/bin/bash

# Store the current directory
CURRENT_DIR=$(pwd)

# Create the release build directory if it doesn't exist
mkdir -p build/release

# Navigate to the build/release directory without changing the original directory
cd build/release

# Run CMake for the release build
echo "**** Running CMake for Release build ****"
cmake -DCMAKE_BUILD_TYPE=Release "$CURRENT_DIR"

# Build the project
echo
echo "**** Building project in Release mode ****"
cmake --build .

# Optionally, run the executable
echo
echo "**** Running the Release executable ****"
./ultra ./src/test.ultra

# Return to the original directory
cd "$CURRENT_DIR"
