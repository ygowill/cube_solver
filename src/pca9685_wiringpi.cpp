#include "../include/pca9685_wiringpi.h"

#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD


//  addr是7位的i2c从机地址，返回的是linux标准的设备描述符，调用它的地方视作pca9685的设备描述符
//  因为可以多个pca9685级联，通过设备描述符区别它们
//  此驱动仅作为驱动舵机使用，周期固定死位20ms，不允许外部设置
int pca9685_init(unsigned char addr){
    int pca9685;
    pca9685 = wiringPiI2CSetup(addr);
    {	//初始化pca9685芯片
        double T = 20000;	//周期，单位是us
        unsigned char prescale;
        double osc_clock = 25000000;
        unsigned char oldmode, newmode;
        T /= 0.915;	    //不知道为什么，会有所偏差，这里需要校准一下T
        T /= 1000000;	//把T转换成秒
        prescale = (unsigned char)(osc_clock/4096*T - 1);
        oldmode = wiringPiI2CReadReg8(pca9685, PCA9685_MODE1);
        newmode = (oldmode&0x7f) | 0x10;	//准备进入sleep，设置时钟前必须先进入sleep模式
        wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, newmode);
        wiringPiI2CWriteReg8(pca9685, PCA9685_PRESCALE, prescale);
        oldmode &= 0xef;	//清除sleep位
        wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, oldmode);
        delay(0.005);
        wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, oldmode | 0xa1);
    }

    return pca9685;
}

//设置指定通道的脉宽。fd是在pca9685_init时获得的设备描述符，num是通道号（从0开始），mk是脉宽单位是us。周期已经固定为20ms了
void pca9685_setmk(int fd, int num, int mk){
    unsigned int ON, OFF;
    ON = 0;	//每次周期一开始就输出高电平
    OFF = (unsigned int)((((double)mk)/20000 * 4096)*1.0067114);	//最后的1.0067114用于校准

    wiringPiI2CWriteReg16(fd, LED0_ON_L+4*num, ON);
    wiringPiI2CWriteReg16(fd, LED0_OFF_L+4*num, OFF);
}