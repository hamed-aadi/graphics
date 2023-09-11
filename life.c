#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

#define WIDTH 604
#define HEIGHT 604

bool Ogrid[300][300];
bool grid[300][300];

void generate_random_grid()
{
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			int j = (rand() % 2);
			grid[i][j] = j; 
			Ogrid[i][j] = j;
		}
	}
}

int number_neighbours(const int i, const int j)
{
	int num = 0;
	if (Ogrid[i+1][j] == 1) num++;
	if (Ogrid[i-1][j] == 1) num++;
	if (Ogrid[i][j+1] == 1) num++;
	if (Ogrid[i][j-1] == 1) num++;
	if (Ogrid[i+1][j+1] == 1) num++;
	if (Ogrid[i-1][j-1] == 1) num++;
	if (Ogrid[i+1][j-1] == 1) num++;
	if (Ogrid[i-1][j+1] == 1) num++;
	return num;
}

void update()
{
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			int neighbours = number_neighbours(i, j);
			if (Ogrid[i][j] == 1) {
				if (neighbours < 2 || neighbours > 3) grid[i][j] = 0;
			} else {
				if (neighbours == 3) grid[i][j] = 1;
			}
		}
	}
}

void draw() {
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			if (grid[i][j] == 1) {
				/* random color ? */
				DrawRectangle(i*2, j*2, 2, 2, BLUE);
			}
			Ogrid[i][j] = grid[i][j];
		}
	}
}

int main() {
	generate_random_grid();
	InitWindow(WIDTH, HEIGHT, "life");

	Camera2D camera = { 0 };
	camera.zoom = 1.0f;

	SetTargetFPS(60);
	generate_random_grid();
	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);
			BeginMode2D(camera);
			{
				update();
				draw();
			}
			EndMode2D();
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
