// Functions for UI drawing.
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "raylib.h"

using namespace std;

enum Align {A_LEFT, A_CENTER, A_RIGHT};
enum VAlign {V_TOP, V_CENTER, V_BOTTOM};

void textRec(Font t_font, string strText, Rectangle t_area, float t_size, float t_spacing = 0, Vector4 t_padding = (Vector4){0,0,0,0}, Align al = A_CENTER, VAlign val = V_CENTER);
void textRec(Font t_font, string strText, Vector2 t_point, float t_size, float t_spacing = 0, Vector4 t_padding = (Vector4){0,0,0,0}, Align al = A_CENTER, VAlign val = V_CENTER);
