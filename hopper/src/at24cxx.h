#pragma once

#include <Wire.h>
#include <Arduino.h>
#define AT_DEBUG    1

#define pin_SDA 21
#define pin_SCL 22

#define SDA_IN()  {pinMode(pin_SDA,INPUT);}
#define SDA_OUT() {pinMode(pin_SDA,OUTPUT);}
#define WRITE_IIC_SCL(x)    {digitalWrite(pin_SCL,x);} //SCL
#define WRITE_IIC_SDA(x)     {digitalWrite(pin_SDA,x);} //SDA	 
#define READ_SDA   digitalRead(pin_SDA)  //输入SDA

class Myiic
{
    public:
        void iic_init();
        void IIC_Init(void);                //初始化IIC的IO口				 
        void IIC_Start(void);				//发送IIC开始信号
        void IIC_Stop(void);	  			//发送IIC停止信号
        void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
        uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
        uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
        void IIC_Ack(void);					//IIC发送ACK信号
        void IIC_NAck(void);				//IIC不发送ACK信号
        void IIC_Write_One_Byte(unsigned char daddr,unsigned char addr,unsigned char data);
        uint8_t IIC_Read_One_Byte(unsigned char daddr,unsigned char addr);
    protected:

};


#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  

#define EE_TYPE AT24C32
#define CHECK_BIT 255

class At24c:public Myiic
{
    public:
        void init();
        void writeByte(uint32_t address,byte data);
        byte readByte(uint32_t address);
        bool check();
    private:
        

};