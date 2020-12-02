#include "WordGame.hpp"
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#define PERMS 0644
#define MAX_BUF_SIZE 1024

using namespace std;

WordGame::WordGame() {
    loadWords();
    usedCount = 0;
    lifeCount = 0;

    srand(time(NULL));
    int random = rand() % 10000;
    before = words.at(random); // 컴퓨터 시작 단어 결정
    used.push_back(before);
}

WordGame::~WordGame() {
    usedCount = 0;
    lifeCount = 0;
}

void WordGame::playGame() {
    cout << "Game Start!" << endl;
    cout << "컴퓨터: " << before << endl;

    while (lifeCount != 2) {
        cout << "플레이어: ";
        cin >> later;
        if (checkWords(later)) {
            before = later;
            usedCount++;
            used.push_back(later);

            comWords();
            continue;
        } else {
            lifeCount++;
            cout << lifeCount << "회 실패! 2회 실패 시 게임 오버" << endl;
            continue;
        }
    }

    cout << "Game Over!!" << endl;
    return;
}

void WordGame::loadWords() {
    int array_size = 1024;
    char line[100];

    ifstream fin;
    fin.open("merged.txt");
    if (fin.is_open()) {
        while (fin.getline(line, sizeof(line))) {
            words.push_back(line);
        }
    }
}

bool WordGame::checkWords(string str) {

    // int i = before.size();
    /*const wchar_t *str1;
    const wchar_t *str2;
    wstring str3;
    wstring str4;

    str3.assign(str.begin(), str.end());
    str4.assign(before.begin(), before.end());

    str1 = str3.c_str();
    str2 = str4.c_str();*/

    const char *str1 = str.c_str();
    const char *str2 = before.c_str();

    // before.at(i - 1) == str.at(0) && before.at(i - 2) == str.at(1)

    char temp1[3] = {
        0x00,
    };
    sprintf(temp1, "%c%c%c\n", *str1, *(str1 + 1), *(str1 + 2));

    char temp2[3] = {
        0x00,
    };
    sprintf(temp2, "%c%c%c\n", *(str2 + strlen(str2) - 3),
            *(str2 + strlen(str2) - 2), *(str2 + strlen(str2) - 1));

    if (strcmp(temp1, temp2) == 0) {
        for (iter = words.begin(); iter != words.end(); iter++) {
            if (str == *iter) {
                for (iter2 = used.begin(); iter2 != used.end(); iter2++) {
                    if (str == *iter2) {
                        cout << "기존파일 등록 실패" << endl;
                        return false; // 이미 사용함
                    }
                }
                return true; // 사전에 있고, 중복이 아니며 첫 글자 일치
            }
            cout << "사전에 존재하지x" << endl;
            return false; // 사전에 존재하지 않음
        }
    } else {
        /*wcout << str3 << endl;
        wcout << str4 << endl;
        wcout << str1 << endl;
        wcout << str2 << endl;

        cout << str1[0] << str[1] << endl;
        cout << str2[sizeof(str) - 1] << endl;
        char temp[5] = {
            0x00,
        };
        sprintf(temp, "%c%c%c\n", *str1, *(str1 + 1), *(str1 + 2));
        cout << temp << endl;*/

        cout << temp1 << endl;
        cout << temp2 << endl;

        return false; // 첫 글자 불일치
    }
}

void WordGame::comWords() {
    srand(time(NULL));
    int random = rand() % 10000;
    string temp = words[random];
    if (checkWords(temp))
        before = words[random];

    cout << "컴퓨터: " << before << endl;
}

int main() {
    cout << "3초 후 게임을 시작합니다." << endl;
    sleep(3);
    WordGame game;
    game.playGame();
}
