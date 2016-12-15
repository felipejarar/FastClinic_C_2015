/*****************************************************************************************************************

       @file Pacientes.c
       @brief Archivo que contiene todas las funciones que relacionadas con la estructura Paciente
       @author Felipe Ignacio Jara Ramirez (nialevolstel)
       @version 1.0
       @date 18 de Septiembre del 2014

*******************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../Estructuras/Estructuras.h"
#include "General.h"
#include "Pacientes.h"

/**
    @def ARCHIVO_PACIENTES
    @brief Contiene la ruta en donde se encuentra la base de datos correspondiente a los pacientes.

    @def COLUMNAS_PACIENTES
    @brief Contiene la cantidad de elementos diferentes que estructuran la base de datos correspondiente a los pacientes

    @def REFERENCIA_PACIENTES
    @brief Contiene una referencia utilizada para realizar un conteo de la cantidad de pacientes contenidos en su respectiva
    base de datos. Es utilizado en la funcion  contadorDeDatos() declarada en el archivo General.c
*/

#define ARCHIVO_PACIENTES "Bases de Datos/Paciente.txt"
#define COLUMNAS_PACIENTES 6
#define REFERENCIA_PACIENTES 0




                        /*****************************************************************************************
                                                             _                  _
                                                            (_)                | |
                                      _ __     __ _    ___   _    ___   _ __   | |_    ___   ___
                                     | '_ \   / _` |  / __| | |  / _ \ | '_ \  | __|  / _ \ / __|
                                     | |_) | | (_| | | (__  | | |  __/ | | | | | |_  |  __/ \__ \
                                     | .__/   \__,_|  \___| |_|  \___| |_| |_|  \__|  \___| |___/
                                     | |
                                     |_|

                        *****************************************************************************************/



/**
    @brief      Funcion utilizada para obtener toda la informacion relacionada con los pacientes a partir de la lectura de su correspondiente base de datos

    @param      pacientes
    @brief      Arreglo de estructura Paciente. Parametro pasado por referencia que, tras finalizar la ejecucion de la funcion, pasa a contener
                toda la informacion relacionada con los pacientes (IdentificadorPaciente, rut, email, nombre, apellido, fecha de nacimiento) almacenada
                en la correspondiente base de datos

    @param      cantidadPacientes
                Numero entero que representa la cantidad de pacientes incluidos en la base de datos. Tambien indica la dimension del arreglo de estructura
                Paciente entregado como parametro

    @return     Numero entero que indica la existencia de errores, en el caso de que existan.
                    \n a)  Retornar 0 indica que la funcion se ha llevado a cabo correctamente.
                    \n b)  Retornar un numero diferente de 0 indica que se ha presentado una anormalidad en la funcion cuando esta fue ejecutada.
*/
int lecturaPacientes(struct Paciente pacientes[], int cantidadPacientes){

    /**
        Se obtiene el archivo (base de datos) relacionado con la informacion de los pacientes y dependiendo de si el archivo fue obtenido correctamente, se procede
        a realizar la lectura de este.
    */
    FILE* archivoPaciente = fopen(ARCHIVO_PACIENTES, "r");

    if (archivoPaciente == NULL){

        /**
            En el caso de que la apertura del archivo no haya podido llevarse a cabo correctamente, se retorna -1 indicando un error
            en la ejecucion de la funcion
        */
        return -1;

    }

    else{

        /**
            Conociendo la cantidad de pacientes que hay en la base de datos, se procede a agregar la informacion contenida en el archivo de texto
            al arreglo de structura Paciente pasado como argumento. La primera linea del archivo sirve solamente como referencia, por lo que debe
            ser ignorada
        */

        fscanf(archivoPaciente, "%*[identificador,rut,email,nombre,apellido,fecha de nacimiento] %*[\n]");

        char stringAux[DEFAULT_STRING_SIZE]; /**<   Se declara la variable local stringAux para aquellos datos, del paciente, que requieren
                                                    ser transformados a un tipo de dato int antes de ser incluidos al arreglo
                                                    de estructura Paciente (Identificador)*/

        /**
            Bajo una sentencia while y switch-case se procede a agregar al arreglo de estructura Paciente la informacion necesaria para estructurar
            a cada uno de los pacientes
        */

        int fscanfAux = 0; /**<    Se declara la variable local fscanfAux con el proposito de detener el ciclo while cuando, durante
                                    la lectura, se llega al final del archivo. Es decir, cuando fscanfAux es igual a EOF */

        int i = 0;
        int index = 0;
        while (index < cantidadPacientes && fscanfAux != EOF){

            switch(i){

                // Caso para agregar el identificador del paciente
                case 0: fgets(stringAux, 1, archivoPaciente);
                        fscanf(archivoPaciente, "%[^,]", stringAux);
                        pacientes[index].ID = atoi(stringAux);
                        i++;

                // Caso para agregar el rut del paciente
                case 1: fscanf(archivoPaciente, "%*[,] %[^,]", pacientes[index].rut);
                        i++;

                // Caso para agregar el mail del paciente
                case 2: fscanf(archivoPaciente, "%*[,] %[^,]", pacientes[index].email);
                        i++;

                // Caso para agregar el nombre del paciente
                case 3: fscanf(archivoPaciente, "%*[,] %[^,]", pacientes[index].nombre);
                        i++;

                // Caso para agregar el apellido del paciente
                case 4: fscanf(archivoPaciente, "%*[,] %[^,]", pacientes[index].apellido);
                        i++;

                // Caso para agregar la fecha de nacimiento del paciente
                case 5: fscanf(archivoPaciente, "%*[,] %[^\n] %*[\n] ", pacientes[index].fechaNacimiento);
                        i = 0;
                        index++;
            }

        }

    /**
        Se cierra el archivo y se retorna 0 para indicar que ningun error ha ocurrido
    */

    fclose(archivoPaciente);
    return 0;

    }
}

