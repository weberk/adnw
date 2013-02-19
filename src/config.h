/*
    Copyright 2013 Stefan Fröbe, <frobiac /at/ gmail [d0t] com>

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

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file config.h
 *
 * User specific configuration of the firmware.
 * Debug and PS/2 options must be set in makefile.
 * Do not forget to adjust matrix.h to the hardware wiring used.
 *
 * @todo : Still need to configure command keys here.
 */

/// define DEBUG_OUTPUT in makefile to enable printf() for hid_listen.
#ifdef DEBUG_OUTPUT
    #include "hhstdio.h"
    //#define TRACE printf
    #define TRACE(...)
#else
    #define TRACE(...)
    #define printf(...) 
#endif

#define PINKYDROP          0  ///<  drop pinky column by one for more ergonomic layout
#define GEOGRAPHICAL_AREAS 3 // QWERTZ(DE), QWERTY(GB), QWERTY(US)

// thanks to Openmoko, Inc we now have a dedicated USB Product ID
// Change this if you indend to make changes to the firmware, or distribute it
// in any way as these are specifically acquired for this setup!
#define VENDOR_ID             0x1D50
#define PRODUCT_ID            0x6033
#define RELEASE_NUMBER        0x0001

// Defines dependent on keyboard model
#ifdef MALTRON_KW
  #define STR_MANUFACTURER L"Maltron"
  #define STR_PRODUCT      L"Maltron KW AdNW"
  #define DEFAULTLAYOUT       KOY
  #define DEFAULTMACORPC      Mac
  #define DEFAULTGEOAREA      DE
  // Menu and Fn pressed simultaneously
  #define CMD_MODE() ((rowData[6] & (1<<4)) && (rowData[6] & (1<<3)) )
  #define LAYERS   3
  #define LAYOUTS  4
  #define ROWS     8  // F,Nr,3xChars,Subs,Thumb, Middle
  #define COLS    12  ///< cols of both keyboard halves are "stacked" in layout and physically connected
  /*
   * 101 102 103 104 105 106         107 108 109 110 111 112
   * 201 202 203 204 205 206   803   207 208 209 210 211 212
   * 301 302 303 304 305 306   802   307 308 309 310 311 312
   * 401 402 403 404 405 406   801   407 408 409 410 411 412
   * 501 502 503 504 505 506         507 508 509 510 511 512
   * 601 602 603 604 605                 606 607 608 609 610
   *                  701 704       709 706
   *                   702 705   710 707
   *                     703       708
   */

  #define KEYMAP( k101, k102, k103, k104, k105, k106,           k107, k108, k109, k110, k111, k112, \
                  k201, k202, k203, k204, k205, k206,   k803,   k207, k208, k209, k210, k211, k212, \
                  k301, k302, k303, k304, k305, k306,   k802,   k307, k308, k309, k310, k311, k312, \
                  k401, k402, k403, k404, k405, k406,   k801,   k407, k408, k409, k410, k411, k412, \
                  k501, k502, k503, k504, k505, k506,           k507, k508, k509, k510, k511, k512, \
                  k601, k602, k603, k604, k605,                       k608, k609, k610, k611, k612, \
                                            k701, k704,       k709, k706,                           \
                                              k702, k705,   k710, k707,                             \
                                                k703,           k708                                \
  ) { \
      { k101, k102, k103, k104, k105, k106,           k107, k108, k109, k110, k111, k112 }, \
      { k201, k202, k203, k204, k205, k206,           k207, k208, k209, k210, k211, k212 }, \
      { k301, k302, k303, k304, k305, k306,           k307, k308, k309, k310, k311, k312 }, \
      { k401, k402, k403, k404, k405, k406,           k407, k408, k409, k410, k411, k412 }, \
      { k501, k502, k503, k504, k505, k506,           k507, k508, k509, k510, k511, k512 }, \
      { k601, k602, k603, k604, k605, 0000,           0000, k608, k609, k610, k611, k612 }, \
      { k701, k702, k703, k704, k705, k706,           k707, k708, k709, k710, 0000, 0000 }, \
      { k801, k802, k803, 0000, 0000, 0000,           0000, 0000, 0000, 0000, 0000, 0000 } \
    }
/**
 * Mouse keycodes that temporarily override normal keycodes during trackpoint usage.
 * Mouse buttons can be mapped to good locations this way.
 * This is not to be confused with the mousekey implementation, which is activated by switching to its layer.
 *
 */
