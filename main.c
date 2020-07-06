#include "drw.h"
#include <time.h>
#include <raylib.h>
#include <raymath.h>

#define NUM_TARGETS 6

#define R() ((float)GetRandomValue(20, 80) / 10)
#define RANDOM_POS() (Vector2) { R(), R() };

int main()
{
	const int screenw = 800,
		screenh = 450;

	InitWindow(screenw, screenh, "head clicker");
	SetExitKey(0);

	Camera3D camera = { 0 };
	camera.position = (Vector3){ -5.0f, 5.0f, 0.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.type = CAMERA_PERSPECTIVE;

	SetCameraMode(camera, CAMERA_FREE);

	Vector3 cubepos = { 0.0f, 0.0f, 0.0f };

	SetTargetFPS(120);

	bool clicked = false;
	bool paused = true;

	SetWindowMinSize(1280, 720);
	SetMouseScale(0.1, 0.1);
	SetCameraMoveControls(0, 0, 0, 0, 0, 0);

	Vector2 targets[NUM_TARGETS] = { 0 };

	for (int i = 0; i < NUM_TARGETS; i++)
	{
		targets[i] = RANDOM_POS()
	}

	Vector3 where = (Vector3){5, 5, 0};

	camera.target = where;

	long score = 0;

	clock_t last = clock();

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_GRAVE))
		{
			SetWindowSize(1920, 1080);
			ToggleFullscreen();
		}

		if (paused)
		{
			BeginDrawing();

				ClearBackground(BG);

				DrawText("Game Paused. Click to resume", 10, 10, 20, WHITE);

				if (IsMouseButtonPressed(0))
				{
					paused = false;
					SetCameraMode(camera, CAMERA_FIRST_PERSON);
				}

			EndDrawing();
		}
		else
		{
			if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ESCAPE))
			{
				paused = true;
				SetCameraMode(camera, CAMERA_FREE);
			}

			UpdateCamera(&camera);
			
			BeginDrawing();

				ClearBackground(clicked ? RED : RAYWHITE);
				BeginMode3D(camera);

					Ray ray = { 0 };
					ray.position = camera.position;
					ray.direction = Vector3Subtract(camera.target, camera.position);

					drwboard(where, 10, 10);
					int c = drwtargets(ray, where, targets, NUM_TARGETS);

					DrawGrid(10, 1.0f);

					if (c != -1 && IsMouseButtonPressed(0))
					{
						puts("CLICKED");
						targets[c] = RANDOM_POS();

						clock_t now = clock();

						score += now - last > 1200 ? 800 : 2000 - (now - last);
						last = now;
					}
					else if (IsMouseButtonPressed(0))
					{
						score -= 1000;
					}

				EndMode3D();

				DrawText(FormatText("Score: %d", score), 10, 40, 20, RED);

				drwxhair();
				DrawFPS(10, 10);

			EndDrawing();
		}
	}

	CloseWindow();

	return 0;
}
