#include "letter.h"

const char *codes[] = {
    ".-",    // A
    "-...",  // B
    "-.-.",  // C 
    "-..",   // D
    ".",     // E
    "..-.",  // F
    "--.",   // G
    "....",  // H
    "..",    // I
    ".---",  // J
    "-.-",   // K
    ".-..",  // L
    "--",    // M
    "-.",    // N
    "---",   // O
    ".--.",  // P
    "--.-",  // Q
    ".-.",   // R
    "...",   // S
    "-",     // T
    "..-",   // U
    "...-",  // V
    ".--",   // W
    "-..-",  // X
    "-.--",  // Y
    "--..",  // Z
    "-----", // 0
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----.", // 9
    ""
};

bool strEq(char *a, char *b) {
    int i = 0;
    while (a[i] != 0 && b[i] != 0) {
        if (a[i] == b[i]) i++;
        else return false;
    }
    return a[i] == 0 && b[i] == 0;
}

Letter::Letter() {
    int t = 6;
    while (t--) bits[t] = 0;
    index = 0;
}

char Letter::decode() {
    for (int i = 0; i < 37; i++) {
        if (strEq(codes[i], bits)) {
            if (i == 36) return 0;
            return (i < 26 ? 'A'+i : '0'+i-26);
        }
    }
    return '?';
}

void Letter::append(char c) {
    if (index >= 5) return;
    bits[index++] = c;
}
