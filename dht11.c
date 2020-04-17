#include "dht11.h"
#include "delay.h"
#include "UART.h"
#include <STC8.H>
sbit dht=P5^5;
void DHT11_Start(void)
{
	Delay1000ms();
	dht = 1;
	dht = 0;
	Delay30ms();//总线拉低至少18ms
	dht = 1;
	while(dht);//等待从机响应
	while(!dht);//从机发送80us的低电平
	while(dht);	//从机拉高总线80us
}

void DHT11_Read(char *dataRead)
{
	char i,j,flag,byteRead;
	DHT11_Start();//主机发送start信号
	for(j=0;j<5;j++)
	{ //读取5个字节
		for(i=0;i<8;i++)
		{
			while(!dht);//等待起始信号的高电平
			Delay60us();//延迟60us，如果过了之后还是高电平，则是逻辑1，否则就是逻辑0；
			if(dht)//逻辑1
			{
				flag=1;
				while(dht);//等待逻辑1的高电平过去
			}
			else flag=0;
			byteRead |= flag;
			byteRead <<= 1;	
		}
		dataRead[j]=byteRead;	
	}
	if(dataRead[0]+dataRead[1]+dataRead[2]+dataRead[3]!=dataRead[4]) //检验数据是否是对的
		dataRead=0;	
}

void Serial_Print(char *str)
{
	Uart_String("hum:");
	Uart_char(str[0]/10+0x30);//取出单个位上的数，然后转成asc的值
	Uart_char(str[0]%10+0x30);
	Uart_char('.');
	Uart_char(str[1]/10+0x30);
	Uart_char(str[1]%10+0x30);
	Uart_String("\r\n");
	
	Uart_String("temp:");
	Uart_char(str[2]/10+0x30);
	Uart_char(str[2]%10+0x30);
	Uart_char('.');
	Uart_char(str[3]/10+0x30);
	Uart_char(str[3]%10+0x30);
	Uart_String("\r\n");
}
