#include "iGraphics.h"
#include<iostream>
#include<vector>
using namespace std;

int background_sprite, score_sprite;
int jannatuz_sprite, pruz_sprite, hypo_sprite;
int pipe_sprite;
int cat_sprites[11];

int points = 0;

typedef struct player player;
struct player{ // Defines the player character for the game
	int posX = 50, posY = 190;
	int jump_count = 0;
	bool hasJumped = false, hasLanded = true;

	int bottomX, bottomY;
	int topX, topY;
	int rightX, rightY;
	int leftX, leftY;

	player(){ ; };

	void render(){
		iShowImage(posX - 100 / 2, posY, 100, 100, jannatuz_sprite);
	}

	void updateBounds(){
		bottomX = posX, bottomY = posY;
		topX = posX, topY = posY + 100;
		rightX = posX + 100 / 2, rightY = posY + 100 / 2;
		leftX = posX - 100 / 2, leftY = posY + 100 / 2;
	}


	int isColliding(int x, int y){ // checks if target is colliding with the player
		if ((x >= leftX + 40 && x <= rightX - 40) && (y >= bottomY && y <= topY)){
			return 1;
		}

		return 0;
	}
};

player current_player;
int playerCollisionFlag;
int rightFlag = 0, leftFlag = 0;

typedef struct cat cat;
struct cat{
	int posX = 50, posY = 640;

	int bottomX, bottomY;
	int topX, topY;
	int rightX, rightY;
	int leftX, leftY;

	int sizeX, sizeY;

	int animIndex = 0;
	int catCollisionFlag;

	bool isDead = false;
	bool leftToRight = true;

	cat(){
		if (rand() % 2){
			posX = 50;
			sizeX = 100;
			leftToRight = true;
		}
		else{
			posX = 1230;
			sizeX = -100;
			leftToRight = false;
		}
	};

	void render(){
		if (!isDead){
				iShowImage(posX - sizeX / 2, posY, sizeX, 100, cat_sprites[animIndex]);
		}
		else{
				iShowImage(posX - sizeX / 2, posY, sizeX, 100, cat_sprites[10]);
		}
	}

	void move(){
		if (leftToRight){
			posX += 2;
		}
		else{
			posX -= 2;
		}
	}

	void die(){
		isDead = true;
	}

	void collide(){
		cout << "muri kha!" << endl;
	}

	void updateBounds(){
		bottomX = posX, bottomY = posY;
		topX = posX, topY = posY + 100;
		rightX = posX + sizeX / 2, rightY = posY + 100 / 2;
		leftX = posX - sizeX / 2, leftY = posY + 100 / 2;
	}
};

int enemy_count_max = 8;
vector<cat> enemies; // initial 0

typedef struct pipe pipe;
struct pipe{ // Defines the platform (aka pipe) as a struct
	int posX, posY;
	int bump_count = 0;
	bool isBumped = false;
	int sizeX = 120, sizeY = 33;

	pipe(){ ; };

	pipe(int x, int y){
		posX = x;
		posY = y;
	};

	void render(){
			iShowImage(posX, posY, sizeX, sizeY, pipe_sprite);
	}

	int isColliding(int x, int y){ // checks if target is colliding with a particular pipe or not
		if ((x >= posX && x <= posX + sizeX) && (y >= posY && y <= posY + sizeY)){
			return 1;
		}

		return 0;
	}

	void bump(){
		isBumped = true;

		for (int i = 0; i < enemies.size(); i++){
			if (isColliding(enemies[i].bottomX, enemies[i].bottomY)){
				enemies[i].die();

				points += 100; // move to die()
			}
		}
	}
};

int pipe_count = 31;
pipe all_pipes[31]; // Array to maintain all the pipes

