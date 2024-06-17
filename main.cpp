// 뱀: -1 빈 공간: 0 item:1 poison:2 벽 :3  게이트:4  citem:5 벽생성지역:9
#include <ncursesw/curses.h>
#include <locale.h>
#include <ctime>
#include <stdlib.h>
#include "snake.h"
#include "items.h"
#include <string>
#include <iostream>









int main()
{
    setlocale(LC_ALL, "ko_KR.utf8");
    initscr();
    box(stdscr, 0, 0);
    WINDOW *win = subwin(stdscr, 42 + 2, 5 * 21 + 1, 1, 5);
    box(win, 0, 0);

    WINDOW *win2 = subwin(stdscr, 17, 45, 1, 112); //Score Board
    box(win2, 0, 0);
    WINDOW *win3 = subwin(stdscr, 15, 45, 19, 112); //Mission
    box(win3, 0, 0);


    start_color();
    
    init_pair(1, COLOR_RED, COLOR_WHITE); //빨간 글씨 , 하얀배경
    init_pair(2, COLOR_WHITE, COLOR_BLACK); //검정
    init_pair(3, COLOR_WHITE, COLOR_GREEN); //초록
    init_pair(4, COLOR_WHITE, COLOR_RED); //빨강
    init_pair(5, COLOR_CYAN, COLOR_CYAN); //하늘
    init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA); //보라
    init_pair(7, COLOR_WHITE, COLOR_YELLOW); //노랑

    init_color(10,1000,550,800);
    init_color(11,800,1000,550); 
    init_color(12,0,800,800);
    
    init_pair(8,10,10);//연분홍
    init_pair(9,11,11);//형광초록
    init_pair(10,12,12); //짙은보라

    
    
    int color_type=7; //snake의 color를 결정, 처음은 노란색
    int map_change=0;
    int past_map_change=0;

    attron(COLOR_PAIR(1));
    printw("SnakeGame");
    attroff(COLOR_PAIR(1));
    wrefresh(win);
    while(map_change<4){
        past_map_change=map_change; //++ 되기 전의 값을 담아두어 next turn인지 game over인지 체크
        wbkgd(win, COLOR_PAIR(2)); //검은색 배경 설정
        int valueing=1; //1~4맵 벽 1번 생성에 씀
        int valueing4=1; // 4맵 2번째 벽 1번 생성에 씀
        box(stdscr, 0, 0);
        box(win, 0, 0);
        box(win2, 0, 0);
        box(win3, 0, 0);
        int arr[21][21] = {};//뱀,벽,아이템 위치를 담을 배열

        // std::pair<int, int> arrGates[442];
        int arrGates[442][2]; //for 구문 순서대로 벽의 인덱스를 집어넣는 배열. 벽 추가 -> makeGates 나머지 연산 증가 필요.
        int numberGates = 0;
        int itemcnt=0;
        //map 만들기
        switch(map_change){
        case 3:
            for (int i = 0; i < 21; i++){
                for (int j = 0; j < 21; j++){
                    if (((i==6)&&(2<j && j<10))||((j==3)&&(i<12 && i>3))||((i==15)&&(9<j && j<18))||((j==14)&&(i<18 && i>8))||((i==0)||(i==20)||(j==0)||(j==20))){
                        if(((i==0)&&(j==0))||((i==0)&&(j==20))||((i==20)&&(j==0))||((i==20)&&(j==20))||((i==15)&&(j==14)))
                        {   
                            arr[i][j] = 6;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                        }
                        else
                        {
                            arr[i][j]=3;
                            arrGates[numberGates][0] = i; //gate의 y 값
                            arrGates[numberGates][1] = j; //gate의 x 값
                            numberGates+=1;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                        }
                    }
                    else{
                        arr[i][j] = 0;
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                        mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                        wattroff(win, COLOR_PAIR(1));
                    }
                }
            }
            break;

        case 2:
            for (int i = 0; i < 21; i++){
                for (int j = 0; j < 21; j++){
                    if (((i==13)&&(13<j && j<18))||((j==14)&&(i<13 && i>5))||((i==0)||(i==20)||(j==0)||(j==20))){
                        if(((i==0)&&(j==0))||((i==0)&&(j==20))||((i==20)&&(j==0))||((i==20)&&(j==20)))
                        {   
                            arr[i][j] = 6;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                        }
                        else
                        {
                            arr[i][j]=3;
                            arrGates[numberGates][0] = i; //gate의 y 값
                            arrGates[numberGates][1] = j; //gate의 x 값
                            numberGates+=1;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                        }
                    }
                    else{
                        arr[i][j] = 0;
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                        mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                        wattroff(win, COLOR_PAIR(1));
                    }
                }
            } 
            break;

        case 1:
            for (int i = 0; i < 21; i++){
                for (int j = 0; j < 21; j++){
                    if (((i==10)&&(2<j && j<12))||((j==10)&&(i<15 && i>5))||((i==0)||(i==20)||(j==0)||(j==20))){
                        if(((i==0)&&(j==0))||((i==0)&&(j==20))||((i==20)&&(j==0))||((i==20)&&(j==20))||((i==10)&&(j==10)))
                        {   
                            arr[i][j] = 6;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                        }
                        else
                        {
                            arr[i][j]=3;
                            arrGates[numberGates][0] = i; //gate의 y 값
                            arrGates[numberGates][1] = j; //gate의 x 값
                            numberGates+=1;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                        }
                    }
                    else{
                        arr[i][j] = 0;
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                        mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                        wattroff(win, COLOR_PAIR(1));
                    }
                }
            } 
            break;
        case 0:
            for (int i = 0; i < 21; i++){
                for (int j = 0; j < 21; j++){
                    if ((i==0)||(i==20)||(j==0)||(j==20)){
                        if(((i==0)&&(j==0))||((i==0)&&(j==20))||((i==20)&&(j==0))||((i==20)&&(j==20)))
                        {   
                            arr[i][j] = 6;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                        }
                        else
                        {
                            arr[i][j]=3;
                            arrGates[numberGates][0] = i; //gate의 y 값
                            arrGates[numberGates][1] = j; //gate의 x 값
                            numberGates+=1;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                        }
                    }
                    else{
                        arr[i][j] = 0;
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                        mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                        wattroff(win, COLOR_PAIR(1));
                    }
                }
            } 
            break;
        }

        noecho();
        int x, y, dy, dx, ch, gateY1, gateX1, gateY2, gateX2 ,gateY, gateX; //gateY1~gateX2 == makegates의 반환값, gateY,gateX == snake가 순간이동할 gate
        char direction;
        x = 31;
        y = 15;
        dx = 1;
        dy = 0;
        head h(x, y);
        //head에서 몸길이 3 변경
        body* b1 = new body(x - 5, y);  // 1번 몸
        body* b2 = new body(x - 10, y); // 2번 몸
        int a1=x-5;
        int a2=x-10;
        move(win, a1, y, color_type);
        move(win, a2, y, color_type);
        
        h.next = b1;
        b1->next = b2;
        h.len = 3;
        

        //Board, Mission
        int eat_growth=0;
        int eat_poison=0;
        int eat_citem=0;
        int use_gate=0;

    


    
        int growth_mission[4]={1,2,3,4};
        int posion_mission[4]={1,2,3,4};
        int gate_mission[4]={1,1,2,2};

        char len_check=' ';
        char growth_check=' ';
        char posion_check=' ';
        char gate_check=' ';

        mvwprintw(win2, 2, 28, "TURN : ( %d / 4 )",map_change+1);
        mvwprintw(win2, 3, 4, "Score Board");
        mvwprintw(win2, 5, 4, "B: ( %d ) / ( %d )", h.len, h.maxlen);;
        mvwprintw(win2, 7, 4, "+: ( %d )", eat_growth);
        mvwprintw(win2, 9, 4, "-: ( %d )", eat_poison);
        mvwprintw(win2, 11, 4, "G: ( %d )", use_gate);
        mvwprintw(win2, 13, 4, "Color Change: ( %d )", eat_citem);

        mvwprintw(win3, 3, 4, "Misson");
        mvwprintw(win3, 5, 4, "B: 10 ( %c )", len_check);
        mvwprintw(win3, 7, 4, "+: %d ( %c )", growth_mission[map_change], growth_check);
        mvwprintw(win3, 9, 4, "-: %d ( %c )", posion_mission[map_change], posion_check);
        mvwprintw(win3, 11, 4, "G: %d ( %c )",  gate_mission[map_change], gate_check);

        wrefresh(win2);
        wrefresh(win3);
        
        
        curs_set(0);
        wattron(win, COLOR_PAIR(color_type));
        mvwprintw(win, y, x, "    ");
        mvwprintw(win, y + 1, x, "    ");
        wattroff(win, COLOR_PAIR(color_type));
        keypad(stdscr, 1);
        arr[(y - 1) / 2][(x - 1) / 5] = 2;
        wrefresh(win);

        clock_t delay = 0.5 * CLOCKS_PER_SEC;   // 0.5초 간격으로 반복(이동)
        clock_t delayItem = 2 * CLOCKS_PER_SEC; // 2초 간격으로 반복(item생성)
        clock_t ptime = clock();
        clock_t ptimeItem = clock();
        clock_t ptimeGate = clock();
        clock_t dtime=clock();
        nodelay(stdscr, true); // kbhit과 같은 효과.(키입력을 기다리지 않음. 키입력이 들어오지않으면 ERR을 리턴)
        item items(21);
        poison poisons(21);
        citem citems(21);
        gate gates(21);
        char state = 'g';
        dx = 5;
        dy = 0;
        
        int citem_appear=0;
        int gateFirstProduce=1; // 첫 gate생성에만 씀

        int whileTrue = 1; // state == n, h.len<=3 일 때, whileTrue =0(반복문 종료)
        clock_t gametime=clock();
        while (whileTrue)
        {   
            if ((clock() - dtime) >= 10*CLOCKS_PER_SEC){
                dtime=clock();
                if (delay>0.2*CLOCKS_PER_SEC){
                    delay-= 0.2*CLOCKS_PER_SEC;
                }
            }
            ch = getch();
            state = 'g';
            switch (ch)
            {
            //키 입력에 따라 direction 설정
            case KEY_UP:
                dx = 0;
                dy = -2;
                break;

            case KEY_DOWN:
                dx = 0;
                dy = 2;
                break;

            case KEY_RIGHT:
                dx = 5;
                dy = 0;
                break;

            case KEY_LEFT:
                dx = -5;
                dy = 0;
                break;
            }
            if ((clock() - ptime) >= delay)
            {
                ptime = clock();
                memory(&h.next, h.x, h.y, h.next);//현재 head가 가리키는 좌표를 body 객체로 생성. head.next에 연결
                h.len += 1;
                //좌표 이동
                x = h.x + dx;
                y = h.y + dy;
                //이동한 곳이 벽이거나 snake면 break
                //arr에 쓰이는 좌표와 여기서 쓰이는 좌표가 다르므로 변환을 해줘야함.
                if ((arr[(y-1)/2][(x-1)/5]==3) ||(arr[(y-1)/2][(x-1)/5]==-1)){
                    map_change = 4; // 57번 줄 while 빠져나감 gameover
                    break;
                }
                h.x = x;//head의 좌표 갱신
                h.y = y;
                //이동한 곳이 gate
                if (arr[(y - 1) / 2][(x - 1) / 5] == 4)
                {
                    // state = 's'; //state=g remove(배경색 흰색) -> state=s remove(배경색 보라색)
                    //gate 수명을 snake 길이만큼 증가
                    gates.gateList[gateY1][gateX1] += h.len;
                    gates.gateList[gateY2][gateX2] += h.len;
                    //닿은 gate와 순간이동할 gate(gateY,gateX) 구별 필요
                    if((gateY1 == (y-1)/2) && (gateX1 == (x-1)/5)) {gateY = gateY2; gateX = gateX2;}
                    else {gateY = gateY1; gateX = gateX1;}

                    int direction[4][2]={{5,0},{0,-2},{-5,0},{0,2}};
                    int idx;
                    
                    if (dx==5&&dy==0){
                        idx=0;
                    }     
                    else if (dx==0&&dy==-2){
                        idx=1;
                    }       
                    else if (dx==-5&&dy==0){
                        idx=2;
                    }       
                    else if (dx==0&&dy==2){
                        idx=3;
                    }
                    int realGy = gateY*2+1;
                    int realGx = gateX*5+1;
                    int count=idx;
                    for (int i=0;i<4;i++){
                        int ny=realGy+direction[count][1];
                        int nx=realGx+direction[count][0];
                        if( ((0 > (nx-1)/5) || ((nx-1)/5 > 20)) || ((0 > (ny-1)/2) || (ny-1)/2 > 20) ){ //갈 수 없는 곳 검사
                            count=(count+1)%4;
                            continue;
                        }
                        if(arr[(ny-1)/2][(nx-1)/5]==0||arr[(ny-1)/2][(nx-1)/5]==1||arr[(ny-1)/2][(nx-1)/5]==2||arr[(ny-1)/2][(nx-1)/5]==5){ //갈 수 있는 곳 
                            h.x = nx;
                            h.y = ny;
                            dy=direction[count][1];
                            dx=direction[count][0];
                            move(win, nx, ny, color_type);
                            break;
                        }
                        count=(count+1)%4;
                    }
                    use_gate+=1;
                }
                
                //이동한 곳이 item이면 state=p로 설정. p면 꼬리 자르는 코드가 실행되지 않음
                else if (arr[(y - 1) / 2][(x - 1) / 5] == 1)
                {   itemcnt-=1;
                    state = 'p';
                    items.itemList[(y - 1) / 2][(x - 1) / 5] = 0;
                    eat_growth+=1;
                    move(win, x, y, color_type);
                    
                }
                //이동한 곳이 poison이면 state=n으로 설정. n이면 꼬리를 두번 잘라냄
                else if (arr[(y - 1) / 2][(x - 1) / 5] == 2)
                {   itemcnt-=1;
                    state = 'n';
                    poisons.poisonList[(y - 1) / 2][(x - 1) / 5] = 0;
                    eat_poison+=1;
                    move(win, x, y, color_type);
                }
                else if (arr[(y - 1) / 2][(x - 1) / 5] == 5)
                {   
                    while(true){
                        srand(clock());
                        int new_color_type = rand()%4+7;
                        if (color_type!=new_color_type){
                            color_type=new_color_type;
                            break;
                        }
                    }
                    citems.citemList[(y - 1) / 2][(x - 1) / 5] = 0;
                    eat_citem+=1;

                    move(win, x, y, color_type);
                }

                //해당사항이 없다면 default값으로 state=g. g면 꼬리 한번 잘라냄. head 생성하고 꼬리 한번 자르는 방식으로 이동 구현.
                else {move(win, x, y, color_type);}
                arr[(h.y - 1) / 2][(h.x - 1) / 5] = -1;//arr에 snake의 머리 좌표 입력.


                if (state == 'g')
                {               
                    body *p = h.next;//꼬리 한칸 앞의 body객체를 찾음.
                    for (int i = 0; i < h.len - 3; i++)
                    {
                        p = (*p).next;
                    }
                    body *lastBody = (*p).next;//꼬리 찾기

                    h.len -= 1;

                    remove(win, (*lastBody).x, (*lastBody).y, gates.gateList);
                    arr[((*lastBody).y - 1) / 2][((*lastBody).x - 1) / 5] = 0;
                    delete (*p).next;
                    (*p).next = nullptr;
                }            
                
                else if (state == 'n')//이 경우 위의 꼬리자르기 코드가 두번 동작함.
                {
                    for (int i=0;i<2;i++){
                        if (h.len == 3) //기존 h.len == 2
                        {
                            body *p = h.next;
                            for (int i = 0; i < h.len - 3; i++)
                            {
                                p = (*p).next;
                            }
                            body *lastBody = (*p).next;

                            h.len -= 1;

                            remove(win, (*lastBody).x, (*lastBody).y, gates.gateList);
                            arr[((*lastBody).y - 1) / 2][((*lastBody).x - 1) / 5] = 0;
                            delete (*p).next;
                            (*p).next = nullptr;
                            whileTrue = 0;
                            map_change = 4; // 57번 줄 while 빠져나감 gameover
                            break;
                        }
                        else
                        {
                            body *p = h.next;
                            for (int i = 0; i < h.len - 3; i++)
                            {
                                p = (*p).next;
                            }
                            body *lastBody = (*p).next;

                            h.len -= 1;

                            remove(win, (*lastBody).x, (*lastBody).y, gates.gateList);
                            arr[((*lastBody).y - 1) / 2][((*lastBody).x - 1) / 5] = 0;
                            delete (*p).next;
                            (*p).next = nullptr;
                        }
                    }
                }

                if (h.len >= h.maxlen) {h.maxlen = h.len;}
                if (h.maxlen >= 10) {len_check = 'v';}
                if (eat_growth >= growth_mission[map_change]) {growth_check = 'v';}
                if(eat_poison >= posion_mission[map_change]) {posion_check ='v';}
                if(use_gate >= gate_mission[map_change]) {gate_check='v';}
                mvwprintw(win2, 2, 28, "TURN : ( %d / 4 )",map_change+1);
                mvwprintw(win2, 5, 4, "B: ( %d ) / ( %d )", h.len, h.maxlen);;
                mvwprintw(win2, 7, 4, "+: ( %d )", eat_growth);
                mvwprintw(win2, 9, 4, "-: ( %d )", eat_poison);
                mvwprintw(win2, 11, 4, "G: ( %d )", use_gate);
                mvwprintw(win2, 13, 4, "Color Change: ( %d )", eat_citem);
                mvwprintw(win3, 5, 4, "B: 10 ( %c )", len_check);
                mvwprintw(win3, 7, 4, "+: %d ( %c )", growth_mission[map_change], growth_check);
                mvwprintw(win3, 9, 4, "-: %d ( %c )", posion_mission[map_change], posion_check);
                mvwprintw(win3, 11, 4, "G: %d ( %c )",  gate_mission[map_change], gate_check);
                mvwprintw(win2, 15, 4, "Game Time:  %ld sec", (clock()-gametime)/CLOCKS_PER_SEC);
                wrefresh(win2);
                wrefresh(win3);
                if (len_check=='v'&&growth_check=='v'&&posion_check=='v'&&gate_check=='v'){
                    break;
                }
                wrefresh(win);
            }
            if ((clock() - ptimeItem) >= delayItem)//설정한 시간마다 반복
            {   
                ptimeItem = clock();
                items.lifeTimeReduce(win, arr,itemcnt);//모든 lifetime 1 감소(lifeTime = rand() % 3 + 2)
                poisons.poisonTimeReduce(win, arr,itemcnt);
                if (itemcnt<3){
                    srand(clock());
                    int selectItem = rand() % 2;
                    if (selectItem){
                        makeItems(win, arr, items);//랜덤 위치에 생성
                        itemcnt+=1;
                    }
                    else{
                        makePoison(win, arr, poisons);
                        itemcnt+=1;
                        }
                    }
                if (citem_appear%3==0){
                    citems.citemTimeReduce(win, arr);
                    makeCitems(win, arr, citems);
                }
                citem_appear+=1;
                if (arr[gateY1][gateX1] != -1 || arr[gateY2][gateX2] != -1&&gates.gateList[gateY2][gateX2]!=0&&gates.gateList[gateY1][gateX1]!=0) //snake가 gate위에 없다면, gate 수명 단축(gateTimeReduce)
                { 
                    gates.gateTimeReduce(win, arr); //gate time 1 감소()
                    
                    if((gateFirstProduce == 1) || (arr[gateY2][gateX2]==3&&arr[gateY1][gateX1]==3&&gates.gateList[gateY2][gateX2]==0&&gates.gateList[gateY1][gateX1]==0)) //gate가 존재하는지 검사
                    {
                        int arrGatsPs[4]={0};
                        makeGates(win, arr, gates, arrGates, numberGates,arrGatsPs); //gate의 x,y값 받아옴 (0~20)
                        gateY1 = arrGatsPs[0];
                        gateX1 = arrGatsPs[1];
                        gateY2 = arrGatsPs[2];
                        gateX2 = arrGatsPs[3];
                        gateFirstProduce=0; //첫 gate 생성에만 씀
                } 
                }
            }
            int check=0; // 스네이크가 벽에 있으면, while break, gameover
            body *p = h.next;
            for (int i = 0; i < h.len -2; i++)
                    {
                        p = (*p).next;
                        if(arr[((*p).y-1)/2][((*p).x-1)/5]==3) //스네이크 몸통 벽에 닿았는지 검사
                        {
                            check =1;
                            break;
                        }
                    }
            if(arr[(h.y-1)/2][(h.x-1)/5]==3){check =1;} // 스네이크 머리 검사
            if(check){map_change=4; break;}//while ``br`ea`k``
            if (map_change==0){
                if ((clock()-ptimeGate>2*CLOCKS_PER_SEC) && (clock()-ptimeGate<6*CLOCKS_PER_SEC)) //5초 경과
                {
                    for(int j=10; j<18; ++j){
                        arr[4][j] = 9;
                        wattron(win, COLOR_PAIR(9));
                        mvwprintw(win, 4 * 2 + 1, 5 * j + 1, "    ");
                        mvwprintw(win, 4 * 2 + 2, 5 * j + 1, "    ");
                        wattroff(win, COLOR_PAIR(9));
                    }
                }
                else if(clock()-ptimeGate>=6* CLOCKS_PER_SEC && clock()-ptimeGate<=7* CLOCKS_PER_SEC)
                {
                    if(valueing)
                    {   
                        for(int j=10; j<18; ++j){
                        arr[4][j] = 3;
                        arrGates[numberGates][0] = 4; //gate의 y 값
                        arrGates[numberGates][1] = j; //gate의 x 값
                        numberGates+=1;
                        wattron(win, COLOR_PAIR(5));
                        mvwprintw(win, 4 * 2 + 1, 5 * j + 1, "    ");
                        mvwprintw(win, 4 * 2 + 2, 5 * j + 1, "    ");
                        wattroff(win, COLOR_PAIR(5));
                        }
                        valueing =0;
                    }
                }
            }
            else if(map_change==1){
                if ((clock()-ptimeGate>2*CLOCKS_PER_SEC) && (clock()-ptimeGate<4*CLOCKS_PER_SEC)) //5초 경과
                {
                for (int i = 11; i<17; ++i){
                    for (int j=12; j<18; ++j){
                        if(((i==16)&&(11<j&& j<18))||((i>10&&i<17)&&(j==17))){
                            wattron(win, COLOR_PAIR(9));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(9));
                            }
                        }
                    }
                }
                else if(clock()-ptimeGate>=4* CLOCKS_PER_SEC && clock()-ptimeGate<=5* CLOCKS_PER_SEC)
                {
                if(valueing)
                {   
                for (int i = 11; i<17; ++i){
                    for (int j=12; j<18; ++j){
                        if(((i==16)&&(11<j&& j<18))||((i>10&&i<17)&&(j==17))){
                            arr[i][j] = 3;
                            arrGates[numberGates][0] = i; //gate의 y 값
                            arrGates[numberGates][1] = j; //gate의 x 값
                            numberGates+=1;
                            wattron(win, COLOR_PAIR(5));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(5));
                            }
                        }
                    }
                    valueing =0;
                }
                    
                }      
            }
            else if(map_change==2){
                if ((clock()-ptimeGate>2*CLOCKS_PER_SEC) && (clock()-ptimeGate<4*CLOCKS_PER_SEC)) //5초 경과
                {
                for (int i = 10; i<17; ++i){
                    for (int j=4; j<11; ++j){
                        if(((i==10)&&(3<j&& j<11))||((i>9&&i<17)&&(j==10))){
                            wattron(win, COLOR_PAIR(9));
                            mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                            mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                            wattroff(win, COLOR_PAIR(9));
                            }
                        }
                    }

                }
                else if(clock()-ptimeGate>=4* CLOCKS_PER_SEC && clock()-ptimeGate<=5* CLOCKS_PER_SEC)
                {
                    if(valueing)
                    {   
                    for (int i = 10; i<17; ++i){
                        for (int j=4; j<11; ++j){
                            if(((i==10)&&(3<j&& j<11))||((i>9&&i<17)&&(j==10))){
                                arr[i][j] = 3;
                                arrGates[numberGates][0] = i; //gate의 y 값
                                arrGates[numberGates][1] = j; //gate의 x 값
                                numberGates+=1;
                                wattron(win, COLOR_PAIR(5));
                                mvwprintw(win, i * 2 + 1, 5 * j + 1, "    ");
                                mvwprintw(win, i * 2 + 2, 5 * j + 1, "    ");
                                wattroff(win, COLOR_PAIR(5));
                                }
                            }
                        }
                        valueing =0;
                    }       
                }
            }
            else if(map_change==3){
                if ((clock()-ptimeGate>2*CLOCKS_PER_SEC) && (clock()-ptimeGate<4*CLOCKS_PER_SEC)) //2~4초 경과
                {
                for(int j=12; j<18; ++j){
                    arr[4][j] = 9;
                    wattron(win, COLOR_PAIR(9));
                    mvwprintw(win, 4 * 2 + 1, 5 * j + 1, "    ");
                    mvwprintw(win, 4 * 2 + 2, 5 * j + 1, "    ");
                    wattroff(win, COLOR_PAIR(9));
                    }
                }
                else if(clock()-ptimeGate>=4* CLOCKS_PER_SEC && clock()-ptimeGate<=5* CLOCKS_PER_SEC) //4~5초 경과
                {
                    if(valueing)
                    {   
                        for(int j=12; j<18; ++j){
                        arr[4][j] = 3;
                        arrGates[numberGates][0] = 4; //gate의 y 값
                        arrGates[numberGates][1] = j; //gate의 x 값
                        numberGates+=1;
                        wattron(win, COLOR_PAIR(5));
                        mvwprintw(win, 4 * 2 + 1, 5 * j + 1, "    ");
                        mvwprintw(win, 4 * 2 + 2, 5 * j + 1, "    ");
                        wattroff(win, COLOR_PAIR(5));
                        }
                        valueing =0;
                    }
                }
                else if ((clock()-ptimeGate>6*CLOCKS_PER_SEC) && (clock()-ptimeGate<8*CLOCKS_PER_SEC)) //6~8초 경과
                {
                    for(int i=12; i<18; ++i){
                    arr[i][6] = 9;
                    wattron(win, COLOR_PAIR(9));
                    mvwprintw(win, i * 2 + 1, 5 * 6 + 1, "    ");
                    mvwprintw(win, i * 2 + 2, 5 * 6 + 1, "    ");
                    wattroff(win, COLOR_PAIR(9));
                    }
                }
                else if(clock()-ptimeGate>=9* CLOCKS_PER_SEC && clock()-ptimeGate<=10* CLOCKS_PER_SEC) //4~5초 경과
                {
                    if(valueing4)
                    {   
                        for(int i=12; i<18; ++i){
                        arr[i][6] =3;
                        arrGates[numberGates][0] = i; //gate의 y 값
                        arrGates[numberGates][1] = 6; //gate의 x 값
                        numberGates+=1;
                        wattron(win, COLOR_PAIR(5));
                        mvwprintw(win, i * 2 + 1, 5 * 6 + 1, "    ");
                        mvwprintw(win, i * 2 + 2, 5 * 6 + 1, "    ");
                        wattroff(win, COLOR_PAIR(5));
                        }
                        valueing4 =0;
                    }
                }
            }
            wrefresh(win);
            wrefresh(win2);
        }
        
        if (map_change==past_map_change&& map_change!=3){
            refresh();
            clear();
            box(win,0,0);
            wbkgd(win, COLOR_PAIR(7));

            mvwprintw(win,14,30,"Complete Stage %d          Next Stage %d",map_change+1, map_change+2);
            mvwprintw(win,17,22," _   _  _____ __   __ _____   _____  _   _ ______  _   _ ");
            mvwprintw(win,18,22,"| \\ | ||  ___|\\ \\ / /|_   _| |_   _|| | | || ___ \\| \\ | |");
            mvwprintw(win,19,22,"|  \\| || |__   \\ V /   | |     | |  | | | || |_/ /|  \\| |");
            mvwprintw(win,20,22,"| . ` ||  __|  /   \\   | |     | |  | | | ||    / | . ` |");
            mvwprintw(win,21,22,"| |\\  || |___ / /^\\ \\  | |     | |  | |_| || |\\ \\ | |\\  |");
            mvwprintw(win,22,22,"\\_| \\_/\\____/ \\/   \\/  \\_/     \\_/   \\___/ \\_| \\_|\\_| \\_/");
            mvwprintw(win,24,26,"PRESS ENTER (If you press enter : go next stage)");
            wrefresh(win);

            while(true){
                char asd = getch();
                if (asd=='\n'){
                    clear();
                    break;
                }
            }
        }
        map_change++;
    }
    //끝났을 때 window쓰기
    clear();
    if(map_change==4){
        box(win, 0, 0);
        wbkgd(win, COLOR_PAIR(3));
        mvwprintw(win,18,8,"___  ___ _            _                  _____                           _        _         ");
        mvwprintw(win,19,8,"|  \\/  |(_)          (_)                /  __ \\                         | |      | |        ");
        mvwprintw(win,20,8,"| .  . | _  ___  ___  _   ___   _ __    | /  \\/  ___   _ __ ___   _ __  | |  ___ | |_   ___ ");
        mvwprintw(win,21,8,"| |\\/| || |/ __|/ __|| | / _ \\ | '_ \\   | |     / _ \\ | '_ ` _ \\ | '_ \\ | | / _ \\| __| / _ \\");
        mvwprintw(win,22,8,"| |  | || |\\__ \\\\__ \\| || (_) || | | |  | \\__/\\| (_) || | | | | || |_) || ||  __/| |_ |  __/");
        mvwprintw(win,23,8,"\\_|  |_/|_||___/|___/|_| \\___/ |_| |_|   \\____/ \\___/ |_| |_| |_|| .__/ |_| \\___| \\__| \\___|");
        mvwprintw(win,24,8,"                                                                 | |  ");
        mvwprintw(win,25,8,"                                                                 |_|  ");
        wrefresh(win);

        nodelay(stdscr, false);
        getch();
        endwin();
    }
    else{
        box(win,0,0);
        wbkgd(win, COLOR_PAIR(4));
        mvwprintw(win,18,17," _   _____   ___  ___  ___ _____   _____  _   _  _____ ______   _" );
        mvwprintw(win,19,17,"| | |  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | ||  ___|| ___ \\ | |");
        mvwprintw(win,20,17,"| | | |  \\// /_\\ \\| .  . || |__   | | | || | | || |__  | |_/ / | |");
        mvwprintw(win,21,17,"| | | | __ |  _  || |\\/| ||  __|  | | | || | | ||  __| |    /  | |");
        mvwprintw(win,22,17,"|_| | |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ /| |___ | |\\ \\  |_|");
        mvwprintw(win,23,17,"(_)  \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/ \\____/ \\_| \\_| (_)");
        wrefresh(win);

        nodelay(stdscr, false);
        getch();
        endwin();
    }
    
    return 0;
    
} 
//473 빨노초
