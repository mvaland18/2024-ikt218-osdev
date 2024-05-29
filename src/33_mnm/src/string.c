#include "libc/string.h"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}


void int_to_string(int value, char* buffer) {
    char* ptr = buffer;
    if (value < 0) {
        *ptr++ = '-';
        value = -value;
    }
    int start = ptr - buffer;
    do {
        *ptr++ = '0' + (value % 10);
        value /= 10;
    } while (value);
    *ptr = '\0';
    
    // Reverse the string
    for (int i = start, j = ptr - buffer - 1; i < j; i++, j--) {
        char tmp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = tmp;
    }
}

