#include <stddef.h>
#include <stdint.h>

// this file is our keyboard driver 
#define KBD_DATA_PORT   0x60

// we need some map of the scan codes to the assigned character
// ignore modifier and special keys for now ig.

// also in the future do this:
// keep a map in memory of all keys pressed, the interrupt will on press release edit the map to show pressed or released when released.

// all of the definitions will also be here for funsys
#define RELEASE_KEY(base) (base + 0x128)

#define ESC_KEY 1
#define F1_KEY 59
#define F2_KEY 60
#define F3_KEY 61
#define F4_KEY 62
#define F5_KEY 63
#define F6_KEY 64
#define F7_KEY 65
#define F8_KEY 66
#define F9_KEY 67
#define F10_KEY 68
#define F11_KEY 87
#define F12_KEY 88
#define SCROLL_LOCK_KEY 70
#define PB_KEY 255 // this is not right
#define TILDE_KEY 41
#define ONE_KEY 2
#define TWO_KEY 3
#define THREE_KEY 4
#define FOUR_KEY 5
#define FIVE_KEY 6
#define SIX_KEY 7
#define SEVEN_KEY 8
#define EIGHT_KEY 9
#define NINE_KEY 10
#define ZERO_KEY 11
#define MINUS_KEY 12
#define EQUAL_KEY 13
#define BACKSPACE_KEY 14
#define INSERT_KEY 82
#define HOME_KEY 71
#define PAGE_UP_KEY 73
#define TAB_KEY 15
#define Q_KEY 16
#define W_KEY 17
#define E_KEY 18
#define R_KEY 19
#define T_KEY 20
#define Y_KEY 21
#define U_KEY 22
#define I_KEY 23
#define O_KEY 24
#define P_KEY 25
#define LEFT_SQUARE_BRACKET_KEY 26
#define RIGHT_SQUARE_BRACKET_KEY 27
#define BACKSLASH_KEY 43
#define CAPSLOCK_KEY 58
#define A_KEY 30
#define S_KEY 31
#define D_KEY 32
#define F_KEY 33
#define G_KEY 34
#define H_KEY 35
#define J_KEY 36
#define K_KEY 37
#define L_KEY 38
#define SEMICOLON_KEY 39
#define APOSTROPHE_KEY 40
#define ENTER_KEY 28
#define LEFT_SHIFT 42
#define Z_KEY 44
#define X_KEY 45
#define C_KEY 46
#define V_KEY 47
#define B_KEY 48
#define N_KEY 49
#define M_KEY 50
#define COMMA_KEY 51
#define FULLSTOP_KEY 52
#define FORWARD_SLASH_KEY 53
#define RIGHT_SHIFT_KEY 54
#define CONTROL_KEY 29
#define WINDOWS_KEY 91 // no clue
#define ALT_KEY 56
#define SPACEBAR_KEY 57

// arrow keys and most modifiers for some reason use
// multiple bytes to encode the press?.

// our first prototype probably deprecated soon
unsigned char scanned_letter_keyboard(unsigned char byte);

