#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Estructuras/Estructuras.h"

#include "Funciones/Pacientes.h"
#include "Funciones/Doctores.h"
#include "Funciones/TratamientoDiagnosticoPaciente.h"
#include "Funciones/TratamientosDiagnosticos.h"
#include "Funciones/Diagnosticos.h"
#include "Funciones/DiagnosticosPacientes.h"
#include "Funciones/Tratamiento.h"

#define DEFAULT_STRING_SIZE 50
#define DEFAULT_LONG_STRING_SIZE 1024

#define ARCHIVO_TRATAMIENTO_DIAGNOSTICO "Bases de Datos/TratamientoDiagnostico.txt"
#define REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS 5
#define COLUMNAS_TRATAMIENTO_DIAGNOSTICO 2

#define ARCHIVO_TRATAMIENTO_DIAGNOSTICO_PACIENTE "Bases de Datos/TratamientoDiagnosticoPaciente.txt"
#define COLUMNAS_TRATAMIENTO_DIAGNOSTICO_PACIENTE 6
#define REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES 6

#define ARCHIVO_TRATAMIENTOS "Bases de Datos/Tratamiento.txt"
#define COLUMNAS_TRATAMIENTOS 4
#define REFERENCIA_TRATAMIENTOS 3

#define ARCHIVO_DOCTORES "Bases de Datos/Doctor.txt"
#define COLUMNAS_DOCTORES 6
#define REFERENCIA_DOCTORES 1

#define COLUMNAS_DIAGNOSTICO_PACIENTE 9
#define REFERENCIA_DIAGNOSTICOS_PACIENTES 4
#define ARCHIVO_DIAGNOSTICO_PACIENTE "Bases de Datos/DiagnosticoPaciente.txt"

#define ARCHIVO_DIAGNOSTICOS "Bases de Datos/Diagnostico.txt"
#define REFERENCIA_DIAGNOSTICOS 2
#define COLUMNAS_DIAGNOSTICO 3

#define ARCHIVO_PACIENTES "Bases de Datos/Paciente.txt"
#define COLUMNAS_PACIENTES 6
#define REFERENCIA_PACIENTES 0

#define ARCHIVO_TRATAMIENTO_DIAGNOSTICO "Bases de Datos/TratamientoDiagnostico.txt"
#define REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS 5
#define COLUMNAS_TRATAMIENTO_DIAGNOSTICO 2

#define ARCHIVO_TRATAMIENTO_DIAGNOSTICO_PACIENTE "Bases de Datos/TratamientoDiagnosticoPaciente.txt"
#define COLUMNAS_TRATAMIENTO_DIAGNOSTICO_PACIENTE 6
#define REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES 6

#define ARCHIVO_TRATAMIENTOS "Bases de Datos/Tratamiento.txt"
#define COLUMNAS_TRATAMIENTOS 4
#define REFERENCIA_TRATAMIENTOS 3

#define ARCHIVO_DOCTORES "Bases de Datos/Doctor.txt"
#define COLUMNAS_DOCTORES 6
#define REFERENCIA_DOCTORES 1

#define COLUMNAS_DIAGNOSTICO_PACIENTE 9
#define REFERENCIA_DIAGNOSTICOS_PACIENTES 4
#define ARCHIVO_DIAGNOSTICO_PACIENTE "Bases de Datos/DiagnosticoPaciente.txt"

#define ARCHIVO_DIAGNOSTICOS "Bases de Datos/Diagnostico.txt"
#define REFERENCIA_DIAGNOSTICOS 2
#define COLUMNAS_DIAGNOSTICO 3

#define ARCHIVO_OUTPUT "Output/output.txt"



