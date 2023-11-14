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
    EndDrawing();
  }
}