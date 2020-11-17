#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
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

int main(){
    int array_size = 1024;
    char line[200];
    int position = 0;
    vector<string> words;

    ifstream fin("merged.txt");
    if(fin.is_open())
    {
        while(fin.getline(line,sizeof(line)))
        {
            words[position] = line;
            position++;
        }

    }
    srand(time(NULL));
    int random = rand() % 40;
    cout << "컴퓨터 단어 : " << words[random] << endl;
    string text = words[random];
    string endcomword = text.substr(text.length() - 1, text.length());


    char userword[100];
    char line1[100];
    char line2[100];
    char buf[200];
    FILE *fp;
    fp = fopen("merged.txt", "r");

    string firstuserword;
    char enduserword;

    while (true) {
        int num1 = 0;
        int num2 = 0;

        cout << "단어입력 : "; //사용자 단어 입력
        cin >> userword;
        firstuserword = userword[0];

        while (!feof(fp)) { //사용자 단어 입력성공시
            num1++;
            fgets(line1, 100, fp);
            if (strstr(line1, userword) != NULL && firstuserword == endcomword) {
                cout << "성공" << endl;
            }
        }

        enduserword = userword[strlen(userword) - 1];
        while (!feof(fp)) { //컴퓨터 사전에서 찾기
            num2++;
            fgets(line2, 100, fp);
            if (line2[0] == enduserword ) {
                cout << "컴퓨터 : " << line2 << endl;
                endcomword = line2[strlen(line2) - 1, strlen(line2)];
            }
        }
    }
    fclose(fp);
    return 0;
}

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
