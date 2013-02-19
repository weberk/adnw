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


    Debounce code based on code from Peter Dannegger [danni/At/specs/d0t/de]
        described in German at bottom of page
            http://www.mikrocontroller.net/articles/Entprellung
        and discussed at
            http://www.mikrocontroller.net/topic/48465
    Array extensions inspired by Pult.zip
            http://www.mikrocontroller.net/topic/48465#1489399

*/

#include <limits.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "Keyboard.h"
#include "keyboard_class.h"

#include "keymap.h"
#include "mousekey.h"
#include "macro.h"
#include "matrix.h"
#include "command.h"
#include "jump_bootloader.h"

uint16_t lastKeyCode;
uint16_t rowData[ROWS];
uint16_t prevRowData[ROWS];

/**
 * SecondUseToggle is a simple state machine that enables keys to:
 * 1) emit a normal keycode, including its modifiers, if pressed without any other key being
 *         held down AND immediately released again.
 * 2) act as a modifier if pressed together with another normal key.

 * This enables keys in good locations (e.g. thumb buttons) to be used either as frequent keys
 * such as space, return or backspace to also act as layer or control modifiers, thus minimizing
 * finger travel across the board.
 *
 */
typedef enum {
    SECOND_USE_OFF ,
    SECOND_USE_ACTIVE ,
    SECOND_USE_REPEAT ,
    SECOND_USE_PASSIVE
} SecondUse_State;
typedef enum {
    MOD_TRANS_ON ,
    DELAY_MOD_TRANS
} ModifierTransmission_State;

#define SECOND_USE_TIMEOUT 30 // = x/61 [s]: a modekey will remain modifier key if pressed this long; if released earlier the second use normal key is signaled
uint32_t    secondUse_timer;
SecondUse_State secondUse_state=SECOND_USE_OFF;
SecondUse_State secondUse_state_prev=SECOND_USE_OFF;
ModifierTransmission_State prev_modTrans_state = DELAY_MOD_TRANS;
uint8_t modTrans_prev_Mods = 0;
struct Key  secondUse_key;

#define REPEAT_GESTURE_TIMEOUT 30 // = x/61 [s]: a modekey will remain modifier key if pressed this long; if released earlier the second use normal key is signaled
uint32_t    repeatGesture_timer;


/// debounce variables
volatile uint16_t kb_state[ROWS];    // debounced and inverted key state: bit = 1: key pressed
volatile uint16_t kb_press[ROWS];    // key press detect
volatile uint16_t kb_release[ROWS];  // key release detect
volatile uint16_t kb_rpt[ROWS];      // key long press and repeat

static uint16_t ct0[ROWS], ct1[ROWS];
static int32_t rpt[ROWS];

#define ALL_COLS_MASK ((1<<COLS)-1)  // 0x63 or all lower 6 bits
#define REPEAT_MASK    ALL_COLS_MASK // repeat: key0 = 0x3F = 63
#define REPEAT_START   31            // 61 = 1000ms
#define REPEAT_NEXT    15

/**
  * ISR that should get called 61 times a second.
  * Allows exact timers
  */
ISR(TIMER0_OVF_vect)
{
    idle_count++;
    /// @todo What happens on overflow? with 61/s and 16bit=65536
    // (2^15-1)/61/60        ~= 9 minutes till overflow
    // (2^31-1)/61/60/60/24   = 407 days should suffice...
    if(idle_count<0)
        idle_count=0;
}

/**
 * Some startup initialization is performed here.
 */
void initKeyboard()
{
    idle_count=0;
    // not strictly necessary
    for (uint8_t row = 0; row < ROWS; ++row) {
        rowData[row]=0;
        ct0[row]=0xFF;
        ct1[row]=0xFF;
    }

    g_mouse_keys_enabled = 0;
    g_mouse_keys = 0;
    secondUse_timer=idle_count + SECOND_USE_TIMEOUT;

#ifdef DEBUG_OUTPUT
    stdio_init();
#endif
    init_cols();

    initMacros();
}

void clearRowData() {
    for (uint8_t row = 0; row < ROWS; ++row) {
        rowData[row]=0;
        ct0[row]=0xFF;
        ct1[row]=0xFF;
    }
}

