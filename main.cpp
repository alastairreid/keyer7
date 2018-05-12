////////////////////////////////////////////////////////////////
// Chording keyboard based on Adafruit BLE M0 Feather
////////////////////////////////////////////////////////////////

#include <bluefruit.h>

////////////////////////////////////////////////////////////////
// USB HID scan codes
////////////////////////////////////////////////////////////////

#define KEY_A           4
#define KEY_B           5
#define KEY_C           6
#define KEY_D           7
#define KEY_E           8
#define KEY_F           9
#define KEY_G           10
#define KEY_H           11
#define KEY_I           12
#define KEY_J           13
#define KEY_K           14
#define KEY_L           15
#define KEY_M           16
#define KEY_N           17
#define KEY_O           18
#define KEY_P           19
#define KEY_Q           20
#define KEY_R           21
#define KEY_S           22
#define KEY_T           23
#define KEY_U           24
#define KEY_V           25
#define KEY_W           26
#define KEY_X           27
#define KEY_Y           28
#define KEY_Z           29
#define KEY_1           30
#define KEY_2           31
#define KEY_3           32
#define KEY_4           33
#define KEY_5           34
#define KEY_6           35
#define KEY_7           36
#define KEY_8           37
#define KEY_9           38
#define KEY_0           39
#define KEY_ENTER       40
#define KEY_ESC         41
#define KEY_BACKSPACE   42
#define KEY_TAB         43
#define KEY_SPACE       44
#define KEY_MINUS       45
#define KEY_EQUAL       46
#define KEY_LEFT_BRACE  47
#define KEY_RIGHT_BRACE 48
#define KEY_BACKSLASH   49
#define KEY_NON_US_NUM  50
#define KEY_SEMICOLON   51
#define KEY_QUOTE       52
#define KEY_TILDE       53
#define KEY_COMMA       54
#define KEY_PERIOD      55
#define KEY_SLASH       56
#define KEY_CAPS_LOCK   57
#define KEY_F1          58
#define KEY_F2          59
#define KEY_F3          60
#define KEY_F4          61
#define KEY_F5          62
#define KEY_F6          63
#define KEY_F7          64
#define KEY_F8          65
#define KEY_F9          66
#define KEY_F10         67
#define KEY_F11         68
#define KEY_F12         69
#define KEY_PRINTSCREEN 70
#define KEY_SCROLL_LOCK 71
#define KEY_PAUSE       72
#define KEY_INSERT      73
#define KEY_HOME        74
#define KEY_PAGE_UP     75
#define KEY_DELETE      76
#define KEY_END         77
#define KEY_PAGE_DOWN   78
#define KEY_RIGHT       79
#define KEY_LEFT        80
#define KEY_DOWN        81
#define KEY_UP          82
#define KEY_NUM_LOCK    83
#define KEYPAD_SLASH    84
#define KEYPAD_ASTERISK 85
#define KEYPAD_MINUS    86
#define KEYPAD_PLUS     87
#define KEYPAD_ENTER    88
#define KEYPAD_1        89
#define KEYPAD_2        90
#define KEYPAD_3        91
#define KEYPAD_4        92
#define KEYPAD_5        93
#define KEYPAD_6        94
#define KEYPAD_7        95
#define KEYPAD_8        96
#define KEYPAD_9        97
#define KEYPAD_0        98
#define KEYPAD_PERIOD   99

#define MOD_LCTRL   (1 <<  8)
#define MOD_LSHIFT  (1 <<  9)
#define MOD_LALT    (1 << 10)
#define MOD_LGUI    (1 << 11)
#define MOD_RCTRL   (1 << 12)
#define MOD_RSHIFT  (1 << 13)
#define MOD_RALT    (1 << 14)
#define MOD_RGUI    (1 << 15)

////////////////////////////////////////////////////////////////
// "Modified NASA" septambic keyer layout
// https://chorder.cs.vassar.edu/doku.php?id=spiffchorder:modified_nasa:chart_alphanumeric_keys
////////////////////////////////////////////////////////////////

