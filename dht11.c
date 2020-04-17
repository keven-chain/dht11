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
	Delay30ms();//������������18ms
	dht = 1;
	while(dht);//�ȴ��ӻ���Ӧ
	while(!dht);//�ӻ�����80us�ĵ͵�ƽ
	while(dht);	//�ӻ���������80us
}

void DHT11_Read(char *dataRead)
{
	char i,j,flag,byteRead;
	DHT11_Start();//��������start�ź�
	for(j=0;j<5;j++)
	{ //��ȡ5���ֽ�
		for(i=0;i<8;i++)
		{
			while(!dht);//�ȴ���ʼ�źŵĸߵ�ƽ
			Delay60us();//�ӳ�60us���������֮���Ǹߵ�ƽ�������߼�1����������߼�0��
			if(dht)//�߼�1
			{
				flag=1;
				while(dht);//�ȴ��߼�1�ĸߵ�ƽ��ȥ
			}
			else flag=0;
			byteRead |= flag;
			byteRead <<= 1;	
		}
		dataRead[j]=byteRead;	
	}
	if(dataRead[0]+dataRead[1]+dataRead[2]+dataRead[3]!=dataRead[4]) //���������Ƿ��ǶԵ�
		dataRead=0;	
}

void Serial_Print(char *str)
{
	Uart_String("hum:");
	Uart_char(str[0]/10+0x30);//ȡ������λ�ϵ�����Ȼ��ת��asc��ֵ
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
