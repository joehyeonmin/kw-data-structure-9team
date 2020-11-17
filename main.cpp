/*
 * 자료구조실습 9조 팀프로젝트
 */
#include "TypingPracticeGame.hpp"
#include "WordGame.hpp"
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include <string>

#define ENTER 10
#define ESCAPE 27

void InitCurses();  // curses 기초 설정
void Title();       // 타이틀 출력 함수
void Information(); // 정보 출력 함수

int flag = 0; // 0: 타이틀, 1: 긴글연습, 2: 끝말잇기, 3: Information

void InitCurses() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
}

void Title() {
    WINDOW *w;
    char list[3][20] = {"Typing Practice", "Word Chain Game", "Information"};
    char item[20];
    int ch, i = 0, width = 20;

    initscr();
    w = newwin(15, 30, 1, 1);
    box(w, 0, 0);

    mvwprintw(
        w, 1, 3,
        "Typing Practice in Linux"); // mvwprintw(화면, y좌표, x좌표, 내용)

    for (i = 0; i < 3; i++) {
        if (i == 0)
            wattron(w, COLOR_PAIR(2)); // Highlight the line
        else
            wattroff(w, COLOR_PAIR(2));
        sprintf(item, "%-7s", list[i]);
        mvwprintw(w, i + 10, 2, "%s", item);
    }

    wrefresh(w);

    i = 0;
    noecho();
    keypad(w, TRUE);
    curs_set(0);

    while (flag == 0) {
        while ((ch = wgetch(w)) != ESCAPE) { // 'esc'키로 종료
            sprintf(item, "%-7s", list[i]);
            mvwprintw(w, i + 10, 2, "%s", item);
            switch (ch) {
            case KEY_UP: // 위 방향키
                i--;
                i = (i < 0) ? 2 : i;
                break;
            case KEY_DOWN: // 아래 방향키
                i++;
                i = (i > 2) ? 0 : i;
                break;
            case ENTER: // 엔터키
                if (i == 0) {
                    flag = 1;
                    TypingGame();
                } else if (i == 1) {
                    flag = 2;
                    WordChainUI();
                } else
                    Information();
            }
            wattron(w, COLOR_PAIR(2));

            sprintf(item, "%-7s", list[i]);
            mvwprintw(w, i + 10, 2, "%s", item);
            wattroff(w, COLOR_PAIR(2));
        }
        delwin(w);
        endwin();
        return;
    }
}

void Information() {}

int main() {
    InitCurses();
    Title();
}
