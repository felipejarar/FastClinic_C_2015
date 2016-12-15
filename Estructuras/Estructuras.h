/*****************************************************************************************************************

       @file Estructuras.h
       @brief Archivo para guardar las estructuras que son utilizadas en el programa principal (main)
       @author Felipe Jara Ramirez (nialevolstel)
       @version 1.0
       @date 18 de Septiembre del 2014

******************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H



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
*/

#define DEFAULT_STRING_SIZE 50
#define DEFAULT_LONG_STRING_SIZE 1024



                                /***********************************************************
                                  ______     _                   _
                                 |  ____|   | |                 | |
                                 | |__   ___| |_ _ __ _   _  ___| |_ _   _ _ __ __ _ ___
                                 |  __| / __| __| '__| | | |/ __| __| | | | '__/ _` / __|
                                 | |____\__ \ |_| |  | |_| | (__| |_| |_| | | | (_| \__ \
                                 |______|___/\__|_|   \__,_|\___|\__|\__,_|_|  \__,_|___/


                                ************************************************************/

/**
    @struct Diagnostico
    @brief Estructura de datos utilizada para almacenar informacion relativa a un diagnostico en especifico.

    @var Diagnostico::ID
    @brief "ID" contiene al identificador de un diagnostico en su respectiva base de datos.

    @var Diagnostico::descripcion
    @brief "descripcion" contiene una breve descripcion de lo que consiste un diagnostico.

    @var Diagnostico::nivel
    @brief "nivel" contiene el nivel de gravedad que representa el diagnostico.
*/

struct Diagnostico{
    int ID;
    char descripcion[DEFAULT_LONG_STRING_SIZE];
    char nivel[DEFAULT_STRING_SIZE];
};


/**
    @struct Paciente
    @brief Estructura de datos utilizada almacenar informacion relativa a un paciente en especifico.

    @var Paciente::ID
    @brief "ID" contiene al identificador de un paciente en su respectiva base de datos.

    @var Paciente::rut
    @brief "rut" contiene el rut de un paciente.

    @var Paciente::email
    @brief "email" contiene el correo de un paciente.

    @var Paciente::nombre
    @brief "nombre" contiene el nombre de un paciente.

    @var Paciente::apellido
    @brief "apellido" contiene el apellido de un paciente.

    @var Paciente::fechaNacimiento
    @brief "fechaNacimiento" contiene la fecha de nacimiento de un paciente. En formato (dd/mm/aa).
*/

struct Paciente{
    int ID;
    char rut[DEFAULT_STRING_SIZE];
    char email[DEFAULT_STRING_SIZE];
    char nombre[DEFAULT_STRING_SIZE];
    char apellido[DEFAULT_STRING_SIZE];
    char fechaNacimiento[DEFAULT_STRING_SIZE];
};

/**
    @struct Doctor
    @brief Estructura de datos utilizada para almacenar informacion relativa a un doctor en especifico.

    @var Doctor::ID
    @brief "ID" contiene al identificador de un doctor en su respectiva base de datos.

    @var Doctor::rut
    @brief "rut" contiene el rut de un doctor.

    @var Doctor::email
    @brief "email" contiene el correo de un doctor.

    @var Doctor::nombre
    @brief "nombre" contiene el nombre de un doctor.

    @var Doctor::apellido
    @brief "apellido" contiene el apellido de un doctor.

    @var Doctor::especialidad
    @brief "especialidad" contiene la especialidad de un doctor.
*/
struct Doctor{
    int ID;
    char rut[DEFAULT_STRING_SIZE];
    char email[DEFAULT_STRING_SIZE];
    char nombre[DEFAULT_STRING_SIZE];
    char apellido[DEFAULT_STRING_SIZE];
    char especialidad[DEFAULT_STRING_SIZE];
};

/**
    @struct Tratamiento
    @brief Estructura de datos para almacenar informacion relativa a un tratamiento en especifico.

    @var Tratamiento::ID
    @brief "ID" contiene el identificador de un tratamiento en su respectiva base de datos.

    @var Tratamiento::nombre
    @brief "nombre" contiene el nombre de un tratamiento.

    @var Tratamiento::descripcion
    @brief "descripcion" contiene una breve descripcion de un tratamiento.

    @var Tratamiento::nivel
    @brief "nivel" contiene el nivel de riesgo que presenta un tratamiento (nulo, bajo, medio, alto, muy alto).
*/
struct Tratamiento{
    int ID;
    char nombre[DEFAULT_STRING_SIZE];
    char descripcion[DEFAULT_LONG_STRING_SIZE];
    char nivel[DEFAULT_STRING_SIZE];
};

