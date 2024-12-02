#include "utilities.h"

//variables
uint8_t currentColor = RED;
char * newline = "\r\n";
uint8_t counter = 1;
char counterStr[10]; // Buffer to hold the counter string
char receivedChar;
// Initialize the GPIO for LEDs
void LED_Init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Enable Port F
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Wait for the peripheral to be ready

    // Unlock PF0 if needed (not used here but ensures proper setup)
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, ALL_LEDS); // Configure LEDs as output
    GPIOPinWrite(GPIO_PORTF_BASE, ALL_LEDS, 0);       // Turn off all LEDs
}

// Toggle a specific LED
void LED_Toggle(uint8_t led) {
    uint8_t current = GPIOPinRead(GPIO_PORTF_BASE, led);
    GPIOPinWrite(GPIO_PORTF_BASE, led, current ^ led);
}

// Turn on a specific LED
void LED_On(uint8_t led) {
    GPIOPinWrite(GPIO_PORTF_BASE, ALL_LEDS, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, led, led);
}

// Turn off all LEDs
void LED_Off(void) {
    GPIOPinWrite(GPIO_PORTF_BASE, ALL_LEDS, 0);
}

// Turn on the red LED
void LED_Red(void) {
    LED_On(RED);
}

// Turn on the blue LED
void LED_Blue(void) {
    LED_On(BLUE);
}

// Turn on the green LED
void LED_Green(void) {
    LED_On(GREEN);
}

void LED_loop(void){
    // Turn off all LEDs
    GPIOPinWrite(GPIO_PORTF_BASE, RED | BLUE | GREEN, 0);

    // Turn on the current color
    GPIOPinWrite(GPIO_PORTF_BASE, RED | BLUE | GREEN, currentColor);

    // Delay for 500 milliseconds
    Delay_ms(500);

    // Cycle through colors (Red -> Blue -> Green)
    if (currentColor == RED) {
        currentColor = BLUE;
    } else if (currentColor == BLUE) {
        currentColor = GREEN;
    } else {
        currentColor = RED;
    }
}
// Delay in milliseconds
void Delay_ms(uint32_t milliseconds) {
    SysCtlDelay((SysCtlClockGet() / 3000) * milliseconds);
}

// Delay in seconds
void Delay_s(uint32_t seconds) {
    SysCtlDelay((SysCtlClockGet() / 3) * seconds);
}

// Function to initialize UART0 with 9600 baud rate, no parity, and 1 stop bit
void printInit(void) {
    // Set the clock to 50 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Enable UART0 and GPIOA peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure GPIO pins for UART0 (PA0: RX, PA1: TX)
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configure UART0 for 9600 baud rate, 8 data bits, no parity, 1 stop bit
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

// Function to send a string via UART0
void print_f(const char *str) {
    while (*str) {
        UARTCharPut(UART0_BASE, *str++); // Send each character
    }
}

void print(const char *str) {
    print_f("\r\n");
    while (*str) {
        UARTCharPut(UART0_BASE, *str++); // Send each character
    }
}
//print the message with counter on the left
void printlog(const char *str) {
    print_f("\r\n");
    // Convert counter to string using sprint_f
    sprintf(counterStr, "%d", counter);  // Converts integer to string
    print_f(counterStr);
    print_f(": ");
    counter++;
    while (*str) {
        UARTCharPut(UART0_BASE, *str++); // Send each character
    }
}
void print_c(uint8_t CharPut){
    UARTCharPut(UART0_BASE, CharPut); // Send each character
}
char UART0_Read(void) {
    while (UARTCharsAvail(UART0_BASE) == 0);  // Wait for data to be available
    return UARTCharGet(UART0_BASE);  // Read a character from UART
}
void checkkeyboard(char input){
    if (input == 'W' || input == 'w') {
         LED_Red();
                     }
     if (input == 'S'|| input == 's'){
                LED_On(YELLOW);
    }
     if (input == 'D' || input == 'd'){
         LED_On(Cyan);
      }
     if (input == 'A' || input == 'a'){
        LED_Green();
      }
}
void readWSAD(void){
        receivedChar = UART0_Read();
        // Echo the received character (for testing)
        UARTCharPut(UART0_BASE, receivedChar);  // Send it back to the terminal
        checkkeyboard(receivedChar);
}
