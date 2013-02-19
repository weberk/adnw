/*
    Copyright 2010-2013 Stefan Fröbe, <frobiac /at/ gmail [d0t] com>

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

#ifndef _HID_USAGE_H
#define _HID_USAGE_H 1

#include <stdint.h>

// see also ../LUFA/LUFA/Drivers/USB/Class/Common/HIDClassCommon.h
// or http://www.freebsddiary.org/APC/usb_hid_usages


/*
   The largest HID usage code is AC_Distribute_Vertically from the Consumer
   Control usage page.  Its id is 0x29c, which requires 10 bits.  The largest
   usage page used by a keyboard, on the other hand, is 0x0c, which requires
   only 4 bits.  So we pack the usage id in the lower 10 bits of a 16 bit int,
   and the usage page in the upper 6 bits.
*/

#define MAKE_USAGE(page,id) (((page)<<10)|(id))
#define USAGE_ID(usage)     (usage&~(0xffff<<10))
#define USAGE_PAGE(usage)   (usage>>10)

typedef enum {
    page_keyboard = 0x07,
    page_system = 0x01,
    page_consumer = 0x0c
} usage_page;

#define HID_NO_KEY          MAKE_USAGE(page_keyboard, 0)
#define HID_ERROR_ROLLOVER  MAKE_USAGE(page_keyboard, 1)
#define HID_POST_FAIL       MAKE_USAGE(page_keyboard, 2)
#define HID_ERROR_UNDEFINED MAKE_USAGE(page_keyboard, 3)
#define HID_A               MAKE_USAGE(page_keyboard, 4)
#define HID_B               MAKE_USAGE(page_keyboard, 5)
#define HID_C               MAKE_USAGE(page_keyboard, 6)
#define HID_D               MAKE_USAGE(page_keyboard, 7)
#define HID_E               MAKE_USAGE(page_keyboard, 8)
#define HID_F               MAKE_USAGE(page_keyboard, 9)
#define HID_G               MAKE_USAGE(page_keyboard, 10)
#define HID_H               MAKE_USAGE(page_keyboard, 11)
#define HID_I               MAKE_USAGE(page_keyboard, 12)
#define HID_J               MAKE_USAGE(page_keyboard, 13)
#define HID_K               MAKE_USAGE(page_keyboard, 14)
#define HID_L               MAKE_USAGE(page_keyboard, 15)
#define HID_M               MAKE_USAGE(page_keyboard, 16)
#define HID_N               MAKE_USAGE(page_keyboard, 17)
#define HID_O               MAKE_USAGE(page_keyboard, 18)
#define HID_P               MAKE_USAGE(page_keyboard, 19)
#define HID_Q               MAKE_USAGE(page_keyboard, 20)
#define HID_R               MAKE_USAGE(page_keyboard, 21)
#define HID_S               MAKE_USAGE(page_keyboard, 22)
#define HID_T               MAKE_USAGE(page_keyboard, 23)
#define HID_U               MAKE_USAGE(page_keyboard, 24)
#define HID_V               MAKE_USAGE(page_keyboard, 25)
#define HID_W               MAKE_USAGE(page_keyboard, 26)
#define HID_X               MAKE_USAGE(page_keyboard, 27)
#define HID_Y               MAKE_USAGE(page_keyboard, 28)
#define HID_Z               MAKE_USAGE(page_keyboard, 29)
#define HID_1               MAKE_USAGE(page_keyboard, 30)
#define HID_2               MAKE_USAGE(page_keyboard, 31)
#define HID_3               MAKE_USAGE(page_keyboard, 32)
#define HID_4               MAKE_USAGE(page_keyboard, 33)
#define HID_5               MAKE_USAGE(page_keyboard, 34)
#define HID_6               MAKE_USAGE(page_keyboard, 35)
#define HID_7               MAKE_USAGE(page_keyboard, 36)
#define HID_8               MAKE_USAGE(page_keyboard, 37)
#define HID_9               MAKE_USAGE(page_keyboard, 38)
#define HID_0               MAKE_USAGE(page_keyboard, 39)
#define HID_ENTER           MAKE_USAGE(page_keyboard, 40)
#define HID_ESC             MAKE_USAGE(page_keyboard, 41)
#define HID_BACKSPACE       MAKE_USAGE(page_keyboard, 42)
#define HID_TAB             MAKE_USAGE(page_keyboard, 43)
#define HID_SPACE           MAKE_USAGE(page_keyboard, 44)
#define HID_MINUS           MAKE_USAGE(page_keyboard, 45)
#define HID_EQUAL           MAKE_USAGE(page_keyboard, 46)
#define HID_L_BRACKET       MAKE_USAGE(page_keyboard, 47)
#define HID_R_BRACKET       MAKE_USAGE(page_keyboard, 48)
#define HID_BSLASH          MAKE_USAGE(page_keyboard, 49)
#define HID_NON_US_1        MAKE_USAGE(page_keyboard, 50)
#define HID_SEMICOLON       MAKE_USAGE(page_keyboard, 51)
#define HID_QUOTE           MAKE_USAGE(page_keyboard, 52)
#define HID_GRAVE           MAKE_USAGE(page_keyboard, 53)
#define HID_COMMA           MAKE_USAGE(page_keyboard, 54)
#define HID_PERIOD          MAKE_USAGE(page_keyboard, 55)
#define HID_SLASH           MAKE_USAGE(page_keyboard, 56)
#define HID_CAPS_LOCK       MAKE_USAGE(page_keyboard, 57)
#define HID_F1              MAKE_USAGE(page_keyboard, 58)
#define HID_F2              MAKE_USAGE(page_keyboard, 59)
#define HID_F3              MAKE_USAGE(page_keyboard, 60)
#define HID_F4              MAKE_USAGE(page_keyboard, 61)
#define HID_F5              MAKE_USAGE(page_keyboard, 62)
#define HID_F6              MAKE_USAGE(page_keyboard, 63)
#define HID_F7              MAKE_USAGE(page_keyboard, 64)
#define HID_F8              MAKE_USAGE(page_keyboard, 65)
#define HID_F9              MAKE_USAGE(page_keyboard, 66)
#define HID_F10             MAKE_USAGE(page_keyboard, 67)
#define HID_F11             MAKE_USAGE(page_keyboard, 68)
#define HID_F12             MAKE_USAGE(page_keyboard, 69)
#define HID_PRINTSCREEN     MAKE_USAGE(page_keyboard, 70)
#define HID_SCROLL_LOCK     MAKE_USAGE(page_keyboard, 71)
#define HID_PAUSE           MAKE_USAGE(page_keyboard, 72)
#define HID_INSERT          MAKE_USAGE(page_keyboard, 73)
#define HID_HOME            MAKE_USAGE(page_keyboard, 74)
#define HID_PAGE_UP         MAKE_USAGE(page_keyboard, 75)
#define HID_DELETE          MAKE_USAGE(page_keyboard, 76)
#define HID_END             MAKE_USAGE(page_keyboard, 77)
#define HID_PAGE_DOWN       MAKE_USAGE(page_keyboard, 78)
#define HID_RIGHT           MAKE_USAGE(page_keyboard, 79)
#define HID_LEFT            MAKE_USAGE(page_keyboard, 80)
#define HID_DOWN            MAKE_USAGE(page_keyboard, 81)
#define HID_UP              MAKE_USAGE(page_keyboard, 82)
#define HID_NUM_LOCK        MAKE_USAGE(page_keyboard, 83)
#define HID_KEYPAD_SLASH    MAKE_USAGE(page_keyboard, 84)
#define HID_KEYPAD_ASTERIX  MAKE_USAGE(page_keyboard, 85)
#define HID_KEYPAD_MINUS    MAKE_USAGE(page_keyboard, 86)
#define HID_KEYPAD_PLUS     MAKE_USAGE(page_keyboard, 87)
#define HID_KEYPAD_ENTER    MAKE_USAGE(page_keyboard, 88)
#define HID_KEYPAD_1        MAKE_USAGE(page_keyboard, 89)
#define HID_KEYPAD_2        MAKE_USAGE(page_keyboard, 90)
#define HID_KEYPAD_3        MAKE_USAGE(page_keyboard, 91)
#define HID_KEYPAD_4        MAKE_USAGE(page_keyboard, 92)
#define HID_KEYPAD_5        MAKE_USAGE(page_keyboard, 93)
#define HID_KEYPAD_6        MAKE_USAGE(page_keyboard, 94)
#define HID_KEYPAD_7        MAKE_USAGE(page_keyboard, 95)
#define HID_KEYPAD_8        MAKE_USAGE(page_keyboard, 96)
#define HID_KEYPAD_9        MAKE_USAGE(page_keyboard, 97)
#define HID_KEYPAD_0        MAKE_USAGE(page_keyboard, 98)
#define HID_KEYPAD_PERIOD   MAKE_USAGE(page_keyboard, 99)
#define HID_NON_US_2        MAKE_USAGE(page_keyboard, 100)
#define HID_APPLICATION     MAKE_USAGE(page_keyboard, 101)
#define HID_MAC_POWER       MAKE_USAGE(page_keyboard, 102)
#define HID_KEYPAD_EQUAL    MAKE_USAGE(page_keyboard, 103)
#define HID_F13             MAKE_USAGE(page_keyboard, 104)
#define HID_F14             MAKE_USAGE(page_keyboard, 105)
#define HID_F15             MAKE_USAGE(page_keyboard, 106)
// ... till F24             ...
#define HID_F24             MAKE_USAGE(page_keyboard, 115)

