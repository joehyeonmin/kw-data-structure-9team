#include "TypingPracticeGame.hpp"

#define ENTER 10

void TypingGame() {
    WINDOW *typingWindow;
    char list[5][30] = {"1. Beauty and the beast", "2. Gulliver's Travels",
                        "3. Rapunzel", "4. The little prince",
                        "5. The wind and the sun"};
    char item[30];
    string path;
    initscr();
    clear();
    refresh();

    typingWindow = newwin(20, 40, 0, 0);
    touchwin(typingWindow);
    box(typingWindow, 0, 0);
    mvwprintw(typingWindow, 1, 8, "< Typing Practice Game >");
    wrefresh(typingWindow);

    int i = 0;
    for (i = 0; i < 5; i++) {
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
            i = (i < 0) ? 4 : i;
            break;
        case KEY_DOWN: // 아래 방향키
            i++;
            i = (i > 4) ? 0 : i;
            break;
        case ENTER: // 엔터키
            if (i == 0)
                path = "./longtext/BeautyAndTheBeast.txt";
            else if (i == 1)
                path = "./longtext/Gulliver's Travels.txt";
            else if (i == 2)
                path = "./longtext/Rapunzel.txt";
            else if (i == 3)
                path = "./longtext/The Little Prince.txt";
            else
                path = "./longtext/The Wind and the Sun.txt";
            longprac_game(path);
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
