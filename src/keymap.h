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

#ifndef KEYMAP_H
#define KEYMAP_H 1

#include <avr/eeprom.h>
#include <stdint.h>
#include <stdbool.h>
#include "hid_usage.h"
#include "config.h"

typedef struct {
    uint16_t  hid;   ///< HID usage code, will be interpreted by OS keyboard layout!
    uint8_t  mods;  ///< HID modifiers , will be interpreted by OS keyboard layout!
} keycode;


typedef struct {
    InterimsKeycode ikc; // internal usage code, used for layout definition
    keycode kc[GEOGRAPHICAL_AREAS];
} local_keycode;

// gespeichert im EEPROM. ca. 100.000 Schreibzugriffe.
typedef enum
{
    QWERTZ_DE,
    KOY,
    Malt90,
    QWERTY_GB
} Layout;

EEMEM extern Layout alternateLayoutNr; // der Wert des aktiven Layouts; wird persistent gespeichert
typedef enum
{
    DE,
    GB,
    US
} GeoArea;
EEMEM extern GeoArea alternateGeoArea;  // der Wert des aktiven geografischen Bereichs; wird persistent gespeichert

typedef enum
{
    PC,
    Mac
} MacOrPC;
EEMEM extern MacOrPC altMacOrPC;  // der Wert des aktiven Rechnertyps; wird persistent gespeichert

uint8_t getModifier(uint8_t row, uint8_t col, uint8_t layer);
uint16_t getKeyCode (uint8_t row, uint8_t col, uint8_t layer);
uint8_t getKeyChar (uint8_t row, uint8_t col, uint8_t layer);
keycode getKeyStruct_Ic(InterimsKeycode ikc);
void    printLayout(uint8_t l);

#define _MACRO _no




PROGMEM static const local_keycode localizedMacDifferences[] = {
    // Index                  DE                          GB                          US
    {_ik_UNDO              , {{HID_Y,        R_GUI      },{HID_Z,        L_GUI      },{HID_Z,        L_GUI      }}  },
    {_ik_REDO              , {{HID_Y,    R_GUI | L_SHF  },{HID_Z,    L_GUI | L_SHF  },{HID_Z,    L_GUI | L_SHF  }}  },
    {_ik_BSLASH            , {{0    , 0                 },{HID_NON_US_1,        0   },{HID_NON_US_1,     0      }}  },
    {_ik_HASH              , {{0,                0      },{HID_3,       L_ALT       },{0,0                      }}  },
    {_ik_PIPE              , {{HID_GRAVE,        ALTGR  },{HID_GRAVE,        L_SHF  },{HID_GRAVE,        L_SHF  }}  },
    {_ik_DEGUE             , {{0    , 0                 },{HID_E,       L_ALT       },{HID_E,       L_ALT       }}  },
    {_ik_GRAVE             , {{0    , 0                 },{HID_GRAVE,    L_ALT      },{HID_GRAVE,    L_ALT      }}  },
    {_ik_GREATER           , {{HID_GRAVE,        L_SHF  },{0    , 0                 },{0    , 0                 }}  },
    {_ik_LESS              , {{HID_GRAVE,        0      },{0    , 0                 },{0    , 0                 }}  },
    {_ik_DEGREE            , {{HID_NON_US_2,     L_SHF  },{0    , 0                 },{0    , 0                 }}  },
    {_ik_CARET             , {{HID_NON_US_2,     0      },{0    , 0                 },{0    , 0                 }}  },
    {_ik_SYSTEM_POWER      , {{HID_MAC_POWER,    0      },{HID_MAC_POWER,    0      },{HID_MAC_POWER,    0      }}  }
};
#define MAC_DIFFS_COUNT sizeof(localizedMacDifferences)/sizeof(local_keycode)

