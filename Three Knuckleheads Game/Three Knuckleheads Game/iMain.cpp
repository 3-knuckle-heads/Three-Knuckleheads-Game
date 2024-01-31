#include "iGraphics.h"
#include<iostream>
#include<vector>
using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 780

enum pages { MENU, SETTINGS, LEVELS, SCORE, CREDITS, HELP, LVL1, LVL2, LVL3, BOSS };
pages page = MENU;
void changePage(pages p);

int background_sprite[3], score_sprite, menu_sprite, credits_sprite, settings_sprite, levels_sprite, help_sprite, highscore_sprite;
int player_sprite[3];
int pipe_sprite[3];
int cat_sprites[11];

int points = 0, health = 3, level = 1;
bool isSoundOn = true;

typedef struct player player;
struct player{ // Defines the player character for the game
	int posX = 50, posY = 190;
	int jump_count = 0;
	bool hasJumped = false, hasLanded = true;

	int bottomX, bottomY;
	int topX, topY;
	int rightX, rightY;
	int leftX, leftY;

	double rot = 0;

	bool isDead = false;

	player(){ ; };

	void render(){
		if (isDead){
			rot += 0.6;
			iRotate(posX, posY + 100/2, rot);
		}

		iShowImage(posX - 100 / 2, posY, 100, 100, player_sprite[level-1]);

		if (isDead){
			iUnRotate();
		}
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

	void die(){
		if (isSoundOn){
			PlaySound("sounds\\playerdie.wav", NULL, SND_ASYNC);
		}

		isDead = true;
		
		if (health < 1){
			// game over
		}
		else{
			health--;
		}
	}

	void reset(){
		isDead = false;
		posX = 50;
		posY = 190;
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

	double rot = 0;

	int animIndex = 0;
	int catCollisionFlag;

	bool isStunned = false;
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
		if (isDead){
			rot += 0.6;
			iRotate(posX, posY, rot);
		}

		if (!isStunned){
			iShowImage(posX - sizeX / 2, posY, sizeX, 100, cat_sprites[animIndex]);
		}
		else{
			iShowImage(posX - sizeX / 2, posY, sizeX, 100, cat_sprites[10]);
		}

		if (isDead){
			iUnRotate();
		}
	}

	void move(){
		int speed = 2;
		
		if (level == 2){
			speed = 3;
		}
		else if (level == 3){
			speed = 4;
		}

		if (leftToRight){
			posX += speed;
		}
		else{
			posX -= speed;
		}
	}

	void stun(){
		isStunned = !isStunned;
		posY += 50;
	}

	void die(){
		if (isSoundOn){
			PlaySound("sounds\\enemydie.wav", NULL, SND_ASYNC);
		}

		isDead = true;
		points += 100;
	}

	void collide(){
		if (isStunned){
			die();
		}
		else if (!current_player.isDead){
			current_player.die();
		}
	}

	void updateBounds(){
		bottomX = posX, bottomY = posY;
		topX = posX, topY = posY + 100;
		rightX = posX + sizeX / 2, rightY = posY + 100 / 2;
		leftX = posX - sizeX / 2, leftY = posY + 100 / 2;
	}
};

int enemy_count_max = 10;
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
		iShowImage(posX, posY, sizeX, sizeY, pipe_sprite[level-1]);
	}

	int isColliding(int x, int y){ // checks if target is colliding with a particular pipe or not
		if ((x >= posX && x <= posX + sizeX) && (y >= posY && y <= posY + sizeY)){
			return 1;
		}

		return 0;
	}

	void bump(){
		if (isSoundOn){
			PlaySound("sounds\\bump.wav", NULL, SND_ASYNC);
		}

		isBumped = true;

		for (int i = 0; i < enemies.size(); i++){
			if (isColliding(enemies[i].bottomX, enemies[i].bottomY)){
				enemies[i].stun();
			}
		}
	}
};


vector<pipe> all_pipes; // vector to maintain all the pipes

int mouseX, mouseY;

typedef struct button button;
struct button{
	int rightX, leftX, topY, bottomY;
	(void*)func;
	
	button(){ ; };

	button(int rX, int lX, int tY, int bY, void (*f)(void)){
		rightX = rX;
		leftX = lX;
		topY = tY;
		bottomY = bY;

		func = f;
	};

