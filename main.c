//���ߣ�qzl
//DHT11���ڴ�ӡ   �����ʣ�9600  8λ���� ��Ч��
//����Ƶ�ʣ�24M
//�������ߵ�������dht11.c
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