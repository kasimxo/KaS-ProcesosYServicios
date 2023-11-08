#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//Variables Globales
int TRUE = 1;
int FALSE = 0;
int sel;
int contador;
//Probando -> Esta variable almacena si queremos salir del programa. 
//Mientras sea TRUE, seguiremos con el menu
int probando;
pid_t pidSubproceso;

//Declaraciones de funciones
void menu();
void opciones();

int main(){
	probando = TRUE;
	while(probando == TRUE){
		menu();
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
			printf("\nIntroduce la cantidad de números de la secuencia de Fibonacci que quieres generar: ");
			scanf("%d", &contador);
			fibo();
			break;
		case 3:
			//Uso de una función recursiva
			printf("\nIntroduce el valor del que quieres calcular el factorial: ");
			scanf("%d", &contador);
			printf("El valor de %d! es %d",contador,factorial(contador));
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
	printf("\n3. Factorial");
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
	printf("\nIniciando subproceso.");	
		
	pid_t pid = fork();
	
	if (pid < 0) {
		perror("\nHa fallado el uso de fork");
	} else if(pid == 0) {
		printf("\nEl PID del proceso hijo es: %d", getpid());
		fibonacci();
		printf("\nCerramos el proceso hijo.");
	} else if(pid>0){
		printf("\nEl proceso padre va a esperar a que el proceso hijo finnalice");
		int status;
		waitpid(pid, &status,WUNTRACED);	
		printf("\nEl proceso padre va a reanudar su funcionamiento");
	}

}

void fibonacci(){
	int n1 = 0;
	int n2 = 1;
	printf("\nImprimiendo la secuencia");
	printf("\nSe van a generar %d numeros de fibonacci",contador);
	printf("\n%d\n%d",n1,n2);
	for(int i = 0; i<contador; i++){
		int aux = n2;
		n2 += n1;
		n1 = aux;
		printf("\n%d",n2);
	}
	printf("\n");
	exit(0);
}
int factorial(int value) {
	if(value<2){
		return 1;
	} else{
		int aux = factorial(value-1);
		return value * aux;
	}
}

