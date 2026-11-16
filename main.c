#include "raylib.h"

int main(void)
{
    const int screenWidth = 960;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "Mini Balatro - First Window");
    SetTargetFPS(60);

    // 游戏主循环：处理输入、更新状态、绘制画面。
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color){ 25, 65, 48, 255 });

        // raylib 默认字体支持英文；中文显示需要另外加载字体。
        DrawText("Mini Balatro", 60, 60, 48, RAYWHITE);
        DrawText("raylib is ready!", 60, 130, 24, GOLD);
        DrawText("Next step: create a deck of 52 cards.", 60, 180, 22, RAYWHITE);
        DrawText("Press ESC to close.", 60, 560, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
