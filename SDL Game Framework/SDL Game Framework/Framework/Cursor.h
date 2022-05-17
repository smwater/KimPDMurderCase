#pragma once
#include "Common.h"
#include "Type.h"
#include "Image.h"

typedef struct cursor
{
	Image	CursorImage;
	COORD	CursorPos;
} Cursor;

void moveCursor();