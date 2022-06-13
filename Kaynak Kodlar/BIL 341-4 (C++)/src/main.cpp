// ==================
//                                                                         
//   main.cpp
//   Serdar GÜL                                                      
//   20421689                                                                 
//                                                                            
//                                                                           
// ==================

/* include header */
#include "space.h"


/* _________________ MAIN _________________ */  

/* 
  first parameter : program
  second parameter : difficulty level [1,3]
  //third parameter : frequency level [1,3]
*/
 
int main(int argc, char *argv[]) {

  /*if(argc != 3) {
    printf("PARAMETER NUMBER\n");
    printf("Usage: Program Name - Difficulty Level [1,3] - Frequency Level [1,3]");
    exit(-1);
  }*/
  if(argc != 2) {
    printf("PARAMETER NUMBER\n");
    printf("Usage: Program Name - Difficulty Level [1,3]");
    exit(-1);
  }
  
  writeChar(3,5, 'K');
  
  level = atoi(argv[1]);
  
  initialEnemyNumber = level * 8; /* difficulty level * 8 */

  //enemyFrequency = 18.75 *(atof(argv[2])); /* frequency */
  initialFreq = enemyFrequency = 18.75 / level;
  
  initializeBoard(initialEnemyNumber);
  
  return 0;
  
} /* main */


/* _________________ FUNCTIONS _________________ */ 

/* prints the board */
void printBoard()
{
  int i, j;
  clearScreen();

  for(i = 0; i < ROW; i++)
  {
    for(j = 0; j < COLUMN; j++)
      writeChar(i + 5, j, board[i][j]);
  }
  printStatus();
} /* printBoard */

/* prints the game status */
void printStatus()
{
  //go to 0, 0
  _asm{
    mov	ah, 02h
    mov bh, 0
    mov	dh, 0
    mov dl, 0
    int	10h
  }
  printf("Player A: %d Time Elapsed: %.2f\n", enemyKilled * level, seconds/18);
} /* printStatus */

void clearScreen()
{
  //clear screen - set color: white over green
  _asm{
    mov	ax, 0600h
    mov	bh, 74h
    mov	cx, 0
    mov	dx, 184Fh
    int	10h
  }
}

/* puts cursor a specific coordinate(col,row) */
void writeChar(char row, char col, char c)
{
  //go to specified position
  _asm{
    mov	ah, 02h
    mov bh, 0
    mov	dh, row
    mov dl, col
    int	10h
  }
  
  //put character
  _asm{
    mov	ah, 0Eh
    mov bh, 0
    mov	al, c
    int	10h
  }
} 

/* timer interrupt */
void interrupt Timer() {
    _asm sti	
	 enemyFrequency--;
	 seconds++;
	_asm{	
		mov al, TIMER	
		out TIMER, al	
	}
}

void interrupt KeyBoard()
{
  _asm {
    sti                     
    in    al, KEY_BUFFER      
    xor   ah, ah              
    mov   pressedKey, ax         
    in    al, KEY_CONTROL     
    or    al, 82h             
    out   KEY_CONTROL, al     
    and   al, 7Fh
    out   KEY_CONTROL, al     
    mov   al, 20h
    out   INT_CONTROL, al     
  }

  switch(pressedKey)  {
  
    case MAKE_UP:     move(UP); /* move player up */ 
      break;
    case MAKE_DOWN:   move(DOWN); /* move player down */ 
      break;
    case MAKE_RIGHT:  move(RIGHT); /* move player right */ 
      break;
    case MAKE_LEFT:   move(LEFT); /* move player left */ 
      break;
    case MAKE_M:      fire();      /* fire from player */ 
      break;
    case ESC:         endGame = 1;
      break;
    default:
      break;
  }
}

/* fire from player */
void fire()
{
  if(board[playerRow][playerColumn-1] == 'E')
  {
    enemyKilled ++;
    board[playerRow][playerColumn-1] = ' ';
  }
  
  else if(board[playerRow][playerColumn-2] == 'E')
  {
    enemyKilled ++;
    board[playerRow][playerColumn-2] = ' ';
  }
  
  else if(board[playerRow][playerColumn-3] == 'E')
  {
    enemyKilled ++;
    board[playerRow][playerColumn-3] = ' ';
  }
  
  else if(board[playerRow][playerColumn-1] == '*')
  {
    board[playerRow][playerColumn-1] = ' ';
  }
  
  else if(board[playerRow][playerColumn-2] == '*')
  {
    board[playerRow][playerColumn-2] = ' ';
  }
  
  else if(board[playerRow][playerColumn-3] == '*')
  {
    board[playerRow][playerColumn-3] = ' ';
  }
  
  else
  { 
    if(playerColumn > 2)
    {
      board[playerRow][playerColumn-3] = '-';
    }
  }
}