#define HID_L_CONTROL       MAKE_USAGE(page_keyboard, 0xE0)
#define HID_L_SHIFT         MAKE_USAGE(page_keyboard, 0xE1)
#define HID_L_ALT           MAKE_USAGE(page_keyboard, 0xE2)
#define HID_L_GUI           MAKE_USAGE(page_keyboard, 0xE3)
#define HID_R_CONTROL       MAKE_USAGE(page_keyboard, 0xE4)
#define HID_R_SHIFT         MAKE_USAGE(page_keyboard, 0xE5)
#define HID_R_ALT           MAKE_USAGE(page_keyboard, 0xE6)
#define HID_R_GUI           MAKE_USAGE(page_keyboard, 0xE7)

#define HID_SYSRQ           MAKE_USAGE(page_keyboard, 0x9A)

// Consumer Page(0x0C)
// following are supported by Windows: http://msdn.microsoft.com/en-us/windows/hardware/gg463372.aspx

#define HID_AUDIO_MUTE              MAKE_USAGE(page_consumer, 0x00E2)
#define HID_AUDIO_VOL_UP            MAKE_USAGE(page_consumer, 0x00E9)
#define HID_AUDIO_VOL_DOWN          MAKE_USAGE(page_consumer, 0x00EA)
#define HID_TRANSPORT_NEXT_TRACK    MAKE_USAGE(page_consumer, 0x00B5)
#define HID_TRANSPORT_PREV_TRACK    MAKE_USAGE(page_consumer, 0x00B6)
#define HID_TRANSPORT_STOP          MAKE_USAGE(page_consumer, 0x00B7)
#define HID_TRANSPORT_PLAY_PAUSE    MAKE_USAGE(page_consumer, 0x00CD)
#define HID_Bass_Up                 MAKE_USAGE(page_consumer, 0x0152)
#define HID_Bass_Down               MAKE_USAGE(page_consumer, 0x0153)
#define HID_Treble_Up               MAKE_USAGE(page_consumer, 0x0154)
#define HID_Treble_Down             MAKE_USAGE(page_consumer, 0x0155)
#define HID_AL_CC_CONFIG            MAKE_USAGE(page_consumer, 0x0183) // Media Select
#define HID_AL_EMAIL                MAKE_USAGE(page_consumer, 0x018A)
#define HID_AL_CALCULATOR           MAKE_USAGE(page_consumer, 0x0192)
#define HID_AL_LOCAL_BROWSER        MAKE_USAGE(page_consumer, 0x0194) // My Computer
#define HID_AC_SEARCH               MAKE_USAGE(page_consumer, 0x0221) // WWW Search
#define HID_AC_HOME                 MAKE_USAGE(page_consumer, 0x0223) // WWW Home
#define HID_AC_BACK                 MAKE_USAGE(page_consumer, 0x0224) // WWW Back
#define HID_AC_FORWARD              MAKE_USAGE(page_consumer, 0x0225) // WWW Forward
#define HID_AC_STOP                 MAKE_USAGE(page_consumer, 0x0226) // WWW Stop
#define HID_AC_REFRESH              MAKE_USAGE(page_consumer, 0x0227) // WWW Refresh
#define HID_AC_BOOKMARKS            MAKE_USAGE(page_consumer, 0x022A) // WWW Favorites
// supplement for Bluegiga iWRAP HID(not supported by Windows?)
#define HID_AL_LOCK                 MAKE_USAGE(page_consumer, 0x019E)
#define HID_TRANSPORT_RECORD        MAKE_USAGE(page_consumer, 0x00B2)
#define HID_TRANSPORT_REWIND        MAKE_USAGE(page_consumer, 0x00B4)
#define HID_TRANSPORT_EJECT         MAKE_USAGE(page_consumer, 0x00B8)
#define HID_AC_MINIMIZE             MAKE_USAGE(page_consumer, 0x0206)

