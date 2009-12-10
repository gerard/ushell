/*-----------------------------------------------------+      
 |     R E D I R E C C I O N . C                       |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :                           |
 |     Asignatura :  SO2                               |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/
#include "defines.h"
#include "redireccion.h"

int maxfds=3;

struct cmdfd
{
  int infd;	
  int outfd;
}cmdfd[PIPELINE];

int pipeline(int ncmd, char * infile, char * outfile, int append, int bgnd) {	
	int i, fd;
	int descr[2];
	
	redireccion_ini();
	
	/*Entrada*/
	if(strcmp(infile, "\0")) {
		if(bgnd)
			cmdfd[0].infd=open("/dev/null", O_RDONLY);
		else if(strcmp(infile, "-")) { /*Leemos de la stdin*/
			cmdfd[0].infd=open(infile, O_RDONLY);
			maxfds++;
		}
	}
	
	/*Tubos*/
	for(i=1; i<ncmd; i++) {
		if(pipe(descr)) {
			perror("No se pudo hacer pipe()");
			return 0;
		}
		cmdfd[i-1].outfd=descr[1];
		cmdfd[i].infd=descr[0];
		maxfds+=2;
	}
	
	/*Salida*/
	if(strcmp(outfile, "\0")) {
		if(strcmp(outfile, "-")) { /*Si no, usamos la stdout*/
			if(append) {
				if((fd=open(outfile, O_WRONLY | O_APPEND, 0666))==-1) perror("Error");
				else cmdfd[i-1].outfd=fd;
			} else {
				if((fd=open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666))==-1) perror("Error");
				else {
					cmdfd[i-1].outfd=fd;
					maxfds++;
				}
			}
		}
	}
	return 1;	
} /* pipeline */

int redirigir_ent(int i)
{
	if(cmdfd[i].infd==0) return 0;
	if(dup2(cmdfd[i].infd, 0)==-1) return 0;
	return 1;
} /* redirigir_ent */

int redirigir_sal(int i)
{
	if(cmdfd[i].outfd==1) return 0;
	if(dup2(cmdfd[i].outfd, 1)==-1) return 0;
	return 1;
} /* redirigir_sal */

int cerrar_fd()
{
	int i;
	/*for(i=3; i<=maxfds; i++) {
		
		close(i);
	}*/
	for(i=0; i<PIPELINE; i++) {
		if(cmdfd[i].infd>2) close(cmdfd[i].infd);
		if(cmdfd[i].outfd>2) close(cmdfd[i].outfd);
	}
} /* cerrar_fd */

void redireccion_ini() {
	int i;
	
	for(i=0; i<PIPELINE; i++) {
		cmdfd[i].outfd=1;
		cmdfd[i].infd=0;
	}
} /* redireccion_ini */

int r_entrada(char *s)
{
/*	int fin;

	if(fin=open(s, O_RDONLY)==-1) {
		perror("El fichero no existe");
		exit(1);
	}
	cmdfd[0].infd=fin;*/
} /* r_entrada */


int r_salida(char *s, int append)
{
       
} /* r_salida */
