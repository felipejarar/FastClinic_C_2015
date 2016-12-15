/*****************************************************************************************************************

       @file TratamientosDiagnosticos.c
       @brief Archivo que contiene todas las funciones que relacionadas con la estructura TratamientosDiagnosticos
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

#include "TratamientosDiagnosticos.h"


/**
    @def ARCHIVO_TRATAMIENTO_DIAGNOSTICO
    @brief Contiene la ruta en donde se encuentra la base de datos correspondiente a las vinculaciones entre Tratamientos y Diagnosticos.

    @def REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS
    @brief Contiene la cantidad de elementos diferentes que estructuran la base de datos correspondiente a las vinculaciones entre Tratamientos y Diagnosticos.

    @def COLUMNAS_TRATAMIENTO_DIAGNOSTICO
    @brief Contiene una referencia utilizada para realizar un conteo de la cantidad de vinculaciones entre Tratamientos y Diagnosticos contenidos en su respectiva
    base de datos. Es utilizado en la funcion  contadorDeDatos() declarada en el archivo General.c
*/

#define ARCHIVO_TRATAMIENTO_DIAGNOSTICO "Bases de Datos/TratamientoDiagnostico.txt"
#define REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS 5
#define COLUMNAS_TRATAMIENTO_DIAGNOSTICO 2



/**
              _                    _                         _                  _                   _   _                                         _     _
             | |                  | |                       (_)                | |                 | | (_)                                       | |   (_)
             | |_   _ __    __ _  | |_    __ _   _ __ ___    _    ___   _ __   | |_    ___       __| |  _    __ _    __ _   _ __     ___    ___  | |_   _    ___    ___
             | __| | '__|  / _` | | __|  / _` | | '_ ` _ \  | |  / _ \ | '_ \  | __|  / _ \     / _` | | |  / _` |  / _` | | '_ \   / _ \  / __| | __| | |  / __|  / _ \
             | |_  | |    | (_| | | |_  | (_| | | | | | | | | | |  __/ | | | | | |_  | (_) |   | (_| | | | | (_| | | (_| | | | | | | (_) | \__ \ | |_  | | | (__  | (_) |
              \__| |_|     \__,_|  \__|  \__,_| |_| |_| |_| |_|  \___| |_| |_|  \__|  \___/     \__,_| |_|  \__,_|  \__, | |_| |_|  \___/  |___/  \__| |_|  \___|  \___/
                                                                                                                     __/ |
                                                                                                                    |___/
*/