/**
    @brief          Funcion utilizada para verificar la existencia del identificador de un paciente en su respectiva base de datos

    @param          IDPaciente
    @brief          Identificador del paciente cuya existencia en la base de datos requiere ser verificada.

    @param          datos
    @brief          Arreglo de estructura Paciente que contiene toda la informacion relacionada con los pacientes en la base de datos.

    @param          cantidadDatos
    @brief          Numero entero que indica la cantidad de pacientes contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura Paciente ingresado como parametro

    @return         Numero entero que indica la existencia del identificador en la base de datos
                        \n  a)  0   :   El identificador esta en la base de datos
                        \n  b)  -1  :   El identificador no esta en la base de datos
*/
int verificarIdentificadorPaciente(int IDPaciente, struct Paciente datos[], int cantidadDatos){

    /**
        Mediante un ciclo for, se procede comparar uno por uno los identificadores pacientes presentes en la base de datos con
        el identificador paciente ingresado como parametro. Cuando un identificador de la base de datos sea igual al identificador
        ingresado como parametro, signica que el identificador ingresado si existe en la base de datos
    */

    int verificador = -1;/**<   Se declara e inicializa la variable local "verificador" con un valor de -1. En el caso de que se
                                verifique la existencia del identificador ingresado como parametro en la base de datos, este adquiere
                                un valor de 0 */
    int index;
    for (index = 0; index < cantidadDatos && verificador == -1; index++){
        if (datos[index].ID == IDPaciente){
            verificador = 0;
        }
    }

    /** Se retorna el valor de "verificador*/
    return verificador;

}

