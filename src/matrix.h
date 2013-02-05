/*
    Copyright 2010-2012 Stefan Fröbe, <frobiac /at/ gmail [d0t] com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef MATRIX_H
#define  MATRIX_H

#include <avr/io.h>


void unselect_rows(void);
void activate(uint8_t row);

// this must be called once before matrix_scan.
static inline uint16_t read_col(void)
{   // Teensy 2.0                  // Teensy++ 2.0
#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)
    // 12 cols ordered left to right: PIND:0123457 and PINF:34567
    uint16_t resLow=PIND & 0b10111111;
    uint16_t resHigh=PINF;
    uint16_t resHigh1=(resHigh & 0b11110000)<<4;
    uint16_t resHigh0=(resHigh & 0b00001000)<<3;
//    uint16_t resHigh=(PINF & 0b11110000)<<4;
    uint16_t result = (resHigh1 | resHigh0 | resLow);
    // lets debug
//    printf ("\n E: ");
//    for(int i=(sizeof(result) * 8) - 1; i >= 0;i--)
//    {
////         printf("%d",(resHigh0 & (0x01 << 6)) > 0);
//     printf("%d",(result & (0x01 << i)) > 0);
//    }
//    printf (":E\n");
    return result;
#else
#error "weder Teensy 2 noch 2++ eingestellt"
    return 0;
#endif
}

void unselect_rows(void)
{   // Teensy 2.0                  // Teensy++ 2.0
#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)
    // B:76543210 in use
    // set all row pins as inputs
    DDRB  &= 0b00000000;
    // drive all row pins low
    PORTB &= 0b00000000;
#endif
}

void activate(uint8_t row)
{   // Teensy 2.0                  // Teensy++ 2.0
#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)
    unselect_rows();
    // B:76543210 in use
    // set current row pin as output
    if (row<8) {
        DDRB |= (1<<row);
    }
    return;
#endif
}

static inline void init_cols(void)
{   // Teensy 2.0                  // Teensy++ 2.0
#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)
    // 12 cols ordered left to right: PIND:0123457 and PINF:34567
    // set all column pins as inputs
    DDRD  &= 0b00000000;
    DDRF  &= 0b00000111;
    /* Enable pull-up resistors on inputs */
    PORTD |= (0b11111111);
    PORTF |= (0b11111000);
    return;
#endif
}
#endif
