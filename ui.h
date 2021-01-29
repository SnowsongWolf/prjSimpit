// Functions for UI drawing.
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "raylib.h"

using namespace std;

struct Padding {
  int left;
  int right;
  int top;
  int bottom;
};

struct Style {
    Font txtFont;
    Padding txtPad;
    float txtSpacing;

    Font numFont;
    Padding numPad;
    float numSpacing;

    Color txtColor;
    Color bkgColor;
    Color stkColor;

    Color txtSelect;
    Color bkgSelect;
    Color stkSelect;

    Color txtHighight;
    Color bkgHighlight;
    Color stkHighlight;

    Color txtDisable;
    Color bkgDisable;
    Color stkDisable;
};

struct Button {
    uint8_t btnIndex;
    uint8_t btnLabel;
    Texture2D *btnIcon = nullptr;
};

struct Screen {
    string scrName;
    string btnName;
    uint8_t btnIndex;
    Button scrButton[24];
};

#define PADDING_NONE    (Padding){0,0,0,0}
#define FSIZE           20.0f
#define MFCD_LEFT       (Vector2){100,100}
#define MFCD_RIGHT      (Vector2){1380,100}

//Texture2D I_NONE;

enum Align {A_LEFT = 0, A_CENTER = 1, A_RIGHT = 2};
enum VAlign {V_TOP = 0, V_CENTER = 1, V_BOTTOM = 2};
enum BState {B_NONE = 0, B_SEL = 1, B_HI = 2, B_DIS = 3};
enum TType {T_TEXT = 0, T_NUM = 2};

void textAlign(Font t_font, string strText, Rectangle t_area, float t_size, float t_spacing, Color t_color,
             Padding t_padding = PADDING_NONE, Align al = A_CENTER, VAlign val = V_CENTER);

void textAlign(Font t_font, string strText, Vector2 t_point, float t_size, float t_spacing, Color t_color,
             Padding t_padding = PADDING_NONE, Align al = A_CENTER, VAlign val = V_CENTER);

void scalePadding(float scaleSize, Padding &scalePadding);

void btnLabel(uint8_t btn, string label, Style stlLabel, Vector2 drawOffset = MFCD_LEFT, BState = B_NONE, Texture2D *icon = nullptr);

void uiTemplate(Vector2 ui_origin, Font font);
