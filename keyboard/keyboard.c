#include "../keyboard.h"
unsigned char scanned_letter_keyboard(unsigned char byte){
    char key = '?';
    switch(byte){
    case ESC_KEY:
        break;
    case F1_KEY:
        break;
    case F2_KEY:
        break;
    case F3_KEY:
        break;
    case F4_KEY:
        break;
    case F5_KEY:
        break;
    case F6_KEY:
        break;
    case F7_KEY:
        break;
    case F8_KEY:
        break;
    case F9_KEY:
        break;
    case F10_KEY:
        break;
    case F11_KEY:
        break;
    case F12_KEY:
        break;
    case SCROLL_LOCK_KEY:
        break;
    case PB_KEY:
        break;
    case TILDE_KEY:
        return '~';
        break;
    case ONE_KEY:
        return '1';
        break;
    case TWO_KEY:
        return '2';
        break;
    case THREE_KEY:
        return '3';
        break;
    case FOUR_KEY:
        return '4';
        break;
    case FIVE_KEY:
        return '5';
        break;
    case SIX_KEY:
        return '6';
        break;
    case SEVEN_KEY:
        return '7';
        break;
    case EIGHT_KEY:
        return '8';
        break;
    case NINE_KEY:
        return '9';
        break;
    case ZERO_KEY:
        return '0';
        break;
    case MINUS_KEY:
        return '-';
        break;
    case EQUAL_KEY:
        return '=';
        break;
    case BACKSPACE_KEY:
        break;
    case INSERT_KEY:
        break;
    case HOME_KEY:
        break;
    case PAGE_UP_KEY:
        break;
    case TAB_KEY:
        return '\t';
        break;
    case Q_KEY:
        return 'q';
        break;
    case W_KEY:
        return 'w';
        break;
    case E_KEY:
        return 'e';
        break;
    case R_KEY:
        return 'r';
        break;
    case T_KEY:
        return 't';
        break;
    case Y_KEY:
        return 'y';
        break;
    case U_KEY:
        return 'u';
        break;
    case I_KEY:
        return 'i';
        break;
    case O_KEY:
        return 'o';
        break;
    case P_KEY:
        return 'p';
        break;
    case LEFT_SQUARE_BRACKET_KEY:
        return '[';
        break;
    case RIGHT_SQUARE_BRACKET_KEY:
        return ']';
        break;
    case BACKSLASH_KEY:
        return '\\';
        break;
    case CAPSLOCK_KEY:
        break;
    case A_KEY:
        return 'a';
        break;
    case S_KEY:
        return 's';
        break;
    case D_KEY:
        return 'd';
        break;
    case F_KEY:
        return 'f';
        break;
    case G_KEY:
        return 'g';
        break;
    case H_KEY:
        return 'h';
        break;
    case J_KEY:
        return 'j';
        break;
    case K_KEY:
        return 'k';
        break;
    case L_KEY:
        return 'l';
        break;
    case SEMICOLON_KEY:
        return ';';
        break;
    case APOSTROPHE_KEY:
        return '\'';
        break;
    case ENTER_KEY:
        return '\n';
        break;
    case LEFT_SHIFT:
        break;
    case Z_KEY:
        return 'z';
        break;
    case X_KEY:
        return 'x';
        break;
    case C_KEY:
        return 'c';
        break;
    case V_KEY:
        return 'v';
        break;
    case B_KEY:
        return 'b';
        break;
    case N_KEY:
        return 'n';
        break;
    case M_KEY:
        return 'm';
        break;
    case COMMA_KEY:
        return ',';
        break;
    case FULLSTOP_KEY:
        return '.';
        break;
    case FORWARD_SLASH_KEY:
        break;
    case RIGHT_SHIFT_KEY:
        break;
    case CONTROL_KEY:
        break;
    case WINDOWS_KEY:
        break;
    case ALT_KEY:
        break;
    case SPACEBAR_KEY:
        return ' ';
        break;
    }

    return key;
}