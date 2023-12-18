/*
 * Si se preciona el boton se togglea los estados de los leds
 *
 * Se iplementa por polling
 */

#include <msp430.h> 
#include <stdint.h>

//Pines de boton y leds de la tarjeta
#define LEDr BIT0 //P1.0
#define LEDv BIT0 //P2.0
#define BOTON BIT1 //P1.1

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode

    //Configuramos los pines OUTPUTS
    P1DIR |= LEDr;
    P1OUT |= LEDr; //Estado inicial 1 ON
    P2DIR |= LEDv;
    P2OUT &= ~LEDv; //Estado inicial 0 OFF

    //Configuramos los pines INPUTS
    P1DIR &= ~BOTON;
    P1REN |= BOTON; // Habilitamos las resistencias de pull down up
    P1OUT |= BOTON; // Escogemos pullup

    for(;;){

        /*
         * AGREGAR ALGORITMO DE ANTIDEBOUNCING
         */

        if((P1IN & BOTON) != BOTON){ //(active low)
            //Operacion logica XOR implementa un toggle
            P2OUT ^= LEDv;
            P1OUT ^= LEDr;

        }

    }
}
