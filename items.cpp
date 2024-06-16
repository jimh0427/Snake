#include "items.h"


void makePoison(WINDOW *win, int arr[][21], poison &poison)
{
    int x, y, lifeTime;
    srand(clock());
    while (1)
    {
        x = rand() % 19 + 1;
        y = rand() % 19 + 1;
        lifeTime = rand() % 3 + 2;
        if (arr[y][x] == 0)
        {
            arr[y][x] = 2;
            break;
        }
    }

    poison.poisonList[y][x] = lifeTime;
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, y * 2 + 1, 5 * x + 1, "    ");
    mvwprintw(win, y * 2 + 2, 5 * x + 1, "    ");
    wattroff(win, COLOR_PAIR(4));
    wrefresh(win);
}

void makeItems(WINDOW *win, int arr[][21], item &item)
{
    int x, y, lifeTime;
    srand(clock());
    while (1)
    {
        x = rand() % 19 + 1;
        y = rand() % 19 + 1;
        lifeTime = rand() % 3 + 2;
        if (arr[y][x] == 0)
        {
            arr[y][x] = 1;
            break;
        }
    }

    item.itemList[y][x] = lifeTime;
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, y * 2 + 1, 5 * x + 1, "    ");
    mvwprintw(win, y * 2 + 2, 5 * x + 1, "    ");
    wattroff(win, COLOR_PAIR(3));

    wrefresh(win);
}

void makeCitems(WINDOW *win, int arr[][21], citem &citem)
{
    int x, y, lifeTime;
    srand(clock());
    while (1)
    {
        x = rand() % 19 + 1;
        y = rand() % 19 + 1;
        lifeTime = rand() % 1 + 1;
        if (arr[y][x] == 0)
        {
            arr[y][x] = 5;
            break;
        }
    }

    citem.citemList[y][x] = lifeTime;
    wattron(win, COLOR_PAIR(2)); //검은색
    mvwprintw(win, y * 2 + 1, 5 * x + 1, "    ");
    mvwprintw(win, y * 2 + 2, 5 * x + 1, "    ");
    wattroff(win, COLOR_PAIR(2));

    wrefresh(win);
}




void makeGates(WINDOW *win, int arr[][21], gate &gate, int arrGates[][2], int numberGates,int *p)// gate x,y전부 반환
{
    int a, b, lifeTime;
    srand(clock());
    while (1)
    {
        lifeTime = rand() % 3 + 2;
        a = rand() % numberGates;
        b = rand() % numberGates;
        if(a!=b)
        {
            //gate 겹침 방지
            arr[arrGates[a][0]][arrGates[a][1]] = 4;
            arr[arrGates[b][0]][arrGates[b][1]] = 4;
            break;
        
        }
    }
    //gate 위치 반환
    int* arrGatesPs=p;
    arrGatesPs[0] = arrGates[a][0]; //Y1
    arrGatesPs[1] = arrGates[a][1]; //X1
    arrGatesPs[2] = arrGates[b][0]; //Y2
    arrGatesPs[3] = arrGates[b][1]; //X2

    gate.gateList[arrGates[a][0]][arrGates[a][1]] = lifeTime;
    gate.gateList[arrGates[b][0]][arrGates[b][1]] = lifeTime;

    wattron(win, COLOR_PAIR(6));    
    mvwprintw(win, arrGates[a][0] * 2 + 1, 5 * arrGates[a][1] + 1, "    ");
    mvwprintw(win, arrGates[a][0] * 2 + 2, 5 * arrGates[a][1] + 1, "    ");
    mvwprintw(win, arrGates[b][0] * 2 + 1, 5 * arrGates[b][1] + 1, "    ");
    mvwprintw(win, arrGates[b][0] * 2 + 2, 5 * arrGates[b][1] + 1, "    ");
    wattroff(win, COLOR_PAIR(6)); 
    wrefresh(win);

    // return arrGatesPs;
}





item::item(int sz)
    {
        for (int x = 0; x < 21; x++)
        {
            for (int y = 0; y < 21; y++)
                itemList[y][x] = 0;
        }
    }

void item::lifeTimeReduce(WINDOW *win, int arr[21][21],int &itemcnt){
    for (int x = 0; x < 21; x++){
        for (int y = 0; y < 21; y++){
            if (itemList[y][x] != 0){
                itemList[y][x] -= 1;
                if (itemList[y][x] == 0){
                    itemcnt-=1;
                    arr[y][x] = 0; // 색칠
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win, y * 2 + 1, 5 * x + 1, "    ");
                    mvwprintw(win, y * 2 + 2, 5 * x + 1, "    ");
                    wattroff(win, COLOR_PAIR(1));
                    wrefresh(win);
                }
            }
        }
    }
}



poison::poison(int sz){
    for (int x = 0; x < 21; x++)
    {
        for (int y = 0; y < 21; y++)
            poisonList[y][x] = 0;
    }
}
void poison::poisonTimeReduce(WINDOW *win, int arr[21][21],int & itemcnt){
    for (int x = 0; x < 21; x++){
        for (int y = 0; y < 21; y++){
            if (poisonList[y][x] != 0){
                poisonList[y][x] -= 1;
                if (poisonList[y][x] == 0){
                    itemcnt-=1;
                    arr[y][x] = 0; // 색칠
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win, y * 2 + 1, 5 * x + 1, "    ");

                    mvwprintw(win, y * 2 + 2, 5 * x + 1, "    ");

                    wattroff(win, COLOR_PAIR(1));
                    wrefresh(win);
                }
            }
        }
    }
}


citem::citem(int sz)
    {
        for (int x = 0; x < 21; x++)
        {
            for (int y = 0; y < 21; y++)
                citemList[y][x] = 0;
        }
    }

void citem::citemTimeReduce(WINDOW *win, int arr[21][21]){
    for (int x = 0; x < 21; x++){
        for (int y = 0; y < 21; y++){
            if (citemList[y][x] != 0){
                citemList[y][x] -= 1;
                if (citemList[y][x] == 0){
                    arr[y][x] = 0; // 색칠
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win, y * 2 + 1, 5 * x + 1, "    ");
                    mvwprintw(win, y * 2 + 2, 5 * x + 1, "    ");
                    wattroff(win, COLOR_PAIR(1));
                    wrefresh(win);
                }
            }
        }
    }
}

void citem::citemChange(WINDOW *win, int &x, int &y, int& color_type){
    wattron(win, COLOR_PAIR(color_type));
    mvwprintw(win, y, x, "    ");
    mvwprintw(win, y + 1, x, "    ");
    wattroff(win, COLOR_PAIR(color_type));
    wrefresh(win);
}

gate::gate(int sz)
    {
        for (int x = 0; x < 21; x++)
        {
            for (int y = 0; y < 21; y++)
                gateList[y][x] = 0;
        }
    }

void gate::gateTimeReduce(WINDOW *win, int arr[21][21]){
    for (int x = 0; x < 21; x++){
        for (int y = 0; y < 21; y++){
            if (gateList[y][x] != 0){
                gateList[y][x] -= 1;
                if (gateList[y][x] == 0){
                    arr[y][x] = 3; // 색칠
                    wattron(win, COLOR_PAIR(5));
                    mvwprintw(win, y * 2 + 1, 5 * x + 1, "    ");
                    mvwprintw(win, y * 2 + 2, 5 * x + 1, "    ");
                    wrefresh(win);
                    wattroff(win, COLOR_PAIR(5));
                    wrefresh(win);
                }
            }
        }
    }
}
