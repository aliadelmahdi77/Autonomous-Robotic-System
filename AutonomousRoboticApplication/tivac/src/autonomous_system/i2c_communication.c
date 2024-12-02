#include "i2c_communication.h"
#include "utilities.h"
#include "driverlib/i2c.h"

void I2C0_MasterInit(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure GPIO pins for I2C0 (PB3 - SDA, PB2 - SCL)
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE,GPIO_PIN_3);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0));

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);
}


void I2C0_SendData(uint8_t data) {
    // Set slave address and write mode
    I2CMasterSlaveAddrSet(I2C0_BASE, I2C_SLAVE_ADDRESS, false);

    // Place data in the data register
    I2CMasterDataPut(I2C0_BASE, data);

    // Initiate send
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

    // Wait until transmission completes
    while (I2CMasterBusy(I2C0_BASE));
}

// Function to receive data from the slave
uint8_t I2C0_ReceiveData_SingleReceive(uint8_t slaveAddress)
{
    // Set the slave address and read mode
    I2CMasterSlaveAddrSet(I2C0_BASE, slaveAddress, true);  // true means read mode

    // Start the transmission
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    // Wait until the data is received
    while (I2CMasterBusy(I2C0_BASE));

    // Retrieve the received data from the I2C data register
    return I2CMasterDataGet(I2C0_BASE);;


}
// Function to receive multiple bytes from the slave (burst receive)
void I2C0_ReceiveData_Burst(uint8_t slaveAddress, uint8_t *buffer, uint16_t numBytes)
{

    // Set the slave address and read mode
    I2CMasterSlaveAddrSet(I2C0_BASE, slaveAddress, true);  // true means read mode

    // Start the transmission for the first byte
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

    // Wait until the first byte is received
    while (I2CMasterBusy(I2C0_BASE));

    // Store the received data in the buffer
    buffer[0] = I2CMasterDataGet(I2C0_BASE);
    uint8_t i;
    // Now read the rest of the bytes (burst receive)
    for (i = 1; i < (numBytes-1); i++) {
        // Start burst receive command
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

        // Wait until the byte is received
        while (I2CMasterBusy(I2C0_BASE));

        // Store the received data in the buffer
        buffer[i] = I2CMasterDataGet(I2C0_BASE);
    }

    // End the burst receive by sending the last receive command
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    // Wait for the last byte to be received
    while (I2CMasterBusy(I2C0_BASE));

    // Retrieve the last byte
    buffer[numBytes - 1] = I2CMasterDataGet(I2C0_BASE);
}
