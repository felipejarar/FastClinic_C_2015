/****************************************************************************************************************************************************

       @file TratamientoDiagnosticoPaciente.c
       @brief Archivo que contiene todas las funciones que relacionadas con la estructura TratamientoDiagnosticoPaciente
       @author Felipe Jara Ramirez (nialevolstel)
       @version 1.0
       @date 18 de Septiembre del 2014

******************************************************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../Estructuras/Estructuras.h"
#include "General.h"

#include "TratamientoDiagnosticoPaciente.h"
                                        /****************************************************
                                           _____                _              _
                                          / ____|              | |            | |
                                         | |     ___  _ __  ___| |_ __ _ _ __ | |_ ___  ___
                                         | |    / _ \| '_ \/ __| __/ _` | '_ \| __/ _ \/ __|
                                         | |___| (_) | | | \__ \ || (_| | | | | ||  __/\__ \
                                          \_____\___/|_| |_|___/\__\__,_|_| |_|\__\___||___/

                                        ****************************************************/

/**
    @def ARCHIVO_TRATAMIENTO_DIAGNOSTICO_PACIENTE
    @brief Contiene la ruta en donde se encuentra la base de datos correspondiente a la vinculacion Tratamiento, Diagnostico y Paciente.

    @def COLUMNAS_TRATAMIENTO_DIAGNOSTICO_PACIENTE
    @brief Contiene la cantidad de elementos diferentes que estructuran a la base de datos correspondiente a la vinculacion Tratamiento, Diagnostico y Paciente.

    @def REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES
    @brief Contiene una referencia utilizada para realizar un conteo de la cantidad de vinculaciones contenidas en su respectiva
    base de datos. Es utilizado en la funcion contadorDeDatos() declarada en el archivo General.c
*/

#define ARCHIVO_TRATAMIENTO_DIAGNOSTICO_PACIENTE "Bases de Datos/TratamientoDiagnosticoPaciente.txt"
#define COLUMNAS_TRATAMIENTO_DIAGNOSTICO_PACIENTE 6
#define REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES 6

/***************************************************************************************************************************************************************************************
  _                    _                         _                  _                   _   _                                         _     _
 | |                  | |                       (_)                | |                 | | (_)                                       | |   (_)
 | |_   _ __    __ _  | |_    __ _   _ __ ___    _    ___   _ __   | |_    ___       __| |  _    __ _    __ _   _ __     ___    ___  | |_   _    ___    ___
 | __| | '__|  / _` | | __|  / _` | | '_ ` _ \  | |  / _ \ | '_ \  | __|  / _ \     / _` | | |  / _` |  / _` | | '_ \   / _ \  / __| | __| | |  / __|  / _ \
 | |_  | |    | (_| | | |_  | (_| | | | | | | | | | |  __/ | | | | | |_  | (_) |   | (_| | | | | (_| | | (_| | | | | | | (_) | \__ \ | |_  | | | (__  | (_) |
  \__| |_|     \__,_|  \__|  \__,_| |_| |_| |_| |_|  \___| |_| |_|  \__|  \___/     \__,_|_|_|  \__,_|  \__, | |_| |_|  \___/  |___/  \__| |_|  \___|  \___/
                                                                      (_)                | |             __/ |
                                                _ __     __ _    ___   _    ___   _ __   | |_    ___    |___/
                                               | '_ \   / _` |  / __| | |  / _ \ | '_ \  | __|  / _ \
                                               | |_) | | (_| | | (__  | | |  __/ | | | | | |_  |  __/
                                               | .__/   \__,_|  \___| |_|  \___| |_| |_|  \__|  \___|
                                               | |
                                               |_|
****************************************************************************************************************************************************************************************/



