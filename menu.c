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
FILE *registro;
//REGISTRANDO -> Esta variable almacena si tenemos abierto un subproceso que este registrando las opciones que introducimos
int REGISTRANDO;
pid_t pidSubprocesoRegistro;
//fp -> es la pipe que pasa las selecciones al proceso hijo de registro de seleccion
int fp[2];

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
void mostrarRegistroOpciones();
void eliminarRegistroOpciones();
void abrirPipe();
void leerPipe();
void cerrarPipe();
void consola();

int main(int argc, char* argv[]){
	probando = TRUE;
	REGISTRANDO = FALSE;
	while(probando == TRUE){
		menu();
	}
	printf("\nSaliendo del programa sin errores.\n");
	return 0;
}

void menu(){
	system("clear");
	printf("Programación de servicios y procesos:");
	if(REGISTRANDO == TRUE) {
		printf("\nRegistro de opciones: ON");
	} else {
		printf("\nRegistro de opciones: OFF");
	}
	opciones();
	sel = introducirNumero("\nIntroduce tu selección: ");
	
	if(REGISTRANDO == TRUE && sel > 0 && sel < 12) {
		char str[5];
		sprintf(str, "%d", sel);
		write(fp[1], str, 5);
		printf("\nSe ha registrado la opción: %d", sel);
	}

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
			pausa();
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
			//Permite al usuario ejecutar comandos en la consola
			consola();
			break;
		case 7:
			//Eliminar el registro de opciones
			eliminarRegistroOpciones();
			
			break;
		case 8:
			//Consulta del archivo de registro de opciones
			mostrarRegistroOpciones();
			break;
		case 9:
			//Apertura de pipe
			//Comienzo de registro de opciones
			abrirPipe();
			break;
		case 10:
			//Cierre de pipe
			cerrarPipe();
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
	while (contador<= 25 && path[contador] >47 && path[contador]<123) {
		usuario[contador] = path[contador];
		contador++;
	}
	
	printf("\nEl usuario actual es: %s", usuario);
	printf("\nEl nombre del usaurio invertido es: ");
	for(int i = contador; i>=0; i--) {
			printf("%c", usuario[i]);
	}
	

	pclose(fp);
	pausa();
}

void pausa() {
	printf("\nPulsa cualquier tecla y presiona enter para continuar...");
	char dummy;
	char pulsado[100];
	scanf("%c%*c",&dummy);
	//scanf("%c",&pulsado);
}

//Este método muestra un texto y pide al usuario que introduzca un número
//Comprueba que sea un número y no otra cosa
//Si no es un número, vuelve a pedir al usuario que lo introduzca
int introducirNumero(char texto[]) {
	char escaneado[100];
	do {
		printf("%s", texto);
		scanf("%s%*c",&escaneado);
	} while (comprobarNumero(escaneado)==FALSE);
	if (REGISTRANDO == TRUE) {
	}
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
}

