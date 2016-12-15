/*****************************************************************************************************************

       @file Diagnosticos.c
       @brief Archivo que contiene todas las funciones que relacionadas con la estructura Diagnostico
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

#include "Diagnosticos.h"
       
#define ARCHIVO_DIAGNOSTICOS "Bases de Datos/Diagnostico.txt"
#define REFERENCIA_DIAGNOSTICOS 2
#define COLUMNAS_DIAGNOSTICO 3


/**
                  _   _                                         _     _
                 | | (_)                                       | |   (_)
               __| |  _    __ _    __ _   _ __     ___    ___  | |_   _    ___    ___    ___
              / _` | | |  / _` |  / _` | | '_ \   / _ \  / __| | __| | |  / __|  / _ \  / __|
             | (_| | | | | (_| | | (_| | | | | | | (_) | \__ \ | |_  | | | (__  | (_) | \__ \
              \__,_| |_|  \__,_|  \__, | |_| |_|  \___/  |___/  \__| |_|  \___|  \___/  |___/
                                   __/ |
                                  |___/
*/

/**
    @brief      Funcion utilizada para obtener toda la informacion relacionada con los diagnosticos a partir de su respectiva base de datos

    @param      diagnostico
    @brief      Arreglo de estructura Diagnostico. Parametro pasado por referencia que, tras finalizar la ejecucion de la funcion, pasa a contener
                toda la informacion relacionada con los diagnosticos (identificador,descripcionDiagnostico,nivelGravedad) almacenada
                en la correspondiente base de datos

    @param      cantidadDiagnosticos
                Numero entero que representa la cantidad de diagnosticos contenidos en la base de datos. Tambien indica la dimension del arreglo de
                estructura Diagnostico entregado como parametro

    @return     Numero entero que indica la existencia de errores, en el caso de que existan.
                    \n a)  Retornar 0 indica que la funcion se ha llevado a cabo correctamente.
                    \n b)  Retornar un numero diferente de 0 indica que se ha presentado una anormalidad en la funcion cuando esta fue ejecutada.
*/

int lecturaDiagnosticos(struct Diagnostico diagnosticos[], int cantidadDiagnosticos){

    /**     Se realiza la apertura de la base de datos, en el modo lectura, y su referencia es entregada a la variable "archivoDiagnosticos".    */
    FILE* archivoDiagnosticos = fopen(ARCHIVO_DIAGNOSTICOS, "r");

    /**     En el caso de que se haya presentado un problema al momento de realizar la apertura del archivo y se retorna a -1. */
    if (archivoDiagnosticos == NULL){
        return -1;
    }

    else{

        /**     Se realiza una lectura de la primera linea de la base de datos, la cual contiene solamente una referencia de los tipos de
                elementos contenidos en el archivo por lo que debe ser ignorada. */
        fscanf(archivoDiagnosticos, "%*[identificador,descripcionDiagnostico,nivelGravedad] *[\n]");

        char stringAux[DEFAULT_STRING_SIZE];    /**<    Se declara la variable local stringAux para aquellos datos, del diagnostico, que requieren
                                                        ser transformados a un tipo de dato int antes de ser incluidos al arreglo
                                                        de estructura Diagnostico (Identificador).*/



        /**     Mediante un ciclo while y switch-case se procede a incluir en "diagnosticos" uno por uno la informacion contenida en su
                correspondiente base de datos. */

        int fscanfAux = 0; /**<     Se declara la variable local fscanfAux con el proposito de detener el ciclo while cuando, durante
                                    la lectura, se llega al final del archivo. Es decir, cuando fscanfAux es igual a EOF */

        int i = 0;
        int index = 0;

        while (index < cantidadDiagnosticos && fscanfAux != EOF){

            switch(i){

                // Caso para agregar el identificador del diagnostico
                case 0: fgets(stringAux, 1, archivoDiagnosticos);
                        fscanf(archivoDiagnosticos, "%[^,]", stringAux);
                        diagnosticos[index].ID = atoi(stringAux);
                        i++;

                // Caso para agregar la descripcion del diagnostico
                case 1: fscanf(archivoDiagnosticos, "%*[,] %[^,]", diagnosticos[index].descripcion);
                        i++;

                // Caso para agregar el nivel de gravedad del diagnostico
                case 2: fscanf(archivoDiagnosticos, "%*[,] %[^\n] %*[\n] ", diagnosticos[index].nivel);
                        i = 0;
                        index++;
            }

        }

    /** Se cierra la base de datos y se retorna 0 para indicar que ningun error ha ocurrido.  */
    fclose(archivoDiagnosticos);
    return 0;

        }
}

/**
    @brief          Funcion utilizada para verificar la existencia del identificador de un diagnostico, ingresado como parametro,
                    en la base de datos.

    @param          IDDiagnostico
    @brief          Identificador del diagnostico cuya existencia en la base de datos se desea verificar.

    @param          datos
    @brief          Arreglo de estructura Diagnostico que contiene toda la informacion relacionada con los diagnostico en su correspondiente
                    base de datos.

    @param          cantidadDatos
    @brief          Numero entero que indica la cantidad de diagnosticos contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura Diagnostico ingresado como parametro.

    @return         Numero entero que indica la presencia del identificador en la base de datos.
                    \n  a)      Retornar 0 indica que el identificador efectivamente se encuentra en la base de datos
                    \n  b)      Retornar -1 indica que el identificador no se encuentra en la base de datos
*/
int verificarIdentificadorDiagnostico(int IDDiagnostico, struct Diagnostico datos[], int cantidadDatos){

    /**
        Mediante un ciclo for, se pretende recorrer la informacion contenida en el parametro "datos" (Teniendo
        en cuenta de que "datos" contiene toda la informacion de la base de datos Diagnostico) hasta encontrar
        un identificador Diagnostico que sea identico al identificador Diagnostico que fue ingresado como parametro.
    */

    int verificador = -1;   /**<        Se declara e inicializa la variable "verificador" en -1 como una forma de
                                        indicar si el identificador Diagnostico fue encontrado en la base de datos
                                        o no. Ademas, es utilizado como una forma de detener el ciclo for en caso
                                        de que la existencia de dicho identificador haya sido confirmada. */

    int index;
    for (index = 0; index < cantidadDatos && verificador == -1; index++){
        if (datos[index].ID == IDDiagnostico){
            verificador = 0;
        }
    }

    /**   Se retorna el valor contenido por la variable "verificador"   */
    return verificador;

}

