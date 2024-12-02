#include "utilities.h"
#include "i2c_communication.h"
#define SIZE_OF_BUFFER 11
int main(void) {
    LED_Init();
    printInit();

//    uint8_t receivedData;      // Byte received from slave
    uint8_t buffer[SIZE_OF_BUFFER];  // Buffer to hold the received data

    I2C0_MasterInit();
    I2CSlaveInit(I2C0_BASE, I2C_SLAVES_GENERAL_ADDRESS);
    printlog("TIVA C is ready");

    while (1) {

                // Request data from the slave (ONE BYTE)
//                receivedData = I2C0_ReceiveData_SingleReceive(I2C_SLAVE_ADDRESS);
//                printlog("Received Data: ");
//                UARTCharPut(UART0_BASE,receivedData); // Send each character3

                // Request data from the slave
                I2C0_ReceiveData_Burst(I2C_SLAVE_ADDRESS, buffer, SIZE_OF_BUFFER);
                printlog("Received Data: ");
                print_f(&buffer);
                LED_Toggle(RED);
                Delay_s(1);

    }
}

