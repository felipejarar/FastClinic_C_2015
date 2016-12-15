/*****************************************************************************************************************

       @file DiagnosticosPacientes.c
       @brief Archivo que contiene todas las funciones que relacionadas con la estructura DiagnosticoPaciente
       @author Felipe Ignacio Jara Ramirez (nialevolstel)
       @version 1.0
       @date 18 de Septiembre del 2014

*******************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../Estructuras/Estructuras.h"
#include "General.h"

#include "DiagnosticosPacientes.h"

/**
    @def ARCHIVO_DIAGNOSTICO_PACIENTE
    @brief Contiene la ruta en donde se encuentra la base de datos correspondiente a las vinculaciones diagnostico-paciente.

    @def COLUMNAS_DIAGNOSTICO_PACIENTE
    @brief Contiene la cantidad de elementos diferentes que estructuran la base de datos correspondiente a las vinculaciones diagnostico-paciente.

    @def REFERENCIA_DIAGNOSTICOS_PACIENTES
    @brief Contiene una referencia utilizada para realizar un conteo de la cantidad de vinculaciones diagnostico-paciente. contenidos en su respectiva
    base de datos. Es utilizado en la funcion contadorDeDatos() declarada en el archivo "General.c"
*/

#define COLUMNAS_DIAGNOSTICO_PACIENTE 9
#define REFERENCIA_DIAGNOSTICOS_PACIENTES 4
#define ARCHIVO_DIAGNOSTICO_PACIENTE "Bases de Datos/DiagnosticoPaciente.txt"



/*********************************************************************************************************************************************************


                  _   _                                         _     _                                           _                  _
                 | | (_)                                       | |   (_)                                         (_)                | |
               __| |  _    __ _    __ _   _ __     ___    ___  | |_   _    ___    ___      _ __     __ _    ___   _    ___   _ __   | |_    ___
              / _` | | |  / _` |  / _` | | '_ \   / _ \  / __| | __| | |  / __|  / _ \    | '_ \   / _` |  / __| | |  / _ \ | '_ \  | __|  / _ \
             | (_| | | | | (_| | | (_| | | | | | | (_) | \__ \ | |_  | | | (__  | (_) |   | |_) | | (_| | | (__  | | |  __/ | | | | | |_  |  __/
              \__,_| |_|  \__,_|  \__, | |_| |_|  \___/  |___/  \__| |_|  \___|  \___/    | .__/   \__,_|  \___| |_|  \___| |_| |_|  \__|  \___|
                                   __/ |                                                  | |
                                  |___/                                                   |_|


**********************************************************************************************************************************************************/