void opciones(){
	printf("\n\n 1. Directorio");
	printf("\n 2. Fibonacci");
	printf("\n 3. Factorial");
	printf("\n 4. Batería");
	printf("\n 5. Usuario");
	printf("\n 6. Consola");
	printf("\n 7. Eliminar registro de opciones");
	printf("\n 8. Consultar registro de opciones");
	printf("\n 9. Iniciar registro de opciones");
	printf("\n10. Finalizar registro de opciones");
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

//Este método se encarga de iniciar el subproceso que va a generar la secuencia
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

//Este método genera los números de la secuencia
void fibonacci(){
	int n1 = 0;
	int n2 = 1;
	printf("\nImprimiendo la secuencia");
	printf("\nSe van a generar %d numeros de fibonacci",contador);
	printf("\n%d\n%d",n1,n2);
	//Imprimimos exactamente tantos números como el usuario haya introducido
	for(int i = 0; i<contador - 2; i++){
		int aux = n2;
		n2 += n1;
		n1 = aux;
		printf("\n%d",n2);
	}
	printf("\nCerramos el proceso hijo.");
	exit(0);

}

//Este método genera el valor factorial de manera recursiva
int factorial(int value) {
	if(value<2){
		return 1;
	} else{
		int aux = factorial(value-1);
		return value * aux;
	}
}

void mostrarRegistroOpciones() {
	if(access("RegistroOpciones", F_OK) == 0) {
		printf("\nMostrando el contenido del Registro de Opciones");
		system("cat RegistroOpciones");
	} else {
		printf("\nNo se ha encontrado el registro de opciones. ¿Seguro que habías creado alguno?");
	}
	pausa();
}

void eliminarRegistroOpciones() {
	//No permitimos la usuario eliminar el registro si se está registrando en ese momento
	if(REGISTRANDO == TRUE) {
		printf("\nActualmente se están registrando las opciones\nPara poder eliminar el archivo de registro de opciones, primero debes finalizar el registro de opciones");
		pausa();
		return;
	}
	if(access("RegistroOpciones", F_OK) == 0) {
		int resultado = system("rm RegistroOpciones");
		if(resultado == 0) {
			printf("\nSe ha eliminado el registro de opciones con éxito");
		} else {
			printf("\nSe ha encontrado un error tratando de eliminar el registro de opciones");
		}
	} else {
	
		printf("\nNo se ha encontrado el registro de opciones. ¿Seguro que habías creado alguno?");
	}
	pausa();
}

void abrirPipe() {
	//Comprobamos si ya estamos registrando y si abortamos si es el caso
	if(REGISTRANDO == TRUE) {
		printf("\nYa se estaban registrando las opciones");
		pausa();
		return;
	}
	
	//Comprobamos si existe el archivo de RegistroOpciones y si no, lo creamos
	if(access("RegistroOpciones", F_OK) != 0) {
		system("echo > RegistroOpciones");
		registro = fopen("RegistroOpciones", "w");
		fprintf(registro, "Selección\tFecha y hora\n");
		fclose(registro);
	}
	
	//Abrimos el Pipe entre procesos
	if( pipe(fp) == -1 ) {
		printf("\nHa surgido un error en la apertura del pipe");
	} else {
		pidSubprocesoRegistro = fork();
		if(pidSubprocesoRegistro < 0) {
			perror("\nHa fallado la apertura del registro de opciones");
		} else if ( pidSubprocesoRegistro == 0) {
			close(fp[1]);
			probando = FALSE;
			leerPipe();	
		} else {
			REGISTRANDO = TRUE;
			close(fp[0]);
			printf("\nSe ha iniciado el registro de opciones");
			pausa();
		}
	}	
}

void leerPipe() {
	
	char* input[5];
	
	ssize_t rc;
	while( (rc = read(fp[0], input, 5)) > 0){
		FILE *ff;
		FILE* registroOpciones;
		registroOpciones = fopen("RegistroOpciones","a");
	
		char hora[35];
		char *com = "date";
		ff = popen(com, "r");
		
		fgets(hora, sizeof(hora), ff);

		fprintf(registroOpciones, "%s\t\t%s", input, hora);
		fclose(registroOpciones);
		fclose(ff);
	}
	exit(0);
}

void cerrarPipe() {
	if(REGISTRANDO == TRUE) {
		REGISTRANDO = FALSE;
		printf("\nSe ha detenido el registro de opciones");
		kill(pidSubprocesoRegistro, SIGKILL);
	} else {
		printf("\nNo se estaban registrando las opciones, por lo que no hay nada que detener");
	}
	pausa();
}

void consola() {
	printf("\nIntroduce el comando que quieres ejecutar en la consola: ");
	fflush(stdin);
	char input[100];
	char comando[100];
	fgets(input, sizeof(input), stdin);
	if((strlen(input) > 0) && (input[strlen(input)-1] == '\n')) {
		input[strlen(input)-1] = '\0';
	}
	system(input);
	pausa();
}