/**

    @brief          Funcion utilizada para obtener el identificacor de un paciente a traves de su rut

    @param          rut
    @brief          Rut del paciente, escrito como String, cuyo identificador se desea obtener.

    @param          pacientes
    @brief          Arreglo de estructura Paciente que contiene toda la informacion relacionada con los pacientes en la base de datos.

    @param          cantidadPacientes
    @brief          Numero entero que indica la cantidad de pacientes contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura Paciente ingresado como parametro

    @return         Identificador del paciente que se desea encontrar. En el caso de que no exista en la base de datos, se retorna -1
*/
int buscarPacientePorRut(char rut[], struct Paciente pacientes[], int cantidadPacientes){

    /** Se recurre a un ciclo for para comparar el rut ingresado como parametro con el rut de cada uno de los pacientes contenidos en la
        base de datos, uno por uno. En el caso de que el rut ingresado sea igual al rut de un paciente en la base de datos, se devuelve
        el identificador de ese paciente */

    int i;
    int ID = -1; /**<   Se declara e inicializa la variable local "ID" con el valor de -1. Si es que se encuentra el rut ingresado en la base
                        de datos, la variable toma el valor del identificador del paciente al cual el corresponde ese rut */

    for (i = 0; i < cantidadPacientes; i++){
        if (strcmp(rut, pacientes[i].rut) == 0){
             ID = pacientes[i].ID;
        }
    }

    /** Se retorna la variable local "ID" */
    return ID;
}

/**
    @brief          Funcion utilizada para obtener el identificador de un paciente a traves de su correo

    @param          correo
    @brief          Correo del paciente, escrito como String (Arreglo de char), que se desea encontrar

    @param          pacientes
    @brief          Arreglo de estructura Paciente que contiene toda la informacion relacionada con los pacientes en la base de datos.

    @param          cantidadPacientes
    @brief          Numero entero que indica la cantidad de pacientes contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura Paciente ingresado como parametro

    @return         Identificador del paciente que se desea encontrar. En el caso de que no exista en la base de datos, se retorna -1
*/

int buscarPacientePorCorreo(char correo[], struct Paciente pacientes[], int contadorPacientes){

    /** Se recurre a un ciclo for para comparar el correo ingresado como parametro con el correo de cada uno de los pacientes contenidos en la
        base de datos, uno por uno. En el caso de que el correo ingresado sea igual al correo de un paciente en la base de datos, se devuelve
        el identificador de ese paciente */

    int i;
    int ID = -1;    /**<   Se declara e inicializa la variable local "ID" con el valor de -1. Si es que se encuentra el correo ingresado en la base
                            de datos, la variable toma el valor del identificador del paciente al cual el corresponde ese correo */

    for (i = 0; i < contadorPacientes; i++){
        if (strcmp(correo, pacientes[i].email) == 0){
             ID = pacientes[i].ID;
        }
    }

    return ID;
}

/**

    @brief         Funcion utilizada para obtener el identificador de un paciente por medio de su nombre y apellido

    @param          nombre
    @brief          Nombre del paciente.

    @param          apellido
    @brief          Apellido del paciente.

    @param          pacientes
    @brief          Arreglo de estructura Paciente que contiene toda la informacion relacionada con los pacientes en la base de datos.

    @param          cantidadPacientes
    @brief          Numero entero que indica la cantidad de pacientes contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura Paciente ingresado como parametro.

    @return         Identificador del paciente que se desea encontrar. En el caso de que no exista en la base de datos, se retorna -1

*/
int buscarPacientePorNombreYApellido(char nombre[], char apellido[], struct Paciente pacientes[], int cantidadPacientes){

   /** Se recurre a un ciclo for para comparar el nombre y apellido ingresado como parametro con el nombre y apellido de cada uno de los pacientes
    contenidos en la base de datos, uno por uno. En el caso de que el nombre y apellido ingresados sean igual al nombre y apellido de un paciente
    en la base de datos, se devuelve el identificador de ese paciente */

    int i;
    int ID = -1; /**<   Se declara e inicializa la variable local "ID" con el valor de -1. Si es que se encuentra el nombre y apellido ingresado en la base
                        de datos (simultaneamente), la variable toma el valor del identificador del paciente al cual le corresponde ese nombre y apellido */

    for (i = 0; i < cantidadPacientes; i++){
        if (strcmp(pacientes[i].nombre,nombre) == 0 && strcmp(pacientes[i].apellido,apellido) == 0){
            ID = pacientes[i].ID;
        }
    }
    return ID;
}