	bool hasPressed(){
		if (mouseX >= leftX && mouseX <= rightX && mouseY >= bottomY && mouseY <= topY){
			return true;
		}
		return false;
	}

	void callFunc(){
		((void(*)())func)();
	}
};

int menu_button_count = 6;
button menuButtons[6];

int volume_button_count = 2;
button volumeButtons[2];

int level_button_count = 3;
button levelButtons[3];

void images()
{
	///updated see the documentations
	player_sprite[0] = iLoadImage("./images/Nayem.png");
	player_sprite[1] = iLoadImage("./images/Durjoy.png");
	player_sprite[2] = iLoadImage("./images/Pabak.png");
	background_sprite[0] = iLoadImage("./images/bg.png");
	background_sprite[1] = iLoadImage("./images/bg1.png");
	background_sprite[2] = iLoadImage("./images/bg2.png");
	score_sprite = iLoadImage("./images/board.png");
	
	pipe_sprite[0] = iLoadImage("./images/pipe.png");
	pipe_sprite[1] = iLoadImage("./images/pipe1.png");
	pipe_sprite[2] = iLoadImage("./images/pipe2.png");
	menu_sprite = iLoadImage("./images/Menu.png");
	credits_sprite = iLoadImage("./images/Credits.jpg");
	settings_sprite = iLoadImage("./images/Volume.jpg");
	levels_sprite = iLoadImage("./images/Levels.png");
	help_sprite = iLoadImage("./images/Help.jpg");
	highscore_sprite = iLoadImage("./images/highscore.png");

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
	all_pipes.push_back(pipe(0,300));
	all_pipes.push_back(pipe(120, 300));
	all_pipes.push_back (pipe(240, 300));
	all_pipes.push_back(pipe(360, 300));
	all_pipes.push_back (pipe(680, 300));
	all_pipes.push_back (pipe(800, 300));
	all_pipes.push_back(pipe(920, 300));
	all_pipes.push_back(pipe(1040, 300));
	all_pipes.push_back(pipe(1160, 300));   // 0 to 8 index



	// Vertical level 2
	all_pipes.push_back(pipe(240, 450));
	all_pipes.push_back(pipe(360, 450));
	all_pipes.push_back(pipe(480, 450));
	all_pipes.push_back(pipe(600, 450));
	all_pipes.push_back(pipe(720, 450));
	all_pipes.push_back(pipe(1040, 450));
	all_pipes.push_back(pipe(1160, 450));

	// Vertical level 3
	all_pipes.push_back(pipe(0, 600));
	all_pipes.push_back(pipe(120, 600));
	all_pipes.push_back(pipe(240, 600));
	all_pipes.push_back(pipe(360, 600));
	all_pipes.push_back(pipe(680, 600));
	all_pipes.push_back(pipe(800, 600));
	all_pipes.push_back(pipe(920, 600));
	all_pipes.push_back(pipe(1040, 600));
	all_pipes.push_back(pipe(1160, 600));

	// Bottom (under score image) pipe, so that player does not fall through bottom
	all_pipes.push_back(pipe(0, 0));
	all_pipes[25].sizeX = 1400;
	all_pipes[25].sizeY = 170;

	// Side (out of screen) pipes, so that player does not fall when looping the screen
	all_pipes.push_back(pipe(-120, 300));
	all_pipes.push_back(pipe(SCREEN_WIDTH, 300));
	all_pipes.push_back(pipe(SCREEN_WIDTH, 450));
	all_pipes.push_back(pipe(-120, 600));
	all_pipes.push_back(pipe(SCREEN_WIDTH, 600));
}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void drawLvl(){
	current_player.updateBounds();

	for (int i = 0; i < enemies.size(); i++)
		enemies[i].updateBounds();

	iShowImage(0, 150, SCREEN_WIDTH, 650, background_sprite[level - 1]);

	// render the player
	current_player.render();
	for (int i = 0; i < enemies.size(); i++){
		enemies[i].render();
		enemies[i].catCollisionFlag = 0;
	}

	//iShowImage(250, 650, 100, 50, pruz_sprite);

	playerCollisionFlag = 0; // flag for colliding

	for (int i = 0; i < all_pipes.size(); i++){
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
		if (enemies[i].isDead) continue;

		// bottom collision check for cat
		if (current_player.isColliding(enemies[i].rightX, enemies[i].rightY) || current_player.isColliding(enemies[i].leftX, enemies[i].leftY)) // either 0 or 1 is returned
		{
			enemies[i].collide(); // colliding with player
		}
	}

	bool allDead = true;
	for (int i = 0; i < enemies.size(); i++){
		if (!enemies[i].isDead){
			allDead = false;
		}
	}

	if (allDead){
		// you win
	}

	iShowImage(0, 0, SCREEN_WIDTH, 170, score_sprite);
	iShowImage(22, 25, 125, 125, player_sprite[level - 1]);

	iSetColor(55, 228, 255);

	char pointsS[20];
	sprintf_s(pointsS, "%d", points);
	iText(433, 45, pointsS, GLUT_BITMAP_TIMES_ROMAN_24);

	char healthS[20];
	sprintf_s(healthS, "%d", health);
	iText(433, 115, healthS, GLUT_BITMAP_TIMES_ROMAN_24);

	char levelS[20];
	sprintf_s(levelS, "%d", level);
	iText(800, 83, levelS, GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0, 0, 0);
}