/**
    @brief          Funcion utilizada para obtener todo los registros relacionados con las vinculaciones diagnostico-paciente contenidos en su
                    correspondiente base de datos.

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente. Parametro pasado por referencia que, tras finalizar la ejecucion de la funcion, pasa a contener
                    toda la informacion relacionada con las vinculaciones diagnostico-paciente (identificadorDiagnosticoPaciente,  identificadorPaciente,
                    identificadorDiagnostico,fechaDiagnostico,identificadorDoctorDiagnostico,estadoDiagnostico,fechaAlta,identificadorDoctorAlta,detalleAlta).

    @param          cantidadDatos
                    Numero entero que representa la cantidad de registros (vinculaciones) contenidos en la base de datos. Tambien indica la dimension del
                    arreglo de estructura DiagnosticoPaciente entregado como parametro

    @return         Numero entero que indica la existencia de errores, en el caso de que existan.
                        \n a)  Retornar 0 indica que la funcion se ha llevado a cabo correctamente.
                        \n b)  Retornar un numero diferente de 0 indica que se ha presentado una anormalidad en la funcion cuando esta fue ejecutada.
*/
int lecturaDiagnosticosPacientes(struct DiagnosticoPaciente datos[], int cantidadDatos){

    FILE* archivo = fopen(ARCHIVO_DIAGNOSTICO_PACIENTE, "r");   /**< Se declara el puntero "archivo" para entregarle la referencia a un
                                                                        archivo de texto (base de dato) */

    if (archivo == NULL){
        return -1;
    }

    else{

        char stringAux[DEFAULT_STRING_SIZE];
        int fscanfAux = 0;
        int i = 0;
        int index = 0;

        fscanf(archivo, "%*[identificadorDiagnosticoPaciente,identificadorPaciente,identificadorDiagnostico,fechaDiagnostico,identificadorDoctorDiagnostico,estadoDiagnostico,fechaAlta,identificadorDoctorAlta,detalleAlta] %*[\n]"); // Se ignora la primera linea en el archivo.
        while (index < cantidadDatos && fscanfAux != EOF){

            switch(i){

                // Caso para agregar el identificador del diagnostico paciente
                case 0: fgets(stringAux, 1, archivo);
                        fscanf(archivo, "%[^,]", stringAux);
                        datos[index].ID = atoi(stringAux);
                        i++;

                // Caso para agregar el identificador del paciente
                case 1: fscanf(archivo, "%*[,] %[^,]", stringAux);
                        datos[index].IDPaciente = atoi(stringAux);
                        i++;

                // Caso para agregar el identificador del diagnostico
                case 2: fscanf(archivo, "%*[,] %[^,]", stringAux);
                        datos[index].IDDiagnostico = atoi(stringAux);
                        i++;

                // Caso para agregar la fecha del diagnostico
                case 3: fscanf(archivo, "%*[,] %[^,]", datos[index].fechaDiagnostico);
                        i++;

                // Caso para agregar el identificador del doctor del diagnostico
                case 4: fscanf(archivo, "%*[,] %[^,]", stringAux);
                        datos[index].IDDoctorDiagnostico = atoi(stringAux);
                        i++;

                // Caso para agregar el estado del diagnostico
                case 5: fscanf(archivo, "%*[,] %[^,]", datos[index].estadoDiagnostico);
                        i++;

                // Caso para agregar la fecha del dia de alta
                case 6: fscanf(archivo, "%*[,] %[^,]", datos[index].fechaAlta);
                        i++;

                // Caso para agregar el identificador del doctor del alta
                case 7: fscanf(archivo, "%*[,] %[^,]", stringAux);
                        datos[index].IDDoctorAlta = atoi(stringAux);
                        i++;

                // Caso para agregar detalles sobre el alta
                case 8: fscanf(archivo, "%*[,] %[^\n] %*[\n] ", datos[index].detalleAlta);
                        i = 0;
                        index++;
            }

        }

    fclose(archivo);
    return 0;

        }
}


/**

    @brief          Funcion para realizar un conteo sobre la cantidad de veces que se repite el identificador de un paciente en la base de datos
                    Diagnostico-Paciente

    @param          IDPaciente
    @brief          Identificador del paciente

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente.

    @return         Cantidad de repeticiones del paciente en la base de datos Diagnostico-Paciente
*/
int contarPacienteEnDiagnosticosPacientes(int IDPaciente, struct DiagnosticoPaciente datos[], int cantidadDatos){
    int contador = 0;
    int index;
    for (index = 0; index < cantidadDatos; index++){
        if (datos[index].IDPaciente == IDPaciente){
            contador++;
        }
    }
    return contador;
}

/**

    @brief          Funcion utilizada para realizar un conteo de la cantidad de veces que se repite simultaneamente el identificador de un paciente junto
                    con el identificador de un diagnostico en la base de datos Diagnostico-Paciente

    @param          IDPaciente
    @brief          Identificador del paciente

    @param          IDDiagnostico
    @brief          Identificador del diagnostico

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente.

    @return         Cantidad de repeticiones de ambos identificadores ingresados en la base de datos Diagnostico-Paciente
*/
int contarPacienteYDiagnosticoEnDiagnosticosPacientes(int IDPaciente, int IDDiagnostico, struct DiagnosticoPaciente datos[], int cantidadDatos){
    int contador = 0;   /**<    Se declara la variable local "contador" con el proposito de contener la cantidad de veces que
                                se encuentra al identificador paciente y al identificador diagnostico simultaneamente en uno
                                de los registros contenidos en datos */
    int index;
    for (index = 0; index < cantidadDatos; index++){
        if (datos[index].IDPaciente == IDPaciente && datos[index].IDDiagnostico == IDDiagnostico){
            contador++;
        }
    }
    return contador;
}