// Generic Desktop Page(0x01)
#define HID_SYSTEM_POWER_DOWN       MAKE_USAGE(page_system, 0x0081)
#define HID_SYSTEM_SLEEP            MAKE_USAGE(page_system, 0x0082)
#define HID_SYSTEM_WAKE_UP          MAKE_USAGE(page_system, 0x0083)


/* mouse buttons hid codes */
#define HID_MOUSEBTN_1 (1<<0)
#define HID_MOUSEBTN_2 (1<<1)
#define HID_MOUSEBTN_3 (1<<2)
#define HID_MOUSEBTN_4 (1<<3)
#define HID_MOUSEBTN_5 (1<<4)


typedef enum {
//##########################################
    /* Mousekey */
    MS_BEGIN=0xEF,
    MS_U, //  = 0xF0,
    MS_D,
    MS_L,
    MS_R,
    MS_BTN1,
    MS_BTN2,
    MS_BTN3,
    MS_BTN4,
    MS_BTN5,         /* 0xF8 */
    /* Mousekey wheel */
    MS_W_U,
    MS_W_D,
    MS_W_L,
    MS_W_R,     /* 0xFC */
    /* Mousekey accel */
    MS_ACC0,
    MS_ACC1,
    MS_ACC2,        /* 0xFF */
//##########################################

    // modifier bits to use, actual HID-modifier is (1<<(modbit-MOD_CTRL))
    MOD_L_CTRL=0xE0, // E0 is rather arbitrarily taken to be same as HID
    MOD_L_SHIFT,
    MOD_L_ALT,
    MOD_L_GUI,
    MOD_R_CTRL,
    MOD_R_SHIFT,
    MOD_R_ALT,
    MOD_R_GUI,
    MOD_END,

    // layer modifiers
    MOD_LAYER_0=0xF2,
    MOD_LAYER_1,
    MOD_LAYER_2,
    MOD_LAYER_3,
    MOD_MOUSEKEY,
    MOD_COMPOSE,
    MOD_LAYER_LAST
} modbits;

