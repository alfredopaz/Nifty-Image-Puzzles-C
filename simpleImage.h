#ifndef SIMPLEIMAGE_H
#define SIMPLEIMAGE_H

#include <stddef.h>

typedef struct SimpleImage SimpleImage;

SimpleImage* simpleImageLoad(const char* filename);
SimpleImage* simpleImageCreate(int width, int height);
void simpleImageDestroy(SimpleImage* image);

int simpleImageGetWidth(const SimpleImage* image);
int simpleImageGetHeight(const SimpleImage* image);

int simpleImageGetRed(const SimpleImage* image, int x, int y);
int simpleImageGetGreen(const SimpleImage* image, int x, int y);
int simpleImageGetBlue(const SimpleImage* image, int x, int y);

void simpleImageSetRed(SimpleImage* image, int x, int y, int value);
void simpleImageSetGreen(SimpleImage* image, int x, int y, int value);
void simpleImageSetBlue(SimpleImage* image, int x, int y, int value);

int simpleImageSave(const SimpleImage* image, const char* filename);
const unsigned char* simpleImageGetData(const SimpleImage* image);

#endif
