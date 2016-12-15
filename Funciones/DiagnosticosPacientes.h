#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../Estructuras/Estructuras.h"
#include "General.h"

#ifndef GENERAL_H
#define GENERAL_H


int contarPacienteEnDiagnosticosPacientes(int IDPaciente, struct DiagnosticoPaciente datos[], int cantidadDatos);
int contarPacienteYDiagnosticoEnDiagnosticosPacientes(int IDPaciente, int IDDiagnostico, struct DiagnosticoPaciente datos[], int cantidadDatos);
int encontrarFechaDeAltaMasRecienteSegundIDDiagnosticoPaciente( int identificadoresDiagnosticoPaciente[], int cantidadIdentificadores, struct DiagnosticoPaciente datos[], int cantidadDatos);
void encontrarIdentificadoresDiagnostico(int IDPaciente, int diagnosticosRealizados, struct DiagnosticoPaciente datos[], int cantidadDatos, int identificadoresDiagnostico[]);
void encontrarIdentificadoresDiagnosticoPaciente(int IDPaciente, int diagnosticosRealizados, struct DiagnosticoPaciente datos[], int cantidadDatos, int identificadoresDiagnosticoPaciente[]);
void encontrarIdentificadoresDiagnosticoPacienteSegunPacienteYDiagnostico(int IDPaciente, int IDDiagnostico, int cantidadDiagnosticosEstudiados, struct DiagnosticoPaciente datos[], int cantidadDatos, int identificadoresDiagnosticoPaciente[]);
int lecturaDiagnosticosPacientes(struct DiagnosticoPaciente datos[], int cantidadDatos);
int outputModificarMedicoDeAlta(int IDDiagnosticoPaciente, int IDMedicoAlta, struct DiagnosticoPaciente datos[], int cantidadDatos);
int verificarDiagnosticoNuloEnPaciente(int IDPaciente, struct DiagnosticoPaciente datos[], int cantidadDatos);
int verificarMedicosSinDiagnosticosVigentes(int identificadoresDiagnosticoPaciente[], int cantidadIdentificadores, struct DiagnosticoPaciente datos[], int cantidadDatos);

#endif /* GENERAL_H */