#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

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
void bateria();
void directorio();
void fibo();
void fibonacci();
int factorial();
int introducirNumero();
int comprobarNumero();
int stringToInt();
void pausa();
void usuarioActual();

int main(int argc, char* argv[]){
	probando = TRUE;
	while(probando == TRUE){
		menu();
	}
	printf("\nSaliendo del programa sin errores.\n");
	return 0;
}

void menu(){
	system("clear");
	printf("Programación de servicios y procesos:\nIntroduce tu selección");
	opciones();
	sel = introducirNumero("\nIntroduce tu selección: ");
	printf("\nHas seleccionado la opción: %d",sel);
	switch (sel){
		case 1:
			//Uso de system()
			directorio();
			break;
		case 2:
			//Uso de fork
			contador = introducirNumero("\nIntroduce la cantidad de números de la secuencia de Fibonacci que quieres generar: ");
			fibo();
			break;
		case 3:
			//Uso de una función recursiva
			contador = introducirNumero("\nIntroduce el valor del que quieres calcular el factorial: ");
			printf("El valor de %d! es %d",contador,factorial(contador));
			break;
		case 4:
			//Uso de excel()
			bateria();
			break;
		case 5:
			//Recupera el nombre de usuario actual e invierte la cadena 
			usuarioActual();
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
//Este método utiliza una pipe para recuperar datos al ejecutar un comando
void usuarioActual() {
	FILE *fp;
	char path[1035];
	char usuario[25];
	fp = popen("whoami","r");
	if (fp == NULL) {
		printf("\nNo se ha podido consultar el usuario actual");
	}

	while (fgets(path, sizeof(path), fp) != NULL) {
		printf("\n%s", path);
		
	}
	
	int contador = 0;
	while (contador<= 25 && path[contador] != ' ') {
		usuario[contador] = path[contador];
		contador++;
	}
	
	printf("\nEl usuario actual es: %s", usuario);
	printf("\nEl nombre del usaurio invertido es: \n");
	for(int i = sizeof(usuario); i>=0; i--) {
		if(usuario[i]!=' ') {
			printf("%c", usuario[i]);
		}
	}
	

	pclose(fp);
	pausa();
}

void pausa() {
	printf("\nPulsa cualquier tecla y presiona enter para continuar...");
	char dummy;
	char pulsado[100];
	scanf("%c",&dummy);
	scanf("%c",&pulsado);
}

//Este método muestra un texto y pide al usuario que introduzca un número
//Comprueba que sea un número y no otra cosa
//Si no es un número, vuelve a pedir al usuario que lo introduzca
int introducirNumero(char texto[]) {
	char escaneado[100];
	do {
		printf("%s", texto);
		scanf("%s",&escaneado);
	} while (comprobarNumero(escaneado)==FALSE);

	return stringToInt(escaneado);	
}

int stringToInt(char escaneado[]) {
	int valor = 0;
	for(int i = 0; i<strlen(escaneado); i++) {
		valor +=(escaneado[i] - 'O' + 31);
		valor *= 10;
	}
	valor /= 10;
	return valor;
}

int comprobarNumero(char escaneado[]){
	for(int i = 0; i<strlen(escaneado); i++) {
		if(isdigit(escaneado[i])==0) {
			printf("\nEl valor introducido no es válido");
			return FALSE;
		}
	}
	return TRUE;
}

void bateria(){
	printf("\nSe va a consultar la bateria actual mediante la ejecución del programa 'Bateria' con excel()");
	char *argumentos[] = {"./Bateria", NULL};
	pid_t p;
	if((p = fork())<0){
		printf("\nHa surgido un error tratando de ejecutar el programa 'Batería'");
	} else if (p == 0) {
		execl("./Bateria", NULL);
	} else 	{
		int status;
		waitpid(p, &status,WUNTRACED);	
		printf("\nSe ha consultado la batería sin errores");
		pausa();
	}


	//execl(argumentos[0],NULL);
}

void opciones(){
	printf("\n1. Directorio");
	printf("\n2. Fibonacci");
	printf("\n3. Factorial");
	printf("\n4. Batería");
	printf("\n5. Usuario");
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
	pausa();
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
	} else if(pid>0){
		printf("\nEl proceso padre va a esperar a que el proceso hijo finalice");
		int status;
		waitpid(pid, &status,WUNTRACED);	
		printf("\nEl proceso padre va a reanudar su funcionamiento");
	}
	pausa();
}

void fibonacci(){
	int n1 = 0;
	int n2 = 1;
	printf("\nImprimiendo la secuencia");
	printf("\nSe van a generar %d numeros de fibonacci",contador);
	printf("\n%d\n%d",n1,n2);
	for(int i = 0; i<contador - 2; i++){
		int aux = n2;
		n2 += n1;
		n1 = aux;
		printf("\n%d",n2);
	}
	printf("\nCerramos el proceso hijo.");
	exit(0);
}
int factorial(int value) {
	if(value<2){
		return 1;
	} else{
		int aux = factorial(value-1);
		return value * aux;
	}
	pausa();
}

