#include "at24cxx.h"


void Myiic::iic_init(){
    pinMode(pin_SDA,OUTPUT);
    pinMode(pin_SCL,OUTPUT);
}

void Myiic::IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	// WRITE_IIC_SDA(HIGH);
    digitalWrite(pin_SDA,HIGH);
	// WRITE_IIC_SCL(HIGH);
    digitalWrite(pin_SCL,HIGH);
	delayMicroseconds(4);
    WRITE_IIC_SDA(LOW);
 	// WRITE_IIC_SDA(LOW);//START:when CLK is high,DATA change form high to low 
	delayMicroseconds(4);
    WRITE_IIC_SCL(LOW);
	// WRITE_IIC_SCL(LOW);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void Myiic::IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	WRITE_IIC_SCL(LOW);
	WRITE_IIC_SDA(LOW);//STOP:when CLK is high DATA change form low to high
    delayMicroseconds(4);
	WRITE_IIC_SCL(HIGH); 
	WRITE_IIC_SDA(HIGH);//发送I2C总线结束信号
	delayMicroseconds(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t Myiic::IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	WRITE_IIC_SDA(HIGH);delayMicroseconds(1);	   
	WRITE_IIC_SCL(HIGH);delayMicroseconds(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	WRITE_IIC_SCL(LOW);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void Myiic::IIC_Ack(void)
{
	WRITE_IIC_SCL(LOW);
	SDA_OUT();
	WRITE_IIC_SDA(LOW);
	delayMicroseconds(2);
	WRITE_IIC_SCL(HIGH);
	delayMicroseconds(2);
	WRITE_IIC_SCL(LOW);
}
//不产生ACK应答		    
void Myiic::IIC_NAck(void)
{
	WRITE_IIC_SCL(LOW);
	SDA_OUT();
	WRITE_IIC_SDA(HIGH);
	delayMicroseconds(2);
	WRITE_IIC_SCL(HIGH);
	delayMicroseconds(2);
	WRITE_IIC_SCL(LOW);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void Myiic::IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    WRITE_IIC_SCL(LOW);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        WRITE_IIC_SDA((txd&0x80)>>7);
        // IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delayMicroseconds(2);   //对TEA5767这三个延时都是必须的
		WRITE_IIC_SCL(HIGH);
		delayMicroseconds(2); 
		WRITE_IIC_SCL(LOW);	
		delayMicroseconds(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t Myiic::IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        WRITE_IIC_SCL(LOW); 
        delayMicroseconds(2);
		WRITE_IIC_SCL(HIGH);
        receive<<=1;
        if(READ_SDA)receive++;   
		delayMicroseconds(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}


void At24c::init(){
    iic_init();
    #if AT_DEBUG
    Serial.println("At24cxx initial successfully !");
    #endif
}

void At24c::writeByte(uint32_t address,byte data){
    IIC_Start();
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(address>>8);//发送高地址
 	}else
	{
		IIC_Send_Byte(0XA0+((address/256)<<1));   //发送器件地址0XA0,写数据 
	}
	IIC_Wait_Ack();	   
    IIC_Send_Byte(address%256);   //发送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(data);     //发送字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	delay(3);	
}

byte At24c::readByte(unsigned int address){
    byte data = 0xFF;
    // Wire.beginTransmission(0);
    // Wire.write((int)0xA0);
    // Wire.write((int)(address >> 8));
    // Wire.write((int)(address & 0xFF));
    // Wire.endTransmission();
    // Wire.requestFrom((int)0, 1);
    // if(Wire.available()){
    //     Serial.println("wire available!");
    //     data = Wire.read();
    // }
    // delay(3);
    // return data;

    IIC_Start();
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(address>>8);//发送高地址
//		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((address/256)<<1));   //发送器件地址0XA0,写数据 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(address%256);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //进入接收模式			   
	IIC_Wait_Ack();
    data=IIC_Read_Byte(0);
    IIC_Stop();//产生一个停止条件
	return data;
}