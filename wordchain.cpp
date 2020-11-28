#include "WordGame.hpp"
#include <vector>

#define PERMS 0644
#define MAX_BUF_SIZE 1024

using namespace std;
/*int main() {
    FILE *pFile = fopen("merged.txt", "r");
    fseek(pFile, 0, SEEK_END);
    long int wordCount = ftell(pFile);
    int existFlag = false;
    inputWordStruct temp;

    wchar_t *compareWord;
    inputWordStruct *fileWriteWord;

    cout << "단어를 입력해주세요 : ";
    scanf("%ls", fileWriteWord->inputWord);
    compareWord = fileWriteWord->inputWord;

    rewind(pFile);
    for (int i = 0; i < wordCount; i++){
        fread(&temp, sizeof(temp), 1, pFile);
        if(wcscmp(temp.inputWord, compareWord) == 0){
            existFlag = true;
            break;
        }
    }

    if(existFlag == true){
        cout << "success";

    }
    else
    {
        cout << "fail";
    }
    return 0;
}*/

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
    if (before.at(before.length() - 1) == str.at(0)) {
        for (iter = words.begin(); iter != words.end(); iter++) {
            if (str == *iter) {
                for (iter2 = used.begin(); iter2 != used.end(); iter2++) {
                    if (str == *iter2)
                        return false; // 이미 사용함
                }
                return true; // 사전에 있고, 중복이 아니며 첫 글자 일치
            }
            return false; // 사전에 존재하지 않음
        }
    } else {
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

// int main() {
//     int array_size = 1024;
//     char line[200];
//     int position = 0;
//     vector<string> words; // 단어 저장 사전
//     vector<string> used;  // 사용한 단어 저장

//     ifstream fin; // words에 사전 텍스트 파일 저장
//     fin.open("merged.txt");
//     if (fin.is_open()) {
//         while (fin.getline(line, sizeof(line))) {
//             words.push_back(line);
//         }
//     }
//     srand(time(NULL));
//     int random = rand() % 40;
//     std::cout << "컴퓨터 단어 : " << words[random] << endl;
//     string text = words[random];
//     string endcomword = text.substr(text.length() - 1, 1);
//     fin.close();

//     string userword;
//     char line1[100];
//     char line2[100];
//     char buf[200];
//     /*FILE *fp;
//     fp = fopen("merged.txt", "r");*/
//     vector<string>::iterator iter;

//     string firstuserword;
//     string enduserword;
//     int gameover = 0; // 3번 연속 실패하면 게임 오버
//     int num1 = 0;
//     int num2 = 0;

//     while (gameover != 3) {

//         std::cout << "단어입력 : "; //사용자 단어 입력
//         cin >> userword;
//         firstuserword = userword.at(0);
//         if (firstuserword ==
//             endcomword) //사용자 단어 입력성공시 사전파일에 있는 단어인지
//             확인
//         {
//             /*while (!feof(fp)) {
//                 num1++;
//                 fgets(line1, 100, fp);
//                 if (strstr(line1, userword) != NULL)
//                 {
//                     cout << "성공" << endl;
//                     break;
//                 }
//             }*/
//             for (iter = words.begin(); iter != words.end();
//                  iter++) { //사용자 단어 입력성공시 사전파일에 있는 단어인지
//                            //확인
//                 if (userword == *iter) {
//                     std::cout << "성공" << endl;
//                     break;
//                 }
//                 num1++;
//             }

//             enduserword = userword[userword.length() - 1];
//             /*while (!feof(fp)) { //컴퓨터 사전에서 찾기
//                 num2++;
//                 fgets(line2, 100, fp);
//                 if (line2[0] == enduserword ) {
//                     cout << "컴퓨터 : " << line2 << endl;
//                     endcomword = line2[strlen(line2) - 1, strlen(line2)];

//                     break;
//                 }
//             }*/
//             for (iter = words.begin(); iter != words.end(); iter++) {
//                 if (words[num2].at(0) == enduserword) {
//                     std::cout << "컴퓨터 : " << words[num2] << endl;

//                     endcomword = words[num2].back(); //왜오류지
//                     num2++;
//                     words.erase(words.begin() + num2 - 1);
//                     break;
//                 }
//             }
//             /*
//             ofstream newdata("newdata.txt");
//             for (int i = 0; i < words.size(); i++) {
//                 newdata << words[i] << endl;
//             }
//             newdata.close();
//             remove("merged.txt");
//             rename("newdata.txt", "merged.txt");*/
//         } else {
//             std::cout << "실패" << endl;
//             gameover++;
//         }
//     }
//     // fclose(fp);
//     std::cout << "게임 오버!" << endl;
//     return 0;
// }

/*int fd = 0;
char *pathname = "./merged.txt";
fd = open(pathname, O_RDONLY, PERMS);

char comword[1024] = {
    '\0',
};
srand(time(NULL));
int random = rand() % 10;

lseek(fd, (off_t)random, SEEK_CUR);

int rsize = 0;

do {

    memset(comword, '\0', 1025);
    rsize = read(fd, comword, MAX_BUF_SIZE);
    printf("%s", comword);
    // cout << comword[i] << endl;

} while (rsize > 0);

//cout << "컴퓨터 : " << comword[random] << endl;
printf("컴퓨터 : %s", comword);
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

        cout << "단어입력 : ";
        cin >> userword;

        while (!feof(fp)) {
            num++;
            fgets(line, 100, fp);
            if (strstr(line, userword) != NULL && firstuserword ==
endcomword) { cout << "성공" << endl; firstuserword = userword[0];
            }
        }

        enduserword = userword[strlen(userword) - 1];
        while (!feof(fp)) {
            while (fscanf(fp, "%s", buf) != EOF) {
                if (enduserword == buf[0]) {
                    cout << userword << endl;
                    char firstuserword = userword[0];
                } else {
                    cout << "다시입력해주세요" << endl;
                }
            }
        }
    }
    fclose(fp);

    close(fd);*/
