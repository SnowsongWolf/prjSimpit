#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <errno.h>
#include "raylib.h"
#include "mnwolfSerial.h"
#include "colorsheet.h"
#include "ui.h"

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

    //Shader sh;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    MaximizeWindow();
    HideCursor();

    SetTargetFPS(60);
    //sh = LoadShader(0, "resources/shaders/glsl100/bloom.fs");
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

    //RenderTexture2D tgt = LoadRenderTexture(screenWidth, screenHeight);
    GenTextureMipmaps(&font.texture);
    //SetTextureFilter(font.texture, FILTER_BILINEAR);
    //SetTextureFilter(font2.texture, FILTER_BILINEAR);
    //SetTextureFilter(tgt.texture, FILTER_BILINEAR);

    while(!WindowShouldClose() && !updateSerial())
    {
    BeginDrawing();
    ClearBackground(BLACK);
    //BeginTextureMode(tgt);

    DrawRectangleLines(99,99,602,602,UI_LINE);      // Display area
    Rectangle dArea = (Rectangle){100,100,600,600};
    Padding pfont = (Padding){2,0,-6,-6};
    //textAlign(font, "TOP LEFT", dArea, 50, 0, UI_BOX_LGT, pfont, A_LEFT, V_TOP);
    //textAlign(font, "CENTER", dArea, 50, 0, UI_BOX_LGT, pfont, A_CENTER, V_CENTER);
    //textAlign(font, "BOTTOM RIGHT", dArea, 50, 0, UI_BOX_LGT, pfont, A_RIGHT, V_BOTTOM);

    // MFD top row buttons
    DrawRectangleRoundedLines((Rectangle){184,18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "1", (Rectangle){184,18,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){277,18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "2", (Rectangle){277,18,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){370,18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "3", (Rectangle){370,18,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){464,18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "4", (Rectangle){464,18,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){556,18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "5", (Rectangle){556,18,59,59}, 50, 0, UI_GREEN_LGT, pfont);

    /*char ch_x[3];
    for (int x = 1; x < 6; x++)
    {
        sprintf(ch_x,"%d",x);
        DrawTextEx(font, ch_x,(Vector2){198 + (x - 1) * 93, 18}, 59, 0, UI_GREEN_LGT);
    }*/

    //MFD left row buttons
    DrawRectangleRoundedLines((Rectangle){18,200,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "20", (Rectangle){18,200,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){18,285,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "19", (Rectangle){18,285,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){18,371,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "18", (Rectangle){18,371,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){18,456,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "17", (Rectangle){18,456,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){18,542,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "16", (Rectangle){18,542,59,59}, 50, 0, UI_GREEN_LGT, pfont);

    /*for (int x = 16; x < 21; x++)
    {
        sprintf(ch_x,"%i",x);
        DrawTextEx(font, ch_x,(Vector2){16, 542 - (x - 16) * 85}, 59, 0, UI_GREEN_LGT);
    }*/

    //MFD bottom column buttons
    DrawRectangleRoundedLines((Rectangle){184,723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "11", (Rectangle){184,723,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){277,723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "12", (Rectangle){277,723,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){370,723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "13", (Rectangle){370,723,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){464,723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "14", (Rectangle){464,723,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){556,723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "15", (Rectangle){556,723,59,59}, 50, 0, UI_GREEN_LGT, pfont);

    /*for (int x = 11; x < 16; x++)
    {
        sprintf(ch_x,"%i",x);
        DrawTextEx(font, ch_x,(Vector2){554 - (x - 11) * 93, 723}, 59, 0, UI_GREEN_LGT);
    }*/

    //MFD right column buttons
    DrawRectangleRoundedLines((Rectangle){722,200,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "6", (Rectangle){722,200,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){722,285,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "7", (Rectangle){722,285,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){722,371,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "8", (Rectangle){722,371,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){722,456,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "9", (Rectangle){722,456,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){722,542,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "10", (Rectangle){722,542,59,59}, 50, 0, UI_GREEN_LGT, pfont);

    /*ch_x[1] = '\0';
    for (int x = 6; x < 10; x++)
    {
        sprintf(ch_x,"%i",x);
        DrawTextEx(font, ch_x,(Vector2){738, 200 + (x - 6) * 85}, 59, 0, UI_GREEN_LGT);
    }
    DrawTextEx(font, "10",(Vector2){720, 542}, 59, 0, UI_GREEN_LGT);*/

    //MFD corner rocker buttons
    DrawRectangleRoundedLines((Rectangle){18,78,59,100},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "27", (Rectangle){18,78,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_TOP);
    textAlign(font, "28", (Rectangle){18,78,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_BOTTOM);
    DrawRectangleRoundedLines((Rectangle){722,78,59,100},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "21", (Rectangle){722,78,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_TOP);
    textAlign(font, "22", (Rectangle){722,78,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_BOTTOM);
    DrawRectangleRoundedLines((Rectangle){18,613,59,100},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "25", (Rectangle){18,613,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_TOP);
    textAlign(font, "26", (Rectangle){18,613,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_BOTTOM);
    DrawRectangleRoundedLines((Rectangle){722,613,59,100},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "23", (Rectangle){722,613,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_TOP);
    textAlign(font, "24", (Rectangle){722,613,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_BOTTOM);

    //EndTextureMode();

    //BeginShaderMode(sh);
    //DrawTextureRec(tgt.texture, (Rectangle){0, 0, tgt.texture.width, -tgt.texture.height}, (Vector2){0, 0}, WHITE);
    //EndShaderMode();
    //DrawFPS(10,10);

    EndDrawing();
    }
    TakeScreenshot("./RecTest.png");
    //sleep(10);
    //UnloadRenderTexture(tgt);

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