/// @todo : cleanup modifiers everywhere
#define ALTGR (1<<6)

typedef enum
{
    NONE  = 0,
    L_CTL = (1<<0),
    L_SHF = (1<<1),
    L_ALT = (1<<2),
    L_GUI = (1<<3),
    R_CTL = (1<<4),
    R_SHF = (1<<5),
    R_ALT = (1<<6), // alias ALTGR
    R_GUI = (1<<7),
    A_CTL = (1<<8),
    A_SHF = (1<<9),
    A_ALT = (1<<10),
    A_GUI = (1<<11),
} Modifier;

// *************************************************************
// mapping of characters and HID codes
// differences between qwert_Y and qwert_Z are separate at the bottom
// **************************************************************

/*
QWERTY US                                QWERTZ DE
---------                                ---------
                                AltGr      ¹ ² ³ ¼ ½   { [ ] } \ ¸
~ ! @ # $ % ^ & * ( ) - +       shift    ° ! " § $ % & / ( ) = ? `
` 1 2 3 4 5 6 7 8 9 0 _ =       ROW1     ^ 1 2 3 4 5 6 7 8 9 0 ß ´
-----                                    -----
                                           @   €
  Q W E R T Y U I O P { } |     shift      Q W E R T Z U I O P Ü *
            y         [ ] \     ROW2                 z         ü +
-----                                    -----

  A S D F G H J K L : "         shift    A S D F G H J K L Ö Ä '
                    ; '         ROW3                         ö ä #
-----                                    -----
                                         |             µ
  Z X C V B N M < > ?           shift    > Y X C V B N M ; : _
  z             , . /           ROW4     < y             , . -
-----                                    -----

-> Different keys in QWERTZ DE :
Normal : ^                 ß ´     z ü + ö ä # < y , . -
Shifted: ^ 2 3 4 6 7 8 9 0 ß ´     z ü + ö ä # < y , . -
AltGr  :           7 8 9 0 ß   q e     +       <

*/



