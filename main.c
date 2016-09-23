#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
#include "croco.h"
#include "snake.h"
#include "home.h"
#include "frogger.h"
#include "lose.h"
#include "lo.h"
#include "st.h"
#include "up.h"
#include "down.h"
#include "left.h"
#include "right.h"
#include "winner.h"

enum{START, INSTRUCTIONS, GAMESCREEN, LOSESCREEN, WINSCREEN};
int start();
int instructions();
int gameScreen(int);
void loseScreen();
void winScreen();
int time;
int i = 0;
FROG frog;
FROG *frogp = &frog;

int main()
{
    int seed = 0;
    int state = START;
    while(1)
    {
        switch(state)
        {
            case START:
                seed = start();
                state = INSTRUCTIONS;
                break;

            case INSTRUCTIONS:
                seed = instructions();
                state = GAMESCREEN;
                break;
            case GAMESCREEN:
                state = gameScreen(seed);
                break;
            case WINSCREEN:
                winScreen();
                state = START;
                break;
            case LOSESCREEN:
                loseScreen();
                state = START;
                break;
            default:
                break;
        }
    }
}

int start()
{
    int seed = 0;
    u16 *p = videoBuffer;
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    for(i=0; i<38400; i++)
    {
        *p++ = BLACK;
    }
    drawImage3(5, 5, 240, 160, st);
    drawString(70, 60, "Press Start (Enter)", GREEN);
    while(!KEY_DOWN_NOW(BUTTON_START))
    {
        seed++;
    }
    while(KEY_DOWN_NOW(BUTTON_START));
    return seed;
    
}

int instructions()
{
    int seed = 0;
    u16 *p = videoBuffer;
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    for(i=0; i<38400; i++)
    {
        *p++ = BLACK;
    }
    drawImage3(15, 60, 120, 30, frogger);
    drawString(50, 80, "INSTRUCTIONS", BLACK);
    drawString(55, 80, "------------", BLACK);
    drawString(60, 30, "Use arrow keys to move the frog.", YELLOW);
    drawString(70, 60, "Press Start (Enter)", GREEN);
    while(!KEY_DOWN_NOW(BUTTON_START))
    {
        seed++;
    }
    while(KEY_DOWN_NOW(BUTTON_START));
    return seed;
}

void winScreen()
{
    u16 *p = videoBuffer;
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    for(i=0; i<38400; i++)
    {
        *p++ = BLACK;
    }
    drawImage3(5, 235, 240, 160, winner);
    drawString(50, 80, "CONGRATULATIONS!", BROWN);
    drawString(60, 30, "Press Start (Enter) to continue...", BROWN); 
    while(!KEY_DOWN_NOW(BUTTON_START));
    while(KEY_DOWN_NOW(BUTTON_START));
}

