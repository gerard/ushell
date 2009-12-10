/*-----------------------------------------------------+
 |     U S H. C                                        |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :                          |
 |     Asignatura :  SO2                               |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/

#include <signal.h>
#include "defines.h"
#include "analizador.h"
#include "redireccion.h"
#include "ejecucion.h"


/****************************************************************/
/*                       visualizar                             */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCION:                                                 */
/* Visualiza los distintos argumentos de la orden analizada.    */
/* Util para depuracion.                                        */
/*                                                              */
/* ENTRADA: void                                                */
/*                                                              */
/* SALIDA: void                                                 */
/*                                                              */
/****************************************************************/

char buffer[MAXLINE];
char current[MAXLINE];



void visualizar() {  
	int i, j;
	int *numarg;
	char ***argumentos;
	char **ordenes;
	char fent[MAXLINE];
	char fsal[MAXLINE];
	
	if(analizar(buffer)==ERROR) printf("Error de analisis\n");
	/* Analisis con éxito */
	else {
		numarg=num_argumentos();
		argumentos=get_argumentos();
		ordenes=get_ordenes();
		
		/*Argumentos y ordenes*/
		for(i=0; i<num_ordenes(); i++) {
			printf("Orden: %s\n", ordenes[i]);
			printf("Número de argumentos: %d\n", numarg[i]-1);
			printf("Argumentos: ");
			for(j=1; j<numarg[i]; j++) 	printf("%s ", argumentos[i][j]);
			printf("\n-----\n");
		}
		printf("\n");
		
		/*Ficheros y estados*/
		strcpy(fent, fich_entrada());
		strcpy(fsal, fich_salida());
		
		if(fent[0]!='\0') printf("Fichero de entrada: %s\n", fich_entrada());
		else printf("No hay fichero de entrada\n");

		if(fsal[0]!='\0') printf("Fichero de salida: %s\n", fich_salida());
		else printf("No hay fichero de salida\n");
		
		if(fsal[0]!='\0') {
			if(es_append()) printf("Ordenes analizadas añadidas al fichero\n");
			else printf("Las ordenes truncarán el fichero\n");
		}
		
		if(es_background()) printf("Orden en background\n");
		else printf("Orden en primer plano\n");

		printf("\n");
	}
} /* visualizar */


char * getline();
void cdexec(char ***ordres, int *narg, char *current);

int main(int argc, char * argv[]) {
	char *linia;
	
	if(argc==3 && argv[1][0]=='-' && argv[1][1]=='c') {
		/*printf("Arguments\n");*/
		if(strlen(argv[2])>=MAXLINE) {
			printf("Excesivo número de carácteres\n");
			exit(1);
		}
		
		/* Ejecución de la orden */
		argv[2][strlen(argv[2])]='\n';
		argv[2][strlen(argv[2])+1]='\0';
		analizar(argv[2]);

		pipeline(num_ordenes(), fich_entrada(), fich_salida(), es_append(), es_background());
		ejecutar(num_ordenes(), num_argumentos(), get_ordenes(), get_argumentos(), es_background());
		
		exit(0);
	}

	if(argc!=1) {
		printf("Parámetros erróneos\nUSO: -c \"comando\"\n", argv[1]);
		exit(1);
	}

	getcwd(current, MAXLINE);
	
    fprintf(stdout, LOGO);
    while(1) {
		
		linia=getline();
		analizar(linia);
		
		/*printf("Analizadas %d ordenes\n", num_ordenes());*/

		struct sigaction senyal;
		char **ordres;
		
		sigemptyset(&senyal.sa_mask);
		senyal.sa_flags=0;
    	if(sigaction(SIGINT, NULL, &senyal)!=-1) {
			senyal.sa_handler=SIG_IGN;
			sigaction(SIGINT, &senyal, NULL);
			sigaction(SIGQUIT, &senyal, NULL);
			sigaction(SIGTTIN, &senyal, NULL);
			sigaction(SIGTTOU, &senyal, NULL);
		}
		
		ordres=get_ordenes();

		if(num_ordenes()==0) continue;

		if(!strcmp(ordres[0],"exit")) exit(0);
		
		if(!strcmp(ordres[0],"cd")) cdexec(get_argumentos(), num_argumentos(), current);
		else {
			pipeline(num_ordenes(), fich_entrada(), fich_salida(), es_append(), es_background());
			ejecutar(num_ordenes(), num_argumentos(), get_ordenes(), get_argumentos(), es_background());
			/*visualizar();*/
			/*printf("Command: %s", buffer); */
		}
	}
	return 0;
} /* main */

void cdexec(char ***ordres, int *narg, char *current) {
	char aux[MAXLINE];
	
	/* Comprovació d'errors */
	if(narg[0]>2) {
		fprintf(stderr, "El comandament cd només requereix un paràmetre");
		return;
	}
	if(narg[0]==1) {
		getcwd(current, MAXLINE);
		chdir((char *)getenv("HOME"));
		return;
	}

	if(!strcmp(ordres[0][1], "-")) {
		getcwd(aux, MAXLINE);
		chdir(current);
		strcpy(current, aux);
		return;
	}
	
	getcwd(current, MAXLINE);
	chdir(ordres[0][1]);
}

char * getline() {
	char dir[MAXLINE];
	int i;
	
	/*Mostrar prompt*/
	getcwd(dir, MAXLINE);
	printf("%s %s", dir, PROMPT);
	
	/*Getline*/
	for(i=0; (buffer[i]=getchar())!='\n' && i<MAXLINE; i++) {
		if(buffer[i]==EOF) {
			printf("logout\n");
			exit(0);
		}
	}
	
	buffer[i+1]='\0';
	return buffer;
} /* getline */

