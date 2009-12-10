/*-----------------------------------------------------+      
 |     R E D I R E C C I O N . H                       |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :  Joan Vila                         |
 |     Asignatura :  SO2                               |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/

#ifndef REDIRECCION_H
#define REDIRECCION_H


/*-----------------------------------------------------+
 |     FASE 1                                          |
 +-----------------------------------------------------*/


/*************************************************************************/
/*                       redireccion_ini                                  */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRIPCION:                                                          */
/* Inicializa la redireccion.                                            */
/*                                                                       */
/* ENTRADA: void                                                         */
/*                                                                       */
/* SALIDA: OK o ERROR                                                    */
/*                                                                       */
/* IMPORTANTE:                                                           */
/* * La iniciacion solo es necesaria si se invocan funciones de la fase 2*/
/* sin introducir un pipeline en la fase 1.                              */
/*                                                                       */
/*************************************************************************/

extern void redireccion_ini(void);


/*************************************************************************/
/*                      pipeline                                         */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRIPCION:                                                           */
/* Crea los tubos necesarios (n-1) para ejecutar n ordenes en tubería y  */ 
/* redirige la STD_INPUT y STD_OUTPUT de un proceso.                     */
/* Deben especificarse redirecciones de entrada, de salida y background. */
/*                                                                       */
/* ENTRADA:                                                              */
/* nmcd: numero de ordenes del pipe.                                     */
/* infile: fichero a donde se redirecciona la STD_INPUT.                 */
/* outfile: fichero a donde se redirecciona la STD_OUTPUT.               */
/* append: (TRUE o FALSE) indica si el fichero al que se redirecciona la */
/* salida standard se añade la salida al final o debe ser sobreescrito.  */
/* bgnd: (TRUE o FALSE) indica si la instruccion se ejecuta en modo      */
/* background.                                                           */
/*                                                                       */
/* SALIDA: OK o ERROR.                                                   */
/*                                                                       */
/*************************************************************************/



extern int pipeline(int ncmd, char * infile, char * outfile, int append, int bgnd);


/*-----------------------------------------------------+
 |     FASE 2                                          |
 +-----------------------------------------------------*/


/*************************************************************************/
/*                       redirigir_ent                                   */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRPCION:                                                           */
/* Redirige la STD_INPUT del proceso i al descriptor fd del tubo/fichero */
/* correspondiente de la tuberia.                                        */
/*                                                                       */
/* ENTRADA: entero que identifica el proceso                             */
/*                                                                       */
/* SALIDA: OK o ERROR                                                    */
/*                                                                       */
/*************************************************************************/

extern int redirigir_ent(int i);

/*************************************************************************/
/*                       redirigir_sal                                   */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRPCION:                                                           */
/* Redirige la STD_OUTPUT del proceso i al descriptor fd del tubo/fichero*/
/* correspondiente de la tuberia.                                        */
/*                                                                       */
/* ENTRADA: entero que identifica el proceso                             */
/*                                                                       */
/* SALIDA: OK o ERROR                                                    */
/*                                                                       */
/*************************************************************************/

extern int redirigir_sal(int i);


/*-----------------------------------------------------+
 |     FASE 3                                          |
 +-----------------------------------------------------*/



/*************************************************************************/
/*                       cerrar_fd                                       */
/*-----------------------------------------------------------------------*/
/*                                                                       */
/* DESCRPCION:                                                           */
/* Cierra los descriptores fd de los tubos creados con pipeline.         */
/*                                                                       */
/* ENTRADA: void                                                         */
/*                                                                       */
/* SALIDA: OK o ERROR                                                    */
/*                                                                       */
/* IMPORTANTE:                                                           */
/* * Es imprescindible cerrar TODOS los descriptores de fichero creados  */
/* o heredados de pipeline que no van a utilizarse.                      */
/* Mientras no se cierren todos los fd de escritura sobre el tubo, el    */
/* lector del tubo no recibirá EOF y permanecerá esperando más datos.    */ 
/* * El padre debe invocarlo despues de crear todos los hijos.           */
/* Los hijos deben invocarlo depues de redirigir STD_INPUT y STD_OUTPUT  */
/*                                                                       */
/*************************************************************************/


extern int cerrar_fd(void);


#endif

