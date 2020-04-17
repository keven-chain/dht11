
#include <STC8.H>
#include "UART.h"



void UartInit(void)		//9600bps@24.000MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xB2;		//�趨��ʱ��ֵ
	TH1 = 0xB2;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}





void Uart_char(char uartData)
{
	ES = 0;
	TI = 0;
	SBUF = uartData;
	while(!TI);
	ES = 1;
}

void Uart_String(char *str)
{
	while(*str)
	{
		Uart_char(*str);
		str++;
	}
}