#include <stdio.h>
#include "simpleImage.h"

int main(void) {
  SimpleImage* image;
  int x, y, width, height;

  image = simpleImageLoad("flowers.ppm");
  if(image == NULL) {
    fprintf(stderr, "No se pudo leer flowers.ppm\n");
    return 1;
  }

  width = simpleImageGetWidth(image);
  height = simpleImageGetHeight(image);
  
  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      int green = simpleImageGetGreen(image, x, y);
      simpleImageSetGreen(image, x, y, green * 0.75);
    }
  }

  if(!simpleImageSave(image, "flowers_no_green_three_fourths.ppm")) {
    fprintf(stderr, "No se pudo guardar flowers_no_green_three_fourths.ppm\n");
    simpleImageDestroy(image);
    return 1;
  }

  simpleImageDestroy(image);
  printf("Imagen guardada en flowers_no_green_three_fourths.ppm\n");
  return 0;
}