/**

    @brief          Funcion utilizada para obtener toda la informacion relacionada con las vinculaciones entre tratamientos y diagnosticos a partir de su respectiva base de datos

    @param          datos
    @brief          Arreglo de estructura TratamientoDiagnostico. Parametro pasado por referencia que, tras finalizar la ejecucion de la funcion,
                    pasa a contener toda la informacion relacionada con las vinculaciones entre Tratamientos y Diagnosticos
                    (identificadorDiagnostico,identificadorTratamiento).

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura TratamientoDiagnostico
                    entregado como parametro

    @return         Numero entero que indica la existencia de errores, en el caso de que existan.
                    \n a)  Retornar 0 indica que la funcion se ha llevado a cabo correctamente.
                    \n b)  Retornar un numero diferente de 0 indica que se ha presentado una anormalidad en la funcion cuando esta fue ejecutada.
*/
int lecturaTratamientosDiagnosticos(struct TratamientoDiagnostico datos[], int cantidadDatos){
    /**
        Se obtiene el archivo (base de datos) relacionado con la informacion las vinculaciones entre Tratamientos y Diagnosticos, su referencia es
        entregada a la variable local "archivo" y dependiendo de si la apertura del archivo fue realizada correctamente, se procede a empezar con
        la lectura de este.
    */

    FILE* archivo = fopen(ARCHIVO_TRATAMIENTO_DIAGNOSTICO, "r");
    /** En el caso de que no se haya logrado realizar la apertura de la base de datos correctamente, se escribe un mensaje de error en output y se retorna -1. */
    if (archivo == NULL){
        return -1;
    }

    else{

        /**
            Conociendo la cantidad de vinculaciones que hay en la base de datos, se procede a agregar la informacion contenida en el archivo de texto
            al arreglo de structura TratamientoDiagnotico entregado como parametro. La primera linea del archivo sirve solamente como referencia,
            por lo que debe ser ignorada.
        */
        fscanf(archivo,"%*[identificadorDiagnostico,identificadorTratamiento] %*[\n]");

        char stringAux[DEFAULT_STRING_SIZE];        /**<   Se declara la variable local stringAux para aquellos datos que requieren
                                                    ser transformados a un tipo de dato int antes de ser incluidos al arreglo
                                                    de estructura TratamientoDiagnostico (Identificadores).*/

        /**
            Bajo una sentencia while y switch-case se procede a agregar al arreglo de estructura TratamientoDiagnostico la informacion necesaria
            para construir a cada una de las vinculaciones Tratamiento-Diagnostico.
        */

        int fscanfAux = 0;          /**<    Se declara la variable local fscanfAux con el proposito de detener el ciclo while cuando, a medida que se realiza
                                    la lectura del archivo, se llega al final de este. Es decir, cuando fscanfAux es igual a EOF.*/
        int i = 0;
        int index = 0;
        while (index < cantidadDatos && fscanfAux != EOF){

            switch(i){

                // Caso para agregar el identificador del diagnostico
                case 0: fgets(stringAux, 1, archivo);
                        fscanf(archivo, "%[^,]", stringAux);
                        datos[index].IDDiagnostico = atoi(stringAux);
                        i++;

                // Caso para agregar el identificador del tratamiento
                case 1: fscanf(archivo, "%*[,] %[^\n] %*[\n] ", stringAux);
                        datos[index].IDTratamiento = atoi(stringAux);
                        i = 0;
                        index++;
            }

        }

    /**
        Se cierra el archivo y se retorna 0 para indicar que ningun error ha ocurrido.
    */

    fclose(archivo);
    return 0;

        }
}

/**
    @brief          Procedimiento utilizado para encontrar los identificadores de Tratamiento relacionados con ciertos identificadores de Diagnostico

    @param          identificadoresDiagnostico
    @brief          Arreglo que representa un conjunto de identificadores de Diagnostico.

    @param          identificadoresTratamiento
    @brief          Arreglo entregado por referencia que, tras finalizar la ejecucion de la funcion, pasa a contener todos los identificadores de los
                    tratamientos relacionados con los Diagnosticos cuyos identificadores fueron entregados como parametro.

    @param          cantidadIdentificadores
    @brief          Representa la dimension de los arreglos identificadoresDiagnostico e identificadoresTratamiento,

    @param          datos
    @brief          Arreglo de estructura TratamientoDiagnostico que contiene toda la informacion relacionada con las vinculaciones entre
                    Tratamiento y Diagnostico

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura TratamientoDiagnostico
                    entregado como parametro.

    @return         void
*/
void encontrarIdentificadoresTratamientoSegunDiagnostico(int identificadoresDiagnostico[], int identificadoresTratamiento[], int cantidadIdentificadores, struct TratamientoDiagnostico datos[], int CantidadDatos){

    /**
        Se procede a comparar los identificadores Diagnostico entregados como parametro con los identificadores DiagnosticoPaciente contenidos en la
        estructura de datos TratamientoDiagnosticoPaciente. Cuando se encuentra una similitud, es posible obtener uno de los identificadores del
        tratamiento relacionado con uno de los identificadores Diagnostico.
    */

    int auxBreak;   /**<    Se declara auxBreak como una forma de detener el ciclo for cuando se haya encontrado el identificador de un tratamiento para uno
                            de los identificadores Diagnostico  */

    int i, j;
    for (i = 0; i < cantidadIdentificadores; i++){
        auxBreak = 0;
        for (j = 0; i < CantidadDatos && auxBreak == 0; j++){
            if (datos[j].IDDiagnostico == identificadoresDiagnostico[i]){
                identificadoresTratamiento[i] = datos[j].IDTratamiento;
                auxBreak = -1;
            }
        }
    }
}
