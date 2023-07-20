#include "mcp23017.h"
#include <stdio.h>
#include "cmsis_os2.h"
#include "iot_errno.h"
#include "genki_pin.h"
#include "hi_i2c.h"
#include "hi_errno.h"

#include "genki_pin.h"
#include <hi_stdlib.h>
 
#define MCP23017_I2C_IDX HI_I2C_IDX_0
#define MCP23017_I2C_ADDRESS 0x40
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit MCP23017_INIT(unsigned char deviceAddr,unsigned char ab,unsigned char hwa,unsigned char o)
//  函数功能：初始化指定地址的MCP23017器件
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  intab——配置INTA、INTB是否关联，取值INTA_INTB_CONJUNCTION、INTA_INTB_INDEPENDENT
//		  hwa——配置A0、A1、A2硬件地址是否使能，取值HWA_EN、HWA_DIS	
//		  o——配置INTA、INTB的输出类型，取值INT_OD、INT_PUSHPULL_HIGH、INT_PUSHPULL_LOW 
//--------------------------------------------------------------------------------------  
int MCP23017_INIT(hi_u8 deviceAddr,hi_u8 intab,hi_u8 hwa,hi_u8 o){
    hi_u8 state = 0x2E;
    int res;
 
    if(intab==INTA_INTB_CONJUNCTION){
		state |= 0x40;
	}
	if(hwa==HWA_DIS){
		state &= (~0x08);
	}
	if(o==INT_PUSHPULL_HIGH){
		state &= (~0x04);
		state |= 0x02;
	}
	if(o==INT_PUSHPULL_LOW){
		state &= (~0x04);
		state &= (~0x02);
	}
 
    res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_IOCON,state);
 
    return res;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：MCP23017_IO_DIR(unsigned char deviceAddr,unsigned char port,unsigned char pin,unsigned char dir)
//  函数功能：设置制定地址的MCP23017的指定端口的指定引脚为输入或输出状态
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//		  pin——引脚号，取值PIN0-PIN7对应端口的8个引脚,ALLPIN包括端口所有8个引脚
//		  dir——输入输出方向，取值INPUT、OUTPUT 
//--------------------------------------------------------------------------------------   
int MCP23017_IO_DIR(hi_u8 deviceAddr,hi_u8 port,hi_u8 pin,hi_u8 dir){
    hi_u8 portState = 0;
    int res;
    res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_IODIR+port,&portState);
 
    //如果出错则返回
	if(res == 0){
		return res;
	}
 
	if(dir==INPUT){
		portState |= pin;
	}else{
		portState &= (~pin);
	}
 
	//写回方向寄存器
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_IODIR+port,portState);
	
	return res;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit MCP23017_IO_PU(unsigned char deviceAddr,unsigned char port,unsigned char pin,unsigned char pu)
//  函数功能：设置指定地址的MCP23017的指定端口的指定引脚是否开启上拉电阻
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//		  pin——引脚号，取值PIN0-PIN7对应端口的8个引脚,ALLPIN包括端口所有8个引脚
//		  pull——输入输出方向，取值ENABLE、DISABLE 
//--------------------------------------------------------------------------------------  
int MCP23017_IO_PU(hi_u8 deviceAddr,hi_u8 port,hi_u8 pin,hi_u8 pu){
    hi_u8 portState = 0;
    int res;
 
    //首先读取当前端口方向的配置状态
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
    res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_GPPU+port,&portState);
 
    //如果出错则返回
	if(res == 0){
		return res;
	}
 
	if(pu==ENABLE){
		portState |= pin;
	}else{
		portState &= (~pin);
	}
 
	//写回方向寄存器
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_GPPU+port,portState);
	
	return res;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit MCP23017_IO_POLARITY(unsigned char deviceAddr,unsigned char port,unsigned char pin,unsigned char polarity)
//  函数功能：设置指定地址的MCP23017的指定端口的指定引脚是否对端口极性取反
//			  当设置为取反时，读取的端口状态与实际输入状态极性相反
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//		  pin——引脚号，取值PIN0-PIN7对应端口的8个引脚,ALLPIN包括端口所有8个引脚
//		  polarity——是否取反，取值POLARITY_REVERSE、POLARITY_NON_REVERSE 
//--------------------------------------------------------------------------------------   
int MCP23017_IO_POLARITY(hi_u8 deviceAddr,hi_u8 port,hi_u8 pin,hi_u8 polarity){
    hi_u8 portState = 0;
	int res;
	
	//首先读取当前端口极性的配置状态
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_IPOL+port,&portState);
 
	//如果出错则返回
	if(res == 0){
		return res;
	}
 
	if(polarity==POLARITY_REVERSE){
		portState |= pin;
	}else{
		portState &= (~pin);
	}
 
	//写回方向寄存器
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_IPOL+port,portState);
	
	return res;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit MCP23017_IO_INT(unsigned char deviceAddr,unsigned char port,unsigned char pin,unsigned char Interupt)
