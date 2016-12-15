/*****************************************************************************************************************

       @file General.c
       @brief Archivo que contiene todas las funciones generales
       @author Felipe Jara Ramirez (nialevolstel)
       @version 1.0
       @date 18 de Septiembre del 2014

*******************************************************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "General.h"
                                    /****************************************************
                                       _____                _              _
                                      / ____|              | |            | |
                                     | |     ___  _ __  ___| |_ __ _ _ __ | |_ ___  ___
                                     | |    / _ \| '_ \/ __| __/ _` | '_ \| __/ _ \/ __|
                                     | |___| (_) | | | \__ \ || (_| | | | | ||  __/\__ \
                                      \_____\___/|_| |_|___/\__\__,_|_| |_|\__\___||___/

                                    ****************************************************/

/**
    @def DEFAULT_STRING_SIZE
    @brief Corresonde la cantidad maxima de caracteres que un String (char Array), destinado a representar una o dos palabras, puede contener.

    @def DEFAULT_LONG_STRING SIZE
    @brief Representa la cantidad maxima de caracteres que un String (char Array), destinado a descripciones o detalles, puede contener.

    @def ARCHIVO_OUTPUT
    @brief Contiene la ruta en donde se encuentra el archivo output, archivo en el cual se registran la respuesta
        a una consulta realizada por el usuario del programa.
*/

#define DEFAULT_STRING_SIZE 50
#define DEFAULT_LONG_STRING_SIZE 1024
#define ARCHIVO_OUTPUT "Output/output.txt"






