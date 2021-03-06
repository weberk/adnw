/*********************************************************************************
 * Title: PS/2 Library
 * Author: Akshay Srinivasan<akshaysrinivasan@nitk.ac.in>
 * Date: 22 June 2009
 * Software: AVR-GCC 4.3.2

 *-------------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <akshaysrinivasan@gmail.com> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Akshay Srinivasan
 *-------------------------------------------------------------------------------------

 DESCRIPTION
    This library provides an abstraction layer for the PS/2 protocol. This library
    provides functions for receiving and sending bytes via PS/2. This library can
    be used to read and write data in PS/2 devices, although interpreting the data
    is left for you to do.

    For more information goto,
    http://computer-engineering.org/ps2protocol/
**********************************************************************************/

#include <util/delay.h>

#include "Keyboard.h"
#include "ps2mouse.h"
#include "trackpoint.h"


volatile uint8_t     scrollcnt;
volatile uint32_t    mouse_timer; /// toggle mouse mode for a specified time
volatile uint16_t    accel; /// toggle mouse mode for a specified time

// only used here
void    serout(uint8_t bit);
uint8_t serin (void);


void data(uint8_t x)
{
    DDDR |= (1 << DBIT);
    if(x==0)
        DPORT &= ~(1 << DBIT);
    else if(x==1)
        DPORT |= (1 << DBIT);
    return;
}

void clk(uint8_t x)
{
    CDDR |= (1 << CBIT);
    if(x==0)
        CPORT &= ~(1 << CBIT);
    else if(x==1)
        CPORT |= (1 << CBIT);
    return;
}



#define CNT 500
void serout(uint8_t bit)
{
    uint8_t cnt;
    cnt=0;
    while(CLK && cnt++ < CNT) {
        __asm__("nop");
    }
    data(bit);
    cnt = 0;
    while(!CLK && cnt++ < CNT) {
        __asm__("nop");
    }
}

uint8_t serin()
{
    uint8_t state;
    uint8_t cnt;
    cnt=0;
    while(CLK && cnt++ < CNT) {
        __asm__("nop");
    }
    state = DATA;
    cnt = 0;
    while(!CLK && cnt++ < CNT) {
        __asm__("nop");
    }
    return state;
}

uint8_t oparity(uint8_t byte)
{
    uint8_t par=1;
    par ^= ((byte & (1 << 0)) >> 0);
    par ^= ((byte & (1 << 1)) >> 1);
    par ^= ((byte & (1 << 2)) >> 2);
    par ^= ((byte & (1 << 3)) >> 3);
    par ^= ((byte & (1 << 4)) >> 4);
    par ^= ((byte & (1 << 5)) >> 5);
    par ^= ((byte & (1 << 6)) >> 6);
    par ^= ((byte & (1 << 7)) >> 7);
    return par;
}



bool send_packet(uint8_t byte)
{
    /// @todo Error checking in PS/2 code
    uint8_t errcnt=0;

    do {
        uint8_t parity = oparity(byte);
        clk(0);
        _delay_us(DELAY);
        data(0); //Start
        clk(1);
        CDDR &= ~(1 << CBIT); // Release clock
        CPORT |= (1 << CBIT); //Set the pull up on Clock

        /////////////
        serout((byte & (1 << 0)) >> 0);
        serout((byte & (1 << 1)) >> 1);
        serout((byte & (1 << 2)) >> 2);
        serout((byte & (1 << 3)) >> 3);
        serout((byte & (1 << 4)) >> 4);
        serout((byte & (1 << 5)) >> 5);
        serout((byte & (1 << 6)) >> 6);
        serout((byte & (1 << 7)) >> 7);
        serout(parity);

        serout(1); //Stop

        DDDR &= ~(1 << DBIT); //Release the Data line
        DPORT |= (1 << DBIT); //Set the pull up on Data

        //if(serin() != PS2_ACK )
        //    send_packet(byte); // Try again if PS2_ACK has not been received
        errcnt++;
    } while (serin() != 0 && errcnt < 5 );

    if(errcnt >= 5)
        return false;
    return true;
}

uint8_t read_packet(void)
{
    uint8_t byte=0,par;
    serin(); //Start
    byte |= (serin() << 0);
    byte |= (serin() << 1);
    byte |= (serin() << 2);
    byte |= (serin() << 3);
    byte |= (serin() << 4);
    byte |= (serin() << 5);
    byte |= (serin() << 6);
    byte |= (serin() << 7);
    par = serin(); //Parity
    serin(); //Stop

    if(par != oparity(byte))
        send_packet(0xfe); //Resend

    return byte;
}

bool ps2_send_expect(uint8_t send, uint8_t expect)
{
    if( ! send_packet(send) ) {
        printf("\nPS/2: send %x failed, expect %x", send, expect);
        return false;
    }
    uint8_t read = read_packet();
    if(read != expect) {
        printf("\nPS/2: send %x, read %x != %x", send, read, expect);
        return false;
    }
    return true;
}


