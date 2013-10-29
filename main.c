/**
Name: Jonathan Foster
2110 Homework 8
**/

#define REG_DISPCTL *(unsigned short *)0x4000000
#define RGB(r, g, b) ((r) | ((g)<<5) | ((b)<<10))
#define MODE3 3
#define BG2_ENABLE (1<<10)
typedef unsigned short u16;
extern u16 *videoBuffer;

void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void recursiveFun(int r, int c, int height, int width, u16 color);

int main(void) {
	// Set up the Display control register to mode3, and BG2 enabled
    REG_DISPCTL = MODE3 | BG2_ENABLE;

    // Infinitely draws the "fractal". Draws two sets of hollow 
    // rectangle shapes over top of each other repeatedly. 
    int i;
    while(1) {
    	for (i=0; i <= 256; i++) {
   			recursiveFun(i, i, 170, 80, RGB(i/4, 0, 31+i));
		}
		for (i=0; i <= 256; i++) {
   			recursiveFun(i, i, 170, 80, RGB(0, i/4, 31+i));
		}
    }
    return 0;
}
