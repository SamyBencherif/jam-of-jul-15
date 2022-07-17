#include "raylib.h"
#include <math.h>

Color light(Color src, float index)
{
  // index=+1 : returns src slightly lighter
  // index= 0 : returns src
  // index=-1 : returns src slightly darker

  Color blackpoint = {23, 20, 31, 255};
  Color whitepoint = {214, 242, 237, 255};

  Vector3 blk_hsv = ColorToHSV(blackpoint);
  Vector3 wht_hsv = ColorToHSV(whitepoint);

  Vector3 src_hsv = ColorToHSV(src);

  float gradations = .1;
  int compFunction(int a, int b, int w)
  {
    if (index == 0)
      return a;
    else if (index > 0)
      return a+(w-a)*gradations*index;
    else
      return a+(b-a)*gradations*(-index);
  }

  Vector3 comp_hsv;
  comp_hsv.x = compFunction(src_hsv.x, blk_hsv.x, wht_hsv.x);
  comp_hsv.y = compFunction(src_hsv.y, blk_hsv.y, wht_hsv.y);
  comp_hsv.z = compFunction(src_hsv.z, blk_hsv.z, wht_hsv.z);

  return ColorFromHSV(comp_hsv.x, comp_hsv.y, comp_hsv.z);
}

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib");
    
    SetTargetFPS(10);
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
      Color beige = (Color){190, 162, 113, 255};
      Vector3 s = (Vector3){1,3,10};

      // this should draw three shades of beige cubes
      // but it calls to `light` are currenlty just returning black
      Vector3 pos = (Vector3){0,2,0};
      DrawCube(pos, 4*s.x, 4*s.y, 4*s.z, light(beige, -1));

      pos = (Vector3){4,2,0};
      DrawCube(pos, 4*s.x, 4*s.y, 4*s.z, beige);

      pos = (Vector3){8,2,0};
      DrawCube(pos, 4*s.x, 4*s.y, 4*s.z, light(beige, 1));

      EndMode3D();
      DrawFPS(10, 10);

      EndDrawing();
    }

    CloseWindow();
    return 0;
}