static const uint8_t MouseUsage[ROWS][COLS];
//  /*KEYMAP(*/{ 0,
// HID_ESC,  0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0 ,
// 0, HID_MOUSEBTN_1, HID_MOUSEBTN_3, HID_MOUSEBTN_2, HID_MOUSEBTN_4, 0 , 0, 0, 0, 0, 0, 0 ,
// 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0 ,
// 0, 0, HID_ESC, HID_TAB,0, HID_MOUSEBTN_1,0, /* | */ HID_MOUSEBTN_3, HID_MOUSEBTN_2, HID_BACKSPACE, HID_ENTER, 0, 0, 0
//};

static const uint16_t secondaryModifierUsageMatrix[LAYOUTS][ROWS][COLS] = {
    {   // LAYOUT 1: QWERTZ de
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { HID_TAB,   HID_SPACE, HID_BACKSPACE,0,     0,       /**/ HID_ENTER, HID_SPACE, HID_DELETE,0,         0,         0,         0 }, // nur 5 Tasten belegt pro Seite!!
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 }
    },
    {   // LAYOUT 2: KO.,Y de
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { HID_ESC,   0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { HID_TAB,   HID_SPACE, HID_BACKSPACE,0,     0,       /**/ HID_ENTER, HID_SPACE, HID_DELETE,0,         0,         0,         0 }, // nur 5 Tasten belegt pro Seite!!
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 }
    },
    {   // LAYOUT 3: Malt90 en
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { HID_E,HID_SPACE,HID_BACKSPACE,      0,     0,       /**/ HID_ENTER, HID_SPACE, HID_DELETE,0,         0,         0,         0 }, // nur 5 Tasten belegt pro Seite!!
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 }
    },
    {   // LAYOUT 4: QWERTY en
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 },
        { HID_TAB,HID_SPACE,HID_BACKSPACE,    0,     0,       /**/ HID_ENTER, HID_SPACE, HID_DELETE,0,         0,         0,         0 }, // nur 5 Tasten belegt pro Seite!!
        { 0,         0,         0,            0,     0,    0, /**/ 0,         0,         0,         0,         0,         0 }
    }
};


// on BlueCube, the innermost thumb-buttons are on outermost columns in matrix!
//         0  5
// 2 3 4 5 1  4 0 1 2 3
//
#define _ik_MACRO _ik_no

#define _ik_THUMB_ROW_LEFT_QWERTZ  _ik_L_CTRL,   _ik_L_SHIFT,            _ik_L_ALT,                \
                                _ik_MOD_2/*FN*/, _ik_APP
#define _ik_THUMB_ROW_RIGHT_QWERTZ _ik_R_CTRL,           _ik_R_SHIFT,    _ik_L_ALT,                 \
                                _ik_ALTGR /*_R_ALT*/, _ik_R_GUI,                              _ik_no,            _ik_no
#define _ik_THUMB_ROW_LEFT_NEO  _ik_MOD_1,   _ik_L_SHIFT,            _ik_MOD_2,                \
                                _ik_MOD_2/*FN*/, _ik_APP
#define _ik_THUMB_ROW_RIGHT_NEO _ik_MOD_1,           _ik_R_SHIFT,    _ik_MOD_2,                 \
                                _ik_ALTGR /*_R_ALT*/, _ik_R_GUI,                              _ik_no,            _ik_no

// #define _ik_THUMB_ROW_RIGHT _ik_L_SHIFT,      _ik_MOD_1,   _ik_R_ALT,  _ik_MOD_3,  _ik_MOD_2, _ik_MOD_3
#define _ik_EXTRA_KEYS  _ik_MAIL, _ik_CALCULATOR, _ik_MY_COMPUTER, _ik_WWW_SEARCH,_ik_F5,_ik_F6,  /**/ _ik_MEDIA_PREV_TRACK,_ik_MEDIA_PLAY_PAUSE,_ik_MEDIA_NEXT_TRACK,_ik_AUDIO_VOL_DOWN,_ik_AUDIO_VOL_UP,_ik_MEDIA_SELECT
// von unten nach oben
#define _ik_MIDDLE_COLUMN  _ik_INS, _ik_SYSTEM_POWER, _ik_AUDIO_MUTE, _ik_no, _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no