void drawMenu(){
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menu_sprite);
}

void iDraw()
{
	iClear(); // MENU, SETTINGS, LEVELS, SCORE, CREDITS, HELP, LVL1, LVL2, LVL3, BOSS

	if (page == MENU){
		drawMenu();
	}
	else if (page == SETTINGS){
		iShowImage(0, 0, 1280, 780, settings_sprite);
	}
	else if (page == LEVELS){
		iShowImage(0, 0, 1280, 780, levels_sprite);
	}
	else if (page == SCORE){
		iShowImage(0, 0, 1280, 780, highscore_sprite);
	}
	else if (page == CREDITS){
		iShowImage(0, 0, 1280, 780, credits_sprite);
	}
	else if (page == HELP){
		iShowImage(0, 0, 1280, 780, help_sprite);
	}
	else if (page == LVL1){
		drawLvl();
	}
	else if (page == LVL2){
		drawLvl();
	}
	else if (page == LVL3){
		drawLvl();
	}
	else if (page == BOSS){

	}
}

void updateLoop(){
	if (page != LVL1 && page != LVL2 && page != LVL3) return;

	if (playerCollisionFlag == 0){ // colliding with no pipes at all
		if (!current_player.hasJumped){
			current_player.posY -= 8;
		}

		current_player.hasLanded = false;
	}
	else{
		current_player.hasLanded = true;
	}

	if (current_player.isDead){
		current_player.posY -= 10;
	}

	for (int i = 0; i < enemies.size(); i++){

		if (enemies[i].catCollisionFlag == 0){
			enemies[i].posY -= 12;
		}
		else if (enemies[i].isDead){
			enemies[i].posY -= 16;
		}

		if (!enemies[i].isStunned){
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
	if (current_player.posX > SCREEN_WIDTH)
	{
		current_player.posX = 0;
	}
	else if (current_player.posX < 0)
	{
		current_player.posX = SCREEN_WIDTH;
	}

	if (current_player.posY < 0 && health > 0){
		current_player.reset();
	}

	for (int i = 0; i < enemies.size(); i++){

		if (enemies[i].posX > SCREEN_WIDTH)
		{
			enemies[i].posX = 0;

			if (enemies[i].posY < 250){
				if (enemies[i].posX > SCREEN_WIDTH)
					enemies[i].posY = 640;
			}
		}
		else if (enemies[i].posX < 0)
		{
			enemies[i].posX = SCREEN_WIDTH;

			if (enemies[i].posY < 250){
				enemies[i].posY = 640;
			}
		}
	}
}

void updateBumpStatus(){
	if (page != LVL1 && page != LVL2 && page != LVL3) return;

	for (int i = 0; i < all_pipes.size(); i++){
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
	if (page != LVL1 && page != LVL2 && page != LVL3) return;

	for (int i = 0; i < enemies.size(); i++){
		enemies[i].animIndex++;

		if (enemies[i].animIndex > 9){
			enemies[i].animIndex = 0;
		}
	}
}

void createEnemy(){
	if (enemies.size() < enemy_count_max){
		enemies.push_back(cat());
	}
}

void spawnEnemyLvl1(){
	if (page != LVL1) return;

	createEnemy();
}
void spawnEnemyLvl2(){
	if (page != LVL2) return;

	createEnemy();
}
void spawnEnemyLvl3(){
	if (page != LVL3) return;

	createEnemy();
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
		mouseX = mx;
		mouseY = my;
		if (page == MENU){
			for (int i = 0; i < menu_button_count; i++){
				if (menuButtons[i].hasPressed()){
					menuButtons[i].callFunc();
				}
			}
		}
		else if (page == SETTINGS){
			for (int i = 0; i < volume_button_count; i++){
				if (volumeButtons[i].hasPressed()){
					volumeButtons[i].callFunc();
				}
			}
		}
		else if (page == LEVELS){
			for (int i = 0; i < level_button_count; i++){
				if (levelButtons[i].hasPressed()){
					levelButtons[i].callFunc();
				}
			}
		}
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
	if (key == GLUT_KEY_HOME || key == GLUT_KEY_F1){
		changePage(MENU);
	}
}

void play(){
	changePage(LEVELS);
}

void highscore(){
	changePage(SCORE);
}

void settings(){
	changePage(SETTINGS);
}

void credits(){
	changePage(CREDITS);
}

void quit(){
	exit(0);
}

void help(){
	changePage(HELP);
}

void soundOn(){
	isSoundOn = true;
	cout << "volume on";
}

void soundOff(){
	isSoundOn = false;
	cout << "volume off";
	PlaySound(0, 0, 0);
}

void lvl1(){
	changePage(LVL1);
}

void lvl2(){
	changePage(LVL2);
}

void lvl3(){
	changePage(LVL3);
}

void startMenu(){


	menuButtons[0] = button(1220, 870, 730, 640, play);
	menuButtons[1] = button(1220, 870, 580, 490, highscore);
	menuButtons[2] = button(1220, 870, 430, 340, settings);
	menuButtons[3] = button(1220, 870, 280, 190, credits);
	menuButtons[4] = button(1220, 870, 130, 40, quit);
	menuButtons[5] = button(75, 5, 100, 30, help);

	if (isSoundOn){
		PlaySound("sounds\\bgmusic.wav", NULL, SND_LOOP | SND_ASYNC);
	}
}

void startSettings(){
	volumeButtons[0] = button(750, 650, 440, 340, soundOn);
	volumeButtons[1] = button(900, 800, 440, 340, soundOff);
}

void startLevels(){
	levelButtons[0] = button(370, 135, 470, 230, lvl1);
	levelButtons[1] = button(760, 520, 470, 230, lvl2);
	levelButtons[2] = button(1145, 905, 470, 230, lvl3);
}

void resetLevel(){
	all_pipes.clear();
	enemies.clear();

	points = 0;
	current_player.posX = 50;
	current_player.posY = 190;
}

void startLvl(int lvl){
	resetLevel();
	PlaySound(0, 0, 0);

	if (lvl == 1){
		health = 3;
		level = 1;
		enemy_count_max = 10;
	}
	else if (lvl == 2){
		health = 5;
		level = 2;
		enemy_count_max = 15;
	}
	else if (lvl == 3){
		health = 7;
		level = 3;
		enemy_count_max = 20;
	}

	generateMap(); // used a generateMap function to generate the pipes on the foreground
}

void changePage(pages p){
	page = p;

	if (page == MENU){
		startMenu();
	}
	else if (page == SETTINGS){
		startSettings();
	}
	else if (page == LEVELS){
		startLevels();
	}
	else if (page == LVL1){
		startLvl(1);
	}
	else if (page == LVL2){
		startLvl(2);
	}
	else if (page == LVL3){
		startLvl(3);
	}
}

int main()
{
	///srand((unsigned)time(NULL));
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Three Knuckleheads");
	
	images(); // used an image function to declare the images

	changePage(MENU);

	iSetTimer(25, updateLoop);
	iSetTimer(5000, spawnEnemyLvl1);
	iSetTimer(4000, spawnEnemyLvl2);
	iSetTimer(3000, spawnEnemyLvl3);

	iSetTimer(100, updateCatAnim);
	iSetTimer(10, updateBumpStatus);

	glutSpecialUpFunc(specialUp); // subscribe the specialUp function to the glutSpecialUpFunc from glut.h
	iStart();

	return 0;
}