#include "ui.h"

public void textAlign(Font t_font, string strText, Rectangle t_area, float t_size, float t_spacing = 0, Color t_color,
             Padding t_padding = PADDING_NONE, Align al = A_CENTER, VAlign val = V_CENTER) {
  Vector2 origin = {t_area.x, t_area.y};
  Vector2 tmpSize = MeasureTextEx(t_font, (char*)strText.c_str(), t_size, t_spacing);
  
  switch (al) {
    case A_LEFT:
      origin.x = t_area.x + t_padding.left;
      break;
      
    case A_CENTER:
      origin.x = (tmpSize.x + t_padding.left + t_padding.right) / 2 + t_area.width / 2 + t_area.x + t_padding.left;  // I have a headache
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
      origin.y = (tmpSize.y + t_padding.top + t_padding.bottom) / 2 + t_area.height / 2 + t_area.y + t_padding.top; 
      break;
      
    case V_BOTTOM:
      origin.y = t_area.y + t_area.height - tmpSize.y - t_padding.top - t_padding.bottom;
      
    default:
      break;
  }
  
  DrawTextEx(t_font, origin, t_size, t_spacing, t_color);
}

public void textAlign(Font t_font, string strText, Vector2 t_point, float t_size, float t_spacing = 0, Color t_color,
             Padding t_padding = PADDING_NONE, Align al = A_CENTER, VAlign val = V_CENTER) {
  Vector2 origin = t_point;
  Vector2 tmpSize = MeasureTextEx(t_font, (char*)strText.c_str(), t_size, t_spacing);
}