PROGMEM static const InterimsKeycode KeyMatrix[LAYOUTS][LAYERS][ROWS][COLS] = {
    {   // LAYOUT 1: QWERTZ de
        // normal layer
        KEYMAP (
            _ik_F1,       _ik_F2,       _ik_F3,       _ik_F4,       _ik_F5,       _ik_F6,                  _ik_F7,       _ik_F8,       _ik_F9,       _ik_F10,      _ik_F11,      _ik_F12    ,
            _ik_CARET,    _ik_1,        _ik_2,        _ik_3,        _ik_4,        _ik_5,  _ik_AUDIO_MUTE,  _ik_6,        _ik_7,        _ik_8,        _ik_9,        _ik_0,        _ik_SSHARP ,
            _ik_SQUOTE,   _ik_q,        _ik_w,        _ik_e,        _ik_r,        _ik_t, _ik_SYSTEM_POWER, _ik_z,        _ik_u,        _ik_i,        _ik_o,        _ik_p,        _ik_u_UML  ,
            _ik_ESC,      _ik_a,        _ik_s,        _ik_d,        _ik_f,        _ik_g,    _ik_INS,       _ik_h,        _ik_j,        _ik_k,        _ik_l,        _ik_o_UML,    _ik_a_UML  ,
            _ik_LESS,     _ik_y,        _ik_x,        _ik_c,        _ik_v,        _ik_b,                   _ik_n,        _ik_m,        _ik_COMMA,    _ik_PERIOD,   _ik_MINUS,    _ik_PLUS   ,
            _ik_L_CTRL,   _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,                                            _ik_LEFT,     _ik_RIGHT,    _ik_DOWN,     _ik_UP,       _ik_HASH   ,
                                                                  _ik_L_CTRL,   _ik_MOD_2,                 _ik_ALTGR,  _ik_R_CTRL,
                                                                     _ik_L_SHIFT,  _ik_APP,             _ik_R_GUI,  _ik_R_SHIFT,
                                                                        _ik_L_ALT,                               _ik_L_ALT
        ),
        // dummy MOD3 layer
        {
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    }
        },
        // FN called MOD4 layer -  (movement controls and numbers, media control, layout switch, power, applications)
        KEYMAP (
            _ik_MAIL,     _ik_CALCULATOR,_ik_MY_COMPUTER,_ik_WWW_SEARCH,_ik_F5,   _ik_F6,                  _ik_MEDIA_PREV_TRACK,_ik_MEDIA_PLAY_PAUSE,_ik_MEDIA_NEXT_TRACK,_ik_AUDIO_VOL_DOWN,_ik_AUDIO_VOL_UP,_ik_MEDIA_SELECT,
            _ik_CARET,    _ik_1,        _ik_2,        _ik_3,        _ik_4,        _ik_5,  _ik_AUDIO_MUTE,  _ik_POUND,     _ik_7,        _ik_TAB,      _ik_SLASH,    _ik_ASTERIX,  _ik_SSHARP ,
            _ik_no,       _ik_PGUP,     _ik_BSPACE,   _ik_UP,       _ik_DEL ,     _ik_PGDN, _ik_SYSTEM_POWER, _ik_EXCLAMI,_ik_7,        _ik_8,        _ik_9,        _ik_PLUS,     _ik_MINUS  ,
            _ik_ESC,      _ik_HOME,     _ik_LEFT,     _ik_DOWN,     _ik_RIGHT,    _ik_END,    _ik_INS,     _ik_QUESTIONI, _ik_4,        _ik_5,        _ik_6,        _ik_COMMA,    _ik_PERIOD ,
            _ik_no,       _ik_ESC,      _ik_TAB,      _ik_INS,      _ik_ENTER,    _ik_UNDO,                _ik_REDO,      _ik_1,        _ik_2,        _ik_3,        _ik_no,       _ik_no     ,
            _ik_L_CTRL,   _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,                                             _ik_LEFT,     _ik_0,        _ik_DOWN,     _ik_UP,       _ik_HASH   ,
                                                                  _ik_L_CTRL,   _ik_MOD_2,                 _ik_ALTGR,  _ik_R_CTRL,
                                                                     _ik_L_SHIFT,  _ik_APP,             _ik_R_GUI,  _ik_R_SHIFT,
                                                                        _ik_L_ALT,                               _ik_L_ALT
        )
    },
    {   // LAYOUT 2: KO.,Y de
        // KO.,Y (meins)
        {
            { _ik_F1,       _ik_F2,       _ik_F3,       _ik_F4,       _ik_F5,       _ik_F6,        /**/ _ik_F7,       _ik_F8,       _ik_F9,       _ik_F10,      _ik_F11,      _ik_F12    },
            { _ik_CARET,    _ik_1,        _ik_2,        _ik_3,        _ik_4,        _ik_5,         /**/ _ik_6,        _ik_7,        _ik_8,        _ik_9,        _ik_0,        _ik_MINUS  },
            { _ik_TAB,      _ik_k,        _ik_o,        _ik_PERIOD,   _ik_COMMA,    _ik_y,         /**/ _ik_p,        _ik_c,        _ik_l,        _ik_m,        _ik_b,        _ik_x      },
            { _ik_L_ALT,    _ik_h,        _ik_a,        _ik_e,        _ik_i,        _ik_u,         /**/ _ik_d,        _ik_t,        _ik_r,        _ik_n,        _ik_s,        _ik_SSHARP },
            { _ik_L_CTRL,   _ik_z,        _ik_q,        _ik_a_UML,    _ik_u_UML,    _ik_o_UML,     /**/ _ik_j,        _ik_g,        _ik_w,        _ik_v,        _ik_f,        _ik_R_CTRL },
            { _ik_GRAVE,    _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,     _ik_no,        /**/ _ik_no,       _ik_LEFT,     _ik_RIGHT,    _ik_DOWN,     _ik_UP,       _ik_DEGUE  },
            {                                           _ik_THUMB_ROW_LEFT_NEO ,    /**/ _ik_THUMB_ROW_RIGHT_NEO                                           },
            {                                                            _ik_MIDDLE_COLUMN                                                              }
        },
        //                                                                      //  BU-TECK
        //        { _ik_ESC,      _ik_b,        _ik_u,        _ik_q,        _ik_PERIOD,   _ik_x,         /**/ _ik_p,        _ik_c,        _ik_l,        _ik_m,        _ik_f,        _ik_BSPACE },
        //        { _ik_TAB,      _ik_h,        _ik_i,        _ik_e,        _ik_a,        _ik_o,         /**/ _ik_d,        _ik_t,        _ik_r,        _ik_n,        _ik_s,        _ik_ENTER  },
        //        { _ik_DQUOTE,   _ik_k,        _ik_y,        _ik_MINUS,    _ik_COMMA,    _ik_SLASH,     /**/ _ik_j,        _ik_g,        _ik_w,        _ik_v,        _ik_z,        _ik_no  },
        // MOD3 layer (special char)
        {
            { _ik_F1,       _ik_F2,       _ik_F3,       _ik_F4,       _ik_F5,       _ik_F6,        /**/ _ik_F7,       _ik_F8,       _ik_F9,       _ik_F10,      _ik_F11,      _ik_F12    },
            { _ik_CARET,    _ik_1,        _ik_2,        _ik_3,        _ik_SR_QUOTM, _ik_SL_QUOTM,  /**/ _ik_6,        _ik_7,        _ik_8,        _ik_9,        _ik_0,         _ik_MINUS },
            { _ik_no,       _ik_DOT3,      _ik_USCORE,  _ik_L_BRACKET, _ik_R_BRACKET,_ik_CARET,     /**/ _ik_EXCLAM,   _ik_LESS,     _ik_GREATER,  _ik_EQUAL,    _ik_AMPERSAND,_ik_no     },
            { _ik_ESC,      _ik_BSLASH,   _ik_SLASH,    _ik_L_BRACE,  _ik_R_BRACE,  _ik_ASTERIX,   /**/ _ik_QUESTION, _ik_L_PAREN,  _ik_R_PAREN,  _ik_MINUS,    _ik_COLON,    _ik_AT     },
            { _ik_no,       _ik_HASH,     _ik_DOLLAR,   _ik_PIPE,     _ik_TILDE,    _ik_GRAVE,     /**/ _ik_PLUS,     _ik_PERCENT,  _ik_DQUOTE,   _ik_SQUOTE,   _ik_SCOLON,   _ik_R_CTRL },
            { _ik_L_CTRL,   _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,     _ik_no,        /**/ _ik_no,       _ik_LEFT,     _ik_RIGHT,    _ik_DOWN,     _ik_UP,       _ik_no     },
            {                                           _ik_THUMB_ROW_LEFT_NEO ,    /**/ _ik_THUMB_ROW_RIGHT_NEO                                           },
            {                                                            _ik_MIDDLE_COLUMN                                                              }
        },
        // MOD4 layer (movement controls and numbers)
        {
            {                                                                _ik_EXTRA_KEYS                                                             },
            { _ik_CARET,    _ik_1,        _ik_2,        _ik_3,        _ik_4,        _ik_5,         /**/ _ik_POUND,    _ik_7,        _ik_TAB,      _ik_SLASH,    _ik_ASTERIX,  _ik_MINUS  },
            { _ik_no,       _ik_PGUP,     _ik_BSPACE,   _ik_UP,       _ik_DEL ,     _ik_PGDN,      /**/ _ik_EXCLAMI,  _ik_7,        _ik_8,        _ik_9,        _ik_PLUS,     _ik_MINUS  },
            { _ik_ESC,      _ik_HOME,     _ik_LEFT,     _ik_DOWN,     _ik_RIGHT,    _ik_END,       /**/ _ik_QUESTIONI,_ik_4,        _ik_5,        _ik_6,        _ik_COMMA,    _ik_PERIOD },
            { _ik_no,       _ik_ESC,      _ik_TAB,      _ik_INS,      _ik_ENTER,    _ik_UNDO,      /**/ _ik_REDO,     _ik_1,        _ik_2,        _ik_3,        _ik_no,       _ik_no     },
            { _ik_L_CTRL,   _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,     _ik_no,        /**/ _ik_no,       _ik_LEFT,     _ik_0,        _ik_DOWN,     _ik_UP,       _ik_HASH   },
            {                                           _ik_THUMB_ROW_LEFT_NEO ,    /**/ _ik_THUMB_ROW_RIGHT_NEO                                           },
            {                                                            _ik_MIDDLE_COLUMN                                                              }
        }
    },
    {   // LAYOUT 3: Malt90en
        // normal layer
        {
            { _ik_F1,       _ik_F2,       _ik_F3,       _ik_F4,       _ik_F5,       _ik_F6,        /**/ _ik_F7,       _ik_F8,       _ik_F9,       _ik_F10,      _ik_F11,      _ik_F12    },
            { _ik_GRAVE,    _ik_1,        _ik_2,        _ik_3,        _ik_4,        _ik_5,         /**/ _ik_6,        _ik_7,        _ik_8,        _ik_9,        _ik_0,        _ik_ESC     },
            { _ik_EQUAL,    _ik_q,        _ik_p,        _ik_y,        _ik_c,        _ik_b,         /**/ _ik_v,        _ik_m,        _ik_u,        _ik_z,        _ik_l,        _ik_L_BRACKET},
            { _ik_TAB,      _ik_a,        _ik_n,        _ik_i,        _ik_s,        _ik_f,         /**/ _ik_d,        _ik_t,        _ik_h,        _ik_o,        _ik_r,        _ik_SQUOTE },
            { _ik_BSLASH,   _ik_COMMA,    _ik_PERIOD,   _ik_j,        _ik_g,        _ik_SLASH,     /**/ _ik_SCOLON,   _ik_w,        _ik_k,        _ik_MINUS,    _ik_x,        _ik_R_BRACKET},
            { _ik_L_CTRL,   _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,     _ik_no,        /**/ _ik_no,       _ik_LEFT,     _ik_RIGHT,    _ik_DOWN,     _ik_UP,       _ik_HASH   },
            {                                           _ik_THUMB_ROW_LEFT_QWERTZ , /**/ _ik_THUMB_ROW_RIGHT_QWERTZ                                        },
            {                                                            _ik_MIDDLE_COLUMN                                                              }
        },
        // dummy MOD3 layer
        {
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    }
        },
        // FN called MOD4 layer -  (movement controls and numbers, media control, layout switch, power, applications)
        {
            {                                                                _ik_EXTRA_KEYS                                                              },
            { _ik_CARET,    _ik_1,        _ik_2,        _ik_3,        _ik_4,        _ik_5,         /**/ _ik_POUND,     _ik_7,        _ik_TAB,      _ik_SLASH,    _ik_ASTERIX,  _ik_no     },
            { _ik_no,       _ik_PGUP,     _ik_BSPACE,   _ik_UP,       _ik_DEL ,     _ik_PGDN,      /**/ _ik_EXCLAMI,   _ik_7,        _ik_8,        _ik_9,        _ik_PLUS,     _ik_MINUS  },
            { _ik_TAB,      _ik_HOME,     _ik_LEFT,     _ik_DOWN,     _ik_RIGHT,    _ik_END,       /**/ _ik_QUESTIONI, _ik_4,        _ik_5,        _ik_6,        _ik_COMMA,    _ik_PERIOD },
            { _ik_no,       _ik_ESC,      _ik_TAB,      _ik_INS,      _ik_ENTER,    _ik_UNDO,      /**/ _ik_REDO,      _ik_1,        _ik_2,        _ik_3,        _ik_no,       _ik_no     },
            { _ik_L_CTRL,   _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,     _ik_no,        /**/ _ik_no,        _ik_LEFT,     _ik_0,        _ik_DOWN,     _ik_UP,       _ik_HASH   },
            {                                           _ik_THUMB_ROW_LEFT_QWERTZ , /**/ _ik_THUMB_ROW_RIGHT_QWERTZ                                         },
            {                                                            _ik_MIDDLE_COLUMN                                                               }
        }
    },
    {   // LAYOUT 4: QWERTY en
        // normal layer
        {
            { _ik_F1,       _ik_F2,       _ik_F3,       _ik_F4,       _ik_F5,       _ik_F6,        /**/ _ik_F7,       _ik_F8,       _ik_F9,       _ik_F10,      _ik_F11,      _ik_F12    },
            { _ik_GRAVE,    _ik_1,        _ik_2,        _ik_3,        _ik_4,        _ik_5,         /**/ _ik_6,        _ik_7,        _ik_8,        _ik_9,        _ik_0,        _ik_MINUS  },
            { _ik_EQUAL,    _ik_q,        _ik_w,        _ik_e,        _ik_r,        _ik_t,         /**/ _ik_y,        _ik_u,        _ik_i,        _ik_o,        _ik_p,        _ik_L_BRACKET},
            { _ik_ESC,      _ik_a,        _ik_s,        _ik_d,        _ik_f,        _ik_g,         /**/ _ik_h,        _ik_j,        _ik_k,        _ik_l,        _ik_SCOLON,   _ik_SQUOTE },
            { _ik_BSLASH,   _ik_z,        _ik_x,        _ik_c,        _ik_v,        _ik_b,         /**/ _ik_n,        _ik_m,        _ik_COMMA,    _ik_PERIOD,   _ik_SLASH,    _ik_R_BRACKET},
            { _ik_L_CTRL,   _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,     _ik_no,        /**/ _ik_no,       _ik_LEFT,     _ik_RIGHT,    _ik_DOWN,     _ik_UP,       _ik_HASH   },
            {                                           _ik_THUMB_ROW_LEFT_QWERTZ , /**/ _ik_THUMB_ROW_RIGHT_QWERTZ                                        },
            {                                                            _ik_MIDDLE_COLUMN                                                              }
        },
        // dummy MOD3 layer
        {
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    },
            { _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,       _ik_no,        /**/ _ik_no,       _ik_no,       _ik_no,       _ik_no,      _ik_no,      _ik_no    }
        },
        // FN called MOD4 layer -  (movement controls and numbers, media control, layout switch, power, applications)
        {
            {                                                                _ik_EXTRA_KEYS                                                                },
            { _ik_CARET,    _ik_1,        _ik_2,        _ik_3,        _ik_4,        _ik_5,         /**/ _ik_POUND,        _ik_7,       _ik_TAB,      _ik_SLASH,    _ik_ASTERIX,  _ik_no     },
            { _ik_no,       _ik_PGUP,     _ik_BSPACE,   _ik_UP,       _ik_DEL ,     _ik_PGDN,      /**/ _ik_EXCLAMI,      _ik_7,       _ik_8,        _ik_9,        _ik_PLUS,     _ik_MINUS  },
            { _ik_ESC,      _ik_HOME,     _ik_LEFT,     _ik_DOWN,     _ik_RIGHT,    _ik_END,       /**/ _ik_QUESTIONI,   _ik_4,        _ik_5,        _ik_6,        _ik_COMMA,    _ik_PERIOD },
            { _ik_no,       _ik_ESC,      _ik_TAB,      _ik_INS,      _ik_ENTER,    _ik_UNDO,      /**/ _ik_REDO,        _ik_1,        _ik_2,        _ik_3,        _ik_no,       _ik_no     },
            { _ik_L_CTRL,   _ik_L_SHIFT,  _ik_PRTSC,    _ik_PGDN,     _ik_PGUP,     _ik_no,        /**/ _ik_no,          _ik_LEFT,     _ik_0,        _ik_DOWN,     _ik_UP,       _ik_HASH   },
            {                                           _ik_THUMB_ROW_LEFT_QWERTZ , /**/ _ik_THUMB_ROW_RIGHT_QWERTZ                                           },
            {                                                            _ik_MIDDLE_COLUMN                                                                 }
        }
    }
}; // end of layouts