int main(int argc, char* argv[]){

    /**
        Se realiza la lectura de todas las base de datos, almacenando toda la informacion contenida en variables cuyas estructuras estan definidas
        en el archivo Estructuras.h
    */

    int CANTIDAD_PACIENTES = contadorDeDatos(ARCHIVO_PACIENTES,REFERENCIA_PACIENTES, COLUMNAS_PACIENTES);
	struct Paciente pacientes[CANTIDAD_PACIENTES];
	lecturaPacientes(pacientes, CANTIDAD_PACIENTES);

    int CANTIDAD_DOCTORES = contadorDeDatos(ARCHIVO_DOCTORES,REFERENCIA_DOCTORES,COLUMNAS_DOCTORES);
    struct Doctor doctores[CANTIDAD_DOCTORES];
    lecturaDoctores(doctores, CANTIDAD_DOCTORES);

    int CANTIDAD_DIAGNOSTICOS = contadorDeDatos(ARCHIVO_DIAGNOSTICOS,REFERENCIA_DIAGNOSTICOS,COLUMNAS_DIAGNOSTICO);
    struct Diagnostico diagnosticos[CANTIDAD_DIAGNOSTICOS];
    lecturaDiagnosticos(diagnosticos,CANTIDAD_DIAGNOSTICOS);

    int CANTIDAD_TRATAMIENTOS = contadorDeDatos(ARCHIVO_TRATAMIENTOS,REFERENCIA_TRATAMIENTOS,COLUMNAS_TRATAMIENTOS);
    struct Tratamiento tratamientos[CANTIDAD_TRATAMIENTOS];
    lecturaTratamientos(tratamientos, CANTIDAD_TRATAMIENTOS);

    int CANTIDAD_DIAGNOSTICOS_PACIENTES = contadorDeDatos(ARCHIVO_DIAGNOSTICO_PACIENTE,REFERENCIA_DIAGNOSTICOS_PACIENTES,COLUMNAS_DIAGNOSTICO_PACIENTE);
    struct DiagnosticoPaciente diagnosticosPacientes[CANTIDAD_DIAGNOSTICOS_PACIENTES];
    lecturaDiagnosticosPacientes(diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);

    int CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS = contadorDeDatos(ARCHIVO_TRATAMIENTO_DIAGNOSTICO,REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS,COLUMNAS_TRATAMIENTO_DIAGNOSTICO);
    struct TratamientoDiagnostico tratamientosDiagnosticos[CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS];
    lecturaTratamientosDiagnosticos(tratamientosDiagnosticos, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS);

    int CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES = contadorDeDatos(ARCHIVO_TRATAMIENTO_DIAGNOSTICO_PACIENTE,REFERENCIA_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES,COLUMNAS_TRATAMIENTO_DIAGNOSTICO_PACIENTE);
    struct TratamientoDiagnosticoPaciente tratamientosDiagnosticosPacientes[CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES];
    lecturaTratamientosDiagnosticosPacientes(tratamientosDiagnosticosPacientes, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES);

    int verificador = 0;    /**<    Se declara la variable local "verificador" como una forma de indicar la presencia de errores en cualquiera de las funciones utilizadas. La variable
                                    permanece con el valor 0 en caso de que ninguna anormalidad haya ocurrido en la ejecucion del programa. */

        // Nivel Facil

    // a) Obtener el nombre de un paciente dado su rut.
    if(strcmp(argv[1],"-obtenerPaciente") == 0 || strcmp(argv[1], "-obtenerNombrePaciente") == 0){
        // Se obtiene el identificador del paciente
        int ID = buscarPacientePorRut(argv[2],pacientes,CANTIDAD_PACIENTES);

        // En el caso de que el rut del paciente no pudo ser encontrado en la base de datos
        if (ID == -1){
            escribirMensajeDeError("No se ha logrado encontrar el rut ingresado en la base de datos");
            verificador = -1;
        }

        else{
            // Se escribe en un archivo output el nombre del paciente
            verificador = outputNombrePaciente(ID,pacientes,CANTIDAD_PACIENTES);
        }
    }

    // b) Obtener la especialidad de un médico a partir de su rut.
    else if(strcmp(argv[1],"-especialidad") == 0){
        // Se obtiene el identificador del doctor
        int ID = buscarDoctorPorRut(argv[2],doctores,CANTIDAD_DOCTORES);
        // En el caso de que no pudo encontrarse el rut en la base de datos
        if (ID == -1){
            escribirMensajeDeError("No ha sido posible encontrar el rut ingresado en la base de datos");
        }

        else{
            // Se escribe en un archivo output la especialidad del doctor
            verificador = outputEspecialidadDoctor(ID,doctores,CANTIDAD_DOCTORES);
        }
    }

    // c) Listar el o los tratamientos de acuerdo a un nivel de riesgo dado.
    else if(strcmp(argv[1],"-tratamientoRiesgoso") == 0){
        verificador = outputListarTratamientosSegunNivel(argv[2],tratamientos,CANTIDAD_TRATAMIENTOS);
    }

    // r) Modificar el correo electrónico de un paciente. Se asume que el correo es unico.
    else if (strcmp(argv[1],"-modificarCorreoPaciente") == 0){
        verificador = outputModificarCorreoPaciente(argv[2],argv[3],pacientes, CANTIDAD_PACIENTES);
    }

    // s) Modificar el resultado de un tratamiento de un paciente.
    else if (strcmp(argv[1],"-modificarEstadoPaciente") == 0){
        int cantidadDiagnosticoEnPaciente = contarPacienteEnDiagnosticosPacientes( atoi(argv[2]), diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES );
        int identificadoresDiagnosticoPaciente[cantidadDiagnosticoEnPaciente];
        encontrarIdentificadoresDiagnosticoPaciente(atoi(argv[2]), cantidadDiagnosticoEnPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES, identificadoresDiagnosticoPaciente);
        verificador = outputModificarResultadoTratamiento(identificadoresDiagnosticoPaciente, cantidadDiagnosticoEnPaciente, atoi(argv[3]), tratamientosDiagnosticosPacientes, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES, argv[4]);
    }

        // Nivel Medio

    // w) Dado el nombre y apellido de un paciente, modificar el resultado de un tratamiento.
    else if (strcmp(argv[1],"-modificarResultadoTratamiento") == 0){
        //  Se busca en la base de datos el identificador del paciente de nombre y apellido ingresado como argumento
        int IDPaciente = buscarPacientePorNombreYApellido(argv[2],argv[3], pacientes, CANTIDAD_PACIENTES);
        //  Se verifica si el paciente existe o no en la base de datos
        if (IDPaciente == -1){

            /* Llegando a este punto del programa, no ha sido posible encontrar el paciente en la base de datos, por lo que
                se le comunica dicho resultado al usuario mediante el archivo output */

            FILE*   output = fopen(ARCHIVO_OUTPUT,"a");
            if (output != NULL){
                fprintf(output,"ERROR: No ha sido posible encontrar al paciente %s %s en la base de datos\n\n",argv[2],argv[3]);
                fclose(output);
            }
            verificador = -1;
        }

        else{

            /* Llegando a este punto del programa, se ha encontrado el paciente en la base de datos, por lo que
                se procede a verificar si el Tratamiento entregado como parametro existe tambien en ella */

            int IDTratamiento = atoi(argv[4]);
            verificador = verificarExistenciaDeTratamiento(IDTratamiento, tratamientos, CANTIDAD_TRATAMIENTOS);
            if (verificador == -1){

                /* Llegando a este punto del programa, no ha sido posible encontrar el tratamiento ingresado como
                    parametro en su respectiva base de datos */

                FILE*   output = fopen(ARCHIVO_OUTPUT,"a");
                if (output != NULL){
                    fprintf(output,"ERROR: No ha sido posible encontrar el tratamiento (ID:%d) en la base de datos\n\n",IDTratamiento);
                    fclose(output);
                }
            }

            else{

                /* Llegando a este punto del programa se sabe que paciente y tratamiento existen en la base de datos,
                    por lo que ahora se procede a modificar los resultados de un tratamiento */

                // Se realiza un conteo de la cantidad de veces que se repite el paciente en la base de datos DiagnosticoPaciente
                int cantidadRepeticiones = contarPacienteEnDiagnosticosPacientes(IDPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
                // Se obtienen los identificadores DiagnosticoPaciente relacionado con el paciente
                int identificadoresDiagnosticoPaciente[cantidadRepeticiones];
                encontrarIdentificadoresDiagnosticoPaciente(IDPaciente, cantidadRepeticiones, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES, identificadoresDiagnosticoPaciente);
                // Se obtienen los identificadores Tratamientos relacionados con los identificadoresDiagnosticoPaciente
                int identificadoresTratamientos[cantidadRepeticiones];
                encontrarIdentificadoresTratamientoSegunDiagnosticoPaciente(identificadoresDiagnosticoPaciente, identificadoresTratamientos, cantidadRepeticiones, tratamientosDiagnosticosPacientes, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES);
                // Se verifican si uno de esos Tratamientos corresponde al ingresado como parametro
                int index;
                verificador = -1;
                for (index = 0; index < cantidadRepeticiones && verificador == -1; index++){
                    if (identificadoresTratamientos[index] == IDTratamiento){
                        verificador = 0;
                    }
                }

                // Si verificador es -1, significa que al usuario no le corresponde el identificador de tratamiento ingresado
                if (verificador == -1){
                    // Se escribe un mensaje de error en el archivo output
                    FILE*   output = fopen(ARCHIVO_OUTPUT,"a");
                    if (output != NULL){
                        fprintf(output,"ERROR: Al paciente %s %s no le corresponde el tratamiento ID:%d \n\n",argv[2],argv[3],IDTratamiento);
                        fclose(output);
                    }
                }

                else{
                    // Se realiza la modificacion del tratamiento en la base de datos
                    outputModificarResultadoTratamiento(identificadoresDiagnosticoPaciente, cantidadRepeticiones, IDTratamiento, tratamientosDiagnosticosPacientes, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES, argv[5]);
                }
            }
        }
    }

    // u) Eliminar un paciente, siempre y cuando este no tenga diagnósticos.
    else if (strcmp(argv[1],"-eliminarPaciente") == 0){
        int IDPaciente = buscarPacientePorRut(argv[2], pacientes, CANTIDAD_PACIENTES);
        verificador = -2;

        // En el caso de que el rut del paciente haya sido encontrado en la base de datos
        if (IDPaciente != -1){
            verificador = verificarDiagnosticoNuloEnPaciente(IDPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
        }

        // OUTPUT
        if (verificador == 0){
            // Es posible eliminar el paciente
            verificador = outputEliminarPaciente(IDPaciente, pacientes, CANTIDAD_PACIENTES);
        }

        else if (verificador == -1){
            escribirMensajeDeError("No ha sido posible eliminar el paciente ya que este aun posee diagnosticos vigentes");
        }

        else if (verificador == -2){
            escribirMensajeDeError("El rut ingresado no ha podido ser encontrado en la base de datos");
        }
    }

    // n) Listar los tratamientos que ha recibido un paciente a partir de su correo electrónico.
    else if (strcmp(argv[1],"-tratamientosPacienteCorreo") == 0){
        // Se obtiene el identificador del paciente
        int IDPaciente = buscarPacientePorCorreo(argv[2], pacientes, CANTIDAD_PACIENTES);
        // En el caso de que el identificador no haya podido ser encontrado
        if (IDPaciente == -1){
            escribirMensajeDeError("No ha sido posible encontrar el mail ingresado en la base de datos");
        }

        else{
            // Se obtiene la cantidad de diagnosticos relacionados con el paciente
            int cantidadDiagnosticosDePaciente = contarPacienteEnDiagnosticosPacientes(IDPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
            // En el caso de que al paciente no le corresponda ningun diagnostico
            if (cantidadDiagnosticosDePaciente == 0){
                escribirMensajeDeError("El paciente ingresado no tiene ningun diagnostico asignado y, por lo tanto, ningun tratamiento asignado");
                verificador = -1;
            }

            else{
                int identificadoresDiagnosticos[cantidadDiagnosticosDePaciente];
                int identificadoresTratamientos[cantidadDiagnosticosDePaciente];
                // Se obtienen los identificadores de los diagnosticos relacionados con el paciente
                encontrarIdentificadoresDiagnostico(IDPaciente, cantidadDiagnosticosDePaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES, identificadoresDiagnosticos);
                // Se obtienen los identificadores de los tratamientos relacionados con los diagnosticos
                encontrarIdentificadoresTratamientoSegunDiagnostico(identificadoresDiagnosticos, identificadoresTratamientos, cantidadDiagnosticosDePaciente, tratamientosDiagnosticos, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS);
                // Se enlistan los tratamientos
                verificador = outputListarTratamientosSegunID(identificadoresTratamientos, cantidadDiagnosticosDePaciente, tratamientos, CANTIDAD_TRATAMIENTOS);
            }
        }
    }

    // m) Dado el identificador de un paciente, indicar el rut, nombre y apellido de todos los médicos que lo han atendido.
    else if (strcmp(argv[1],"-medicosTratantes") == 0){
        // Se verifica si el identificador ingresado existen en la base de datos
        int IDPaciente = atoi(argv[2]);
        verificador = verificarIdentificadorPaciente(IDPaciente, pacientes, CANTIDAD_PACIENTES);
        // En el caso de que el identificador no haya podido ser encontrado en la base de datos
        if (verificador == -1){
            escribirMensajeDeError("No se ha podido encontrar el identificador del paciente ingresado en la base de datos");
        }

        else{
            // Se realiza un conteo de la cantidad de diagnosticos que le corresponde a un paciente
            int cantidadDiagnosticosDePaciente = contarPacienteEnDiagnosticosPacientes( IDPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
            // Si al paciente no le corresponde ningun diagnostico
            if (cantidadDiagnosticosDePaciente == 0){
                escribirMensajeDeError("El paciente ingresado no se ha realizado ningun diagnostico y, por lo tanto, nigun medico lo ha atendido");
                verificador = -1;
            }

            else{
                int IDDiagnosticosDePaciente[cantidadDiagnosticosDePaciente];
                int IDMedicos[cantidadDiagnosticosDePaciente];
                // Se obtienen los identificadores DiagnosticoPaciente relacionados con el paciente
                encontrarIdentificadoresDiagnosticoPaciente(IDPaciente, cantidadDiagnosticosDePaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES, IDDiagnosticosDePaciente);
                // Se obtienen los identificadores Medico relacionados con los identificadores DiagnosticoPaciente
                encontrarIdentificadoresMedicos(IDDiagnosticosDePaciente, IDMedicos, cantidadDiagnosticosDePaciente, tratamientosDiagnosticosPacientes, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES);
                // Se enlistan los medicos en un archivo output
                verificador = outputListarMedicos(IDMedicos, cantidadDiagnosticosDePaciente, doctores, CANTIDAD_DOCTORES);
            }
        }
    }

    // l) Determinar qué tratamientos puede recibir un paciente a partir de su diagnostico
    else if (strcmp(argv[1],"-tratamientosDiagnosticoPaciente") == 0){
        // Se verifica la existencia del identificador paciente ingresado como argumento en la base de datos
        int IDPaciente = atoi(argv[3]);
        verificador = verificarIdentificadorPaciente(IDPaciente, pacientes, CANTIDAD_PACIENTES);
        // Para el caso en que el identificador no exista
        if (verificador == -1){
            escribirMensajeDeError("No se ha podido encontrar el identificador del paciente ingresado en la base de datos");
        }

        else{
            // Se verifica la existencia del identificador Diagnostico ingresado como argumento en la base de datos
            int IDDiagnostico = atoi(argv[2]);
            verificador = verificarIdentificadorDiagnostico(IDDiagnostico, diagnosticos, CANTIDAD_DIAGNOSTICOS);
            // Ṕara el caso en que el identificador no exista en la base de datos
            if (verificador == -1){
                escribirMensajeDeError("No se ha podido encontrar el identificador del diagnostico en la base de datos");
            }

            else{
                // Se realiza un conteo de la cantidad de identificadores DiagnosticoPaciente relacionados con IDPaciente e IDDiagnosticos
                int cantidadDiagnosticoPaciente = contarPacienteYDiagnosticoEnDiagnosticosPacientes(IDPaciente, IDDiagnostico, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
                // Si no existe tal identificador, entonces se lanza un mensaje de error:
                if (cantidadDiagnosticoPaciente == 0){
                    escribirMensajeDeError("No existe ningun Tratamiento para el paciente y el diagnostico ingresado");
                }
                else{
                    // Se procede a buscar los identificadores DiagnosticoPaciente relacionados con IDPaciente e IDDiagnostico
                    int identificadoresDiagnosticoPaciente[cantidadDiagnosticoPaciente];
                    encontrarIdentificadoresDiagnosticoPacienteSegunPacienteYDiagnostico(IDPaciente, IDDiagnostico, cantidadDiagnosticoPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES, identificadoresDiagnosticoPaciente);
                    // Se procede a buscar los identificadores Tratamiento relacionados con los identificadores Diagnostico Paciente
                    int identificadoresTratamiento[cantidadDiagnosticoPaciente];
                    encontrarIdentificadoresTratamientoSegunDiagnosticoPaciente(identificadoresDiagnosticoPaciente, identificadoresTratamiento, cantidadDiagnosticoPaciente, tratamientosDiagnosticosPacientes, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES);
                    // Se procede a escribir sobre el archivo output los tratamientos que puede recibir el paciente
                    verificador = outputListarTratamientosSegunID(identificadoresTratamiento, cantidadDiagnosticoPaciente, tratamientos, CANTIDAD_TRATAMIENTOS);
                }
            }
        }
    }


        // Dificiles

    // q) Dado el rut de un paciente, indicar el rut, nombre y apellido de todos los médicos que lo han atendido.
    else if (strcmp(argv[1],"-listarMedicosTratantesPaciente") == 0){
        // Se obtiene el identificador del paciente
        int IDPaciente = buscarPacientePorRut(argv[2], pacientes, CANTIDAD_PACIENTES);
        // En el caso de que no se pueda encontrar el paciente mediante el rut ingresado
        if (IDPaciente == -1){
            // Se escribe en output un mensaje de error
            FILE* output = fopen(ARCHIVO_OUTPUT,"a");
            if (output != NULL){
                fprintf(output,"ERROR!: El paciente de rut %s no ha sido encontrado en la base de datos\n\n",argv[2]);
                fclose(output);
            }
            verificador = -1;
        }

        // Se ha obtenido exitosamente el identificador del paciente
        else{
            // Se realiza un conteo de la cantidad de diagnosticos que posee el paciente
            int cantidadDiagnosticosDePaciente = contarPacienteEnDiagnosticosPacientes( IDPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
            // Si el paciente no tiene diagnosticos
            if (cantidadDiagnosticosDePaciente == 0){
                FILE* output = fopen(ARCHIVO_OUTPUT,"a");
                if (output != NULL){
                    fprintf(output,"ERROR!: El paciente (ID:%d) no se ha hecho ningun diagnostico y, por lo tanto, nigun medico lo ha atendido\n\n",IDPaciente);
                    fclose(output);
                }
                verificador = -1;
            }
            // Si el paciente tiene diagnosticos
            else{
                int IDDiagnosticosDePaciente[cantidadDiagnosticosDePaciente];
                int IDMedicos[cantidadDiagnosticosDePaciente];
                // Se encuentran los identificadores DiagnosticoPaciente relacionados con el paciente
                encontrarIdentificadoresDiagnosticoPaciente(IDPaciente, cantidadDiagnosticosDePaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES, IDDiagnosticosDePaciente);
                // Se encuentran los identificadores de los Medicos relacionados con los identificadores DiagnosticoPaciente
                encontrarIdentificadoresMedicos(IDDiagnosticosDePaciente, IDMedicos, cantidadDiagnosticosDePaciente, tratamientosDiagnosticosPacientes, CANTIDAD_TRATAMIENTOS_DIAGNOSTICOS_PACIENTES);
                // Se escribe en output la lista de Medicos
                verificador = outputListarMedicos(IDMedicos, cantidadDiagnosticosDePaciente, doctores, CANTIDAD_DOCTORES);
            }
        }
    }

    // y) Dado el correo del paciente y del médico, modificar el médico que da el alta.
    else if (strcmp(argv[1],"-modificarMedicoAlta") == 0){
        printf("hEYYY");
        // Se encuentra el identificador del paciente
        int IDPaciente = buscarPacientePorCorreo(argv[2], pacientes, CANTIDAD_PACIENTES);
        // Si no ha sido posible encontrar el identificador del paciente
        if (IDPaciente == -1){
            escribirMensajeDeError("No ha sido posible encontrar el correo del paciente en la base de datos");
        }

        else{
            // Se encuentra el identificador del medico
            int IDMedico = buscarDoctorPorCorreo(argv[3], doctores, CANTIDAD_DOCTORES);
            // Si no ha sido posible encontrar el identificador del medico
            if (IDMedico == -1){
                escribirMensajeDeError("No ha sido posible encontrar el correo del medico en la base de datos");
            }

            else{
                // Se realiza un conteo de la cantidad de veces que se repite el paciente simultaneamente en la base de datos DiagnosticoPaciente
                int cantidadSegunPaciente = contarPacienteEnDiagnosticosPacientes(IDPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
                // Se obtienen todos los Identificadores diagnosticos pacientes relacionados con el paciente
                int identificadoresDiagnosticoPaciente[cantidadSegunPaciente];
                encontrarIdentificadoresDiagnosticoPaciente(IDPaciente, cantidadSegunPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES, identificadoresDiagnosticoPaciente);
                // Se obtiene el identificador DiagnosticoPaciente con la fecha de alta mas reciente
                int IDDiagnosticoPaciente = encontrarFechaDeAltaMasRecienteSegundIDDiagnosticoPaciente(identificadoresDiagnosticoPaciente,cantidadSegunPaciente, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
                // Se modifica el medico que da el alta en la base de datos
                verificador = outputModificarMedicoDeAlta(IDDiagnosticoPaciente, IDMedico, diagnosticosPacientes, CANTIDAD_DIAGNOSTICOS_PACIENTES);
            }
        }
    }

    // Si se ingresa una funcionalidad no existente
    else{
        escribirMensajeDeError("La funcionalidad ingresada no existe en el sistema");
    }
	return verificador;
}