/**

    @brief          Procedimiento utilizado para encontrar todos los identificadores de Diagnostico pretenecientes a un paciente en especifico

    @param          IDPaciente
    @brief          Identificador del paciente.

    @param          diagnosticosRealizados
    @brief          Cantidad de diagnosticos realizados para el paciente cuyo identificador fue entregado como parametro. Tambien in

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente.

    @param          identificadoresDiagnostico
    @brief          Arreglo de identificadores Diagnostico. Parametro pasado por referencia que al finalizar la funcion pasa a contener todos los
                    identificadores Diagnosttico relacionado con cierto identificador Paciente.

    @return         void.
*/
void encontrarIdentificadoresDiagnostico(int IDPaciente, int diagnosticosRealizados, struct DiagnosticoPaciente datos[], int cantidadDatos, int identificadoresDiagnostico[]){

    int datosAgregados = 0;     /**<    Se declara la variable "datosAgregados" como una forma de detener el ciclo for cuando se hayan encontrado
                                        todos los identificadores Diagnostico relacionados con IDPaciente. */
    int index;
    for (index = 0; index < cantidadDatos && datosAgregados <= diagnosticosRealizados; index++){
        if (datos[index].IDPaciente == IDPaciente){
            identificadoresDiagnostico[datosAgregados] = datos[index].IDDiagnostico;
            datosAgregados++;
        }
    }
}


/**

    @param          Procedimiento utilizado para encontrar todos los identificadores de las vinculaciones entre Diagnostico y Paciente
                    relacionados con el identificador de un paciente en particular.

    @param          IDPaciente
    @brief          Identificador del paciente.

    @param          diagnosticosRealizados
    @brief          Representa la cantidad diagnosticos que un paciente tiene en la base de datos y la cantidad de identificadores
                    DiagnosticoPaciente relacionado con el. Tambien indica la dimension del arreglo identificadoresDiagnosticoPaciente.

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente.

    @param          identificadoresDiagnosticoPaciente
    @brief          Arreglo de identificadores DiagnosticoPaciente. Parametro pasado por referencia que al finalizar la funcion pasa a contener todos los
                    identificadores DiagnosticoPaciente relacionado con cierto identificador Paciente.

    @return         void.
*/
void encontrarIdentificadoresDiagnosticoPaciente(int IDPaciente, int diagnosticosRealizados, struct DiagnosticoPaciente datos[], int cantidadDatos, int identificadoresDiagnosticoPaciente[]){

    int datosAgregados = 0;     /**<    Se declara la variable "datosAgregados" como una forma de detener el ciclo for cuando se hayan encontrado
                                        todos los identificadores DiagnosticoPaciente relacionados con IDPaciente. */

    int index;
    for (index = 0; index < cantidadDatos && datosAgregados <= diagnosticosRealizados; index++){
        if (datos[index].IDPaciente == IDPaciente){
            identificadoresDiagnosticoPaciente[datosAgregados] = datos[index].ID;
            datosAgregados++;
        }
    }
}