#elif BLUECUBE
  #define STR_MANUFACTURER L"frobiac"
  #define STR_PRODUCT      L"AdNW TP and mouse"
  #define DEFAULTLAYOUT       QWERTZ_DE
  #define DEFAULTMACORPC      PC
  #define DEFAULTGEOAREA      DE
  #define CMD_MODE() ((rowData[2] & (1<<0)) && (rowData[6] & (1<<5)) )
  #define LAYERS   5
  #define LAYOUTS  1
  #define ROWS     8
  #define COLS     6  ///< cols of both keyboard halves are "stacked" in layout and physically connected
  /*
   * 00 01 02 03 04 05    40 41 42 43 44 45
   * 10 11 12 13 14 15    50 51 52 53 54 55
   * 20 21 22 23 24 25    60 61 62 63 64 65
   *                30    75
   *    32 33 34 35 31    74 70 71 72 73
   *
   *
   */

  // on BlueCube, the innermost thumb-buttons are on outermost columns in matrix!
  //         0  5
  // 2 3 4 5 1  4 0 1 2 3 4
  //

  #define KEYMAP( no, \
     k00,k01,k02,k03,k04,k05,        k40,k41,k42,k43,k44,k45, \
     k10,k11,k12,k13,k14,k15,        k50,k51,k52,k53,k54,k55, \
     k20,k21,k22,k23,k24,k25,        k60,k61,k62,k63,k64,k65, \
     no30,t31,t32,t33,t34,t35,t36,t70,t71,t72,t73,t74,t75,no76   \
  ) { \
    { k00,k01,k02,k03,k04,k05 }, \
    { k10,k11,k12,k13,k14,k15 }, \
    { k20,k21,k22,k23,k24,k25 }, \
    { t36,t35,t31,t32,t33,t34 }, \
    { k40,k41,k42,k43,k44,k45 }, \
    { k50,k51,k52,k53,k54,k55 }, \
    { k60,k61,k62,k63,k64,k65 }, \
    { t72,t73,t74,t75,t71,t70 } \
  }

