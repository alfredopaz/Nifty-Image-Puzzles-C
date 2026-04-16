# SimpleImage (versión en C con PPM)

## Descripción

SimpleImage es una biblioteca en C para manipulación básica de imágenes RGB, portada de [Nifty Image Puzzles](http://nifty.stanford.edu/2011/parlante-image-puzzle/) de Nick Parlante.
Permite cargar, crear, modificar y guardar imágenes utilizando el formato PPM.

Está diseñada con fines educativos para:
- entender el manejo de memoria en C
- trabajar con arreglos y punteros
- manipular imágenes a nivel de píxel

## Formato soportado

Lectura, escritura:
- P3 (ASCII)

## Estructura de datos

width × height × 3 bytes (RGB)

Cada píxel:
- Red
- Green
- Blue

## Archivos

- simpleImage.h
- simpleImage.c
- Makefile
- eje01.c

## Compilación
```bash
make eje01
```
## Ejecución
```bash
./ eje01
xdg-open texao\_no\_red.ppm
```
## Código básico

### Cargar imagen
```c
SimpleImage* image = simpleImageLoad("texao.ppm");
```

### Crear imagen
```c
SimpleImage* image = simpleImageCreate(256, 256);
```

### Dimensiones
```c
int width = simpleImageGetWidth(image);
int height = simpleImageGetHeight(image);
```

### Leer píxel
```c
int r = simpleImageGetRed(image, x, y);
int g = simpleImageGetGreen(image, x, y);
int b = simpleImageGetBlue(image, x, y);
```

### Modificar píxel
```c
simpleImageSetRed(image, x, y, 0);
```

### Guardar
```c
simpleImageSave(image, "output.ppm");
```

### Liberar memoria
```c
simpleImageDestroy(image);
```

## Ejemplo
```c
#include <stdio.h>
#include "simpleImage.h"

int main(void) {
  SimpleImage* image;
  int x, y, width, height;

  image = simpleImageLoad("texao.ppm");
  if(image == NULL) {
    fprintf(stderr, "Error al cargar la imagen\n");
    return 1;
  }

  width = simpleImageGetWidth(image);
  height = simpleImageGetHeight(image);

  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      simpleImageSetRed(image, x, y, 0);
    }
  }

  simpleImageSave(image, "texao_no_red.ppm");
  simpleImageDestroy(image);

  return 0;
}
```

## Conversión de imágenes

Usa ImageMagick:
```bash
convert input.jpg -compress none -define ppm:format=plain output.ppm
```
## Notas

- Solo maxValue = 255
- Manejo básico de errores
- Liberar memoria manualmente

## Objetivo

Aprender:
- memoria
- punteros
- estructuras de datos
- representación de imágenes con bits
