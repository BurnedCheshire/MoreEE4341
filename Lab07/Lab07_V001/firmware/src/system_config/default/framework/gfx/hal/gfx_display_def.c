#include "gfx/hal/inc/gfx_display.h"
#include "gfx/hal/inc/gfx_common.h"


GFX_DisplayInfo GFX_DisplayInfoList[] =
{
    {
	    "",  // description
		GFX_COLOR_MODE_RGB_332,  // color mode
		{
			0,  // x position (always 0)
			0,  // y position (always 0)
			,  // display width
			, // display height
		},
		{
		    ,  // data bus width
		    {
				,  // horizontal pulse width
				,  // horizontal back porch
				,  // horizontal front porch
		    },
		    {
				,  // vertical pulse width
				,  // vertical back porch
				,  // vertical front porch
		    },
			,  // inverted left shift
		},
	},
};