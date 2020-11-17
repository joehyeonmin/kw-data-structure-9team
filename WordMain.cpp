#include "WordGame.hpp"

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

void WordChainGame() {
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

    /*move(19, 1);
    cout << "3초 후 게임이 시작됩니다." << endl;
    sleep(3);
    move(19, 1);
    cout << "                                       ";*/

    // move(6, 1);
    cout << "컴퓨터 : " << sleep(1) << comword[random] << endl;
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
}
