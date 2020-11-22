#include "TypingPracticeGame.hpp"

#define ENTER 10

void TypingGame() {
    WINDOW *typingWindow;
    char list[3][20] = {"1. aaa", "2. bbb", "3. ccc"};
    // 파일 이름 적기 추가 수정 필요
    char item[20];

    initscr();
    clear();
    refresh();

    typingWindow = newwin(40, 40, 0, 0);
    touchwin(typingWindow);
    box(typingWindow, 0, 0);
    mvwprintw(typingWindow, 1, 8, "< Typing Practice Game >");
    wrefresh(typingWindow);

    int i = 0;
    for (i = 0; i < 3; i++) {
        if (i == 0)
            wattron(typingWindow, COLOR_PAIR(4));
        else
            wattroff(typingWindow, COLOR_PAIR(4));
        sprintf(item, "%-7s", list[i]);
        mvwprintw(typingWindow, i + 10, 2, "%s", item);
    }

    wrefresh(typingWindow);

    i = 0;
    noecho();
    keypad(typingWindow, TRUE);
    curs_set(0);

    int ch;
    while (ch = wgetch(typingWindow)) {
        sprintf(item, "%-7s", list[i]);
        mvwprintw(typingWindow, i + 10, 2, "%s", item);
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
            longprac_game();
            // 파일 별로 다르게 열리도록 수정해야함
        }
        wattron(typingWindow, COLOR_PAIR(4));

        sprintf(item, "%-7s", list[i]);
        mvwprintw(typingWindow, i + 10, 2, "%s", item);
        wattroff(typingWindow, COLOR_PAIR(4));
    }
    delwin(typingWindow);
    endwin();
    return;
}