//void send_extra(void){
//  USB_ExtraReport_Data_t report_data = {
//      .report_id = REPORT_ID_CONSUMER,
//      .usage = 0
//  };
//  static uint16_t prevRowData[ROWS];
//  bool changeInMatrixDetected=false;
//
//  uint16_t consumer_code = 0;
//  uint16_t system_code = 0;
//  uint8_t code = 0;
//  uint8_t idx=0;
//
//  // scan for changes:
//  for (uint8_t row = 0; row < ROWS; ++row) {
//    if (rowData[row] != prevRowData[row]){
//      changeInMatrixDetected = true;
//    }
//    prevRowData[row] = rowData[row];
//  }
//
//  // scan keys
//  for(uint8_t i=0; i < activeKeys.keycnt; ++i) {
//      struct Key k=activeKeys.keys[i];
//      if(k.normalKey && idx < 6) {
//          code=getKeyCode(k.row, k.col, getActiveLayer());
//          idx++;
//      }
//      if(idx>6) {
//          printf("\nError: more than 6 keys! ");
//          break;
//      }
//  }
//
//  // System Control
//   if (code == KB_SYSTEM_POWER) {
//      system_code = SYSTEM_POWER_DOWN;
//  } else if (code == KB_SYSTEM_SLEEP) {
//      system_code = SYSTEM_SLEEP;
//  } else if (code == KB_SYSTEM_WAKE) {
//      system_code = SYSTEM_WAKE_UP;
//  }
//  // Consumer Page
//  else if (code == KB_AUDIO_MUTE) {
//      consumer_code = AUDIO_MUTE;
//  } else if (code == KB_AUDIO_VOL_UP) {
//      consumer_code = AUDIO_VOL_UP;
//  } else if (code == KB_AUDIO_VOL_DOWN) {
//      consumer_code = AUDIO_VOL_DOWN;
//  }
//  else if (code == KB_MEDIA_NEXT_TRACK) {
//      consumer_code = TRANSPORT_NEXT_TRACK;
//  } else if (code == KB_MEDIA_PREV_TRACK) {
//      consumer_code = TRANSPORT_PREV_TRACK;
//  } else if (code == KB_MEDIA_STOP) {
//      consumer_code = TRANSPORT_STOP;
//  } else if (code == KB_MEDIA_PLAY_PAUSE) {
//      consumer_code = TRANSPORT_PLAY_PAUSE;
//  } else if (code == KB_MEDIA_SELECT) {
//      consumer_code = AL_CC_CONFIG;
//  }
//  else if (code == KB_MAIL) {
//      consumer_code = AL_EMAIL;
//  } else if (code == KB_CALCULATOR) {
//      consumer_code = AL_CALCULATOR;
//  } else if (code == KB_MY_COMPUTER) {
//      consumer_code = AL_LOCAL_BROWSER;
//  }
//  else if (code == KB_WWW_SEARCH) {
//      consumer_code = AC_SEARCH;
//  } else if (code == KB_WWW_HOME) {
//      consumer_code = AC_HOME;
//  } else if (code == KB_WWW_BACK) {
//      consumer_code = AC_BACK;
//  } else if (code == KB_WWW_FORWARD) {
//      consumer_code = AC_FORWARD;
//  } else if (code == KB_WWW_STOP) {
//      consumer_code = AC_STOP;
//  } else if (code == KB_WWW_REFRESH) {
//      consumer_code = AC_REFRESH;
//  } else if (code == KB_WWW_FAVORITES) {
//      consumer_code = AC_BOOKMARKS;
//  }
//
//  // fill report
//   if (system_code != 0){
//     report_data.report_id=REPORT_ID_SYSTEM;
//     report_data.usage=system_code;
//   }
//   else { // fill in consumer code or empty report (consumer_code=0)
//     report_data.report_id=REPORT_ID_CONSUMER;
//     report_data.usage=consumer_code;
//   }
//
//   // send
//   if ((system_code + consumer_code > 0) &&
//       changeInMatrixDetected) {
//     Endpoint_SelectEndpoint(EXTRA_IN_EPADDR);
//     if (Endpoint_IsReadWriteAllowed()) {
//       Endpoint_Write_Stream_LE(&report_data, sizeof(USB_ExtraReport_Data_t), NULL);
//       Endpoint_ClearIN();
//       printf("\n extra send %x",system_code + consumer_code);
//     }
//   }
//}