/**
    @struct DiagnosticoPaciente
    @brief Estructura de datos para almacenar informacion relativa a la vinculacion entre un diagnostico y un paciente.

    @var DiagnosticoPaciente::ID
    @brief "ID" contiene el identificador de una vinculacion diagnostico-paciente en la base de datos.

    @var DiagnosticoPaciente::IDPaciente
    @brief "IDPaciente" contiene el identificador de un paciente relacionado con una vinculacion diagnostico-paciente.

    @var DiagnosticoPaciente::IDDiagnostico
    @brief "IDDiagnostico" contiene el identificador de un diagnostico relacionado con una vinculacion diagnostico-paciente.

    @var DiagnosticoPaciente::IDDoctorDiagnostico
    @brief "IDDoctorDiagnostico" contiene el identificador del doctor que llevo a cabo un diagnostico relacionado con una vinculacion diagnostico-paciente.

    @var DiagnosticoPaciente::IDDoctorAlta
    @brief "IDDoctorAlta" contiene el identificador del doctor que dio de alta a un paciente relacionado con una vinculacion diagnostico-paciente.

    @var DiagnosticoPaciente::fechaDiagnostico
    @brief "fechaDiagnostico" contiene la fecha en que se llevo a cabo un diagnostico relacionado con una vinculacion diagnostico-paciente.
    En formato (dd/mm/aa).

    @var DiagnosticoPaciente::estadoDiagnostico
    @brief "estadoDiagnostico" contiene el estado del diagnostico relacionado con una vinculacion diagnostico-paciente.

    @var DiagnosticoPaciente::fechaAlta
    @brief "fechaAlta" contiene la fecha en que se dio de alta al paciente relacionado con una vinculacion diagnostico-paciente.
    En formato (dd/mm/aa).

    @var DiagnosticoPaciente::detalleAlta
    @brief "detalleAlta" contiene una breve descripcion del alta de un paciente relacionado con una vinculacion diagnostico-paciente.
*/
struct DiagnosticoPaciente{
    int ID;
    int IDPaciente;
    int IDDiagnostico;
    int IDDoctorDiagnostico;
    int IDDoctorAlta;
    char fechaDiagnostico[DEFAULT_STRING_SIZE];
    char estadoDiagnostico[DEFAULT_STRING_SIZE];
    char fechaAlta[DEFAULT_STRING_SIZE];
    char detalleAlta[DEFAULT_LONG_STRING_SIZE];
};

/**
    @struct TratamientoDiagnostico
    @brief Estructura de datos para utilizada almacenar informacion relativa al vinculo entre un tratamiento y un diagnostico.

    @var TratamientoDiagnostico::IDDiagnostico
    @brief "IDDiagnostico" contiene el identificador del diagnostico relacionado con una vinculacion tratamiento-diagnostico.

    @var TratamientoDiagnostico::IDTratamiento
    @brief "IDTratamiento" contiene el identificador del tratamiento relacionado con una vinculacion tratamiento-diagnostico.
*/
struct TratamientoDiagnostico{
    int IDDiagnostico;
    int IDTratamiento;
};

/**
    @struct TratamientoDiagnosticoPaciente
    @brief Estructura de datos utilizada para almacenar informacion relativa al vinculo entre un tratamiento, un diagnostico y un paciente.

    @var TratamientoDiagnosticoPaciente::IDDiagnosticoPaciente
    @brief "IDDiagnosticoPaciente" contiene el identificador de la vinculacion diagnostico-paciente relacionado con una vinculacion
    tratamiento-diagnostico-paciente.

    @var TratamientoDiagnosticoPaciente::IDTratamiento
    @brief "IDTratamiento" contiene el identificador del tratamiento relacionado con una vinculacion tratamiento-diagnostico-paciente.

    @var TratamientoDiagnosticoPaciente::IDMedico
    @brief "IDMedico" contiene el identificador del medico relacionado con una vinculacion tratamiento-diagnostico-paciente.

    @var TratamientoDiagnosticoPaciente::fechaInicio
    @brief "fechaInicio" contiene la fecha en que se dio inicio a un tratamiento relacionado con una vinculacion tratamiento-diagnostico-paciente.

    @var TratamientoDiagnosticoPaciente::duracionDias
    @brief "duracionDias" contiene la duracion de un tratamiento, en dias, relacionado con una vinculacion tratamiento-diagnostico-paciente.

    @var TratamientoDiagnosticoPaciente::resultado
    @brief "resultado" contiene el resultado de un tratamiento relacionado con una vinculacion tratamiento-diagnostico-paciente
    (ej. exitoso, parcial, fracaso).
*/
struct TratamientoDiagnosticoPaciente{
    int IDDiagnosticoPaciente;
    int IDTratamiento;
    int IDMedico;
    char fechaInicio[DEFAULT_STRING_SIZE];
    int duracionDias;
    char resultado[DEFAULT_LONG_STRING_SIZE];
};

#endif /* ESTRUCTURAS_H */
