// vim: ft=cpp
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Debouncer.h>
#include "letter.h"
                
const int RS = 2, E = 3, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
const int LED = 8, INPUT_BTN = 10, BS_BTN = 12;
const int tick = 100;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
Debouncer debouncer(BS_BTN, 40);
Letter letter;
bool pressed = false;
bool led = false;
unsigned long last = 0;
int cursor = 0;

void setup() {
    lcd.begin(16, 2);
    for (int pin = 2; pin <= 8; pin++) 
        pinMode(pin, OUTPUT);
    pinMode(INPUT_BTN, INPUT);
    pinMode(BS_BTN, INPUT);
    debouncer.subscribe(Debouncer::Edge::FALL, [](){
        if (letter.bits[0] != 0) {
            lcd.setCursor(cursor, 0);
            lcd.print("         ");
            letter = Letter();
        } else {
            lcd.setCursor(--cursor, 0);
            lcd.print("         ");
        }
        lcd.setCursor(cursor, 0);
        last = millis();
    });
    last = millis();
    lcd.cursor();
}

void loop() {
    unsigned long current = millis();
    unsigned long gap = current - last;
    int button = digitalRead(INPUT_BTN);
    debouncer.update();
    if (current/tick % 2 != led) {
        led = !led;
        digitalWrite(8, led ? HIGH : LOW);
    }
    if (!pressed && button == LOW) {
        pressed = true;
        last = current;
        if (gap > 3*tick) {
            char c = letter.decode();
            if (c != 0) {
                lcd.setCursor(cursor, 0);
                lcd.print("     ");
                lcd.setCursor(cursor++, 0);
                lcd.print(c);
            }
            if (gap > 18*tick) {
                lcd.print(" ");
                cursor++;
            }
            letter = Letter();
        }
    } else if (pressed && button == HIGH) {
        pressed = false;
        last = current;
        if (gap > tick) {
            char sym = (gap > 3*tick ? '-' : '.');
            lcd.print(sym);
            letter.append(sym);
        }
    }
}
