#include "TypingPracticeGame.hpp"

void move_cursor(int x, int y) { printf("\033[%dd\033[%dG", y, x); }

void longbackground() {
    for (int i = 0; i < 90; i++) {
        cout << "■ ";
    }
    for (int i = 1; i < 45; i++) {
        move_cursor(0, i);
        cout << "■";
        move_cursor(179, i);
        cout << "■";
    }
    move_cursor(0, 45);
    for (int i = 0; i < 90; i++) {
        cout << "■ ";
    }
}
void subbackground() {
    for (int point = 6; point <= 42; point += 4) {
        move_cursor(6, point - 1);
        cout << "+";
        for (int i = 1; i < 168; i++) {
            cout << "-";
        }
        cout << "+";
        move_cursor(6, point);
        cout << "|";
        move_cursor(174, point);
        cout << "|";
        move_cursor(6, point + 1);
        cout << "+";
        for (int i = 1; i < 168; i++) {
            cout << "-";
        }
        cout << "+";
    }
}
