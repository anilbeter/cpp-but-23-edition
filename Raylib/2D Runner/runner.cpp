#include "raylib.h"

int main()
{
  const int window_width = 512;
  const int window_height = 380;
  InitWindow(window_width, window_height, "2D Runner");

  const int gravity = 1;

  // Character textures
  Texture2D ilayda = LoadTexture("textures/scarfy.png");
  Rectangle ilaydaRec;
  ilaydaRec.width = ilayda.width / 6;
  ilaydaRec.height = ilayda.height;
  ilaydaRec.x = 0;
  ilaydaRec.y = 0;
  Vector2 ilaydaPos;
  ilaydaPos.x = window_width / 2 - (ilaydaRec.width / 2);
  ilaydaPos.y = window_height - ilaydaRec.height;

  int velocity = 0;
  bool isInAir;
  const int jumpVelocity = -22;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    if (ilaydaPos.y > window_height - ilaydaRec.height)
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
    ilaydaPos.y += velocity;

    DrawTextureRec(ilayda, ilaydaRec, ilaydaPos, WHITE);

    EndDrawing();
  }
  UnloadTexture(ilayda);
  CloseWindow();
}