/* move player */
void move(int direction) {
  
    switch(direction) {
      case UP:
        if(playerRow-1 >= 0) {
          if(board[playerRow-1][playerColumn] == 'E' || board[playerRow-1][playerColumn] == '*') {
              playerKilled = 1;
              endGame = 1;
          }
          if(board[playerRow-1][playerColumn] == ' ') {
              board[playerRow-1][playerColumn] = 'A';
              board[playerRow][playerColumn] = ' ';
              playerRow --;
          }             
        }
      break;
    
      case DOWN:
        if(playerRow+1 <= 19) {
          if(board[playerRow+1][playerColumn] == 'E' || board[playerRow+1][playerColumn] == '*') {
              playerKilled = 1;
              endGame = 1;
          }
          if(board[playerRow+1][playerColumn] == ' ') {
              board[playerRow+1][playerColumn] = 'A';
              board[playerRow][playerColumn] = ' ';
              playerRow ++;
          }            
        }
      
      break;
    
      case RIGHT:
         if(playerColumn+1 <= 59) {
          if(board[playerRow][playerColumn+1] == 'E' || board[playerRow][playerColumn+1] == '*') {
              playerKilled = 1;
              endGame = 1;
          }
        
          if(board[playerRow][playerColumn+1] == ' ') {
              board[playerRow][playerColumn+1] = 'A';
              board[playerRow][playerColumn] = ' ';
              playerColumn ++;
          }             
        }
      break;
    
      case LEFT:
        if(playerColumn-1 >= 0) {
          if(board[playerRow][playerColumn-1] == 'E' || board[playerRow][playerColumn-1] == '*') {
              playerKilled = 1;
              endGame = 1;
          }
          if(board[playerRow][playerColumn-1] == ' ') {
              board[playerRow][playerColumn-1] = 'A';
              board[playerRow][playerColumn] = ' ';
              playerColumn --;
          }            
        }
      break;
    
      default:
      break;
    }    
    
    printBoard();
} /* move */

/* moves enemies*/
void moveEnemies() {
  
  int i, j, control = 0, r;
  char temp[ROW][COLUMN];

  srand ( time(NULL) );
  
  /* load temp */
  for(i = 0; i< ROW; i++)
    for(j = 0; j < COLUMN; j++)
      temp[i][j] = board[i][j];
  
  /* move right */
  for(i = 0; i < ROW; i++)
    for(j = COLUMN-1; j >= 0; j--)
    {
        if(temp[i][j] == 'E')
        {
          if(j+1 <= 59)
          {
            if(board[i][j+1] != 'E') 
            { 
             if(board[i][j+1] == 'A')
             {
                playerKilled = 1;
                board[i][j+1] = 'A'; 
             }
              else
              {   
                board[i][j] = ' ';
                board[i][j+1] = 'E';
              }
            }
          }
          else
          {
          int control = 0;
            while(control == 0)
            {
            int nr = ((rand() % (19)) + 1);
            
             if(board[20 - nr][0] != 'E') 
             {    
              if(board[20-nr][0] == 'A')
              {
                playerKilled = 1; 
                board[20-nr][0] = 'A';
                control = 1; 
              }
              else
              {  
                board[i][j] = ' ';
                board[20-nr][0] = 'E';
                control = 1;
                }
              }
            }
          }
  
    }
  }
  
  /* reload temp */    
  for(i = 0; i< ROW; i++)
    for(j = 0; j < COLUMN; j++)
      temp[i][j] = board[i][j];
  
  for(i = 0; i < ROW; i++)
    for(j = 0; j < COLUMN; j++) {
      if(temp[i][j] == 'E') {
       
      while(control != 1) {
      
      r = ((rand() % (5)) + 1);

         switch(r) {
        
          /* up */
          case 1:
            if(i-1 >= 0)
             if(board[i-1][j] != 'E' || board[i-1][j] != '*') {
              if(board[i-1][j] == 'A')
              {
                playerKilled = 1; 
                board[i-1][j] = 'A';
              }
              else
              {
                board[i-1][j] = 'E';
                board[i][j] = ' ';
                control = 1;
              }
             }
          break;
        
          /* down */
          case 2:
            if(i+1 <= 19)
              if(board[i+1][j] != 'E'|| board[i+1][j] != '*') {
                if(board[i+1][j] == 'A')
                {
                  playerKilled = 1; 
                   board[i+1][j] = 'A';
                }
                else
                {
                  board[i+1][j] = 'E';
                  board[i][j] = ' ';
                  control = 1;
                }
              }
          break;
          
          /* fire */
          case 3:
            if(rand() % 4 != 0) break; // decrease fire frequency by 1/4 
            
            if(board[i][j+1] == 'A')
            {
              playerKilled = 1;
              endGame = 1;
              board[i][j+1] = 'A';
            }
            
            else if(board[i][j+2] == 'A')
            {
              playerKilled = 1;
              endGame = 1;
              board[i][j+2] = 'A';
            }
            else if(board[i][j+3] == 'A')
            {
              playerKilled = 1;
              endGame = 1;
              board[i][j+3] = 'A';
            }
            
            else if(temp[i][j+1] == '-')
            {
              board[i][j+1] = ' ';
              board[i][j] = ' ';
            }
            
            else if(temp[i][j+2] == '-')
            {
              board[i][j+2] = ' ';
              board[i][j] = ' ';
            }
            
            else if(temp[i][j+3] == '-')
            {
              board[i][j+3] = ' ';
              board[i][j] = ' ';
            }
  
            else
            { 
              if(j < 57)
              {
                board[i][j+3] = '*';
              }
              
            }
  
          break;
          
          case 4,5:
            control = 1;
          break;
          
          default:
            
          break;
          
          } /* switch */
        }
        
        control = 0;
          
      } /* if cell is an enemy */
          
    } /* for */
    
    printBoard();
 
} /* moveEnemies */

