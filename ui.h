// Functions for UI drawing.
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "raylib.h"

using namespace std;

public struct Padding {
  int left;
  int right;
  int top;
  int bottom;
};

#define PADDING_NONE    (Padding){0,0,0,0}

public enum Align {A_LEFT, A_CENTER, A_RIGHT};
public enum VAlign {V_TOP, V_CENTER, V_BOTTOM};

public void textAlign(Font t_font, string strText, Rectangle t_area, float t_size, float t_spacing = 0, Color t_color, 
             Padding t_padding = PADDING_NONE, Align al = A_CENTER, VAlign val = V_CENTER);

public void textAlign(Font t_font, string strText, Vector2 t_point, float t_size, float t_spacing = 0, Color t_color, 
             Padding t_padding = PADDING_NONE, Align al = A_CENTER, VAlign val = V_CENTER);
