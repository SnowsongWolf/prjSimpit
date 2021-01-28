#include "raylib.h"
#include "colorsheet.h"
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

  switch (al) {
    case A_LEFT:
      origin.x = t_point.x + t_padding.left;
      break;

    case A_CENTER:
      origin.x = t_point.x - tmpSize.x / 2 - (t_padding.right - t_padding.left)/2;  // I have a headache
      break;

    case A_RIGHT:
      origin.x = t_point.x - tmpSize.x - t_padding.left - t_padding.right;
      break;

    default:
      break;
  }

  switch (val) {
    case V_TOP:
      origin.y = t_point.y + t_padding.top;
      break;

    case V_CENTER:
      origin.y = t_point.y - tmpSize.y / 2 - (t_padding.bottom - t_padding.top)/2;
      break;

    case V_BOTTOM:
      origin.y = t_point.y - tmpSize.y - t_padding.top;

    default:
      break;
  }

  DrawTextEx(t_font, (char*)strText.c_str(), origin, t_size, t_spacing, t_color);
}

void scalePadding(float scaleSize, Padding &scalePadding) {
    // Scale padding assuming generated based on 100pt font
    scalePadding.left = (int)((float)scalePadding.left / 100.0f * scaleSize);
    scalePadding.right = (int)((float)scalePadding.right / 100.0f * scaleSize);
    scalePadding.top = (int)((float)scalePadding.top / 100.0f * scaleSize);
    scalePadding.bottom = (int)((float)scalePadding.bottom / 100.0f * scaleSize);
}

void btnLabel(uint8_t btn, string label, Style stlLabel, Vector2 drawOffset, BState bState, Texture2D *icon) {

    Color text;
    Color bkg;
    Color stroke;

    // select colors
    switch (bState) {
        case B_SEL:
            text = stlLabel.txtSelect;
            bkg = stlLabel.bkgSelect;
            stroke = stlLabel.stkSelect;
            break;

        case B_HI:
            text = stlLabel.txtHighight;
            bkg = stlLabel.bkgHighlight;
            stroke = stlLabel.stkHighlight;
            break;

        case B_DIS:
            text = stlLabel.txtDisable;
            bkg = stlLabel.bkgDisable;
            stroke = stlLabel.stkDisable;
            break;

        default:                        // bState NONE
            text = stlLabel.txtColor;
            bkg = stlLabel.bkgColor;
            stroke = stlLabel.stkColor;
            //printf("bState is NONE\n\r");
            break;
    }

    // select font/icon
    printf ("Icon: %i\n\r", icon);
    bool useText = true;
    if (icon)
        useText = false;
    /*printf("Use Text: ");
    if (useText)
        printf("TRUE\n\r");
    else
        printf("FALSE\n\r");*/

    // calculate size adjusted padding
    Font lblFont = stlLabel.txtFont;
    float lblSpacing = stlLabel.txtSpacing;
    Padding lblPadding = stlLabel.txtPad;
    scalePadding(FSIZE, lblPadding);

    // calculate size adjusted font size
    float lblSize = FSIZE;
    if (useText)
        lblSize *= lblSize / (FSIZE + lblPadding.top + lblPadding.bottom);

    // find position
    Align lblAlign = A_RIGHT;
    VAlign lblVAlign = V_TOP;
    Rectangle recBtn = (Rectangle){0,0,0,0};
    switch (btn) {
        case 1 ... 5:
            recBtn.x = drawOffset.x + (btn - 1) * 93 + 69;
            printf("Button is %i\n\rLabel X is %f\n\r",btn,drawOffset.x + (btn - 1) * 93 + 169);
            recBtn.y = drawOffset.y;
            recBtn.width = 90;
            recBtn.height = 30;

            if (!useText) {
                recBtn.x = drawOffset.x + (btn - 1) * 93 + 99;
                recBtn.width = 30;
                recBtn.height = 30;
            }

            lblVAlign = V_CENTER;
            lblAlign = A_CENTER;
            break;

        case 6 ... 10:
            recBtn.x = drawOffset.x + 460;
            recBtn.y = drawOffset.y + (btn - 6) * 85.5f + 115;
            recBtn.width = 140;
            recBtn.height = 30;

            if (!useText) {
                recBtn.x = drawOffset.x + 570;
                recBtn.width = 30;
            }

            lblAlign = A_RIGHT;
            lblVAlign = V_CENTER;
            break;

        case 11 ... 15:
            recBtn.x = drawOffset.x + (15 - btn) * 93 + 69;
            recBtn.y = drawOffset.y + 570;
            recBtn.width = 90;
            recBtn.height = 30;

            if (!useText) {
                recBtn.x = drawOffset.x + (15 - btn) * 93 + 99;
                recBtn.width = 30;
                recBtn.height = 30;
            }

            lblVAlign = V_CENTER;
            lblAlign = A_CENTER;
            break;

        case 16 ... 20:
            recBtn.x = drawOffset.x;
            recBtn.y = drawOffset.y + (20 - btn) * 85.5f + 115;
            recBtn.width = 140;
            recBtn.height = 30;

            if (!useText)
                recBtn.width = 30;

            lblAlign = A_LEFT;
            lblVAlign = V_CENTER;
            break;

        default:
            break;
    }

    //printf("Draw rectangle is %f,%f %fx%f\n\r",recBtn.x, recBtn.y, recBtn.width, recBtn.height);

    // draw background
    DrawRectangleRec(recBtn,bkg);

    // draw stroke
    DrawRectangleLinesEx(recBtn, 1, stroke);

    // draw text/icon
    if (useText)
        textAlign(lblFont, label, recBtn, lblSize, lblSpacing, text, lblPadding, lblAlign, lblVAlign);
    else
        DrawTextureV(*icon, (Vector2){recBtn.x, recBtn.y}, text);

}

