#include <stdio.h>
#include <time.h>
#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"

#define WIDTH 502
#define HEIGHT 502


typedef enum  {
	EMPTY,
	SAND,
	WATER,
	/* FIRE, */
	/* SMOKE, */
} ParticalType;

typedef struct {
	ParticalType type;
} Partical;


Partical grid[WIDTH][HEIGHT];
Partical Ogrid[WIDTH][HEIGHT];

void generate_empty_world() {
	for (int i = 0; i < WIDTH - 1; i++) {
		for (int j = 0; j < HEIGHT - 1; j++) {
			grid[i][j].type = EMPTY;
			Ogrid[i][j].type = EMPTY;
		}
	}
}

void sand(const Partical partical) {
}

void update(void) {
  for (int i = 0; i < WIDTH - 1; i++) {
		for (int j = 0; j < HEIGHT - 1; j++) {
			switch (Ogrid[i][j].type) {
			case EMPTY: break;
			case SAND:
				if (j == 500) break;
				if (Ogrid[i][j+1].type == EMPTY) {
					grid[i][j+1].type = SAND;
					grid[i][j].type = EMPTY;
				} else if (Ogrid[i+1][j+1].type == EMPTY) {
					grid[i+1][j+1].type = SAND;
					grid[i][j].type = EMPTY;
				} else if(Ogrid[i-1][j+1].type == EMPTY) {
					grid[i-1][j+1].type = SAND;
					grid[i][j].type = EMPTY;
				};
				break;
			case WATER:
				if (j == 500) break;
				if (Ogrid[i][j+1].type == EMPTY) {
					grid[i][j+1].type = WATER;
					grid[i][j].type = EMPTY;
				} else if (Ogrid[i][j+1].type == SAND) {
					break;
				} else if (Ogrid[i+1][j+1].type == EMPTY) {
					grid[i+1][j+1].type = WATER;
					grid[i][j].type = EMPTY;
				} else if (Ogrid[i-1][j+1].type == EMPTY) {
					grid[i-1][j+1].type = WATER;
					grid[i][j].type = EMPTY;
				} else if (Ogrid[i+1][j].type == EMPTY) {
					grid[i+1][j].type = WATER;
					grid[i][j].type = EMPTY;
				} else if (Ogrid[i-1][j].type == EMPTY) {
					grid[i-1][j].type = WATER;
					grid[i][j].type = EMPTY;
				};
				break;
			}
		}
	}
}


void draw(void) {
	for (int i = 0; i < WIDTH - 1; i++) {
		for (int j = 0; j < HEIGHT - 1; j++) {
			switch (grid[i][j].type) {
			case EMPTY:  break;
			case SAND: DrawRectangle(i, j, 2 , 2, YELLOW); break;
			case WATER: DrawRectangle(i, j, 2 , 2, BLUE); break;
			}
			Ogrid[i][j] = grid[i][j];
		}
	}
}

int main()
{
	
	InitWindow(WIDTH, HEIGHT, "example");

	Camera2D camera = { 0 };
	camera.zoom = 1.0f;

	SetTargetFPS(90);
	generate_empty_world();
	while (!WindowShouldClose())
		{
			/* if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) */
			/* 	{ */
			/* 		Vector2 delta = GetMouseDelta(); */
			/* 		/\* scale the vector based on size then invert the sign *\/ */
			/* 		/\* delta = Vector2Scale(delta, -1.0f/camera.zoom); *\/ */
			/* 		camera.target = Vector2Add(camera.target, delta); */
			/* 	} */
			
			BeginDrawing();
			{
			ClearBackground(RAYWHITE);
				BeginMode2D(camera);
				{
					Vector2 pos = GetMousePosition();
					/* DrawText("pos", pos.x, pos.y, 12,BLACK); */
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
						{
							grid[(int)pos.x][(int)pos.y].type = SAND;
							grid[(int)pos.x+1][(int)pos.y+1].type = SAND;
							grid[(int)pos.x+2][(int)pos.y+2].type = SAND;
							grid[(int)pos.x+3][(int)pos.y+3].type = SAND;
						}
					if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
							grid[(int)pos.x][(int)pos.y].type = WATER;
							grid[(int)pos.x+1][(int)pos.y+1].type = WATER;
							grid[(int)pos.x+2][(int)pos.y+2].type = WATER;
							grid[(int)pos.x+3][(int)pos.y+3].type = WATER;
					}
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