/**

    @brief          Funcion utilizada para escribir sobre un archivo output el nombre de un paciente dado su identificador

    @param          ID
    @brief          Identificador del paciente, cuyo nombre se desea escribir en el archivo output.

    @param          pacientes
    @brief          Arreglo de estructura Paciente que contiene toda la informacion relacionada con los pacientes en la base de datos.

    @param          cantidadPacientes
    @brief          Numero entero que indica la cantidad de pacientes contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura Paciente ingresado como parametro.

    @return         Numero entero que indica la existencia de anormalidades durante la ejecucion de la funcion.
                    \n  a)  Retorna 0 si la funcion no presento ningun error durante su ejecucion
                    \n  b)  Retorna -1 si la funcion presento error durante su ejecucion. Siendo mas especifico,
                            si se presento un error al momento de abrir el archivo output.
*/
int outputNombrePaciente(int ID, struct Paciente pacientes[], int cantidadPacientes){

    /**
        Se abre el archivo output
    */

    FILE* output = fopen(ARCHIVO_OUTPUT,"a");

    /**
        En el caso de que se presente un error en la apertura del archivo, se retorna a -1
    */
    if (output == NULL){
        return -1;
    }

    else{

        /**
            En el caso de que la apertura del archivo se haya realizado correctamente, se procede a escribir sobre este
            el nombre del paciente al cual le pertenece el identificador ingresado como parametro. Para ello se recurre
            a un ciclo for para comparar uno por uno los identificadores contenidos en la base de datos con el identificador
            ingresado como parametro, hasta encontrar una similitud. Despues de haber encontrado dicha similitud, es posible
            escribir el nombre del paciente en el archivo output.
        */

        int i;
        for (i = 0; i < cantidadPacientes; i++){
            if ( ID == pacientes[i].ID){
                fprintf(output, "%s", pacientes[i].nombre);
            }
        }
        fprintf(output, "\n\n");

        /**
            Finalmente, se retorna a 0 para indicar que la funcion se llevo a cabo correctamente
        */

        return 0;
    }
}

