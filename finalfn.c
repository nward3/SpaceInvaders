// Authors: Nicholas Ward & Dina Vu

#include "gfx3.h"
#include "finalfn.h"

// initializes enemies and barriers
void fillArray(int invaders[8][5], int barrierlife[6][4])
{
	int i, j; // loop counters

	// initialize enemies
        for(i=0; i<8; i++) {
                for(j=0; j<5; j++) {
                        invaders[i][j]=1;
                }
        }

	// initialize barriers
        for(i=0; i<6; i++) {
                for(j=0; j<4; j++) {
                        barrierlife[i][j]=1;
                }
        }
	return;
}

// moves the enemies
void moveEnemy(int *xfish, int *yfish, int *dirfish)
{
	static int count=1; // total movement count

	count++;
	// increases enemy speed every few lines
	if ((count%200)==0) {
		(*dirfish)+=((*dirfish)/(abs(*dirfish))); // adds pos. or neg. 1 depending on direction
	}

	// keep enemies in the grid boundaries by switching direction of motion
        if (*xfish>316) { 
                (*dirfish) = (*dirfish*(-1));		
	}
	else if (*xfish<90) {
		(*dirfish) = (*dirfish * (-1));	
	}

	// updates enemies' positions
        *xfish = (*xfish) + (*dirfish);
	if (count%90==0) {
		*yfish+=10;
	}
        return;
}

// moves the ship
void moveShip(int *xship, char action)
{
	// move left
	if(action=='a') {
		*xship-=10;
		if(*xship<90) {
			 *xship=90;
		}
	}
	// move right
	else if(action=='d') {
		*xship+=10;
		if(*xship>650) {
			*xship=650;
		}
	}
	return;
}

// draws the barriers
void drawBarrier(int barrierlife[6][4])
{
        int i, j;	// loop counters
	int scale; 	// scaling factor
	int x, y; 	// initial x,y coordinates of barrier
        x=100;
        y=580;
        scale=2;

        for (i = 0; i <6; i++){
                if (barrierlife[i][0]==1){      // draw 1/4 of the barrier (starting from the left)
                        gfx_color(0,250,0);
                        gfx_fill_rectangle(x,y,7*scale,20*scale);
                        gfx_color(0,0,0);
                        gfx_fill_rectangle(x,y,1*scale,3*scale);
                        gfx_fill_rectangle(x+1*scale,y,1*scale,2*scale);
                        gfx_fill_rectangle(x+2*scale,y,1*scale,1*scale);
                }
                if (barrierlife[i][1]==1){	// draw 2/4 of the barrier
                        gfx_color(0,250,0);
                        gfx_fill_rectangle(x+7*scale,y,7*scale,20*scale);
                        gfx_color(0,0,0);
                        gfx_fill_rectangle(x+7*scale,y+12*scale,1*scale,8*scale);
                        gfx_fill_rectangle(x+8*scale,y+11*scale,1*scale,9*scale);
                        gfx_fill_rectangle(x+9*scale,y+10*scale,1*scale,10*scale);
                        gfx_fill_rectangle(x+10*scale,y+9*scale,1*scale,11*scale);
                        gfx_fill_rectangle(x+11*scale,y+8*scale,1*scale,12*scale);
                        gfx_fill_rectangle(x+12*scale,y+7*scale,2*scale,13*scale);
                }
                if (barrierlife[i][2]==1){	// draw 3/4 of the barrier
                        gfx_color(0,250,0);
                        gfx_fill_rectangle(x+14*scale,y,7*scale,20*scale);
                        gfx_color(0,0,0);
                        gfx_fill_rectangle(x+14*scale,y+7*scale,2*scale,13*scale);
                        gfx_fill_rectangle(x+16*scale,y+8*scale,1*scale,12*scale);
                        gfx_fill_rectangle(x+17*scale,y+9*scale,1*scale,11*scale);
                        gfx_fill_rectangle(x+18*scale,y+10*scale,1*scale,10*scale);
                        gfx_fill_rectangle(x+19*scale,y+11*scale,1*scale,9*scale);
                        gfx_fill_rectangle(x+20*scale,y+12*scale,1*scale,8*scale);
                }
                if (barrierlife[i][3]==1){	// draw 4/4 of the barrier
                        gfx_color(0,250,0);
                        gfx_fill_rectangle(x+21*scale,y,7*scale,20*scale);
                        gfx_color(0,0,0);
                        gfx_fill_rectangle(x+25*scale,y,1*scale,1*scale);
                        gfx_fill_rectangle(x+26*scale,y,1*scale,2*scale);
                        gfx_fill_rectangle(x+27*scale,y,1*scale,3*scale);
                }
                x+=50*scale;
        }
	return;
}

