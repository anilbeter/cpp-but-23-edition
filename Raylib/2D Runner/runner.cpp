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

  Rectangle ilaydaRec;
  ilaydaRec.width = ilayda.width / 6;
  ilaydaRec.height = ilayda.height;
  ilaydaRec.x = 0;
  ilaydaRec.y = 0;
  Vector2 ilaydaPos;
  ilaydaPos.x = windowWidth / 2 - (ilaydaRec.width / 2);
  ilaydaPos.y = windowHeight - ilaydaRec.height;

  // Nebula variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  // AnimData for nebula
  AnimData nebData{
      {0, 0, (float)nebula.width / 8, (float)nebula.height / 8},
      {windowWidth, windowHeight - nebula.height / 8},
      0,
      1.0 / 12.0,
      0};

  // x, y, width, height
  Rectangle nebulaRec = {0, 0, (float)nebula.width / 8, (float)nebula.height / 8};
  // x, y
  Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};

  Rectangle neb2Rec{0, 0, (float)nebula.width / 8, (float)nebula.height / 8};
  Vector2 neb2Pos{windowWidth + 500, windowHeight - nebulaRec.height};

  int nebulaVel = -200;

  int velocity = 0;
  bool isInAir;
  const int jumpVelocity = -600;

  int frame;
  const float updateTime = 1.0 / 12.0;
  float runningTime;

  int nebFrame;
  const float nebUpdateTime = 1.0 / 12.0;
  float nebRunningTime;

  int neb2Frame;
  const float neb2UpdateTime = 1.0 / 16.0;
  float neb2RunningTime;

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

    // Update Ilayda position
    ilaydaPos.y += velocity * dT;

    // Update Nebula position
    nebulaPos.x += nebulaVel * dT;

    // Update second nebula pos
    neb2Pos.x += nebulaVel * dT;

    // Ilayda animation
    if (!isInAir)
    {
      runningTime += dT;
      if (runningTime >= updateTime)
      {
        runningTime = 0.0;

        ilaydaRec.x = frame * ilaydaRec.width;
        frame++;
        if (frame > 5)
        {
          frame = 0;
        }
      }
    }

    // Nebula animation
    nebRunningTime += dT;
    if (nebRunningTime >= nebUpdateTime)
    {
      nebRunningTime = 0.0;
      nebulaRec.x = nebFrame * nebulaRec.width;
      nebFrame++;
      if (nebFrame > 7)
      {
        nebFrame = 0;
      }
    }

    neb2RunningTime += dT;
    if (neb2RunningTime >= neb2UpdateTime)
    {
      neb2RunningTime = 0.0;
      neb2Rec.x = neb2Frame * neb2Rec.width;
      neb2Frame++;
      if (neb2Frame > 7)
      {
        neb2Frame = 0;
      }
    }

    DrawTextureRec(ilayda, ilaydaRec, ilaydaPos, WHITE);
    DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
    DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

    EndDrawing();
  }
  UnloadTexture(ilayda);
  UnloadTexture(nebula);
  CloseWindow();
}