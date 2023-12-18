//***************************************************************************************
//  Se implementa un contador de 0 a 3 con los led integrados en la tarjeta de desarrollo
//  Con un delay por software No por timmers
//***************************************************************************************
#include <msp430.h>
#include <stdint.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode

    //Declaramos los pines de los leds como outputs
    P1DIR |= BIT0; //MSB
    P2DIR |= BIT0; //LSB

    //Contador variable
    uint8_t contador = 0;

    //SW delay
    volatile unsigned int i;            // volatile to prevent optimization

    for(;;) {

            contador++;

            if(contador>3){//Limitamos a maximo contar hasta 3
                contador = 0;
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
                    break;
            }


            i = 50000;// SW Delay
            do i--;
            while(i != 0);
        }

}
