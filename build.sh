#!/bin/bash
# Build script for Orange Updater

echo "🍊 Building Orange Updater..."
echo "=============================="
echo ""

# Check for GTK3
echo "Checking dependencies..."
if ! pkg-config --exists gtk+-3.0; then
    echo "❌ Error: GTK3 development libraries not found!"
    echo ""
    echo "Please install GTK3 development packages:"
    echo "  Ubuntu/Debian: sudo apt install libgtk-3-dev"
    echo "  Fedora:        sudo dnf install gtk3-devel"
    echo "  Arch:          sudo pacman -S gtk3"
    exit 1
fi

GTK_VERSION=$(pkg-config --modversion gtk+-3.0)
echo "✓ GTK3 found (version $GTK_VERSION)"
echo ""

# Make scripts executable
echo "Making scripts executable..."
chmod +x scripts/*.sh
echo "✓ Scripts ready"
echo ""

# Clean previous build
if [ -d "build" ] || [ -f "orange-updater" ]; then
    echo "Cleaning previous build..."
    make clean > /dev/null 2>&1
    echo "✓ Clean complete"
    echo ""
fi

# Build
echo "Compiling..."
if make; then
    echo ""
    echo "=============================="
    echo "✅ Build successful!"
    echo "=============================="
    echo ""
    echo "Run the application with:"
    echo "  ./orange-updater"
    echo ""
    echo "Or install system-wide with:"
    echo "  sudo make install"
    echo ""
else
    echo ""
    echo "=============================="
    echo "❌ Build failed!"
    echo "=============================="
    echo ""
    echo "Check the error messages above."
    exit 1
fi
