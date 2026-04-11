#include <stdio.h>
#include "simpleImage.h"

int main(void) {
  SimpleImage* image;
  int x, y, width, height;

  image = simpleImageLoad("stop.ppm");
  if(image == NULL) {
    fprintf(stderr, "No se pudo leer stop.ppm\n");
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

      if(red > avg){
        simpleImageSetRed(image, x, y, 0);
        simpleImageSetBlue(image, x, y, 255);
      }
    }
  }

  if(!simpleImageSave(image, "stop_blue_for_red.ppm")) {
    fprintf(stderr, "No se pudo guardar stop_blue_for_red.ppm\n");
    simpleImageDestroy(image);
    return 1;
  }

  simpleImageDestroy(image);
  printf("Imagen guardada en stop_blue_for_red.ppm\n");
  return 0;
}


