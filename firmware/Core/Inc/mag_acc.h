#ifndef __MAG_ACC_H__
#define __MAG_ACC_H__

#define ACC_ADDRESS                   0x1D
#define ACC_REG_WHO_AM_I              0x0F    // Should be 0x43
#define ACC_REG_CTRL1                 0x20    // Control registers
#define ACC_REG_CTRL2                 0x21
#define ACC_REG_CTRL3                 0x22
#define ACC_REG_CTRL4                 0x23
#define ACC_REG_CTRL5                 0x24
#define ACC_REG_FIFO_CTRL             0x25    // FIFO control register
#define ACC_REG_OUT_T                 0x26    // Temp sensor output
#define ACC_REG_STATUS                0x27    // Status data register
#define ACC_REG_OUT_X_L               0x28    // Acceleration data registers
#define ACC_REG_OUT_X_H               0x29
#define ACC_REG_OUT_Y_L               0x2A
#define ACC_REG_OUT_Y_H               0x2B
#define ACC_REG_OUT_Z_L               0x2C
#define ACC_REG_OUT_Z_H               0x2d
#define ACC_REG_FIFO_THS              0x2E    // FIFO threshold
#define ACC_REG_FIFO_SRC              0x2F    // FIFO SRC
#define ACC_REG_FIFO_SAMPLES          0x30    // Unread samples stored in FIFO
#define ACC_REG_TAP_6D_THS            0x31    // TAP, 4D, 6D threshold
#define ACC_REG_INT_DUR               0x32    // Interrupt duration
#define ACC_REG_WAKE_UP_THS           0x33    // Wakeup threshold
#define ACC_REG_WAKE_UP_DUR           0x34    // Wakeup duration
#define ACC_REG_FREE_FALL             0x35    // Free-fall config
#define ACC_REG_STATUS_DUP            0x36    // Status register
#define ACC_REG_WAKE_UP_SRC           0x37    // Wakeup SRC
#define ACC_REG_TAP_SRC               0x38    // TAP SRC
#define ACC_REG_6D_SRC                0x39    // 6D SRC
#define ACC_REG_STEP_COUNTER_MINTHS   0x3A    // Step counter config
#define ACC_REG_STEP_COUNTER_L        0x3B    // Steps LSB
#define ACC_REG_STEP_COUNTER_H        0x3C    // Steps MSB
#define ACC_REG_FUNC_CK_GATE          0x3D    // ST Function setting
#define ACC_REG_FUNC_SRC              0x3E    // Function SRC
#define ACC_REG_FUNC_CTRL             0x3F    // Function CTRL

#define MAG_ADDRESS                   0x1E
#define MAG_REG_OFFSET_X_L            0x45    // Hard-iron registers
#define MAG_REG_OFFSET_X_H            0x46
#define MAG_REG_OFFSET_Y_L            0x47
#define MAG_REG_OFFSET_Y_H            0x48
#define MAG_REG_OFFSET_Z_L            0x49
#define MAG_REG_OFFSET_Z_H            0x4A
#define MAG_REG_WHO_AM_I              0x4F    // Should be 0x40
#define MAG_REG_CFG_A                 0x60    // Config registers
#define MAG_REG_CFG_B                 0x61
#define MAG_REG_CFG_C                 0x62
#define MAG_REG_INT_CTRL              0x63    // Interrupt config registers
#define MAG_REG_INT_SOURCE            0x64
#define MAG_REG_INT_THS_L             0x65
#define MAG_REG_INT_THS_H             0x66
#define MAG_REG_STATUS                0x67    // Status register
#define MAG_REG_OUTX_L                0x68    // Magnetometer data registers
#define MAG_REG_OUTX_H                0x69
#define MAG_REG_OUTY_L                0x6A
#define MAG_REG_OUTY_H                0x6B
#define MAG_REG_OUTZ_L                0x6C
#define MAG_REG_OUTZ_H                0x6D

#define ACC_REG_CTRL1_DEF             0x81
#define ACC_REG_CTRL2_DEF             0x04
#define MAG_REG_CFG_A_DEF             0x90
#define MAG_REG_CFG_B_DEF             0x01
#define MAG_REG_CFG_C_DEF             0x10

#endif