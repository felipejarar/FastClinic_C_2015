#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../Estructuras/Estructuras.h"
#include "General.h"

#ifndef DIAGNOSTICOS_H
#define DIAGNOSTICOS_H

int lecturaDiagnosticos(struct Diagnostico diagnosticos[], int cantidadDiagnosticos);
int verificarIdentificadorDiagnostico(int IDDiagnostico, struct Diagnostico datos[], int cantidadDatos);

#endif /* DIAGNOSTICOS_H */
