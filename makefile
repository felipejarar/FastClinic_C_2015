all:	
		gcc	-c Funciones/Diagnosticos.c -o Funciones/Diagnosticos.o
		gcc	-c Funciones/DiagnosticosPacientes.c -o Funciones/DiagnosticosPacientes.o
		gcc	-c Funciones/Doctores.c -o Funciones/Doctores.o
		gcc	-c Funciones/General.c -o Funciones/General.o
		gcc	-c Funciones/Pacientes.c -o Funciones/Pacientes.o
		gcc	-c Funciones/Tratamiento.c -o Funciones/Tratamiento.o
		gcc	-c Funciones/TratamientoDiagnosticoPaciente.c -o Funciones/TratamientoDiagnosticoPaciente.o
		gcc	-c Funciones/TratamientosDiagnosticos.c -o Funciones/TratamientosDiagnosticos.o
		

		gcc Main.c Funciones/Diagnosticos.o Funciones/DiagnosticosPacientes.o Funciones/Doctores.o Funciones/General.o Funciones/Pacientes.o Funciones/Tratamiento.o Funciones/TratamientoDiagnosticoPaciente.o Funciones/TratamientosDiagnosticos.o -o fastClinic
	
clear:
		rm -f Funciones/*.o 
		rm -f fastClinic