/**

    @brief          Funcion utilizada para modificar el correo de un paciente en su respectiva base de datos

    @param          correoAntiguo
    @brief          Antiguo correo del paciente, el cual se desea modificar en la base de datos.

    @param          correoNuevo
    @brief          Nuevo correo del paciente, el cual pretende reemplazar al antiguo en la base de datos.

    @param          pacientes
    @brief          Arreglo de estructura Paciente que contiene toda la informacion relacionada con los pacientes en la base de datos.

    @param          cantidadPacientes
    @brief          Numero entero que indica la cantidad de pacientes contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura Paciente ingresado como parametro.

    @return         Numero entero que indica la presencia de errores en la ejecucion de la funcion.
                    \n  a)      Retornar 0 indica que la funcion no presento ningun error.
                    \n  b)      Retornar -1 indica que la funcion presento un error al momento de ser ejecutada.
*/
int outputModificarCorreoPaciente (char correoAntiguo[], char correoNuevo[], struct Paciente pacientes[], int cantidadPacientes){

    /**    Se realiza la apertura del archivo output.  */
    FILE* output = fopen(ARCHIVO_OUTPUT,"a");

    /**  En el caso de que se haya presentado un error al momento de realizar la apertura del archivo, se retorna -1  */
    if( output == NULL){
        return -1;
    }

    else{

        /**
            Antes de realizar cualquier modificacion en el archivo output, se revisa si el nuevo correo corresponde a un cambio valido o no. Para
            ello se declara la variable "verificadorCorreo", el cual toma un valor diferente de 0 en caso de que el nuevo correo no corresponda
            a un cambio valido
        */

        int verificadorCorreo = -1; /**<    La variable local "verificadorCorreo" se inicializa con el valor -1. Lo que significa que el cambio no es valido
                                            hasta que se demuestre lo contrario */

        /**
            Mediante un ciclo for, se recorre la informacion de todos los pacientes en la base de datos y se realiza una comparacion hasta encontrar
            un correo que sea igual al correo antiguo ingresado como parametro. De esta manera se revisa si efectivamente existe el correo que se
            desea modificar en la base de datos
        */

        int index;
        for (index = 0; index < cantidadPacientes && verificadorCorreo != 0; index++){
            if (strcmp(correoAntiguo, pacientes[index].email) == 0){
                verificadorCorreo = 0;
            }
        }

        /**
            En el caso de que no se haya podido encontrar el correo antiguo en la base de datos, se escribe en el archivo output un mensaje de error
            y se retorna a -1
        */

        if (verificadorCorreo == -1){
            fprintf(output, "ERROR!: NO ES POSIBLE ENCONTRAR EL CORREO ANTIGUO EN LA BASE DE DATOS\n\n");
            fclose(output);
            return -1;
        }

        else{

            /**
                Se procede a verificar si el correo antiguo y el correo nuevo son iguales. En tal caso, ninguna modificacion deberia ser
                efectuada  y para indicarle eso a la funcion, se le asigna el valor -2 a la variable local "verificadorCorreo"
            */
            if (strcmp(correoAntiguo, correoNuevo) == 0){
                verificadorCorreo = -2;
            }

            /**
                Si ambos correos resultaron ser diferentes, se procede a verificar que el nuevo correo no haya sido tomado por otro paciente
                en la base de datos. Para ello se recurre a un ciclo for para comparar todos los correos en la base de datos con el correo
                nuevo ingresado como parametro. En el caso de que se encuentre una similitud, se le asigna el valor -3 a la variable local
                "verificadorCorreo" para indicarle al programa de que la modificacion no puede ser efectuada
            */
            else{
                for (index = 0; index < cantidadPacientes && verificadorCorreo == 0; index++){
                    if (strcmp(correoNuevo, pacientes[index].email) == 0){
                        verificadorCorreo = -3;
                    }
                }
            }

            /**
                En el caso de que verificadorCorreo tome los valores de -2 o -3. Se escribe en el archivo output un mensaje de error y se
                retorna a -1.
            */

            if (verificadorCorreo == -2){
                fprintf(output,"ERROR!: AMBOS CORREOS INGRESADOS SON IGUALES, POR LO QUE NINGUNA MODIFICACION FUE EFECTUADA\n\n");
                fclose(output);
                return -1;
            }

            else if (verificadorCorreo == -3){
                fprintf(output, "ERROR!: EL NUEVO CORREO INGRESADO YA EXISTE EN LA BASE DE DATOS, POR LO QUE NINGUNA MODIFICACION FUE EFECTUADA\n\n");
                fclose(output);
                return -1;
            }

            else {

                /**
                    Habiendo verificado que es posible realizar la modificacion, se realiza la apertura de la base de datos
                */
                FILE* archivoPacientes = fopen(ARCHIVO_PACIENTES,"w");

                /**
                    En el caso de que se haya presentado un error al momento de realizar la apertura de la base de datos, se retorna a -1
                */
                if (archivoPacientes == NULL){
                    return -1;
                }

                else{

                    /**
                        Se recurre a un ciclo for para re-escribir la base de datos utilizando la informacion contenida en el arreglo de
                        estructura Paciente
                    */

                    int index; /**<     Se declara la variable local "index" para acceder a un paciente en el arreglo de estructuraPaciente */
                    int linea; /**<     Se declara la variable local "linea" para saber sobre que linea del archivo se esta trabajando */

                    for (linea = 0, index = -1; linea < cantidadPacientes+1; linea++, index++){

                        /**
                            En la primera linea de la base de datos se escribe la referencia, es decir, "identificador,rut,email,nombre,apellido,fecha de nacimiento"
                        */

                        if (linea == 0){
                            fprintf(archivoPacientes, "identificador,rut,email,nombre,apellido,fecha de nacimiento\n");
                        }

                        /**
                            En el resto de las lineas, se escribe la informacion de un paciente
                        */

                        else{
                            if (strcmp(pacientes[index].email, correoAntiguo) != 0){
                                fprintf(archivoPacientes,"%d,%s,%s,%s,%s,%s\n",pacientes[index].ID,pacientes[index].rut,pacientes[index].email,pacientes[index].nombre,pacientes[index].apellido,pacientes[index].fechaNacimiento);
                            }

                            else{
                                fprintf(archivoPacientes,"%d,%s,%s,%s,%s,%s\n",pacientes[index].ID,pacientes[index].rut,correoNuevo,pacientes[index].nombre,pacientes[index].apellido,pacientes[index].fechaNacimiento);
                            }
                        }

                    }

                    /**
                        Se escribe un mensaje en el archivo output, se cierra junto con la base de datos y se retorna a 0 para indicar que ningun
                        error ha ocurrido durante la ejecucion de la funcion
                    */

                    fclose(archivoPacientes);
                    fprintf(output, "El correo %s ha sido modificado a %s\n\n",correoAntiguo,correoNuevo);
                    fclose(output);
                    return 0;

                }
            }
        }
    }
}