#elif HYPERNANO
  #define STR_MANUFACTURER L"frobiac"
  #define STR_PRODUCT      L"AdNW TP and mouse"
  #define DEFAULTLAYOUT       QWERTZ_DE
  #define DEFAULTMACORPC      PC
  #define DEFAULTGEOAREA      DE
  #define CMD_MODE() ( (rowData[3] & (1<<1)) && (rowData[7] & (1<<5)) )
  #define LAYERS 5
  #define LAYOUTS  1
  #define ROWS   8
  #define COLS   6  ///< cols of both keyboard halves are "stacked" in layout and physically connected
  /*  Row/col matrix: (0-based)
   *  unused: 11,21,51,61
   *  innermost thumb buttons: 31,41,71,81
   *  mapped to match BlueCube without 31 & 75 using the keycode from the outer lower pinky
   *
   *     01 02 03 04 05 --  -- 41 42 43 44 45
   *    11 12 13 14 15 --    -- 51 52 53 54 55
   *   21 22 23 24 25 20      60 61 62 63 64 65
   *    31 32 33 34 35 30    70 71 72 73 74 75
   */

   //_X, SHFT L_ALT LCTRL, SPACE, GUI, _MACRO,  MOD_3, MOD_2,  L_SHIFT, MOD_1,  AltGr, _A, _B

  #define KEYMAP( no, \
    no00,k01,k02,k03,k04,k05,        k40,k41,k42,k43,k44,no45, \
    no10,k11,k12,k13,k14,k15,        k50,k51,k52,k53,k54,no55, \
    no20,k21,k22,k23,k24,k25,        k60,k61,k62,k63,k64,no65, \
  /*                              M3 M2  SHF  M1  AGr A  B  */ \
     t30,t31,t32,t33,t34,t35,t20,t65,t70,t71,t72,t73,t74,t75   \
  ) { \
    {  no, k01,k02,k03,k04,k05 }, \
    {  no, k11,k12,k13,k14,k15 }, \
    { t20, k21,k22,k23,k24,k25 }, \
    { t35, /*t30*/no20,t31,t32,t33,t34 }, \
  \
    {  no, k40, k41,k42,k43,k44 }, \
    {  no, k50, k51,k52,k53,k54 }, \
    { t65/*no00 ESC*/, k60, k61,k62,k63,k64 }, \
    { t70, t71, t72,t73,t74,/*t75*/no65 } \
  }
