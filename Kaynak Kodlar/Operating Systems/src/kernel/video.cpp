#include <video.h>
#include <asm.h>
#include <string.h>

const int Color::BLACK		= 0;
const int Color::BLUE		= 1;
const int Color::GREEN		= 2;
const int Color::CYAN		= 3;
const int Color::RED		= 4;
const int Color::MAGENTA	= 5;
const int Color::BROWN		= 6;
const int Color::GRAY		= 7;
const int Color::LIGHTGRAY	= 8;
const int Color::LIGHTBLUE	= 9;
const int Color::LIGHTGREEN	= 10;
const int Color::LIGHTCYAN	= 11;
const int Color::LIGHTRED	= 12;
const int Color::LIGHTMAGENTA	= 13;
const int Color::YELLOW		= 14;
const int Color::WHITE		= 15;

int Video::Attr = Color::WHITE;

static int CursorX, CursorY;
static short *VideoRam = (short *)0xB8000;

static void SetChar(int c)
{
	VideoRam[CursorX + CursorY * 80] = ((Video::Attr << 8) & 0xff00) + (c & 0xff);
}

static void UpdateCursor()
{
	int location = (CursorY * 80 + CursorX);

	outportb(0x3d4, 0x0f);
	outportb(0x3d5, location & 0xff);

	outportb(0x3d4, 0x0e);
	outportb(0x3d5, ( location >> 8 ) & 0xff);
}

void Video::PutChar(int c)
{
	if(c == 0x08)			// Backspace erases the previous character
	{
		if(CursorX > 0)
		{
			CursorX--;

			SetChar(0);
		}
	}
	else if(c == 0x09)		// TAB moves to next field (8 chars wide)
		for(int nextPos = ((CursorX / 8) * 8) + 8; CursorX < nextPos; CursorX++)
		{
			UpdateCursor();
			SetChar(0);
		}
	else if(c == 0x0a)		// LF goes to the line below
	{
		if(CursorY >= 24)
			Scroll();
		else
			CursorY++;
	}
	else if(c == 0x0d)		// CR returns to the beginning
	{
		CursorX = 0;
	}
	else
	{
		SetChar(c);

		if(++CursorX == 80)	// CR + LF if current is full
		{
			if(CursorY >= 24)
				Scroll();
			else
				CursorY++;

			CursorX = 0;
		}
	}

	UpdateCursor();
}

void Video::SetCursor(int x, int y)
{
	if(x < 0 || x > 79 || y < 0 || y > 24)
		return;

	CursorX = x;
	CursorY = y;

	UpdateCursor();
}

void Video::Scroll()
{
	memmove(VideoRam, VideoRam + 80, 4000 - 160);

	for(int i = 2000 - 80; i < 2000; i++)
		VideoRam[i] = Attr << 8;
}

void Video::Clear()
{
	Attr = Color::GRAY;
	SetCursor(0, 0);

	for(int i = 0; i < 80 * 25; i++)
		VideoRam[i] = Color::GRAY << 8;
}

extern "C" int putchar(int c);

int putchar(int c)
{
	if(c == '\n')
		Video::PutChar('\r');

	Video::PutChar(c);

	return (unsigned int)c;
}