uint8_t getExtraReport(USB_ExtraReport_Data_t *report_data)
{
    uint16_t consumer_code = 0;
    uint16_t system_code = 0;
    uint16_t code = 0;

    // scan keys
    clearActiveKeys();
    scan_matrix();
    init_active_keys();

    if(activeKeys.keycnt==0) {
        // also need to reset MOUSEKEY
        mousekey_activate(0);
    }

    // no keys or macromode or command mode
    // then send empty report
    if(activeKeys.keycnt==0 ||
            macroMode() ||
            commandMode()) {
        // empty report
        report_data->report_id=REPORT_ID_CONSUMER;
        report_data->usage=0;
        return sizeof(USB_ExtraReport_Data_t);
    }

    for(uint8_t i=0; i < activeKeys.keycnt; ++i) {
        struct Key k=activeKeys.keys[i];
        if(k.normalKey &&
                (USAGE_PAGE(code) != page_keyboard)) {
            code=getKeyCode(k.row, k.col, getActiveLayer());
            break;
        }
    }


    // System Control
    if (USAGE_PAGE(code) == page_system) {
        system_code = USAGE_ID(code);
        report_data->report_id=REPORT_ID_SYSTEM;
        report_data->usage=system_code;
    }
    // Consumer Page
    else if (USAGE_PAGE(code) == page_consumer) {
        consumer_code = USAGE_ID(code);
        report_data->report_id=REPORT_ID_CONSUMER;
        report_data->usage=consumer_code;
    }
    else { // fill in empty report (consumer_code=0)
        report_data->report_id=REPORT_ID_CONSUMER;
        report_data->usage=0;
    }

    return sizeof(USB_ExtraReport_Data_t);
}


// Save all currently pressed keys for later evaluation
void fill_secondUse_Prev_activeKeys(void) {
    secondUse_Prev_activeKeys.keycnt = activeKeys.keycnt;
    for (uint8_t i = 0; i < activeKeys.keycnt; ++i) {
        secondUse_Prev_activeKeys.keys[i] = activeKeys.keys[i];
    }
}

// Updates new and previous state and prints a debug message
void changeSecondUseState(SecondUse_State currentState, SecondUse_State newState) {
    char * stateStr;
    if (currentState != newState) {
        secondUse_state = newState;
        secondUse_state_prev = currentState;
        if (secondUse_state == SECOND_USE_ACTIVE) stateStr = "Active";
        if (secondUse_state == SECOND_USE_PASSIVE) stateStr = "Passive";
        if (secondUse_state == SECOND_USE_REPEAT) stateStr = "Repeat";
        if (secondUse_state == SECOND_USE_OFF) stateStr = "Off";
        TRACE("\n2nd: -> %s",stateStr);
    }
}

// Send out necessary modifiers
void handleModifierTransmission(USB_KeyboardReport_Data_t* report_data, ModifierTransmission_State newState) {
    switch( newState ) {
        case MOD_TRANS_ON:
            // remember sent mods to be able to repeat them later
            modTrans_prev_Mods = report_data->Modifier;
            break;

        case DELAY_MOD_TRANS:
            report_data->Modifier = modTrans_prev_Mods;
            break;

        default:    // invalid state, should not happen!
            TRACE("ModifierTransmission: illegal state");
            break;
    }

    if (prev_modTrans_state != newState) {
        char * stateStr;
        prev_modTrans_state = newState;
        if (newState == MOD_TRANS_ON) stateStr = "TRANS_ON";
        if (newState == DELAY_MOD_TRANS) stateStr = "DELAY";
        TRACE("; Mod -> %s\n",stateStr);
    }
}