/**

    @brief          Procedimiento utilizado para encontrar todos los identificadores de las vinculaciones entre Diagnostico y Paciente
                    relacionado con cierto identificador Paciente y cierto identificador, ambos entregados como parametro.

    @param          IDPaciente
    @brief          Identificador del paciente.

    @param          IDDiagnostico
    @brief          Identificador del diagnostico.

    @param          cantidadDiagnosticosEstudiados
    @brief          Cantidad de vinculaciones DiagnosticoPaciente relacionados con IDPaciente e IDDiagnostico. Tambien representa la
                    dimension del arreglo identificadoresDiagnosticoPaciente ingresado como parametro.

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente entregado como parametro.

    @param          identificadoresDiagnosticoPaciente
    @brief          Arreglo de identificadores. Parametro pasado por referencia que al finalizar la funcion pasa a contener todos los
                    identificadores DiagnosticoPaciente relacionado con cierto identificador Paciente y cierto identificador Diagnostico.

    @return         void
*/

void encontrarIdentificadoresDiagnosticoPacienteSegunPacienteYDiagnostico(int IDPaciente, int IDDiagnostico, int cantidadDiagnosticosEstudiados, struct DiagnosticoPaciente datos[], int cantidadDatos, int identificadoresDiagnosticoPaciente[]){

    int datosAgregados = 0;     /**<    Se declara la variable "datosAgregados" como una forma de detener el ciclo for cuando se hayan encontrado
                                        todos los identificadores DiagnosticoPaciente relacionados con IDPaciente e IDDiagnostico. */

    int index;

    for (index = 0; index < cantidadDatos && datosAgregados <= cantidadDiagnosticosEstudiados; index++){
        if (datos[index].IDPaciente == IDPaciente && datos[index].IDDiagnostico ==  IDDiagnostico){
            identificadoresDiagnosticoPaciente[datosAgregados] = datos[index].ID;
            datosAgregados++;
        }
    }
}



/**

    @brief          Funcion utilizada para verificar, en la informacion obtenida a partir de la base de datos, si los diagnosticos de
                    un paciente estan todos anulados o no.

    @param          IDPaciente
    @brief          Identificador del paciente cuyos diagnosticos se pretenden verificar.

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente entregado como parametro.

    @return         Numero entero que indica si el paciente presenta o no diagnosticos.
                    \n  a)  0 indica que todos los diagnosticos del pacientes estan anulados.
                    \n  b)  -1 indica que el paciente tiene almenos un diagnostico.
*/
int verificarDiagnosticoNuloEnPaciente(int IDPaciente, struct DiagnosticoPaciente datos[], int cantidadDatos){

    int verificador = 0;    /**<    Se declara la variable verificador como una forma de indicar si el paciente presenta
                                    o no diagnosticos */

    int index;
    for (index = 0; index < cantidadDatos && verificador == 0; index++){
        if (datos[index].IDPaciente == IDPaciente){
            if (strcmp(datos[index].estadoDiagnostico, "anulado") != 0){
                verificador = -1;
                return verificador;
            }
        }
    }
    return verificador;
}

/**
    @brief          Funcion utilizada para verificar si un particular presenta diagnosticos vigentes o no. Explicado de otra manera,
                    utilizada para verificar si al menos uno de los diagnosticos relacionados con los identificadores DiagnosticoPaciente
                    entregado estan en vigencia o no.

    @param          identificadoresDiagnosticoPaciente
    @brief          Arreglo que contiene un conjunto de identificadores DiagnosticoPaciente, pertenecientes a un
                    medico en particular.

    @param          cantidadIdentificadores
    @brief          Cantidad de identificadores contenidos en el arreglo identificadoresDiagnosticoPaciente.

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente entregado como parametro.

    @return         Numero entero que indica si hay almenos un diagnostico en vigencia o no.
                    \n  a)  0 indica que ninguno de los diagnosticos esta vigente.
                    \n  b)  -1 indica que almenos uno de los diagnosticos esta vigente.
*/
int verificarMedicosSinDiagnosticosVigentes(int identificadoresDiagnosticoPaciente[], int cantidadIdentificadores, struct DiagnosticoPaciente datos[], int cantidadDatos){

    int verificador = 0;    /**<    Se declara la variable "verificador" como una forma de indicar si hay diagnosticos vigentes o no */
    int i,j;
    for (i = 0; i < cantidadIdentificadores; i++ ){
        for (j = 0; j < cantidadDatos; j++){
            if (datos[j].ID == identificadoresDiagnosticoPaciente[i]){
                if(strcmp(datos[j].estadoDiagnostico,"vigente") == 0){
                    verificador = -1;
                    return verificador;
                }
            }
        }
    }
    return verificador;
}

