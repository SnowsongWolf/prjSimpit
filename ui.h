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

#define PADDING_NONE    (Padding){0,0,0,0}

enum Align {A_LEFT = 0, A_CENTER = 1, A_RIGHT = 2};
enum VAlign {V_TOP = 0, V_CENTER = 1, V_BOTTOM = 2};

void textAlign(Font t_font, string strText, Rectangle t_area, float t_size, float t_spacing, Color t_color,
             Padding t_padding = PADDING_NONE, Align al = A_CENTER, VAlign val = V_CENTER);

void textAlign(Font t_font, string strText, Vector2 t_point, float t_size, float t_spacing, Color t_color,
             Padding t_padding = PADDING_NONE, Align al = A_CENTER, VAlign val = V_CENTER);

void uiTemplate(Vector2 ui_origin, Font font);
