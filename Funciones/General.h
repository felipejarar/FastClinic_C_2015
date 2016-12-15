#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#ifndef GENERAL_H
#define GENERAL_H


#define DEFAULT_STRING_SIZE 50
#define DEFAULT_LONG_STRING_SIZE 1024
#define ARCHIVO_OUTPUT "Output/output.txt"

int contadorDeDatos( char nombreArchivo[], int identificador, int cantidadColumnas);
void escribirMensajeDeError(char mensaje[]);
void transformarFecha(char fecha[], int fechaInt[]);

#endif /* GENERAL_H */
