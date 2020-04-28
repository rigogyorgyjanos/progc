#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>



#define MAX 25
#define INVALID_AREA 219
void red () {
  printf("\033[1;31m");
}
void yellow() {
  printf("\033[1;33m");
}
void Green() {
  printf("\033[0;32m");
}
void Cyan() {
  printf("\033[0;36m");
}



char area[MAX][MAX];
int p = 0;
int Px = 2,Py = 2;
int Ex = 11,Ey = 11;

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}
/*---------- J�t�kt�r -------------*/
void AreaUpload(char area[MAX][MAX]){
    srand(time(0));
    for(int i = 0 ; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            int r = rand() % 100 + 1;

            if(i == 0 || i == MAX-1 || j == 0 || j == MAX-1 || (r <= 45 && r >= 30)){
                area[i][j] = INVALID_AREA;
            }else{
                area[i][j] = ' ';
            }
        }
    }
    area[1][1] = ' ';
    area[1][2] = ' ';
    area[10][10] = ' ';
}

void AreaPrint(char area[MAX][MAX]){
    Green();
    for(int i = 0 ; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            printf("%c",area[i][j]);
        }
        puts("");
    }
}
/*---------- J�t�kt�r v�ge -------------*/


void Player(){
    yellow();
    gotoxy(Px,Py);
    putchar('X');
    gotoxy(40,40);
    printf("Score: %d",p);
//Ex != Px && Ey != Py
    while(1){
        if(kbhit()){
            Enemy();
            yellow();
            switch(getch()){
                case 77:/*RIGHT KEY*/
                    if(area[Py-1][Px+1-1] == ' '){
                        gotoxy(Px,Py);
                        putchar(' ');
                        gotoxy(++Px,Py);
                        putchar('X');
                        p++;
                        gotoxy(40,40);
                        printf("Score: %d",p);
                    }

                    break;
                case 75:/*LEFT KEY*/
                    if(area[Py-1][Px-1-1] == ' '){
                        gotoxy(Px,Py);
                        putchar(' ');
                        gotoxy(--Px,Py);
                        putchar('X');
                        p++;
                        gotoxy(40,40);
                        printf("Score: %d",p);
                    }

                    break;
                case 72:/*UP KEY*/
                    if(area[Py-1-1][Px-1] == ' '){
                        gotoxy(Px,Py);
                        putchar(' ');
                        gotoxy(Px,--Py);
                        putchar('X');
                        p++;
                        gotoxy(40,40);
                        printf("Score: %d",p);
                    }
                    break;
                case 80:/*DOWN KEY*/
                    if(area[Py+1-1][Px-1] == ' '){
                        gotoxy(Px,Py);
                        putchar(' ');
                        gotoxy(Px,++Py);
                        putchar('X');
                        p++;
                        gotoxy(40,40);
                        printf("Score: %d",p);
                    }
                    break;
            }
        }
                if(Ex == Px && Ey == Py){
            break;
        }


    }
}
void OtGrammElment(){
    gotoxy(0,40);
    puts("You died! Game over! Press ESC to quit.");
    printf("You scored: %d point(s).",p);
    int exit;
    do{

        exit = getch();
    }while(exit != 27);//ESC ascii code
}

void Enemy(){
        red();
        int r = rand() % 100 + 1;
        if(r < 50){
            gotoxy(Ex,Ey);
            putchar(' ');
            if(Ex > Px && area[Ey-1][Ex-1-1] == ' '){
                Ex--;
            }else if ( Ex < Px && area[Ey-1][Ex+1-1] == ' '){
                Ex++;
            }
            gotoxy(Ex,Ey);
            putchar('Y');
        }else{
            gotoxy(Ex,Ey);
            putchar(' ');
            if(Ey > Py && area[Ey-1-1][Ex-1] == ' '){
                Ey--;
            }else if(Ey < Py && area[Ey+1-1][Ex-1] == ' '){
                Ey++;
            }
            gotoxy(Ex,Ey);
            putchar('Y');
        }
}

void RobbanACsar(){
    Cyan();
    puts("Cheers! ;)");
    puts("Press 'S' key to start the session...");
    int s;
    do{

        s = getch();
    }while(s != 115);//ESC ascii code
//s != 83 ||
}
int main()
{

    system("cls");
    RobbanACsar();
    system("cls");
    AreaUpload(area);   // upload
    AreaPrint(area);    // print

    Player();
    OtGrammElment();





    return 0;
}


