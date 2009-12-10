/*-----------------------------------------------------+
 |     defines . H                                     |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :  Joan Vila                         |
 |     Asignatura :  SO2                               |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/

#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define max(a,b) (((a)>(b)) ? (a): (b))


/* Valores enteros asignados a verdadero, falso, ejcucion */
/* correcta y ejecucion con error.                        */

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

/* Longitud maxima de la linea de ordenes.             */
#define MAXLINE 200
/* Numero maximo de argumentos para cada orden simple. */
#define MAXARG 20
/* Numero maximo de ardenes simples en una linea. Nor- */
/* malmente, estaran interconectadas mediante tubos.   */
#define PIPELINE 10
/* Longitud maxima de los nombres de fichero a utilizar*/
#define MAXNAME 100
/* LOGO que aparece al empezar e ejecutar el micro shell */
#define LOGO "MICRO SHELL  (c)2004 Gerard\n"
/* Cadena que aparece como PROMPT en la linea de comandos */
#define PROMPT "ush_$ "

#endif

