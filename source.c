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
    camera.projection = CAMERA_PERSPECTIVE;

    // Specify the amount of blocks in each direction
    const int numBlocks = 15;

    while (!WindowShouldClose())
    {

        double time = GetTime();

        // Calculate time scale for cube position and size
        float scale = (2.0f + (float)sin(time))*0.7f;

        // Move camera around the scene
        double cameraTime = time*0.3;
        camera.position.x = (float)cos(cameraTime)*40.0f;
        camera.position.z = (float)sin(cameraTime)*40.0f;

      BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);

      // https://www.raylib.com/examples.html "Waving cubes"
      DrawGrid(10, 5.0f);

      for (int x = 0; x < numBlocks; x++)
      {
        for (int y = 0; y < numBlocks; y++)
        {
          for (int z = 0; z < numBlocks; z++)
          {
            // Scale of the blocks depends on x/y/z positions
            float blockScale = (x + y + z)/30.0f;

            // Scatter makes the waving effect by adding blockScale over time
            float scatter = sinf(blockScale*20.0f + (float)(time*4.0f));

            // Calculate the cube position
            Vector3 cubePos = {
              (float)(x - numBlocks/2)*(scale*3.0f) + scatter,
              (float)(y - numBlocks/2)*(scale*2.0f) + scatter,
              (float)(z - numBlocks/2)*(scale*3.0f) + scatter
            };

            // Pick a color with a hue depending on cube position for the rainbow color effect
            Color cubeColor = ColorFromHSV((float)(((x + y + z)*18)%360), 0.75f, 0.9f);

            // Calculate cube size
            float cubeSize = (2.4f - scale)*blockScale;

            // And finally, draw the cube!
            DrawCube(cubePos, cubeSize, cubeSize, cubeSize, cubeColor);
          }
        }
      }

      EndMode3D();
      DrawFPS(10, 10);

      EndDrawing();
    }

    CloseWindow();
    return 0;
}
