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

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "trackpoint.h"
#include "Keyboard.h"
//#include "ps2mouse.h"

#define ACC_RAMPTIME 400 // acc incrementation time till maximum
#define ACC_MAX      2.5 // maximum accelleration factor reachable

volatile uint8_t     scrollcnt;
volatile uint32_t    mouse_timer; /// toggle mouse mode for a specified time
volatile uint16_t    accel; /// toggle mouse mode for a specified time

void tp_reset()
{
    RDDR |= (1 << RBIT);
    RPORT |= (1 << RBIT);
    _delay_us(DELAY);
    RPORT &= ~(1 << RBIT);
    return;

    while(CLK) {
        __asm__("nop");
    }
    while(!CLK) {
        __asm__("nop");
    }
    while(CLK) {
        __asm__("nop");
    }
    while(!CLK) {
        __asm__("nop");
    }
    RPORT &= ~(1 << RBIT);
}



void tp_ram_toggle(uint8_t addr, uint8_t val){
    uint8_t tmp;

    tp_send_read_ack(0xe2);
    tp_send_read_ack(0x2c);
    tmp=read_packet();
    if( (tmp & val) != 0x00) {
        printf("\nAlready set");
    }

    tp_send_read_ack(0xe2);
    tp_send_read_ack(0x47);
    tp_send_read_ack(addr);
    tp_send_read_ack(val);
}

uint8_t tp_ram_read(uint8_t addr){
    tp_send_read_ack(0xe2);
    tp_send_read_ack(0x80);
    tp_send_read_ack(addr);
    return( read_packet() );
}

void tp_ram_write(uint8_t addr, uint8_t val){
    tp_send_read_ack(0xe2);
    tp_send_read_ack(0x81);
    tp_send_read_ack(addr);
    tp_send_read_ack(val);
}

// TP config register: See p33 of YKT3Eext.pdf
enum { TP_PTS=0, TP_RES, TP_BTN2, TP_FLIPX, TP_FLIPY, TP_FLIPZ, TP_SWAPXY, TP_FTRANS };

bool tp_send_read_ack(uint8_t val)
{
    if( ! send_packet(val) ) {
        printf("\nError: not send");
        return false;
    }
    if(read_packet() != 0xfa) {
        printf("\nError: not ack");
        return false;
    }
    return true;
}

uint8_t tp_read_config(){
    printf("\nTP Config= ");
    tp_send_read_ack(0xe2);
    tp_send_read_ack(0x2c);
    uint8_t config = read_packet();
    printf("%02x ", config);
    return config;
}

void tp_id(void) {
    g_trackpoint=0;

    //uint8_t tmp;
    // read secondary ID
/*
    if( tp_send_read_ack(0xe1) )
        printf("\n2nd  ID: %02x%02x \nExt. ID: ", read_packet(),read_packet());

    // read extended ID
    if( tp_send_read_ack(0xd0) ){
        // better scan for ")" == 29 // 41 ?
        for(uint8_t i=0; i < 31; ++i) {
            tmp=read_packet();
            printf("%c",tmp);
            if( tmp == (uint8_t)')')
                continue;
        }
    }
*/
    /* smaller TP:
     * 2nd  ID:  010e
     * Ext. ID: M 19990623($IBM3780)
     */

    // read config byte at 2C: E2 2C or E2 80 2C
    /* bit  0   1   2    3    4    5    6    7
            Pts res 2clk invX invY invZ ExXY HardTransp
      */
    tp_read_config();
    tp_ram_toggle(0x2c, (1<<TP_PTS) );
    tp_read_config();

    /* RAM locations:
     * - Read with E2 80 ADDR
     * - Read with E2 81 ADDR VAL
     *
     * 41,42,43 pts btn mask
     * 5C PtS thres
     */

    // setup PressToSroll by enabling PTS, setting button masks and increasing threshold
    printf("\nPTS btn masks: %02x %02x %02x ", tp_ram_read(0x41), tp_ram_read(0x42), tp_ram_read(0x43) );
    tp_ram_write(0x41, 0xff);
    tp_ram_write(0x42, 0xff);
    printf("\nPTS btn masks: %02x %02x %02x ", tp_ram_read(0x41), tp_ram_read(0x42), tp_ram_read(0x43) );
    printf("\nPTS thres: %02x", tp_ram_read(0x5c));
    tp_ram_write(0x5c, 0x0A); // 08 is default, 10 too hard
    printf("\nPTS thres: %02x", tp_ram_read(0x5c));

    /// @todo Set only on successful init
    g_trackpoint = 1;


}