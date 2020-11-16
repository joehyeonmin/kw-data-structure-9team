#include "wordGame.h"
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644
#define MAX_BUF_SIZE 1024
using namespace std;

int main() {
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
        cout << comword << endl;
    } while (rsize > 0);

    cout << "컴퓨터 : " << comword[random] << endl;
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
                    cout << "다시입력해주세요" << endl;
                }
            }
        }
    }
    fclose(fp);

    close(fd);
    return 0;
}
