// Include raylib library
#include "raylib.h"

int main()
{
  int width = 350;
  int height = 200;
  InitWindow(width, height, "Another Life");

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RED);
    DrawCircle(350 / 2, 200 / 2, 25, BLUE);
    EndDrawing();
  }
}