// alphabet map
static uint16_t tableA[32] = {
    0,
    KEY_SPACE,
    KEY_I,
    KEY_L,
    KEY_R,
    KEY_C,
    KEY_D,
    KEY_M,

    KEY_Y,
    KEY_G,
    KEY_K,
    KEY_J,
    KEY_H,
    KEY_P,
    KEY_E,
    KEY_A,

    KEY_W,
    KEY_F,
    KEY_B,
    KEY_X,
    KEY_PERIOD,
    KEY_COMMA,
    KEY_QUOTE,
    KEY_SEMICOLON,

    KEY_U,
    KEY_V,
    KEY_Z,
    KEY_Q,
    KEY_S,
    KEY_N,
    KEY_T,
    KEY_O
};

// N prefix map
static uint16_t tableN[32] = {
    // 0
    0,
    KEY_1,
    KEY_2,
    KEY_6,
    KEY_3,
    KEY_7,
    KEY_SLASH,
    KEY_8 | MOD_LSHIFT, // *

    // 8
    KEY_4,
    KEY_8,
    KEY_4 | MOD_LSHIFT, // $
    0, // should be ()
    0, // should be 00
    KEY_5 | MOD_LSHIFT, // %
    KEY_EQUAL,
    KEY_EQUAL | MOD_LSHIFT, // +

    // 16
    KEY_5,
    KEY_9,
    KEY_BACKSLASH,
    KEY_7 | MOD_LSHIFT, // &
    0,
    0,
    0,
    0,

    // 24
    0, // should be ""
    KEY_RIGHT_BRACE,
    KEY_TILDE,              // `
    KEY_SLASH | MOD_LSHIFT, // ?
    KEY_MINUS,
    KEY_LEFT_BRACE,
    0, // should be 000
    KEY_0
};

// F+ map (using F as modifier, no prefix)
static uint16_t tableFmod[16] = {
    0,
    KEY_LEFT,
    KEY_BACKSPACE,
    KEY_UP,

    KEY_RIGHT,
    KEY_TAB,
    KEY_DELETE,
    KEY_PAGE_UP,

    KEY_ENTER,
    KEY_END,
    0,
    0,

    KEY_DOWN,
    KEY_HOME,
    KEY_PAGE_DOWN,
    KEY_CAPS_LOCK
};

// CF+ map (using C+F as modifier, no prefix)
static uint16_t tableCFmod[16] = {
    KEYPAD_PLUS,
    KEYPAD_4,
    KEYPAD_5,
    KEYPAD_8,

    KEYPAD_6,
    KEYPAD_MINUS,
    KEYPAD_PERIOD,
    KEYPAD_9,

    KEYPAD_ENTER,
    KEYPAD_1,
    KEYPAD_ASTERISK,
    KEYPAD_SLASH,

    KEYPAD_2,
    KEYPAD_7,
    KEYPAD_3,
    KEYPAD_0
};

// N+ map (using N as modifier, no prefix)
static uint16_t tableNmod[16] = {
    0,
    0,
    KEY_COMMA,
    0,

    0,
    0,
    KEY_PERIOD,
    KEY_QUOTE,

    KEY_ESC,
    KEY_INSERT,
    0,
    0,

    KEY_SEMICOLON,
    0,
    0,
    0
};

static const bool lefthanded = false;