void handleSecondaryKeyUsage(USB_KeyboardReport_Data_t* report_data) {

    switch( secondUse_state ) {
        case SECOND_USE_REPEAT:
        {
            if( activeKeys.keycnt==1 ) { // only one => previously determined key to repeat still pressed
                memset(&report_data->KeyCode[0], 0, 6);
                report_data->Modifier=0;
                report_data->KeyCode[0] = SecondaryUsage[activeKeys.keys[0].row][activeKeys.keys[0].col];
                changeSecondUseState(SECOND_USE_REPEAT, SECOND_USE_REPEAT);
                break;
            } else {  // repeated key was released
                repeatGesture_timer = idle_count;
                changeSecondUseState(SECOND_USE_REPEAT, SECOND_USE_OFF);
            }
        }
        case SECOND_USE_OFF:
        {
            if( activeKeys.keycnt==1 && ! activeKeys.keys[0].normalKey &&
                0 != SecondaryUsage[activeKeys.keys[0].row][activeKeys.keys[0].col] &&
                activeKeys.keys[0].row == secondUse_Prev_activeKeys.keys[0].row &&
                activeKeys.keys[0].col == secondUse_Prev_activeKeys.keys[0].col &&
                idle_count-repeatGesture_timer < 10 )
            {
                changeSecondUseState(SECOND_USE_OFF, SECOND_USE_REPEAT);
                break;
            }
            bool modifierOrLayerKeyPresent = false;
            // Modifier among pressed keys?
            for (uint8_t i = 0; i < activeKeys.keycnt; ++i) {
                struct Key current_key = activeKeys.keys[i];
                if (!current_key.normalKey) {
                    modifierOrLayerKeyPresent = true;
                    break;
                }
            }

            // activate 2nd-use when modifier is pressed
            if(modifierOrLayerKeyPresent) {
                changeSecondUseState(SECOND_USE_OFF, SECOND_USE_ACTIVE);
                secondUse_timer=idle_count;
                fillReport(report_data);    // prepare to send, but modifiers not just yet
                handleModifierTransmission(report_data, DELAY_MOD_TRANS);
            } else { // normal key / no modifier
                changeSecondUseState(SECOND_USE_OFF, SECOND_USE_OFF);
            }

            fill_secondUse_Prev_activeKeys();
            break;
        }
        case SECOND_USE_ACTIVE:
        {
            bool normalKeyPresent = false;
            // Normal key among pressed ?
            for (uint8_t i = 0; i < activeKeys.keycnt; ++i) {
                struct Key current_key = activeKeys.keys[i];
                if (current_key.normalKey) {
                    normalKeyPresent = true;
                    break;
                }
            }
            // Which key was just released ?
            if (activeKeys.keycnt < secondUse_Prev_activeKeys.keycnt) {
                bool secondUseNecessityFound = false;
                for (uint8_t i = 0; i < activeKeys.keycnt; ++i) {
                    struct Key current_key = activeKeys.keys[i];
                    struct Key previous_key = secondUse_Prev_activeKeys.keys[i];
                    if (!(current_key.col == previous_key.col
                            && current_key.row == previous_key.row)) {
                        secondUseNecessityFound = true;
                        secondUse_key = previous_key;
                        break;
                    }
                }
                // the last previously saved key was released
                if (!secondUseNecessityFound) {
                    secondUse_key = secondUse_Prev_activeKeys.keys[secondUse_Prev_activeKeys.keycnt - 1];
                }
                // report without the released key
                fillReport(report_data);
                // secondaryModifierUsageMatrix-Code ermitteln
                uint8_t currentLayoutNr = eeprom_read_byte(&alternateLayoutNr);
                // and add keycode as only keycode
                report_data->KeyCode[0] = USAGE_ID(secondaryModifierUsageMatrix[currentLayoutNr][secondUse_key.row][secondUse_key.col]);;
                //report_data->KeyCode[0] = SecondaryUsage[secondUse_key.row][secondUse_key.col];;
                changeSecondUseState(SECOND_USE_ACTIVE, SECOND_USE_PASSIVE);
                // send remaining modifiers and stop delaying
                handleModifierTransmission(report_data, MOD_TRANS_ON);
                // store pressed keys for next 2nd-Use run
                fill_secondUse_Prev_activeKeys();

                repeatGesture_timer = idle_count;
                break; // end switch
            } // less keys than previously

            // normal key or timeout of secondUse timer ends further second use
            if ( normalKeyPresent || (secondUse_timer + SECOND_USE_TIMEOUT < idle_count) ) {
                changeSecondUseState(SECOND_USE_ACTIVE, SECOND_USE_PASSIVE);
                fillReport(report_data);
                handleModifierTransmission(report_data, MOD_TRANS_ON);
                fill_secondUse_Prev_activeKeys();
                break; // end switch
            }

            // Only MKTs were and still are pressed, do not yet emit them though
            if (!normalKeyPresent && activeKeys.keycnt >= secondUse_Prev_activeKeys.keycnt) {
                if(activeKeys.keycnt > secondUse_Prev_activeKeys.keycnt)
                    secondUse_timer=idle_count;
                changeSecondUseState(SECOND_USE_ACTIVE, SECOND_USE_ACTIVE);
                fillReport(report_data);
                handleModifierTransmission(report_data, DELAY_MOD_TRANS);
                fill_secondUse_Prev_activeKeys();
                break; // end switch
            }
            printf("SecondUse: unhandled event in SECOND_USE_ACTIVE");
            break;
        }

        case SECOND_USE_PASSIVE:
        {
            // number of modifiers now ...
            uint8_t actModNo=0, prevModNo = 0;
            for (uint8_t i = 0; i < activeKeys.keycnt; ++i) {
                struct Key current_key = activeKeys.keys[i];
                if (!current_key.normalKey) {
                    actModNo++;
                }
            }
            // ... and previously
            for (uint8_t i = 0; i < secondUse_Prev_activeKeys.keycnt; ++i) {
                struct Key current_key = secondUse_Prev_activeKeys.keys[i];
                if (!current_key.normalKey) {
                    prevModNo++;
                }
            }
            if (activeKeys.keycnt == 0) {  // nothing is pressed
                changeSecondUseState(SECOND_USE_PASSIVE, SECOND_USE_OFF);
                fill_secondUse_Prev_activeKeys();
                break; // end switch
            }
            // was a modifier released ?
            if(actModNo <= prevModNo) {
                changeSecondUseState(SECOND_USE_PASSIVE, SECOND_USE_PASSIVE);
                fillReport(report_data);
                // send modifiers now
                handleModifierTransmission(report_data, MOD_TRANS_ON);
                fill_secondUse_Prev_activeKeys();
                break; // end switch
            }
            // another modifier pressed?
            if(actModNo > prevModNo) {
                changeSecondUseState(SECOND_USE_PASSIVE, SECOND_USE_ACTIVE);
                secondUse_timer=idle_count;
                fillReport(report_data);
                handleModifierTransmission(report_data, DELAY_MOD_TRANS);
                fill_secondUse_Prev_activeKeys();
                break; // end switch
            }
            printf("SecondUse: unhandled event in SECOND_USE_PASSIVE");
            break; // end switch
        }
        default:
            printf("SecondUse: illegal state");
            break;
    }
}


