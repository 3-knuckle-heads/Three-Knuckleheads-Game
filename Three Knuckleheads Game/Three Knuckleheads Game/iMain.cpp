#include "iGraphics.h"
#include<iostream>
using namespace std;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
double x = 0,y=150,r=50,b=500, inc1=0.5,inc2=0,c=40;
double xx = 250,xy = 650,inc3=0;
int flag = 0;
int N, P,B,S,mv_left = 0, mv_right = 0;
int left1 = 0;

void iDraw()
{
	iClear();
	iShowImage(0, 150, 1200,650 , B);
	iShowImage(0, 0, 1200, 150,S);
	iShowImage(x, y, 100, 50, N);
	iShowImage(xx, xy, 100, 50, P);
	iFilledRectangle(200, b, 100, 50);
	//iFilledRectangle(200,c , 100, 50);
	if(flag==1) // single jump 
		y += inc1;
	if (x+r >= 200 && x+r <= 200 + 100 && y+r>=b && y+r<= b+50)
	{
		inc1=-0.5;
		inc2 = 0.5;
	}
	b += inc2;
	if (xx + r >= 200 && xx + r <= 200 + 100 && xy - r >= b && xy - r <= b + 50)
	{
		inc3 = 10;
		cout << "NANI" << "\n";
	}
	xy += inc3;
	if (x + r >= 200 && x + r <= 200 + 100 && y - r >= c && y - r <= c + 50)
	{
		inc1 = 0;
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
		flag = 1;
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
		x += 2;
		
	}
	if (key == GLUT_KEY_LEFT)
	{
		x -= 2;
	}
	
	if (key == GLUT_KEY_HOME)
	{
		
	}
	
}


int main()
{
	///srand((unsigned)time(NULL));
	iInitialize(1200, 800, "Basic Collision");
	///updated see the documentations
	P = iLoadImage("./images/Pabak.png");
	N = iLoadImage("./images/Nayem.png");
	B = iLoadImage("./images/bg.png");
	S = iLoadImage("./images/Score.png");

	iStart();
	return 0;
}