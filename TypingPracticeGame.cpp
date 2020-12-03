#include "TypingPracticeGame.hpp"

#define ENTER 10
#define PageOfLine 6 //페이지 줄 수
#define MAX_STR_LEN 4000

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
            delwin(typingWindow);
            endwin();
            return;
        }
        wattron(typingWindow, COLOR_PAIR(4));

        sprintf(item, "%-7s", list[i]);
        mvwprintw(typingWindow, i + 10, 2, "%s", item);
        wattroff(typingWindow, COLOR_PAIR(4));
    }
    /*
    delwin(typingWindow);
    endwin();
    return;
    */
}

// char*  trim(char *s); // 문자열 좌우 공백 모두 삭제 함수
// char* ltrim(char *s); // 문자열 좌측 공백 제거 함수
// char* rtrim(char* s); // 문자열 우측 공백 제거 함수

// int row = 1;
// int col = 3;

// int total = 0;
// int wrong = 0;
// void longprac_game(){
//     WINDOW* lw;
//     FILE* fp = fopen("a.txt", "r"); // 읽어올 파일을 연다.

//     if (fp == NULL) exit(1);

//     char* line = NULL;
//     string text;
//     string cmptext;

//     size_t len = 0;
//     ssize_t read;
//     int result = 0;

//     initscr();
//     start_color();
//     init_pair(1,COLOR_RED,COLOR_BLACK);
//     init_pair(2,COLOR_WHITE,COLOR_BLACK);
//     lw = newwin(30,150,1,1);
//     box(lw,0,0);
//     int page = 0;
//     clock_t start = clock();
//     while ( (read = getline(&line, &len, fp)) != -1 ) // 한줄씩 읽어온다
//     {
//         char str[180];
//         line = trim(line);
//         text =line;
//         mvwprintw(
//             lw,row,col,
//             line
//         );
//         row += 2;
//         wrefresh(lw);
//         int temp;
//         temp = mvwgetstr(lw,row,col,str);

//         cmptext = str;
//         //틀린 문자 체크
//         int i = 0;
//         for(i; str[i] != '\0'; i++){
//             if(text[i]!=str[i]){
//                 wattron(lw,COLOR_PAIR(1));
//                 mvwprintw(
//                     lw,row,col+i,
//                     &str[i]
//                 );
//                 wattroff(lw,COLOR_PAIR(1));
//                 wrong++;
//             }
//             else{
//                 wattron(lw,COLOR_PAIR(2));
//                 mvwprintw(
//                     lw,row,col+i,
//                     &str[i]
//                 );
//                 wattroff(lw,COLOR_PAIR(2));
//             }
//         }
//         int W = text.length() - cmptext.length();
//         if(W < 0)
//             W = -W;
//         total += W;

//         row += 2;
//         page++;
//         if(page >= PageOfLine){
//             page = 0;
//             wclear(lw);
//             box(lw,0,0);
//             row = 1;
//             col = 1;
//         }
//     }

//     clock_t end = clock();

//     wclear(lw);
//     box(lw,0,0);
//     row = 1;
//     col = 1;
//     string str1 = "\n평균 타수 : ";
//     string str2 = "\n틀린 글자 개수 : ";
//     string str3 = "\n걸린 초 : ";
//     string str4 = "\n정확도 : ";

//     //출력 계산
//     int res2 = wrong;
//     float res3 = (float)(end-start)/CLOCKS_PER_SEC;
//     float res4 = (float)(total - wrong)/total;
//     float res1 = (float)total/res3;

//     string Result = str1 + to_string(res1) + str2 + to_string(res2)
//         + str3 + to_string(res3) + str4 + to_string(res4);

//     const char* cResult = Result.c_str();
//     mvwprintw(lw,row,col,
//         cResult
//     );
//     wrefresh(lw);

//     //endwin();
//     return;
// }

// // 문자열 우측 공백문자 삭제 함수
// char* rtrim(char* s) {
//   char t[MAX_STR_LEN];
//   char *end;

//   // Visual C 2003 이하에서는
//   // strcpy(t, s);
//   // 이렇게 해야 함
//   strcpy(t, s); // 이것은 Visual C 2005용
//   end = t + strlen(t) - 1;
//   while (end != t && isspace(*end))
//     end--;
//   *(end + 1) = '\0';
//   s = t;

//   return s;
// }

// // 문자열 좌측 공백문자 삭제 함수
// char* ltrim(char *s) {
//   char* begin;
//   begin = s;

//   while (*begin != '\0') {
//     if (isspace(*begin))
//       begin++;
//     else {
//       s = begin;
//       break;
//     }
//   }

//   return s;
// }

// // 문자열 앞뒤 공백 모두 삭제 함수
// char* trim(char *s) {
//   return rtrim(ltrim(s));
// }