uint8_t getKeyboardReport(USB_KeyboardReport_Data_t *report_data)
{

    clearActiveKeys();
    scan_matrix();

    init_active_keys();


#ifdef ANALOGSTICK
    analogDataAcquire();
#endif

    // send empty report in command mode
    if(commandMode()) {
        handleCommand();
        report_data->Modifier=0;
        memset(&report_data->KeyCode[0], 0, 6);
        return sizeof(USB_KeyboardReport_Data_t);
    }

    handleSecondaryKeyUsage(report_data);
    if( secondUse_state == SECOND_USE_ACTIVE || secondUse_state == SECOND_USE_PASSIVE || secondUse_state == SECOND_USE_REPEAT) {
        // buffer already filled by 2nd-use
        return sizeof(USB_KeyboardReport_Data_t);
    }

    // while macro mode is on, acquire data from it
    if(macroMode()) {
        if(getMacroReport(report_data)) {
            return sizeof(USB_KeyboardReport_Data_t);
        }
    }
    return fillReport(report_data);
}


uint8_t fillReport(USB_KeyboardReport_Data_t *report_data)
{
    if(activeKeys.keycnt==0) {
        // empty report
        memset(&report_data->KeyCode[0], 0, 6 );
        report_data->Modifier=0;
        return sizeof(USB_KeyboardReport_Data_t);
    }

    // if layer is set to MOUSEKEY LAYER
    if(getActiveLayer()==(MOD_MOUSEKEY-MOD_LAYER_0)) {
        uint16_t mk_mask=0;
        for(uint8_t i=0; i < activeKeys.keycnt; ++i) {
            struct Key k=activeKeys.keys[i];
            mk_mask |= (1<<(getKeyCode(k.row, k.col, (MOD_MOUSEKEY-MOD_LAYER_0))-1-MS_BEGIN));
        }
        mousekey_activate(mk_mask);

        // empty report
        // @todo: There could technically be keys on mouse layer, but why?
        memset(&report_data->KeyCode[0], 0, 6 );
        report_data->Modifier=0;
        return sizeof(USB_KeyboardReport_Data_t);
    } else {
        mousekey_activate(0);
    }

    uint8_t idx=0;
    // Alle normalen Tasten einsetzen: Codepage 7
    for(uint8_t i=0; i < activeKeys.keycnt; ++i) {
        struct Key k=activeKeys.keys[i];
        if(k.normalKey && idx < 6) {
            uint16_t code=getKeyCode(k.row, k.col, getActiveLayer());
            if (USAGE_PAGE(code) == page_keyboard) {
                report_data->KeyCode[idx]= USAGE_ID(code);
                idx++;
            }
        }
        if(idx>6) {
            printf("\nError: more than 6 keys! ");
            for( uint8_t k=0; k<6; ++k)
                printf(" %d ", report_data->KeyCode[k]);
            break;
        }
    }

    // Modifier einsetzen
    report_data->Modifier=getActiveModifiers()|getActiveKeyCodeModifier();
    return sizeof(USB_KeyboardReport_Data_t);
}