/**
    @brief          Funcion utilizada para encontrar la vinculacion Diagnostico-Paciente con la fecha de alta más reciente

    @param          identificadoresDiagnosticoPaciente
    @brief          Arreglo que contiene un conjunto de identificadores DiagnosticoPaciente.

    @param          cantidadIdentificadores
    @brief          Cantidad de identificadores contenidos en el arreglo identificadoresDiagnosticoPaciente.

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente entregado como parametro.

    @return         Identificador DiagnosticoPaciente con la fecha de alta mas reciente.
*/
int encontrarFechaDeAltaMasRecienteSegundIDDiagnosticoPaciente( int identificadoresDiagnosticoPaciente[], int cantidadIdentificadores, struct DiagnosticoPaciente datos[], int cantidadDatos){

    int auxFechai[3], auxFechaj[3]; /**<    Se declaran las variables "auxFechai" y "auxFechaj" como una forma de contener una fecha transformada
                                            desde una cadena de caracteres a un arreglo de enteros. Facilitando de esta manera la comparacion
                                            para determinar que fecha es mas reciente que la otra. */

    int IDretorno;  /**<    Se declara "IDretorno" para almacenar el identificador DiagnosticoPaciente cuya fecha de alta es la mas reciente */

    int auxBreak = 0; /**<      Se declara "auxBreak" como una forma de detener los ciclos for utilizados para recorrer los elementos contenidos
                                en "datos", parametro que contiene toda la informacion relacionada con las vinculaciones entre Diagnostico y Paciente. */

    int i,j;
    // Se le da un valor inicial a auxFechai
    for (j = 0; j < cantidadDatos && auxBreak == 0; j++){
        if (datos[j].ID == identificadoresDiagnosticoPaciente[0]){
            transformarFecha(datos[j].fechaAlta, auxFechai);
            IDretorno = identificadoresDiagnosticoPaciente[0];
            auxBreak = -1;
        }
    }

    // Se recorren todos los elementos del arreglo de identificadores Diagnostico Paciente
    for (i = 1; i < cantidadIdentificadores; i++){
        auxBreak = 0;
        // Se recorren todos los elementos del arreglo de datos Diagnostico Paciente
        for (j = 0; j < cantidadDatos && auxBreak == 0; j++){
            // Se consideran solo aquellos datos que corresponden a los identificadores Diagnotico Paciente entregados como argumento
            if (datos[j].ID == identificadoresDiagnosticoPaciente[i]){
                auxBreak = -1;
                // Se obtiene la fecha de alta del dato sobre el cual se esta trabajando (se transforma a entero)
                transformarFecha(datos[j].fechaAlta, auxFechaj);
                // Se realizan las comparaciones para determinar cual es mas reciente. COmparando primero los años
                if (auxFechai[2] < auxFechaj[2]){
                    auxFechai[0] = auxFechaj[0];
                    auxFechai[1] = auxFechaj[1];
                    auxFechai[2] = auxFechaj[2];
                    IDretorno = identificadoresDiagnosticoPaciente[i];

                }

                else if(auxFechai[2] == auxFechaj[2]){
                    // Los años son los mismos, entonces se comparan los meses
                    if (auxFechai[1] < auxFechaj[1]){
                        auxFechai[0] = auxFechaj[0];
                        auxFechai[1] = auxFechaj[1];
                        auxFechai[2] = auxFechaj[2];
                        IDretorno = identificadoresDiagnosticoPaciente[i];
                    }

                    else if (auxFechai[1] == auxFechaj[1]){
                        // Los meses son los mismos, entonces se comparan los dias
                        if (auxFechai[0] < auxFechaj[0]){
                            auxFechai[0] = auxFechaj[0];
                            auxFechai[1] = auxFechaj[1];
                            auxFechai[2] = auxFechaj[2];
                            IDretorno = identificadoresDiagnosticoPaciente[i];
                        }
                    }
                }
            }
        }
    }

    return IDretorno;

}


