#include "TypingPracticeGame.hpp"
#include <array>
#include <cstdio>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define TEXT_SIZE 5000 // fseek랑 ftell로 파일 사이즈 알 수 있을 거 같은데
#define DEL 127
#define BS 8

void longprac_game() {
    string pathname = "./BeautyAndTheBeast.txt";
    array<char, TEXT_SIZE> read_text = {
        '\0',
    }; // 전체파일 읽어오기
    array<char, TEXT_SIZE> write_text = {
        '\0',
    };
    char cut_text[100][TEXT_SIZE] = {
        '\0',
    };
    ssize_t rsize = 0; // 읽어온 크기
    int xpoint = 7;
    int ypoint = 6;
    int write_count = 0;
    char write_char;
    int cut_count_row;
    int cut_count_col;
    int index = 0;

    clear();
    refresh();
    longbackground();
    subbackground();

    memset(&read_text, '\0', TEXT_SIZE);
    memset(&write_text, '\0', TEXT_SIZE);
    memset(&cut_text, '\0', TEXT_SIZE);

    int fd = open(pathname.c_str(), O_RDONLY);
    if (fd == -1) {
        perror("error");
    }
    rsize = read(fd, &read_text, TEXT_SIZE);
    if (rsize == 0)
        return;
    cut_count_row = 0;
    cut_count_col = 0;

    array<char, TEXT_SIZE>::iterator iter_read;
    for (iter_read = read_text.begin(); iter_read != read_text.end();
         ++iter_read) {
        cut_text[cut_count_row][cut_count_col] = *iter_read;
        cut_count_col++;

        if (*iter_read == '\n') {
            cut_count_row++;
        }
    }
    index = cut_count_row;
    for (int i = 0; i <= cut_count_row; i++) {
        move_cursor(xpoint, ypoint);
        ypoint += 8;

        for (char c : cut_text[i]) {
            cout << c;
        }

        if ((i + 1) % 5 == 0) {
            ypoint = 10;
            move(ypoint - 1, xpoint - 1);
            refresh();

            while (1) {
                write_char = getchar();
                write_text[write_count] = write_char;
                cout << write_text[write_count];
                write_count++;
                if (write_char == '\r' || write_count > 166) {
                    index--;
                    ypoint += 8;
                    write_count = 0;
                    memset(&write_text, '\0', TEXT_SIZE);
                    if (ypoint > 44) { // 다음 페이지로
                        clear();
                        refresh();
                        longbackground();
                        subbackground();
                        break;
                    }
                    if (index <= 0) {
                        clear();
                        refresh();
                        longbackground();
                    }
                    move_cursor(xpoint, ypoint);
                } else if (write_char == DEL || write_char == BS) {
                    write_count--;
                    write_text[write_count] = '\0';
                    if (write_count == 0) {
                        continue;
                    }
                    move_cursor(xpoint + write_count - 1, ypoint);
                    cout << " ";
                    move_cursor(xpoint + write_count - 1, ypoint);
                    write_count--;
                }
                // 틀렸을 때 색 표시 추가
            }
            ypoint = 6;
        }
    }
    move_cursor(0, 46);
    close(fd);
}
