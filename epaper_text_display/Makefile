# Makefile for 2.15" B E-Paper Text Display Demo
# Based on Waveshare e-Paper library

# Compiler
CC = gcc

# Platform selection (uncomment one)
# PLATFORM = RPI
PLATFORM = RPI

# Library selection for Raspberry Pi (uncomment one)
# For Raspberry Pi, you can use:
# - USE_SYSFS_GPIO = 1 (no external libraries needed, recommended)
# - USE_BCM2835_LIB = 1 (requires libbcm2835-dev)
# - USE_WIRINGPI_LIB = 1 (requires libwiringpi-dev)
# - USE_DEV_LIB = 1 (requires libgpiod-dev)
# - USE_LGPIO_LIB = 1 (requires liblgpio-dev)

USE_SYSFS_GPIO = 1
# USE_BCM2835_LIB = 1
# USE_WIRINGPI_LIB = 1
# USE_DEV_LIB = 1
# USE_LGPIO_LIB = 1

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -g

# Platform-specific flags
ifeq ($(PLATFORM), RPI)
    CFLAGS += -D RPI
    ifeq ($(USE_SYSFS_GPIO), 1)
        CFLAGS += -D USE_DEV_LIB
        LDFLAGS += -lm
    else ifeq ($(USE_BCM2835_LIB), 1)
        CFLAGS += -D USE_BCM2835_LIB
        LDFLAGS += -lbcm2835 -lm
    else ifeq ($(USE_WIRINGPI_LIB), 1)
        CFLAGS += -D USE_WIRINGPI_LIB
        LDFLAGS += -lwiringPi -lm
    else ifeq ($(USE_DEV_LIB), 1)
        CFLAGS += -D USE_DEV_LIB
        LDFLAGS += -lgpiod -lm
    else ifeq ($(USE_LGPIO_LIB), 1)
        CFLAGS += -D USE_LGPIO_LIB
        LDFLAGS += -llgpio -lm
    endif
endif

# Include paths
INCLUDES = -I./lib/Config -I./lib/e-Paper -I./lib/GUI -I./lib/Fonts

# Source files
SRCS = main.c \
       lib/e-Paper/EPD_2in15b.c \
       lib/Config/DEV_Config.c \
       lib/Config/sysfs_gpio.c \
       lib/Config/sysfs_software_spi.c \
       lib/Config/dev_hardware_SPI.c \
       lib/GUI/GUI_Paint.c \
       lib/Fonts/font8.c \
       lib/Fonts/font12.c \
       lib/Fonts/font16.c \
       lib/Fonts/font20.c \
       lib/Fonts/font24.c \
       lib/Fonts/font12CN.c \
       lib/Fonts/font24CN.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = epaper_text_display

# Default target
all: check_dependencies $(TARGET)

# Check for required dependencies
check_dependencies:
	@echo "Checking dependencies..."
	@if [ "$(USE_BCM2835_LIB)" = "1" ]; then \
		if ! pkg-config --exists libbcm2835 2>/dev/null; then \
			echo "ERROR: libbcm2835-dev is required but not installed."; \
			echo "Install it with: sudo apt install libbcm2835-dev"; \
			exit 1; \
		fi; \
	fi
	@if [ "$(USE_WIRINGPI_LIB)" = "1" ]; then \
		if ! pkg-config --exists libwiringpi 2>/dev/null; then \
			echo "ERROR: libwiringpi-dev is required but not installed."; \
			echo "Install it with: sudo apt install libwiringpi-dev"; \
			exit 1; \
		fi; \
	fi
	@if [ "$(USE_DEV_LIB)" = "1" ]; then \
		if ! pkg-config --exists libgpiod 2>/dev/null; then \
			echo "ERROR: libgpiod-dev is required but not installed."; \
			echo "Install it with: sudo apt install libgpiod-dev"; \
			exit 1; \
		fi; \
	fi
	@if [ "$(USE_LGPIO_LIB)" = "1" ]; then \
		if ! pkg-config --exists liblgpio 2>/dev/null; then \
			echo "ERROR: liblgpio-dev is required but not installed."; \
			echo "Install it with: sudo apt install liblgpio-dev"; \
			exit 1; \
		fi; \
	fi
	@echo "All dependencies are installed."

# Build executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

# Build object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the program (requires sudo for GPIO access)
run: $(TARGET)
	sudo ./$(TARGET)

# Install dependencies for sysfs_gpio (no external libs needed)
install_deps:
	@echo "No external libraries needed for sysfs_gpio!"
	@echo "The program uses /sys/class/gpio interface directly."

.PHONY: all clean rebuild run check_dependencies install_deps