/**
    @brief          Funcion utilizada para modificar en la base de datos el medico que da el alta para cierto identificador DiagnosticoPaciente

    @param          IDDiagnosticoPaciente
    @brief          Identificador de la vinculacion Diagnostico Paciente cuyo medico de alta se pretende reemplazar.

    @param          IDMedicoAlta
    @brief          Identificador del medico que pretende reemplazar al medico que da el alta para el DiagnosticoPaciente cuyo identificador
                    fue entregado como parametro.

    @param          datos
    @brief          Arreglo de estructura DiagnosticoPaciente que contiene toda la informacion relacionada con las vinculaciones entre
                    Diagnostico y Paciente.

    @param          cantidadDatos
    @brief          Cantidad de vinculaciones existentes en la base de datos. Indica ademas la dimension del arreglo de estructura
                    DiagnosticoPaciente entregado como parametro.

    @return         Numero entero que indica la existencia de errores, en el caso de que existan.
                    \n a)  Retornar 0 indica que la funcion se ha llevado a cabo correctamente.
                    \n b)  Retornar un numero diferente de 0 indica que se ha presentado una anormalidad en la funcion cuando esta fue ejecutada.

*/
int outputModificarMedicoDeAlta(int IDDiagnosticoPaciente, int IDMedicoAlta, struct DiagnosticoPaciente datos[], int cantidadDatos){

    FILE* archivo = fopen(ARCHIVO_DIAGNOSTICO_PACIENTE,"w"); /**<   Se declara el puntero "archivo" para entregarle la referencia a la base de
                                                                    datos correspondiente a las vinculaciones entre diagnostico y paciente. */

    if (archivo == NULL){
        escribirMensajeDeError("Se ha presentado un error al momento de abrir la base de datos DiagnosticoPaciente");
        return -1;
    }

    else{

        int i;

        fprintf(archivo,"identificadorDiagnosticoPaciente,identificadorPaciente,identificadorDiagnostico,fechaDiagnostico,identificadorDoctorDiagnostico,estadoDiagnostico,fechaAlta,identificadorDoctorAlta,detalleAlta\n");
        for (i = 0; i < cantidadDatos; i++){
            if (datos[i].ID == IDDiagnosticoPaciente){
                fprintf(archivo, "%d,%d,%d,%s,%d,%s,%s,%d,%s\n", datos[i].ID, datos[i].IDPaciente, datos[i].IDDiagnostico, datos[i].fechaDiagnostico, datos[i].IDDoctorDiagnostico, datos[i].estadoDiagnostico, datos[i].fechaAlta, IDMedicoAlta, datos[i].detalleAlta);
            }

            else{
                fprintf(archivo, "%d,%d,%d,%s,%d,%s,%s,%d,%s\n", datos[i].ID, datos[i].IDPaciente, datos[i].IDDiagnostico, datos[i].fechaDiagnostico, datos[i].IDDoctorDiagnostico, datos[i].estadoDiagnostico, datos[i].fechaAlta, datos[i].IDDoctorAlta, datos[i].detalleAlta);
            }
        }

        fclose(archivo);

        FILE* output = fopen(ARCHIVO_OUTPUT,"a"); /**<  Se declara el puntero "output" y se le entrega la referencia del archivo output
                                                        para poder escribir un mensaje que comunique al usuario de que el reemplazo de
                                                        medicos se ha llevado a cabo correctamente. */

        if ( output != NULL){
            fprintf(output,"Se ha modificado correctamente el medico que da el alta \n");
            fclose(output);
        }

        return 0;
    }
}



