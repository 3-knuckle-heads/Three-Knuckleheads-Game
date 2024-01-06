#include "iGraphics.h"
#include<iostream>
using namespace std;

int jannatuz_sprite, pruz_sprite, hypo_sprite, background_sprite, score_sprite, pipe_sprite;
int x_hypo=140, y_hypo=720, jump_count = 0;
bool hasJumped = false;

typedef struct pipe pipe;
struct pipe{ // Defines the platform (aka pipe) as a struct
	int posX, posY;
	int sizeX = 120, sizeY = 33;

	pipe(){ ; };

	pipe(int x, int y){
		posX = x;
		posY = y;
	};

	void render(){
		iShowImage(posX, posY, sizeX, sizeY, pipe_sprite);
	}

	int isColliding(int playerX, int playerY){ // checks if player is colliding with a particular pipe or not
		if ((playerX >= posX && playerX <= posX + sizeX) && (playerY >= posY && playerY <= posY + sizeY)){
			return 1;
		}

		return 0;
	}
};

int pipe_count = 25;
pipe all_pipes[25]; // Array to maintain all the pipes

void generateMap(){
	// Vertical level 1
	all_pipes[0] = pipe(0, 300);
	all_pipes[1] = pipe(120, 300);
	all_pipes[2] = pipe(240, 300);
	all_pipes[3] = pipe(360, 300);
	all_pipes[4] = pipe(680, 300);
	all_pipes[5] = pipe(800, 300);
	all_pipes[6] = pipe(920, 300);
	all_pipes[7] = pipe(1040, 300);
	all_pipes[8] = pipe(1160, 300);   // 0 to 8 index



	// Vertical level 2
	all_pipes[9] = pipe(240, 450);
	all_pipes[10] = pipe(360, 450);
	all_pipes[11] = pipe(480, 450);
	all_pipes[12] = pipe(600, 450);
	all_pipes[13] = pipe(720, 450);
	all_pipes[14] = pipe(1040, 450);
	all_pipes[15] = pipe(1160, 450);

	//vertical level 3
	all_pipes[16] = pipe(0, 600);
	all_pipes[17] = pipe(120, 600);
	all_pipes[18] = pipe(240, 600);
	all_pipes[19] = pipe(360, 600);
	all_pipes[20] = pipe(680, 600);
	all_pipes[21] = pipe(800, 600);
	all_pipes[22] = pipe(920, 600);
	all_pipes[23] = pipe(1040, 600);
	all_pipes[24] = pipe(1160, 600);

}

void images()
{
	///updated see the documentations
	pruz_sprite = iLoadImage("./images/Pabak.png");
	jannatuz_sprite = iLoadImage("./images/Nayem.png");
	background_sprite = iLoadImage("./images/bg.png");
	score_sprite = iLoadImage("./images/Score.png");
	hypo_sprite = iLoadImage("./images/ashfaq.png");
	pipe_sprite = iLoadImage("./images/pipe.png");
}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://


void iDraw()
{
	iClear();
	iShowImage(0, 150, 1280, 650, background_sprite);
	iShowImage(0, 0, 1280, 170, score_sprite);
	iShowImage(x_hypo, y_hypo, 100, 100, hypo_sprite);
	//iShowImage(250, 650, 100, 50, pruz_sprite);

	int flag = 0; // flag for colliding
	for (int i = 0; i < pipe_count; i++){
		all_pipes[i].render();

		if (all_pipes[i].isColliding(x_hypo + 100 / 2, y_hypo)) // either 0 or 1 is returned
		{
			flag = 1; // colliding with any one pipe
		}
	}

	if (flag == 0){ // colliding with no pipes at all
		y_hypo -= 4;
	}

	if (hasJumped){
		if (jump_count < 20){
			y_hypo += 15;
			jump_count++;
		}
		else{
			hasJumped = false;
			jump_count = 0;
		}
	}

	// Screen looping logic 
	if (x_hypo > 1280)
	{
		x_hypo = 0;
	}
	else if (x_hypo < 0)
	{
		x_hypo = 1280;
	}
}


/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	cout << mx << " " << my << "\n";
}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{


	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == 'j'){
		hasJumped = true;
	}
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{


	if (key == GLUT_KEY_RIGHT)
	{
		x_hypo += 12;
	}
	if (key == GLUT_KEY_LEFT)
	{
		x_hypo -= 12;   // 8 to 12 range is good
	}

	if (key == GLUT_KEY_HOME)
	{

	}

}


int main()
{
	///srand((unsigned)time(NULL));
	iInitialize(1280, 780, "Three Knuckleheads");
	
	images(); // used an image function to declare the images
	generateMap(); // used a generateMap function to generate the pipes on the foreground

	iStart();
	return 0;
}