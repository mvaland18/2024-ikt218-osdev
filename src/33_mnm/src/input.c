#include "input.h"
#include "libc/system.h"

bool capsEnabled = false;
bool shiftPressed = false;

const char large_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '\b', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '\n', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};
const char small_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '\b', '?', 'q', 'w', 'e', 'r', 't', 'y',
                         'u', 'i', 'o', 'p', '[', ']', '\n', '?', 'a', 's', 'd', 'f', 'g',
                         'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
                         'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

char scancode_to_ascii(unsigned char* scan_code) {
    unsigned char a = *scan_code;
    switch (a){
        case 1:     // ESC
            return 0;
        case 14:    // BACKSPACE
            return '\b';
        case 28:    // ENTER
            return '\n';
        case 42:    // LEFT SHIFT
        case 54:    // RIGHT SHIFT
            shiftPressed = true;
            return 0;
        case 170:   // LEFT SHIFT RELEASE
        case 182:   // RIGHT SHIFT RELEASE
            shiftPressed = false;
            return 0;
        case 57:    // SPACE
            return ' ';
        case 58:    // CAPS LOCK
            capsEnabled = !capsEnabled;
            return 0;
        default:
            if (a < sizeof(small_ascii)) {
                if (shiftPressed) {
                    return large_ascii[a];
                } else if (capsEnabled) {
                    return (a >= 16 && a <= 25) || (a >= 30 && a <= 38) || (a >= 44 && a <= 50) ? large_ascii[a] : small_ascii[a];
                } else {
                    return small_ascii[a];
                }
            }
            return 0;
    }
}
