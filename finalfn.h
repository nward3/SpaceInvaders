// Authors: Nicholas Ward & Dina Vu

#include<stdio.h>
#include "gfx3.h"
#include<unistd.h>
#include<time.h>
#include<math.h>

void drawEnemy(int, int, int [][5]);
void drawBarrier(int [][4]);
void moveEnemy(int *, int *,int *);
void drawShip(int, int);
void moveShip(int *, char);
int shipshot(int *, int *, int , int *);
int enemyshot(int *, int *, int, int *);
int chooseEnemy(int [8][5], int *, int *, int *, int *, int *);
void fillArray(int [8][5],int [6][4]);
int shipcheckHit( int *, int *, int [6][4], int [8][5],int *, int *, int *, int *, int *);
int enemycheckHit(int *, int *, int [6][4], int *, int *, int *, int *, int *);
void scoreboard(int, int);
char *num2str(int);
int checkBarrier(int [8][5], int);
void instructions(int, int);
