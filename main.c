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
int time_diff;

typedef enum State{ TITLE, GAME_LOOP, GAME_OVER } State;
extern State state;

State state = TITLE; 

void titleScreen()
{
    wipeScreen( RGB( 0, 0, 0 ) );
    // Set our game data
    shipRow         = 55;
    shipCol         = 0;
    enemyCol        = 225;
    lives           = 3;
    enemy_num       = 0;
    projectile_num  = 0;
    time_diff       = 0;

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

    EntityClass enemy;
    initialize_entity( &enemy, 0, 0, 0, 0 );
    enemies[max_enemies+1] = enemy;

    while (lives != 0) 
    {
        // Draw background
        drawImage3( 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, background );

        // Draw ship
        draw_entity( &player_ship, ship ); 

        // Generate enemy
        if( time_diff <= 0 && enemy_num < 10 ) 
        {
            time_diff = 75;
            int rand_row = ( rand() % (150+1-10) ) + 10;
            generate_enemy( rand_row, enemyCol );
        }

        // Draw Enemy
        update_enemies();

        // Draw each projectile
        update_projectiles();

        // Check if player is dead. 
        if( is_player_dead( &player_ship ) == 1 )
        {
            lives--; 
        }

        check_collisions();
        remove_old_projectiles();
        remove_old_enemies();

        // Draw lives
        // Use drawImage3
        
        waitForVblank();

        // If player hits 'select' return to titleScreen and start game over.
        if( KEY_DOWN_NOW( BUTTON_SELECT ) )
        {
            state = TITLE;
            break;
        }

        // Player Actions 
        if( KEY_DOWN_NOW( BUTTON_DOWN ) ) 
        {
            if( get_row( &player_ship ) < 141 )
                move_entity( &player_ship, 2, 0 );
        }

        if( KEY_DOWN_NOW( BUTTON_UP ) ) 
        {
            if( get_row( &player_ship ) > 20 )
                move_entity( &player_ship, -2, 0 );
        }
    
        if( KEY_DOWN_NOW( BUTTON_A ) )
        {
            while( KEY_DOWN_NOW( BUTTON_A ) ){;}
            fire_weapon( &player_ship );
        }

        time_diff--;
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
