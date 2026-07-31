# 2.15" B E-Paper Text Display Demo

A simple C program to display text on a 2.15" B (Black/Red) E-Paper display using the Waveshare library.

## Features

- Displays text on a 2.15" B E-Paper display (160x296 pixels)
- Supports both black and red colors
- Demonstrates various text display functions
- Includes proper cleanup and error handling
- Graceful exit on Ctrl+C

## Hardware Requirements

- Raspberry Pi (tested on Raspberry Pi 4, should work on others)
- 2.15" B E-Paper display from Waveshare
- Proper wiring connections

## Wiring Connection

The program uses the following GPIO pins by default (Raspberry Pi):

| E-Paper Pin | Raspberry Pi GPIO | Function |
|-------------|-------------------|----------|
| RST         | GPIO 17 (Pin 11)  | Reset    |
| DC          | GPIO 25 (Pin 22)  | Data/Command |
| CS          | GPIO 8 (Pin 24)   | Chip Select |
| BUSY        | GPIO 24 (Pin 18)  | Busy      |
| PWR         | GPIO 18 (Pin 12)  | Power     |
| MOSI        | GPIO 10 (Pin 19)  | SPI MOSI  |
| SCLK        | GPIO 11 (Pin 23)  | SPI Clock |

## Software Requirements

- Raspberry Pi OS (or other Linux distribution)
- GCC compiler
- Required libraries (depending on configuration):
  - `libgpiod-dev` (for USE_DEV_LIB - recommended)
  - OR `libbcm2835-dev` (for USE_BCM2835_LIB)
  - OR `libwiringpi-dev` (for USE_WIRINGPI_LIB)
  - OR `liblgpio-dev` (for USE_LGPIO_LIB)

## Installation

### 1. Install Dependencies

For the recommended configuration (USE_DEV_LIB = libgpiod):

```bash
sudo apt update
sudo apt install gcc make libgpiod-dev
```

**OR** for other library options:

- **USE_BCM2835_LIB**: `sudo apt install gcc make libbcm2835-dev`
- **USE_WIRINGPI_LIB**: `sudo apt install gcc make libwiringpi-dev`
- **USE_LGPIO_LIB**: `sudo apt install gcc make liblgpio-dev`

**Note**: Only one library is needed. The default in the Makefile is `USE_DEV_LIB = 1` which requires `libgpiod-dev`.

For other configurations:

- **USE_BCM2835_LIB**: `sudo apt install libbcm2835-dev`
- **USE_WIRINGPI_LIB**: `sudo apt install libwiringpi-dev`
- **USE_LGPIO_LIB**: `sudo apt install liblgpio-dev`

### 2. Build the Program

```bash
cd epaper_text_display
make clean
make
```

### 3. Run the Program

The program requires root privileges to access GPIO pins:

```bash
sudo ./epaper_text_display
```

## Customization

### Change Library Configuration

Edit the Makefile and uncomment the desired library:

```makefile
# USE_BCM2835_LIB = 1
# USE_WIRINGPI_LIB = 1
USE_DEV_LIB = 1  # Recommended
# USE_LGPIO_LIB = 1
```

### Modify Display Content

Edit `main.c` to change the text and graphics displayed. The main display functions are:

- `display_text()` - Display text messages
- `Paint_DrawString_EN()` - Draw English text
- `Paint_DrawNum()` - Draw numbers
- `Paint_DrawLine()`, `Paint_DrawRectangle()`, `Paint_DrawCircle()` - Draw shapes

### Change GPIO Pins

Edit `lib/Config/DEV_Config.c` and modify the `DEV_GPIO_Init()` function to change the GPIO pin assignments.

## Program Flow

1. Initialize hardware and e-Paper display
2. Allocate memory for image buffers
3. Clear the display
4. Display "Hello World!" message
5. Display technical information about the display
6. Display numbers and shapes
7. Clean up and exit

## File Structure

```
epaper_text_display/
├── main.c                 # Main program
├── Makefile              # Build configuration
├── README.md             # This file
└── lib/
    ├── Config/           # Hardware configuration
    │   ├── DEV_Config.h
    │   ├── DEV_Config.c
    │   ├── Debug.h
    │   ├── RPI_gpiod.h
    │   ├── RPI_gpiod.c
    │   ├── dev_hardware_SPI.h
    │   └── dev_hardware_SPI.c
    ├── e-Paper/           # E-Paper driver
    │   ├── EPD_2in15b.h
    │   └── EPD_2in15b.c
    ├── GUI/               # Graphics library
    │   ├── GUI_Paint.h
    │   └── GUI_Paint.c
    └── Fonts/             # Font definitions
        ├── fonts.h
        ├── font8.c
        ├── font12.c
        ├── font16.c
        ├── font20.c
        ├── font24.c
        ├── font12CN.c
        └── font24CN.c
```

## Troubleshooting

### Compilation Errors

- **Missing libraries**: Install the required development packages as described above
- **Permission denied**: Use `sudo` when running the program

### Runtime Issues

- **Display not responding**: Check wiring connections
- **GPIO access denied**: Ensure you're running with sudo
- **SPI not working**: Enable SPI in raspi-config (`sudo raspi-config` -> Interface Options -> SPI)

### Enable SPI on Raspberry Pi

```bash
sudo raspi-config
```

Navigate to:
1. Interface Options
2. SPI
3. Enable
4. Reboot

## License

This program is based on the Waveshare e-Paper library and is provided under the MIT License. See the license headers in the source files for details.

## Acknowledgments

- Waveshare team for the original e-Paper library
- Mistral AI for the Vibe Code agent

## Support

For issues or questions, please refer to the Waveshare documentation or create an issue in the repository.
