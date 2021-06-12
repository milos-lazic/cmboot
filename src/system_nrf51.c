#include "uart_nrf51.h"

void systemInit()
{
    const char message[] = "Starting bootloader...\r\n";

    // Disable UART.
    NRF51_UART0->enable = 0x00000000;

    // Configure pin P0.09 as the TXD signal out.
    NRF51_UART0->pinSelectTxd = 9;

    // Configure pin P0.11 as the RXD signal in.
    NRF51_UART0->pinSelectRxd = 11;

    // Configure baud rate (57600 baud).
    NRF51_UART0->baudRate = 0x00EBF000;

    // Enable UART.
    NRF51_UART0->enable = 0x00000004;

    // Start UART transmitter.
    NRF51_UART0->startTx = 1;

    for (uint32_t i = 0; i < sizeof(message) - 1; i++)
    {
        NRF51_UART0->txd = message[i];
        // Wait for TXDRDY event.
        while (!(NRF51_UART0->txdReady)) {}
        // Clear TXRDY event.
        NRF51_UART0->txdReady = 0;
    }
}