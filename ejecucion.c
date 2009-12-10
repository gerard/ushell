/*-----------------------------------------------------+      
 |     E J E C U C I O N . C                           |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :                           |
 |     Asignatura :  SO2                               |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/
#include <signal.h>
#include <sys/wait.h>

#include "defines.h"
#include "redireccion.h"
#include "ejecucion.h"


int ejecutar (int nordenes , int *nargs , char **ordenes , char ***args , int bgnd)
{
	int i, stat, pid[PIPELINE], pid2=1;
	struct sigaction sig;
	
	for(i=0; i<nordenes; i++) {
		pid[i]=fork();
		if(pid[i]==0) { /*Fill*/
			redirigir_ent(i);
			redirigir_sal(i);
			cerrar_fd();

			/* Senyals */			
			sigemptyset(&sig.sa_mask);
      		sig.sa_flags=0;
      		if(sigaction(SIGINT, NULL, &sig)!=-1) {
			    if(bgnd==1) {
      				sig.sa_handler=SIG_IGN;
    				sigaction(SIGINT,&sig,NULL);
    				sigaction(SIGQUIT,&sig,NULL);
    				}
    			else {
      				sig.sa_handler=SIG_DFL;
      				sigaction(SIGINT,&sig,NULL);
      				sigaction(SIGQUIT,&sig,NULL);
    			}
			}

			execvp(ordenes[i], args[i]);
			printf("No se consiguó ejecutar %s\n", ordenes[i]);
			cerrar_fd();
			exit(1);
		}
		/*Pare*/
	}

	if(!bgnd) {
		for(i=0; i<nordenes; i++) {
			waitpid(pid[i], &stat, 0);
			cerrar_fd();
		}
		while(pid2>0) {
			pid2=waitpid(-1, &stat, WNOHANG);
			cerrar_fd();
		}	
	}
	cerrar_fd();
} /* ejecutar */
