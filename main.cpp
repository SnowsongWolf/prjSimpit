#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <errno.h>
#include "raylib.h"

using namespace std;

int uart0_filestream = -1;
int uart_tx_string(string tx_string);

int main()
{
    int screenWidth = 1280;
    int screenHeight = 800;

    Shader sh;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    MaximizeWindow();

    SetTargetFPS(60);
    sh = LoadShader(0, "resources/shaders/glsl120/bloom.fs");
    Font font = LoadFont("resources/fonts/BlenderPro-Heavy.ttf");

    RenderTexture2D tgt = LoadRenderTexture(screenWidth, screenHeight);
    GenTextureMipmaps(&font.texture);
    SetTextureFilter(font.texture, FILTER_BILINEAR);
    SetTextureFilter(tgt.texture, FILTER_BILINEAR);

    BeginDrawing();
    ClearBackground(BLACK);
    BeginTextureMode(tgt);
    ClearBackground(BLACK);
    DrawTextEx(font, "MENU", (Vector2){15.0f, 106.0f}, 20, 2, (Color){118,182,216,255});
    DrawTextEx(font, "SYSTEM", (Vector2){5.0f, 131.0f}, 13, 1, (Color){118,182,216,255});

    DrawRectangleRoundedLines((Rectangle){3,105,72,21}, 0.2f, 0, 2, (Color){65,127,181,255});
    DrawLineEx((Vector2){0,130},(Vector2){104,130},2.0f,(Color){118,182,216,255});
    DrawLineEx((Vector2){115,137},(Vector2){104,130},2.0f,(Color){118,182,216,255});
    DrawLineEx((Vector2){115,137},(Vector2){115,143},2.0f,(Color){118,182,216,255});
    DrawLineEx((Vector2){0,143},(Vector2){1280,143},2.0f,(Color){118,182,216,255});

    EndTextureMode();

    BeginShaderMode(sh);
    DrawTextureRec(tgt.texture, (Rectangle){0, 0, tgt.texture.width, -tgt.texture.height}, (Vector2){0, 0}, WHITE);
    EndShaderMode();

    //DrawText("Congrats! You created your first window!", 190, 200, 20, SKYBLUE);

    EndDrawing();

    sleep(10);
    UnloadRenderTexture(tgt);
    CloseWindow();

    return 1;
}

int uart_tx_string(string tx_string) {
    if (uart0_filestream == -1)
        return 0;

    write(uart0_filestream, (char*)tx_string.c_str(), tx_string.length());
    return 1;
}
