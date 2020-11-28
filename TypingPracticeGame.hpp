#ifndef __LONGPRAC_H__
#define __LONGPRAC_H__

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void move_cursor(int x, int y);
void subbackground();
void longbackground();
void longprac_game(string pathname);
void TypingGame();
char*  trim(char *s); // 문자열 좌우 공백 모두 삭제 함수
char* ltrim(char *s); // 문자열 좌측 공백 제거 함수
char* rtrim(char* s); // 문자열 우측 공백 제거 함수


#endif