/**

    @brief          Funcion utilizada para obtener toda la informacion relacionada con las vinculaciones entre tratamientos, diagnosticos y pacientes a partir
                    de su respectiva base de datos

    @param          datos
    @brief          Arreglo de estructura TratamientoDiagnosticoPaciente. Parametro pasado por referencia que, tras finalizar la ejecucion de la funcion,
                    pasa a contener toda la informacion relacionada con las vinculaciones entre Tratamientos, Diagnosticos y Pacientes
                    (identificadorDiagnosticoPaciente,identificadorTratamiento,identificadorMedico,fechaInicio,duracionDias,resultado).

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura TratamientoDiagnosticoPaciente
                    entregado como parametro.

    @return         Numero entero que indica la existencia de errores, en el caso de que existan.
                    \n a)  Retornar 0 indica que la funcion se ha llevado a cabo correctamente.
                    \n b)  Retornar un numero diferente de 0 indica que se ha presentado una anormalidad en la funcion cuando esta fue ejecutada.
*/
int lecturaTratamientosDiagnosticosPacientes(struct TratamientoDiagnosticoPaciente datos[], int cantidadDatos){

    /**
        Se obtiene el archivo (base de datos) relacionado con la informacion las vinculaciones entre Tratamientos, Diagnosticos y Pacientes, y dependiendo de
        si el archivo fue obtenido correctamente, se procede a realizar la lectura de este.
    */

    FILE* archivo = fopen(ARCHIVO_TRATAMIENTO_DIAGNOSTICO_PACIENTE, "r");

    /**
        En el caso de que no se haya logrado realizar la apertura de la base de datos, se escribe un mensaje de error en output y se retorna -1
    */
    if (archivo == NULL){
        escribirMensajeDeError("Se ha presentado un error al momento de realizar la apertura de la base de datos TratamientoDiagnosticoPaciente");
        return -1;
    }

    else{

        /**
            Conociendo la cantidad de vinculaciones que hay en la base de datos, se procede a agregar la informacion contenida en el archivo de texto
            al arreglo de structura TratamientoDiagnoticoPaciente entregado como parametro. La primera linea del archivo sirve solamente como referencia,
            por lo que debe ser ignorada
        */
        fscanf(archivo,"%*[identificadorDiagnosticoPaciente,identificadorTratamiento,identificadorMedico,fechaInicio,duracionDias,resultado] %*[\n]");

        char stringAux[DEFAULT_STRING_SIZE];        /**<   Se declara la variable local stringAux para aquellos datos que requieren
                                                    ser transformados a un tipo de dato int antes de ser incluidos al arreglo
                                                    de estructura TratamientoDiagnosticoPaciente (Identificadores, duracionDias)*/

        /**
            Bajo una sentencia while y switch-case se procede a agregar al arreglo de estructura TratamientoDiagnosticoPaciente la informacion necesaria
            para construir a cada una de las vinculaciones Tratamiento-Diagnostico-Paciente
        */

        int fscanfAux = 0;  /**<    Se declara la variable local fscanfAux con el proposito de detener el ciclo while cuando, a medida que se realiza
                                    la lectura del archivo, se llega al final de este. Es decir, cuando fscanfAux es igual a EOF */

        int i = 0;
        int index = 0;
        while (index < cantidadDatos && fscanfAux != EOF){

            switch(i){

                // Caso para agregar el identificador del Diagnostico de un Paciente
                case 0: fgets(stringAux, 1, archivo);
                        fscanf(archivo, "%[^,]", stringAux);
                        datos[index].IDDiagnosticoPaciente = atoi(stringAux);
                        i++;

                // Caso para agregar el identificador de un Tratamiento
                case 2: fscanf(archivo, "%*[,] %[^,]", stringAux);
                        datos[index].IDTratamiento = atoi(stringAux);
                        i++;

                // Caso para agregar el identificador de un Medico
                case 3: fscanf(archivo, "%*[,] %[^,]", stringAux);
                        datos[index].IDMedico = atoi(stringAux);
                        i++;

                // Caso para agregar la fecha de inicio
                case 4: fscanf(archivo, "%*[,] %[^,]", datos[index].fechaInicio);
                        i++;

                // Caso para agregar la duracion en Dias
                case 5: fscanf(archivo, "%*[,] %[^,]", stringAux);
                        datos[index].duracionDias = atoi(stringAux);
                        i++;

                // Caso para agregar los resultados
                case 6: fscanf(archivo, "%*[,] %[^\n] %*[\n] ", datos[index].resultado);
                        i = 0;
                        index++;
            }

        }

        /**
            Se cierra el archivo y se retorna 0 para indicar que ningun error ha ocurrido
        */

        fclose(archivo);
        return 0;

        }
}