void images()
{
	///updated see the documentations
	pruz_sprite = iLoadImage("./images/Pabak.png");
	jannatuz_sprite = iLoadImage("./images/Nayem.png");
	background_sprite = iLoadImage("./images/bg.png");
	score_sprite = iLoadImage("./images/Score.png");
	hypo_sprite = iLoadImage("./images/ashfaq.png");
	pipe_sprite = iLoadImage("./images/pipe.png");

	cat_sprites[0] = iLoadImage("./images/cat/Walk (1).png");
	cat_sprites[1] = iLoadImage("./images/cat/Walk (2).png");
	cat_sprites[2] = iLoadImage("./images/cat/Walk (3).png");
	cat_sprites[3] = iLoadImage("./images/cat/Walk (4).png");
	cat_sprites[4] = iLoadImage("./images/cat/Walk (5).png");
	cat_sprites[5] = iLoadImage("./images/cat/Walk (6).png");
	cat_sprites[6] = iLoadImage("./images/cat/Walk (7).png");
	cat_sprites[7] = iLoadImage("./images/cat/Walk (8).png");
	cat_sprites[8] = iLoadImage("./images/cat/Walk (9).png");
	cat_sprites[9] = iLoadImage("./images/cat/Walk (10).png");
	cat_sprites[10] = iLoadImage("./images/cat/Dead (10).png");
}

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

	// Vertical level 3
	all_pipes[16] = pipe(0, 600);
	all_pipes[17] = pipe(120, 600);
	all_pipes[18] = pipe(240, 600);
	all_pipes[19] = pipe(360, 600);
	all_pipes[20] = pipe(680, 600);
	all_pipes[21] = pipe(800, 600);
	all_pipes[22] = pipe(920, 600);
	all_pipes[23] = pipe(1040, 600);
	all_pipes[24] = pipe(1160, 600);

	// Bottom (under score image) pipe, so that player does not fall through bottom
	all_pipes[25] = pipe(0, 0);
	all_pipes[25].sizeX = 1400;
	all_pipes[25].sizeY = 170;

	// Side (out of screen) pipes, so that player does not fall when looping the screen
	all_pipes[26] = pipe(-120, 300);
	all_pipes[27] = pipe(1280, 300);
	all_pipes[28] = pipe(1280, 450);
	all_pipes[29] = pipe(-120, 600);
	all_pipes[30] = pipe(1280, 600);
}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://


void iDraw()
{
	iClear();
	current_player.updateBounds();

	for (int i = 0; i < enemies.size(); i++)
		enemies[i].updateBounds();

	iShowImage(0, 150, 1280, 650, background_sprite);
	
	// render the player
	current_player.render();
	for (int i = 0; i < enemies.size(); i++){
		enemies[i].render();
		enemies[i].catCollisionFlag = 0;
	}

	//iShowImage(250, 650, 100, 50, pruz_sprite);

	playerCollisionFlag = 0; // flag for colliding
	
	for (int i = 0; i < pipe_count; i++){
		all_pipes[i].render();

		// bottom collision check
		if (all_pipes[i].isColliding(current_player.bottomX, current_player.bottomY)) // either 0 or 1 is returned
		{
			playerCollisionFlag = 1; // colliding with any one pipe
		}

		// top collision check
		if (all_pipes[i].isColliding(current_player.topX, current_player.topY)) // either 0 or 1 is returned
		{
			if (current_player.hasJumped){
				if (!all_pipes[i].isBumped){
					cout << "A pipe was bumped: " << i << endl;
					all_pipes[i].bump();
				}

				current_player.jump_count = 16;
			}
			else{
				//current_player.posY = all_pipes[i].posY + 40;
			}
		}
		for (int j = 0; j < enemies.size(); j++){
			// bottom collision check for cat
			if (all_pipes[i].isColliding(enemies[j].bottomX, enemies[j].bottomY)) // either 0 or 1 is returned
			{
				enemies[j].catCollisionFlag = 1; // colliding with any one pipe

			}
		}
	}

	for (int i = 0; i < enemies.size(); i++){
		// bottom collision check for cat
		if (current_player.isColliding(enemies[i].rightX, enemies[i].rightY) || current_player.isColliding(enemies[i].leftX, enemies[i].leftY)) // either 0 or 1 is returned
		{
			enemies[i].collide(); // colliding with player

		}
	}

	iShowImage(0, 0, 1280, 170, score_sprite);

	char pointsS[50];
	sprintf_s(pointsS, "%d", points);
	iText(720, 42, pointsS, GLUT_BITMAP_TIMES_ROMAN_24);
}

