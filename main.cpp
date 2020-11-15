/*
 * 자료구조실습 9조 팀프로젝트
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <string>

void title();
void TypingPracticeUI();
void TypingPractice();
void WordChainUI();
void WordChainGame();
void Information();

void title() {
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
            wattron(w, A_STANDOUT); // Highlight the line
        else
            wattroff(w, A_STANDOUT);
        sprintf(item, "%-7s", list[i]);
        mvwprintw(w, i + 10, 2, "%s", item);
    }

    wrefresh(w);

    i = 0;
    noecho();
    keypad(w, TRUE);
    curs_set(0);

    while ((ch = wgetch(w)) != 'q') {
        sprintf(item, "%-7s", list[i]);
        mvwprintw(w, i + 10, 2, "%s", item);
        switch (ch) {
        case KEY_UP:
            i--;
            i = (i < 0) ? 2 : i;
            break;
        case KEY_DOWN:
            i++;
            i = (i > 2) ? 0 : i;
            break;
        case KEY_ENTER:
            if (i == 0)
                TypingPracticeUI();
            else if (i == 1)
                WordChainUI();
            else
                Information();
        }
        wattron(w, A_STANDOUT);

        sprintf(item, "%-7s", list[i]);
        mvwprintw(w, i + 10, 2, "%s", item);
        wattroff(w, A_STANDOUT);
    }
    delwin(w);
    endwin();
}

void TypingPracticeUI() {}
void TypingPractice() {}
void WordChainUI() {}
void WordChainGame() {}
void Information() {}

int main() { title(); }
