/*
 * Se emula un dado digital por medio de software
 * Se manda como outputs leds indicadores de numeros binarios del 0 al 6
 */

#include <msp430.h> 
#include <stdint.h>

//Pines de boton y leds de la tarjeta
#define BOTON BIT1 //P1.1

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode

	//Configuramos los pines OUTPUTS P2.1 - P2.3
	P2DIR |= 0x0E;// Son necsariostres bits para representar en binario del 0-6
	P2OUT &= ~0x0E; //Estado inicial 0

	//Configuramos los pines INPUTS
	P1DIR &= ~BOTON;
	P1REN |= BOTON; // Habilitamos las resistencias de pull down up
	P1OUT |= BOTON; // Escogemos pullup
	
	uint8_t contador = 0;

	for(;;){

	    while((P1IN & BOTON) == BOTON){ //mientras no precionado el boton

            //__delay_cycles(500);

	        contador++;

	        if(contador > 6){
	            contador = 0; //seteamos a 0
	        }

	    }

	    P2OUT &= ~0x0E; //Limpiamos lo que se tenai anteriormente
        P2OUT |= (contador << 1);//Actualizamos indicador

	}
}
