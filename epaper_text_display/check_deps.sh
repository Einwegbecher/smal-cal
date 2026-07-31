#!/bin/bash

# Dependency checker for 2.15" B E-Paper Text Display

echo "Checking dependencies for e-Paper display program..."
echo "===================================================="
echo ""

# Check compiler
echo -n "Checking GCC compiler... "
if command -v gcc &> /dev/null; then
    echo "✓ GCC is installed"
else
    echo "✗ GCC is NOT installed"
    echo "  Install with: sudo apt install gcc"
    exit 1
fi

# Check make
echo -n "Checking Make... "
if command -v make &> /dev/null; then
    echo "✓ Make is installed"
else
    echo "✗ Make is NOT installed"
    echo "  Install with: sudo apt install make"
    exit 1
fi

# Check for libgpiod (default library)
echo -n "Checking libgpiod-dev (default)... "
if pkg-config --exists libgpiod 2>/dev/null; then
    echo "✓ libgpiod-dev is installed"
else
    echo "✗ libgpiod-dev is NOT installed"
    echo "  Install with: sudo apt install libgpiod-dev"
    echo ""
    echo "Alternative libraries:"
    echo "  - libbcm2835-dev: sudo apt install libbcm2835-dev"
    echo "  - libwiringpi-dev: sudo apt install libwiringpi-dev"
    echo "  - liblgpio-dev: sudo apt install liblgpio-dev"
    echo ""
    echo "After installing, edit the Makefile to use the appropriate library."
    exit 1
fi

echo ""
echo "===================================================="
echo "All dependencies are installed! ✓"
echo ""
echo "To build and run:"
echo "  make clean"
echo "  make"
echo "  sudo ./epaper_text_display"
