#include <stdio.h>
#include "simpleImage.h"

int main(void) {
  SimpleImage* image;

  image = simpleImageLoad("texao.ppm");
  if(image == NULL) {
    fprintf(stderr, "No se pudo leer texao.ppm\n");
    return 1;
  }

  int width = simpleImageGetWidth(image);
  int height = simpleImageGetHeight(image);

  int y = 0;
  while(y < height) {
    int x = 0;
    while(x < width) {
      simpleImageSetRed(image, x, y, 0);
      x++;
    }
    y++;
  }

  if(!simpleImageSave(image, "texaoNoRed.ppm")) {
    fprintf(stderr, "No se pudo guardar texaoNoRed.ppm\n");
    simpleImageDestroy(image);
    return 1;
  }

  simpleImageDestroy(image);
  printf("Imagen guardada en texaoNoRed.ppm\n");
  return 0;
}