void updateLoop(){
	if (playerCollisionFlag == 0){ // colliding with no pipes at all
		if (!current_player.hasJumped){
			current_player.posY -= 8;
		}

		current_player.hasLanded = false;
	}
	else{
		current_player.hasLanded = true;
	}

	for (int i = 0; i < enemies.size(); i++){

		if ((enemies[i].catCollisionFlag == 0 && !enemies[i].isDead) || enemies[i].isDead){
			enemies[i].posY -= 12;
		}

		if (!enemies[i].isDead){
			enemies[i].move();
		}
	}

	if (current_player.hasJumped){
		if (current_player.jump_count < 16){
			current_player.posY += 10;
			current_player.jump_count++;
		}
		else{
			current_player.hasJumped = false;
			current_player.jump_count = 0;
		}
	}

	if (rightFlag){
		current_player.posX += 9;
	}

	if (leftFlag){
		current_player.posX -= 9;
	}

	// Screen looping logic 
	if (current_player.posX > 1280)
	{
		current_player.posX = 0;
	}
	else if (current_player.posX < 0)
	{
		current_player.posX = 1280;
	}

	for (int i = 0; i < enemies.size(); i++){

		if (enemies[i].posX > 1280)
		{
			enemies[i].posX = 0;

			if (enemies[i].posY < 250){
				enemies[i].posY = 640;
			}
		}
		else if (enemies[i].posX < 0)
		{
			enemies[i].posX = 1280;

			if (enemies[i].posY < 250){
				enemies[i].posY = 640;
			}
		}
	}
}

void updateBumpStatus(){
	for (int i = 0; i < pipe_count; i++){
		if (all_pipes[i].isBumped){
			if (all_pipes[i].bump_count < 7){
				all_pipes[i].posY += 10;
			}
			else if (all_pipes[i].bump_count < 14){
				all_pipes[i].posY -= 10;
			}

			all_pipes[i].bump_count++;

			if (all_pipes[i].bump_count >= 14){
				all_pipes[i].bump_count = 0;
				all_pipes[i].isBumped = false;
			}
		}
	}
}

void updateCatAnim(){
	for (int i = 0; i < enemies.size(); i++){
		enemies[i].animIndex++;

		if (enemies[i].animIndex > 9){
			enemies[i].animIndex = 0;
		}
	}
}

void spawnEnemy(){
	if (enemies.size() < enemy_count_max){
		enemies.push_back(cat());
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
	if (key == ' ')
	{
		if (current_player.hasLanded){
			current_player.hasJumped = true;
		}
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

void specialUp(int key, int x, int y){ // Called directly from glut
	if (key == 102){ // right key int value 102
		rightFlag = 0;
	}

	if (key == 100){
		leftFlag = 0;
	}
}

void iSpecialKeyboard(unsigned char key)
{


	if (key == GLUT_KEY_RIGHT)
	{
		rightFlag = 1;
	}
	if (key == GLUT_KEY_LEFT)
	{
		leftFlag = 1;
	}

}


int main()
{
	///srand((unsigned)time(NULL));
	iInitialize(1280, 780, "Three Knuckleheads");
	
	images(); // used an image function to declare the images
	generateMap(); // used a generateMap function to generate the pipes on the foreground

	iSetTimer(25, updateLoop);
	iSetTimer(5000, spawnEnemy);

	iSetTimer(100, updateCatAnim);
	iSetTimer(10, updateBumpStatus);

	glutSpecialUpFunc(specialUp); // subscribe the specialUp function to the glutSpecialUpFunc from glut.h
	iStart();

	return 0;
}