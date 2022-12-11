#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ESD.h"
#define BULLETS 5000

struct bullet{
int x;
int y;
int old_x;
int old_y;
int shot;
};

struct player{
int x;
int y;
int old_x;
int old_y;
};

struct balls{
int x;
int y;
int pos;
int out;
int old_x;
int old_y;
};
typedef struct bullet BULLET;
typedef struct player PLAYER;
typedef struct balls BALLS;

void clrscr1();

int main()
{
    BULLET shots[BULLETS];
    BALLS ball[BULLETS];
    PLAYER player;
    char key;
    int i=0;
    int loop=0;
    int temp=0;

    player.x=24;
    player.y=22;

    player.old_x = 24;
    player.old_y = 22;

    setColor(4*16+7);
    clrscr1();

    for(int k=0; k<BULLETS;k++)
    {
        shots[k].shot = 0;
        ball[k].out=0;
        ball[k].x=0;
        ball[k].y=0;
    }

    box(0,0,48,24);

    gotoxy(player.x, player.y);
    printf("P");
    gotoxy(0,0);

    do
    {
        if(kbhit())
        {
            key=getch();
            if(key==-32)
            {
                key=getch();
            }
            // key management
            switch(key)
            {
            case 77:
                if(player.x<44)player.x+=3;
                break;
            case 75:
               if(player.x>3)player.x-=3;
                break;
            case 's': // bullet is loaded here, and locked for shooting.
                shots[i].shot=1;
                shots[i].x = player.x;
                shots[i].y = player.y-1;
                i++;
                if(i==30)i=0;
                break;

            }
            gotoxy(player.old_x, player.old_y);
            printf(" ");

            gotoxy(player.x, player.y);
            printf("P");

            player.old_x = player.x;
            player.old_y = player.y;
        }

            // keep changing the positions of the bullets shot
            int k=0;
            while(shots[k].shot!=0)
            {
                //save old value before change
                shots[k].old_y = shots[k].y;
                shots[k].old_x = shots[k].x;
                //change old value
                if(shots[k].y>2)shots[k].y--;
                k++;
            }
            // bullets print
            int j=0;
            while(shots[j].shot!=0)
            {
                gotoxy(shots[j].x, shots[j].y);
                printf("%c",254);

                gotoxy(shots[j].old_x, shots[j].old_y);
                printf(" ");
                j++;
            }

            gotoxy(player.x,player.y);

            temp++;


            // drop one ball at a time;
            ball[loop].out = 1;

            if(temp%10==0)loop++;

            //falling balls to shoot.....

            int s=0;
            while(ball[s].out!=0 )
            {
                //update old positions
                ball[s].old_x = ball[s].x;
                ball[s].old_y = ball[s].y;

                if(ball[s].x==0)ball[s].x = 1+rand()%16*2;
                //change the y position of the balls
                if(ball[s].y<=15)ball[s].y++;

                s++;
            }

            int d=0;

            //print the balls

            while(ball[d].out!=0)
            {
               // Sleep(20);

                gotoxy(ball[d].x, ball[d].y);
                printf("%c",224);

                gotoxy(ball[d].old_x,ball[d].old_y);
                printf(" ");

                d++;
            }


            if(loop==30)
            {
                loop=0;
                for(int k=0; k<BULLETS;k++)
                {
                    shots[k].shot = 0;
                    ball[k].out=0;
                    ball[k].x=0;
                    ball[k].y=0;
                }
            }

            Sleep(100);




    }while(key!=27);


    getch();

    return 0;
}


void clrscr1()
{
    for(int y=0;y<30;y++)
    {
        for(int x=0; x<50;x++)
        {
            gotoxy(x,y);
            printf(" ");
        }
    }
    gotoxy(0,0);
}
