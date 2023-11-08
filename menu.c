#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

//Variables Globales
int TRUE = 1;
int FALSE = 0;
int sel;
//Probando -> Esta variable almacena si queremos salir del programa. 
//Mientras sea TRUE, seguiremos con el menu
int probando;
//Suboproceso -> Esta variable bloquea este proceso (padre)
//si hay un proceso hijo
int subproceso;
int pidSubproceso;

//Declaraciones de funciones
void menu();
void opciones();

int main(){
	probando = TRUE;
	subproceso = FALSE;
	pidSubproceso = -1;
	while(probando == TRUE){
		if(subproceso == FALSE){
			if(pidSubproceso>0 && (kill(pidSubproceso,0))==0) {
				printf("\nHay un subproceso en ejecución, por lo que ");
				printf("el proceso padre, con pid %d, va a detener su ejecución hasta que el proceso hijo, con pid %d, finalice.",getpid(),pidSubproceso);
				subproceso = TRUE;
			} else {
				printf("\nNo hay ningún subproceso en ejecución.");
				pidSubproceso = -1;
				subproceso = FALSE;
				menu();
			}
		}
	}
	printf("\nSaliendo del programa sin errores.\n");
	return 0;
}

void menu(){
	printf("\nProgramación de servicios y procesos:\nIntroduce tu selección");
	opciones();
	scanf("%d", &sel);
	printf("\nHas seleccionado la opción: %d",sel);
	switch (sel){
		case 1:
			//Uso de system()
			directorio();
			break;
		case 2:
			//Uso de fork
			fibo();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			//Salir del programa
			probando = FALSE;
			break;
		default:
			printf("\nOpción no reconocida");
			break;
	}
}

void opciones(){
	printf("\n1. Directorio");
	printf("\n2. Fibonacci");
	printf("\n3. ");
	printf("\n4. ");
	printf("\n5. ");
	printf("\n6. ");
	printf("\n7. ");
	printf("\n8. ");
	printf("\n9. ");
	printf("\n10. ");
	printf("\n11. Salir\n");
}
void directorio(){
	printf("\nSe va a consultar el directorio actual mediante el uso de system():\n");
	int resultado = system("pwd");
	if(resultado == 0) {
		printf("\nLa consulta del directorio no ha dado errores.");
	} else {
		printf("\nHa surgido un error consultando el directorio actual.");
	}
}

void fibo() {
	printf("\nSe va a iniciar un nuevo proceso para generar la secuencia de Fibonacci mediante el uso de fork:");
	printf("\nEl PID del proceso padre es: %d", getpid());
	pid_t pid;
	printf("\nIniciando subproceso.");	
	
	if ((pid=fork()) < 0) {
		perror("\nHa fallado el uso de fork");
	} else if(pid == 0) {
		printf("\nEl PID del proceso hijo es: %d", getpid());
		fibonacci();
		printf("\nCerramos el proceso hijo.");
		exit(1);
	} else if(pid>0){
		pidSubproceso=pid;	
	}
}

void fibonacci(){
	int contador;
	int n1 = 0;
	int n2 = 1;
	printf("\n¿Cuántos número de la secuencia de Fibonacci quieres generar?");
	scanf("%d", contador);
}
