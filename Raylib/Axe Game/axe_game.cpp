// Include raylib library
#include "raylib.h"

int main()
{
  int width = 800;
  int height = 450;
  InitWindow(width, height, "Another Life");

  int circle_x = 200;
  int circle_y = 200;
  int circle_radius = 25;
  int axe_x = 400;
  int axe_y = 0;
  int axe_length = 50;
  int direction = 10;

  // circle edges
  int l_circle_x = circle_x - circle_radius;
  int r_circle_x = circle_x + circle_radius;
  int u_circle_y = circle_y - circle_radius;
  int b_circle_y = circle_y + circle_radius;

  // axe edges
  int l_axe_x = axe_x;
  int r_axe_x = axe_x + axe_length;
  int u_axe_y = axe_y;
  int b_axe_y = axe_y + axe_length;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Game logic begins
    DrawCircle(circle_x, circle_y, circle_radius, BLUE);
    DrawRectangle(axe_x - 25, axe_y, axe_length, axe_length, RED);

    axe_y += direction;
    if (axe_y > height - 50 || axe_y < 0)
    {
      direction = -direction;
    }

    if (IsKeyDown(KEY_D) && circle_x < 775)
    {
      circle_x += 10;
    }

    if (IsKeyDown(KEY_A) && circle_x > 25)
    {
      circle_x -= 10;
    }

    // Game logic ends
    EndDrawing();
  }
}