/**

    @brief          Procedimiento utilizado para encontrar los identificadores de los medicos relacionados con ciertos identificadores de vinculacion Diagnostico-Paciente

    @param          identificadoresDiagnosticoPaciente
    @brief          Arreglo que representa un conjunto de identificadores de vinculaciones Diagnostico-Paciente.

    @param          identificadoresMedico
    @brief          Arreglo entregado por referencia que, tras finalizar la ejecucion de la funcion, pasa a contener todos los identificadores de los medicos
                    relacionados con las vinculaciones Diagnostico-Paciente cuyos identificadores fueron entregados como parametro.

    @param          cantidadIdentificadores
    @brief          Representa la dimension de los arreglos identificadoresDiagnosticoPaciente e identificadoresMedico

    @param          datos
    @brief          Arreglo de estructura TratamientoDiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Tratamiento, Diagnostico y Paciente

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura TratamientoDiagnosticoPaciente
                    entregado como parametro.

    @return         void.
*/
void encontrarIdentificadoresMedicos(int identificadoresDiagnosticoPaciente[], int identificadoresMedico[], int cantidadIdentificadores, struct TratamientoDiagnosticoPaciente datos[], int cantidadDatos){

    /**
        Se procede a comparar los identificadores DiagnosticoPaciente entregados como parametro con los identificadores DiagnosticoPaciente contenidos en la
        estructura TratamientoDiagnosticoPaciente. Cuando se encuentra una similitud, es posible obtener uno de los identificadores del medico relacionado con
        una de las vinculaciones DiagnosticoPaciente.
    */

    int auxBreak;   /**<    Se declara auxBreak como una forma de detener el ciclo for cuando se haya encontrado el identificador de un medico para uno
                            de los identificadores DiagnosticoPaciente  */
    int i, j;
    for (i = 0; i < cantidadIdentificadores; i++){
        auxBreak = 0;
        for( j = 0; j < cantidadDatos && auxBreak == 0; j++){
            if (datos[j].IDDiagnosticoPaciente == identificadoresDiagnosticoPaciente[i]){
                identificadoresMedico[i] = datos[j].IDMedico;
                auxBreak = -1;
            }
        }
    }
}


/**
    @brief          Procedimiento utilizado para encontrar los identificadores de Tratamientos relacionados con ciertos identificadores DiagnosticoPaciente

    @param          identificadoresDiagnosticoPaciente
    @brief          Arreglo que representa un conjunto de identificadores de vinculaciones Diagnostico-Paciente.

    @param          identificadoresTratamiento
    @brief          Arreglo entregado por referencia que, tras finalizar la ejecucion de la funcion, pasa a contener todos los identificadores de los tratamientos
                    relacionados con las vinculaciones Diagnostico-Paciente cuyos identificadores fueron entregados como parametro.

    @param          cantidadIdentificadores
    @brief          Representa la dimension de los arreglos identificadoresDiagnosticoPaciente e identificadoresTratamiento

    @param          datos
    @brief          Arreglo de estructura TratamientoDiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Tratamiento, Diagnostico y Paciente

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura TratamientoDiagnosticoPaciente
                    entregado como parametro.

    @return         void.
*/
void encontrarIdentificadoresTratamientoSegunDiagnosticoPaciente(int identificadoresDiagnosticoPaciente[], int identificadoresTratamiento[], int cantidadIdentificadores, struct TratamientoDiagnosticoPaciente datos[], int cantidadDatos){

    /**
        Se procede a comparar los identificadores DiagnosticoPaciente entregados como parametro con los identificadores DiagnosticoPaciente contenidos en la
        estructura TratamientoDiagnosticoPaciente. Cuando se encuentra una similitud, es posible obtener uno de los identificadores del tratamiento relacionado con
        una de las vinculaciones DiagnosticoPaciente.
    */

    int i, j;
    int auxBreak; /**<    Se declara auxBreak como una forma de detener el ciclo for cuando se haya encontrado el identificador de un tratamiento para uno
                            de los identificadores DiagnosticoPaciente  */

    for (i = 0; i < cantidadIdentificadores; i++){
        auxBreak = 0;
        for (j = 0; i < cantidadDatos && auxBreak == 0; j++){
            if (datos[j].IDDiagnosticoPaciente == identificadoresDiagnosticoPaciente[i]){
                identificadoresTratamiento[i] = datos[j].IDTratamiento;
                auxBreak = -1;
            }
        }
    }
}