PROGMEM static const local_keycode localizationMatrix[_ik_NUMBERoF]   = {
    // Index                  DE                          GB                          US
    {_ik_no                , {{0    , 0                 },{0    , 0                 },{0    , 0                 }}  },
    {_ik_1                 , {{HID_1, 0                 },{HID_1, 0                 },{HID_1, 0                 }}  },
    {_ik_EXCLAM            , {{HID_1, L_SHF             },{HID_1, L_SHF             },{HID_1, L_SHF             }}  },
    {_ik_EXCLAMI           , {{HID_1, ALTGR             },{HID_1, ALTGR             },{HID_1, ALTGR             }}  },
    {_ik_2                 , {{HID_2, 0                 },{HID_2, 0                 },{HID_2, 0                 }}  },
    {_ik_3                 , {{HID_3, 0                 },{HID_3, 0                 },{HID_3, 0                 }}  },
    {_ik_4                 , {{HID_4, 0                 },{HID_4, 0                 },{HID_4, 0                 }}  },
    {_ik_DOLLAR            , {{HID_4, L_SHF             },{HID_4, L_SHF             },{HID_4, L_SHF             }}  },
    {_ik_5                 , {{HID_5, 0                 },{HID_5, 0                 },{HID_5, 0                 }}  },
    {_ik_PERCENT           , {{HID_5, L_SHF             },{HID_5, L_SHF             },{HID_5, L_SHF             }}  },
    {_ik_6                 , {{HID_6, 0                 },{HID_6, 0                 },{HID_6, 0                 }}  },
    {_ik_7                 , {{HID_7, 0                 },{HID_7, 0                 },{HID_7, 0                 }}  },
    {_ik_8                 , {{HID_8, 0                 },{HID_8, 0                 },{HID_8, 0                 }}  },
    {_ik_9                 , {{HID_9, 0                 },{HID_9, 0                 },{HID_9, 0                 }}  },
    {_ik_0                 , {{HID_0, 0                 },{HID_0, 0                 },{HID_0, 0                 }}  },
    {_ik_q                 , {{HID_Q, 0                 },{HID_Q, 0                 },{HID_Q, 0                 }}  },
    {_ik_Q                 , {{HID_Q, L_SHF             },{HID_Q, L_SHF             },{HID_Q, L_SHF             }}  },
    {_ik_w                 , {{HID_W, 0                 },{HID_W, 0                 },{HID_W, 0                 }}  },
    {_ik_W                 , {{HID_W, L_SHF             },{HID_W, L_SHF             },{HID_W, L_SHF             }}  },
    {_ik_e                 , {{HID_E, 0                 },{HID_E, 0                 },{HID_E, 0                 }}  },
    {_ik_E                 , {{HID_E, L_SHF             },{HID_E, L_SHF             },{HID_E, L_SHF             }}  },
    {_ik_r                 , {{HID_R, 0                 },{HID_R, 0                 },{HID_R, 0                 }}  },
    {_ik_R                 , {{HID_R, L_SHF             },{HID_R, L_SHF             },{HID_R, L_SHF             }}  },
    {_ik_t                 , {{HID_T, 0                 },{HID_T, 0                 },{HID_T, 0                 }}  },
    {_ik_T                 , {{HID_T, L_SHF             },{HID_T, L_SHF             },{HID_T, L_SHF             }}  },
    {_ik_u                 , {{HID_U, 0                 },{HID_U, 0                 },{HID_U, 0                 }}  },
    {_ik_U                 , {{HID_U, L_SHF             },{HID_U, L_SHF             },{HID_U, L_SHF             }}  },
    {_ik_i                 , {{HID_I, 0                 },{HID_I, 0                 },{HID_I, 0                 }}  },
    {_ik_I                 , {{HID_I, L_SHF             },{HID_I, L_SHF             },{HID_I, L_SHF             }}  },
    {_ik_o                 , {{HID_O, 0                 },{HID_O, 0                 },{HID_O, 0                 }}  },
    {_ik_O                 , {{HID_O, L_SHF             },{HID_O, L_SHF             },{HID_O, L_SHF             }}  },
    {_ik_p                 , {{HID_P, 0                 },{HID_P, 0                 },{HID_P, 0                 }}  },
    {_ik_P                 , {{HID_P, L_SHF             },{HID_P, L_SHF             },{HID_P, L_SHF             }}  },
    {_ik_a                 , {{HID_A, 0                 },{HID_A, 0                 },{HID_A, 0                 }}  },
    {_ik_A                 , {{HID_A, L_SHF             },{HID_A, L_SHF             },{HID_A, L_SHF             }}  },
    {_ik_s                 , {{HID_S, 0                 },{HID_S, 0                 },{HID_S, 0                 }}  },
    {_ik_S                 , {{HID_S, L_SHF             },{HID_S, L_SHF             },{HID_S, L_SHF             }}  },
    {_ik_d                 , {{HID_D, 0                 },{HID_D, 0                 },{HID_D, 0                 }}  },
    {_ik_D                 , {{HID_D, L_SHF             },{HID_D, L_SHF             },{HID_D, L_SHF             }}  },
    {_ik_f                 , {{HID_F, 0                 },{HID_F, 0                 },{HID_F, 0                 }}  },
    {_ik_F                 , {{HID_F, L_SHF             },{HID_F, L_SHF             },{HID_F, L_SHF             }}  },
    {_ik_g                 , {{HID_G, 0                 },{HID_G, 0                 },{HID_G, 0                 }}  },
    {_ik_G                 , {{HID_G, L_SHF             },{HID_G, L_SHF             },{HID_G, L_SHF             }}  },
    {_ik_h                 , {{HID_H, 0                 },{HID_H, 0                 },{HID_H, 0                 }}  },
    {_ik_H                 , {{HID_H, L_SHF             },{HID_H, L_SHF             },{HID_H, L_SHF             }}  },
    {_ik_j                 , {{HID_J, 0                 },{HID_J, 0                 },{HID_J, 0                 }}  },
    {_ik_J                 , {{HID_J, L_SHF             },{HID_J, L_SHF             },{HID_J, L_SHF             }}  },
    {_ik_k                 , {{HID_K, 0                 },{HID_K, 0                 },{HID_K, 0                 }}  },
    {_ik_K                 , {{HID_K, L_SHF             },{HID_K, L_SHF             },{HID_K, L_SHF             }}  },
    {_ik_l                 , {{HID_L, 0                 },{HID_L, 0                 },{HID_L, 0                 }}  },
    {_ik_L                 , {{HID_L, L_SHF             },{HID_L, L_SHF             },{HID_L, L_SHF             }}  },
    {_ik_x                 , {{HID_X, 0                 },{HID_X, 0                 },{HID_X, 0                 }}  },
    {_ik_X                 , {{HID_X, L_SHF             },{HID_X, L_SHF             },{HID_X, L_SHF             }}  },
    {_ik_c                 , {{HID_C, 0                 },{HID_C, 0                 },{HID_C, 0                 }}  },
    {_ik_C                 , {{HID_C, L_SHF             },{HID_C, L_SHF             },{HID_C, L_SHF             }}  },
    {_ik_v                 , {{HID_V, 0                 },{HID_V, 0                 },{HID_V, 0                 }}  },
    {_ik_V                 , {{HID_V, L_SHF             },{HID_V, L_SHF             },{HID_V, L_SHF             }}  },
    {_ik_b                 , {{HID_B, 0                 },{HID_B, 0                 },{HID_B, 0                 }}  },
    {_ik_B                 , {{HID_B, L_SHF             },{HID_B, L_SHF             },{HID_B, L_SHF             }}  },
    {_ik_n                 , {{HID_N, 0                 },{HID_N, 0                 },{HID_N, 0                 }}  },
    {_ik_N                 , {{HID_N, L_SHF             },{HID_N, L_SHF             },{HID_N, L_SHF             }}  },
    {_ik_m                 , {{HID_M, 0                 },{HID_M, 0                 },{HID_M, 0                 }}  },
    {_ik_M                 , {{HID_M, L_SHF             },{HID_M, L_SHF             },{HID_M, L_SHF             }}  },
    {_ik_CAPS              , {{HID_CAPS_LOCK,0          },{HID_CAPS_LOCK,0          },{HID_CAPS_LOCK,0          }}  },
    {_ik_APP               , {{HID_APPLICATION, 0       },{HID_APPLICATION, 0       },{HID_APPLICATION, 0       }}  },
    {_ik_BSPACE            , {{HID_BACKSPACE,0          },{HID_BACKSPACE,0          },{HID_BACKSPACE,0          }}  },
    {_ik_TAB               , {{HID_TAB,      0          },{HID_TAB,      0          },{HID_TAB,      0          }}  },
    {_ik_noN_US_1          , {{HID_NON_US_1, 0          },{HID_NON_US_1, 0          },{HID_NON_US_1, 0          }}  },
    {_ik_noN_US_2          , {{HID_NON_US_2, 0          },{HID_NON_US_2, 0          },{HID_NON_US_2, 0          }}  },
    {_ik_ENTER             , {{HID_ENTER,    0          },{HID_ENTER,    0          },{HID_ENTER,    0          }}  },
    {_ik_COMMA             , {{HID_COMMA,    0          },{HID_COMMA,    0          },{HID_COMMA,    0          }}  },
    {_ik_PERIOD            , {{HID_PERIOD,   0          },{HID_PERIOD,   0          },{HID_PERIOD,   0          }}  },
    {_ik_DOT3              , {{HID_PERIOD,   ALTGR      },{HID_PERIOD,   ALTGR      },{HID_PERIOD,   ALTGR      }}  },
    {_ik_SPACE             , {{HID_SPACE,    0          },{HID_SPACE,    0          },{HID_SPACE,    0          }}  },
    {_ik_L_SHIFT           , {{HID_L_SHIFT,  MOD_L_SHIFT},{HID_L_SHIFT,  MOD_L_SHIFT},{HID_L_SHIFT,  MOD_L_SHIFT}}  },
    {_ik_R_SHIFT           , {{HID_R_SHIFT,  MOD_R_SHIFT},{HID_R_SHIFT,  MOD_R_SHIFT},{HID_R_SHIFT,  MOD_R_SHIFT}}  },
    {_ik_L_CTRL            , {{HID_L_CONTROL,MOD_L_CTRL },{HID_L_CONTROL,MOD_L_CTRL },{HID_L_CONTROL,MOD_L_CTRL }}  },
    {_ik_R_CTRL            , {{HID_R_CONTROL,MOD_R_CTRL },{HID_R_CONTROL,MOD_R_CTRL },{HID_R_CONTROL,MOD_R_CTRL }}  },
    {_ik_L_ALT             , {{HID_L_ALT,    MOD_L_ALT  },{HID_L_ALT,    MOD_L_ALT  },{HID_L_ALT,    MOD_L_ALT  }}  },
    {_ik_R_ALT/*_ik_ALTGR*/, {{HID_R_ALT,    MOD_R_ALT  },{HID_R_ALT,    MOD_R_ALT  },{HID_R_ALT,    MOD_R_ALT  }}  },
    {_ik_L_GUI             , {{HID_L_GUI,    MOD_L_GUI  },{HID_L_GUI,    MOD_L_GUI  },{HID_L_GUI,    MOD_L_GUI  }}  },
    {_ik_R_GUI             , {{HID_R_GUI,    MOD_R_GUI  },{HID_R_GUI,    MOD_R_GUI  },{HID_R_GUI,    MOD_R_GUI  }}  },
    {_ik_MOD_0             , {{HID_NO_KEY,   MOD_LAYER_0},{HID_NO_KEY,   MOD_LAYER_0},{HID_NO_KEY,   MOD_LAYER_0}}  },
    {_ik_MOD_1             , {{HID_NO_KEY,   MOD_LAYER_1},{HID_NO_KEY,   MOD_LAYER_1},{HID_NO_KEY,   MOD_LAYER_1}}  },
    {_ik_MOD_2             , {{HID_NO_KEY,   MOD_LAYER_2},{HID_NO_KEY,   MOD_LAYER_2},{HID_NO_KEY,   MOD_LAYER_2}}  },
    {_ik_MOD_3             , {{HID_NO_KEY,   MOD_LAYER_3},{HID_NO_KEY,   MOD_LAYER_3},{HID_NO_KEY,   MOD_LAYER_3}}  },
    {_ik_COMPOSE           , {{HID_NO_KEY,   MOD_COMPOSE},{HID_NO_KEY,   MOD_COMPOSE},{HID_NO_KEY,   MOD_COMPOSE}}  },
    {_ik_INS               , {{HID_INSERT,   0          },{HID_INSERT,   0          },{HID_INSERT,   0          }}  },
    {_ik_DEL               , {{HID_DELETE,   0          },{HID_DELETE,   0          },{HID_DELETE,   0          }}  },
    {_ik_LEFT              , {{HID_LEFT,     0          },{HID_LEFT,     0          },{HID_LEFT,     0          }}  },
    {_ik_HOME              , {{HID_HOME,     0          },{HID_HOME,     0          },{HID_HOME,     0          }}  },
    {_ik_END               , {{HID_END,      0          },{HID_END,      0          },{HID_END,      0          }}  },
    {_ik_UP                , {{HID_UP,       0          },{HID_UP,       0          },{HID_UP,       0          }}  },
    {_ik_DOWN              , {{HID_DOWN,     0          },{HID_DOWN,     0          },{HID_DOWN,     0          }}  },
    {_ik_PGUP              , {{HID_PAGE_UP,  0          },{HID_PAGE_UP,  0          },{HID_PAGE_UP,  0          }}  },
    {_ik_PGDN              , {{HID_PAGE_DOWN,0          },{HID_PAGE_DOWN,0          },{HID_PAGE_DOWN,0          }}  },
    {_ik_RIGHT             , {{HID_RIGHT,    0          },{HID_RIGHT,    0          },{HID_RIGHT,    0          }}  },
    {_ik_NUMLOCK           , {{HID_NUM_LOCK,0           },{HID_NUM_LOCK,0           },{HID_NUM_LOCK,0           }}  },
    {_ik_PRTSC             , {{HID_PRINTSCREEN,0        },{HID_PRINTSCREEN,0        },{HID_PRINTSCREEN,0        }}  },
    {_ik_ESC               , {{HID_ESC, 0               },{HID_ESC, 0               },{HID_ESC, 0               }}  },
    {_ik_F1                , {{HID_F1,  0               },{HID_F1,  0               },{HID_F1,  0               }}  },
    {_ik_F2                , {{HID_F2,  0               },{HID_F2,  0               },{HID_F2,  0               }}  },
    {_ik_F3                , {{HID_F3,  0               },{HID_F3,  0               },{HID_F3,  0               }}  },
    {_ik_F4                , {{HID_F4,  0               },{HID_F4,  0               },{HID_F4,  0               }}  },
    {_ik_F5                , {{HID_F5,  0               },{HID_F5,  0               },{HID_F5,  0               }}  },
    {_ik_F6                , {{HID_F6,  0               },{HID_F6,  0               },{HID_F6,  0               }}  },
    {_ik_F7                , {{HID_F7,  0               },{HID_F7,  0               },{HID_F7,  0               }}  },
    {_ik_F8                , {{HID_F8,  0               },{HID_F8,  0               },{HID_F8,  0               }}  },
    {_ik_F9                , {{HID_F9,  0               },{HID_F9,  0               },{HID_F9,  0               }}  },
    {_ik_F10               , {{HID_F10, 0               },{HID_F10, 0               },{HID_F10, 0               }}  },
    {_ik_F11               , {{HID_F11, 0               },{HID_F11, 0               },{HID_F11, 0               }}  },
    {_ik_F12               , {{HID_F12, 0               },{HID_F12, 0               },{HID_F12, 0               }}  },
    {_ik_SYSTEM_POWER      , {{HID_SYSTEM_POWER_DOWN,0        },{HID_SYSTEM_POWER_DOWN,0        },{HID_SYSTEM_POWER_DOWN,0        }}  },
    {_ik_SYSTEM_SLEEP      , {{HID_SYSTEM_SLEEP,0        },{HID_SYSTEM_SLEEP,0        },{HID_SYSTEM_SLEEP,0        }}  },
    {_ik_SYSTEM_WAKE       , {{HID_SYSTEM_WAKE_UP,0         },{HID_SYSTEM_WAKE_UP,0         },{HID_SYSTEM_WAKE_UP,0         }}  },
    {_ik_AUDIO_MUTE        , {{HID_AUDIO_MUTE,0          },{HID_AUDIO_MUTE,0          },{HID_AUDIO_MUTE,0          }}  },
    {_ik_AUDIO_VOL_UP      , {{HID_AUDIO_VOL_UP,0        },{HID_AUDIO_VOL_UP,0        },{HID_AUDIO_VOL_UP,0        }}  },
    {_ik_AUDIO_VOL_DOWN    , {{HID_AUDIO_VOL_DOWN,0      },{HID_AUDIO_VOL_DOWN,0      },{HID_AUDIO_VOL_DOWN,0      }}  },
    {_ik_MEDIA_NEXT_TRACK  , {{HID_TRANSPORT_NEXT_TRACK,0    },{HID_TRANSPORT_NEXT_TRACK,0    },{HID_TRANSPORT_NEXT_TRACK,0    }}  },
    {_ik_MEDIA_PREV_TRACK  , {{HID_TRANSPORT_PREV_TRACK,0    },{HID_TRANSPORT_PREV_TRACK,0    },{HID_TRANSPORT_PREV_TRACK,0    }}  },
    {_ik_MEDIA_STOP        , {{HID_TRANSPORT_STOP,0          },{HID_TRANSPORT_STOP,0          },{HID_TRANSPORT_STOP,0          }}  },
    {_ik_MEDIA_PLAY_PAUSE  , {{HID_TRANSPORT_PLAY_PAUSE,0    },{HID_TRANSPORT_PLAY_PAUSE,0    },{HID_TRANSPORT_PLAY_PAUSE,0    }}  },
    {_ik_MEDIA_SELECT      , {{HID_AL_CC_CONFIG,0        },{HID_AL_CC_CONFIG,0        },{HID_AL_CC_CONFIG,0        }}  },
    {_ik_MAIL              , {{HID_AL_EMAIL,0                },{HID_AL_EMAIL,0                },{HID_AL_EMAIL,0                }}  },
    {_ik_CALCULATOR        , {{HID_AL_CALCULATOR,0          },{HID_AL_CALCULATOR,0          },{HID_AL_CALCULATOR,0          }}  },
    {_ik_MY_COMPUTER       , {{HID_AL_LOCAL_BROWSER,0         },{HID_AL_LOCAL_BROWSER,0         },{HID_AL_LOCAL_BROWSER,0         }}  },
    {_ik_WWW_SEARCH        , {{HID_AC_SEARCH,0          },{HID_AC_SEARCH,0          },{HID_AC_SEARCH,0          }}  },
    {_ik_WWW_HOME          , {{HID_AC_HOME,0            },{HID_AC_HOME,0            },{HID_AC_HOME,0            }}  },
    {_ik_WWW_BACK          , {{HID_AC_BACK,0            },{HID_AC_BACK,0            },{HID_AC_BACK,0            }}  },
    {_ik_WWW_FORWARD       , {{HID_AC_FORWARD,0         },{HID_AC_FORWARD,0         },{HID_AC_FORWARD,0         }}  },
    {_ik_WWW_STOP          , {{HID_AC_STOP,0            },{HID_AC_STOP,0            },{HID_AC_STOP,0            }}  },
    {_ik_WWW_REFRESH       , {{HID_AC_REFRESH,0         },{HID_AC_REFRESH,0         },{HID_AC_REFRESH,0         }}  },
    {_ik_WWW_FAVORITES     , {{HID_AC_BOOKMARKS,0       },{HID_AC_BOOKMARKS,0       },{HID_AC_BOOKMARKS,0       }}  },
    {_ik_UNDO              , {{HID_Y,        R_CTL      },{HID_Z,        R_CTL      },{HID_Z,        R_CTL      }}  },
    {_ik_REDO              , {{HID_Z,        R_CTL      },{HID_Y,    R_CTL          },{HID_Y,    R_CTL          }}  },
    {_ik_BSLASH            , {{HID_MINUS,        ALTGR  },{HID_NON_US_2,        0   },{HID_BSLASH,    0         }}  },
    {_ik_PIPE              , {{HID_NON_US_2,     ALTGR  },{HID_NON_US_2,     L_SHF  },{HID_BSLASH,       L_SHF  }}  },
    {_ik_GRAVE             , {{HID_EQUAL,        L_SHF  },{HID_GRAVE,        0      },{HID_GRAVE,    0          }}  },
    {_ik_DEGUE             , {{HID_EQUAL,               },{HID_GRAVE,        L_SHF  },{HID_NON_US_2,     L_SHF  }}  },
    {_ik_POUND             , {{HID_4,L_SHF |L_ALT       },{HID_3,L_SHF              },{HID_3,L_SHF              }}  },
    {_ik_SL_QUOTM          , {{HID_B,L_SHF |L_ALT |L_GUI},{HID_3,L_SHF |L_ALT       },{HID_3,L_SHF |L_ALT       }}  },
    {_ik_SR_QUOTM          , {{HID_N,L_SHF |L_ALT |L_GUI},{HID_4,L_SHF |L_ALT       },{HID_4,L_SHF |L_ALT       }}  },
    {_ik_AMPERSAND         , {{HID_6,            L_SHF  },{HID_7,         L_SHF     },{HID_7,         L_SHF     }}  },
    {_ik_ASTERIX           , {{HID_R_BRACKET,    L_SHF  },{HID_8,         L_SHF     },{HID_8,         L_SHF     }}  },
    {_ik_AT                , {{HID_Q,            ALTGR  },{HID_2,         L_SHF     },{HID_2,         L_SHF     }}  },
    {_ik_CARET             , {{HID_GRAVE,        0      },{HID_6,         L_SHF     },{HID_6,         L_SHF     }}  },
    {_ik_COLON             , {{HID_PERIOD,       L_SHF  },{HID_SEMICOLON, L_SHF     },{HID_SEMICOLON, L_SHF     }}  },
    {_ik_DQUOTE            , {{HID_2,            L_SHF  },{HID_QUOTE,     L_SHF     },{HID_QUOTE,     L_SHF     }}  },
    {_ik_EQUAL             , {{HID_0,            L_SHF  },{HID_EQUAL,     0,        },{HID_EQUAL,     0,        }}  },
    {_ik_GREATER           , {{HID_NON_US_2,     L_SHF  },{HID_PERIOD,    L_SHF     },{HID_PERIOD,    L_SHF     }}  },
    {_ik_HASH              , {{HID_BSLASH,       0      },{HID_NON_US_1,    0       },{HID_3,    L_SHF          }}  },
    {_ik_L_BRACE           , {{HID_7,            ALTGR  },{HID_L_BRACKET, L_SHF     },{HID_L_BRACKET, L_SHF     }}  },
    {_ik_L_BRACKET         , {{HID_8,            ALTGR  },{HID_L_BRACKET, 0         },{HID_L_BRACKET, 0         }}  },
    {_ik_LESS              , {{HID_NON_US_2,     0      },{HID_COMMA ,    L_SHF     },{HID_COMMA ,    L_SHF     }}  },
    {_ik_L_PAREN           , {{HID_8,            L_SHF  },{HID_9,         L_SHF     },{HID_9,         L_SHF     }}  },
    {_ik_MINUS             , {{HID_SLASH,        0      },{HID_MINUS,     0         },{HID_MINUS,     0         }}  },
    {_ik_PLUS              , {{HID_R_BRACKET,    0      },{HID_EQUAL,     L_SHF     },{HID_EQUAL,     L_SHF     }}  },
    {_ik_QUESTION          , {{HID_MINUS,        L_SHF  },{HID_SLASH,     L_SHF     },{HID_SLASH,     L_SHF     }}  },
    {_ik_QUESTIONI         , {{HID_MINUS, L_ALT | L_CTL },{HID_SLASH,L_ALT | L_SHF  },{HID_SLASH,L_ALT | L_SHF  }}  },
    {_ik_SQUOTE            , {{HID_NON_US_1,     L_SHF  },{HID_QUOTE,     0         },{HID_QUOTE,     0         }}  },
    {_ik_R_BRACE           , {{HID_0,            ALTGR  },{HID_R_BRACKET, L_SHF     },{HID_R_BRACKET, L_SHF     }}  },
    {_ik_R_BRACKET         , {{HID_9,            ALTGR  },{HID_R_BRACKET, 0         },{HID_R_BRACKET, 0         }}  },
    {_ik_R_PAREN           , {{HID_9,            L_SHF  },{HID_0,         L_SHF     },{HID_0,         L_SHF     }}  },
    {_ik_SCOLON            , {{HID_COMMA,        L_SHF  },{HID_SEMICOLON, 0         },{HID_SEMICOLON, 0         }}  },
    {_ik_SLASH             , {{HID_7,            L_SHF  },{HID_SLASH,     0,        },{HID_SLASH,     0,        }}  },
    {_ik_USCORE            , {{HID_SLASH,        L_SHF  },{HID_MINUS,     L_SHF     },{HID_MINUS,     L_SHF     }}  },
    {_ik_y                 , {{HID_Z,         0         },{HID_Y,         0         },{HID_Y,         0         }}  },
    {_ik_Y                 , {{HID_Z,         L_SHF     },{HID_Y,         L_SHF     },{HID_Y,         L_SHF     }}  },
    {_ik_z                 , {{HID_Y,         0         },{HID_Z,         0         },{HID_Z,         0         }}  },
    {_ik_Z                 , {{HID_Y,         L_SHF     },{HID_Z,         L_SHF     },{HID_Z,         L_SHF     }}  },
    {_ik_DEGREE            , {{HID_GRAVE,        L_SHF  },{0    , 0                 },{0    , 0                 }}  },
    {_ik_TILDE             , {{HID_R_BRACKET,    ALTGR  },{HID_NON_US_1,   L_SHF    },{HID_GRAVE,   L_SHF       }}  },
    {_ik_SSHARP            , {{HID_MINUS,        0      },{0    , 0                 },{0    , 0                 }}  },
    {_ik_a_UML             , {{HID_QUOTE,        0      },{0    , 0                 },{0    , 0                 }}  },
    {_ik_A_UML             , {{HID_QUOTE,        L_SHF  },{0    , 0                 },{0    , 0                 }}  },
    {_ik_O_UML             , {{HID_SEMICOLON,    L_SHF  },{0    , 0                 },{0    , 0                 }}  },
    {_ik_o_UML             , {{HID_SEMICOLON,    0      },{0    , 0                 },{0    , 0                 }}  },
    {_ik_U_UML             , {{HID_L_BRACKET,    L_SHF  },{0    , 0                 },{0    , 0                 }}  },
    {_ik_u_UML             , {{HID_L_BRACKET,    0      },{0    , 0                 },{0    , 0                 }}  },
    {_ik_MS_U              , {{ MS_U,            0,     },{ MS_U,            0,     },{ MS_U,            0,     }}  },
    {_ik_MS_D              , {{ MS_D,            0,     },{ MS_D,            0,     },{ MS_D,            0,     }}  },
    {_ik_MS_L              , {{ MS_L,            0,     },{ MS_L,            0,     },{ MS_L,            0,     }}  },
    {_ik_MS_R              , {{ MS_R,            0,     },{ MS_R,            0,     },{ MS_R,            0,     }}  },
    {_ik_MS_W_U            , {{ MS_W_U,          0,     },{ MS_W_U,          0,     },{ MS_W_U,          0,     }}  },
    {_ik_MS_W_D            , {{ MS_W_D,          0,     },{ MS_W_D,          0,     },{ MS_W_D,          0,     }}  },
    {_ik_MS_W_L            , {{ MS_W_L,          0,     },{ MS_W_L,          0,     },{ MS_W_L,          0,     }}  },
    {_ik_MS_W_R            , {{ MS_W_R,          0,     },{ MS_W_R,          0,     },{ MS_W_R,          0,     }}  },
    {_ik_MS_ACC0           , {{ MS_ACC0,         0,     },{ MS_ACC0,         0,     },{ MS_ACC0,         0,     }}  },
    {_ik_MS_ACC1           , {{ MS_ACC1,         0,     },{ MS_ACC1,         0,     },{ MS_ACC1,         0,     }}  },
    {_ik_MS_ACC2           , {{ MS_ACC2,         0,     },{ MS_ACC2,         0,     },{ MS_ACC2,         0,     }}  },
    {_ik_MS_BTN1           , {{ MS_BTN1,         0,     },{ MS_BTN1,         0,     },{ MS_BTN1,         0,     }}  },
    {_ik_MS_BTN2           , {{ MS_BTN2,         0,     },{ MS_BTN2,         0,     },{ MS_BTN2,         0,     }}  },
    {_ik_MS_BTN3           , {{ MS_BTN3,         0,     },{ MS_BTN3,         0,     },{ MS_BTN3,         0,     }}  },
    {_ik_MS_BTN4           , {{ MS_BTN4,         0,     },{ MS_BTN4,         0,     },{ MS_BTN4,         0,     }}  },
    {_ik_MS_BTN5           , {{ MS_BTN5,         0,     },{ MS_BTN5,         0,     },{ MS_BTN5,         0,     }}  }
};


#endif

