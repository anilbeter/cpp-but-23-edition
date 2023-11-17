#include "raylib.h"

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main()
{
  const int windowWidth = 512;
  const int windowHeight = 380;
  InitWindow(windowWidth, windowHeight, "2D Runner");

  const int gravity = 1'000; //(1000)

  // Ilayda variables
  Texture2D ilayda = LoadTexture("textures/scarfy.png");
  AnimData ilaydaData;
  ilaydaData.rec.width = ilayda.width / 6;
  ilaydaData.rec.height = ilayda.height;
  ilaydaData.rec.x = 0;
  ilaydaData.rec.y = 0;
  ilaydaData.pos.x = windowWidth / 2 - (ilaydaData.rec.width / 2);
  ilaydaData.pos.y = windowHeight - ilaydaData.rec.height;
  ilaydaData.frame = 0;
  ilaydaData.updateTime = 1.0 / 12.0;
  ilaydaData.runningTime = 0.0;

  // Rectangle ilaydaRec;
  // ilaydaRec.width = ilayda.width / 6;
  // ilaydaRec.height = ilayda.height;
  // ilaydaRec.x = 0;
  // ilaydaRec.y = 0;
  // Vector2 ilaydaPos;
  // ilaydaPos.x = windowWidth / 2 - (ilaydaRec.width / 2);
  // ilaydaPos.y = windowHeight - ilaydaRec.height;

  // Nebula variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  // AnimData for nebula
  AnimData nebData{
      {0, 0, (float)nebula.width / 8, (float)nebula.height / 8},
      {windowWidth, windowHeight - nebula.height / 8},
      0,
      1.0 / 12.0,
      0};

  // AnimData for 2nd nebula
  AnimData neb2Data{{0, 0, (float)nebula.width / 8, (float)nebula.height / 8}, {windowWidth + 500, windowHeight - nebula.height / 8}, 0, 1.0 / 16.0, 0};

  int nebulaVel = -200;

  int velocity = 0;
  bool isInAir;
  const int jumpVelocity = -600;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    const float dT = GetFrameTime();

    if (ilaydaData.pos.y > windowHeight - ilaydaData.rec.height)
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

    // Update Ilayda position
    ilaydaData.pos.y += velocity * dT;

    // Update Nebula position
    nebData.pos.x += nebulaVel * dT;

    // Update second nebula pos
    neb2Data.pos.x += nebulaVel * dT;

    // Ilayda animation
    if (!isInAir)
    {
      ilaydaData.runningTime += dT;
      if (ilaydaData.runningTime >= ilaydaData.updateTime)
      {
        ilaydaData.runningTime = 0.0;

        ilaydaData.rec.x = ilaydaData.frame * ilaydaData.rec.width;
        ilaydaData.frame++;
        if (ilaydaData.frame > 5)
        {
          ilaydaData.frame = 0;
        }
      }
    }

    // Nebula animation
    nebData.runningTime += dT;
    if (nebData.runningTime >= nebData.updateTime)
    {
      nebData.runningTime = 0.0;
      nebData.rec.x = nebData.frame * nebData.rec.width;
      nebData.frame++;
      if (nebData.frame > 7)
      {
        nebData.frame = 0;
      }
    }

    neb2Data.runningTime += dT;
    if (neb2Data.runningTime >= neb2Data.updateTime)
    {
      neb2Data.runningTime = 0.0;
      neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
      neb2Data.frame++;
      if (neb2Data.frame > 7)
      {
        neb2Data.frame = 0;
      }
    }

    DrawTextureRec(ilayda, ilaydaData.rec, ilaydaData.pos, WHITE);
    DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
    DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

    EndDrawing();
  }
  UnloadTexture(ilayda);
  UnloadTexture(nebula);
  CloseWindow();
}