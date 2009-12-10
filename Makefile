all: ush

todo: ush

ush: ush.c defines.h analizador.h redireccion.h analizador.o redireccion.o ejecucion.o
	gcc ush.c analizador.o redireccion.o ejecucion.o -o ush -g

analizador.o: analizador.c defines.h
	gcc -c analizador.c -g

redireccion.o: redireccion.c defines.h
	gcc -c redireccion.c -g

ejecucion.o: ejecucion.c defines.h analizador.c redireccion.h
	gcc -c ejecucion.c -g

clean:
	rm *.o ush


