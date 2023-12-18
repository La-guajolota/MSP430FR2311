/*
    Se crean un patron pseudorandom de secuenica de leds
 */

#include <msp430.h> 
#include <stdint.h>

//Pulsos por contar maximos del timer
#define PULSOS 65535 //16bits maximo CNTL_0

//Pines de leds de la tarjeta
#define LEDr BIT0 //P1.0
#define LEDv BIT0 //P2.0

//Parametros para emular un shiftregister
#define REGLENGTH 4 // <= 15 De lo contrai modificar lastmask y nextmask
#define LASTMASK  ((uint16_t ) (BIT0 << REGLENGTH))
#define NEXTMASK  ((uint16_t ) (BIT0 << (REGLENGTH -1)))


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode

    TB0CCR0 = PULSOS;//Cuenta hasta X pulsos
    TB0CTL = MC_1|ID_3|TBSSEL_2|TBCLR|CNTL_0;// "Up to CCR0" mode , divide clock by 8, clock from SMCLK , clear timer

    //Configuramos los pines OUTPUTS
    P1DIR |= LEDr;
    P1OUT &= ~LEDr;
    P2DIR |= LEDv;
    P2OUT &= ~LEDv;

    //Colocar la semilla del patron
    uint16_t pattern = 3; // next pattern to be displayed No debe inicializarse en o

    for(;;){

        while((TBCTL & TBIFG) == 0){
        //Bandera activa de overflow del timer??? CICLADO CANDADO
        }

        TBCTL &= ~TBIFG;//Limpiamos la bandera de overflow

        //Actualizamos el patron visualizandos en los leds LSB
        switch (pattern & 0x03) {//Pseudo decodificador binario
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

        pattern <<= 1;//Recorremos el registro

        //XOR en los ultimos en los ultimos dos MSb
        switch (pattern & (LASTMASK|NEXTMASK)) {
            case LASTMASK:
            case NEXTMASK:
                pattern |= BIT0; // XOR gives 1
                break ;
            default :
                pattern &= ~BIT0; // XOR gives 0
                break ;
        }

    }
}
