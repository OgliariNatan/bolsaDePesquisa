#ifndef _USART_H
#define _USART_H

#include "globalDefines.h"

void usart_init(void);
void usart_send_char(unsigned char *ch);
void usart_sendstring(char *mens);
void usart_send_hex(char *ch);


#endif