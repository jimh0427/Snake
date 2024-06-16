#include "snake.h"

// void remove(WINDOW *win, int &x, int &y){

//     wattron(win, COLOR_PAIR(1));
//     mvwprintw(win, y, x, "    ");
//     mvwprintw(win, y + 1, x, "    ");
//     wattroff(win, COLOR_PAIR(1));

//     wrefresh(win);
// }


void remove(WINDOW *win, int &x, int &y, int gateList[21][21])
{
    //arr에 쓰이는 좌표와 여기서 쓰이는 좌표가 다르므로 변환을 해줘야함.
    int gateX = (x - 1) / 5;
    int gateY = (y - 1) / 2;

    if (gateList[gateY][gateX] != 0) 
    {
        // 게이트라면 보라색 유지
        wattron(win, COLOR_PAIR(6));
    } 
    else 
    {
        // 게이트가 아니라면 흰색으로 변경
        wattron(win, COLOR_PAIR(1));
    }

    mvwprintw(win, y, x, "    ");
    mvwprintw(win, y + 1, x, "    ");
    wattroff(win, COLOR_PAIR(6));
    wattroff(win, COLOR_PAIR(1));

    wrefresh(win);
}

void move(WINDOW *win, int &x, int &y, int &color_type){

    wattron(win, COLOR_PAIR(color_type));
    mvwprintw(win, y, x, "    ");
    mvwprintw(win, y + 1, x, "    ");
    wattroff(win, COLOR_PAIR(color_type));

    wrefresh(win);
}

// void moveGate(WINDOW *win, int &x, int &y){

//     wattron(win, COLOR_PAIR(6));
//     mvwprintw(win, y, x, "    ");
//     mvwprintw(win, y + 1, x, "    ");
//     wattroff(win, COLOR_PAIR(6));

//     wrefresh(win);
// }

void memory(body **p, int x, int y, body *n){
    *p = new body(x, y, n);
}

body::body(int x, int y, body *next) : x(x), y(y), next(next){
    next = nullptr;
}


head::head(int x, int y, body *n) : x(x), y(y){

    body *b1 = new body(x - 5, y);  // 첫 번째 몸통
    body *b2 = new body(x - 10, y); // 두 번째 몸통
    b1->next = b2;
    next = b1;
    len = 3;
    maxlen = len;
}


