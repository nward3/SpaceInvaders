// Authors: Nicholas Ward & Dina Vu
// final.c
#include<stdio.h>
#include "finalfn.h"

int main()
{
	int xsize; 	  // x dimension of graphics window
	int ysize; 	  // y dimension of graphics window
	int scoretot=0;	  // Initialize score
	int ylimit=380;	  // Calculates how far down the fish can go before game over
	char action;      // What key is pressed
	int invaders[8][5]; // enemy count
	int barrierlife[6][4]; // barrier count and life amount
	int xfish, yfish; // x,y coordinate of first fish
	int xship, yship; // x,y coordinate of ship
	int dir; 	  // +1 corresponds to enemy shot direction and -1 corresponds to player shot direction
	int dirfish;      // speed of enemies
	int i, j; 	  // loop counters
	int xshipshot=0;  // x coordinate of player's shot
	int yshipshot=0;  // y coordinate of player's shot
	int xenemyshot=0; // x coordinate of enemy's shot
	int yenemyshot=0; // y coordinate of enemy's shot
	int shipshotcontinue, enemyshotcontinue; // determines to continue the shot motion
	int dist=0; 	 // Distance of ship shot
	int dist1=0 ;	 // Distance of enemy Shot
	int enemyshotcount=0; // number of enemy shots
	int hit=0; 	 // If anything is hit
	int validshot=0; // true/false of whether a shot hit
	int lives=3;	 // three initial lives
	time_t t; 	 // time 


	// initialize variables
	xship=90;
	yship=675;
	xfish=90;
	yfish=100;
	dirfish=3;
	shipshotcontinue=0;
	enemyshotcontinue=0;
	srand(time(&t));
	fillArray(invaders,barrierlife);

	// initialize graphics window
	xsize=800;
	ysize=700;
	gfx_open(xsize, ysize, "Space Invaders");

	// while loop for game
	while(1)
	{	
		instructions(xfish,yfish);		// game directions
		gfx_repeat_off();			// disable ability to hold down key for multiple inputs
		gfx_clear();	

                // check for victory
                if (scoretot>=400) {
                	gfx_color(0,255,0);
                	gfx_text(300,350, "YOU WIN!");
                	gfx_repeat_on();
                	gfx_wait();
                	break;
		}
            	drawBarrier(barrierlife);
		drawShip(xship,yship);
		drawEnemy(xfish,yfish,invaders);
		moveEnemy(&xfish,&yfish,&dirfish);
		ylimit=checkBarrier(invaders, yfish);	// check if the enemies have made it to the bottom of the barriers
		if (yfish>ylimit){			// enemy position is passed the barriers
			gfx_color(255,0,0);
			gfx_text(300,350,"GAME OVER");
			gfx_repeat_on();		// restores ability to hold down key for multiple inputs
			gfx_wait();
			break;
		}

		// check for an event
		if (gfx_event_waiting()) { 
			action=gfx_wait(); 
			moveShip(&xship,action);

			// check if the specified action was to shoot
			if (action=='s'&&shipshotcontinue==0){
				dir=-1;
				shipshotcontinue=1;
				xshipshot=xship+24;
				yshipshot=yship-10;
			}
		
			// check if the specified action was to quit
			else if (action=='q') {
				gfx_color(255,0,0);
				gfx_text(300,350,"GAME OVER");
				gfx_repeat_on();
				gfx_wait();
				break;
			}	
		}

		// checks whether player shot has hit something or to continue motion
                if (shipshotcontinue==1){
                	dir=-1;
                       	shipshotcontinue=shipshot(&xshipshot,&yshipshot,dir,&dist);
			hit=shipcheckHit(&xshipshot,&yshipshot,barrierlife, invaders,&shipshotcontinue, &dist,&xfish,&yfish,&scoretot);
                	drawBarrier(barrierlife);	// Updates Barrier Life
		}

		enemyshotcount++; // update enemy shot count
		// ramdomly choose an enemy to shoot 
		if (enemyshotcount%8==0 && enemyshotcontinue==0) {
			validshot=chooseEnemy(invaders, &xfish, &yfish, &xenemyshot, &yenemyshot,&enemyshotcontinue);
			if (validshot==0) {
				 enemyshotcount=7;		
			}
		}
		// checks whether enemy shot has hit something or to continue motion
		if (enemyshotcontinue==1) {
			dir=1;
			enemyshotcontinue=enemyshot(&xenemyshot, &yenemyshot,dir,&dist1);
			hit=enemycheckHit(&xenemyshot, &yenemyshot,barrierlife, &lives, &enemyshotcontinue, &dist1, &xship,&yship);
			drawBarrier(barrierlife);
		}

		// update scoreboard
		gfx_color(255,255,255);
		scoreboard(scoretot, lives);

		gfx_flush();
		usleep(125000);

		// check for game over
		if (lives == 0){
			gfx_color(255,0,0);
			gfx_text(300,350, "GAME OVER");
			gfx_repeat_on();
			gfx_wait();
			break;
		}
	}
	return 0;
}
