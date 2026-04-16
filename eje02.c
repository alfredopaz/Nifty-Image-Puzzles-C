#include <stdio.h>
#include "simpleImage.h"

int main(void) {
  SimpleImage* image;
  int x, y, width, height;

  image = simpleImageLoad("texao.ppm");
  if(image == NULL) {
    fprintf(stderr, "No se pudo leer texao.ppm\n");
    return 1;
  }

  width = simpleImageGetWidth(image);
  height = simpleImageGetHeight(image);
  
  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      simpleImageSetGreen(image, x, y, 0);
      simpleImageSetBlue(image, x, y, 0);
    }
  }

  if(!simpleImageSave(image, "texao_no_green_blue.ppm")) {
    fprintf(stderr, "No se pudo guardar texao_no_green_blue.ppm\n");
    simpleImageDestroy(image);
    return 1;
  }

  simpleImageDestroy(image);
  printf("Imagen guardada en texao_no_green_blue.ppm\n");
  return 0;
}


