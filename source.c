#include "raylib.h"

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib");
    
    SetTargetFPS(60);
    SetExitKey(0);

    while (!WindowShouldClose())
    {
      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawText("Congrats! You created a window!", 190, 200, 20, LIGHTGRAY);
      EndDrawing();
    }

    CloseWindow();
    return 0;
}
