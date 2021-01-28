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
    int screenWidth = 1280 * 2;
    int screenHeight = 800;

    bool serConn = initSerial();
    if (serConn)
        dPrintln("Serial connected.");
    else
        dPrintln("Serial connection error.\n\r");

    txSerial("Hello!\n\r");

    //Shader sh;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);

    //SetTraceLogLevel(LOG_ALL);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    MaximizeWindow();
    HideCursor();
    //printf("Monitors detected: %i\n\r",GetMonitorCount());
    //printf("Monitor size: %ix%i\n\r",GetMonitorWidth(2),GetMonitorHeight(2));
    //printf("Monitor physical size: %ix%i\n\r",GetMonitorPhysicalWidth(7),GetMonitorPhysicalHeight(7));

    SetTargetFPS(60);
    //sh = LoadShader(0, "resources/shaders/glsl120/bloom.fs");
    //Font font = LoadFont("resources/fonts/BlenderPro-Heavy.ttf");
    //Font font2 = LoadFont("resources/pixantiqua.ttf");

    unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData("resources/fonts/BlenderPro-Heavy.ttf", &fileSize);

    Font font = {0};
    font.baseSize = 50;
    font.charsCount = 95;
    font.chars = LoadFontData(fileData, fileSize, 50, 0, 0, FONT_DEFAULT);
    Image atlas = GenImageFontAtlas(font.chars, &font.recs, 95, 50, 0, 1);
    font.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);
    UnloadFileData(fileData);
    GenTextureMipmaps(&font.texture);

    fileSize = 0;
    fileData = LoadFileData("resources/fonts/MigraineMachine-mL2aj.ttf", &fileSize);

    Font fnum = {0};
    fnum.baseSize = 50;
    fnum.charsCount = 95;
    fnum.chars = LoadFontData(fileData, fileSize, 50, 0, 0, FONT_DEFAULT);
    atlas = GenImageFontAtlas(fnum.chars, &fnum.recs, 95, 50, 0, 1);
    fnum.texture = LoadTextureFromImage(atlas);
    UnloadImage(atlas);
    UnloadFileData(fileData);

    //RenderTexture2D tgt = LoadRenderTexture(screenWidth, screenHeight);
    GenTextureMipmaps(&font.texture);
    //SetTextureFilter(font.texture, FILTER_BILINEAR);
    //SetTextureFilter(font2.texture, FILTER_BILINEAR);
    //SetTextureFilter(tgt.texture, FILTER_BILINEAR);

    Vector2 wo = (Vector2){100,100};

    Style stylDefault = (Style){ font, (Padding){8,0,-12,-12}, 0.0f,
                                fnum, (Padding){0,0,0,0}, 0.0f,
                                UI_LINE_LGT, UI_BOX_DRK, UI_LINE,
                                UI_LINE_DRK, UI_BOX_LGT, UI_LINE_LGT,
                                UI_LINE_LGT, UI_BOX, UI_GREEN_LGT,
                                UI_LINE, UI_BKG, UI_LINE_DRK};

    /*stylDefault.txtFont = font;
    stylDefault.txtPad = (Padding){8,0,-12,-12};
    stylDefault.txtSpacing = 0.0f;
    stylDefault.bkgColor = UI_BOX;
    stylDefault.stkColor = UI_LINE_LGT;
    stylDefault.txtColor = UI_LINE_LGT;*/

    Image image = LoadImage("resources/icons/ico_home.png");
    Texture2D icoHome = LoadTextureFromImage(image);
    UnloadImage(image);

    while(!WindowShouldClose() && !updateSerial())
    {
    BeginDrawing();
    ClearBackground(BLACK);
    //BeginTextureMode(tgt);

    uiTemplate((Vector2){0,0}, fnum);
    uiTemplate((Vector2){1280,0}, fnum);

    Padding pfont = (Padding){2,0,-6,-6};
    //textAlign(font, "MFCD Left", (Rectangle){100,100,600,600}, 50, 0, UI_LINE_LGT, pfont);
    //textAlign(font, "MFCD Right", (Rectangle){1380,100,600,600}, 50, 0, UI_LINE_LGT, pfont);

    //EndTextureMode();

    //BeginShaderMode(sh);
    //DrawTextureRec(tgt.texture, (Rectangle){0, 0, tgt.texture.width, -tgt.texture.height}, (Vector2){0, 0}, WHITE);
    //EndShaderMode();
    //DrawFPS(10,10);

    /*btnLabel(1, "First!", stylDefault);
    btnLabel(2, "Second!", stylDefault);
    btnLabel(3, "", stylDefault, MFCD_LEFT, B_NONE, &icoHome);
    btnLabel(4, "Fourth!", stylDefault);
    btnLabel(5, "5!", stylDefault);*/

    btnLabel(20, "Sel Ship", stylDefault);
    btnLabel(19, "Retrieve", stylDefault);
    btnLabel(18, "Add New", stylDefault);
    btnLabel(17, "Power", stylDefault);
    btnLabel(16, "Ext Lights", stylDefault);
    btnLabel(6, "Ext Doors", stylDefault);
    btnLabel(7, "LDG Gear", stylDefault);
    btnLabel(8, "FGT Assist", stylDefault);
    btnLabel(9, "VTOL", stylDefault, MFCD_LEFT, B_DIS);
    btnLabel(10, "DSMS Edit", stylDefault, MFCD_LEFT, B_HI);

    /*btnLabel(6, "Do you want", stylDefault);
    btnLabel(7, "Some more?", stylDefault);
    btnLabel(8, "", stylDefault, MFCD_LEFT, B_NONE, &icoHome);*/

    btnLabel(15, "Pre F", stylDefault, MFCD_LEFT, B_SEL);
    btnLabel(14, "DSMS", stylDefault);
    btnLabel(13, "Power", stylDefault);
    btnLabel(12, "Fly", stylDefault);
    btnLabel(11, "Drive", stylDefault);

    /*btnLabel(17, "Hello", stylDefault);
    btnLabel(16, "World!", stylDefault);

    btnLabel(17, "Konnichi-wa", stylDefault, MFCD_RIGHT);
    btnLabel(16, "Sekai!", stylDefault, MFCD_RIGHT);*/

    EndDrawing();

    /*BeginDrawing(1);
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your SECOND window!", 190, 200, 20, BLACK);
    EndDrawing();*/
    }
    //TakeScreenshot("./Template.png");
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
