#ifndef UART_NRF51_H
#define UART_NRF51_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//-------------------------------------------------------------------
/// @brief NRF51 UART peripheral register block.
//
typedef struct 
{
    // Task register group
    uint32_t startRx;         // Start UART receiver                      (+0x000)
    uint32_t stopRx;          // Stop UART receiver                       (+0x004)
    uint32_t startTx;         // Start UART transmitter                   (+0x008)
    uint32_t stopTx;          // Stop UART transmitter                    (+0x00C)
    uint8_t  pad0[0x00C];     // Padding
    uint32_t suspend;         // Suspend UART                             (+0x01C)
    uint8_t  pad1[0x0E0];     // Padding
    
    // Event register group
    uint32_t clearToSend;     // Clear to send                            (+0x100)
    uint32_t notClearToSend;  // Not clear to send                        (+0x104)
    uint32_t rxdReady;        // Data received in RXD                     (+0x108)
    uint8_t  pad2[0x010];     // Padding
    uint32_t txdReady;        // Data sent from TXD                       (+0x11C)
    uint8_t  pad3[0x004];     // Padding
    uint32_t error;           // Error detected                           (+0x124)
    uint8_t  pad4[0x01C];     // Padding
    uint32_t rxTimeout;       // Receiver timeout                         (+0x144)
    uint8_t  pad5[0x1B8];     // Padding

    // Registers
    uint32_t intEnable;       // Enable/disable interrupt                 (+0x300)
    uint32_t intEnableSet;    // Enable interrupt                         (+0x304)
    uint32_t intEnableClear;  // Disable interrupt                        (+0x308)
    uint8_t  pad6[0x174];     // Padding
    uint32_t errorSrc;        // Error source                             (+0x480)
    uint8_t  pad7[0x07C];     // Padding
    uint32_t enable;          // Enable UART                              (+0x500)
    uint8_t  pad8[0x004];     // Padding
    uint32_t pinSelectRts;    // Pin select for RTS                       (+0x508)
    uint32_t pinSelectTxd;    // Pin select for TXD                       (+0x50C)
    uint32_t pinSelectCts;    // Pin select for CTS                       (+0x510)
    uint32_t pinSelectRxd;    // Pin select for RXD                       (+0x514)
    uint32_t rxd;             // RXD register                             (+0x518)
    uint32_t txd;             // TXD register                             (+0x51C)
    uint8_t  pad9[0x004];     // Padding
    uint32_t baudRate;        // Baud rate                                (+0x524)
    uint8_t  pad10[0x044];    // Padding
    uint32_t config;          // Configuration of parity and flow control (+0x56C)

} tNrf51UartRegisterBlock;

/// @brief UART0 peripheral register block base address.
#define NRF51_UART0_BASE_ADDR (0x40002000)

/// @brief UART0 peripheral.
#define NRF51_UART0           ((tNrf51UartRegisterBlock*)NRF51_UART0_BASE_ADDR)



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UART_NRF51_H
