#include <plib.h>
#include <stdint.h>
#include "chipKITEthernetAPI.h"

/*
 *  Main Clock       -> SYSCLK = (Crystal_Freq / FPLLIDIV) * FPLLMUL / FPLLODIV
 *  Peripheral Clock -> PBCLK  = SYSCLK / FPBDIV
 *
 *  SYSCLK = 80MHz, PBCLK = 40MHz
 */
#pragma config FNOSC     = PRIPLL            // Oscillator Selection
#pragma config FPLLIDIV  = DIV_2             // PLL Input Divider (PIC32 Starter Kit: use divide by 2 only)
#pragma config FPLLMUL   = MUL_20            // PLL Multiplier
#pragma config FPLLODIV  = DIV_1             // PLL Output Divider
#pragma config FPBDIV    = DIV_2             // Peripheral Clock divisor
#pragma config FWDTEN    = OFF               // Watchdog Timer
#pragma config WDTPS     = PS32768           // Watchdog Timer Postscale
#pragma config FCKSM     = CSECMD            // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC  = OFF               // CLKO Enable
#pragma config POSCMOD   = HS                // Primary Oscillator
#pragma config IESO      = OFF               // Internal/External Switch-over
#pragma config FSOSCEN   = OFF               // Secondary Oscillator Enable
#pragma config CP        = OFF               // Code Protect
#pragma config BWP       = OFF               // Boot Flash Write Protect
#pragma config PWP       = OFF               // Program Flash Write Protect
/* Ethernet configuration. */
#pragma config FETHIO=ON
#pragma config FMIIEN=OFF

/* Configure the microcontroller for use with the on-board (MX7) licensed
 * debugger circuit.
 */
#pragma config ICESEL = ICS_PGx1

uint8_t mac[] = { 0x54, 0x55, 0x58, 0x10, 0x00, 0x24 };
uint8_t ip[] = { 192,168,3,9 };
uint8_t gateway[] = { 192,168,3, 14 };
uint8_t subnet[] = { 255, 255, 255, 0 };
uint8_t dns1[] = { 192, 168, 3, 14 };
uint8_t dns2[] = { 8, 8, 8, 8 };

int main() {
  INTEnableSystemMultiVectoredInt();
  PORTSetPinsDigitalOut (IOPORT_G, BIT_12|BIT_13| BIT_14|BIT_15);
  ChipKITEthernetBegin(mac, ip, gateway, subnet, dns1, dns2);

  PORTWrite(IOPORT_G, 0);
  while (1) {
    ChipKITPeriodicTasks();
  }
}