#endif // defines per keyboard model

#if defined (BLUECUBE) || defined (HYPERNANO)
/**
 * Mouse keycodes that temporarily override normal keycodes during trackpoint usage.
 * Mouse buttons can be mapped to good locations this way.
 * This is not to be confused with the mousekey implementation, which is activated by switching to its layer.
 *
 */
static const uint8_t MouseUsage[ROWS][COLS] =
  /*KEYMAP(*/{ 0,
 HID_ESC,  0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0 ,
 0, HID_MOUSEBTN_1, HID_MOUSEBTN_3, HID_MOUSEBTN_2, HID_MOUSEBTN_4, 0 , 0, 0, 0, 0, 0, 0 ,
 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0 ,
 0, 0, HID_ESC, HID_TAB,0, HID_MOUSEBTN_1,0, /* | */ HID_MOUSEBTN_3, HID_MOUSEBTN_2, HID_BACKSPACE, HID_ENTER, 0, 0, 0
};

/**
 * MKT keycode if single key and mousekey location is stored in here.
 * In contrast to the keymatrix below, only actual HID-usage codes are used, as
 * there should be no need for modifiers with MKTs.
 * The mouse button locations are put here as there is no overlap whith other keys,
 * but strictly not the right place here.
 */
static const uint8_t SecondaryUsage[ROWS][COLS] =
  KEYMAP( 0,
 HID_ESC,  0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0 ,
 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0 ,
 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0 ,
 0, 0, HID_ESC, HID_TAB,0, 0 /*is real SPACE*/,0, /* | */ 0, HID_ESC, HID_BACKSPACE, HID_ENTER, 0, 0, 0
);


