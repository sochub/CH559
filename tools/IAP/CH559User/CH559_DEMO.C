
/********************************** (C) COPYRIGHT ******************************
* File Name          : CH559_DEMO.C
* Author             : WCH
* Version            : V1.3
* Date               : 2016/06/24
* Description        : IAP����������
                       ��ʾ�û��������У���P13����͵�ƽʱ��������ת��IAP�������������û���������
*******************************************************************************/

#include "../../CH559.H"
#include <string.h>
#include <intrins.h>

#define IAP_ProgrameStartAddr    (0xE800)             //IAP�����ŵ���ʼ��ַ���õ�ַ����Ҫ��ʵ�ʵ�IAP��ַС4�ֽ�
sbit EnableIAP  = P1^3;                                    //IAP��ת�������

typedef void( *pTaskFn)( void );
pTaskFn tasksArr[1]; 

#pragma NOAREGS

/*******************************************************************************
* Function Name  : mDelay20us(UNIT16 n)
* Description    : 20us��ʱ��������Ƶ12MHz����ʱ��׼��������Ƶ�ο�DEBUG.C����ʱ����
* Input          : UNIT16 n
* Output         : None
* Return         : None
*******************************************************************************/ 
void mDelay20us( UINT16 n )
{
	for( n <<= 3;n;--n ){
		_nop_( );
	}
}

/*******************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void main( void ) 
{
	UINT16 i=0;

	P4_DIR = 0x00;
	P4_DIR |= 0x0f;       		                                 //P40-P43���ʹ��
	P4_OUT = 0x0A;                                             //P41 P43����ߵ�ƽ
	tasksArr[0] = (pTaskFn)(IAP_ProgrameStartAddr+0x00);       //IAP�����ַ
	while(1)
  {
		if( EnableIAP == 0 )                                     //���P13�����Ƿ�Ϊ��
    {	  
			P4_OUT =  0x0f;
			P4_OUT =  ~(1<<1);		                                 //P4���ӵ�LED����״ָ̬ʾ
			mDelay20us(60000);
			P4_OUT =  0x0f;
	 		(tasksArr[0])( );                                      //��ת��IAP������
		}
	  i++;
		if( i == 200 ) i = 0;                                    //�û�������Ը��������飬�˴���ֻ������
		if( i == 0 )   P4_OUT =  0x0f;
		if( i == 100 ) P4_OUT =  ~(1<<2);
		mDelay20us(1000);
	}
}