#ifndef __DEBUG_H__
#define __DEBUG_H__

#define SERIAL_DEBUG 1

#if SERIAL_DEBUG
#include "uart.h"
#define DEBUG(X) UART_PutString(X)
#else
#define DEBUG(X)
#endif

#endif /* __DEBUG_H__ */
