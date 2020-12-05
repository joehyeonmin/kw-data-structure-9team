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

            before = comWords(later);
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
    const char *str1 = str.c_str();
    const char *str2 = before.c_str();

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
                        cout << "이미 사용한 단어입니다" << endl;
                        return false; // 이미 사용함
                    }
                }
                return true; // 사전에 있고, 중복이 아니며 첫 글자 일치
            }
        }

        cout << "사전에 존재하지 않는 단어입니다" << endl;
        return false; // 사전에 존재하지 않음
    }

    else {
        cout << temp1 << endl;
        cout << temp2 << endl;
        cout << "끝말잇기가 불가능합니다" << endl;
        return false; // 첫 글자 불일치
    }
}

/*void WordGame::comWords() {
    srand(time(NULL));
    int random = rand() % 10000;
    string temp = words[random];
    if (checkWords(temp))
        before = words[random];

    cout << "컴퓨터: " << before << endl;
}*/

string WordGame::comWords(string str) {
    const char *str1 = str.c_str();

    char temp1[3] = {
        0x00,
    };

    char temp2[3] = {
        0x00,
    };
    sprintf(temp2, "%c%c%c\n", *(str1 + strlen(str1) - 3),
            *(str1 + strlen(str1) - 2), *(str1 + strlen(str1) - 1));

    vector<string> temp;

    for (iter = words.begin(); iter != words.end(); iter++) {
        const char *str2 = (*iter).c_str();
        sprintf(temp1, "%c%c%c\n", *str2, *(str2 + 1), *(str2 + 2));
        if (strcmp(temp1, temp2) == 0) {
            temp.push_back(*iter);
        }
    }
    srand(time(NULL));
    int random = rand() % 10;
    cout << "컴퓨터: " << temp[random] << endl;
    return temp[random];

    /* srand(time(NULL));
     int random = rand() % 10000;
     string temp = words[random];
     if (checkWords(temp))
         before = words[random];

     cout << "컴퓨터: " << before << endl;*/
}

int main() {
    cout << "3초 후 게임을 시작합니다." << endl;
    sleep(3);
    WordGame game;
    game.playGame();
}
