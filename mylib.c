#include "mylib.h"



unsigned short *videoBuffer = (unsigned short *)0x6000000;

// A function to set pixel (r, c) to the color passed in. 
void setPixel(int r, int c, u16 color)
{
    videoBuffer[OFFSET(r, c, 240)] = color;          
}

void drawChar(int r, int c, char ch, unsigned short color)
{
    int i,j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<6; j++)
        {
            if(fontdata_6x8[OFFSET(i, j, 6)+ch*48])
            {
                setPixel(r+i, c+j, color);
            }
        }
    }
}

void drawString(int r, int c, char *str, unsigned short color)
{
    while(*str)
    {
        drawChar(r, c, *str++, color);
        c += 6;
    }
}
//waitForVblank
void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}
// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int width, int height, u16 color) 
{
    for (int i = 0; i < height; ++i)
    {
        
            DMA[3].src = &color;
            DMA[3].dst = &videoBuffer[OFFSET(r+i, c, 240)];
            DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | width; 
        
    }
}

void drawHollowRect(int r, int c, int width, int height, u16 color)
{
    for (int i = 0; i <= height; i++)
       {
           setPixel(i+r, c, color);
           setPixel(i+r, c+width, color);
       } 
    for(int j = 0; j <= width; j++) 
    {
        setPixel(r, j+c, color);
        setPixel(r+height, j+c, color);
    }    
}
// A function to fill the entire screen with a given color
void fillinScreen(volatile unsigned short color)
{
    DMA[3].src = &color;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (160*240) | DMA_SOURCE_FIXED | DMA_ON;
}

void drawImage3(int r, int c, int width, int height, const u16* image)
{
    for (int i = 0; i < height; ++i)
    {
        DMA[3].src = &image[OFFSET(i, 0, width)];
        DMA[3].dst = &videoBuffer[OFFSET(r+i, c, 240)];
        DMA[3].cnt = DMA_ON | width;
    }
}

//Checks to see if two objects collide
int isCollision(int row1, int col1, int row2, int col2, int rowDiff, int colDiff)
{
    if ((row1 - row2 < rowDiff && row1 - row2 > -rowDiff) && (col1 - col2 < colDiff && col1 - col2 > -colDiff))
    {

        return 1;
    }
    return 0;
}

void delay(int n)
{
    int i;
    volatile int x;
    for(i=0; i<n*10000; i++)
    {
        x++;
    }
}