/**

    @brief          Funcion utilizada para modificar en la base de datos el resultado del tratamiento de un paciente en particular.

    @param          IDDiagnosticosPacientes
    @brief          Arreglo que representa un conjunto de identificadores de vinculaciones Diagnostico-Paciente.

    @param          cantidadDiagnosticos
    @brief          Cantidad de diagnosticos realizados por un paciente. Indica tambien la dimension del arreglo IDDiagnosticosPacientes.

    @param          IDTratamiento
    @brief          Identificador del tratamiento cuyo resultado en la base de datos se desea modificar.

    @param          datos
    @brief          Arreglo de estructura TratamientoDiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Tratamiento, Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura TratamientoDiagnosticoPaciente
                    entregado como parametro.

    @param          resultado
    @brief          Texto que reemplazara el resultado de un tratamiento en la base de datos.

    @return         Numero entero que indica la existencia de errores, en el caso de que existan.
                    \n a)  Retornar 0 indica que la funcion se ha llevado a cabo correctamente.
                    \n b)  Retornar un numero diferente de 0 indica que se ha presentado una anormalidad en la funcion cuando esta fue ejecutada.
*/
int outputModificarResultadoTratamiento(int IDDiagnosticosPacientes[], int cantidadDiagnosticos, int IDTratamiento, struct TratamientoDiagnosticoPaciente datos[], int cantidadDatos, char resultado[]){
    int index;
    int i;
    int verificador = -1;
    /** Se recurre a un primer ciclo for para recorrer los elementos contenidos en IDDiagnosticosPacientes. */
    for (i = 0; i < cantidadDiagnosticos; i++){

        /** Simultaneamente, se recurre a un segundo siclo for para recorrer los elementos contenidos en el arreglo de datos. */
        for (index = 0; index < cantidadDatos; index++){

            /**
                Mediante comparaciones con los datos se intenta encontrar el Identificador DiagnosticoPaciente, contenido en IDDiagnosticosPacientes,
                que se encuentra relacionado con el identificador del tratamiento ingresado como parametro.
            */
            if (IDDiagnosticosPacientes[i] == datos[index].IDDiagnosticoPaciente && IDTratamiento == datos[index].IDTratamiento){

                /**
                    Tras haber encontrado dicho identificador DiagnosticoPaciente, se procede a abrir la base de datos relacionado con las vinculaciones
                    entre Tratamiento, Diagnostico y Paciente. Su referencia es entregada al puntero "archivoTratamientoDiagnosticoPaciente."
                */
                FILE* archivoTratamientoDiagnosticoPaciente = fopen(ARCHIVO_TRATAMIENTO_DIAGNOSTICO_PACIENTE, "w");

                /** Por otro lado, se realiza la apertura del archivo output, cuya referencia es entregada al puntero "output". */
                FILE* output = fopen(ARCHIVO_OUTPUT,"a");

                if ( archivoTratamientoDiagnosticoPaciente == NULL ){

                    /**
                        En el caso de que se haya producido un error al momento de realizar la apertura de la base de datos, se
                        escribe un mensaje de error en el archivo output y se retorna -1.
                    */

                    if ( output != NULL){
                        fprintf(output, "ERROR! NO SE HA PODIDO MODIFICAR EL RESULTADO DEL TRATAMIENTO (ID = %d)\n\n",IDTratamiento);
                        fclose(output);
                    }
                    return -1;
                }

                else{

                    /**
                        Se reescribe en la base de datos la primera linea, la cual solo es una referencia de los diferentes tipos de elementos que contiene
                        el archivo.
                    */
                    fprintf(archivoTratamientoDiagnosticoPaciente,"identificadorDiagnosticoPaciente,identificadorTratamiento,identificadorMedico,fechaInicio,duracionDias,resultado\n");

                    /**
                        Mediante un ciclo for, se reescribe el resto de las lineas de la base de datos con la informacion contenida en el arreglo de estructura
                        TratamientoDiagnosticoPaciente. Con la excepcion de aquel resultado correspondiente a los identificadores DiagnosticoPaciente y
                        Tratamiento sobre los cuales se esta trabajando, ya que en este caso se utiliza el resultado que fue entregado como parametro.
                    */

                    for (index = 0; index < cantidadDatos; index++){

                        if (datos[index].IDTratamiento == IDTratamiento && datos[index].IDDiagnosticoPaciente == IDDiagnosticosPacientes[i]){

                            fprintf(archivoTratamientoDiagnosticoPaciente,"%d,%d,%d,%s,%d,%s\n",datos[index].IDDiagnosticoPaciente,datos[index].IDTratamiento,datos[index].IDMedico,datos[index].fechaInicio,datos[index].duracionDias,resultado);

                        }

                        else{

                            fprintf(archivoTratamientoDiagnosticoPaciente,"%d,%d,%d,%s,%d,%s\n",datos[index].IDDiagnosticoPaciente,datos[index].IDTratamiento,datos[index].IDMedico,datos[index].fechaInicio,datos[index].duracionDias,datos[index].resultado);

 }
                    }

                    /** Tras haber reescrito la base de datos, se procede a cerrar el archivo y a escribir un mensaje en el archivo output. */
                    fclose(archivoTratamientoDiagnosticoPaciente);
                    if ( output != NULL){
                        fprintf(output,"El resultado de un tratamiento (ID = %d) de un paciente ha sido modificado a %s\n\n", IDTratamiento, resultado);
                    }

                    /** Finalmente se cierra el archivo output y se retorna a 0 indicando que ningun error ocurrio durante la ejecucion del programa. */
                    fclose(output);
                    verificador = 0;
                    return verificador;
                }
            }
        }
    }

    if (verificador == -1){
        FILE* output = fopen(ARCHIVO_OUTPUT,"a");
        if ( output != NULL){
            fprintf(output,"ERROR!: No ha sido posible modificar el resultado del tratamiento (ID:%d)\n\n", IDTratamiento);
            fclose(output);
        }
        return verificador;
    }
}