uint16_t get_kb_release( uint16_t key_mask, uint16_t col)
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        key_mask &= kb_release[col];                      // read key(s)
        kb_release[col] ^= key_mask;                      // clear key(s)
    }
    return key_mask;
}

uint16_t get_kb_press( uint16_t key_mask, uint16_t col )
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        key_mask &= kb_press[col];                      // read key(s)
        kb_press[col] ^= key_mask;                      // clear key(s)
    }
    return key_mask;
}
uint16_t get_kb_rpt( uint16_t key_mask, uint16_t col )
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        key_mask &= kb_rpt[col];                        // read key(s)
        kb_rpt[col] ^= key_mask;                        // clear key(s)
    }
    return key_mask;
}

/** The real hardware access take place here.
 *  Each of the rows is individually activated and the resulting column value read.
 *  Should more than 8 channels be needed, this can easily be extended to 16/32bit.
 *  By means of a neat routine found on http://hackaday.com/2010/11/09/debounce-code-one-post-to-rule-them-all/
 *
 */
void scan_matrix(void)
{
    uint16_t i, data;

    for (uint8_t row = 0; row < ROWS; ++row) {
        activate(row);

        // Insert NOPs for synchronization
        _delay_us(20);

        // Place data on all column pins for active row
        // into a single 32 bit value.
        data = read_col();
        /// @see top comment for source of debounce magic
        // Needs to be adjusted for more than 8 columns
        i = kb_state[row] ^ (~data);                    // key changed ?
        ct0[row] = ~( ct0[row] & i );                   // reset or count ct0
        ct1[row] = ct0[row] ^ (ct1[row] & i);           // reset or count ct1
        i &= ct0[row] & ct1[row];                       // count until roll over ?
        kb_state[row] ^= i;                             // then toggle debounced state

        kb_press  [row] |=  kb_state[row] & i;          // 0->1: key press detect
        kb_release[row] |= ~kb_state[row] & i;          // 1->0: key press detect

        if( (kb_state[row] & REPEAT_MASK) == 0 ) {      // check repeat function
            rpt[row] = idle_count + REPEAT_START;       // start delay
        }
        if(  rpt[row] <= idle_count ) {
            rpt[row] = idle_count + REPEAT_NEXT;        // repeat delay
            kb_rpt[row] |= kb_state[row] & REPEAT_MASK;
        }

        // Now evaluate results
        uint16_t p,r,h;
        p=get_kb_press  (ALL_COLS_MASK, row);
        h=get_kb_rpt    (ALL_COLS_MASK, row);
        r=get_kb_release(ALL_COLS_MASK, row);

        rowData[row] = ((rowData[row]|(p|h)) & ~r);
    }
}


void printCurrentKeys(void)
{

    for(uint8_t i=0; i < activeKeys.keycnt; ++i) {
        struct Key k=activeKeys.keys[i];
        printf("Spalte: %u ; Reihe: %u gedrueckt\n",k.col,k.row);
    }

/*
    for(uint8_t r=0; r<ROWS/2; ++r) {
        printf("\n");
        for(uint8_t c=0; c< COLS; ++c) {
            if( rowData[r] & (1<<c))
                printf("X");
            else
                printf(".");
        }
        printf("|  |");
        for(uint8_t c=0; c< COLS; ++c) {
            if( rowData[r+ROWS/2] & (1<<c))
                printf("X");
            else
                printf(".");
        }
    }
    printf("\n");
*/
}


void clearActiveKeys()
{
    activeKeys.keycnt=0;
}

/// @todo Switch back from mouse layer!
uint8_t getActiveLayer()
{
    TRACE("gAL ");

    uint8_t layer=0;
    for(uint8_t i=0; i < activeKeys.keycnt; ++i) {
        struct Key k = activeKeys.keys[i];
        if( isLayerKey(k.row, k.col) ) {
            if(layer!=0) {
                // printf("\nWARN: More than one layer key pressed!");
            }
            layer += getModifier(k.row, k.col,0)-MOD_LAYER_0;
        }
    }
    return layer;
}

