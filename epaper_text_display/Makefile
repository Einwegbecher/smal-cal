# Makefile for 2.15" B E-Paper Text Display Demo
# Based on Waveshare e-Paper library

# Compiler
CC = gcc

# Platform selection (uncomment one)
# PLATFORM = RPI
PLATFORM = RPI

# Library selection for Raspberry Pi (uncomment one)
# USE_BCM2835_LIB = 1
# USE_WIRINGPI_LIB = 1
USE_DEV_LIB = 1
# USE_LGPIO_LIB = 1

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -g

# Platform-specific flags
ifeq ($(PLATFORM), RPI)
    CFLAGS += -D RPI
    ifeq ($(USE_BCM2835_LIB), 1)
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
       lib/Config/RPI_gpiod.c \
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
	@if [ "$(USE_DEV_LIB)" = "1" ]; then \
		if ! pkg-config --exists libgpiod; then \
			echo "ERROR: libgpiod-dev is required but not installed."; \
			echo "Install it with: sudo apt install libgpiod-dev"; \
			exit 1; \
		fi; \
	fi
	@if [ "$(USE_BCM2835_LIB)" = "1" ]; then \
		if ! pkg-config --exists libbcm2835; then \
			echo "ERROR: libbcm2835-dev is required but not installed."; \
			echo "Install it with: sudo apt install libbcm2835-dev"; \
			exit 1; \
		fi; \
	fi
	@if [ "$(USE_WIRINGPI_LIB)" = "1" ]; then \
		if ! pkg-config --exists libwiringpi; then \
			echo "ERROR: libwiringpi-dev is required but not installed."; \
			echo "Install it with: sudo apt install libwiringpi-dev"; \
			exit 1; \
		fi; \
	fi
	@if [ "$(USE_LGPIO_LIB)" = "1" ]; then \
		if ! pkg-config --exists liblgpio; then \
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

# Install dependencies
install_deps:
	@echo "Installing dependencies for USE_DEV_LIB (recommended)..."
	sudo apt update
	sudo apt install -y libgpiod-dev

.PHONY: all clean rebuild run check_dependencies install_deps
