#ifndef _ITEMS_
#정의 _ITEMS_

#include <욕을 참다.h>
# include <ctime>
#include <stdlib>.h>
#include <utility>
#include <스트링>
#include <아이오스트림>
#include <어레이>

//독극물 의 수명 을 관리하는 배열 독극물 목록. 
// 존재하는 모든 포이즌 의 수명 을 1 감소시키는 함수 포이즌 시간 단축.
등급 독극물 {
공개:
 독극물 목록[21][21];
 독(int sz)
 void poison Time Reduce(WINDOW *win, intar[21]);
};

// poison과 동일함
클래스 항목 {
공개:
 항목 목록[21][21];
 항목(int sz);
 void Life Time Reduce(WINDOW *win, intar[21]);
};

계급명제{
공개:
 intemList[21][21];
 citem(int sz);
 시템을 무효로 하다시간 단축(WINDOW *win, intar[21]);
 void citem Change(WINDOW *win, int&x, int&y, int&color_type);
};

클래스 게이트 {
공개:
 intitList[21][21];
 게이트(int sz);
 void gateTimeReduce(WINDOW *win, intar[21]);
};

void make poison (WINDOW *win, intar[21], poison & poison);//poison arr[][]값이 0(빈공간) 인 점 랜덤하게 찾기, 평생 값 랜덤하게 생성.
void make items(WINDOW *win, intar[21], item & item);
void make Citems(WINDOW *win, intar[21], citem & citem);

void makeGates(WINDOW *win, intar[21], gate & gate, intarGates[2], intumberGates, int* p); // 게이트 위치를 정수 4 개로 반환



#endif
