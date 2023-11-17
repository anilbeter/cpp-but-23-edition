#include "raylib.h"

int main()
{
  const int windowWidth = 512;
  const int windowHeight = 380;
  InitWindow(windowWidth, windowHeight, "2D Runner");

  const int gravity = 1'000; //(1000)

  // Character textures
  Texture2D ilayda = LoadTexture("textures/scarfy.png");
  Rectangle ilaydaRec;
  ilaydaRec.width = ilayda.width / 6;
  ilaydaRec.height = ilayda.height;
  ilaydaRec.x = 0;
  ilaydaRec.y = 0;
  Vector2 ilaydaPos;
  ilaydaPos.x = windowWidth / 2 - (ilaydaRec.width / 2);
  ilaydaPos.y = windowHeight - ilaydaRec.height;

  int velocity = 0;
  bool isInAir;
  const int jumpVelocity = -600;

  int frame;
  const float updateTime = 1.0 / 12.0;
  float runningTime;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    const float dT = GetFrameTime();

    if (ilaydaPos.y > windowHeight - ilaydaRec.height)
    {
      velocity = 0;
      isInAir = false;
    }
    else
    {
      isInAir = true;
      velocity += gravity * dT;
    }

    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVelocity;
    }
    ilaydaPos.y += velocity * dT;

    // Update Running Time
    runningTime += dT;
    if (runningTime >= updateTime)
    {
      runningTime = 0.0;

      // Update Animation Frame
      ilaydaRec.x = frame * ilaydaRec.width;
      frame++;
      if (frame > 5)
      {
        frame = 0;
      }
    }

    DrawTextureRec(ilayda, ilaydaRec, ilaydaPos, WHITE);

    EndDrawing();
  }
  UnloadTexture(ilayda);
  CloseWindow();
}