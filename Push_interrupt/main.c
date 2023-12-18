/*
 * ESTE CODIGO DE EJMPLO NO TINE ANTIRREBOTE
 *
 */
#include <msp430.h> 
#include <intrinsics.h>//Pa hacer las mimisiones

//Pines de leds de la tarjeta
#define LEDr BIT0 //P1.0
#define LEDv BIT0 //P2.0

//Pines de boton y leds de la tarjeta
#define BOTON BIT1 //P1.1

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
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

    //Configuramos la interrupion del boton
    P1IE |= BOTON;//Habilitamos la interrupciones por flanco
    P1IES |= BOTON;//Por flanco negativo

    do {
        P1IFG = 0; //Limpiamos yodas las interrupciones pendientes...
    } while (P1IFG != 0);


	for(;;){

	    //Ponemos a hacer la mimicion al micro porque no tiene na que hacer
	    __low_power_mode_4(); // LPM4 with int'pts , all clocks off
	}
}

#pragma vector = PORT1_VECTOR
    __interrupt void PORT1_ISR ( void ){

    P2OUT ^= LEDv; // Toggle LEDv
    P1OUT ^= LEDr; // Toggle LEDr

    P1IES ^= BOTON; // Toggle edge

    do {
        P1IFG = 0; // Clear any pending interrupts...
    } while (P1IFG != 0); // ...until none remain

}
