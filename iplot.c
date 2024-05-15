#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

double f(double x) {
    return (double)SCREEN_HEIGHT/(double)SCREEN_WIDTH * x;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "iplot");
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    camera.offset.x = SCREEN_WIDTH/2;
    camera.offset.y = SCREEN_HEIGHT/2;
    camera.target.x = 0.0f;
    camera.target.y = 0.0f;

    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mouse_pos = GetMousePosition();
        Vector2 mouse_world_pos = GetScreenToWorld2D(mouse_pos, camera);
        // printf("mouse_pos: %f %f mouse_world_pos: %f %f\n", mouse_pos.x, mouse_pos.y, mouse_world_pos.x, mouse_world_pos.y);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse_delta = GetMouseDelta();
            camera.target = Vector2Add(camera.target, Vector2Scale(mouse_delta, -1.0f));
        }
        printf("camera.target: %f %f\n", camera.target.x, camera.target.y);

        // Vector2 delta = GetMouseDelta();
        // printf("%f %f\n", delta.x, delta.y);

        BeginMode2D(camera);
        {
            // draw x axis
            Vector2 p0 = { -SCREEN_WIDTH/2, 0.0 };
            p0.x = p0.x + camera.target.x;
            Vector2 p1 = { SCREEN_WIDTH/2, 0.0 };
            p1.x = p1.x + camera.target.x;
            DrawLine(p0.x, p0.y, p1.x, p1.y, BLACK);
        }

        {
            // draw y axis
            Vector2 p0 = { 0.0, SCREEN_HEIGHT/2 };
            p0.y = p0.y + camera.target.y;
            Vector2 p1 = { 0.0, -SCREEN_HEIGHT/2 };
            p1.y = p1.y + camera.target.y;
            DrawLine(p0.x, p0.y, p1.x, p1.y, BLACK);
        }

        {
            // draw function
            double x0 = 0.0;
            double y0 = f(x0);
            double x1 = SCREEN_WIDTH;
            double y1 = f(x1);
            DrawLine(x0, y0, x1, y1, BLACK);
        }
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
