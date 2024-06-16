#ifndef _NCURSESPROJECT_
#define _NCURSESPROJECT_
#include <ncursesw/curses.h>
#include <utility>
#include <string>
#include <iostream>

class body{
public:
    int x;
    int y;
    body *next;
    body(int x, int y, body *next = nullptr);
};

class head{
public:
    int x;
    int y;
    int len;
    int maxlen;

    body *next;
    head(int x, int y, body *n = nullptr);   
};

void remove(WINDOW *win, int &x, int &y, int gateList[21][21]);//x,y 좌표의 색 지우기
// void removeGate(WINDOW *win, int &x, int &y, int gateList[21][21]);//x,y 좌표의 색 지우기
void move(WINDOW *win, int &x, int &y, int &color_type);//x,y좌표에 색 칠하기
void moveGate(WINDOW *win, int &x, int &y);//x,y좌표에 색 칠하기

void memory(body **p, int x, int y, body *n);//body 객체 생성해서 head.next에 연결



#endif
