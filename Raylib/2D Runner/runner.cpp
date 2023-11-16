#include "raylib.h"

int main()
{
  const int window_width = 512;
  const int window_height = 380;
  InitWindow(window_width, window_height, "2D Runner");

  const int width = 50;
  const int height = 80;

  int posY = window_height - height;
  int velocity = 0;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    if (IsKeyPressed(KEY_SPACE))
    {
      velocity = -10;
    }
    posY += velocity;

    DrawRectangle(window_width / 2, posY, width, height, BLUE);

    EndDrawing();
  }
  CloseWindow();
}