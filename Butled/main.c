/*
 * Si se preciona el boton se enciene el led verde, de lo contrario
 * se enciede el rojo y se apaga el verde
 *
 * Se iplementa por polling
 */

#include <msp430.h>

//Pines de boton y leds de la tarjeta
#define LEDr BIT0 //P1.0
#define LEDv BIT0 //P2.0
#define BOTON BIT1 //P1.1

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode

    //Configuramos los pines OUTPUTS
    P1DIR |= LEDr;
    P2DIR |= LEDv;
    //Configuramos los pines INPUTS
    P1DIR &= ~BOTON;
    P1REN |= BOTON; // Habilitamos las resistencias de pull down up
    P1OUT |= BOTON; // Escogemos pullup

    for(;;){

        while((P1IN & BOTON) != BOTON){ //(active low)
            P2OUT |= LEDv;   //LEDv on
            P1OUT &= ~LEDr;  //LEDr off
        }
        while((P1IN & BOTON) == BOTON) { //Inverso
            P2OUT &= ~LEDv;
            P1OUT |= LEDr;
        }

    }
}
