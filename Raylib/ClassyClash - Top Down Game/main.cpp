#include "raylib.h"
#include "raymath.h"

class Character
{
public:
  Vector2 getWorldPos() { return worldPos; }
  void setScreenPos(int winWidth, int winHeight);
  void tick(float deltaTime);

private:
  Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
  Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
  Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
  Vector2 screenPos;
  Vector2 worldPos;
  float rightLeft = 1.f;
  float runningTime;
  int frame;
  const int maxFrames = 6;
  const float updateTime = 1.0f / 12.0f;
  const float speed = 4.f;
};

void Character::setScreenPos(int winWidth, int winHeight)
{
  screenPos = {
      (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
      (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
};

void Character::tick(float deltaTime)
{
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
    // set worldPos = worldPos + direction

    worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
    direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    texture = run;
  }
  else
  {
    texture = idle;
  }

  // update animation frame
  runningTime += deltaTime;
  if (runningTime >= updateTime)
  {
    frame++;
    runningTime = 0.f;
    if (frame > maxFrames)
      frame = 0;
  }
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

      mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
      direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
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
    Rectangle source{frame * (float)knight.width / 6.f, 0.f, rightLeft * (float)knight.width / 6.f, (float)knight.height};
    Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
    DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

    EndDrawing();
  }
  CloseWindow();
}
