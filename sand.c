#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include "raylib.h"

/* #include "rlgl.h" */
#include "raymath.h"

#define WIDTH 604
#define HEIGHT 604


typedef enum  {
	EMPTY,
	SAND,
	ICE,
	WOOD,
	/* FIRE, */
	/* SMOKE, */
} ParticalType;

typedef struct {
	ParticalType type;
} Partical;


Partical grid[300][300];
Partical Ogrid[300][300];

void generate_empty_world()
{
	for (int i = 0; i < 300 - 1; i++) {
		for (int j = 0; j < 300 - 1; j++) {
			grid[i][j].type = EMPTY;
			Ogrid[i][j].type = EMPTY;
		}
	}
}

void sand(const Partical partical)
{
}

void update(void)
{
  for (int i = 0; i < 300 - 1; i++) {
		for (int j = 0; j < 300 - 1; j++) {
			switch (Ogrid[i][j].type) {
			case EMPTY: break;
			case SAND:
				if (j == 298) break;
				if (Ogrid[i][j+1].type == EMPTY) {
					grid[i][j+1].type = SAND;
					grid[i][j].type = EMPTY;
				}
				else if (Ogrid[i][j+1].type == ICE) {
					grid[i][j+1].type = SAND;
					grid[i][j].type = ICE;
				}
				else if (Ogrid[i+1][j+1].type == EMPTY) {
					grid[i+1][j+1].type = SAND;
					grid[i][j].type = EMPTY;
				}
				else if(Ogrid[i-1][j+1].type == EMPTY) {
					grid[i-1][j+1].type = SAND;
					grid[i][j].type = EMPTY;
				};
				break;
				
			case ICE:
				if (j == 298) break;
				
				int dx = (rand() % 3) - 1;
				int dy = (rand() % 2) + 1;

				if (Ogrid[i + dx][j + dy].type == EMPTY) {
					grid[i + dx][j + dy].type = ICE;
					grid[i][j].type = EMPTY;
				} 
				break;
			case WOOD:
				break;
			}
		}
	}
}


void draw(void)
{
	for (int i = 0; i < 300 - 1; i++) {
		for (int j = 0; j < 300 - 1; j++) {
			switch (grid[i][j].type) {
			case EMPTY:  break;
			case SAND: DrawRectangle(i*2, j*2, 2 , 2, YELLOW); break;
			case ICE: DrawRectangle(i*2, j*2, 2 , 2, WHITE); break;
			case WOOD: DrawRectangle(i*2, j*2, 2 , 2, BROWN); break;
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
				ClearBackground(SKYBLUE);
				DrawText("right click for snow, left for sand", 5, 5, 20, BLACK);
				
				BeginMode2D(camera);
				{
					Vector2 pos = GetMousePosition();
					pos = (Vector2){pos.x/2, pos.y/2};
					if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
						{
							grid[(int)pos.x][(int)pos.y].type = WOOD;
							grid[(int)pos.x+1][(int)pos.y].type = WOOD;
							grid[(int)pos.x][(int)pos.y+1].type = WOOD;
							grid[(int)pos.x+1][(int)pos.y+1].type = WOOD;

							grid[(int)pos.x-1][(int)pos.y].type = WOOD;
							grid[(int)pos.x][(int)pos.y-1].type = WOOD;
							grid[(int)pos.x-1][(int)pos.y-1].type = WOOD;
						}
					if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
						{
							grid[(int)pos.x][(int)pos.y].type = SAND;
							grid[(int)pos.x+5][(int)pos.y+5].type = SAND;
							grid[(int)pos.x-5][(int)pos.y-5].type = SAND;
							grid[(int)pos.x+5][(int)pos.y].type = SAND;
							grid[(int)pos.x-5][(int)pos.y].type = SAND;
							grid[(int)pos.x][(int)pos.y+5].type = SAND;
							grid[(int)pos.x][(int)pos.y-5].type = SAND;
						}
					
					if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
						grid[(int)pos.x][(int)pos.y].type = ICE;
						grid[(int)pos.x+1][(int)pos.y+1].type = ICE;
						grid[(int)pos.x+2][(int)pos.y+2].type = ICE;
						grid[(int)pos.x+3][(int)pos.y+3].type = ICE;
					}
					if (IsKeyDown(KEY_D)) {
						grid[(int)pos.x][(int)pos.y].type = EMPTY;
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