void uiTemplate(Vector2 ui_origin, Font font) {
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 99,ui_origin.y + 99,602,602}, 0.24, 0, 1, UI_LINE);      // Display area
    Rectangle dArea = (Rectangle){ui_origin.x + 100,ui_origin.y + 100,600,600};
    Padding pfont = (Padding){2,0,-6,-6};

    // MFD top row buttons
    printf("Template X is %f",ui_origin.x + 184);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 184,ui_origin.y + 18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "1", (Rectangle){ui_origin.x + 184,ui_origin.y + 18,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 277,ui_origin.y + 18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "2", (Rectangle){ui_origin.x + 277,ui_origin.y + 18,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 370,ui_origin.y + 18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "3", (Rectangle){ui_origin.x + 370,ui_origin.y + 18,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 464,ui_origin.y + 18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "4", (Rectangle){ui_origin.x + 464,ui_origin.y + 18,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 556,ui_origin.y + 18,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "5", (Rectangle){ui_origin.x + 556,ui_origin.y + 18,59,59}, 50, 0, UI_GREEN_LGT, pfont);

    //MFD left row buttons
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 18,ui_origin.y + 200,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "20", (Rectangle){ui_origin.x + 18,ui_origin.y + 200,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 18,ui_origin.y + 285,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "19", (Rectangle){ui_origin.x + 18,ui_origin.y + 285,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 18,ui_origin.y + 371,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "18", (Rectangle){ui_origin.x + 18,ui_origin.y + 371,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 18,ui_origin.y + 456,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "17", (Rectangle){ui_origin.x + 18,ui_origin.y + 456,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 18,ui_origin.y + 542,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "16", (Rectangle){ui_origin.x + 18,ui_origin.y + 542,59,59}, 50, 0, UI_GREEN_LGT, pfont);

    /*for (int x = 16; x < 21; x++)
    {
        sprintf(ch_x,"%i",x);
        DrawTextEx(font, ch_x,(Vector2){16, 542 - (x - 16) * 85}, 59, 0, UI_GREEN_LGT);
    }*/

    //MFD bottom column buttons
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 184,ui_origin.y + 723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "15", (Rectangle){ui_origin.x + 184,ui_origin.y + 723,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 277,ui_origin.y + 723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "14", (Rectangle){ui_origin.x + 277,ui_origin.y + 723,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 370,ui_origin.y + 723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "13", (Rectangle){ui_origin.x + 370,ui_origin.y + 723,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 464,ui_origin.y + 723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "12", (Rectangle){ui_origin.x + 464,ui_origin.y + 723,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 556,ui_origin.y + 723,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "11", (Rectangle){ui_origin.x + 556,ui_origin.y + 723,59,59}, 50, 0, UI_GREEN_LGT, pfont);

    //MFD right column buttons
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 722,ui_origin.y + 200,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "6", (Rectangle){ui_origin.x + 722,ui_origin.y + 200,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 722,ui_origin.y + 285,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "7", (Rectangle){ui_origin.x + 722,ui_origin.y + 285,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 722,ui_origin.y + 371,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "8", (Rectangle){ui_origin.x + 722,ui_origin.y + 371,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 722,ui_origin.y + 456,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "9", (Rectangle){ui_origin.x + 722,ui_origin.y + 456,59,59}, 50, 0, UI_GREEN_LGT, pfont);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 722,ui_origin.y + 542,59,59},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "10", (Rectangle){ui_origin.x + 722,ui_origin.y + 542,59,59}, 50, 0, UI_GREEN_LGT, pfont);

    //MFD corner rocker buttons
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 18,ui_origin.y + 78,59,100},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "27", (Rectangle){ui_origin.x + 18,ui_origin.y + 78,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_TOP);
    textAlign(font, "28", (Rectangle){ui_origin.x + 18,ui_origin.y + 78,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_BOTTOM);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 722,ui_origin.y + 78,59,100},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "21", (Rectangle){ui_origin.x + 722,ui_origin.y + 78,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_TOP);
    textAlign(font, "22", (Rectangle){ui_origin.x + 722,ui_origin.y + 78,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_BOTTOM);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 18,ui_origin.y + 613,59,100},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "25", (Rectangle){ui_origin.x + 18,ui_origin.y + 613,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_TOP);
    textAlign(font, "26", (Rectangle){ui_origin.x + 18,ui_origin.y + 613,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_BOTTOM);
    DrawRectangleRoundedLines((Rectangle){ui_origin.x + 722,ui_origin.y + 613,59,100},0.1f,0,1,UI_BOX_LGT);
    textAlign(font, "23", (Rectangle){ui_origin.x + 722,ui_origin.y + 613,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_TOP);
    textAlign(font, "24", (Rectangle){ui_origin.x + 722,ui_origin.y + 613,59,100}, 50, 0, UI_GREEN_LGT, pfont, A_CENTER, V_BOTTOM);
}
