#include "simpleImage.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SimpleImage {
  int width;
  int height;
  int channels;
  unsigned char* data;
};

static unsigned char clamp(int value) {
  if(value < 0) {
    return 0;
  }
  if(value > 255) {
    return 255;
  }
  return (unsigned char) value;
}

static int isValidCoordinate(const SimpleImage* image, int x, int y) {
  if(image == NULL) {
    return 0;
  }
  return x >= 0 && x < image->width && y >= 0 && y < image->height;
}

static unsigned char* pixelAt(SimpleImage* image, int x, int y) {
  if(!isValidCoordinate(image, x, y)) {
    return NULL;
  }
  return image->data + ((y * image->width + x) * image->channels);
}

static const unsigned char* pixelAtConst(const SimpleImage* image, int x, int y) {
  if(!isValidCoordinate(image, x, y)) {
    return NULL;
  }
  return image->data + ((y * image->width + x) * image->channels);
}

static int skipWhitespaceAndComments(FILE* file) {
  int c;

  do {
    c = fgetc(file);
    if(c == '#') {
      do {
        c = fgetc(file);
      } while(c != '\n' && c != EOF);
    }
  } while(isspace(c));

  if(c != EOF) {
    ungetc(c, file);
  }

  return c != EOF;
}

static int readIntToken(FILE* file, int* value) {
  if(!skipWhitespaceAndComments(file)) {
    return 0;
  }
  return fscanf(file, "%d", value) == 1;
}

SimpleImage* simpleImageCreate(int width, int height) {
  SimpleImage* image;
  size_t totalBytes;

  if(width <= 0 || height <= 0) {
    return NULL;
  }

  image = (SimpleImage*) malloc(sizeof(SimpleImage));
  if(image == NULL) {
    return NULL;
  }

  image->width = width;
  image->height = height;
  image->channels = 3;

  totalBytes = (size_t) width * (size_t) height * (size_t) image->channels;
  image->data = (unsigned char*) calloc(totalBytes, sizeof(unsigned char));
  if(image->data == NULL) {
    free(image);
    return NULL;
  }

  return image;
}

void simpleImageDestroy(SimpleImage* image) {
  if(image == NULL) {
    return;
  }
  free(image->data);
  free(image);
}

SimpleImage* simpleImageLoad(const char* filename) {
  FILE* file;
  SimpleImage* image;
  char magic[3] = {0};
  int width;
  int height;
  int maxValue;
  int x;
  int y;

  if(filename == NULL) {
    return NULL;
  }

  file = fopen(filename, "r");
  if(file == NULL) {
    return NULL;
  }

  if(fscanf(file, "%2s", magic) != 1 || strcmp(magic, "P3") != 0) {
    fclose(file);
    return NULL;
  }

  if(!readIntToken(file, &width) || !readIntToken(file, &height) || !readIntToken(file, &maxValue)) {
    fclose(file);
    return NULL;
  }

  if(width <= 0 || height <= 0 || maxValue != 255) {
    fclose(file);
    return NULL;
  }

  image = simpleImageCreate(width, height);
  if(image == NULL) {
    fclose(file);
    return NULL;
  }

  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      int red;
      int green;
      int blue;
      unsigned char* pixel;

      if(!readIntToken(file, &red) || !readIntToken(file, &green) || !readIntToken(file, &blue)) {
        simpleImageDestroy(image);
        fclose(file);
        return NULL;
      }

      pixel = pixelAt(image, x, y);
      pixel[0] = clamp(red);
      pixel[1] = clamp(green);
      pixel[2] = clamp(blue);
    }
  }

  fclose(file);
  return image;
}

int simpleImageGetWidth(const SimpleImage* image) {
  if(image == NULL) {
    return 0;
  }
  return image->width;
}

int simpleImageGetHeight(const SimpleImage* image) {
  if(image == NULL) {
    return 0;
  }
  return image->height;
}

int simpleImageGetRed(const SimpleImage* image, int x, int y) {
  const unsigned char* pixel = pixelAtConst(image, x, y);
  if(pixel == NULL) {
    return 0;
  }
  return pixel[0];
}

int simpleImageGetGreen(const SimpleImage* image, int x, int y) {
  const unsigned char* pixel = pixelAtConst(image, x, y);
  if(pixel == NULL) {
    return 0;
  }
  return pixel[1];
}

int simpleImageGetBlue(const SimpleImage* image, int x, int y) {
  const unsigned char* pixel = pixelAtConst(image, x, y);
  if(pixel == NULL) {
    return 0;
  }
  return pixel[2];
}

void simpleImageSetRed(SimpleImage* image, int x, int y, int value) {
  unsigned char* pixel = pixelAt(image, x, y);
  if(pixel == NULL) {
    return;
  }
  pixel[0] = clamp(value);
}

void simpleImageSetGreen(SimpleImage* image, int x, int y, int value) {
  unsigned char* pixel = pixelAt(image, x, y);
  if(pixel == NULL) {
    return;
  }
  pixel[1] = clamp(value);
}

void simpleImageSetBlue(SimpleImage* image, int x, int y, int value) {
  unsigned char* pixel = pixelAt(image, x, y);
  if(pixel == NULL) {
    return;
  }
  pixel[2] = clamp(value);
}

int simpleImageSave(const SimpleImage* image, const char* filename) {
  FILE* file;
  int x;
  int y;

  if(image == NULL || filename == NULL) {
    return 0;
  }

  file = fopen(filename, "w");
  if(file == NULL) {
    return 0;
  }

  fprintf(file, "P3\n");
  fprintf(file, "%d %d\n", image->width, image->height);
  fprintf(file, "255\n");

  for(y = 0; y < image->height; y++) {
    for(x = 0; x < image->width; x++) {
      const unsigned char* pixel = pixelAtConst(image, x, y);
      fprintf(file, "%d %d %d", pixel[0], pixel[1], pixel[2]);
      if(x + 1 < image->width) {
        fprintf(file, "   ");
      }
    }
    fprintf(file, "\n");
  }

  fclose(file);
  return 1;
}

const unsigned char* simpleImageGetData(const SimpleImage* image) {
  if(image == NULL) {
    return NULL;
  }
  return image->data;
}
