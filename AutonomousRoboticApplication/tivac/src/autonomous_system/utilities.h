#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"    // PWM control

// Define LED colors
#define RED     GPIO_PIN_1
#define BLUE    GPIO_PIN_2
#define GREEN   GPIO_PIN_3
#define YELLOW     (RED | GREEN)
#define Cyan   (GREEN | BLUE)
#define ALL_LEDS  (RED | BLUE | GREEN)

// Function Prototypes
void LED_Init(void);
void LED_Toggle(uint8_t led);
void LED_Red(void);
void LED_Blue(void);
void LED_Green(void);
void LED_Off(void);
void LED_On(uint8_t led);
void LED_loop();
void Delay_ms(uint32_t milliseconds);
void Delay_s(uint32_t seconds);
char UART0_Read(void);
void printInit(void);            // Function to initialize UART
void print(const char *str); // Function to send strings over UART
void print_f(const char *str);
void printlog(const char *str);
void checkkeyboard(char input);
void print_c(uint8_t CharPut);

extern uint8_t currentColor;
extern char * newline;
extern uint8_t counter;
extern char counterStr[10]; // Buffer to hold the counter string
extern char receivedChar;

#endif // UTILITIES_H

