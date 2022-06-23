#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME 25

/* image data*/
unsigned char* image;
/* header variables */
unsigned short signature; // 4D42
unsigned long sizeByte; // size in bytes
unsigned long reserved; // zero
unsigned long startOffset; // in bytes
unsigned long sizeOfInfo; // sizeof bitmapinfoheader, 40
long imageWidth; // in pixels
long imageHeigth; // in pixels
unsigned short numberOfPlanes; // must be 1
unsigned short bitsPerPixel; // 1,4,8 or 24
unsigned long compressionType; // (0 = none, 1 = RLE-8, 2 = RLE -4 )
unsigned long sizeOfImageData; // int bytes
long horizontalResolution; 
unsigned long verticalResolution;
unsigned long numberOfColours; // or zero
unsigned long numberOfImportantColours; // or zero

/* extern functions */
extern "C"
{
	void grayscale(unsigned char *image, int image_size);
	void rotate(unsigned char *image, int image_size);
	void clear(unsigned char *image, int width, int height, int val);
	void grow(unsigned char *image, unsigned char *newimage, int width, int height);
	void invert(unsigned char *image, int width, int height);
	void brightness(unsigned char *image, int width, int height, int val);
	void contrast(unsigned char *image, int width, int height, int val);
	void shrink(unsigned char *image, unsigned char *newimage, int width, int height);
	void blur(unsigned char *image, int width, int height);
	int atleast(unsigned char *image, int width, int height, int val);
}