bool ps2_init_mouse(void)
{
    g_mouse_enabled = 0;
    scrollcnt = 0;

    uint8_t d[2];

    tp_reset();

    if ( ! ps2_send_expect(0xff, PS2_ACK) )
        return false;

    d[0]=read_packet(); //Bat
    d[1]=read_packet(); //dev ID

    //Enable Data reporting
    if ( ! ps2_send_expect(0xf4, PS2_ACK) )
        return false;

    //send_packet(0xe8); //Set Resolution
    //read_packet(); //Ack
    //send_packet(0x01); //8counts/mm
    //read_packet(); //Ack
    ////
    //send_packet(0xf3); //SetSample rate
    //read_packet(); //Ack
    //send_packet(0x64); //200 smaples a second

    //Set remote mode
    if( ! ps2_send_expect(0xf0, PS2_ACK) )
        return false;

    printf("\nTP init: Bat:%02x Id:%02x",d[0],d[1]);

    tp_init();

    /// @todo Set only on successful init
    g_mouse_enabled = 1;

    return true;
}

/*
 *
 */
void ps2_read_mouse(int *dx, int *dy, uint8_t *BTNS )
{

    uint8_t ack;
    uint8_t LMB,MMB,RMB;
    *BTNS=0;
    int mouseinf;
    {
        send_packet(0xeb);
        ack=read_packet(); //Ack
        if(ack==0xfa) {
            mouseinf=read_packet();
            LMB=0;
            MMB=0;
            RMB=0;

            if(mouseinf & 0x01)  //0x09
                LMB=1;         // Get leftbutton status
            if(mouseinf & 0x02)
                RMB=1;        // Get rightbutton status
            if(mouseinf & 0x04)
                MMB=1;       // Get middlebutton status


            /*          // emulate 3 buttons
                        if( RMB & LMB ) {
                            MMB=1;
                            RMB=LMB=0;
                        }
            */
            // *BTNS = (LMB<<2) | (MMB<<1) | (RMB << 0);
            // buttons (left to right) are  1 2 3
            // hexcode as expected is       1 4 2
            // swap lower two buttons on "blue cube"
            *BTNS = (LMB<<0) | (MMB<<1) | (RMB << 2);


            *dx= read_packet();
            *dy= read_packet();
            // raw *dx is of 0xXX
            int x = *dx;
            //int y = *dy;
            int xtest = *dx;

            if(mouseinf&0x10)
                *dx=-(256-*dx);

            if(mouseinf&0x20)
                *dy=-(256-*dy);

            return;

            if(mouseinf&0x10) {
                xtest=-(256-*dx);
                *dx-=0x100; // Add sign bit to dx

            }
            if(mouseinf&0x20)
                *dy-=0x100; // Add sign bit to dy

            if( x!=0 ) {
                //printf("\n%4x %4x | %4x %4x", x,*dx,y,*dy);
                printf("\ninf=0x%04x x:%2d dx:0x%04x xtest: %d dxrevert: ", mouseinf, x,*dx, xtest);
                if(*dx&0xFF00)
                    printf("-%2d" , 256-(*dx+0x100));
                else
                    printf("+%2d" , *dx);
            }

        }
    }
}


uint8_t getMouseReport(USB_MouseReport_Data_t *MouseReport)
{
    if(!g_mouse_enabled)
        return 0;

    int16_t dx=0, dy=0;
    uint8_t ps2_buttons=0;
    float factor;

#ifdef PS2MOUSE
    ps2_read_mouse(&dx, &dy, &ps2_buttons);
#endif

    if( (g_mouse_keys & 0x0F) || (ps2_buttons & 0x07) || (dx+dy) > 0 /* Test for spurious movements */ ) {
        if(g_mouse_keys_enabled==0) {
            g_mouse_keys_enabled=1;
            accel=0;
        }

        mouse_timer=idle_count;
        if(accel<ACC_RAMPTIME)
            accel++;

        // reset mouse mode after inactivity: idle_count is incremented 61 times per second
    } else if(idle_count-mouse_timer > 1/*seconds*/ *61 ) {
        g_mouse_keys_enabled=0;
        accel=0;
        scrollcnt=0;
    }

    if(g_mouse_keys_enabled || ps2_buttons) {
        factor= 1 + accel * (ACC_MAX-1) / ACC_RAMPTIME;

#ifdef MOUSE_HAS_SCROLL_WHEELS
        MouseReport->V=0;
        MouseReport->H=0;
        MouseReport->Button=0;

        // keyboard mouse buttons only in mousemode
        if( (ps2_buttons & 0x05)==0x05 || (g_mouse_keys & 0x08)) {
            int8_t sx=0, sy=0;

            if( dx!=0 ) {
                if(dx&0xFF00)
                    sx= -(256-(dx+0x100));
                else
                    sx=dx;
            }
            if( dy!=0 ) {
                if(dy&0xFF00)
                    sy= -(256-(dy+0x100));
                else
                    sy=dy;
            }

            scrollcnt = scrollcnt+abs(sy)+abs(sx);

            // limit 10 and emiting as is way to fast in windows.
            if(scrollcnt>10) {
                scrollcnt=0;
                MouseReport->X=0;
                MouseReport->Y=0;
                // only move by 1 ?!
                MouseReport->H = -sx*(factor-1)/3;
                MouseReport->V = -sy*(factor-1)/3;
            }
        } else
#endif
        {

            MouseReport->Y = dy * factor;
            MouseReport->X = -dx * factor;

            // do not emit the scroll button
            MouseReport->Button = g_mouse_keys & ~(0x08);
            MouseReport->Button |= ps2_buttons;    // PS/2 buttons if set
        }
        g_mouse_keys=0;
        ps2_buttons=0;

        return sizeof(USB_MouseReport_Data_t);

    }
    return 0;
}