static const keycode KeyMatrix[LAYERS][ROWS][COLS] PROGMEM =
{
  // normal layer
 KEYMAP( _no,
         _MOD_3,   _k, _u, _q,     _PERIOD, _j,      _v, _g, _c, _l, _f, _BSPACE ,
         _TAB,   _h, _i, _e,     _a,      _o,      _d, _t, _r, _n, _s, _ENTER  ,
         _DQUOTE,_x, _y, _MINUS, _COMMA,  _SLASH,  _b, _p, _w, _m, _z, _MOD_MOUSEKEY,
         _X, _L_SHIFT, _L_ALT ,  _L_CTRL, _SPACE, _L_GUI, _MACRO,   _MOD_3, _MOD_2,  _L_SHIFT, _MOD_1,  _R_ALT, _A,  _B
  ),

  // MOD1 layer (special char)
  KEYMAP( _no,
    _no, _AT,      _DEGREE,   _L_BRACKET, _R_BRACKET, _HASH   , _EXCLAM,  _LESS,      _GREATER,   _EQUAL,     _AMPERSAND, _no ,
    _no, _BSLASH,  _SLASH,    _L_BRACE,   _R_BRACE,   _ASTERIX, _QUESTION,_L_PAREN,   _R_PAREN,   _PLUS,      _MINUS,     _no ,
    _no, _no,      _DOLLAR,   _PIPE,      _TILDE,     _GRAVE , _CARET,   _PERCENT,   _DQUOTE,    _SQUOTE,    _no,        _no ,
         _X, _L_SHIFT, _L_ALT ,  _L_CTRL, _SPACE, _L_GUI, _MACRO,   _MOD_3, _MOD_2,  _L_SHIFT, _MOD_1,  _R_ALT, _A,     _B
  ),

  // MOD2 layer (movement controls and numbers)
  KEYMAP( _no,
    _no, _PGUP,   _BSPACE,    _UP,        _DEL ,      _PGDN, _SSHARP,_7,         _8,         _9,     _a_UML, _A_UML ,
    _no, _HOME,   _LEFT,      _DOWN,      _RIGHT,     _END , _PERIOD,_4,         _5,         _6,     _o_UML, _O_UML ,
    _no, _ESC,    _TAB,       _INS,       _ENTER,     _no , _0,     _1,         _2,         _3,     _u_UML, _U_UML ,
         _X, _L_SHIFT, _L_ALT ,  _L_CTRL, _SPACE, _L_GUI, _MACRO,   _MOD_3, _MOD_2,  _L_SHIFT, _MOD_1,  _R_ALT, _A,     _B
  ),

  // MOD3 Fx layer
  KEYMAP( _no,
    _no, _no, _no, _no, _a_UML, _o_UML ,   _F1,      _F2,        _F3,        _F4,        _F5,    _F6     ,
    _no, _no, _no, _no, _no,    _no,       _F7,      _F8,        _F9,        _F10,       _F11,   _F12    ,
    _no, _no, _no, _no, _no,    _no,       _no,      _no,        _no,        _no,        _no,    _no     ,
         _X, _L_SHIFT, _L_ALT ,  _L_CTRL, _SPACE, _L_GUI, _MACRO,   _MOD_3, _MOD_2,  _L_SHIFT, _MOD_1,  _R_ALT, _A,     _B
    ),

  // MOD_MOUSE layer
  KEYMAP( _no,
    _no, _no, _MS_W_U,  _MS_U,  _MS_W_D,  _no,  _a_UML, _o_UML ,  _F1,      _F2,        _F3,        _F4,
    _no, _no, _MS_L, _MS_D, _MS_R, _no,  _X,     _MS_BTN1, _MS_BTN3, _MS_BTN2, _no, _no,
    _no, _no, _MS_W_L, _no,      _MS_W_R,  _no,  _no,    _MS_ACC0, _MS_ACC1, _MS_ACC2, _no, _no,
     _X, _L_SHIFT, _L_ALT ,  _L_CTRL, _SPACE, _L_GUI, _MACRO,   _MOD_3, _MOD_2,  _L_SHIFT, _MOD_1,  _R_ALT, _A,     _B
    ),
/*
  // MOD4 BU-TECK
  KEYMAP( _no,
    _ESC,   _b, _u, _q, _PERIOD,_x  , _p,   _c, _l, _m, _f, _BSPACE ,
    _TAB,   _h, _i, _e, _a, _o  , _d,   _t, _r, _n, _s, _ENTER  ,
    _DQUOTE,_k, _y, _MINUS, _COMMA, _SLASH , _j,   _g, _w, _v, _z, _no  ,
         _X, _L_SHIFT, _L_ALT ,  _L_CTRL, _SPACE, _L_GUI, _MACRO,   _MOD_3, _MOD_2,  _L_SHIFT, _MOD_1,  _R_ALT, _A,     _B
  )
*/
}; // end of matrix[][][]
#endif


#endif // CONFIG_H

