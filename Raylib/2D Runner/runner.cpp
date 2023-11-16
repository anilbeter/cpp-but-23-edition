#include "raylib.h"

int main()
{
  const int window_width = 512;
  const int window_height = 380;
  InitWindow(window_width, window_height, "2D Runner");

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
  }
  CloseWindow();
}