/*******************************************************************************
  MPLAB Harmony Graphics Asset Header File

  File Name:
    gfx_resources_ext.h

  Summary:
    Header file containing a list of asset specifications for use with the
	MPLAB Harmony Graphics Stack.

  Description:
    Header file containing a list of asset specifications for use with the
	MPLAB Harmony Graphics Stack.

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

#ifndef GFX_RESOURCES_EXT_H
#define GFX_RESOURCES_EXT_H

#include "gfx/utils/gfx_utils.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END 

/*** Generated Asset Descriptors ***/
/*****************************************************************************
 * MPLAB Harmony Graphics Asset Location IDs
 *****************************************************************************/
#define GFXU_ASSET_LOCATION_ID_INTERNAL    0
 
/*****************************************************************************
 * MPLAB Harmony Graphics Image Assets
 *****************************************************************************/
/*********************************
 * GFX Image Asset
 * Name:   MCHP_LOGO
 * Size:   122x30 pixels
 * Mode:   INDEX_8
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset MCHP_LOGO;
	
/*********************************
 * GFX Image Asset
 * Name:   Frequency
 * Size:   16x21 pixels
 * Mode:   INDEX_8
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset Frequency;
	
/*********************************
 * GFX Image Asset
 * Name:   USB_CONNECTED
 * Size:   30x30 pixels
 * Mode:   INDEX_4
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset USB_CONNECTED;
	
/*********************************
 * GFX Image Asset
 * Name:   USB_DISCONNECTED
 * Size:   30x30 pixels
 * Mode:   INDEX_4
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset USB_DISCONNECTED;
	
/*********************************
 * GFX Image Asset
 * Name:   USB_NOT_CONNECTED
 * Size:   30x30 pixels
 * Mode:   INDEX_4
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset USB_NOT_CONNECTED;
	
/*********************************
 * GFX Image Asset
 * Name:   AudioMute16_2
 * Size:   32x25 pixels
 * Mode:   INDEX_4
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset AudioMute16_2;
	
/*********************************
 * GFX Image Asset
 * Name:   AudioPlay16_2
 * Size:   32x25 pixels
 * Mode:   INDEX_4
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset AudioPlay16_2;
	
/*****************************************************************************
 * MPLAB Harmony Graphics Palette Assets
 *****************************************************************************/
/*********************************
 * GFX Palette Asset
 * Name:   MCHP_LOGO_palette
 * Colors: 228
 * Format: RGB_565
 ***********************************/
extern GFXU_PaletteAsset MCHP_LOGO_palette;
	
/*********************************
 * GFX Palette Asset
 * Name:   Frequency_palette
 * Colors: 38
 * Format: RGB_565
 ***********************************/
extern GFXU_PaletteAsset Frequency_palette;
	
/*********************************
 * GFX Palette Asset
 * Name:   USB_CONNECTED_palette
 * Colors: 4
 * Format: RGB_565
 ***********************************/
extern GFXU_PaletteAsset USB_CONNECTED_palette;
	
/*********************************
 * GFX Palette Asset
 * Name:   USB_DISCONNECTED_palette
 * Colors: 4
 * Format: RGB_565
 ***********************************/
extern GFXU_PaletteAsset USB_DISCONNECTED_palette;
	
/*********************************
 * GFX Palette Asset
 * Name:   USB_NOT_CONNECTED_palette
 * Colors: 3
 * Format: RGB_565
 ***********************************/
extern GFXU_PaletteAsset USB_NOT_CONNECTED_palette;
	
/*********************************
 * GFX Palette Asset
 * Name:   AudioMute16_2_palette
 * Colors: 6
 * Format: RGB_565
 ***********************************/
extern GFXU_PaletteAsset AudioMute16_2_palette;
	
/*********************************
 * GFX Palette Asset
 * Name:   AudioPlay16_2_palette
 * Colors: 5
 * Format: RGB_565
 ***********************************/
extern GFXU_PaletteAsset AudioPlay16_2_palette;
	
/*****************************************************************************
 * MPLAB Harmony Graphics Font Assets
 *****************************************************************************/
/*********************************
 * GFX Font Asset
 * Name:         LiberationSans14
 * Height:       17
 * Style:        Plain
 * Glyph Count:  18
 * Range Count:  13
 * Glyph Ranges: 0x20
			     0x2D
			     0x41-0x44
			     0x48
			     0x4D
			     0x52-0x53
			     0x55
			     0x64-0x65
			     0x69
			     0x6D
			     0x6F
			     0x73
			     0x75
 ***********************************/
extern GFXU_FontAsset LiberationSans14;
	
/*********************************
 * GFX Font Asset
 * Name:         LiberationSans12
 * Height:       15
 * Style:        Plain
 * Glyph Count:  11
 * Range Count:  2
 * Glyph Ranges: 0x25
			     0x30-0x39
 ***********************************/
extern GFXU_FontAsset LiberationSans12;
	
/*********************************
 * GFX Font Asset
 * Name:         LiberationSans11
 * Height:       14
 * Style:        Plain
 * Glyph Count:  0
 * Range Count:  0
 ***********************************/
extern GFXU_FontAsset LiberationSans11;
	
/*****************************************************************************
 * MPLAB Harmony Graphics String Table
 *****************************************************************************/
/*********************************
 * GFX String Table
 * Name:         stringTable
 * Encoding:     ASCII
 * Languages:    default
 * String Count: 2
 ***********************************/
// language IDs
#define language_default    0

// string IDs
#define string_Digits    0
#define string_Title    1
 
extern GFXU_StringTableAsset stringTable;

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* GFX_RESOURCES_EXT_H */

