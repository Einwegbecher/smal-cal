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
all: $(TARGET)

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

.PHONY: all clean rebuild run
