#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <errno.h>
#include "raylib.h"
#include "mnwolfSerial.h"
#include "colorsheet.h"

using namespace std;

const bool debug = true;
void dPrint(string strPrint);
void dPrintln(string strPrint);

int main()
{
    int screenWidth = 1280;
    int screenHeight = 800;

    bool serConn = initSerial();
    if (serConn)
        dPrintln("Serial connected.");
    else
        dPrintln("Serial connection error.\n\r");

    txSerial("Hello!\n\r");

    Shader sh;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    MaximizeWindow();
    HideCursor();

    SetTargetFPS(60);
    sh = LoadShader(0, "resources/shaders/glsl100/bloom.fs");
    Font font = LoadFont("resources/fonts/BlenderPro-Heavy.ttf");

    /*unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData("resources/fonts/BlenderPro-Heavy.ttf", &fileSize);

    Font font = {0};
    font.baseSize = 16;
    font.charsCount = 95;
    font.chars = LoadFontData(fileData, fileSize, 16, 0, 0, FONT_SDF);
    Image atlas = GenImageFontAtlas(font.chars, &font.recs, 95, 16, 0, 1);
    font.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);
    UnloadFileData(fileData);*/

    RenderTexture2D tgt = LoadRenderTexture(screenWidth, screenHeight);
    GenTextureMipmaps(&font.texture);
    SetTextureFilter(font.texture, FILTER_BILINEAR);
    //SetTextureFilter(tgt.texture, FILTER_BILINEAR);

    while(!WindowShouldClose() && !updateSerial())
    {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginTextureMode(tgt);
    ClearBackground(BLACK);
    DrawTextEx(font, "MENU", (Vector2){27.0f, 15.0f}, 30, 2, UI_LINE_LGT);
    DrawTextEx(font, "SYSTEM", (Vector2){4.0f, 52.0f}, 20, 1, UI_LINE_LGT);

    DrawRectangleRoundedLines((Rectangle){6,12,114,34}, 0.2f, 0, UI_LINE_THIN, UI_BOX);
    DrawLineEx((Vector2){0,51},(Vector2){170,51},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){170,51},(Vector2){184,62},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){184,62},(Vector2){184,72},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){0,72},(Vector2){1280,72},UI_LINE_THICK,UI_LINE_LGT);

    EndTextureMode();

    //BeginShaderMode(sh);
    DrawTextureRec(tgt.texture, (Rectangle){0, 0, tgt.texture.width, -tgt.texture.height}, (Vector2){0, 0}, WHITE);
    //EndShaderMode();
    DrawFPS(10,10);

    EndDrawing();
    }
    TakeScreenshot("./FilterOnlyBlack.png");
    //sleep(10);
    UnloadRenderTexture(tgt);

    CloseWindow();

    txSerial("Goodbye!\n\r");
    dPrint("Received: ");
    dPrintln(parseSerial());

    if (closeSerial())
        dPrintln("Serial closed.");
    else
        dPrintln("Error closing serial.");


    return 1;
}

void dPrint(string strPrint) {
    if (debug)
        printf((char*)strPrint.c_str());
}

void dPrintln(string strPrint) {
    if (debug)
        printf("%s%c%c",strPrint.c_str(),'\n','\r');
}
