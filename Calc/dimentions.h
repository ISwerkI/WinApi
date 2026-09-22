#pragma once

#define g_i_BUTTON_SIZE			50
#define g_i_INTERVAL			10
#define g_i_BUTTON_DOUBLE_SIZE	g_i_BUTTON_SIZE*2+g_i_INTERVAL
#define g_i_DISPLAY_WIDTH		g_i_BUTTON_SIZE*5 + g_i_INTERVAL*4
#define g_i_DISPLAY_HEIGHT		20
#define g_i_START_X				10
#define g_i_START_Y				10
#define g_i_BUTTON_START_X		g_i_START_X
#define g_i_BUTTON_START_Y		g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL	
#define BUTTON_SHIFT_X(n)		g_i_BUTTON_START_X + (g_i_INTERVAL+g_i_BUTTON_SIZE) * (n)
#define BUTTON_SHIFT_Y(n)		g_i_BUTTON_START_Y + (g_i_INTERVAL+g_i_BUTTON_SIZE) * (n)
#define WINDOW_SIZE_X			g_i_DISPLAY_WIDTH +	g_i_BUTTON_START_X*4
#define WINDOW_SIZE_Y			g_i_START_Y*6+g_i_DISPLAY_HEIGHT+(g_i_INTERVAL+g_i_BUTTON_SIZE)*4