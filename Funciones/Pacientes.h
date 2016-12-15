#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../Estructuras/Estructuras.h"
#include "General.h"



#ifndef PACIENTES_H
#define PACIENTES_H

int buscarPacientePorCorreo(char correo[], struct Paciente pacientes[], int contadorPacientes);
int buscarPacientePorNombreYApellido(char nombre[], char apellido[], struct Paciente pacientes[], int cantidadPacientes);
int buscarPacientePorRut(char rut[], struct Paciente pacientes[], int cantidadPacientes);
int verificarIdentificadorPaciente(int IDPaciente, struct Paciente datos[], int cantidadDatos);
int outputNombrePaciente(int ID, struct Paciente pacientes[], int cantidadPacientes);
int outputEliminarPaciente (int IDPaciente, struct Paciente datos[], int cantidadDatos);
int outputModificarCorreoPaciente (char correoAntiguo[], char correoNuevo[], struct Paciente pacientes[], int cantidadPacientes);
int lecturaPacientes(struct Paciente pacientes[], int cantidadPacientes);

#endif /* PACIENTES_H */
