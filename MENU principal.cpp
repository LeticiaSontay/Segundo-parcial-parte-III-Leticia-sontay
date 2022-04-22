#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<cstdlib>
#include<iomanip>
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

void menuInicial();

main(){
	menuInicial();
}

void menuInicial() {
	char repite = 1;
	int opcion = -1;

	do {
		system("cls");
		printf("\n\t\t\t  Menu Laboratorio clinico\n");
		printf("\t\t\t============================\n");
		printf("\t\t\tLeticia Sontay 9491-21-9664\n");
		printf("\n\t\t(1). VER EMPLEADOS REGISTRADOS\n");
		printf("\t\t(2). REGISTRAR NUEVO EMPLEADO\n");
		printf("\t\t(3). ACCEDER AL SISTEMA\n");
		printf("\t\t(0). SALIR\n");
		printf("\n\t\tQue deseas hacer hoy?: [ ]\b\b");

		switch (opcion) {
			case 1:
				menuListarUsuarios();
				break;

			case 2:
				menuRegistrarUsuario();
				break;

			case 3:
				menuIniciarSesion();
				break;

			case 0:
				repite = 0;
				break;
		}

	} while (repite == 1);
}
