/**
Name: Jonathan Foster
2110 Homework 9
**/

#include <stdlib.h>
#include <unistd.h>
#include "mylib.h"
#include "title.h"
#include "ship.h"
#include "enemy.h"
#include "background.h"
#include "entity.c" 

// Set up the Display control register to mode3, and BG2 enabled
int shipRow;
int shipCol;
int enemyCol;
int lives;

typedef enum State{ TITLE, GAME_LOOP, GAME_OVER } State;
extern State state;

State state = TITLE; 

void titleScreen()
{
    // Set our game data
    shipRow  = 55;
    shipCol  = 0;
    enemyCol = 0;
    lives    = 3;

    REG_DISPCNT = MODE3 | BG2_ENABLE;
    DMA[3].src = title;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (240*160) | DMA_ON;
    while(!KEY_DOWN_NOW(BUTTON_START));

    // This transitions to our game screen
    wipeScreen( RGB( 0, 0, 0 ) );
    state = GAME_LOOP;
}

void gameLoop()
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    EntityClass player_ship;
    initialize_entity( &player_ship, SHIP_WIDTH, SHIP_HEIGHT, shipRow, shipCol );

    while (lives != 0) 
    {
        // Draw background
        drawImage3( 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, background );

        // Draw ship
        draw_entity( &player_ship, ship ); 

        // Draw Enemy
        drawImage3( 80, enemyCol, ENEMY_WIDTH, ENEMY_HEIGHT, enemy);
        enemyCol--;

        // Draw lives
        //drawString3( 0, 0, "Lives: ", GREEN );

        //if( lives == 3 )
        //{
        //    for( int i = 0; i < lives; i++ ) drawRect( 5, 220 + ( i + 10 ), 5, 5, GREEN );
        //    for( int i = 0; i < lives; i++ ) drawRect( 5, 230 + ( i + 10 ), 5, 5, GREEN );
        //    for( int i = 0; i < lives; i++ ) drawRect( 5, 240 + ( i + 10 ), 5, 5, GREEN );
        //}

        waitForVblank();

        // If player hits 'select' return to titleScreen and start game over.
        if( KEY_DOWN_NOW( BUTTON_SELECT ) )
        {
            state = TITLE;
            break;
        }

        // Below are the checks for the player's ship's movement. 
        if (KEY_DOWN_NOW(BUTTON_DOWN)) 
        {
            if(shipRow < 141)
                move_entity( &player_ship, 4, 0 );
        }
        if (KEY_DOWN_NOW(BUTTON_UP)) 
        {
            if (shipRow > 20)
                move_entity( &player_ship, -4, 0 );
        }
    }
}

int main( void ) 
{
    while( 1 ) 
    { 
        if( state == TITLE )
            titleScreen();
        if( state == GAME_LOOP )
           gameLoop();
        if( state == GAME_OVER )
            break;
    }

    return 0;
}
