#ifndef I2C_COMMUNICATION_H_
#define I2C_COMMUNICATION_H_

#include <stdint.h>

// Define the slave address
#define I2C_SLAVE_ADDRESS 0x02
#define I2C_SLAVES_GENERAL_ADDRESS 0x00

// Function prototypes
void I2C0_MasterInit(void);     // Initialize I2C0 as Master
void I2C0_SendData(uint8_t data); // Send data from Master
void I2C0_ReceiveData_Burst(uint8_t slaveAddress, uint8_t *buffer, uint16_t numBytes);
uint8_t I2C0_ReceiveData_SingleReceive(uint8_t slaveAddress);


#endif /* I2C_COMMUNICATION_H_ */
