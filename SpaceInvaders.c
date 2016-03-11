//*****************************************************************************
// TITLE:					SpaceInvaders
// 
// NAME:		    	Jordan Roen, Jerit George, Sneha Patri
// LAB SECTION:		306
// LAB DAY:				Monday
//
// CLASS:					ECE 210
// DATE: 					FALL 2015
// 
// DESCRIPTION:		The is the game of Space Invaders. It's for two players. Each player
//								plays on their own screen trying to kill all of the aliens first by 
//								firing missiles and moving their ship. There are 3 rounds and the player
//								who kills their aliens in the shortest amount of time wins.
//*****************************************************************************


/* A Sprite can be drawn on screen */
typedef struct sprite {
	int width;
	int height;
	unsigned char *data;
	int xOffset;
	int yOffset;
	int dead;
} Sprite;


/* Initialization Functions */
void	LEDBARInit(void);
void 	DIPSWInit(void);
void	PBSwInit(void);	
void 	RGB_LEDInit(void);
void 	sysTickInit(void);
void potentiometersInit(void);
void	RIT128x96x4Init(int freq);
void    RIT128x96x4Clear(void); 
int readPotentiometer0(void);
/* Inputs, outputs, and wait timers */			
int 	read_PBSwitchNum(int SwitchNumber);
int		read_Switches(void);
void    LEDBAROutput(int value);
void 	turnOn(char color);
void 	turnOff(char color);
void  sysTickWait1mS(int waitTime);
void RIT128x96x4ImageDraw(const unsigned char *pucImage, unsigned long uIZ, unsigned long uIY, unsigned long uIWidth, unsigned long uIHeight);
void RIT128x96x4StringDraw(const char* letter, int xx, int yy, int intensity);
/* Xbee Functions */
void 	Xbee_ConfigureAddresses(int destination, int ownAddr);
void 	Xbee_Send(int message);
int   Xbee_SendArray(char *s, int messageLength);
int		Xbee_Receive(void);
int   Xbee_ReceiveArray(char* message, int messageLength);
void PWM_Init(void);
void setDutyCycle(char , int );
/* Our Functions */
void drawSprite(Sprite *s);



//sprites needed
unsigned char alienData[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x08, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x07, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};//15 high, 15 wide

unsigned char shipData[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0A, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0xFF, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0xFF, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x0D, 0xFF, 0xFF, 0x0D, 0x00, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x04, 0x05, 0x00, 0x00, 0x0D, 0xFF, 0xFF, 0x0D, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x05, 0x06, 0x00, 0x01, 0x0D, 0xFF, 0xFF, 0x0D, 0x01, 0x00, 0x06, 0x05, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x0A, 0x07, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x06, 0x00, 0x00, 0x08, 0x0C, 0x07, 0xFF, 0xFF, 0x0A, 0x09, 0xFF, 0xFF, 0x07, 0x0C, 0x07, 0x00, 0x00, 0x07, 0x01,
  0x01, 0x06, 0x00, 0x00, 0x04, 0x09, 0xFF, 0xFF, 0x08, 0x07, 0x07, 0x09, 0xFF, 0xFF, 0x08, 0x04, 0x00, 0x00, 0x06, 0x01,
  0x02, 0x0A, 0x00, 0x00, 0x05, 0x0B, 0xFF, 0xFF, 0x08, 0x08, 0x09, 0x08, 0xFF, 0xFF, 0x0B, 0x05, 0x00, 0x00, 0x0A, 0x02,
  0x02, 0x0D, 0x00, 0x04, 0x0A, 0xFF, 0xFF, 0xFF, 0x09, 0x0B, 0x0C, 0x09, 0xFF, 0xFF, 0xFF, 0x0A, 0x03, 0x00, 0x0D, 0x02,
  0x02, 0x0D, 0x00, 0x0C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0C, 0x00, 0x0D, 0x02,
  0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0D, 0x07, 0xFF, 0xFF, 0xFF, 0x0D, 0x07, 0x0D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x02,
  0x02, 0xFF, 0xFF, 0xFF, 0x07, 0x04, 0x08, 0x07, 0xFF, 0xFF, 0xFF, 0x0D, 0x07, 0x08, 0x04, 0x08, 0xFF, 0xFF, 0xFF, 0x02,
  0x02, 0xFF, 0xFF, 0x07, 0x02, 0x02, 0x07, 0x07, 0x06, 0x0B, 0x0B, 0x06, 0x07, 0x07, 0x02, 0x03, 0x08, 0xFF, 0xFF, 0x02,
  0x02, 0xFF, 0x0A, 0x01, 0x00, 0x01, 0x05, 0x05, 0x00, 0x09, 0x09, 0x00, 0x05, 0x05, 0x01, 0x00, 0x01, 0x0A, 0xFF, 0x02,
  0x02, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x02
};//20x20



