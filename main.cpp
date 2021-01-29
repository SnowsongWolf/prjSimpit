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
bool init = false;
bool serConn = false;
int screenWidth = 1280 * 2;
int screenHeight = 800;
Font font = {0};
Font fnum = {0};
Texture2D icoHome;
Style stylDefault;

string cType[1] = {"Button Action"};
string c0d[4] = {"Down", "Up", "Press", "Long Press"};
string c0m[7] = {"Joy Left", "Joy Right", "Throttle", "Rudder", "Wheel", "MFCD Left", "MFCD Right"};

#define D_JLEFT     1
#define D_JRIGHT    2
#define D_THROTTLE  3
#define D_RUDDER    4
#define D_WHEEL     5
#define D_MLEFT     6
#define D_MRIGHT    7

enum btnState {BTN_UP = 0, BTN_DOWN = 1, BTN_PRESS = 2, BTN_LONG = 3};
btnState Buttons[7][24];

void dPrint(string strPrint);
void dPrintln(string strPrint);

void doInit();

int main()
{
    if (!init)
        doInit();

    while(!WindowShouldClose())             // main loop here
    {
        if (updateSerial()) {
            dPrint("Message for you sir: ");
            string cmd = parseSerial();
            if (cmd[0] != 1)
                dPrintln(cmd);
            if (cmd[0] == 1) {              // If command is type Button Action
                dPrint(cType[(uint8_t)cmd[0] - 1]);
                dPrint(":");
                dPrint(c0d[(uint8_t)cmd[1] - 1]);
                dPrint(":");
                dPrint(c0m[(uint8_t)cmd[2] - 1]);
                dPrint(": Button ");
                dPrintln(to_string(cmd[3]));

                btnState bAction = BTN_UP;
                uint8_t device = (uint8_t)cmd[2];
                uint8_t button = (uint8_t)cmd[3];

                switch ((uint8_t)cmd[1]) {
                    case 1:              //
                        bAction = BTN_DOWN;
                        break;

                    case 3:
                        bAction = BTN_PRESS;
                        break;

                    case 4:
                        bAction = BTN_LONG;
                        break;

                    default:
                        bAction = BTN_UP;
                        break;
                }

                Buttons[device][button] = bAction;
            }
        }

    BeginDrawing();
    ClearBackground(BLACK);
    //BeginTextureMode(tgt);

    uiTemplate((Vector2){0,0}, fnum);
    uiTemplate((Vector2){1280,0}, fnum);

    //Padding pfont = (Padding){2,0,-6,-6};
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
    //dPrint("Received: ");
    //dPrintln(parseSerial());

    if (closeSerial())
        dPrintln("Serial closed.");
    else
        dPrintln("Error closing serial.");

    return 1;
}

void dPrint(string strPrint) {
    if (debug) {
        printf((char*)strPrint.c_str());
        if (serConn)
            txSerial(strPrint);
    }
}

void dPrintln(string strPrint) {
    if (debug) {
        printf("%s%c%c",strPrint.c_str(),'\n','\r');
            if (serConn) {
                txSerial(strPrint);
                txSerial("\n\r");
            }
    }
}

void doInit() {
    serConn = initSerial();
    if (serConn)
        dPrintln("Serial connected.");
    else
        dPrintln("Serial connection error.\n\r");

    txSerial("Hello!\n\r");

    //Shader sh;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_MSAA_4X_HINT);

    //SetTraceLogLevel(LOG_ALL);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    MaximizeWindow();
    HideCursor();
    SetTargetFPS(60);

    unsigned int fileSize = 0;
    unsigned char *fileData = LoadFileData("resources/fonts/BlenderPro-Heavy.ttf", &fileSize);

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

    stylDefault = (Style){ font, (Padding){8,0,-12,-12}, 0.0f,
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
    icoHome = LoadTextureFromImage(image);
    UnloadImage(image);

    for (uint8_t x = 0; x < 7; x++) {
        for (uint8_t y = 0; y < 24; y++)
            Buttons[x][y] = BTN_UP;
    }
}