void loseScreen()
{
    u16 *p = videoBuffer;
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    for(i=0; i<38400; i++)
    {
    *p++ = BLACK;
    }
    drawImage3(5, 235, 240, 160, lose);
    drawString(80, 80, "GAME OVER", RED);
    drawString(90, 20, "Press Start (Enter) to continue ...", RED);
    //drawString(20, 5, tme, YELLOW);
    time = 0;
    frogp->lives = 0;
    while(!KEY_DOWN_NOW(BUTTON_START));
    while(KEY_DOWN_NOW(BUTTON_START));
}
int gameScreen(int seed)
{
    fillinScreen(BLACK);
    int timer = 0;
    time = 60;

    //Frog initial position
    frog.row = 145;
    frog.col = 110;
    frogp->oldrow = frogp->row;
    frogp->oldcol = frogp->col;


    


    HOME h[4];
    HOME *hp;
    
    
    int col[4] = { 40, 80, 160, 200 };
    int col2[3] = {60, 120, 180};

    for (int i = 0; i < 3; ++i)
    {
        h[i].row = 15;
        h[i].col = col2[i];
        hp = &h[i];
        
    }
    int h1co = 1;
    int h2co = 1;
    int h3co = 1;

    frogp->lives = 5;
    char buffer[41];
    char buffer1[41];
    REG_DISPCNT = MODE3 | BG2_ENABLE;


    CROC croc[4];
 
    for (int i = 0; i < 4; ++i)
    {
       croc[i].row = 120;
       croc[i].col = col[i];
       croc[i].oldrow = croc[i].row;
       croc[i].oldcol = croc[i].col;
    }

    SNAKE sn[4];

    for (int i = 0; i < 4; ++i)
    {
       sn[i].row = 90;
       sn[i].col = col[i];
       sn[i].oldrow = sn[i].row;
       sn[i].oldcol = sn[i].col;
    }

    LOG l;
    l.row =  50;
    l.col =  120;
    
    int oldr= l.row;
    int oldc = l.col;

    int check1=0;
    int check2 = 0;
    int check3 = 0;
    int house1occ = 0;
    int house2occ = 0;
    int house3occ = 0;
    

    while(1)
    {
        if(KEY_DOWN_NOW(BUTTON_START))
        {
            return WINSCREEN;
        }
        if(KEY_DOWN_NOW(BUTTON_SELECT))
        {
            return LOSESCREEN;
        }
        if (KEY_DOWN_NOW(BUTTON_UP))
        {
            frog.row = frog.row-2;
        }
        if (KEY_DOWN_NOW(BUTTON_DOWN))
        {
            drawRect(frogp->oldrow, frogp->oldcol, 20, 17, BLACK);
            drawImage3(frogp->row, frogp->col, 20, 15, down);

           frog.row = frog.row+2;
        }
        if (KEY_DOWN_NOW(BUTTON_RIGHT))
        {
            drawRect(frogp->oldrow, frogp->oldcol, 20, 17, BLACK);
            drawImage3(frogp->row, frogp->col, 20, 15, right);

            frog.col = frog.col+2;
        }
        if (KEY_DOWN_NOW(BUTTON_LEFT))
        {
            drawRect(frogp->oldrow, frogp->oldcol, 20, 17, BLACK);
            drawImage3(frogp->row, frogp->col, 20, 15, left);   
            frog.col = frog.col-2;
        }
        for (i = 0; i < 4; ++i)
        {
            croc[i].col = croc[i].col - 4;
            
            if (croc[i].col <= 0)
            {
                croc[i].col = 240;
            } 
        }
        for (i = 0; i < 4; ++i)
        {
            sn[i].col = sn[i].col - 4;
            
            if (sn[i].col <= 0)
            {
                sn[i].col = 240;
            } 
        }

        for (i = 0; i < 4; ++i)
        {
            l.col--;
            
            if (l.col <= 0)
            {
                l.col = 240;
            } 
        }

        if (time < 0) {
            return LOSESCREEN;
        }
        if (frogp->lives <= 0) {
            return LOSESCREEN;
        }
        delay(1);
        waitForVblank();

        
        
        // Drawing time and lives
        sprintf(buffer, "TIME: %d", time);
        sprintf(buffer1, "LIVES: %d", frogp->lives);
        drawRect(1, 0, 240, 10, BLACK);
        drawString(1, 60, buffer, YELLOW);
        drawString(1, 5, buffer1, YELLOW);  
        

        if(h1co == 0 && h2co == 0 && h3co)
        {
            return WINSCREEN;
        }

        //Draw crocodile
        drawRect(118, 0, 240, 15, BLACK);
        
        for (i = 0; i < 4; ++i)
        {
            if (croc[i].col<240 && croc[i].col >= 0)
            {
               drawImage3(croc[i].row, croc[i].col, 30, 10, croco);
            }  
        }

        //Checks to see if crocodile and frog is colliding
        for(i =0; i < 4; ++i)
        {
            if(isCollision(frogp->row, frogp->col, croc[i].row, croc[i].col, 10, 10))
            {
                frogp->lives--;
                frogp->row = 145;
                frogp->col = 110;
            }
        }

        //Draw snake
        drawRect(68, 0, 240,15 , BLACK);
        for (i = 0; i < 4; ++i)
        {
            if (sn[i].col<240 && sn[i].col >= 0)
            {
               drawImage3(sn[i].row, sn[i].col, 30, 10, snake);
            }  
        }

        //Checks to see if snake and frog is colliding
        for(i =0; i < 4; ++i)
        {
            if(isCollision(frogp->row, frogp->col, sn[i].row, sn[i].col, 10, 10))
            {
                frogp->lives--;
                frogp->row = 145;
                frogp->col = 110;
            }
        }
        
        //Draw log
         drawImage3(l.row, l.col, 60, 15, lo);
        
        oldr= l.row;
        oldc = l.col;
        //Checks to see if log and frog is colliding
        
       
       if(isCollision(frogp->row, frogp->col, l.row, l.col, 15, 15))
       {
            frogp->col = l.col;
            if (frogp->col<=0)
            {
                frogp->row = 145;
                frogp->col = 110;
                
            }

       }


        //Draw frog
        drawRect(frogp->oldrow, frogp->oldcol, 20, 17, BLACK);
        drawImage3(frogp->row, frogp->col, 20, 15, up);

        //Draw Home    
        drawImage3(h[0].row, h[0].col, 30, 20, home);
        drawImage3(h[1].row, h[1].col, 30, 20, home);
        drawImage3(h[2].row, h[2].col, 30, 20, home);

        if(isCollision(frogp->row, frogp->col, h[0].row, h[0].col, 5, 5))
        {
            check1++;
            frogp->row = 145;
            frogp->col = 110;
            house1occ=1;

        }
        if(isCollision(frogp->row, frogp->col, h[1].row, h[1].col, 5, 5))
        {
            check2++;
            frogp->row = 145;
            frogp->col = 110;
            house2occ=1;
            
        }
        if(isCollision(frogp->row, frogp->col, h[2].row, h[2].col, 5, 5))
        {
            check3++;
            frogp->row = 145;
            frogp->col = 110;
            house3occ=1;
        }
    
        if(check1==1 && check2 == 1 && check3==1)
        {
            return WINSCREEN;
        }

        if(house1occ==1)
        {
            drawRect(15, 60, 40, 25, BLACK);
            
        }
        if(house2occ==1)
        {
            drawRect(15, 120, 40, 25, BLACK);
            
        }
        if(house3occ==1)
        {
            drawRect(15, 180, 40, 25, BLACK);
            
        }
        frogp->oldrow = frogp->row;
        frogp->oldcol = frogp->col;

        timer++;
        if (timer == 60) {
            time--;
            timer = 0;
        }
    }
}