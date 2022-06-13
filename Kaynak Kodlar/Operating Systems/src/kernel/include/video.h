#ifndef __VIDEO_H
#define __VIDEO_H

class Color
{
private:
	Color() { }

public:
	static const int BLACK;
	static const int BLUE;
	static const int GREEN;
	static const int CYAN;
	static const int RED;
	static const int MAGENTA;
	static const int BROWN;
	static const int GRAY;
	static const int LIGHTGRAY;
	static const int LIGHTBLUE;
	static const int LIGHTGREEN;
	static const int LIGHTRED;
	static const int LIGHTCYAN;
	static const int LIGHTMAGENTA;
	static const int YELLOW;
	static const int WHITE;

	static const int BLINK;

	static const int BG_BLACK;
	static const int BG_BLUE;
	static const int BG_GREEN;
	static const int BG_CYAN;
	static const int BG_RED;
	static const int BG_MAGENTA;
	static const int BG_BROWN;
	static const int BG_GRAY;
};

class Video
{
private:
	Video() { }

public:
	static int Attr;

	static void PutChar(int c);
	static void Clear();
	static void SetCursor(int x, int y);
	static void GetCursor(int& x, int& y);
	static void Scroll();
};

#endif
