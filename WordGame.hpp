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

#define PERMS 0644
#define MAX_BUF_SIZE 1024
using namespace std;

void WordChainUI();   // 끝말잇기 UI 출력 함수
void WordChainGame(); // 끝말잇기 구현 함수

#endif
