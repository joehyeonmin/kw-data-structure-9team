#include "TypingPracticeGame.hpp"
#include <array>
#include <cstdio>
#include <ctime>
#include <fcntl.h>
#include <list>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define TEXT_SIZE 5000
#define DEL 127
#define BS 8

void longprac_game(string pathname) {
    array<char, TEXT_SIZE> read_text = {
        '\0',
    }; // 전체파일 읽어오기
    array<char, TEXT_SIZE> write_text = {
        '\0',
    };
    char cut_text[100][TEXT_SIZE] = {
        '\0',
    };
    int cut_text_count[100];
    ssize_t rsize = 0; // 읽어온 크기
    int xpoint = 7;
    int ypoint = 6;
    int write_count = 0;
    char write_char;
    int cut_count_row;
    int cut_count_col;
    int index = 0;
    list<int> wrong_count;
    int wrong = 0;

    int totalText = 0; // 총 글자수

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
        totalText++;
        if (*iter_read == '\n') {
            cut_text_count[cut_count_row] = cut_count_col;
            cut_count_row++;
            cut_count_col = 0;
        }
    }
    index = cut_count_row;
    time_t start = 0, end = 0;
    time(&start);
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

                if (write_char == '\r' ||
                    write_count == cut_text_count[cut_count_row - index] - 1) {
                    index--;
                    ypoint += 8;
                    totalText = totalText + write_count;
                    write_count = 0;
                    memset(&write_text, '\0', TEXT_SIZE);
                    wrong += wrong_count.size();
                    wrong_count.clear();
                    if (index <= 0) {
                        clear();
                        refresh();
                        longbackground();
                        close(fd);
                        time(&end);
                        float totalTime = end - start;
                        int min = totalTime / 60;
                        int sec = totalTime - 60 * min;
                        float avgtasu = 60 * (totalText / totalTime);
                        move_cursor(73, 20);
                        cout << "총 걸린 시간 : " << min << "분 " << sec << "초"
                             << endl;
                        move_cursor(73, 21);
                        cout << "평균 타수 : " << avgtasu << endl;
                        move_cursor(73, 22);
                        cout << "틀린 글자 개수 : " << wrong << endl;

                        getchar(); // 아무 버튼이나 누르면 종료
                        return;
                    } else if (ypoint > 44) { // 다음 페이지로
                        ypoint = 6;
                        clear();
                        refresh();
                        longbackground();
                        subbackground();
                        break;
                    }
                    move_cursor(xpoint, ypoint);
                } else if (write_char == DEL || write_char == BS) {
                    write_count--;

                    write_text[write_count] = '\0';
                    if (write_count == 0) {
                        continue;
                    }

                    if (!wrong_count.empty()) {
                        if (wrong_count.back() == write_count - 1)
                            wrong_count.pop_back();
                    }
                    move_cursor(xpoint + write_count - 1, ypoint);
                    cout << " ";
                    move_cursor(xpoint + write_count - 1, ypoint);
                    write_count--;
                } else if (write_char !=
                           cut_text[cut_count_row - index][write_count - 1]) {
                    wrong_count.push_back(write_count - 1);
                    move_cursor(xpoint + write_count - 1, ypoint - 4);
                    printf("%c[31m", 27); // 빨간색
                    printf("%c[40m", 27);
                    cout << cut_text[cut_count_row - index][write_count - 1];
                    printf("%c[37m", 27); // 원래대로 출력
                    move_cursor(xpoint + write_count, ypoint);
                } else if (write_char ==
                           cut_text[cut_count_row - index][write_count - 1]) {
                    move_cursor(xpoint + write_count - 1, ypoint - 4);
                    cout << cut_text[cut_count_row - index][write_count - 1];
                    move_cursor(xpoint + write_count, ypoint);
                }
            }
        }
        if (index < 5) { // 마지막이 한 페이지를 채우지 못했을 경우
            for (int j = cut_count_row - index; j <= cut_count_row; j++) {
                move_cursor(xpoint, ypoint);
                for (char c : cut_text[j]) {
                    cout << c;
                }
                ypoint += 8;
            }

            ypoint = 10;
            move(ypoint - 1, xpoint - 1);
            refresh();

            while (1) {
                write_char = getchar();
                write_text[write_count] = write_char;
                cout << write_text[write_count];
                write_count++;

                if (write_char == '\r' ||
                    write_count == cut_text_count[cut_count_row - index] - 1) {
                    index--;
                    ypoint += 8;
                    totalText = totalText + write_count;
                    write_count = 0;
                    memset(&write_text, '\0', TEXT_SIZE);
                    wrong += wrong_count.size();
                    wrong_count.clear();
                    if (ypoint > 44) { // 다음 페이지로
                        ypoint = 6;
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
                        close(fd);
                        time(&end);
                        float totalTime = end - start;
                        int min = totalTime / 60;
                        int sec = totalTime - 60 * min;
                        float avgtasu = 60 * (totalText / totalTime);
                        move_cursor(73, 20);
                        cout << "총 걸린 시간 : " << min << "분 " << sec << "초"
                             << endl;
                        move_cursor(73, 21);
                        cout << "평균 타수 : " << avgtasu << endl;
                        move_cursor(73, 22);
                        cout << "틀린 글자 개수 : " << wrong << endl;

                        getchar(); // 아무 버튼이나 누르면 종료
                        return;
                    }
                    move_cursor(xpoint, ypoint);
                } else if (write_char == DEL || write_char == BS) {
                    write_count--;
                    write_text[write_count] = '\0';
                    if (write_count == 0) {
                        continue;
                    }
                    if (!wrong_count.empty()) {
                        if (wrong_count.back() == write_count - 1)
                            wrong_count.pop_back();
                    }
                    move_cursor(xpoint + write_count - 1, ypoint);
                    cout << " ";
                    move_cursor(xpoint + write_count - 1, ypoint);
                    write_count--;
                } else if (write_char !=
                           cut_text[cut_count_row - index][write_count - 1]) {
                    wrong_count.push_back(write_count - 1);
                    move_cursor(xpoint + write_count - 1, ypoint - 4);
                    printf("%c[31m", 27); // 빨간색
                    printf("%c[40m", 27);
                    cout << cut_text[cut_count_row - index][write_count - 1];
                    printf("%c[37m", 27); // 원래대로 출력
                    move_cursor(xpoint + write_count, ypoint);
                } else if (write_char ==
                           cut_text[cut_count_row - index][write_count - 1]) {
                    move_cursor(xpoint + write_count - 1, ypoint - 4);
                    cout << cut_text[cut_count_row - index][write_count - 1];
                    move_cursor(xpoint + write_count, ypoint);
                }
            }
        }
    }
    /*
        clock_t end = clock();
        float totalTime = (float)(end - start) / CLOCKS_PER_SEC;
        float accuracy = (float)(totalText - wrong) / totalText;
        float typingSpeed = (float)totalText / totalTime;
        move_cursor(50, 15);
        cout << "평균 타수 : " << typingSpeed << endl;
        cout << "틀린 글자 개수 : " << wrong << endl;
        cout << "걸린 초 : " << totalTime << endl;
        cout << "\n정확도 : " << accuracy << endl;
        getchar(); // 아무 버튼이나 누르면 종료
    */
    // close(fd);
}
