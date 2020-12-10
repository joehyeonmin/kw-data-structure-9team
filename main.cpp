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

int flag = 0; // 0: 타이틀, 1: 긴글연습, 2: 끝말잇기, 3: Information

void InitCurses() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
}

void Title() {
    clear();
    refresh();
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

    mvwprintw(w, 3, 2, "( Press Esc to");
    mvwprintw(w, 4, 4, "exit the program )");

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
                    return;
                } else if (i == 1) {
                    flag = 2;
                    clear();
                    WordChainUI();
                } else {
                    flag = 3;
                    Information();
                }
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

void Information() {
    initscr();
    WINDOW *info;
    info = newwin(15, 80, 1, 1);
    box(info, 0, 0);

    mvwprintw(info, 1, 10, "< Information of This Program >");
    mvwprintw(info, 3, 2, "Data Structure Team 9");
    mvwprintw(info, 5, 2, "Language Used: C++");
    mvwprintw(info, 7, 2,
              "Typing Practice source: "
              "https://m.cafe.daum.net/kimsrabbit/MFyt?boardType=");
    mvwprintw(info, 9, 2,
              "WordChain Words source: https://opendict.korean.go.kr/main");
    mvwprintw(info, 13, 2, "Press ENTER to return to the title.");

    wrefresh(info);

    int ch;

    while (flag == 3) {
        while ((ch = wgetch(info))) {
            switch (ch) {
            case ENTER:
                delwin(info);
                clear();
                refresh();
                flag = 0;
                Title();
            }
        }
    }
}

int main() {
    InitCurses();
    Title();
}