// draw the enemies
void drawEnemy(int x, int y, int invaders[8][5])
{
        int scale = 3;	// scaling factor
        int i,j;	// loop counters
        int x0=x;       // original positions of X and Y
        int y0=y;
	static int iterations=1;	// iteration count
	iterations++;

        for (i=0; i<8; i++){
                for( j =0; j<5; j++){

			// draws enemy if it is alive 
                        if (invaders[i][j]== 1){
                	        gfx_color(250,250,250);
                       		gfx_fill_rectangle(x,y,8*scale,8*scale);
                       		gfx_color(0,0,0);
             	   	        gfx_fill_rectangle(x,y,3*scale,1*scale);
                       		gfx_fill_rectangle(x+5*scale,y,3*scale,1*scale);
                       		gfx_fill_rectangle(x,y+1*scale,2*scale,1*scale);
                       		gfx_fill_rectangle(x+6*scale,y+1*scale,2*scale,1*scale);
                       		gfx_fill_rectangle(x,y+2*scale,1*scale,1*scale);
                       		gfx_fill_rectangle(x+7*scale,y+2*scale,1*scale,1*scale);
                       		gfx_fill_rectangle(x+2*scale,y+3*scale,1*scale,1*scale);
                        	gfx_fill_rectangle(x+5*scale,y+3*scale,1*scale,1*scale);

				// alternate enemy images to simulate motion
				if (iterations%2==0){
					gfx_fill_rectangle(x,y+5*scale,2*scale,1*scale);
					gfx_fill_rectangle(x+3*scale,y+5*scale,2*scale,1*scale);
					gfx_fill_rectangle(x+6*scale,y+5*scale,2*scale,1*scale);
					gfx_fill_rectangle(x,y+6*scale,1*scale,1*scale);
			      		gfx_fill_rectangle(x+2*scale,y+6*scale,1*scale,1*scale);
					gfx_fill_rectangle(x+5*scale,y+6*scale,1*scale,1*scale);
					gfx_fill_rectangle(x+7*scale,y+6*scale,1*scale,1*scale);
					gfx_fill_rectangle(x+1*scale,y+7*scale,1*scale,1*scale);
					gfx_fill_rectangle(x+3*scale,y+7*scale,2*scale,1*scale);
					gfx_fill_rectangle(x+6*scale,y+7*scale,1*scale,1*scale);
				}
				else{
					gfx_fill_rectangle(x,y+5*scale,1*scale,1*scale);
					gfx_fill_rectangle(x+2*scale,y+5*scale,1*scale,1*scale);
					gfx_fill_rectangle(x+5*scale,y+5*scale,1*scale,1*scale);
					gfx_fill_rectangle(x+7*scale,y+5*scale,1*scale,1*scale);	
					gfx_fill_rectangle(x+1*scale,y+6*scale,6*scale,1*scale);
					gfx_fill_rectangle(x,y+7*scale,1*scale,1*scale);
					gfx_fill_rectangle(x+2*scale,y+7*scale,4*scale,1*scale);
					gfx_fill_rectangle(x+7*scale,y+7*scale,1*scale,1*scale);
				}
                        }
			y+=18*scale;
                }
                y=y0;
                x+=18*scale;	// moves to next row of enemies
        }
	return;
}

// draws the player's ship
void drawShip(xship, yship)
{
        int l, w;	// length and width of rectangles
        int scale;	// scaling factor
        scale=3;

        gfx_color(0,240,0);
        gfx_fill_rectangle(xship+1*scale,yship-1*scale,15*scale,5*scale);
        gfx_fill_rectangle(xship+2*scale,yship-2*scale,13*scale,1*scale);
        gfx_fill_rectangle(xship+7*scale,yship-5*scale,3*scale,3*scale);
        gfx_fill_rectangle(xship+8*scale,yship-6*scale,1*scale,1*scale);

	return;
}

// ship's shot at enemies
int shipshot(int *xshipshot, int *yshipshot,int dir,int *dist)
{
	int shipshotcontinue = 1; // true/false of whether to continue shot's motion

	// updates shot position
	*dist = *dist + 3*dir;
	*yshipshot += *dist;
	
	gfx_color(255,255,255);
	gfx_line(*xshipshot,*yshipshot,*xshipshot,*yshipshot-5);

	if (*yshipshot < 0){
		shipshotcontinue =0;	// stops from continuing shot motion
		*dist = 0;		// reset shot distance
	}
	return shipshotcontinue;
}

// randomly choose an enemy to shoot at the player
int chooseEnemy(int invaders[8][5], int *xfish, int *yfish, int *xenemyshot, int *yenemyshot, int *enemyshotcontinue)
{
	int j;			// loop counter
	int shooter;		// selected enemy to shoot
	shooter = rand()%8;	// randomly select an enemy

	for (j = 4; j>=0; j--){
		if (invaders[shooter][j] == 1){	// enemy alive and can shoot
			*xenemyshot = *xfish + 12 + 54*shooter;
			*yenemyshot = *yfish + 24 + 54*j;
			*enemyshotcontinue = 1;
			return 1;
		}
	}
	return 0;		// no available enemy to shoot from specifed column
}

