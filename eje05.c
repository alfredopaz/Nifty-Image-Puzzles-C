#include <stdio.h>
#include "simpleImage.h"

int main(void) {
  SimpleImage* imageStop, *imageLeaves;

  imageStop = simpleImageLoad("stop.ppm");
  if(imageStop == NULL) {
    fprintf(stderr, "No se pudo leer stop.ppm\n");
    return 1;
  }

  imageLeaves = simpleImageLoad("leaves.ppm");
  if(imageLeaves == NULL) {
    fprintf(stderr, "No se pudo leer leaves.ppm\n");
    return 1;
  }

  int wStop = simpleImageGetWidth(imageStop);
  int hStop = simpleImageGetHeight(imageStop);
  
  int x, y;
  for(y = 0; y < hStop; y++) {
    for(x = 0; x < wStop; x++) {
      int red = simpleImageGetRed(imageStop, x, y);
      int green = simpleImageGetGreen(imageStop, x, y);
      int blue = simpleImageGetBlue(imageStop, x, y);
      int avg = (red + green + blue) / 3;

      avg = avg * 1.5;
      if(red > avg){
        simpleImageSetRed(imageStop, x, y, simpleImageGetRed(imageLeaves, x, y));
        simpleImageSetGreen(imageStop, x, y,simpleImageGetGreen(imageLeaves, x, y));
        simpleImageSetBlue(imageStop, x, y, simpleImageGetBlue(imageLeaves, x, y));
      }
    }
  }

  if(!simpleImageSave(imageStop, "redScreen.ppm")) {
    fprintf(stderr, "No se pudo guardar redScreen.ppm\n");
    simpleImageDestroy(imageStop);
    simpleImageDestroy(imageLeaves);
    return 1;
  }

  simpleImageDestroy(imageStop);
  simpleImageDestroy(imageLeaves);

  printf("Imagen guardada en redScreen.ppm\n");
  return 0;
}


