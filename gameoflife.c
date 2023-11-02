//GAME OF LIFE IN C BY MRVOLLBART 
//GAME OF LIFE: RULES:
//1: live cell with 2-3 neighbours lives to next round
//2: live cell with <2 Neighbours dies
//3: live cell with over 3 neighbours dies
//4: dead cell with 3 neighbours becomes live
// in this case the borders are always DEAD!
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define MAP_W 93
#define MAP_H 35
#define FIRST_CHAR 33 // !//64 //@ symbol
int generation=1;
// TO READ A MAP TILE, USE Y, X, e.g. map[1][2]
int map[MAP_H][MAP_W] = {
  {0,0,0,0,0},
  {0,0,1,0,0},
  {0,0,0,1,0},
  {0,1,1,1,0},
  {0,0,0,0,0}
};
int nextMap[MAP_H][MAP_W];


int getLiveNeighbours(int xog, int yog){
  int lives;
  if (map[yog][xog]==1){
    lives=-1;
  } else {
    lives=0;
  }
  // main loop
  for (int y=yog-1; y<=yog+1; y++){
    for (int x=xog-1; x<=xog+1; x++){
      if (x!=0 && y!=0 && y<MAP_H && x<MAP_W){
        if (map[y][x]==1){
          lives++;
          //printf("NEW LIFE LOCATED AT x:%d y:%d!\n",x,y);
        }
      }

    }
  }

  return lives;
}

bool isAlive(int x, int y){
  if (map[y][x]==1){
    return true;
  } else { return false; }
}
void draw(){
  //DRAW 
  clear();
  printw("GENERATION %d - Keybinds: 'q' to quit, 'e' to edit\n", generation);
  for (int i=0; i<MAP_H; i++){
    if (MAP_H>10 && i<10){
      printw(" ");
    }
    printw("%d ",i);
    for (int j=0;j<MAP_W; j++){
      if (map[i][j]==1){
        printw("#");
      } else if (i==MAP_H-1 || i==0){
        printw("-");
      } else if (j==0 || j==MAP_W-1){
        printw("|");
      } else {
        printw(".");
      }
    }
    printw("\n");
  }
  if (MAP_H>10){
    printw(" ");
  }
  printw("  ");
  for (int i=0; i<MAP_W; i++){
    printw("%c", i+FIRST_CHAR);
  }
  printw("\n");
  refresh();
}

void editmode(){
  bool editing=true;
  while (editing){
    draw();
    timeout(1000000000);
    printw("Editing mode (BETA). Write 'q' to quit, 'c' to clear or type address (yx, e.g. 0A for first top cell) to switch cell\n> ");
    char input[100];
    scanw("%100s", input);
    if (strcmp(input,"quit")==0 || strcmp(input, "q")==0){
      timeout(0);
      editing=false;
      refresh();
    } else if (strcmp(input,"c")==0){
      for (int i=0; i<MAP_H; i++){
        for (int j=0; j<MAP_W; j++){
          map[i][j]=0;
          printw("CLEARED %d | %d\n", j,i);
        }
      }
    } else {
        int y=input[0]-'0';
        int x=input[1]-FIRST_CHAR;
      if (strlen(input)>=3) {
        y=y*10+input[1]-'0';
        x=input[2]-FIRST_CHAR;
      }
      if (y<MAP_H && x<MAP_W){
        if (map[y][x]==1){
          map[y][x]=0;
        } else {
          map[y][x]=1;
        }
      }
    }
  }
}


int main(){
  // INIT NCURSES
  initscr();
  //set non-blocking mode
  timeout(0);
  bool running=true;
  //printf("%d\n", getLiveNeighbours(1, 0));
  //UPDATE
  while (running){
    draw();
    //int nextMap[MAP_H][MAP_W];
    // get user input
    for (int i=0;i<=MAP_H; i++){
      for (int j=0;j<=MAP_W; j++){
        // RULE 4
        if (isAlive(j, i)==false){
          if (getLiveNeighbours(j, i)==3){
            nextMap[i][j]=1;
          } else {
            nextMap[i][j]=0;
          } 
        } else{
          // RULE 2
          if (getLiveNeighbours(j, i)<2){
            nextMap[i][j]=0;
          }// RULE 3
          else if (getLiveNeighbours(j, i)>3){
            nextMap[i][j]=0;
          }
          else if (getLiveNeighbours(j, i)==2 || getLiveNeighbours(j, i)==3){
            nextMap[i][j]=1;
          } else {
            nextMap[i][j]=0;
          }
        }
      }
    }
    usleep(100000);
    for (int i=0; i< MAP_H; i++){
      for (int j=0; j< MAP_W; j++){
        map[i][j] = nextMap[i][j];
      }
    }
    generation++;
    int input = getch();
    if (input!=ERR){
      if (input == 'q'){
        running=false;
      }
      if (input == 'e'){
        editmode();
      }
    }
    usleep(100000);
  }
  endwin();
}
