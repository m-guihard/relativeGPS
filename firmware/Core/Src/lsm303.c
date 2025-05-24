#include "lsm303.h"
#include "i2c.h"
#include <stdint.h>
#include "main.h"
#include "printer.h"

bool acc_check_presence();

bool lsm303_init()
{
    bool success = true;

    success &= acc_check_presence();

    return success;
}

bool acc_check_presence()
{
    uint8_t data;

    HAL_I2C_Master_Receive(&hi2c1, ACC_ADDRESS << 1 + 1, &data, 1, 1000);

    return data == ACC_REG_WHO_AM_I;
}