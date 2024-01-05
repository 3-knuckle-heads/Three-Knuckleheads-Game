#include "iGraphics.h"
#include<iostream>
using namespace std;

int jannatuz_sprite, pruz_sprite, hypo_sprite, background_sprite, score_sprite, pipe_sprite;

typedef struct pipe pipe;
struct pipe{ // Defines the platform (aka pipe) as a struct
	int posX, posY;
	
	pipe(){ ; };

	pipe(int x, int y){
		posX = x;
		posY = y;
	};

	void render(){
		 iShowImage(posX, posY, 120, 33, pipe_sprite);
	}
};

int pipe_count = 2;
pipe all_pipes[2]; // Array to maintain all the pipes

void generateMap(){
	// Vertical level 1
	all_pipes[0] = pipe(0, 300);
	all_pipes[1] = pipe(120, 300);

	// Vertical level 2
}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://


void iDraw()
{
	iClear();
	iShowImage(0, 150, 1280,650 , background_sprite);
	iShowImage(0, 0, 1280, 150,score_sprite);
	iShowImage(0, 150, 100, 100, hypo_sprite);
	iShowImage(250, 650, 100, 50, pruz_sprite);

	for (int i = 0; i < pipe_count; i++){
		// iShowImage(all_pipes[i].posX, all_pipes[i].posY, 100, 50, pipe_sprite);
		 all_pipes[i].render();
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
	if (key == 'm')
	{	

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
		
	}
	if (key == GLUT_KEY_LEFT)
	{

	}
	
	if (key == GLUT_KEY_HOME)
	{
		
	}
	
}


int main()
{
	///srand((unsigned)time(NULL));
	iInitialize(1280, 720, "Basic Collision");
	///updated see the documentations
	pruz_sprite = iLoadImage("./images/Pabak.png");
	jannatuz_sprite = iLoadImage("./images/Nayem.png");
	background_sprite = iLoadImage("./images/bg.png");
	score_sprite = iLoadImage("./images/Score.png");
	hypo_sprite = iLoadImage("./images/ashfaq.png");
	pipe_sprite = iLoadImage("./images/pipe.png");

	generateMap();

	iStart();
	return 0;
}