#include "raylib.h"

int main()
{
  int width = 350;
  int height = 200;
  InitWindow(width, height, "Winter");

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
  }
}