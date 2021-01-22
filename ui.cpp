#include "ui.h"

void textAlign(Font t_font, string strText, Rectangle t_area, float t_size, float t_spacing, Color t_color,
             Padding t_padding, Align al, VAlign val) {
  Vector2 origin = {t_area.x, t_area.y};
  Vector2 tmpSize = MeasureTextEx(t_font, (char*)strText.c_str(), t_size, t_spacing);

  switch (al) {
    case A_LEFT:
      origin.x = t_area.x + t_padding.left;
      break;

    case A_CENTER:
      origin.x = t_area.width / 2 + t_area.x - tmpSize.x / 2 - (t_padding.right - t_padding.left)/2;  // I have a headache
      break;

    case A_RIGHT:
      origin.x = t_area.x + t_area.width - tmpSize.x - t_padding.left - t_padding.right;
      break;

    default:
      break;
  }

  switch (val) {
    case V_TOP:
      origin.y = t_area.y + t_padding.top;
      break;

    case V_CENTER:
      origin.y = t_area.height / 2 + t_area.y - tmpSize.y / 2 - (t_padding.bottom - t_padding.top)/2;
      break;

    case V_BOTTOM:
      origin.y = t_area.y + t_area.height - tmpSize.y - t_padding.top;

    default:
      break;
  }

  DrawTextEx(t_font, (char*)strText.c_str(), origin, t_size, t_spacing, t_color);
}

void textAlign(Font t_font, string strText, Vector2 t_point, float t_size, float t_spacing, Color t_color,
             Padding t_padding, Align al, VAlign val) {
  Vector2 origin = t_point;
  Vector2 tmpSize = MeasureTextEx(t_font, (char*)strText.c_str(), t_size, t_spacing);
}