//  函数功能：设置指定地址的MCP23017的指定端口的指定引脚是否开启中断功能及中断的类型
//			  可以设置位不开启中断、高电平中断、低电平中断、电平变化中断
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//		  pin——引脚号，取值PIN0-PIN7对应端口的8个引脚,ALLPIN包括端口所有8个引脚
//		  intKind——中断的类型，取值DIS_INTERRUPT、HIGHLEVEL_INTERRUPT,LOWLEVEL_INTERRUPT,CHANGE_INTERRUPT 
//--------------------------------------------------------------------------------------   
int MCP23017_IO_INT(hi_u8 deviceAddr,hi_u8 port,hi_u8 pin,hi_u8 intKind){
    hi_u8 portState_GPINTEN = 0;	  //中断使能寄存器
	hi_u8 portState_DEFVAL = 0;	  //中断默认值寄存器
	hi_u8 portState_INTCON = 0;	  //中断控制寄存器
	int res;
	
	//首先读取当前配置状态
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_GPINTEN+port,&portState_GPINTEN);
 
	//如果出错则返回
	if(res == 0){
		return res;
	}
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_DEFVAL+port,&portState_DEFVAL);
 
	//如果出错则返回
	if(res == 0){
		return res;
	}
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_INTCON+port,&portState_INTCON);
 
	//如果出错则返回
	if(res == 0){
		return res;
	}
 
	//判断中断的类型
	//如果是关闭中断
	if(intKind==DIS_INTERRUPT){
		portState_GPINTEN &= (~pin);		
	}
	//如果是变化中断
	if(intKind==CHANGE_INTERRUPT){
		portState_GPINTEN |= pin;
		portState_INTCON &= (~pin);		
	}
	//如果是高电平中断
	if(intKind==HIGHLEVEL_INTERRUPT){
		portState_GPINTEN |= pin;
		portState_INTCON |= pin;
		portState_DEFVAL &= (~pin);		
	}
	//如果是高电平中断
	if(intKind==LOWLEVEL_INTERRUPT){
		portState_GPINTEN |= pin;
		portState_INTCON |= pin;
		portState_DEFVAL |=pin;		
	}
	//写回寄存器
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_GPINTEN+port,portState_GPINTEN);
	//如果出错则返回
	if(res == 0){
		return res;
	}
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_INTCON+port,portState_INTCON);
	//如果出错则返回
	if(res == 0){
		return res;
	}
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_DEFVAL+port,portState_DEFVAL);
	//如果出错则返回
	if(res == 0){
		return res;
	}
	
	return res;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：unsigned char MCP23017_READ_INTF(unsigned char deviceAddr,unsigned char port)
//  函数功能：读取指定地址的MCP23017的指定端口的中断标志寄存器
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//	返回值：值中为1的位表示产生中断
//--------------------------------------------------------------------------------------   
hi_u8 MCP23017_READ_INTF(hi_u8 deviceAddr,hi_u8 port){
    hi_u8 portState = 0;
	int res;
	
	//首先读取当前端口状态
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_INTF+port,&portState);
 
	//如果出错则返回0
	if(res == 0){
		return 0;
	}else{
		return portState;
	}
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：unsigned char MCP23017_READ_INTCAP(unsigned char deviceAddr,unsigned char port)
//  函数功能：读取指定地址的MCP23017的指定端口发生中断时中断捕捉寄存器捕捉到的端口值
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//	返回值：中断发生时，当时端口的值
//--------------------------------------------------------------------------------------   
hi_u8 MCP23017_READ_INTCAP(hi_u8 deviceAddr,hi_u8 port){
    hi_u8 portState = 0;
	int res;
	
	//首先读取当前端口状态
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_INTCAP+port,&portState);
 
	//如果出错则返回0
	if(res == 0){
		return 0;
	}else{
		return portState;
	}
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：unsigned char MCP23017_READ_GPIO(unsigned char deviceAddr,unsigned char port)
//  函数功能：读取指定地址的MCP23017的指定端口值
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//	返回值：中断发生时，当时端口的值
//--------------------------------------------------------------------------------------   
hi_u8 MCP23017_READ_GPIO(hi_u8 deviceAddr,hi_u8 port){
    hi_u8 portState = 0;
	int res;
	
	//首先读取当前端口状态
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_GPIO+port,&portState);
 
	//如果出错则返回0
	if(res == 0){
		return 0;
	}else{
		return portState;
	}
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit MCP23017_WRITE_GPIO(unsigned char deviceAddr,unsigned char port,unsigned char val)
//  函数功能：向指定地址的MCP23017的指定端口写值
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//		  val——要写入端口寄存器的值
//--------------------------------------------------------------------------------------   
int MCP23017_WRITE_GPIO(hi_u8 deviceAddr,hi_u8 port,hi_u8 val){
    int res;
	
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_GPIO+port,val);
 
	return res;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit MCP23017_SET_GPIO_PIN(unsigned char deviceAddr,unsigned char port,unsigned char pin,unsigned char s)
