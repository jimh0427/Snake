#include "snake.h"

// 보이드 제거 (WINDOW *win, int &x, int &y){

// 와트론(승용, COLOR_PAIR(1));
// mvwprintw(win, y, x, "");
// mvwprintw(win, y + 1, x, "");
// 와트오프(승차, COLOR_PAIR(1));

// 새로고침(승리);
// }


void remove (WINDOW *win, int &x, int &y, int gateList[21]])
{
 //arr에 쓰이는 좌표와 여기서 쓰이는 좌표가 다르므로 변환을 해줘야함.
 게이트 X = (x - 1) / 5;
 입구 Y = (y - 1) / 2;

 if (gateList[gateY][gateX]!= 0) 
 {
 // 게이트라면 보라색 유지
 와트론(승용, COLOR_PAIR(6));
 } 
 또 다른 
 {
 // 게이트가 아니라면 흰색으로 변경
 와트론(승용, COLOR_PAIR(1));
 }

 mvwprintw(win, y, x, "");
 mvwprintw(win, y + 1, x, "");
 와트오프(승차, COLOR_PAIR(6));
 와트오프(승차, COLOR_PAIR(1));

 새로고침(승리);
}

보이드 무브(WINDOW *win, int & x, int &y, int & color_type){

 와트론(win, COLOR_PAIR(color_type));
 mvwprintw(win, y, x, "");
 mvwprintw(win, y + 1, x, "");
 wattroff(win, COLOR_PAIR(color_type));

 새로고침(승리);
}

void moveGate(WINDOW *win, int &x, int &y){

 와트론(승용, COLOR_PAIR(6));
 mvwprintw(win, y, x, "");
 mvwprintw(win, y + 1, x, "");
 와트오프(승차, COLOR_PAIR(6));

 새로고침(승리);
}

void memory(body **p, int x, inty, body *n){
 *p = new body(x, y, n);
}

body:body(int x, inty, body * next): x(x), y(y), next(next){
 next = nullptr;
}


머리: 머리(int x, inty, body *n): x(x), y(y){

 body *b1 = new body (x - 5, y); // 첫 번째 몸통
 body *b2 = new body (x - 10, y); // 두 번째 몸통
 b1->next = b2;
 next = b1;
 len = 3;
 maxlen = len;
}


