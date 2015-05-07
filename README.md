# Space Invaders
![](https://github.com/nward3/SpaceInvaders/blob/master/images/GameScreenShot.jpg)
By: Nick Ward and Dina Vu.

CSE20211 - Fundamentals of Computing I: Final Project
Last Updated: December 13, 2014


====== THE PROJECT: Space Invaders ======

This program is a recreation of the original Space Invaders game. The goal
of the project was to create a version of the classic 70s arcade game. The
game is comprised of one level similar to the original game.

After the user presses any key, the game will begin and the user sees what 
looks like the Space Invaders arcade game from the 70's. The user controls the
ship at the bottom of the screen and can fire shots to try and kill the enemy.
Like the original game, the user is not allowed to fire multiple shots at a
time. They must wait until the shot hits the enemy or runs off the screen.
There are barriers that can protect the player from enemy fire but degrade
when shot by either the user or the enemy. The enemies move back and forth
across the screen and eventually move faster and down the screen towards the
player. Additionally, the enemies are able to shoot at the user and will fire
a shot downwards every so often that has the ability to kill the ship or
damage the barrier. The user has three lives and dies when shot by the enemy.
Once the user runs out of lives, the game displays a "Game Over" screen and the
user can press any key to exit the program. Additionally, the game can end if
the enemies move too far down the screen, regardless of how many lives the user
has left. If the user manages to shoot down all the enemies in time, "You Win"
is displayed to signify the user's victory.


====== Controls ======

The user exit the opening screen and start the game by pressing any key. Once the
game has started, the controls are as follows:
  Move left:   a
  Move right:  d
  Shoot:       s
  Quit:        q
After the user reaches the "Game Over" or "You Win" screen, the user can then
press any key to quit the program.


====== HOW THE CODE WORKS ======

The program that runs Space Invaders is called final and it features parts
of the original game such as lives, scoring and the player-controlled ship
that shoots down the enemies.

The program is broken down into three main files that will be compiled by a
makefile. The file final.c contains the main code which will call functions from
finalfn.c. The header file is named finalfn.h which contains all the prototypes
as well as the libraries to include in order to properly run the program.
Additionally, the files gfx3.c and accompanying header file, gfx3.h, were used
for the game's graphics. In implementing the gfx3.c and gfx3.h files, some
modifications to these files were done to help tailor the graphics library to
the needs of our game. To modify the gfx library, we added two functions that
returned void and had no inputs. They were called "gfx_repeat_on()" and
"gfx_repeat_off()". The function gfx_repeat_off() used the X11 library's
function to turn off the ability to hold down a key to get multiple inputs.
This function ensured prevented the user from holding down a key for shooting
or moving and being stuck from queued inputs. For example, without implementing
this function, the user might be stuck moving right even after they wanted to
switch movement directions to avoid an incoming enemy attack. The other function
added, gfx_repeat_on(), was used to restore the auto repeat functionality to the
keyboard once the user was done playing the game. Besides the two additional
functions, some modification was done to the gfx_text() function. To modify this
function, we used the X11 library to change the default text font and size to a
font and font size that would look better when implemented in the game. This
change was used for all the text throughout the game, though the color of the
font was changed throughout the program to correspond with particular aspects
of the game.

Besides breaking down the program into multiple different files and
implementing the gfx library, several algorithms were implementing to complete the
game. While most of these these functions are called from within a while loop
in main, after the graphics window has been initialized, the first function that is
called is called before the graphics window is opened. This function fills and
initialize the arrays for the enemies and the barriers. The arrays are initialized as
ones in order to indicate that each enemy is alive. They are then later changed to 0
if that enemy or barrier section is no longer alive. The program then enters a while
loop which continues until the game is over. The first function called is
instructions, which displays the objective and controls for the user. This
function is only called at the start of the game when the enemies are in their
initial positions. Also at the start, the function gfx_repeat_off is called to
disable the user's ability to hold down a key for multiple inputs. The program
checks for victory at before drawing a new iteration so that the screen will
only have the victory screen on it at the end. After this check, the function
drawBarrier, which takes in the value of the barrier array is called. The barrier
array indicates which parts of the barrier are alive and runs through a loop
to check if the part of the array that corresponds to a specific section of the
barrier is alive. If it is alive, then it is drawn, but tf it is not alive (the value
in the array is 0), then that section of the barrier is not drawn. The drawEnemy
function works similiarly. The enemy is not drawn if the array indicates that it is
not alive. Next, the movement of the enemy is called  and the enemies are all drawn
10 positions to the left or right. The gfx_event_waiting is contained within the while
loop to continuously check for input. If the user pressed one of the prescribed keys,
the program will perform that action, but if not, it will do nothing. The movement of
the ship runs similiarly to the enemy movement however the movement only occurs when 
'a' or 'd' is pressed. In both movement functions, there is also an 'if' statement
that prevents movement past the playing field. The user's ship is cannot go past the
limit, while enemies' direction of motion are switched if they try to go beyond it.
If the user fires a shot, the variable called shipshotcontinue becomes 1 and will
enter a different series of statements. Pressing 's' to initiate a shot will only
work for the user if there is not another shot still in the field. In other words,
shipshotcontiue must be 0 at that time. Firing the shot works by increasing a variable
titled 'dist' in the program for each iteration of the loop. What this does is changes
the origin of where the line that represents the bullet is being drawn at each
iteration. Additionally, if the user has fired a shot, the program will check if the
barrier was hit before checking if the enemy is hit. The enemy occupies multiple
positions on the screen so the shot needs to be compared to multiple positions on the
screen. Since the arrays of each enemy are equally drawn apart, a for loop is used to
run through and determine whether each enemy is alive or dead. The position of the
enemy will not be checked if the array indicates that the enemy is dead. The enemy
shot works similiarly in terms of movement. Once the shots hit something or travelout
of the screen, the values of the distances are reset to zero. The shotcontinue
variables are also reset to zero so that the user is allowed to shoot again and enemy
shots can occur. At the end of each iteration of the while loop, the scoreboard is
updated (+10 points for each enemy killed) and the game checks if the user has any
lives remaining to continue to the next iteration. If the user is out of lives, they
will see the game over screen and can press any key to quit the program.


====== Program Verification ======

The program was evaluated for correctness by continually playing the game and
purposefully losing and winning to make sure everything would behave normally
and as expected. In general, the functions that drew and moved the player or enemy
and updated the status of alive or dead were able to be checked just by playing the
game and making adjustments when those functions did not work. However, the fine-tuning
of the game, specifically the determining of the difficulty, depended on the input of
multiple "beta testers" that were asked to play the game. The "beta testers" played
the game with the enemies increasing their horizontal speed more quickly such as
every 80 movements, or more slowly such as as every 300 movements. The "beta testers"
also played the game with the enemies vertical approaching the player player more
quickly from ranges of every 80 movements to 250 movements. Based on the  "beta testers"
success or failure at the specified difficulty factors, we were able to design a
standard difficulty that the average player could win or lose. This method of
determining a difficulty made the game have slightly different parameters than the
original 1970s Space Invaders game, but we believe that this adjustment made sense for
having only one level for a user to play.
