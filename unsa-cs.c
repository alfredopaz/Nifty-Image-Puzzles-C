#include <stdio.h>
#include "simpleImage.h"

int main(void) {
  SimpleImage* image;
  int x, y, width, height;

  image = simpleImageLoad("unsa-cs.ppm");
  if(image == NULL) {
    fprintf(stderr, "No se pudo leer unsa-cs.ppm\n");
    return 1;
  }

  width = simpleImageGetWidth(image);
  height = simpleImageGetHeight(image);
  
  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      int red = simpleImageGetRed(image, x, y);
      int green = simpleImageGetGreen(image, x, y);
      int blue = simpleImageGetBlue(image, x, y);
      int avg = (red + green + blue) / 3;
      simpleImageSetRed(image, x, y, avg);
      simpleImageSetGreen(image, x, y, avg);
      simpleImageSetBlue(image, x, y, avg);
    }
  }

  if(!simpleImageSave(image, "unsa-cs_bw.ppm")) {
    fprintf(stderr, "No se pudo guardar unsa-cs_bw.ppm\n");
    simpleImageDestroy(image);
    return 1;
  }

  simpleImageDestroy(image);
  printf("Imagen guardada en flowers_no_green_three_fourths.ppm\n");
  return 0;
}


