/*********************************************
* vim:sw=8:ts=8:si:et
* To use the above modeline in vim you must have "set modeline" in your .vimrc
* Author: Guido Socher, Copyright: GPL V2
* This program is to test basic functionallity by getting an LED to blink.
* See http://linuxfocus.org/English/November2004/  for details.
* Chip type           : ATMEGA88
*********************************************/
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#define SCK PB5
#define MISO PB4
#define MOSI PB3
#define SS PB2


void delay_ms(unsigned int ms)
/* delay for a minimum of <ms> */
{
        // we use a calibrated macro. This is more
        // accurate and not so much compiler dependent
        // as self made code.
        while(ms){
		_delay_ms(0.998);
                ms--;
        }
}

int main(void)
{
        /* INITIALIZE */
        // Be very careful with low frequencies (less than 1MHz). Modern and fast programmers 
        // can not supply such low programming clocks. It can lock you out!
        //
        // set the clock prescaler. First write CLKPCE to enable setting of clock the
        // next four instructions.
	CLKPR=(1<<CLKPCE);
//	CLKPR=0; // 16 MHZ
	CLKPR=(1<<CLKPS0); // 8MHz
//	CLKPR=(1<<CLKPS1); // 4MHz
//	CLKPR=((1<<CLKPS0)|(1<<CLKPS1)); // 2MHz
//	CLKPR=(1<<CLKPS2); // 1MHZ
//	CLKPR=((1<<CLKPS0)|(1<<CLKPS2)); // 0.5MHz

        /* enable PB1 as output */

	SPCR = (1<<SPE)|(1<<MSTR);
        SPSR |= (1<<SPI2X);

	DDRB = (1<<SS)|(1<<SCK)|(1<<MOSI);
	PORTB |= (1<<SS); //passive


        while (1) {
/*
                    // led on, pin=0
                    PORTB &= ~(1<<LED);
                    delay_ms(500);
                    // set output to 5V, LED off
                    PORTB|= (1<<LED);
                    delay_ms(500);
*/

			PORTB &= ~(1<<SS); //active

			SPDR = 0xAA;
			while(!(SPSR&(1<<SPIF)));

			PORTB |= (1<<SS);

			delay_ms(1000);
        }
        return(0);
}


