#include "raylib.h"

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
  return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
  data.runningTime += deltaTime;
  if (data.runningTime >= data.updateTime)
  {
    data.runningTime = 0.0;
    data.rec.x = data.frame * data.rec.width;
    data.frame++;
    if (data.frame > maxFrame)
    {
      data.frame = 0;
    }
  }
  return data;
}

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

  const int sizeOfNebula = 6;
  AnimData nebulas[sizeOfNebula]{};

  for (int i = 0; i < sizeOfNebula; i++)
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

  int constantRange = 300;
  for (int i = 0; i < sizeOfNebula; i++)
  {
    nebulas[i].pos.x = windowDimensions[0] + constantRange * i;
  }

  float finishLine{nebulas[sizeOfNebula - 1].pos.x};

  const int gravity = 1'000; //(1000)
  int velocity = 0;
  const int jumpVelocity = -600;
  int nebulaVel = -200;
  bool isInAir;

  Texture2D background = LoadTexture("textures/far-buildings.png");
  float bgX{};

  Texture2D midground = LoadTexture("textures/back-buildings.png");
  float mgX{};

  Texture2D foreground = LoadTexture("textures/foreground.png");
  float fgX{};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    const float dT = GetFrameTime();
    BeginDrawing();
    ClearBackground(WHITE);

    bgX -= 20 * dT;
    if (bgX <= -background.width * 2)
    {
      bgX = 0.0;
    }

    mgX -= 40 * dT;
    if (mgX <= -midground.width * 2)
    {
      mgX = 0;
    }

    fgX -= 80 * dT;
    if (fgX <= -foreground.width * 2)
    {
      fgX = 0;
    }

    Vector2 bg1Pos{bgX, 0.0};
    DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
    Vector2 bg2Pos{bgX + background.width * 2, 0.0};
    DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

    Vector2 mg1Pos{mgX, 0.0};
    DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
    Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
    DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

    Vector2 fg1Pos{fgX, 0.0};
    DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
    Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
    DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

    if (isOnGround(ilaydaData, windowDimensions[1]))
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

    for (int i = 0; i < sizeOfNebula; i++)
    {
      nebulas[i].pos.x += nebulaVel * dT;
    }

    // Update finish line
    finishLine += nebulaVel * dT;

    // Ilayda animation
    if (!isInAir)
    {
      ilaydaData = updateAnimData(ilaydaData, dT, 5);
    }

    for (int i = 0; i < sizeOfNebula; i++)
    {
      nebulas[i] = updateAnimData(nebulas[i], dT, 7);
    }

    bool collision;
    // Range based for loop
    for (AnimData neb : nebulas)
    {
      float padding = 50;
      Rectangle nebRec{
          neb.pos.x + padding,
          neb.pos.y + padding,
          neb.rec.width - 2 * padding,
          neb.rec.height - 2 * padding};
      Rectangle ilaydaRec{
          ilaydaData.pos.x,
          ilaydaData.pos.y,
          ilaydaData.rec.width,
          ilaydaData.rec.height};
      if (CheckCollisionRecs(nebRec, ilaydaRec))
      {
        collision = true;
      }
    }

    if (collision)
    {
      // GAME OVER
    }
    else
    {
      DrawTextureRec(ilayda, ilaydaData.rec, ilaydaData.pos, WHITE);

      for (int i = 0; i < sizeOfNebula; i++)
      {
        DrawTextureRec(nebula, nebulas[i].rec, nebulas[i].pos, WHITE);
      }
    }

    EndDrawing();
  }
  UnloadTexture(ilayda);
  UnloadTexture(nebula);
  UnloadTexture(background);
  UnloadTexture(midground);
  UnloadTexture(foreground);
  CloseWindow();
}