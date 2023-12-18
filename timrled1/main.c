/*
 * Se togglea los estados de los leds segun un timer
 *
 * Se iplementa por polling
 */

#include <msp430.h> 
#include <stdint.h>

//Pulsos por contar maximos del timer
#define PULSOS 65535

//Pines de leds de la tarjeta
#define LEDr BIT0 //P1.0
#define LEDv BIT0 //P2.0

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode

    //Configuramosel timer0B
    /*
     * TBSSEL_2 --> SMCLK
     * ID_3 --> DIV /8
     * TBCLR --> Timer_B clear. Setting this bit clears TBxR, the clock divider logic (the divider
                setting remains unchanged), and the count direction. The TBCLR bit is
                automatically reset and is always read as zero.
       MC_2--> continuous mode
     */

    //TB0CTL = MC_2|ID_3|TBSSEL_2|TBCLR;// Continuous up mode , divide clock by 8, clock from SMCLK , clear timer

    TB0CCR0 = PULSOS;//Cuenta hasta X pulsos
    TB0CTL = MC_1|ID_3|TBSSEL_2|TBCLR|CNTL_0;// Up mode , divide clock by 16, clock from SMCLK , clear timer,16 BITS

    //Configuramos los pines OUTPUTS
    P1DIR |= LEDr;
    P1OUT |= LEDr; //Estado inicial 1 ON
    P2DIR |= LEDv;
    P2OUT &= ~LEDv; //Estado inicial 0 OFF

    for(;;){


        if((TBCTL & TBIFG) == TBIFG){ //Bandera activa de overflow del timer???

            P2OUT ^= LEDv;
            P1OUT ^= LEDr;

            TBCTL &= ~TBIFG;//Limpiamos la bandera de overflow
        }

    }
}
