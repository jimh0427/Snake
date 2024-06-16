#ifndef _ITEMS_
#define _ITEMS_

#include <ncursesw/curses.h>
#include <ctime>
#include <stdlib.h>
#include <utility>
#include <string>
#include <iostream>
#include <array>

//poison의 lifetime을 관리하는 배열poisonList. 
//존재하는 모든 poison의 lifetime을 1 감소시키는 함수 poisonTimeReduce.
class poison{
public:
    int poisonList[21][21];
    poison(int sz);
    void poisonTimeReduce(WINDOW *win, int arr[21][21],int & itemcnt);
};

//poison과 동일함
class item{
public:
    int itemList[21][21];
    item(int sz);
    void lifeTimeReduce(WINDOW *win, int arr[21][21],int& itemcnt);
};

class citem{
public:
    int citemList[21][21];
    citem(int sz);
    void citemTimeReduce(WINDOW *win, int arr[21][21]);
    void citemChange(WINDOW *win, int &x, int &y,int& color_type);
};

class gate{
public:
    int gateList[21][21];
    gate(int sz);
    void gateTimeReduce(WINDOW *win, int arr[21][21]);
};

void makePoison(WINDOW *win, int arr[][21], poison &poison);//poison arr[][]값이 0(빈공간)인 점 랜덤하게 찾기. lifetime 값 랜덤하게 생성. 
void makeItems(WINDOW *win, int arr[][21], item &item);
void makeCitems(WINDOW *win, int arr[][21], citem &citem);

void makeGates(WINDOW *win, int arr[][21], gate &gate, int arrGates[][2], int numberGates, int* p); // gate 위치를 정수 4개로 반환



#endif
