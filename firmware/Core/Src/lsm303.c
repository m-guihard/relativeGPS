#include "lsm303.h"
#include "i2c.h"
#include <stdint.h>
#include "main.h"
#include "printer.h"

bool acc_check_presence();

bool lsm303_init()
{
    LL_GPIO_SetOutputPin(ACC_MAG_1V8_EN_GPIO_Port, ACC_MAG_1V8_EN_Pin);

    bool success = true;

    success &= acc_check_presence();

    return success;
}

bool acc_check_presence()
{
    uint8_t data;

    // HAL_I2C_Master_Receive(&hi2c1, ACC_ADDRESS << 1 + 1, &data, 1, 1000);
    if (HAL_I2C_Mem_Read(&hi2c1, ACC_ADDRESS, ACC_REG_WHO_AM_I, 1, &data, 1, 1000) != HAL_OK) {
        printer(USART_DEBUG, "Couldn't read mag_acc WhoAmI register \r\n", 40);
        return false;
    }

    return data == 0x43;
}