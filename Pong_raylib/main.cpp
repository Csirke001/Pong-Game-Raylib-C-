#include <raylib.h>
#include <iostream>

//global variables
const int screenwidth = 800;
const int screenheight = 800;

const float speed = 10.0f;

//Structures
struct paddle {
	float height_x;
	float height_y;

	float pos_x;
	float pos_y;
	
	int score;
};

paddle p1;
paddle p2;

struct ball {
	float pos_x;
	float pos_y;
	float radius;

	float speedx;
	float speedy;
};

ball Ball;

//function declarations
void init_players();
void init_ball();

void moveP1(paddle &player);
void moveP2(paddle &player);

void ballBounce();

int main() {

	//Init window
	InitWindow(screenwidth, screenheight, "Pong Raylib");

	init_players();
	init_ball();

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		//Update variables
		ballBounce();
		moveP1(p1);
		moveP2(p2);

		//Draw
		BeginDrawing();
		ClearBackground(BLACK);

		//Draw p1 & p2
		DrawRectangle(p1.pos_x, p1.pos_y, p1.height_x, p1.height_y, WHITE);
		DrawRectangle(p2.pos_x, p2.pos_y, p2.height_x, p2.height_y, WHITE);

		//Draw ball
		DrawCircle(Ball.pos_x, Ball.pos_y, Ball.radius, WHITE);

		//Draw score
		DrawText(TextFormat("%i", p1.score), 150, 100, 75, WHITE);
		DrawText(TextFormat("%i", p2.score), 650, 100, 75, WHITE);
		
		EndDrawing();
	}
	return 0;
}

//Function definitons
void init_players() {
	//Init p1
	p1.height_x = 25.0f;
	p1.height_y = 100.0f;

	p1.pos_x = 100.0f;
	p1.pos_y = 350.0f;

	//Init p2
	p2.height_x = 25.0f;
	p2.height_y = 100.0f;

	p2.pos_x = 700.0f;
	p2.pos_y = 350.0f;
}

void init_ball() {
	Ball.pos_x = 400.0f;
	Ball.pos_y = 400.0f;
	Ball.radius = 20.0f;

	Ball.speedx = 6.5f;
	Ball.speedy = 6.5f;
}

void moveP1(paddle &player) {
	if (IsKeyDown(KEY_W))
	{
		player.pos_y -= speed;
	}
	else if (IsKeyDown(KEY_S))
	{
		player.pos_y += speed;
	}
}

void moveP2(paddle &player) {
	if (IsKeyDown(KEY_UP))
	{
		player.pos_y -= speed;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		player.pos_y += speed;
	}
}


void ballBounce() {
	Ball.pos_x += Ball.speedx;
	Ball.pos_y += Ball.speedy;

	//Screen collision
	if (Ball.pos_y >= screenheight)
	{
		Ball.speedy *= -1;
	}

	if (Ball.pos_y <= 0)
	{
		Ball.speedy *= -1;
	}

	if (Ball.pos_x >= screenwidth)
	{
		//Adds score to player 1
		Ball.pos_x = 400;
		p1.score++;

		Ball.speedx *= -1;
	}
	if (Ball.pos_x <= 0)
	{
		Ball.pos_x = 400;
		p2.score++;
		Ball.speedx *= -1;
	}

	//Paddle collision
	if (CheckCollisionCircleRec(Vector2{Ball.pos_x, Ball.pos_y}, Ball.radius, Rectangle{p1.pos_x, p1.pos_y, p1.height_x, p1.height_y}))
	{
		Ball.speedx *= -1;
	}

	if (CheckCollisionCircleRec(Vector2{ Ball.pos_x, Ball.pos_y }, Ball.radius, Rectangle{ p2.pos_x, p2.pos_y, p2.height_x, p2.height_y }))
	{
		Ball.speedx *= -1;
	}
}