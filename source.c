#include "raylib.h"
#include <math.h>

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib");
    
    SetTargetFPS(60);
    SetExitKey(0);

    // Initialize the camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 30.0f, 20.0f, 30.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 70.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    while (!WindowShouldClose())
    {

        double time = GetTime();

        // (don't) Move camera around the scene
        double cameraTime = time*0.3;
        //camera.position.x = (float)cos(cameraTime)*40.0f;
        //camera.position.z = (float)sin(cameraTime)*40.0f;

      BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);

      // https://www.raylib.com/examples.html "Waving cubes"
      DrawGrid(10, 5.0f);
      int size = 4;
      DrawCube((Vector3){0,2,0}, size,size,size, BLACK);

      EndMode3D();
      DrawFPS(10, 10);

      EndDrawing();
    }

    CloseWindow();
    return 0;
}