//  函数功能：设置指定地址的MCP23017的指定端口的指定引脚
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//		  pin——引脚号，取值PIN0~PIN7,ALLPIN包括端口所有8个引脚
//		  s——取值SET、RESET
//--------------------------------------------------------------------------------------   
int MCP23017_SET_GPIO_PIN(hi_u8 deviceAddr,hi_u8 port,hi_u8 pin,hi_u8 s){
    hi_u8 portState = 0;
	int res;
	
	//首先读取当前端口方向的配置状态
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_GPIO+port,&portState);
 
	//如果出错则返回
	if(res == 0){
		return res;
	}
 
	if(s ==SET){
		portState |= pin;
	}else{
		portState &= (~pin);
	}
 
	//写回方向寄存器
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_GPIO+port,portState);
	
	return res;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：unsigned char MCP23017_READ_OLAT(unsigned char deviceAddr,unsigned char port)
//  函数功能：读取指定地址的MCP23017的指定端口的输出锁存寄存器
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//	返回值：输出锁存寄存器值，而不是端口值
//--------------------------------------------------------------------------------------   
hi_u8 MCP23017_READ_OLAT(hi_u8 deviceAddr,hi_u8 port){
    hi_u8 portState = 0;
	int res;
	
	//首先读取当前端口状态
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Read_Byte_MCP23017(deviceAddr,MCP23017_OLAT+port,&portState);
 
	//如果出错则返回0
	if(res == 0){
		return 0;
	}else{
		return portState;
	}
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit MCP23017_WRITE_OLAT(unsigned char deviceAddr,unsigned char port,unsigned char val)
//  函数功能：写指定地址的MCP23017的指定端口的输出锁存寄存器
//	参数：deviceAddr——设备地址，有A0，A1，A2决定
//		  port——端口名称，取值MCP23017_PORTA、MCP23017_PORTB
//		  val——要写入端口寄存器的值
//--------------------------------------------------------------------------------------   
int MCP23017_WRITE_OLAT(hi_u8 deviceAddr,hi_u8 port,hi_u8 val){
    int res;
	
	//因为B端口的地址比A端口的寄存器的地址都是大1，所以采用+的技巧切换寄存器
	res = I2C_Write_Byte_MCP23017(deviceAddr,MCP23017_OLAT+port,val);
 
	return res;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit I2C_Read_Byte_MCP23017(unsigned char deviceAddr, unsigned char regAddress, unsigned char* recv)
//  函数功能：从设备读一个字节的数据
//	说明：deviceAddr——设备地址，regAddress——读出地址，recv——接收读取的内容  
//--------------------------------------------------------------------------------------   
int I2C_Read_Byte_MCP23017(hi_u8 deviceAddr, hi_u8 regAddress, hi_u8* recv){
 
    uint8_t writeBuf[1] = {0};
    hi_i2c_idx id = MCP23017_I2C_IDX;
    hi_i2c_data i2cData = {0};
    writeBuf[0] = regAddress;
    i2cData.send_buf = writeBuf;
    i2cData.send_len = 1;
 
    hi_i2c_write(id, (DRIVER_ID | (deviceAddr<<1) | I2C_WRITE), &i2cData);
 
    uint8_t readBuf[1] = {0};
    hi_i2c_data i2cRData = {0};
    i2cRData.receive_buf = readBuf;
    i2cRData.receive_len = 1;
 
    uint32_t Rresult = hi_i2c_read(id, (DRIVER_ID | (deviceAddr<<1) | I2C_READ),&i2cRData);
 
    printf("[MCP23017 READ]%d \r\n",Rresult);
 
    *recv = readBuf[0];
 
    if(Rresult == 0){
        Rresult = 1;
    }
 
    return Rresult;
}
 
//--------------------------------------------------------------------------------------   
//  函数名称：bit I2C_Write_Byte_MCP23017(unsigned char deviceAddr, unsigned char regAddress, unsigned char content)
//  函数功能：向设备写一个字节的数据
//	说明：deviceAddr——设备地址，regAddress——寄存器地址，content——写入的内容  
//--------------------------------------------------------------------------------------   
int I2C_Write_Byte_MCP23017(hi_u8 deviceAddr, hi_u8 regAddress, hi_u8 content){
 
    uint8_t write_data[3] = {regAddress,content};
    hi_i2c_idx id = MCP23017_I2C_IDX;
    hi_i2c_data i2cData = {0};
    i2cData.send_buf = write_data;
    i2cData.send_len = 2;
 
    uint32_t result = hi_i2c_write(id, (DRIVER_ID | (deviceAddr<<1) | I2C_WRITE), &i2cData);
 
    printf("[MCP23017 WRITE]%d \r\n",result);
 
    if(result == 0){
        result = 1;
    }
 
    return result;
}