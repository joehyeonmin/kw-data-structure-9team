# kw-data-structure-9team
광운대학교 자료구조실습 9조 프로젝트입니다.

# description
본 프로젝트에서는 ncurses 라이브러리를 사용합니다.

'fatal error: ncurses.h: No such file or directory' 오류가 뜬다면

1. (root 계정 비활성화일 때) 'sudo passwd root' 를 입력하고 비밀번호를 설정합니다.

2. 터미널에 'su - root'를 입력하고 root 계정으로 로그인합니다. 

3. 터미널에 apt-get install libncurses5-dev libncursesw5-dev 를 입력해 관련 라이브러리를 설치합니다.

4. 빌드할 때, -lncurses 옵션을 붙여야 합니다.

**change.cpp 파일 빌드 방법

g++ -std=c++11 change.cpp -o change
