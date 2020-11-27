#ifndef __LONGPRAC_H__
#define __LONGPRAC_H__

#include <iostream>
#include <ncurses.h>
#include <string.h>

using namespace std;

void move_cursor(int x, int y);
void subbackground();
void longbackground();
void longprac_game(string pathname);
void TypingGame();

#endif
