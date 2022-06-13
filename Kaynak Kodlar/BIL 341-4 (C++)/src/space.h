// ==================
//                                                                         
//   spaceimpact.h                                                                 
//   Serdar GÜL                                                      
//   20421689                                                                 
//                                                                            
//                                                                           
// ==================


#define COLUMN  60
#define ROW     20
#define MAX_ENEMY 100
#define TIMER_INTERRUPT 0x1C
#define KEYBOARD_INTERRUPT 0x09
#define TIMER 20h

#define KEY_BUFFER      0x60
#define KEY_CONTROL     0x61
#define INT_CONTROL     0x20

#define MAKE_RIGHT      77  
#define MAKE_LEFT       75   
#define MAKE_UP         72  
#define MAKE_DOWN       80

#define MAKE_M          50

#define RIGHT           1
#define LEFT            2
#define DOWN            3
#define UP              4

#define ESC             0x01    

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <conio.h>

char board[ROW][COLUMN];

int playerRow, playerColumn;
   
int pressedKey, endGame = 0;
    
int enemyKilled = 0,
    playerKilled = 0,
    noEnemies = 0;    
    
int point = 0,
    level;
    
int enemyFrequency, initialFreq;
float seconds = 0;

int initialEnemyNumber;     

void clearScreen();
void writeChar(char, char, char);
void printStatus();
void initializeBoard(int);
void randomBoard(int);
void moveEnemies();
void move(int);
void game();
void printBoard();
void fire();
void moveMisseles();
void countEnemies();
