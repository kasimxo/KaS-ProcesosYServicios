#include <stdio.h>

//Esta macro comprueba si el sistema operativo es Linux
//Puede haber ciertas distribuciones que se salten esta comprobacion
#if defined(__linux__)
	#define LINUX TRUE
#else
	#define LINUX FALSE
#endif

//Definiciones globales
int TRUE = 1;
int FALSE = 0;
int bateriaTotal;
int bateriaActual;
float porcentaje;

//Definición de funciones
double calcularPorcentaje();
int consultarBateriaActual();
int consultarBateriaTotal();

int main(int argc, char* argv[]) {
	printf("\nSe va a consultar la capacidad total de la bateria");
	//Antes de ejecutar el programa comprobamos si es un SO Linux
	if(LINUX==TRUE){
		bateriaTotal = consultarBateriaTotal();
		bateriaActual = consultarBateriaActual();
		porcentaje = calcularPorcentaje();
		printf("\nEl porcentaje actual de la batería es: %.2f %%\n", porcentaje);
		return 0;
	} else {
		printf("\nNo se ha podido certificar que el sistema operativo sea Linux");
		printf("\nPor seguridad, se va a detener la ejecución del programa");
		return -1;
	}
}

double calcularPorcentaje() {
	double total = bateriaTotal * 1.00;
	double actual = bateriaActual * 1.00;
	double porcentaje = actual/total * 100.00;
	return porcentaje;
}

int consultarBateriaActual() {
	FILE *actBateria;
	actBateria = fopen("/sys/class/power_supply/BAT0/charge_now","r");
	char bateria[8];
	if(fgets(bateria, 8, actBateria)!=NULL){
		printf("\nLa batería actual es: %s", bateria);
		int ret = 0;
		for(int i = 0; i<7; i++){
			ret += (bateria[i] - 'O' + 31);
			ret *= 10;
		}
		ret /=10;	
		fclose(actBateria);
		return ret;
	} else {
		printf("\nSe ha producido un error tratando de leer la batería actual");
		fclose(actBateria);
		return -1;
	}
}

int consultarBateriaTotal() {
	FILE *totBateria;
	totBateria = fopen("/sys/class/power_supply/BAT0/charge_full","r");
	char capacidad[8];
	if(fgets(capacidad, 8, totBateria)!=NULL){
		printf("\nLa capacidad es: %s",capacidad);
		int ret = 0;
		for(int i = 0; i<7; i++){
			ret += (capacidad[i] - 'O' + 31);
			ret *=10;	
		}
		ret /=10;
		fclose(totBateria);
		return ret;
	} else {
		printf("\nSe ha producido un error tratando de leer la capacidad de la bateria");
		fclose(totBateria);
		return -1;
	}
}
