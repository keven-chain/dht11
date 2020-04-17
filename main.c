//作者：qzl
//DHT11串口打印   波特率：9600  8位数据 无效对
//运行频率：24M
//定义总线的引脚在dht11.c
#include <STC8.H>
#include "UART.h"
#include "delay.h"
#include "dht11.h"
char rec[5];
void main()
{
	UartInit();
	while(1)
	{
		DHT11_Read(rec);
		Serial_Print(rec);
		Delay1000ms();
	}
}