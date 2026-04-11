#include <stdio.h>
#include "simpleImage.h"

int main(void) {
  SimpleImage* image;

  image = simpleImageLoad("flowers.ppm");
  if(image == NULL) {
    fprintf(stderr, "No se pudo leer flowers.ppm\n");
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

  if(!simpleImageSave(image, "flowers_no_red.ppm")) {
    fprintf(stderr, "No se pudo guardar flowers_no_red.ppm\n");
    simpleImageDestroy(image);
    return 1;
  }

  simpleImageDestroy(image);
  printf("Imagen guardada en flowers_no_red.ppm\n");
  return 0;
}
