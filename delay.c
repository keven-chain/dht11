#include "delay.h"
#include "intrins.h"
void Delay1000ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 92;
	j = 50;
	k = 238;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}




void Delay30ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 3;
	j = 189;
	k = 92;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay60us()		//@24.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 99;
	do
	{
		while (--j);
	} while (--i);
}



