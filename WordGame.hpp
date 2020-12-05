#ifndef __WORDCHAIN_H__
#define __WORDCHAIN_H__

#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define PERMS 0644
#define MAX_BUF_SIZE 1024
using namespace std;

class WordGame {
  private:
    string before;
    string later;
    vector<string> words;
    vector<string> used;
    vector<string>::iterator iter;
    vector<string>::iterator iter2;
    int usedCount;
    int lifeCount;

  public:
    WordGame();
    ~WordGame();
    void playGame();             // 게임 실행
    bool checkWords(string str); // 사전에 있는 단어인지와 중복 여부 확인
    void loadWords();            // 텍스트 파일 단어 저장
    string comWords(string str); // 컴퓨터 랜덤 단어 선택
};

void WordChainUI();   // 끝말잇기 UI 출력 함수
void WordChainGame(); // 끝말잇기 구현 함수

#endif
