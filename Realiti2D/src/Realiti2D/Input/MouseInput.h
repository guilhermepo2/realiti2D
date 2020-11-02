#pragma once

#define R2D_BUTTON(X)       (1 << ((X)-1))
#define R2D_BUTTON_LEFT     1
#define R2D_BUTTON_MIDDLE   2
#define R2D_BUTTON_RIGHT    3
#define R2D_BUTTON_X1       4
#define R2D_BUTTON_X2       5
#define R2D_BUTTON_LMASK    R2D_BUTTON(R2D_BUTTON_LEFT)
#define R2D_BUTTON_MMASK    R2D_BUTTON(R2D_BUTTON_MIDDLE)
#define R2D_BUTTON_RMASK    R2D_BUTTON(R2D_BUTTON_RIGHT)
#define R2D_BUTTON_X1MASK   R2D_BUTTON(R2D_BUTTON_X1)
#define R2D_BUTTON_X2MASK   R2D_BUTTON(R2D_BUTTON_X2)

namespace Realiti2D {
	typedef enum {
		MOUSECODE_LEFT = R2D_BUTTON_LEFT,
		MOUSECODE_MIDDLE = R2D_BUTTON_MIDDLE,
		MOUSECODE_RIGHT = R2D_BUTTON_RIGHT
	} R2D_Mousecode;
}