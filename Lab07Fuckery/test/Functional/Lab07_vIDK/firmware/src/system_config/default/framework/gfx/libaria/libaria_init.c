/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    libaria_init.c

  Summary:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

    Created with MPLAB Harmony Version 2.06
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#include "gfx/libaria/libaria_init.h"

laScheme NewScheme;
laArcWidget* ArcWidget1;
laArcWidget* ArcWidget2;
laLabelWidget* LabelWidget3;
laCircleWidget* CircleWidget4;
laCircleWidget* CircleWidget5;
laKeyPadWidget* KeyPadWidget6;


static void ScreenCreate_screen1(laScreen* screen);


int32_t libaria_initialize(void)
{
    laScreen* screen;

    laScheme_Initialize(&NewScheme, GFX_COLOR_MODE_RGB_332);
    NewScheme.base = 0x72;
    NewScheme.highlight = 0x92;
    NewScheme.highlightLight = 0xDB;
    NewScheme.shadow = 0x92;
    NewScheme.shadowDark = 0x40;
    NewScheme.foreground = 0x60;
    NewScheme.foregroundInactive = 0xDB;
    NewScheme.foregroundDisabled = 0x92;
    NewScheme.background = 0xFF;
    NewScheme.backgroundInactive = 0xDB;
    NewScheme.backgroundDisabled = 0xBA;
    NewScheme.text = 0x0;
    NewScheme.textHighlight = 0x3;
    NewScheme.textHighlightText = 0xFF;
    NewScheme.textInactive = 0xDB;
    NewScheme.textDisabled = 0x92;

    GFX_Set(GFXF_DRAW_PIPELINE_MODE, GFX_PIPELINE_GCUGPU);
    laContext_SetStringTable(&stringTable);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_screen1);
    laScreen_SetOrientation(screen, LA_SCREEN_ORIENTATION_270);
    laContext_AddScreen(screen);

    laContext_SetActiveScreen(0);

	return 0;
}

static void ScreenCreate_screen1(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 320, 240);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    ArcWidget1 = laArcWidget_New();
    laWidget_SetPosition((laWidget*)ArcWidget1, -39, 191);
    laWidget_SetSize((laWidget*)ArcWidget1, 101, 101);
    laWidget_SetBackgroundType((laWidget*)ArcWidget1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ArcWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ArcWidget1);

    ArcWidget2 = laArcWidget_New();
    laWidget_SetPosition((laWidget*)ArcWidget2, -94, 145);
    laWidget_SetSize((laWidget*)ArcWidget2, 198, 220);
    laWidget_SetScheme((laWidget*)ArcWidget2, &NewScheme);
    laWidget_SetBackgroundType((laWidget*)ArcWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ArcWidget2, LA_WIDGET_BORDER_NONE);
    laArcWidget_SetRadius(ArcWidget2, 100);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ArcWidget2);

    LabelWidget3 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget3, 22, 7);
    laWidget_SetSize((laWidget*)LabelWidget3, 269, 39);
    laWidget_SetScheme((laWidget*)LabelWidget3, &NewScheme);
    laWidget_SetBackgroundType((laWidget*)LabelWidget3, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)LabelWidget3, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget3, laString_CreateFromID(string_Name));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget3);

    CircleWidget4 = laCircleWidget_New();
    laWidget_SetPosition((laWidget*)CircleWidget4, 269, 179);
    laWidget_SetSize((laWidget*)CircleWidget4, 101, 101);
    laWidget_SetScheme((laWidget*)CircleWidget4, &NewScheme);
    laWidget_SetBackgroundType((laWidget*)CircleWidget4, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CircleWidget4, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)CircleWidget4);

    CircleWidget5 = laCircleWidget_New();
    laWidget_SetPosition((laWidget*)CircleWidget5, 284, 197);
    laWidget_SetSize((laWidget*)CircleWidget5, 101, 101);
    laWidget_SetBackgroundType((laWidget*)CircleWidget5, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CircleWidget5, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)CircleWidget5);

    KeyPadWidget6 = laKeyPadWidget_New(3, 3);
    laWidget_SetPosition((laWidget*)KeyPadWidget6, 91, 64);
    laWidget_SetSize((laWidget*)KeyPadWidget6, 138, 128);
    laWidget_SetScheme((laWidget*)KeyPadWidget6, &NewScheme);
    laWidget_SetBackgroundType((laWidget*)KeyPadWidget6, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)KeyPadWidget6, LA_WIDGET_BORDER_BEVEL);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 0, 0, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 0, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 0, 1, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 0, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 0, 2, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 0, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 1, 0, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 1, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 1, 1, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 1, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 1, 2, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 1, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 2, 0, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 2, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 2, 1, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 2, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget6, 2, 2, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget6, 2, 2, LA_RELATIVE_POSITION_BEHIND);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)KeyPadWidget6);

}



