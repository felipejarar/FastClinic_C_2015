#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../Estructuras/Estructuras.h"
#include "General.h"

#ifndef TRATAMIENTODIAGNOSTICOPACIENTE_H
#define TRATAMIENTODIAGNOSTICOPACIENTE_H

void encontrarIdentificadoresMedicos(int identificadoresDiagnosticoPaciente[], int identificadoresMedico[], int cantidadIdentificadores, struct TratamientoDiagnosticoPaciente datos[], int cantidadDatos);
void encontrarIdentificadoresTratamientoSegunDiagnosticoPaciente(int identificadoresDiagnosticoPaciente[], int identificadoresTratamiento[], int cantidadIdentificadores, struct TratamientoDiagnosticoPaciente datos[], int cantidadDatos);
int lecturaTratamientosDiagnosticosPacientes(struct TratamientoDiagnosticoPaciente datos[], int cantidadDatos);
int outputModificarResultadoTratamiento(int IDDiagnosticosPacientes[], int cantidadDiagnosticos, int IDTratamiento, struct TratamientoDiagnosticoPaciente datos[], int cantidadDatos, char resultado[]);

#endif /* TRATAMIENTODIAGNOSTICOPACIENTE_H */