/**
 *  Returns the modifier needed to send first normal key in active keys.
 *  Example: For "@" on a german PC layout "q"+"AltGr" needs to be send to host.
 *  @todo : Where are the other keys parsed? Would need to split a report in case
 *          another modifier is pressed or needed for later characters.
 */
uint8_t getActiveKeyCodeModifier()
{
    TRACE("gAKCM ");
    for(uint8_t i=0; i < activeKeys.keycnt; ++i) {
        struct Key k=activeKeys.keys[i];
        if(k.normalKey) {
            return getModifier(k.row, k.col, getActiveLayer());
        }
    }
    return 0;
}

// Assuming there is only one active key
uint8_t getActiveModifiers()
{
    TRACE("gAM ");
    uint8_t modifiers=0;
    for(uint8_t i=0; i < activeKeys.keycnt; ++i) {
        struct Key k = activeKeys.keys[i];
        if( isModifierKey(k.row, k.col) ) {
            modifiers |= (1 << (getModifier(k.row, k.col,0)-MOD_L_CTRL));
        }
    }
#ifdef ANALOGSTICK
    modifiers |= analogData.mods;
#endif

    return modifiers;
}


/**
  * check whether layer 0 key is a modifier.
  * @todo : keys that are not modifiers in layer 0 cannot be in other layers (but no sensible use case)
  */
bool isModifierKey(uint8_t row, uint8_t col)
{
    TRACE("iMK ");
    if( getModifier(row,col,0) >= MOD_L_CTRL  && getModifier(row,col,0) < MOD_END)
        return true;
    return false;
}

/**
 * check whether layer 0 key is a modifier )
 * @todo : keys that are not modifiers in layer 0 cannot be in other layers (but no sensible use case)
 */
bool isLayerKey(uint8_t row, uint8_t col)
{
    TRACE("iLK ");
    if( getModifier(row,col,0) > MOD_LAYER_0 && getModifier(row,col,0) < MOD_LAYER_LAST) {
        return true;
    }
    return false;
}

bool isNormalKey(uint8_t row, uint8_t col)
{
    TRACE("iNK ");
    return !(isLayerKey(row,col) || isModifierKey(row,col));
}

/**
 * Returns the corresponding mouse hid code, or 0 if none is defined for this matrix position.
 *
 * This enables overiding normal keys when in mouse mode.
 */
uint8_t getMouseKey(uint8_t row, uint8_t col)
{
    uint16_t hid = MouseUsage[row][col];
    if ( hid >= HID_MOUSEBTN_1 && hid <= HID_MOUSEBTN_4 )
        return (hid);
    return 0;
}

/**
 * Appends a row/column pair to the currently active key list unless
 * g_mouse_keys are enabled (for a short while after mouse movement)
 * MKT is either stopped or initialized, depending on the situation.
 */
void ActiveKeys_Add(uint8_t row, uint8_t col)
{
    if(activeKeys.keycnt>= MAX_ACTIVE_KEYS) {
        //printf("ERR: Too many active keys!");
        return;
    }

    struct Key key;
    key.row=row;
    key.col=col;
    key.normalKey = isNormalKey(row,col);

    // quit early if mouse key is pressed in mouse mode, or end it on other keypress.
    if( g_mouse_keys_enabled ) {
        uint8_t btns = getMouseKey(row, col);
        if(btns != 0) {
            g_mouse_keys |= btns;
            return;
        } else if(isNormalKey(row,col)) { // quicker exit from mousekey mode on other key
            g_mouse_keys_enabled = 0;
        }
    }

    activeKeys.keys[activeKeys.keycnt]=key;
    activeKeys.keycnt++;
}

/** key matrix is read into rowData[] at this point,
  * now map all active keys
  */
void init_active_keys()
{
    // only working silently if there are no keycodes sent on first press of cmd combo.
    if(CMD_MODE()) {
        setCommandMode(true);
        return;
    }
    // process row/column data to find the active keys
    for (uint8_t row = 0; row < ROWS; ++row) {
        for (uint8_t col = 0; col < COLS; ++col) {
            if (rowData[row] & (1UL << col)) {
                ActiveKeys_Add(row,col);
            }
        }
    }
}

