#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../Estructuras/Estructuras.h"
#include "General.h"

#ifndef TRATAMIENTO_H
#define TRATAMIENTO_H


int lecturaTratamientos(struct Tratamiento tratamientos[], int contadorTratamientos);
int outputListarTratamientosSegunID(int identificadores[], int cantidadIdentificadores, struct Tratamiento datos[], int cantidadDatos);
int outputListarTratamientosSegunNivel(char nivel[], struct Tratamiento tratamientos[], int cantidadTratamientos);
int verificarExistenciaDeTratamiento(int IDTratamiento, struct Tratamiento datos[], int cantidadDatos);

#endif /* TRATAMIENTO_H */