/**
	@brief          Funcion utilizada para realizar un conteo sobre la cantidad de datos contenidos en una determinada base de datos

    @param          nombreArchivo
    @brief          Nombre de un archivo de texto. En otras palabras, es la referencia la base de datos cuyos datos se desean contabilizar.

    @param          identificador
    @brief          Numero entero que indica la base de datos que la funcion esta trabajando. En otras palabras, le indica a la funcion
                    como debe realizar la contabilizacion de datos. Los valores que puede tomar son:
					\n		0 = Archivo Pacientes
					\n		1 = Archivo Doctores
					\n		2 = Archivo Diagnosticos
					\n		3 = Archivo Tratamientos
					\n		4 = Archivo Diagnosticos-Pacientes
					\n		5 = Archivo Tratamientos-Diagnosticos
					\n		6 = Archivo Tratamientos-Diagnosticos-Pacientes

    @param          cantidadColumnas
    @brief          Corresponde a la cantidad de diferentes tipos de elementos que componen a la base de datos cuya referencia fue entregada como
                    parametro. Dicho de otra manera, corresponde a la cantidad de columnas que estructuran al archivo de texto.

    @return         Cantidad de datos que componen a la base de datos cuya referencia fue entregada como parametro.
*/
int contadorDeDatos( char nombreArchivo[], int identificador, int cantidadColumnas){
    /**
        Se realiza la apertura de la base de datos sobre la cual se desea trabajar.
    */
    FILE* archivo = fopen(nombreArchivo, "r"); // Se abre el archivo

    /**
        En el caso de que se presente un error en la apertura de la base de datos, se retorna a -1.
    */
    if (archivo == NULL){
            return -1; // Error en la apertura del archivo
    }

    else{

        /**
            Se ignora primera linea de la base de datos, ya que esta solamente contiene una referencia de los tipos
            de elementos que componen al archivo. La forma en que se ignora dicha linea depende del identificador que
            fue ingresado como parametro.
        */
    	switch (identificador){
    		case 0:		fscanf(archivo,"%*[identificador,rut,email,nombre,apellido,fecha de nacimiento] %*[\n]");

    		case 1: 	fscanf(archivo,"%*[identificador,rut,email,Nombre,apellido,especialidad] %*[\n]");

    		case 2:		fscanf(archivo,"%*[identificador,descripcionDiagnostico,nivelGravedad] *[\n]");

    		case 3:		fscanf(archivo,"%*[identificador,nombreTratamiento,descripcionTratamiento,nivelDeRiesgo] %*[\n]");

    		case 4:		fscanf(archivo,"%*[identificadorDiagnosticoPaciente,identificadorPaciente,identificadorDiagnostico,fechaDiagnostico,identificadorDoctorDiagnostico,estadoDiagnostico,fechaAlta,identificadorDoctorAlta,detalleAlta] %*[\n]");

            case 5:     fscanf(archivo,"%*[identificadorDiagnostico,identificadorTratamiento] %*[\n]");

            case 6:     fscanf(archivo, "%*[identificadorDiagnosticoPaciente,identificadorTratamiento,identificadorMedico,fechaInicio,duracionDias,resultado] %*[\n]");
       	}

       	/**
            Se procede a realizar un conteo de la cantidad de datos que componen al archivo mediante un bucle while. Para ello se debe tener en cuenta que la cantidad de columnas de la base de datos
            indica la cantidad de elementos que estructuran a uno de los datos
        */


        int contadorDatos = 0;      /**<    Se declara la variable local "contadorDatos" con el proposito de almacenar la cantidad de datos que se van encontrando
                                            a medida que se realiza una lectura de la base de datos */

        int contadorPalabras = 0;   /**<    Se declara la variable local "contadorPalabras" con el proposito de almacenar la cantidad de palabras (elementos) que
                                            se van encontrando a medida que se realiza una lectura de la base de datos. Se ha de tener en cuenta que cuando se alcanza
                                            cierta cantidad de palabras o elementos (cantidad determinada por el numero de columnas que componen a la base de datos)
                                            es posible estructurar un dato. Cuando esto ocurre, se incrementa en una unidad la variable "contadorDatos" mientras que
                                            "contadorPalabras" vuelve a tomar el valor de 0. */

        int fscanfAux = 0;          /**<    Se declara la variable local "fscanfAux" con el proposito de detener el ciclo while cuando, durante la lectura, se alcanza
                                            el final de la base de datos. */
        while (fscanfAux != EOF){

            if (contadorPalabras == cantidadColumnas-1){
                fscanfAux = fscanf(archivo, "%*[^\n] %*[\n]");
                contadorPalabras = 0;
                contadorDatos++;
            }

            else{
                fscanfAux = fscanf(archivo, "%*[,] %*[^,]");
                contadorPalabras++;
            }
        }

        /**
            Se cierra la base de datos sobre la cual se estaba trabajando y se retorna la cantidad de datos encontrados
        */

		fclose(archivo);
        return contadorDatos;
    }
}





/**

    @brief          Procedimiento utilizado para escribir en un archivo output un mensaje de error.

    @param          mensaje
    @brief          Mensaje de error que se desea escribir en el archivo output.

    @return         void
*/
void escribirMensajeDeError(char mensaje[]){
    /** Se realiza la apertura del archivo output. */

    FILE*   output = fopen(ARCHIVO_OUTPUT,"a");

    /** Si la apertura del archivo se ha realizado correctamente, entonces se escribe el mensaje de error y se cierra el archivo */
    if (output != NULL){
        fprintf(output,"ERROR!: %s\n\n", mensaje);
        fclose(output);
    }
}






/**
    @brief          Procedimiento utilizado para convertir una fecha escrita como una cadena de caracteres a una fecha representada como
                    un arreglo de numeros enteros.

    @param          fecha
    @brief          Corresponde a la fecha escrita como un arreglo de char

    @param          fechaInt
    @brief          Corresponde a la fecha escrita como un arreglo de int.

    @return         void.
*/
void transformarFecha(char fecha[], int fechaInt[]){
    int i;
    char fechaAux[DEFAULT_STRING_SIZE];
    strcpy(fechaAux, fecha);
    for (i = 0; i < 3; i++){
        if (i == 0){
            fechaInt[i] = atoi(strtok(fechaAux,"/"));
        }
        else{
            fechaInt[i] = atoi(strtok(NULL,"/"));
        }
    }
}

