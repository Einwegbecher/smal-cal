/*****************************************************************************
* | File      :   main.c
* | Author    :   Vibe Code (based on Waveshare library)
* | Function  :   Display text on 2.15" B E-Paper display
* | Info      :   Simple C program to demonstrate text display
*----------------
* | This version:   V1.0
* | Date        :   2024
* | Info        :   Displays "Hello World!" and other text on e-Paper
* -----------------------------------------------------------------------------
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
******************************************************************************/

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include "lib/e-Paper/EPD_2in15b.h"
#include "lib/GUI/GUI_Paint.h"
#include "lib/Config/DEV_Config.h"

// Global image buffers
UBYTE *BlackImage = NULL;
UBYTE *RedImage = NULL;

/*****************************************************************************
* Function :  Handler for SIGINT (Ctrl+C)
* Description: Clean up and exit gracefully
******************************************************************************/
void Handler(int signo)
{
    printf("\r\nHandler: Cleaning up and exiting...\r\n");
    
    // Free allocated memory
    if (BlackImage != NULL) {
        free(BlackImage);
        BlackImage = NULL;
    }
    if (RedImage != NULL) {
        free(RedImage);
        RedImage = NULL;
    }
    
    // Clean up hardware
    DEV_Module_Exit();
    
    exit(0);
}

/*****************************************************************************
* Function :  Initialize the display and buffers
* Description: Set up the e-Paper display and allocate memory for images
* Return: 0 on success, -1 on failure
******************************************************************************/
int init_display(void)
{
    printf("Initializing e-Paper display...\r\n");
    
    // Initialize hardware module
    if (DEV_Module_Init() != 0) {
        printf("ERROR: Failed to initialize hardware module\r\n");
        return -1;
    }
    
    // Initialize e-Paper
    EPD_2IN15B_Init();
    
    // Calculate image size
    UWORD Imagesize = ((EPD_2IN15B_WIDTH % 8 == 0) ? (EPD_2IN15B_WIDTH / 8) : (EPD_2IN15B_WIDTH / 8 + 1)) * EPD_2IN15B_HEIGHT;
    
    // Allocate memory for black image
    if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("ERROR: Failed to allocate memory for black image\r\n");
        DEV_Module_Exit();
        return -1;
    }
    
    // Allocate memory for red image
    if ((RedImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("ERROR: Failed to allocate memory for red image\r\n");
        free(BlackImage);
        BlackImage = NULL;
        DEV_Module_Exit();
        return -1;
    }
    
    printf("Display initialized successfully\r\n");
    return 0;
}

/*****************************************************************************
* Function :  Display text on e-Paper
* Description: Draw text on both black and red layers and display
* Parameters: text - the text to display
******************************************************************************/
void display_text(const char *text)
{
    printf("Displaying text: %s\r\n", text);
    
    // Create and clear black image
    Paint_NewImage(BlackImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    
    // Draw text on black image (appears as black text on white background)
    Paint_DrawString_EN(10, 10, text, &Font16, BLACK, WHITE);
    Paint_DrawString_EN(10, 30, "2.15\" B E-Paper", &Font16, BLACK, WHITE);
    Paint_DrawString_EN(10, 50, "Display Demo", &Font16, BLACK, WHITE);
    
    // Create and clear red image
    Paint_NewImage(RedImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    
    // Draw some red elements
    Paint_DrawString_EN(10, 80, "Red Text Example", &Font16, BLACK, WHITE);
    Paint_DrawLine(10, 100, 150, 100, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(10, 110, 150, 130, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    
    // Display both images
    EPD_2IN15B_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000); // Display for 2 seconds
}

/*****************************************************************************
* Function :  Clean up resources
* Description: Free memory and clean up hardware
******************************************************************************/
void cleanup(void)
{
    printf("Cleaning up...\r\n");
    
    if (BlackImage != NULL) {
        free(BlackImage);
        BlackImage = NULL;
    }
    if (RedImage != NULL) {
        free(RedImage);
        RedImage = NULL;
    }
    
    // Clear display before exit
    EPD_2IN15B_Clear();
    EPD_2IN15B_Sleep();
    DEV_Delay_ms(2000);
    DEV_Module_Exit();
    
    printf("Cleanup complete\r\n");
}

/*****************************************************************************
* Function :  Main function
* Description: Entry point of the program
* Return: 0 on success, -1 on failure
******************************************************************************/
int main(void)
{
    // Set up signal handler for graceful exit
    signal(SIGINT, Handler);
    
    printf("=== 2.15\" B E-Paper Text Display Demo ===\r\n");
    
    // Initialize display
    if (init_display() != 0) {
        return -1;
    }
    
    // Clear display
    printf("Clearing display...\r\n");
    EPD_2IN15B_Clear();
    DEV_Delay_ms(500);
    
    // Display various text messages
    display_text("Hello World!");
    
    // Clear and display another message
    Paint_NewImage(BlackImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawString_EN(20, 20, "E-Paper Display", &Font16, BLACK, WHITE);
    Paint_DrawString_EN(20, 40, "2.15\" B Version", &Font16, BLACK, WHITE);
    Paint_DrawString_EN(20, 60, "160x296 pixels", &Font16, BLACK, WHITE);
    Paint_DrawString_EN(20, 80, "Black & Red", &Font16, BLACK, WHITE);
    
    Paint_NewImage(RedImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    Paint_DrawCircle(80, 120, 30, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawString_EN(50, 115, "Test", &Font12, BLACK, WHITE);
    
    EPD_2IN15B_Display(BlackImage, RedImage);
    DEV_Delay_ms(3000);
    
    // Display numbers
    Paint_NewImage(BlackImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawString_EN(10, 10, "Number Display:", &Font16, BLACK, WHITE);
    Paint_DrawNum(10, 30, 123456789, &Font16, BLACK, WHITE);
    Paint_DrawNum(10, 50, 987654321, &Font16, BLACK, WHITE);
    
    Paint_NewImage(RedImage, EPD_2IN15B_WIDTH, EPD_2IN15B_HEIGHT, 270, WHITE);
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    Paint_DrawNum(10, 70, 111111111, &Font12, BLACK, WHITE);
    Paint_DrawNum(10, 85, 222222222, &Font12, BLACK, WHITE);
    
    EPD_2IN15B_Display(BlackImage, RedImage);
    DEV_Delay_ms(3000);
    
    // Clean up
    cleanup();
    
    printf("Demo completed successfully!\r\n");
    return 0;
}
