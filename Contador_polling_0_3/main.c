/*
 * Cuenta por  polling del 0 a 3 mostrando en binario on los leds
 * El debouncing es implementado por delay
 */

#include <msp430.h> 
#include <stdint.h>

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode

    //Declaramos los pines de los leds P2.0 y P1.0 como outputs
    P1DIR |= BIT0; //MSB
    P2DIR |= BIT0; //LSB

    //Declaramos los pine de boton P1.1
    P1DIR &= ~BIT1; //como input
    P1REN |= BIT1; // Habilitamso las resistencias de pull down up
    P1OUT |= BIT1; // Escojemos puulup

    //Contador variable
    uint8_t contador = 0;

    for(;;) {

            //Logica negada
            if((P1IN & BIT1) != BIT1){//Revizamso si se tiene presionado el boton

                __delay_cycles(220000);// SW Delay  ANTIREOTE CHAFA
                contador++;
            }


            switch (contador) {//Pseudo decodificador binario
                case 0:
                    // 00
                    P1OUT &= ~BIT0;
                    P2OUT &= ~BIT0;

                    break;
                case 1:

                    // 01
                    P1OUT &= ~BIT0;
                    P2OUT |= BIT0;

                    break;
                case 2:

                    // 10
                    P1OUT |= BIT0;
                    P2OUT &= ~BIT0;

                     break;
                case 3:

                    // 11
                    P1OUT |= BIT0;
                    P2OUT |= BIT0;

                     break;
                default:
                    contador = 0;
            }

        }
}