typedef enum
{
    _ik_no = 0     ,     //{ 0,     0,      ' ' } // No key defined
    _ik_1          ,     //{ HID_1, 0,      '1' }
    _ik_EXCLAM     ,     //{ HID_1, L_SHF , '!' }
    _ik_EXCLAMI    ,     //{ HID_1, ALTGR , 'ç' }
    _ik_2          ,     //{ HID_2, 0,      '2' }
    _ik_3          ,     //{ HID_3, 0,      '3' }
    _ik_4          ,     //{ HID_4, 0,      '4' }
    _ik_DOLLAR     ,     //{ HID_4, L_SHF , '$' }
    _ik_5          ,     //{ HID_5, 0,      '5' }
    _ik_PERCENT    ,     //{ HID_5, L_SHF , '%' }
    _ik_6          ,     //{ HID_6, 0,      '6' }
    _ik_7          ,     //{ HID_7, 0,      '7' }
    _ik_8          ,     //{ HID_8, 0,      '8' }
    _ik_9          ,     //{ HID_9, 0,      '9' }
    _ik_0          ,     //{ HID_0, 0,      '0' }
    _ik_q          ,     //{ HID_Q, 0,      'q' }
    _ik_Q          ,     //{ HID_Q, L_SHF , 'Q' }
    _ik_w          ,     //{ HID_W, 0,      'w' }
    _ik_W          ,     //{ HID_W, L_SHF , 'W' }
    _ik_e          ,     //{ HID_E, 0,      'e' }
    _ik_E          ,     //{ HID_E, L_SHF , 'E' }
    _ik_r          ,     //{ HID_R, 0,      'r' }
    _ik_R          ,     //{ HID_R, L_SHF , 'R' }
    _ik_t          ,     //{ HID_T, 0,      't' }
    _ik_T          ,     //{ HID_T, L_SHF , 'T' }
    _ik_u          ,     //{ HID_U, 0,      'u' }
    _ik_U          ,     //{ HID_U, L_SHF , 'U' }
    _ik_i          ,     //{ HID_I, 0,      'i' }
    _ik_I          ,     //{ HID_I, L_SHF , 'I' }
    _ik_o          ,     //{ HID_O, 0,      'o' }
    _ik_O          ,     //{ HID_O, L_SHF , 'O' }
    _ik_p          ,     //{ HID_P, 0,      'p' }
    _ik_P          ,     //{ HID_P, L_SHF , 'P' }
    _ik_a          ,     //{ HID_A, 0,      'a' }
    _ik_A          ,     //{ HID_A, L_SHF , 'A' }
    _ik_s          ,     //{ HID_S, 0,      's' }
    _ik_S          ,     //{ HID_S, L_SHF , 'S' }
    _ik_d          ,     //{ HID_D, 0,      'd' }
    _ik_D          ,     //{ HID_D, L_SHF , 'D' }
    _ik_f          ,     //{ HID_F, 0,      'f' }
    _ik_F          ,     //{ HID_F, L_SHF , 'F' }
    _ik_g          ,     //{ HID_G, 0,      'g' }
    _ik_G          ,     //{ HID_G, L_SHF , 'G' }
    _ik_h          ,     //{ HID_H, 0,      'h' }
    _ik_H          ,     //{ HID_H, L_SHF , 'H' }
    _ik_j          ,     //{ HID_J, 0,      'j' }
    _ik_J          ,     //{ HID_J, L_SHF , 'J' }
    _ik_k          ,     //{ HID_K, 0,      'k' }
    _ik_K          ,     //{ HID_K, L_SHF , 'K' }
    _ik_l          ,     //{ HID_L, 0,      'l' }
    _ik_L          ,     //{ HID_L, L_SHF , 'L' }
    _ik_x          ,     //{ HID_X, 0,      'x' }
    _ik_X          ,     //{ HID_X, L_SHF , 'X' }
    _ik_c          ,     //{ HID_C, 0,      'c' }
    _ik_C          ,     //{ HID_C, L_SHF , 'C' }
    _ik_v          ,     //{ HID_V, 0,      'v' }
    _ik_V          ,     //{ HID_V, L_SHF , 'V' }
    _ik_b          ,     //{ HID_B, 0,      'b' }
    _ik_B          ,     //{ HID_B, L_SHF , 'B' }
    _ik_n          ,     //{ HID_N, 0,      'n' }
    _ik_N          ,     //{ HID_N, L_SHF , 'N' }
    _ik_m          ,     //{ HID_M, 0,      'm' }
    _ik_M          ,     //{ HID_M, L_SHF , 'M' }
    _ik_CAPS       ,     //{ HID_CAPS_LOCK,0     , ' ' }  //  CapsLock
    _ik_APP        ,     //{ HID_APPLICATION, 0  , ' ' }  //  App
    _ik_BSPACE     ,     //{ HID_BACKSPACE,0     , 171 }  //  Backspace
    _ik_TAB        ,     //{ HID_TAB,      0     , 187 }  //  Tab
    _ik_noN_US_1   ,     //{ HID_NON_US_1, 0     , ' ' }  //  non-US-1
    _ik_noN_US_2   ,     //{ HID_NON_US_2, 0     , ' ' }  //  non-US-1
    _ik_ENTER      ,     //{ HID_ENTER,    0     , 182 }  //  Enter
    _ik_COMMA      ,     //{ HID_COMMA,    0     , ',' }
    _ik_PERIOD     ,     //{ HID_PERIOD,   0     , '.' }
    _ik_DOT3       ,     //{ HID_PERIOD,   ALTGR , '.' } // '...'
    _ik_SPACE      ,     //{ HID_SPACE,    0     , ' ' }
    _ik_L_SHIFT    ,     //{ HID_L_SHIFT,    MOD_L_SHIFT , ' ' }  //  LShift
    _ik_R_SHIFT    ,     //{ HID_R_SHIFT,    MOD_R_SHIFT , ' ' }  //  RShift
    _ik_L_CTRL     ,     //{ HID_L_CONTROL,  MOD_L_CTRL  , ' ' }  //  LCtrl
    _ik_R_CTRL     ,     //{ HID_R_CONTROL,  MOD_R_CTRL  , ' ' }  //  RCtrl
    _ik_L_ALT      ,     //{ HID_L_ALT,      MOD_L_ALT   , ' ' }  //  LAlt
    _ik_R_ALT      ,     //{ HID_R_ALT,      MOD_R_ALT   , ' ' }  //  RAlt alias ALTGR alias AltGr
    _ik_ALTGR = _ik_R_ALT,  //                                       //  AltGr identical to CTRL+ left ALT
    _ik_L_GUI      ,     //{ HID_L_GUI,      MOD_L_GUI   , ' ' }  //  LWin
    _ik_R_GUI      ,     //{ HID_R_GUI,      MOD_R_GUI   , ' ' }  //  RWin
    _ik_MOD_0      ,     //{ HID_NO_KEY,     MOD_LAYER_0 , ' ' } // normale Ebene
    _ik_MOD_1      ,     //{ HID_NO_KEY,     MOD_LAYER_1 , ' ' } // Neo Mod 3
    _ik_MOD_2      ,     //{ HID_NO_KEY,     MOD_LAYER_2 , ' ' } // Neo Mod 4
    _ik_MOD_3      ,     //{ HID_NO_KEY,     MOD_LAYER_3 , ' ' }
    _ik_COMPOSE    ,     //{ HID_NO_KEY,     MOD_COMPOSE , ' ' }
    _ik_INS        ,     //{ HID_INSERT,   0     , ' ' }  //  Insert
    _ik_DEL        ,     //{ HID_DELETE,   0     , ' ' }  //  Delete
    _ik_LEFT       ,     //{ HID_LEFT,     0     , ' ' }  //  Left
    _ik_HOME       ,     //{ HID_HOME,     0     , ' ' }  //  Home
    _ik_END        ,     //{ HID_END,      0     , ' ' }  //  End
    _ik_UP         ,     //{ HID_UP,       0     , ' ' }  //  Up
    _ik_DOWN       ,     //{ HID_DOWN,     0     , ' ' }  //  Down
    _ik_PGUP       ,     //{ HID_PAGE_UP,  0     , ' ' }  //  PgUp
    _ik_PGDN       ,     //{ HID_PAGE_DOWN,0     , ' ' }  //  PgDn
    _ik_RIGHT      ,     //{ HID_RIGHT,    0     , ' ' }  //  Right
    _ik_NUMLOCK    ,     //{ HID_NUM_LOCK,NUMLOCK, ' ' }  //  NumLock
    _ik_PRTSC      ,     //{ HID_PRINTSCREEN,0   , ' ' }  //  PrtSc
    _ik_ESC        ,     //{ HID_ESC, 0,    ' ' }  //  Esc
    _ik_F1         ,     //{ HID_F1,  0,    ' ' }  //  F1
    _ik_F2         ,     //{ HID_F2,  0,    ' ' }  //  F2
    _ik_F3         ,     //{ HID_F3,  0,    ' ' }  //  F3
    _ik_F4         ,     //{ HID_F4,  0,    ' ' }  //  F4
    _ik_F5         ,     //{ HID_F5,  0,    ' ' }  //  F5
    _ik_F6         ,     //{ HID_F6,  0,    ' ' }  //  F6
    _ik_F7         ,     //{ HID_F7,  0,    ' ' }  //  F7
    _ik_F8         ,     //{ HID_F8,  0,    ' ' }  //  F8
    _ik_F9         ,     //{ HID_F9,  0,    ' ' }  //  F9
    _ik_F10        ,     //{ HID_F10, 0,    ' ' }  //  F10
    _ik_F11        ,     //{ HID_F11, 0,    ' ' }  //  F11
    _ik_F12        ,     //{ HID_F12, 0,    ' ' }  //  F12
    _ik_SYSTEM_POWER      ,    //{ KB_SYSTEM_POWER,0         , ' ' }  //  PC Power
    _ik_SYSTEM_SLEEP      ,    //{ KB_SYSTEM_SLEEP,0         , ' ' }
    _ik_SYSTEM_WAKE       ,    //{ KB_SYSTEM_WAKE,0          , ' ' }
    _ik_AUDIO_MUTE        ,    //{ KB_AUDIO_MUTE,0           , ' ' }
    _ik_AUDIO_VOL_UP      ,    //{ KB_AUDIO_VOL_UP,0         , ' ' }
    _ik_AUDIO_VOL_DOWN    ,    //{ KB_AUDIO_VOL_DOWN,0       , ' ' }
    _ik_MEDIA_NEXT_TRACK  ,    //{ KB_MEDIA_NEXT_TRACK,0     , ' ' }
    _ik_MEDIA_PREV_TRACK  ,    //{ KB_MEDIA_PREV_TRACK,0     , ' ' }
    _ik_MEDIA_STOP        ,    //{ KB_MEDIA_STOP,0           , ' ' }
    _ik_MEDIA_PLAY_PAUSE  ,    //{ KB_MEDIA_PLAY_PAUSE,0     , ' ' }
    _ik_MEDIA_SELECT      ,    //{ KB_MEDIA_SELECT,0         , ' ' }
    _ik_MAIL              ,    //{ KB_MAIL,0                 , ' ' }
    _ik_CALCULATOR        ,    //{ KB_CALCULATOR,0           , ' ' }
    _ik_MY_COMPUTER       ,    //{ KB_MY_COMPUTER,0          , ' ' }
    _ik_WWW_SEARCH        ,    //{ KB_WWW_SEARCH,0           , ' ' }
    _ik_WWW_HOME          ,    //{ KB_WWW_HOME,0             , ' ' }
    _ik_WWW_BACK          ,    //{ KB_WWW_BACK,0             , ' ' }
    _ik_WWW_FORWARD       ,    //{ KB_WWW_FORWARD,0          , ' ' }
    _ik_WWW_STOP          ,    //{ KB_WWW_STOP,0             , ' ' }
    _ik_WWW_REFRESH       ,    //{ KB_WWW_REFRESH,0          , ' ' }
    _ik_WWW_FAVORITES     ,    //{ KB_WWW_FAVORITES,0        , ' ' }
    _ik_UNDO         ,     //{ HID_Z,        L_GUI , 'Z' }
    _ik_REDO         ,     //{ HID_Z,        L_GUI | L_SHF , 'Z' }
    _ik_BSLASH       ,     //{ HID_GRAVE,        0,      '\\' }
    _ik_PIPE         ,     //{ HID_GRAVE,        L_SHF , '|' }
    _ik_GRAVE        ,     //{ HID_NON_US_2,     0,      '`' }
    _ik_DEGUE        ,     //{ HID_NON_US_2,        L_SHF , 'Ç' }
    _ik_POUND     ,     //{ HID_3,L_SHF           ,'£' }
    _ik_SL_QUOTM  ,     //{ HID_3,L_SHF |L_ALT    ,'†' }
    _ik_SR_QUOTM  ,     //{ HID_4,L_SHF |L_ALT    ,' ' }
    _ik_AMPERSAND ,     //{ HID_7,         L_SHF , '&' }
    _ik_ASTERIX   ,     //{ HID_8,         L_SHF , '*' }
    _ik_AT        ,     //{ HID_2,         L_SHF , '@' }
    _ik_CARET     ,     //{ HID_6,         L_SHF , '&' }
    _ik_COLON     ,     //{ HID_SEMICOLON, L_SHF, ' ' }
    _ik_DQUOTE    ,     //{ HID_QUOTE,     L_SHF , '"' }
    _ik_EQUAL     ,     //{ HID_EQUAL,     0,      '=' }
    _ik_GREATER   ,     //{ HID_PERIOD,    L_SHF , '>' }
    _ik_HASH      ,     //{ HID_NON_US_1,    0   , '#' }
    _ik_L_BRACE   ,     //{ HID_L_BRACKET, 0 ,     '[' }
    _ik_L_BRACKET ,     //{ HID_L_BRACKET, L_SHF,  '{' }
    _ik_LESS      ,     //{ HID_COMMA ,    L_SHF , '<' }
    _ik_L_PAREN   ,     //{ HID_9,         L_SHF , '(' }
    _ik_MINUS     ,     //{ HID_MINUS,     0,      '-' }
    _ik_PLUS      ,     //{ HID_EQUAL,     L_SHF , '+' }
    _ik_QUESTION  ,     //{ HID_SLASH,     L_SHF , '?' }
    _ik_QUESTIONI ,     //{ HID_SLASH,L_ALT | L_SHF,'Ë'}
    _ik_SQUOTE    ,     //{ HID_QUOTE,     0,      '\''}
    _ik_R_BRACE   ,     //{ HID_R_BRACKET, 0 ,     ']' }
    _ik_R_BRACKET ,     //{ HID_R_BRACKET, L_SHF,  '}' }
    _ik_R_PAREN   ,     //{ HID_0,         L_SHF , ')' }
    _ik_SCOLON    ,     //{ HID_SEMICOLON, 0,      ';' }
    _ik_SLASH     ,     //{ HID_SLASH,     0,      '/' }
    _ik_USCORE    ,     //{ HID_MINUS,     L_SHF , '_' }
    _ik_y         ,     //{ HID_Y,         0,      'y' }
    _ik_Y         ,     //{ HID_Y,         L_SHF , 'Y' }
    _ik_z         ,     //{ HID_Z,         0,      'z' }
    _ik_Z         ,     //{ HID_Z,         L_SHF , 'Z' }
    _ik_DEGREE    ,     // _no
    _ik_TILDE     ,     //{ HID_NON_US_1,   L_SHF , '~' }
    _ik_SSHARP    ,     // _no
    _ik_a_UML     ,     // _no
    _ik_A_UML     ,     // _no
    _ik_O_UML     ,     // _no
    _ik_o_UML     ,     // _no
    _ik_U_UML     ,     // _no
    _ik_u_UML     ,     // _no
    // Mouse
    _ik_MS_U       ,     //{ MS_U, 0,    ' ' }
    _ik_MS_D       ,     //{ MS_D, 0,    ' ' }
    _ik_MS_L       ,     //{ MS_L, 0,    ' ' }
    _ik_MS_R       ,     //{ MS_R, 0,    ' ' }
    _ik_MS_W_U     ,     //{ MS_W_U, 0,    ' ' }
    _ik_MS_W_D     ,     //{ MS_W_D, 0,    ' ' }
    _ik_MS_W_L     ,     //{ MS_W_L, 0,    ' ' }
    _ik_MS_W_R     ,     //{ MS_W_R, 0,    ' ' }
    _ik_MS_ACC0    ,     //{ MS_ACC0, 0,    ' ' }
    _ik_MS_ACC1    ,     //{ MS_ACC1, 0,    ' ' }
    _ik_MS_ACC2    ,     //{ MS_ACC2, 0,    ' ' }
    _ik_MS_BTN1    ,     //{ MS_BTN1, 0,    ' ' }
    _ik_MS_BTN2    ,     //{ MS_BTN2, 0,    ' ' }
    _ik_MS_BTN3    ,     //{ MS_BTN3, 0,    ' ' }
    _ik_MS_BTN4    ,     //{ MS_BTN4, 0,    ' ' }
    _ik_MS_BTN5    ,     //{ MS_BTN5, 0,    ' ' }
    _ik_NUMBERoF
} InterimsKeycode;

