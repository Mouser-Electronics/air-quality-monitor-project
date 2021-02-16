#include "MiCSVZ89TE_sensor.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"

#define MICS_VZ89TE_slave_addr 0b1110000
#define MICS_VZ89TE_reg        0b000001100

void MiCSVZ89teReadSensorData(float *CO2, float *VOC, int *data_available){
    
    uint8_t data[7];
    
    //read raw sensor data
    i2c_readDataBlock(MICS_VZ89TE_slave_addr,MICS_VZ89TE_reg,data,7); 
    
    if((data[0] >= 13) || (data[1] >= 13)){
        
        *data_available = 1;
        
        //converting raw values 
        *CO2 = (data[1] - 13)*(1600.0/229)+400;
        *VOC = (data[0] - 13)*(1000.0/229);
    }
    else{
        *data_available = 0;
    
    }

}