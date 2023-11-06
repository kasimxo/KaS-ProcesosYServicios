#include <stdio.h>

//Variables Globales
int TRUE = 1;
int FALSE = 0;
int sel;
int probando;

//Declaraciones de funciones
void menu();
void opciones();

int main(){
	probando = TRUE;
	while(probando == TRUE){
		printf("\nEl estado es: %d",probando);
		menu();
	}
	printf("\nSaliendo del programa sin errores.");
	return 0;
}

void menu(){
	printf("\nProgramación de servicios y procesos:\nIntroduce tu selección");
	opciones();
	scanf("%d", &sel);
	printf("\nHas seleccionado la opción: %d",sel);
	switch (sel){
		case 1:
			break;
		case 2:
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
			probando = FALSE;
			break;
		default:
			printf("Opción no reconocida");
			break;
	}
}

void opciones(){
	printf("\n1. ");
	printf("\n2. ");
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
