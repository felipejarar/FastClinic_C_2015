#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../Estructuras/Estructuras.h"
#include "General.h"

#ifndef DOCTORES_H
#define DOCTORES_H

int buscarDoctorPorCorreo(char correo[], struct Doctor doctores[], int cantidadDoctores);
int buscarDoctorPorRut(char rut[], struct Doctor doctores[], int contadorDoctores);
int lecturaDoctores(struct Doctor doctores[], int cantidadDoctores);
int outputEliminarMedico(int IDMedico, struct Doctor datos[], int cantidadDatos);
int outputEspecialidadDoctor(int ID, struct Doctor doctores[], int cantidadDoctores);
int outputListarMedicos(int identificadoresMedico[], int cantidadIdentificadores, struct Doctor datos[], int cantidadDatos);

#endif /* DOCTORES_H */
