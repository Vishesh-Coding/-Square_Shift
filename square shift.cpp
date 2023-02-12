#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>

#define ScWidth 1000
#define ScHeight 700
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75

using namespace std;

int main(){
	srand((unsigned) time(0));
		
	int gd = DETECT, gm, err, tmp;
	initgraph( & gd, & gm, "C:\\tc\\bgi");
  
	//Initial Position
	// iX-Initial X pos, iY-Initial Y Pos, gap-initial gap
	int iX = 300, iY = 250, gap = 50;
	
	// Player Variables
	int Player[4][3] = {{iX, iY, 0},{iX, iY+gap, 1},{iX, iY+gap*2, 0},{iX, iY+gap*3, 1}};
	// player size and player step
	int pSize = 20, pStep = 100;
	
	// Enemy Variables
	// ex-enemy x, ey-enemy y, eSize-enemy Size
	// eTimer: counts time for enemy color chance
	// eTime: time to retain specific enemy color
	int eX, eY, eType=0, eSize = 20, eTimer=0, eTime=10+rand()%10;
	
	// Other Variables
	char option, txtScore[5];
	int score = 12;	
	 
	//Generate Enemy
	do{
		eX = (1+rand()%5)*100; // random enemy X position
	}while( eX == Player[0][0] ); // not to generate on top of player
	eY = 250+(rand()%4)*50; // random enemy Y position
	
	setcolor(YELLOW);
	setfillstyle(1,YELLOW);
	bar(eX,eY,eX+eSize,eY+eSize); // draw enemy initially
	
	while(1){
		setcolor(WHITE);
		//draw board
		rectangle(0,0,ScWidth-350,ScHeight);
		rectangle(ScWidth-350,0,ScWidth,ScHeight);
		// print score
		// itoa function converts number to character array
		settextstyle(4,0,8);
		if( score<10 )
			outtextxy(ScWidth-210, 250, itoa(score,txtScore,10));
		else if( score>=10 )
			outtextxy(ScWidth-260, 250, itoa(score,txtScore,10));
		
		settextstyle(4,0,1);
		outtextxy(ScWidth-275, 500, "Use Arrow Keys ");
		outtextxy(ScWidth-275, 540, "to Move Player");
		
		// if enemy type is 0 then draw yellow enemy
		if( eType == 0 ){
			setcolor(YELLOW);
			setfillstyle(1,YELLOW);	
		}else{ // if enemy type is 0 then draw white enemy
			setcolor(WHITE);
			setfillstyle(1,WHITE);
		}
		bar(eX,eY,eX+eSize,eY+eSize); // draw enemy
		
		
		if(kbhit()){ // if any key is pressed
			option = getch(); // catch character in options variable
			if(option == KEY_RIGHT){ // if right arrow key is pressed
				if( Player[0][0]>100){ // restrict player on left border
					Player[0][0] -= pStep; // update player X position
					Player[1][0] -= pStep; // update player X position
					Player[2][0] -= pStep; // update player X position
					Player[3][0] -= pStep; // update player X position
				}
			}else if(option == KEY_LEFT){ // if left arrow key is pressed
				if( Player[0][0]<500 ){ // restrict player on right border
					Player[0][0] += pStep; // update player X position
					Player[1][0] += pStep; // update player X position
					Player[2][0] += pStep; // update player X position
					Player[3][0] += pStep; // update player X position
				}
			}
		}
		
		// If Enemy Hit Player
		for(int i=0; i<4; i++){ // check all 4 player parts
			if( Player[i][0] == eX && Player[i][1] == eY ){ // if hit
				if( Player[i][2] == eType ){ // if player part color matches enemy
					//Generate Enemy
					do{
						eX = (1+rand()%5)*100;// random enemy X position
					}while( eX == Player[0][0] ); // not to generate on top of player
					eY = 250+(rand()%4)*50; // random enemy Y position	
					
					score++; // increase score
				}
				else{
					// Print Game Over Text
					settextstyle(4,0,6);
					outtextxy(100,100,"Game Over");
					getch();
					score=0; // reset score
					
					//Generate Enemy
					do{
						eX = (1+rand()%5)*100; // random enemy X position
					}while( eX == Player[0][0] ); // not to generate on top of player
					eY = 250+(rand()%4)*50;  // random enemy Y position	
					
				}
				
			}	
		}
		
		  
		// Print Player 
		setcolor(YELLOW);
		setfillstyle(1,YELLOW);
		bar(Player[0][0], Player[0][1], Player[0][0]+pSize, Player[0][1]+pSize);
		
		setcolor(WHITE);
		setfillstyle(1,WHITE);
		bar(Player[1][0], Player[1][1], Player[1][0]+pSize, Player[1][1]+pSize);
		
		setcolor(YELLOW);
		setfillstyle(1,YELLOW);
		bar(Player[2][0], Player[2][1], Player[2][0]+pSize, Player[2][1]+pSize);
		
		setcolor(WHITE);
		setfillstyle(1,WHITE);
		bar(Player[3][0], Player[3][1], Player[3][0]+pSize, Player[3][1]+pSize);
		
		eTimer++; //update enemy timer
		if( eTimer == eTime){ // if enemy timer meet time to update color
			eType = !eType; // change enemy color (either enemy or fruit)
			eTimer = 0; // reset timer
			eTime=20+rand()%10; // set random time for this enemy/fruit
		}
		delay(30);
		cleardevice();
	}
	
	
	getch();
	closegraph();
}
