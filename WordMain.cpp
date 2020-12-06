#include "WordGame.hpp"
#include <iostream>
#include <string>
#include <vector>

#define PERMS 0644
#define MAX_BUF_SIZE 1024

using namespace std;

void WordChainUI() {
    WINDOW *wwc;
    initscr();
    wwc = newwin(22, 50, 1, 1);
    touchwin(wwc);
    wborder(wwc, '*', '*', '*', '*', '*', '*', '*', '*');
    /*mvwprintw(wwc, 0, 0, "■■■■■■■■■■■■■■■■■■■■■■■■■");
    for (int i = 1; i <= 20; i++) {
        if (i == 15)
            mvwprintw(wwc, i, 1, "■■■■■■■■■■■■■■■■■■■■■■■■■");
        else
            mvwprintw(wwc, i, 0,
                      "■                                              ■");
    }*/
    mvwprintw(wwc, 2, 1, "**************************************************");
    mvwprintw(wwc, 17, 1, "**************************************************");
    mvwprintw(wwc, 1, 17, "<Word Chain Game>");
    wrefresh(wwc);
    WordChainGame();
}

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

void WordChainGame() {
    cout << "3초 후 게임을 시작합니다." << endl;
    sleep(3);
    WordGame game;
    game.playGame();
}

/*void WordChainGame() {
    int fd = 0;
    char *pathname = "./merged.txt";
    fd = open(pathname, O_RDONLY, PERMS);

    char comword[1024] = {
        '\0',
    };
    srand(time(NULL));
    int random = rand() % 10;

    lseek(fd, (off_t)0, random);

    int rsize = 0;
    do {
        memset(comword, '\0', 1025);
        rsize = read(fd, (char *)comword, MAX_BUF_SIZE);
        // cout << comword << endl;
    } while (rsize > 0);

    move(19, 1);
    cout << "3초 후 게임이 시작됩니다." << endl;
    sleep(3);
    move(19, 1);
    cout << "                                       ";*/

// move(6, 1);
/*cout << "컴퓨터 : " << sleep(1) << comword[random] << endl;
char endcomword = comword[strlen(comword) - 1];
cout << endcomword << endl;

char userword[100];
char line[100];
char buf[200];
FILE *fp;
fp = fopen("merged.txt", "r");
int num = 0;
char firstuserword;
char enduserword;

while (true) {
    // move(1, 19);
    cout << "단어입력 : ";
    cin >> userword;

    while (!feof(fp)) {
        num++;
        fgets(line, 100, fp);
        if (strstr(line, userword) != NULL && firstuserword == endcomword) {
            cout << "성공" << endl;
            firstuserword = userword[0];
        }
    }

    enduserword = userword[strlen(userword) - 1];
    while (!feof(fp)) {
        while (fscanf(fp, "%s", buf) != EOF) {
            if (enduserword == buf[0]) {
                cout << userword << endl;
                char firstuserword = userword[0];
            } else {
                cout << "다시 입력해주세요" << endl;
            }
        }
    }
}
fclose(fp);

close(fd);
return;
}*/
