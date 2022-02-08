/**
  *****************************************************************************
  * @file retarget.c
  * @author hzhong
  * @version V0.0.1
  * @date 05/04/2016
  * @brief This file retargets the output with printf.
  *****************************************************************************
  * @copy
  *
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "hyhwUart.h"


//#pragma import(__use_no_semihosting)


//char CmdLine[] = "";

//char * _sys_command_string(char *cmd, int len) {
//  return (CmdLine);
//}


//void _sys_exit(int return_code) {
//label:  goto label;  /* endless loop */
//}


//struct __FILE { int handle; /* Add whatever you need here */ };
//FILE __stdout;
//FILE __stdin;


int fputc(int ch, FILE *f) {
  /* Write a character to the USART */
  if (ch=='\n') fputc('\r',f);
  USART->DR = ch;

  /* wait until the transmit FIFO is empty */
  while (!((USART->FR) & (1 << 7)));
  
  return (ch);
}

int fgetc(FILE *f)
{
	//RXFF, Receive FIFO full, 
	while (!(USART->FR & (1 << 6)));                             //wait for full
	return (USART->DR);
}
