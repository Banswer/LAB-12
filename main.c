/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18446
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#include "tm1650.h"
#include "clock.h"
#include "controller.h"
#include "button.h"
#include "beat.h"

#include <stdio.h>
#include <stdint.h>

//uint16_t address;
static uint8_t lastRun;
/*
                         Main application
 */

int dataPointer = 0;
uint8_t  dmxChannelData[514];



void DMXReceive(){
    LATC5 = 1;
    if(RC1STAbits.FERR){
        dataPointer = 0;
    }
    
    dmxChannelData[dataPointer++] = RC1REG;
    
    // check for overrun erro to make each bytes are rcorded
    if(RC1STAbits.OERR){
        // disable reaciever and enable receiver
        RC1STAbits.CREN = 0;// disable receiver
        RC1STAbits.CREN = 1;//enable receiver
    }
    LATC5 = 0;
}


void LED_init(){
    //
    
    RC7PPS = 0x09;//route channel one to RC7 //for 4
    TRISC7 = 0; // make RC7 an output //for 4
        
    T2CLKCON = 0x01;
    T2CONbits.ON = 1;
    
    CCP1CONbits.CCP1EN = 1; //for 4
    CCP1CONbits.MODE = 0b1100; // for 4
    
    
    RC6PPS = 0x0A; //change to CCP2
    TRISC6 = 0;
    CCP2CONbits.CCP2EN = 1; 
    CCP2CONbits.MODE = 0b1100;
    
    RC3PPS = 0x0B; //change to CCP3
    TRISC3 = 0;
    CCP3CONbits.CCP3EN = 1; 
    CCP3CONbits.MODE = 0b1100;
    
    RC4PPS = 0x0C; //change to CCP4
    TRISC4 = 0;
    CCP4CONbits.CCP4EN = 1; 
    CCP4CONbits.MODE = 0b1100;
    
    
    
    
}

void LED_setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white){
    

   
    CCPR1L = red >> 1; //get the value
    CCPR2L = green >> 1;
    CCPR3L = blue >> 1;
    CCPR4L = white >> 1;
}

static void soundTask()
{
    if (CLOCK_getTime() - lastRun < 100)
        return;

    lastRun = CLOCK_getTime();
    //LATC5 = 0;
    LED_setColor(0, 0, 0, 0);
    
    
    if (BEAT_detected()) {
      //  LATC5 = 1;
        LED_setColor(255, 255, 255, 255);
        LED_setColor(0, 255, 0, 0);
        LED_setColor(0, 0, 255, 0);
    }
}

static time_t lastTime = 0;

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    __delay_ms(500);
    EUSART1_SetRxInterruptHandler(DMXReceive);

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    TM1650_init();
    CLOCK_init();
    BUTTONS_init();
    CONTROLLER_init();
    BEAT_init();
    
    
     LED_init();
    while(1){
        BUTTONS_task();
        CONTROLLER_task();
        BEAT_task();
       // LED_setColor(dmxChannelData[2], dmxChannelData[3], dmxChannelData[4], dmxChannelData[5]);
       //LED_setColor(dmxChannelData[address+1], dmxChannelData[address+2], dmxChannelData[address+3], dmxChannelData[address+4]);
        
        
           soundTask();
    }
                
    


    // only run every 10 ms
}
/**
 End of File
*/