/**

    @brief          Funcion utilizada para eliminar de la base de datos a un paciente en especifico

    @param          IDPaciente
    @brief          Identificador del paciente que se desea eliminar

    @param          datos
    @brief          Arreglo de estructura Paciente que contiene toda la informacion relacionada con los pacientes en la base de datos.

    @param          cantidadDatos
    @brief          Numero entero que indica la cantidad de pacientes contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura Paciente ingresado como parametro.

    @return         Numero entero que indica la presencia de errores en la ejecucion de la funcion.
                    \n  a)      Retornar 0 indica que la funcion no presento ningun error.
                    \n  b)      Retornar -1 indica que la funcion presento un error al momento de ser ejecutada.
*/
int outputEliminarPaciente (int IDPaciente, struct Paciente datos[], int cantidadDatos){

    /**
        Se realiza la apertura de la base de datos correspondiente a los Pacientes y del archivo output
    */

    FILE* archivoPacientes = fopen(ARCHIVO_PACIENTES, "w");
    FILE* output           = fopen(ARCHIVO_OUTPUT,"a");

    /**
        En el caso de que se presente un error en la apertura de la base de datos, se escribe un mensaje de error
        en el archivo output y se retorna a -1
    */

    if (archivoPacientes == NULL){

        if (output != NULL){
            fprintf(output, "Se ha presentado un error al momento de escribir sobre el archivo %s\n\n",ARCHIVO_PACIENTES);
        }

        fclose(output);
        return -1;
    }

    else{

        /**
            Se re-escribe la primera linea de la base de datos, el cual corresponde a una referencia
        */

        fprintf(archivoPacientes, "identificador,rut,email,nombre,apellido,fecha de nacimiento\n");

        /**
            Se recurre a un ciclo for para re-escribir la base de datos, esta vez ignorando al paciente relacionado con el
            identificador ingresado como parametro. En otras palabras, se re-escribe la informacion de un paciente en la base
            de datos solamente si su identificador es diferente al ingresado como parametro.
        */
        int index;
        for (index = 0; index < cantidadDatos; index++){
            if (datos[index].ID != IDPaciente){
                fprintf(archivoPacientes, "%d,%s,%s,%s,%s,%s\n",datos[index].ID,datos[index].rut,datos[index].email,datos[index].nombre,datos[index].apellido,datos[index].fechaNacimiento);
            }
        }

        /**
            Se escribe un mensaje en el output indicandole al usuario de que el paciente ha sido eliminado correctamente de la base de datos, se cierra el
            output junto con la base de datos y se retorna 0 para indicar que la funcion se ha ejecutado sin error alguno.
        */

        fclose(archivoPacientes);

        if (output != NULL){
            fprintf(output, "El paciente (ID = %d) ha sido eliminado correctamente\n\n",IDPaciente);
            fclose(output);
        }

        return 0;
    }
}



