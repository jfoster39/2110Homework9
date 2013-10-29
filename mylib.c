/**
Name: Jonathan Foster
2110 Homework 8
**/

typedef unsigned short u16;
u16 *videoBuffer = (u16 *)0x6000000;

void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void recursiveFun(int r, int c, int width, int height, u16 color);


/**
Follows formula for calculating where to set the pixel. 
**/
void setPixel(int r, int c, u16 color) {
    videoBuffer[(r*240 + c)] = color;
};

/**
Cycles through two for loops and set a pixel for each iteration
**/
void drawRect(int r, int c, int width, int height, u16 color) {
	int i;
	int j;
	int cReset = c;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			setPixel(r, c ,color);
			c++;
		}
	c = cReset;
	r++;
	}
}

/**
Here we draw 4 seperate rectangles for the outline of a hollow rectangle.
We first draw the top row, then the leftmost coloumn. We then draw the 
bottom rectangle, and then the rightmost. 
**/
void drawHollowRect(int r, int c, int width, int height, u16 color) {
    int i;
    int j;

    // Here we draw the vertical lines
    for (i = r; i<(r+height) && 160; i++) {
        setPixel(i,c,color);
        j = c + width-1;
        if (j<=240) {
            setPixel(i, j, color);
        }
    }

    // Here we draw the horizontal lines
    for (j = c; j<(c+width) && 240; j++) {
        setPixel(r, j, color);
        i = r + height-1;
        if (i<=160) {
            setPixel(i , j, color);
        }
    }
}

/**
Attempt at recursively drawing hollow rectangles to create a 
larger shape. 
**/
void recursiveFun(int r, int c, int width, int height, u16 color) {
    if (width >= 2) {
        drawHollowRect(r, c, height, width, color);
        recursiveFun(r+1, c, height - 2, width/2, color);
        recursiveFun(r, c+1, height - 2, width/2, color);
    }
}
