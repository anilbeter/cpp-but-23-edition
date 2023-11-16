#include "raylib.h"

int main()
{
  const int window_width = 512;
  const int window_height = 380;
  InitWindow(window_width, window_height, "2D Runner");

  const int gravity = 1;

  const int width = 50;
  const int height = 80;

  int posY = window_height - height;
  int velocity = 0;
  bool isInAir;
  const int jumpVelocity = -22;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    if (posY > window_height - height)
    {
      velocity = 0;
      isInAir = false;
    }
    else
    {
      isInAir = true;
      velocity += gravity;
    }

    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVelocity;
    }
    posY += velocity;

    DrawRectangle(window_width / 2, posY, width, height, BLUE);

    EndDrawing();
  }
  CloseWindow();
}