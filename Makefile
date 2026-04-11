# Compilador y flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

# Regla general:
# make nombre  -> compila nombre.c y genera ejecutable nombre
%: %.c simpleImage.c
	$(CC) $(CFLAGS) $^ -o $@

# Limpieza
clean:
	rm -f *.o 
