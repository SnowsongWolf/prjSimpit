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
    //Font font = LoadFont("resources/fonts/BlenderPro-Heavy.ttf");
    //Font font2 = LoadFont("resources/pixantiqua.ttf");

    unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData("resources/fonts/BlenderPro-Heavy.ttf", &fileSize);

    Font font = {0};
    font.baseSize = 100;
    font.charsCount = 95;
    font.chars = LoadFontData(fileData, fileSize, 100, 0, 0, FONT_DEFAULT);
    Image atlas = GenImageFontAtlas(font.chars, &font.recs, 95, 100, 0, 1);
    font.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);
    UnloadFileData(fileData);

    RenderTexture2D tgt = LoadRenderTexture(screenWidth, screenHeight);
    GenTextureMipmaps(&font.texture);
    //SetTextureFilter(font.texture, FILTER_BILINEAR);
    //SetTextureFilter(font2.texture, FILTER_BILINEAR);
    //SetTextureFilter(tgt.texture, FILTER_BILINEAR);

    while(!WindowShouldClose() && !updateSerial())
    {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginTextureMode(tgt);
    ClearBackground(BLACK);
    DrawTextEx(font, "MENU", (Vector2){27.0f, 15.0f}, 30, 2, UI_LINE_LGT);
    DrawTextEx(font, "SYSTEM", (Vector2){4.0f, 52.0f}, 20, 1, UI_LINE_LGT);
    DrawTextEx(font, "ITEMS", (Vector2){198.0f, 52.0f}, 20, 1, UI_LINE_LGT);
    DrawTextEx(font, "USAGE", (Vector2){63.0f, 112.0f}, 28, 0, UI_LINE_LGT);
    DrawTextEx(font, "REQUIRED", (Vector2){62.0f, 167.0f}, 18, 0, UI_LINE_LGT);

    DrawRectangleRoundedLines((Rectangle){6,12,114,34}, 0.2f, 0, UI_LINE_THIN, UI_BOX);

    DrawLineEx((Vector2){184,72},(Vector2){184,53},UI_LINE_THIN,UI_LINE_DRK);
    DrawLineEx((Vector2){187,50},(Vector2){184,53},UI_LINE_THIN,UI_LINE_DRK);
    DrawLineEx((Vector2){184,50},(Vector2){360,50},UI_LINE_THIN,UI_LINE_DRK);
    DrawLineEx((Vector2){374,61},(Vector2){360,50},UI_LINE_THIN,UI_LINE_DRK);
    DrawLineEx((Vector2){374,61},(Vector2){374,72},UI_LINE_THIN,UI_LINE_DRK);

    DrawLineEx((Vector2){0,51},(Vector2){170,51},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){170,51},(Vector2){184,62},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){184,62},(Vector2){184,72},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){0,72},(Vector2){1280,72},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){0,7},(Vector2){1280,7},UI_LINE_THIN,UI_LINE_DRK);

    DrawRectangleV((Vector2){162,101},(Vector2){892,9},UI_BOX_DRK);
    DrawRectangleV((Vector2){162,115},(Vector2){668,26},UI_BOX_DRK);
    DrawRectangleV((Vector2){162,175},(Vector2){633,8},UI_LINE_LGT);
    for (int x = 263; x < 974; x += 100) {
        DrawLineEx((Vector2){x,109},(Vector2){x,147},UI_LINE_THIN,UI_BOX);
    }
    for (int x = 183; x < 1041; x += 20) {
        DrawLineEx((Vector2){x,115},(Vector2){x,141},UI_LINE_THIN,UI_BOX_LGT);
    }
    DrawLineEx((Vector2){162,115},(Vector2){162,141},UI_LINE_THIN,UI_LINE_LGT);
    DrawLineEx((Vector2){162,147},(Vector2){1054,147},UI_LINE_THIN,UI_BOX_DRK);
    DrawLineEx((Vector2){162,169},(Vector2){1054,169},UI_LINE_THIN,UI_BOX_DRK);
    DrawLineEx((Vector2){162,187},(Vector2){1054,187},UI_LINE_THIN,UI_BOX_DRK);
    DrawLineEx((Vector2){795,169},(Vector2){795,187},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){162+668,115},(Vector2){162+668,115+26},UI_LINE_THICK,UI_LINE_LGT);
    DrawLineEx((Vector2){1054,101-16},(Vector2){1054,187},UI_LINE_THICK,UI_LINE_LGT);

    DrawLineEx((Vector2){162,151},(Vector2){162,163},UI_LINE_THIN,UI_RED_DRK);
    DrawLineEx((Vector2){162,163},(Vector2){1054,163},UI_LINE_THIN,UI_RED_DRK);
    DrawLineEx((Vector2){791,151},(Vector2){791,163},UI_LINE_THICK,UI_RED);
    DrawLineEx((Vector2){791,157},(Vector2){810,151},UI_LINE_THICK,UI_RED);
    DrawLineEx((Vector2){791,157},(Vector2){810,163},UI_LINE_THICK,UI_RED);
    DrawLineEx((Vector2){810,151},(Vector2){810,163},UI_LINE_THICK,UI_RED);

    DrawTextEx(font, "0.76", (Vector2){848.0f, 110.0f}, 36, 0, UI_LINE_LGT);

    DrawRectangleRoundedLines((Rectangle){200,200,100,50}, 0.2f, 0, UI_LINE_THIN, UI_RED);

    EndTextureMode();

    //BeginShaderMode(sh);
    DrawTextureRec(tgt.texture, (Rectangle){0, 0, tgt.texture.width, -tgt.texture.height}, (Vector2){0, 0}, WHITE);
    //EndShaderMode();
    DrawFPS(10,10);

    EndDrawing();
    }
    TakeScreenshot("./TextTest2.png");
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
