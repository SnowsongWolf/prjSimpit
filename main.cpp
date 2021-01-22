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
        
    // MFD top row buttons
    DrawRectangleRoundedLines((Rectangle){184,18,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){277,18,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){370,18,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){464,18,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){556,18,59,59},0.1f,0,1,UI_BOX_LGT);
        
    char ch_x[3] = {0};
    for (int x = 1; x < 6; x++)
    {
        sprintf(ch_x,"%i",x);
        DrawTextEx(font, ch_x,(Vector2){202 + (x - 1) * 93, 18}, 59, 0, UI_GREEN_LGT);
    }
    
    //MFD left row buttons
    DrawRectangleRoundedLines((Rectangle){18,200,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){18,285,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){18,371,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){18,456,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){18,542,59,59},0.1f,0,1,UI_BOX_LGT);
    
    for (int x = 6; x < 10; x++)
    {
        sprintf(ch_x,"%i",x);
        DrawTextEx(font, ch_x,(Vector2){46, 200 + (x - 6) * 93, 18}, 59, 0, UI_GREEN_LGT);
    }
    DrawTextEx(font, "10",(Vector2){21, 542, 59, 0, UI_GREEN_LGT);
        
    //MFD bottom column buttons
    DrawRectangleRoundedLines((Rectangle){184,723,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){277,723,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){370,723,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){464,723,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){556,723,59,59},0.1f,0,1,UI_BOX_LGT);
        
    //MFD right column buttons
    DrawRectangleRoundedLines((Rectangle){722,200,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){722,285,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){722,371,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){722,456,59,59},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){722,542,59,59},0.1f,0,1,UI_BOX_LGT);
        
    //MFD corner rocker buttons
    DrawRectangleRoundedLines((Rectangle){18,78,59,100},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){722,78,59,100},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){18,613,59,100},0.1f,0,1,UI_BOX_LGT);
    DrawRectangleRoundedLines((Rectangle){722,613,59,100},0.1f,0,1,UI_BOX_LGT);

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
