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

laScheme TryAgain;
laScheme NewScheme;
laButtonWidget* ButtonWidget5;
laSliderWidget* SliderWidget7;
laRectangleWidget* RectangleWidget8;
laImageWidget* ImageWidget9;
laKeyPadWidget* KeyPadWidget10;


static void ScreenCreate_screen1(laScreen* screen);


int32_t libaria_initialize(void)
{
    laScreen* screen;

    laScheme_Initialize(&TryAgain, GFX_COLOR_MODE_RGB_332);
    TryAgain.base = 0x52;
    TryAgain.highlight = 0x57;
    TryAgain.highlightLight = 0x97;
    TryAgain.shadow = 0x92;
    TryAgain.shadowDark = 0x49;
    TryAgain.foreground = 0x0;
    TryAgain.foregroundInactive = 0xDB;
    TryAgain.foregroundDisabled = 0x92;
    TryAgain.background = 0x76;
    TryAgain.backgroundInactive = 0xDB;
    TryAgain.backgroundDisabled = 0x46;
    TryAgain.text = 0x0;
    TryAgain.textHighlight = 0xCF;
    TryAgain.textHighlightText = 0xFF;
    TryAgain.textInactive = 0xDB;
    TryAgain.textDisabled = 0x92;

    laScheme_Initialize(&NewScheme, GFX_COLOR_MODE_RGB_332);
    NewScheme.base = 0x2C;
    NewScheme.highlight = 0xBA;
    NewScheme.highlightLight = 0xFF;
    NewScheme.shadow = 0x92;
    NewScheme.shadowDark = 0x49;
    NewScheme.foreground = 0x0;
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
    laContext_AddScreen(screen);

    laContext_SetActiveScreen(0);

	return 0;
}

static void ScreenCreate_screen1(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 240, 320);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetScheme((laWidget*)layer0, &TryAgain);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    ButtonWidget5 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget5, 1, 2);
    laWidget_SetSize((laWidget*)ButtonWidget5, 197, 42);
    laWidget_SetScheme((laWidget*)ButtonWidget5, &TryAgain);
    laWidget_SetBackgroundType((laWidget*)ButtonWidget5, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ButtonWidget5, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget5, laString_CreateFromID(string_Text));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget5);

    SliderWidget7 = laSliderWidget_New();
    laWidget_SetPosition((laWidget*)SliderWidget7, 5, 54);
    laWidget_SetSize((laWidget*)SliderWidget7, 20, 100);
    laWidget_SetScheme((laWidget*)SliderWidget7, &TryAgain);
    laWidget_SetBackgroundType((laWidget*)SliderWidget7, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)SliderWidget7, LA_WIDGET_BORDER_BEVEL);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)SliderWidget7);

    RectangleWidget8 = laRectangleWidget_New();
    laWidget_SetPosition((laWidget*)RectangleWidget8, 48, 53);
    laWidget_SetSize((laWidget*)RectangleWidget8, 100, 100);
    laWidget_SetScheme((laWidget*)RectangleWidget8, &TryAgain);
    laWidget_SetBackgroundType((laWidget*)RectangleWidget8, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)RectangleWidget8, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RectangleWidget8);

    ImageWidget9 = laImageWidget_New();
    laWidget_SetPosition((laWidget*)ImageWidget9, 49, 52);
    laWidget_SetSize((laWidget*)ImageWidget9, 100, 102);
    laWidget_SetScheme((laWidget*)ImageWidget9, &TryAgain);
    laWidget_SetBackgroundType((laWidget*)ImageWidget9, LA_WIDGET_BACKGROUND_CACHE);
    laWidget_SetBorderType((laWidget*)ImageWidget9, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(ImageWidget9, &grapes);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ImageWidget9);

    KeyPadWidget10 = laKeyPadWidget_New(3, 3);
    laWidget_SetPosition((laWidget*)KeyPadWidget10, 34, 171);
    laWidget_SetSize((laWidget*)KeyPadWidget10, 129, 140);
    laWidget_SetScheme((laWidget*)KeyPadWidget10, &TryAgain);
    laWidget_SetBackgroundType((laWidget*)KeyPadWidget10, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)KeyPadWidget10, LA_WIDGET_BORDER_BEVEL);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 0, 0, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 0, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 0, 1, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 0, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 0, 2, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 0, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 1, 0, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 1, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 1, 1, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 1, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 1, 2, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 1, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 2, 0, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 2, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 2, 1, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 2, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyAction(KeyPadWidget10, 2, 2, LA_KEYPAD_CELL_ACTION_NONE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget10, 2, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyClickEventCallback(KeyPadWidget10, &KeyPadWidget10_KeyClickEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)KeyPadWidget10);

}



