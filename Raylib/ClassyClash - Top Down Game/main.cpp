#include "raylib.h"
#include "raymath.h"

class Character
{
public:
private:
};

int main()
{
  int windowDimensions[2]{384, 384};
  InitWindow(windowDimensions[0], windowDimensions[1], "Top Down Game");

  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0};
  float speed = 4.0;

  Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
  Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
  Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
  Vector2 knightPos{
      (float)windowDimensions[0] / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
      (float)windowDimensions[1] / 2.0f - 4.0f * (0.5f * (float)knight.height)};

  // 1 -> right, -1 -> left
  float rightLeft = 1.f;

  // animation variables
  float runningTime;
  int frame;
  const int maxFrames = 6;
  const float updateTime = 1.0f / 12.0f;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    Vector2 direction;
    if (IsKeyDown(KEY_A))
      direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
      direction.x += 1.0;
    if (IsKeyDown(KEY_W))
      direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
      direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
      // set mapPos = mapPos - direction

      Vector2 scaledVector = Vector2Scale(Vector2Normalize(direction), speed);
      mapPos = Vector2Subtract(mapPos, scaledVector);
      direction.x < 0.f ? rightLeft = -1.0f : rightLeft = 1.0f;
      knight = knightRun;
    }
    else
    {
      knight = knightIdle;
    }

    // draw the map
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    // update animation frame
    runningTime += GetFrameTime();
    if (runningTime >= updateTime)
    {
      frame++;
      runningTime = 0.f;
      if (frame > maxFrames)
        frame = 0;
    }

    // draw the character
    Rectangle source{knight.width / 6.f * frame, 0.f, rightLeft * knight.width / 6.f, (float)knight.height};
    Rectangle dest{knightPos.x, knightPos.y, 4.0f * knight.width / 6.0f, 4.0f * knight.height};
    DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

    EndDrawing();
  }
  UnloadTexture(map);
  CloseWindow();
}