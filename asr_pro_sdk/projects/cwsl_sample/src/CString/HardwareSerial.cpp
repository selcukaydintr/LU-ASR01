

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

/*---------------------------------------------------------------------------------------------------------*/
/* Includes of local headers                                                                               */
/*---------------------------------------------------------------------------------------------------------*/


#include "HardwareSerial.h"
#include "system_hook.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Macro, type and constant definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/

#define RX_BUFFER_SIZE 250



struct ring_buffer {
  unsigned char buffer[RX_BUFFER_SIZE];
  int head;
  int tail;
};

ring_buffer rx_buffer0 = { { 0 }, 0, 0 };
ring_buffer rx_buffer1 = { { 0 }, 0, 0 };
ring_buffer rx_buffer2 = { { 0 }, 0, 0 };

inline void store_char(unsigned char c, ring_buffer *rx_buffer)
{
	int i = (rx_buffer->head + 1) % RX_BUFFER_SIZE;

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != rx_buffer->tail) {
		rx_buffer->buffer[rx_buffer->head] = c;
		rx_buffer->head = i;
	}
}
extern "C" {
 void hd_uart0_irq_handler(void)
{
	uint8_t rev;

    /*发送数据*/
    if (((UART_TypeDef*)UART0)->UARTMIS & (1UL << UART_TXInt))
    {
        UART_IntClear((UART_TypeDef*)UART0,UART_TXInt);
    }
    /*接受数据*/
    if (((UART_TypeDef*)UART0)->UARTMIS & (1UL << UART_RXInt))
    {
        //here FIFO DATA must be read out
        rev=UART_RXDATA((UART_TypeDef*)UART0);
        UART_IntClear((UART_TypeDef*)UART0,UART_RXInt);
		store_char(rev, &rx_buffer0);
    }

    UART_IntClear(UART0,UART_AllInt);
}
 void hd_uart1_irq_handler(void)
{
	uint8_t rev;
    /*发送数据*/
    if (((UART_TypeDef*)UART1)->UARTMIS & (1UL << UART_TXInt))
    {
        UART_IntClear(UART1,UART_TXInt);
    }
    /*接受数据*/
    if (((UART_TypeDef*)UART1)->UARTMIS & (1UL << UART_RXInt))
    {
        //here FIFO DATA must be read out
        rev=UART_RXDATA((UART_TypeDef*)UART1);
        UART_IntClear((UART_TypeDef*)UART1,UART_RXInt);
		store_char(rev, &rx_buffer1);
    }

    UART_IntClear(UART1,UART_AllInt);
}
 void hd_uart2_irq_handler(void)
{
	uint8_t rev;
    /*发送数据*/
    if (((UART_TypeDef*)UART2)->UARTMIS & (1UL << UART_TXInt))
    {
        UART_IntClear(UART2,UART_TXInt);
    }
    /*接受数据*/
    if (((UART_TypeDef*)UART2)->UARTMIS & (1UL << UART_RXInt))
    {
        //here FIFO DATA must be read out
        rev=UART_RXDATA((UART_TypeDef*)UART2);
        UART_IntClear((UART_TypeDef*)UART2,UART_RXInt);
		store_char(rev, &rx_buffer2);
    }

    UART_IntClear(UART2,UART_AllInt);
}

}


/*---------------------------------------------------------------------------------------------------------*/
/* Interrupt Handler                                                                                 	   */
/*---------------------------------------------------------------------------------------------------------*/

// Constructors ////////////////////////////////////////////////////////////////

    HardwareSerial::HardwareSerial(ring_buffer *rx_buffer,UART_TypeDef *UART)
	 {
	 _rx_buffer=rx_buffer;
	 _port=UART;
	 	 
	 }

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(uint32_t speed)
{

	UART_BaudRate baud=UART_BaudRate115200;
	if(speed==2400)baud=UART_BaudRate2400;
	if(speed==4800)baud=UART_BaudRate4800;
	if(speed==9600)baud=UART_BaudRate9600;
	if(speed==19200)baud=UART_BaudRate19200;
	if(speed==38400)baud=UART_BaudRate38400;
	if(speed==57600)baud=UART_BaudRate57600;
	if(speed==115200)baud=UART_BaudRate115200;
	if(speed==230400)baud=UART_BaudRate230400;
	if(speed==380400)baud=UART_BaudRate380400;
	if(speed==460800)baud=UART_BaudRate460800;
	if(speed==921600)baud=UART_BaudRate921600;
	if(speed==1000000)baud=UART_BaudRate1M;
	if(speed==2000000)baud=UART_BaudRate2M;
	if(speed==3000000)baud=UART_BaudRate3M;

	if(_port==UART1){
		UARTInterruptConfig(UART1,baud);
	}
	if(_port==UART2){
		UARTInterruptConfig(UART2,baud);
	}
	if(_port==UART0){
		UARTInterruptConfig(UART0,baud);
	}
    __eclic_irq_set_vector(UART1_IRQn, (int32_t)hd_uart1_irq_handler);
 
	__eclic_irq_set_vector(UART0_IRQn, (int32_t)hd_uart0_irq_handler);
	__eclic_irq_set_vector(UART2_IRQn, (int32_t)hd_uart2_irq_handler);


}

int HardwareSerial::available(void)
{
	return (RX_BUFFER_SIZE + _rx_buffer->head - _rx_buffer->tail) % RX_BUFFER_SIZE;
}
int HardwareSerial::peek(void)
{
  if (_rx_buffer->head == _rx_buffer->tail) {
    return -1;
  } else {
    return _rx_buffer->buffer[_rx_buffer->tail];
  }
}

int HardwareSerial::read(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
	if (_rx_buffer->head == _rx_buffer->tail) {
		return -1;
	} else {
		unsigned char c = _rx_buffer->buffer[_rx_buffer->tail];
		_rx_buffer->tail = (_rx_buffer->tail + 1) % RX_BUFFER_SIZE;
		return c;
	}
}

void HardwareSerial::flush()
{
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// were full, not empty.
	_rx_buffer->head = _rx_buffer->tail;
}
/*
void HardwareSerial::end()
{
  // wait for transmission of outgoing data
  while (_tx_buffer_head != _tx_buffer_tail)
    ;
  
  // clear any received data
  _rx_buffer_head = _rx_buffer_tail;
}*/

size_t HardwareSerial::write(uint8_t ch)
{
	if (_port == UART1)
	{
		UartPollingSenddata((UART_TypeDef *)UART1, ch);
	}
	if (_port == UART0)
	{
		UartPollingSenddata((UART_TypeDef *)UART0, ch);
	}
	if (_port == UART2)
	{
		UartPollingSenddata((UART_TypeDef *)UART2, ch);
	}
	return 1;
}

// Preinstantiate Objects //////////////////////////////////////////////////////

HardwareSerial Serial(&rx_buffer0, UART0);
HardwareSerial Serial1(&rx_buffer1, UART1);
HardwareSerial Serial2(&rx_buffer2, UART2);

