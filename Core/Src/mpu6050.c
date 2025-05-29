#include "mpu6050.h"

void MPU6050_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t check, data;

    // MPU6050 WHO_AM_I register read
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, 0x75, 1, &check, 1, 1000);
    if (check == 0x68) {
        // Wake up the sensor (disable sleep mode)
        data = 0;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_REG_PWR_MGMT_1, 1, &data, 1, 1000);
    }
}

void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data *data) {
    uint8_t Rec_Data[14];

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT_H, 1, Rec_Data, 14, 1000);

    data->Accel_X = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    data->Accel_Y = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    data->Accel_Z = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    data->Gyro_X = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
    data->Gyro_Y = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
    data->Gyro_Z = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);
}