static uint16_t toUSBCode(uint8_t prefix, uint8_t code) {
    uint8_t NCF = (code >> 4) & 7;
    uint8_t base = 0;
    if (lefthanded) {
        base = code & 0xf;
    } else {
        base = ((code & 8) >> 3)
             | ((code & 4) >> 1)
             | ((code & 2) << 1)
             | ((code & 1) << 3);
    }
    uint8_t index = (base << 1) | ((NCF >> 1) & 1);

    if (prefix == 4) { // N table
        return tableN[index];
    } else if (prefix == 6) { // CN prefix
        uint16_t usb = tableN[index];
        usb = usb | (0x2 << 8);
        return usb;
    } else if (prefix == 1) { // F prefix
        uint16_t usb = tableA[index];
        usb = usb | (0x2 << 8); // shift modifier
        return usb;
    } else if (prefix == 0) { // alphabetic
        if (NCF == 3) { // CF+ table
            return tableCFmod[base];
        } else if (NCF == 1) { // F+ table
            return tableFmod[base];
        } else if (NCF == 4) { // N+ table
            return tableNmod[base];
        } else if (NCF == 0 || NCF == 2) { // A table
            return tableA[index];
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

////////////////////////////////////////////////////////////////
// Dvorak support
//
// If your computer is currently in Software-Dvorak mode,
// you need to apply a reverse mapping before sending the
// USB code to the keyboard.
////////////////////////////////////////////////////////////////

// Mapping of letters to key required if using
// software Dvorak mapping on host device
static uint8_t DvorakTable[128] = {
    [0]               = 0,
    [1]               = 0,
    [2]               = 0,
    [3]               = 0,
    [KEY_A]           = KEY_A,
    [KEY_B]           = KEY_N,
    [KEY_C]           = KEY_I,
    [KEY_D]           = KEY_H,
    [KEY_E]           = KEY_D,
    [KEY_F]           = KEY_Y,
    [KEY_G]           = KEY_U,
    [KEY_H]           = KEY_J,
    [KEY_I]           = KEY_G,
    [KEY_J]           = KEY_C,
    [KEY_K]           = KEY_V,
    [KEY_L]           = KEY_P,
    [KEY_M]           = KEY_M,
    [KEY_N]           = KEY_L,
    [KEY_O]           = KEY_S,
    [KEY_P]           = KEY_R,
    [KEY_Q]           = KEY_X,
    [KEY_R]           = KEY_O,
    [KEY_S]           = KEY_SEMICOLON,
    [KEY_T]           = KEY_K,
    [KEY_U]           = KEY_F,
    [KEY_V]           = KEY_PERIOD,
    [KEY_W]           = KEY_COMMA,
    [KEY_X]           = KEY_B,
    [KEY_Y]           = KEY_T,
    [KEY_Z]           = KEY_SLASH,
    [KEY_1]           = 0,
    [KEY_2]           = 0,
    [KEY_3]           = 0,
    [KEY_4]           = 0,
    [KEY_5]           = 0,
    [KEY_6]           = 0,
    [KEY_7]           = 0,
    [KEY_8]           = 0,
    [KEY_9]           = 0,
    [KEY_0]           = 0,
    [KEY_ENTER]       = 0,
    [KEY_ESC]         = 0,
    [KEY_BACKSPACE]   = 0,
    [KEY_TAB]         = 0,
    [KEY_SPACE]       = 0,
    [KEY_MINUS]       = KEY_QUOTE,
    [KEY_EQUAL]       = KEY_RIGHT_BRACE,
    [KEY_LEFT_BRACE]  = KEY_MINUS,
    [KEY_RIGHT_BRACE] = KEY_EQUAL,
    [KEY_BACKSLASH]   = KEY_BACKSLASH,
    [KEY_NON_US_NUM]  = 0,
    [KEY_SEMICOLON]   = KEY_Z,
    [KEY_QUOTE]       = KEY_Q,
    [KEY_TILDE]       = KEY_TILDE,
    [KEY_COMMA]       = KEY_W,
    [KEY_PERIOD]      = KEY_E,
    [KEY_SLASH]       = KEY_LEFT_BRACE,
};

static uint8_t toDvorak(uint8_t code) {
    if (code < 0x80) {
        uint8_t r = DvorakTable[code];
        if (r) return r;
    }
    return code;
}

////////////////////////////////////////////////////////////////
// Bluetooth support
////////////////////////////////////////////////////////////////

BLEDis bledis;
BLEHidAdafruit blehid;

void startAdvertising(void)
{
    // Advertising packet
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);

    // Include BLE HID service
    Bluefruit.Advertising.addService(blehid);

    // There is enough room for the dev name in the advertising packet
    Bluefruit.Advertising.addName();

    /* Start Advertising
     * - Enable auto advertising if disconnected
     * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
     * - Timeout for fast mode is 30 seconds
     * - Start(timeout) with timeout = 0 will advertise forever (until connected)
     * 
     * For recommended advertising interval
     * https://developer.apple.com/library/content/qa/qa1931/_index.html   
     */
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
    Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

void initBluetooth() {
    Bluefruit.begin();
    // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
    Bluefruit.setTxPower(4);
    Bluefruit.setName("Keyer7");

    // Configure and Start Device Information Service
    bledis.setManufacturer("Haggis Industries");
    bledis.setModel("Haggis Septambic Keyer");
    bledis.begin();

    /* Start BLE HID
     * Note: Apple requires BLE device must have min connection interval >= 20m
     * ( The smaller the connection interval the faster we could send data).
     * However for HID and MIDI device, Apple could accept min connection interval 
     * up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
     * connection interval to 11.25  ms and 15 ms respectively for best performance.
     */
    blehid.begin();

    /* Set connection interval (min, max) to your perferred value.
     * Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
     * min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms 
     */
    /* Bluefruit.setConnInterval(9, 12); */

    // Set up and start advertising
    startAdvertising();
}

static boolean software_dvorak = false;

static void sendcode(uint8_t modifiers, uint8_t code) {
    if (software_dvorak) { // apply reverse Dvorak mapping
        code = toDvorak(code);
    }

    blehid.keyboardReport(modifiers, code, 0, 0, 0, 0, 0);
    delay(5);
    blehid.keyboardReport(0, 0, 0, 0, 0, 0, 0);
}

////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////

#define NUMKEYS 7
#define DEBOUNCE 30

static uint8_t keys[NUMKEYS];

// time each key has been pressed
static uint32_t time[NUMKEYS];

// which pin is each key attached to?
// (in order PRMI NCF)
static uint8_t pin[NUMKEYS] = {
    PIN_A0, PIN_A1, PIN_A2, PIN_A3,
    PIN_SPI_SCK, PIN_A5, PIN_A4
};

static void initKeys() {
    // setup input pins
    for(int i = 0; i < NUMKEYS; ++i) {
        pinMode(pin[i], INPUT_PULLUP);
    }

    // clear record of pressed keys
    for (int i = 0; i < NUMKEYS; ++i) {
        keys[i] = 0;
    }

    // init timeouts
    for(int i = 0; i < NUMKEYS; ++i) {
        time[i] = 0;
    }
}

// debounced key read
static bool readkey(int k) {
    if (digitalRead(pin[k]) == LOW) {
        if (time[k] >= DEBOUNCE) {
            return true;
        } else {
            time[k]++;
        }
    } else {
        time[k] = 0;
    }
    return false;
}

// read all keys (raw, without chording applied)
static uint8_t readkeys() {
    uint8_t keys = 0;
    for(int i = 0; i < NUMKEYS; ++i) {
        if (readkey(i)) {
            keys |= (1 << i);
        }
    }
    return keys;
}

// read chords
// A chord only registers as you release keys, otherwise it reads as 0
// This requires us to keep track of which phase we are in:
// - still pressing keys: don't register chord yet
// - _just_ started to release keys: register chord
static uint8_t readchord() {
    static uint8_t prev = 0;
    static bool pressing = true;  // phase: pressing or releasing?
    uint8_t keys  = readkeys();
    uint8_t chord = 0;
    if (prev &~ keys) { // released at least one key
        if (pressing) { // this is the first key released
            pressing = false;
            chord = prev;
        }
    } else if (keys &~ prev) { // pressed at least one new key
        if (!pressing) {
            pressing = true;
        }
    }
    prev = keys;
    return chord;
}


////////////////////////////////////////////////////////////////
// Main body of program
////////////////////////////////////////////////////////////////

void setup() {
    initKeys();
    initBluetooth();
}

static uint8_t prefix = 0;

void loop() {
    uint8_t code = readchord();
    if (code != 0) {
        if ((code != 0x20) && ((code & 0xf) == 0)) {
            prefix = (code >> 4) & 0x7;
            if (prefix == 7) {
                software_dvorak = true;
                prefix = 0;
            } else if (prefix == 5) {
                software_dvorak = false;
                prefix = 0;
            }
        } else {
            uint16_t usb = toUSBCode(prefix, code);
            if (usb != 0) {
                sendcode((usb >> 8) & 0xf, usb & 0x7f);
            }
            prefix = 0;
        }
    }
    delay(5);

    // Turn off that bright blue LED
    digitalWrite(LED_CONN, LOW);

    // Request CPU to enter low-power mode until an event/interrupt occurs
    waitForEvent();
}

////////////////////////////////////////////////////////////////
// End
////////////////////////////////////////////////////////////////