// enemy's shot at player
int enemyshot(int *xenemyshot, int *yenemyshot, int dir, int *dist1)
{
	int enemyshotcontinue = 1; // true/false of whether to continue shot's motion

	// updates shot position	
	*dist1 = *dist1 + 3*dir;
	*yenemyshot += *dist1;
	
	gfx_color(255,255,255);
	gfx_line(*xenemyshot,*yenemyshot,*xenemyshot,*yenemyshot-5);
	gfx_line(*xenemyshot-1,*yenemyshot-4,*xenemyshot+1,*yenemyshot-5);

	if (*yenemyshot > 800){
		enemyshotcontinue = 0;	// stops from continuing shot motion
		*dist1 = 0;		// reset enemy shot distance
	}
	return enemyshotcontinue;
}

// check if the player's ship has hit anything
int shipcheckHit(int *xshipshot, int *yshipshot, int barrierlife[6][4], int invaders[8][5], int *shipshotcontinue, int *dist, int *xfish, int *yfish, int *scoretot)
{
	int i, j;	// loop counters
	int xdiff=0;	// x,y boundaries of object's hit box
	int ydiff=0;

	// first check if barrier was hit	
	for (i=0;i<6;i++){
		for(j=0;j<4;j++){
			// check if barrier is alive and can be destroyed
			if (barrierlife[i][j]==1){
				xdiff = abs(*xshipshot-((i+1)*100+7+14*(j)));
				// destroys barrier section if shot is within hit box
				if (xdiff <= 7 && abs(*yshipshot-600)<=20){
					barrierlife[i][j]=0;
					*shipshotcontinue=0;
					*dist=0;
					return 1;
				}
			}
		}			
	}

	// now check if enemy was hit
	for (i = 0; i< 8; i++){
		for(j=4; j>=0; j--){
			// check if enemy is alive and can be destroyed
			if (invaders[i][j] == 1){
				xdiff= abs(*xshipshot-(*xfish+12+54*i));
				ydiff= abs(*yshipshot-(*yfish+12+54*j));
				// kills enemy if shot is within hit box
				if(xdiff<=12 && ydiff <=25){
					invaders[i][j]=0;
					*shipshotcontinue=0;
					*dist=0;
					*scoretot +=10;
					return 1;
				}
			}
		}
	}	
	return 0;
}

// check if enemy's shot has hit anything
int enemycheckHit(int *xenemyshot, int *yenemyshot, int barrierlife[6][4], int *lives, int *enemyshotcontinue, int *dist1, int *xship, int *yship)
{
	int i, j;	// loop counters
	int xdiff=0;	// x,y boundaries of object's hit box
	int ydiff=0;

	// first check if barrier was hit
        for (i=0;i<6;i++){	 
               for(j=0;j<4;j++){
			// check if barrier is alive and can be destroyed
                        if (barrierlife[i][j]==1){
                                xdiff = abs(*xenemyshot-((i+1)*100+7+14*(j)));
				ydiff = abs(*yenemyshot - 600);
				// destroys barrier section if shot is within hit box
                                if (xdiff <= 7 && ydiff <=20){
                                        barrierlife[i][j]=0;
                                        *enemyshotcontinue = 0;
                                        *dist1 = 0;
                                        return 1;
                                }
                        }
                }
        }
	
	// now check if ship was hit
	xdiff = abs(*xenemyshot-(*xship+22 ));
	ydiff = abs(*yenemyshot-(*yship+7));

	// decrease player's life count if shot hits player
	if(xdiff<=22 && ydiff<=20){
		*lives = *lives -1;
		*dist1=0;
		*enemyshotcontinue=0;
		*xship=50;
		return 1;
	}
	return 0;
}

// draws the scoreboard
void scoreboard(int scoretot, int lives)
{
        gfx_text(50, 50, "SCORE");
        gfx_text(145, 50, num2str(scoretot));
        gfx_text(650, 50, "LIVES");
        gfx_text(750, 50, num2str(lives));

	return;
}      

// enables numbers to be printed
char *num2str(int k)
{
        static char a[4];	// array for number
        sprintf(a, "%d", k);
        return (char *) a;
}

// check if the enemy has made it passed the barrier
int checkBarrier(int invaders[8][5], int yfish)
{
	int i=0;	// loop counter
	int j=4;	// loop counter
	int sum=0;	// number of enemies remaining in the specified row
	int ylimit;	// max value the enemy can get to before the player loses

	for (j=4;  j>=0; j--){
		sum=0;
		for (i=0; i<8; i++){
			sum+=invaders[i][j];
		}

		// all enemies in specified row are dead
		if (sum==0){
			ylimit=650-(54*(j));
		}

		// at least one enemy in specified row are dead
		else if (sum!=0){
			ylimit=650-(54*(j+1));
			return ylimit;
		}	
	}
	return ylimit;
}

// instruction displayed at the beginning of the game
void instructions(int xfish,int yfish)
{
        if(xfish==90&&yfish==100) {
	        gfx_text(225,200, "Welcome to Space Invaders");
	      	gfx_text(100,250, "Shoot down the enemy before they reach you");
	        gfx_text(300,300, "a: move left");
	        gfx_text(300,350, "d: move right");
	        gfx_text(300,400, "s: shoot");
		gfx_text(300,450, "q: quit");
	        gfx_text(250,500, "Press any key to start");
	        gfx_wait();
	}
	return;
}
