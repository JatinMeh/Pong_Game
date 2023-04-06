#include "raylib.h"

struct Ball
{
	float x, y;
	float SpeedX, SpeedY;
	float radius;

	void Draw() {
		DrawCircle((int) x, (int) y, radius, WHITE);
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle getRec() 
	{
		return Rectangle{ x - width / 2,y - height / 2,10,100 };
	}
	

	void Draw() {
		DrawRectangle(x-width/2,y-height/2 , 10, 100, WHITE);
	}
};
int main() {
	
	InitWindow(800,600,"pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5; 
	ball.SpeedX = 200;
	ball.SpeedY = 250;

	Paddle LeftPaddle;
	LeftPaddle.x = 50;
	LeftPaddle.y = GetScreenHeight() / 2;
	LeftPaddle.width = 10;
	LeftPaddle.height = 100;
	LeftPaddle.speed = 250;

	Paddle RightPaddle;
	RightPaddle.x = GetScreenWidth() - 50;
	RightPaddle.y = GetScreenHeight() / 2;
	RightPaddle.width = 10;
	RightPaddle.height = 100;
	RightPaddle.speed = 250;

	while (!WindowShouldClose()) {

		ball.x += ball.SpeedX * GetFrameTime();
		ball.y += ball.SpeedY * GetFrameTime();

		if (ball.y < 0) {
			ball.y = 0;
			ball.SpeedY *= -1;
		}
		if (ball.y > GetScreenHeight()) {
			ball.y = GetScreenHeight();
			ball.SpeedY *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, LeftPaddle.getRec())) {
			if (ball.SpeedX < 0)
			{
				ball.SpeedX *= -1.07f;
			}
		
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, RightPaddle.getRec())) {
			if (ball.SpeedX > 0)
			{
				ball.SpeedX *= -1.07f;
			}

		}

		if (IsKeyDown(KEY_W)) {
			LeftPaddle.y -= LeftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S)) {
			LeftPaddle.y += LeftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP)) {
			RightPaddle.y -= LeftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN)) {
			RightPaddle.y += LeftPaddle.speed * GetFrameTime();
		}
		if (IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.SpeedX = 200;
			ball.SpeedY = 250;
		}

		BeginDrawing();
			ClearBackground(BLACK);

			ball.Draw();
			LeftPaddle.Draw();
			RightPaddle.Draw();

			DrawFPS(10,10);

		EndDrawing();
	}


	CloseWindow();
	return 0;
}