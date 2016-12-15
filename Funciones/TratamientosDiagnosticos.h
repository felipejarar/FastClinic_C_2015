
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../Estructuras/Estructuras.h"
#include "General.h"

#ifndef TRATAMIENTOSDIAGNOSTICOS_H
#define TRATAMIENTOSDIAGNOSTICOS_H

int lecturaTratamientosDiagnosticos(struct TratamientoDiagnostico datos[], int cantidadDatos);
void encontrarIdentificadoresTratamientoSegunDiagnostico(int identificadoresDiagnostico[], int identificadoresTratamiento[], int cantidadIdentificadores, struct TratamientoDiagnostico datos[], int CantidadDatos);


#endif /* TRATAMIENTOSDIAGNOSTICOS_H */