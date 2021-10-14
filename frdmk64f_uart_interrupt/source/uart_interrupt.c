/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "stdio.h"

/*******************************************************************************
 * Definitions
 *
 *
 *
 */
volatile uint32_t g_systickCounter;

/* UART instance and clock */
#define DEMO_UART            UART0
#define DEMO_UART_CLKSRC     UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define DEMO_UART_IRQn       UART0_RX_TX_IRQn
#define DEMO_UART_IRQHandler UART0_RX_TX_IRQHandler



#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_PIN



/*! @brief Ring buffer size (Unit: Byte). */
#define DEMO_RING_BUFFER_SIZE 16

/*! @brief Ring buffer to save received data. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void workerFunc(uint8_t incominData);
/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_tipString[] =
    "Uart functional API interrupt example\r\nBoard receives characters then sends them out\r\nNow please input:\r\n";

/*
  Ring buffer for data input and output, in this example, input data are saved
  to ring buffer in IRQ handler. The main function polls the ring buffer status,
  if there are new data, then send them out.
  Ring buffer full: (((rxIndex + 1) % DEMO_RING_BUFFER_SIZE) == txIndex)
  Ring buffer empty: (rxIndex == txIndex)
*/
uint8_t demoRingBuffer[DEMO_RING_BUFFER_SIZE];
volatile uint16_t txIndex; /* Index of the data to send out. */
volatile uint16_t rxIndex; /* Index of the memory to save new arrived data. */

/*******************************************************************************
 * Code
 ******************************************************************************/

void DEMO_UART_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(DEMO_UART))
    {
        data = UART_ReadByte(DEMO_UART);


        /* If ring buffer is not full, add data to ring buffer. */
        if (((rxIndex + 1) % DEMO_RING_BUFFER_SIZE) != txIndex)
        {
        	workerFunc(data);

            demoRingBuffer[rxIndex] = data;
            rxIndex++;
            rxIndex %= DEMO_RING_BUFFER_SIZE;
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */


void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}


int main(void)
{
    uart_config_t config;

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUART_ParityDisabled;
     * config.stopBitCount = kUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 1;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;

    UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);

    /* Send g_tipString out. */
    UART_WriteBlocking(DEMO_UART, g_tipString, sizeof(g_tipString) / sizeof(g_tipString[0]));

    /* Enable RX interrupt. */
    UART_EnableInterrupts(DEMO_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
    EnableIRQ(DEMO_UART_IRQn);

    PRINTF("hello world.\r\n");

    while (1)
    {
        /* Send data only when UART TX register is empty and ring buffer has data to send out. */
        while ((kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(DEMO_UART)) && (rxIndex != txIndex))
        {
            UART_WriteByte(DEMO_UART, demoRingBuffer[txIndex]);
            txIndex++;
            txIndex %= DEMO_RING_BUFFER_SIZE;
        }
    }
}

void workerFunc(uint8_t incomingData)
{
	/*
	static size_t counter = 0;

	uint8_t* data;

	counter++;
	data[counter] = incomingData;
	if(counter == 8)
	{
		PRINTF(data);
		if(data == "MERHABA")
		{
			GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
		}
		counter = 0;
	}
	*/

	GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);

	/*
		char* data = incomingData;
		printf(data);
	*/


	PRINTF("hello world.\r\n");


	//SysTick_DelayTicks(1000U);
}