unsigned char missileData[] = {
	0xFF,0xFF,
	0xFF,0xFF,
	0xFF,0xFF,
	0xFF,0xFF,
	0xFF,0xFF,
	0xFF,0xFF,
	
};//2x6

int scoreDisplay[] = { 0, 1, 3, 7 };

//create the sprites
Sprite alienSprite = { 15, 15, alienData, 0, 0, 1 };
Sprite shipSprite = { 20, 20, shipData, 0, 0, 0 };
Sprite missileSprite = { 2, 6, missileData, 0, 0, 1 };

#define FRAME_WIDTH 128
#define FRAME_HEIGHT 96
#define POTEN_MAX 900
#define TRUE 1
#define FALSE 0

//*****************************************************************************
//
// Main Program:
//
//*****************************************************************************
int
main(void)
{
	//vars in program
	int PB1,PB2;			//Pushbutton variables								
	int	destAddress;			//Destination and source addresses for the Xbee
	int ownAddress;
	int gameFinished;
	int shipPosition;
	int myWins;
	int myLosses;
	int i;
	int j;
	int k; //These are all just used in for loops 
	int p;
	unsigned int loopCounter = 0; //used for score keeping
	int goodMessage; 	//used for validating messages after receiving Xbee messages
	int firstTime = TRUE;
	char myScoresChar[3];
	char oppScoresChar[3];
	int allDead;	//boolean, if all aliens are dead
	int PBon;
	int delta = 2; //rate at which aliens move
	int alienX = 0; //alien x position offset
	int myScores[3]; //holding the value of this player's loop counter after each round
	int opponentScores[3]; //gets the value of the opponent's loop counter after each round
	Sprite alienBlock[4][3]; //holds the dreaded aliens
	Sprite missiles[5];	//holds the missiles

	//Initializing the LEDBAR, RGB LED, DIPSwitches and Pushbuttons, and a wait timer
	LEDBARInit();
	DIPSWInit();
	PBSwInit();
	RGB_LEDInit();
	sysTickInit();
	potentiometersInit();
	RIT128x96x4Init(1000000);
	
	/*****************************************************************************/
	
	RIT128x96x4StringDraw("Please Configure", 20, 30, 15);
	RIT128x96x4StringDraw("Xbee addresses", 25, 50, 15);
	
	/* Main Part of the Program starts here */
	turnOn('G'); //Status LED lets us know we are ready to go.		
	sysTickWait1mS(300);
	turnOff('G');
			
	//set the XBEE addresses 

	//First the	destination address should be set.
	PB1 = read_PBSwitchNum(1);
	while(PB1 != 0x0)
	{
		 PB1 = read_PBSwitchNum(1);
		 //Waits until PB1 has been pressed.
	}
	destAddress = read_Switches();

	//LED Sequence lets us know we have recieved the destination properly.
	turnOff('G');
	turnOn('R');
	sysTickWait1mS(150);
	turnOff('R');

	//Next, the source (for this Xbee) address should be set.
	PB2 = read_PBSwitchNum(2);
	while(PB2 != 0x0)
	{
		 PB2 = read_PBSwitchNum(2);
		 //Waits until PB2 has been pressed.
	}
	ownAddress = read_Switches();

	//LED Sequence lets us know we have recieved the source properly.
	turnOn('B');
	sysTickWait1mS(50);
	turnOff('B');

	//Time to set the Xbee up.
	Xbee_ConfigureAddresses(destAddress, ownAddress);

   	//LED Sequence lets us know we have configured the Xbee 
	turnOn('G');
	sysTickWait1mS(150);
	turnOff('G');
	sysTickWait1mS(150);
	turnOn('G');
	sysTickWait1mS(150);
	turnOff('G');
	sysTickWait1mS(150);
	
	
	/***********************************************************************************/

	/* Main Loop */
	while(1) {
		
		//draw welcome/info screen
		if(firstTime == TRUE) {
			firstTime = FALSE;
			RIT128x96x4Clear();
			RIT128x96x4StringDraw("SPACE INVADERS", 20, 15, 15);
			RIT128x96x4StringDraw("Help us save Earth!", 13, 30, 15);
			RIT128x96x4StringDraw("Move your ship ", 22, 40, 15);
			RIT128x96x4StringDraw("w/ potent1", 29, 50, 15);
			RIT128x96x4StringDraw("Fire with PB1", 20, 62, 15);
			RIT128x96x4StringDraw("Press PB2 to start", 14, 80, 15);
		}
		//start game when PB2 is pushed
		PB2 = read_PBSwitchNum(2);
	    while(PB2 != 0x0) {
			PB2 = read_PBSwitchNum(2);
		}
		
		//play 3 rounds
		for (i = 0; i < 3; i++){
			
			//initialize the missiles (start dead)
			for (k = 0;k < 5; k++){
				missiles[k] = missileSprite;
			}
			
				//initialize block of aliens
			for (j = 0; j < 4; j++){ 
				for (k = 0; k < 3; k++){
				 alienBlock[j][k].width = alienSprite.width;;
				 alienBlock[j][k].height = alienSprite.height;
				 alienBlock[j][k].data = alienSprite.data;
				 alienBlock[j][k].xOffset = alienX + j*(alienSprite.width + 5);
				 alienBlock[j][k].yOffset = k*(alienSprite.height + 5);
				 alienBlock[j][k].dead = FALSE; 
				}
			}
			
			
			gameFinished = FALSE;
			
			//play each round as a game
			while(gameFinished != TRUE){
				loopCounter++;
				
				//update ship pos
				shipPosition = (((float)readPotentiometer0())/ ((float)POTEN_MAX)) * (FRAME_WIDTH-30);
				shipSprite.xOffset = shipPosition;
				shipSprite.yOffset = FRAME_HEIGHT - 20;
				
				//if PB1 is pressed then fire a new missile
				PB1 = read_PBSwitchNum(1);
				if (PB1 != 0x0) {
					PBon = FALSE;
				}
				if (PB1 == 0x0 && PBon == FALSE){
					PBon = TRUE;
					//find a dead missile
					for(k = 0; k < 5; k++){
						if (missiles[k].dead == TRUE){
							missiles[k].dead = FALSE;
							missiles[k].xOffset = shipPosition + ((float)shipSprite.height / (float) 2);
							missiles[k].yOffset = FRAME_HEIGHT - shipSprite.height/2;
							break;
						}
					}
				}
				//move all the missiles toward the aliens
				for (p = 0; p < 5; p++){
					missiles[p].yOffset = missiles[p].yOffset - 2;
					if (missiles[p].yOffset < 0) missiles[p].dead = TRUE;
				}
				//move the alien block
				for (j = 0; j < 4; j++){ 
					for (k = 0; k < 3; k++){
						alienBlock[j][k].xOffset = alienX + j*(alienSprite.width + 5);
					}
				}
				alienX = alienX + delta;
				if (alienX > 50) {
					delta = delta*-1;
					alienX = 50;
				} else if (alienX < 0) {
					delta = delta*-1;
					alienX = 0;
				}
				
				//clear screen then draw everything
				RIT128x96x4Clear();
				for (j = 0; j < 4; j++){
					for ( k = 0; k < 3; k++){
						if (alienBlock[j][k].dead == FALSE) {
							drawSprite(&alienBlock[j][k]);
						}
					}
				}
				drawSprite(&shipSprite);
				for (j = 0; j < 5; j++){
					if (missiles[j].dead == FALSE) drawSprite(&missiles[j]);
				}
				sysTickWait1mS(20);//this is to improve screen clarity and give the function time to draw
					
				//check if missile has hit an alien
				for (p = 0; p < 4; p++){
					if (missiles[p].dead == TRUE) continue;
					for (j = 0; j < 4; j++){
						for ( k = 0; k < 3; k++){
							if (missiles[p].dead == TRUE) continue;
							if (alienBlock[j][k].dead == TRUE) continue;
							if (missiles[p].xOffset >= alienBlock[j][k].xOffset
								&& missiles[p].xOffset <= (alienBlock[j][k].xOffset + alienSprite.width) 
								&& missiles[p].yOffset <= alienBlock[j][k].yOffset 
								&& missiles[p].yOffset >= (alienBlock[j][k].yOffset - alienSprite.height)) {
									//if the tip of the missile is within the block of the alien then alien dies
									missiles[p].dead = TRUE;
									alienBlock[j][k].dead = TRUE;
							}	
						}
					}
				}
				
				//check if all the aliens have been killed
				allDead = TRUE;
				for (j = 0; j < 4; j++){
					for (k = 0; k < 3; k++){
						if (alienBlock[j][k].dead == FALSE){
							allDead = FALSE;
						}
					}
				}
				
				
				if (allDead == TRUE){
					//store the number of loops it took to finish each round
					gameFinished = TRUE;
					myScores[i] = loopCounter;
					loopCounter = 0;
				} 
			}
		}
		
		//initialize score
		myWins = 0;
		myLosses = 0;
		
		//send this player's scores and receive opponent's scores
		for (j = 0; j < 3; j++){
			myScores[j] = myScores[j]/3;
			Xbee_Send(myScores[j]);
		}
		for (j = 0; j < 3; j++){
			do {
				opponentScores[j] = Xbee_Receive();
			} while (opponentScores[j] == 0x5A5);
		}

		turnOff('G');
		turnOff('R');
		turnOn('B');
		sysTickWait1mS(1000);
		for (j = 0; j < 3; j++){
			turnOff('B');
			turnOff('R');
			turnOff('G');
			sysTickWait1mS(1000);
			if (myScores[j] < opponentScores[j]){
				myWins++;	
				turnOn('G');
				sysTickWait1mS(1000);
			} else{
				myLosses++;
				turnOn('R');
				sysTickWait1mS(1000);
			}
		}
		turnOff('G');
		turnOff('R');
		turnOff('B');
		
		//print out our scores and our opponent's scores
		RIT128x96x4Clear();
		for (i = 0; i < 3; i++) {
			sprintf(&myScoresChar[i],"%d",myScores[i]);
			sprintf(&oppScoresChar[i],"%d",opponentScores[i]);
			RIT128x96x4StringDraw(&myScoresChar[i], 30 +i*30, 40, 15);
			RIT128x96x4StringDraw(&oppScoresChar[i], 30+ i*30, 70, 15);
		}
		RIT128x96x4StringDraw("Your Scores", 20, 30, 15);
		RIT128x96x4StringDraw("Opponent Scores", 15, 60, 15);
		RIT128x96x4StringDraw("Lower is Better", 20, 10, 15);
		//wait briefly before going to the next screen
		sysTickWait1mS(10000);
			
		
		//display win/lose screen
		RIT128x96x4Clear();
		if(myWins > myLosses){
			RIT128x96x4StringDraw("YOU WON!", 32, 30, 15);
			RIT128x96x4StringDraw("Push PB2 to", 24, 55, 15);
			RIT128x96x4StringDraw("try again", 29, 68, 15);
		} else {
			RIT128x96x4StringDraw("YOU LOSE!", 35, 15, 15);
			RIT128x96x4StringDraw("Mwahaha!", 36, 37, 15);
			RIT128x96x4StringDraw("Tiny Earthlings!", 17, 49, 15);
			RIT128x96x4StringDraw("Push PB2 to", 27, 73, 15);
			RIT128x96x4StringDraw("try again", 32, 86, 15);
		}
	}	
}


/* draw a sprite on the screen */
void drawSprite(Sprite *s) {
	RIT128x96x4ImageDraw(s->data, (int)s->xOffset, (int)s->yOffset, s->width, s->height);
}