/* moveMisseles */
void moveMisseles()
{
  
  int i, j;
  char temp[ROW][COLUMN];
  
   for(i = 0; i< ROW; i++)
    for(j = 0; j < COLUMN; j++)
      temp[i][j] = board[i][j];
   
  for(i = 0; i< ROW; i++)
    for(j = 0; j < COLUMN; j++)
    {
      /* move player misseles */
      if(temp[i][j] == '-')
      {      
        
        if(temp[i][j-1] == 'E')
        {
          enemyKilled ++;
          board[i][j-1] = ' ';
        }
  
        else if(temp[i][j-2] == 'E')
        {
          enemyKilled ++;
          board[i][j-2] = ' ';
        }
  
        else if(temp[i][j-3] == 'E') 
        {       
            enemyKilled ++;
            board[i][j-3] = ' ';
        }
        
        else if(temp[i][j-1] == '*')
        {
          board[i][j-1] = ' ';
          board[i][j] = ' ';
        }
        
        else if(temp[i][j-2] == '*')
        {
          board[i][j-2] = ' ';
          board[i][j] = ' ';
        }
        
        else if(temp[i][j-3] == '*')
        {
          board[i][j-3] = ' ';
          board[i][j] = ' ';
        }
        
        else
        { 
          if ( j > 2)
          {
            board[i][j-3] = '-';
            board[i][j] = ' ';
          }
          else
          {
            board[i][j] = ' ';
          }
        }
      }
    }
    
  for(i = 0; i< ROW; i++)
    for(j = 0; j < COLUMN; j++)
      temp[i][j] = board[i][j];
    
  for(i = 0; i< ROW; i++)
    for(j = 0; j < COLUMN; j++)
    {
      /* move enemy misseles */
      if(temp[i][j] == '*')
      {
            
        if(temp[i][j+1] == 'A')
        {
          playerKilled = 1;
          endGame = 1;
          board[i][j+1] = 'A';
        }
  
        else if(temp[i][j+2] == 'A')
        {
          playerKilled = 1;
          endGame = 1;
          board[i][j+2] = 'A';
        }
  
        else if(temp[i][j+3] == 'A')
        {
          playerKilled = 1;
          endGame = 1;
          board[i][j+3] = 'A';
        }
        
        else if(temp[i][j+1] == '-')
        {
          board[i][j+1] = ' ';
          board[i][j] = ' ';
        }
            
        else if(temp[i][j+2] == '-')
        {
          board[i][j+2] = ' ';
          board[i][j] = ' ';
        }
            
        else if(temp[i][j+3] == '-')
        {
          board[i][j+3] = ' ';
          board[i][j] = ' ';
        }
  
        else
        { 
          if (j < 57)
          {
            board[i][j+3] = '*';
            board[i][j] = ' ';
          }
          else
          {
            board[i][j] = ' ';
          }
        }
      }
    }
    
    printBoard();
} /* moveMisseles */

