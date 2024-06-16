#ifndef _NCURSES PROJECT_
#정의 _NCURSES PROJECT_
#include <ncursesw/curses.h>
#include <utility>
#include <스트링>
#include <아이오스트림>

학급체 {
공개:
 xx;
 인티(inty);
 본문 *다음;
 body(int x, inty, body * next = nullptr);
};

반장 {
공개:
 xx;
 인티(inty);
 강직하게;
 최대치의

 본문 *다음;
 헤드(int x, inty, body *n = nullptr); 
};

void remove (WINDOW *win, int &x, int &y, int gateList[21]]);//x,y 좌표의 색 지우기
// void removeGate(WINDOW *win, int &x, int &y, int gateList[21]]);//x,y 좌표의 색 지우기
void move (WINDOW *win, int & x, int &y, int & color_type);//x,y 좌표에 색 칠하기
void moveGate(WINDOW *win, int &x, int &y);/x,y 좌표에 색 칠하기

void memory (body **p,intx,inty,body *n);/body 객체 생성해서 헤드.다음 에 연결



#endif
