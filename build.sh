#!/data/data/com.termux/files/usr/bin/bash

# Exit on error
set -e

# Step 1: Install Termux dependencies
# echo "Installing required packages..."
# pkg update && pkg upgrade -y
# pkg install git cmake clang make -y

# Step 2: Create build directory
echo "Setting up build directory..."
mkdir -p build
cd build

# Step 3: Run CMake for Android
echo "Configuring CMake for Android..."
cmake .. \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a \
    -DCMAKE_BUILD_TYPE=Release

# Step 4: Compile the test core
echo "Building test_lib.so..."
make -j$(nproc)

# Step 5: Verify output
if [ -f "test_lib.so" ]; then
    echo "Build successful! test_lib.so created in $(pwd)"
else
    echo "Build failed: test_lib.so not found!"
    exit 1
fi

# Step 6: Optional - Copy to RetroArch cores directory (uncomment if needed)
# echo "Copying test_lib.so to RetroArch cores directory..."
# cp test_lib.so ~/storage/shared/Android/data/com.retroarch/.retroarch/cores/
# echo "Copied to RetroArch cores directory. Load in RetroArch to test."

echo "Done!"