/* function instead of _dos_getvect */
void interrupt ( *get_vect(int intNumber) )(){
	
  void interrupt (*interruptPointer)();
	_asm{
		
    XOR   AX, AX	/* clear ax */
		MOV   ES, AX	
		
    cli		/* clear interrupts */
		
		/* multiple intNumber with 4 and put into BX */
    MOV   AX, intNumber	
		MOV   DX, 4	
		MUL   DX		
		MOV   BX, AX	
    
    /* take interrupt from vector and put into an interrupt pointer */
		MOV   DX, ES:[BX]	
		MOV   WORD PTR interruptPointer, DX	
		ADD   BX, 2	
		MOV   DX, es:[BX]	
		MOV   WORD PTR interruptPointer + 2, DX
		
    sti	  /* set interrupts */
	}
	return interruptPointer;	
} /* get_vect */

/* function instead of _dos_setvect */
void set_vect( int intNumber, void interrupt (*interruptPointer)() ){
   
    _asm{	
		XOR   AX, AX	/* clear ax*/
		MOV   ES, AX	
		
    PUSHF	/* push flags */
		
    cli	  /* clear interrupts */
    
    /* multiple intNumber with 4 and put into BX */
		MOV   AX, intNumber 
		MOV   DX, 4	
		MUL   DX	
		MOV   BX, AX	 
    
    /* put interruptPointer into the interrupt vector */
		MOV   AX, WORD PTR interruptPointer	
		MOV   WORD PTR ES:[BX], AX	
		MOV   AX, WORD PTR interruptPointer + 2	
		ADD   BX, 2	
		MOV   WORD PTR ES:[BX], AX	
		
    POPF	/* pop flags */
		
    sti	/* set interrupts */
	}
} /* set_vect */


/* starts the game and handles the interrupts */
void game() {           
  
	void (_interrupt _far *Key_Old_Isr)();
	void (_interrupt _far *time_old_isr) ();
  
  time_old_isr = get_vect(TIMER_INTERRUPT); 
  set_vect(TIMER_INTERRUPT, Timer);
  
  Key_Old_Isr = get_vect(KEYBOARD_INTERRUPT);
  set_vect(KEYBOARD_INTERRUPT, KeyBoard);
     
	while (endGame == 0 && playerKilled == 0 && noEnemies == 0) {      
    
    if(enemyFrequency <= 0) {
      _asm cli
        moveEnemies();
        moveMisseles();
        countEnemies();
        printBoard();
      _asm sti
        
      enemyFrequency = initialFreq; 
    }
    
  }
  
    if(playerKilled) {
      printf("Game Over!! Player died\n");
      printf("Point: %d", enemyKilled * level);
    }

    else if(endGame){
      printf("Game Finished\n");
      printf("Point: %d", enemyKilled * level);
      
    } 
    
    else if(noEnemies){
      printf("Congragulations!! You've kill them all!!\n");
      printf("Point: %d", enemyKilled * level);
      
    } 
    
  set_vect(KEYBOARD_INTERRUPT, Key_Old_Isr);
  set_vect(TIMER_INTERRUPT, time_old_isr);

} /* game */

/* generateBoard randomly */
void randomBoard(int enemyNumber) {
   
  int randR, randC, controlP = 0;
	int i = 0;
	srand (time(NULL));
	
	/* place enemies randomly */
	while (i != enemyNumber)
  {
  	randR = ((rand() % (ROW)));
    randC = ((rand() % (COLUMN / 2)));
    
    if(board[randR][randC] == ' ')
    {
      board[randR][randC] = 'E';
      i++;
    }
  }
  
  /* place player randomly */
	while (controlP == 0)
  {
  	randR = ((rand() % (ROW)));
    randC = 59;
  
    if(board[randR][randC] == ' ')
    {
      board[randR][randC] = 'A';
      playerRow = randR;
      playerColumn = randC;
      controlP = 1;
    }
  }

} /* randomBoard */ 


void initializeBoard(int initialEnemyNumber)
{

  //set video mode:
  _asm{
    mov	ah, 0
    mov	al, 3
    int	10h
  }
  
  //hide cursor:
  _asm{
    mov	ah, 1
    mov	ch, 16
    mov	cl, 0
    int	10h
  }
  
  int i, j;
  for(i = 0; i < ROW; i++)
    for(j = 0; j < COLUMN; j++)
      board[i][j] = ' ';
  
  randomBoard(initialEnemyNumber);    
  printBoard();
  game();
  
} /* initialize */

void countEnemies()
{
  int i,j;
  int count = 0;
  
  for(i = 0; i < ROW; i++)
    for(j = 0; j < COLUMN; j++)
      if(board[i][j] == 'E')
        count++;
        
  if(count == 0)
    noEnemies = 1;
}
