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
  int windowDimensions[2];
  windowDimensions[0] = 512;
  windowDimensions[1] = 380;

  InitWindow(windowDimensions[0], windowDimensions[1], "2D Runner");

  // Ilayda variables
  Texture2D ilayda = LoadTexture("textures/scarfy.png");
  AnimData ilaydaData;
  ilaydaData.rec.width = ilayda.width / 6;
  ilaydaData.rec.height = ilayda.height;
  ilaydaData.rec.x = 0;
  ilaydaData.rec.y = 0;
  ilaydaData.pos.x = windowDimensions[0] / 2 - (ilaydaData.rec.width / 2);
  ilaydaData.pos.y = windowDimensions[1] - ilaydaData.rec.height;
  ilaydaData.frame = 0;
  ilaydaData.updateTime = 1.0 / 12.0;
  ilaydaData.runningTime = 0.0;

  // Nebula variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  AnimData nebulas[3]{};

  for (int i = 0; i < 3; i++)
  {
    nebulas[i].rec.x = 0.0;
    nebulas[i].rec.y = 0.0;
    nebulas[i].rec.width = (float)nebula.width / 8;
    nebulas[i].rec.height = (float)nebula.height / 8;
    nebulas[i].pos.y = (float)windowDimensions[1] - nebula.height / 8;
    nebulas[i].frame = 0;
    nebulas[i].runningTime = 0.0;
    nebulas[i].updateTime = 1.0 / 16.0;
  }

  nebulas[0].pos.x = (float)windowDimensions[0];
  nebulas[1].pos.x = (float)windowDimensions[0] + 300;
  nebulas[2].pos.x = (float)windowDimensions[0] + 600;

  const int gravity = 1'000; //(1000)
  int velocity = 0;
  const int jumpVelocity = -600;
  int nebulaVel = -200;
  bool isInAir;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    const float dT = GetFrameTime();

    if (ilaydaData.pos.y > windowDimensions[1] - ilaydaData.rec.height)
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
    nebulas[0].pos.x += nebulaVel * dT;

    // Update second nebula pos
    nebulas[1].pos.x += nebulaVel * dT;

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
    nebulas[0].runningTime += dT;
    if (nebulas[0].runningTime >= nebulas[0].updateTime)
    {
      nebulas[0].runningTime = 0.0;
      nebulas[0].rec.x = nebulas[0].frame * nebulas[0].rec.width;
      nebulas[0].frame++;
      if (nebulas[0].frame > 7)
      {
        nebulas[0].frame = 0;
      }
    }

    nebulas[1].runningTime += dT;
    if (nebulas[1].runningTime >= nebulas[1].updateTime)
    {
      nebulas[1].runningTime = 0.0;
      nebulas[1].rec.x = nebulas[1].frame * nebulas[1].rec.width;
      nebulas[1].frame++;
      if (nebulas[1].frame > 7)
      {
        nebulas[1].frame = 0;
      }
    }

    DrawTextureRec(ilayda, ilaydaData.rec, ilaydaData.pos, WHITE);
    DrawTextureRec(nebula, nebulas[0].rec, nebulas[0].pos, WHITE);
    DrawTextureRec(nebula, nebulas[1].rec, nebulas[1].pos, RED);

    EndDrawing();
  }
  UnloadTexture(ilayda);
  UnloadTexture(nebula);
  CloseWindow();
}