/// @todo .data usage: this adds 3*128 bytes and is needed only for macro and printf
static const uint8_t ascii2hid[128] = {
    _ik_no , // ( nul)   0
    _ik_no , // ( soh)   1
    _ik_no , // ( stx)   2
    _ik_no , // ( etx)   3
    _ik_no , // ( eot)   4
    _ik_no , // ( enq)   5
    _ik_no , // ( ack)   6
    _ik_no , // ( bel)   7
    _ik_no , // ( bs)    8
    _ik_no , // ( ht)    9
    _ik_ENTER , // ( nl)   10
    _ik_no , // ( vt)   11
    _ik_no , // ( np)   12
    _ik_no , // ( cr)   13
    _ik_no , // ( so)   14
    _ik_no , // ( si)   15
    _ik_no , // ( dle)  16
    _ik_no , // ( dc1)  17
    _ik_no , // ( dc2)  18
    _ik_no , // ( dc3)  19
    _ik_no , // ( dc4)  20
    _ik_no , // ( nak)  21
    _ik_no , // ( syn)  22
    _ik_no , // ( etb)  23
    _ik_no , // ( can)  24
    _ik_no , // ( em)   25
    _ik_no , // ( sub)  26
    _ik_no , // ( esc)  27
    _ik_no , // ( fs)   28
    _ik_no , // ( gs)   29
    _ik_no , // ( rs)   30
    _ik_no , // ( us)   31
    _ik_no , // ( sp)   32
    _ik_EXCLAM ,   // !       33
    _ik_DQUOTE ,   // "       34
    _ik_HASH ,     // #       35
    _ik_DOLLAR ,   // $       36
    _ik_PERCENT ,  // %       37
    _ik_AMPERSAND, // &       38
    _ik_SQUOTE ,   // '       39
    _ik_L_PAREN ,  // (       40
    _ik_R_PAREN ,  // )       41
    _ik_ASTERIX ,  // *       42
    _ik_PLUS ,     // +       43
    _ik_COMMA ,    // ,       44
    _ik_MINUS ,    // -       45
    _ik_PERIOD ,   // .       46
    _ik_SLASH ,    // /       47
    _ik_0 , // 0       48
    _ik_1 , // 1       49
    _ik_2 , // 2       50
    _ik_3 , // 3       51
    _ik_4 , // 4       52
    _ik_5 , // 5       53
    _ik_6 , // 6       54
    _ik_7 , // 7       55
    _ik_8 , // 8       56
    _ik_9 , // 9       57
    _ik_COLON ,    // :       58
    _ik_SCOLON ,   // ;       59
    _ik_LESS ,     // <       60
    _ik_EQUAL ,    // =       61
    _ik_GREATER ,  // >       62
    _ik_QUESTION,  // ?       63
    _ik_AT, // @       64
    _ik_A , // A       65
    _ik_B , // B       66
    _ik_C , // C       67
    _ik_D , // D       68
    _ik_E , // E       69
    _ik_F , // F       70
    _ik_G , // G       71
    _ik_H , // H       72
    _ik_I , // I       73
    _ik_J , // J       74
    _ik_K , // K       75
    _ik_L , // L       76
    _ik_M , // M       77
    _ik_N , // N       78
    _ik_O , // O       79
    _ik_P , // P       80
    _ik_Q , // Q       81
    _ik_R , // R       82
    _ik_S , // S       83
    _ik_T , // T       84
    _ik_U , // U       85
    _ik_V , // V       86
    _ik_W , // W       87
    _ik_X , // X       88
    _ik_Y , // Y       89
    _ik_Z , // Z       90
    _ik_L_BRACKET, // [       91
    _ik_BSLASH ,   // \       92
    _ik_R_BRACKET, // ]       93
    _ik_CARET ,    // ^       94
    _ik_USCORE ,   // _ik_       95
    _ik_GRAVE ,    // `       96
    _ik_a , // a       97
    _ik_b , // b       98
    _ik_c , // c       99
    _ik_d , // d      100
    _ik_e , // e      101
    _ik_f , // f      102
    _ik_g , // g      103
    _ik_h , // h      104
    _ik_i , // i      105
    _ik_j , // j      106
    _ik_k , // k      107
    _ik_l , // l      108
    _ik_m , // m      109
    _ik_n , // n      110
    _ik_o , // o      111
    _ik_p , // p      112
    _ik_q , // q      113
    _ik_r , // r      114
    _ik_s , // s      115
    _ik_t , // t      116
    _ik_u , // u      117
    _ik_v , // v      118
    _ik_w , // w      119
    _ik_x , // x      120
    _ik_y , // y      121
    _ik_z , // z      122
    _ik_L_BRACE ,  // {      123
    _ik_PIPE ,     // |      124
    _ik_R_BRACE ,  // }      125
    _ik_TILDE ,    // ~      126
    _ik_DEL        // ( del) 127
} ;

#endif // _HID_USAGE_H

