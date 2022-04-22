#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<cstdlib>
#include<iomanip>
#include <iostream>
#include <vector>
#include <fstream>

#define MAX 80
#define ARCHIVO_USUARIOS "usuarios.dat"
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 5
#define MAX_INTENTOS 3

using std::cout; using std::ofstream;
using std::endl; using std::string;
using std::cin;

/* Estructura de cuentas de usuario */
struct usuario {
	char nombre[MAX];
	char password[MAX];
};

typedef struct usuario Usuario;

/* Funciones de menú */
void menuInicial();
void menuListarUsuarios();
void menuRegistrarUsuario();
void menuIniciarSesion();
void menuSistema();

/* Funciones que manipulan el archivo de usuarios */
char insertarUsuario(Usuario usuario);
char existeUsuario(char nombreUsuario[], Usuario *usuario);
Usuario *obtenerUsuarios(int *);
char logear(char nombreUsuario[], char password[]);

int leerLinea(char *cad, int n);
void leerClave(char *password);
char hora();

char usuarioglob;

using namespace std;
class persona
{
	private:
		string id,name,phone,date,address,exam,price;
	public:
		void menu();
		void insert();
		void insert2();
		void insert3();
		void display();
		void search();
};

char linea[MAX];
int main() {
	menuInicial();
	return 0;
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
		leerLinea(linea, MAX);
		sscanf(linea, "%d", &opcion);

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

void menuRegistrarUsuario() {
	Usuario usuario;
	char nombreUsuario[MAX];
	char respuesta[MAX];
	char repite = 1;

	do {
		system("cls");
		printf("\n\t\t\tREGISTRAR EMPLEADO\n");
		printf("\t\t\t==================\n");
		printf("\n\tIngrese usuario del empleado: ");
		leerLinea(linea, MAX);
		sscanf(linea, "%s", nombreUsuario);

		/* Se verifica que el nombre de usuario no exista */
		if (!existeUsuario(nombreUsuario, &usuario)) {
			strcpy(usuario.nombre, nombreUsuario);

			printf("\tIngrese la clave: ");
			leerLinea(usuario.password, MAX);

			/* Se inserta el usuario en el archivo de usuarios */
			if (insertarUsuario(usuario)) {
				printf("\n\tSe ha registrado exitosamente!\n");

			} else {
				printf("\n\tOcurrio un error al registrar el usuario\n");
				printf("\nInténtelo mas tarde\n");
			}
		} else {
			printf("\n\tEl usuario \"%s\" ya ha sido registrado\n", usuario.nombre);
			printf("\tNo puede registrar dos usuarios con el mismo nombre de usuario.\n");
		}

		printf("\n\tDesea seguir registrando usuarios? Si/No: ");
		leerLinea(respuesta, MAX);

		if (!(strcmp(respuesta, "Si") == 0 || strcmp(respuesta, "si") == 0)) {
			repite = 0;
		}

	} while (repite == 1);
}

void menuListarUsuarios() {
	int numeroUsuarios = 0;
	Usuario *usuarios;
	int i;

	system("cls");
	usuarios = obtenerUsuarios(&numeroUsuarios); /* Retorna un vector dinámico de usuarios */

	if (numeroUsuarios == 0) {
		printf("\n\tNo hay ningun usuario registrado!\n");

	} else {
		printf("\n\t\t    > EMPLEADOS REGISTRADOS <\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf("%10s%25s%25s\n", "#", "NOMBRE", "PASWORD");
		printf(" ------------------------------------------------------------------------------\n");

		/* Se recorre el vector dinámico de productos */
		for (i = 0; i < numeroUsuarios; i++) {
			printf("%10d%25s%25s\n", (i + 1), usuarios[i].nombre, usuarios[i].password);
		}
		printf(" ------------------------------------------------------------------------------\n");
	}

	// Se libera la memoria asignada al vector dinámico
	free(usuarios);
	usuarios = NULL;
	getchar();
}

void menuIniciarSesion() {
	char nombreUsuario[MAX];
	char password[MAX];
	int intento = 0;
	int loginExitoso = 0;

	do {
		system("cls");
		printf("\n\t\t\tINGRESA AL SISTEMA\n");
		printf("\t\t\t===================\n");

		printf("\n\t\tUSUARIO: ");
		leerLinea(linea, MAX);
		sscanf(linea, "%s", nombreUsuario);

		printf("\t\tCLAVE: ");
		leerClave(password);

		if (logear(nombreUsuario, password)) {
			loginExitoso = 1;
		} else {
			printf("\n\n\t\tUsuario y/o Contraseña incorrectos");
			intento++;
			getchar();
		}
	} while (intento < MAX_INTENTOS && loginExitoso == 0);

	if (loginExitoso == 1) {
		menuSistema();

	} else {
		printf("\n\tHa sobrepasado el numero de intentos permitidos\n");
		getchar();
	}
}

void menuSistema() {
	system("cls");

	persona estudiante;
	estudiante.menu();

	getchar();
}

/* Retorna 1 si se registró el usuario en el archivo correctamente */
char insertarUsuario(Usuario usuario) {
	FILE *archivo;
	char insercion = 0;

	/* Abre el archivo en modo de añadidura, para agregar datos al final. Si no existe es creado*/
	archivo = fopen(ARCHIVO_USUARIOS, "ab");

	if (archivo == NULL) {
		insercion = 0;

	} else {
		/* Registra el struct usuario en el archivo */
		fwrite(&usuario, sizeof(usuario), 1, archivo);
		insercion = 1;

		/* Cierra el archivo */
		fclose(archivo);
	}

	return insercion;
}

/* Retorna 1 si existe el nombre de usuario. Retorna el usuario buscado si existe */
char existeUsuario(char nombreUsuario[], Usuario* usuario) {
	FILE *archivo;
	char existe;

	/* Abre el archivo en modo de lectura */
	archivo = fopen(ARCHIVO_USUARIOS, "rb");

	if (archivo == NULL) {
		existe = 0;

	} else {
		existe = 0;

		/* Lee secuencialmente del archivo de usuarios */
		fread(&(*usuario), sizeof(*usuario), 1, archivo);
		while (!feof(archivo)) {
			if (strcmp((*usuario).nombre, nombreUsuario) == 0) {
				/* Encuentra un usuario del archivo con el nombre de usuario buscado */
				existe = 1;
				break;
			}

			fread(&(*usuario), sizeof(*usuario), 1, archivo);
		}

		/* Cierra el archivo*/
		fclose(archivo);
	}

	return existe;
}

Usuario *obtenerUsuarios(int *n) {
	FILE *archivo;
	Usuario usuario;
	Usuario *usuarios; /* Vector dinámico de usuarios */
	int i;

	/* Abre el archivo en modo lectura */
	archivo = fopen(ARCHIVO_USUARIOS, "rb");

	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		*n = 0; /* No se pudo abrir. Se considera n = 0 */
		usuarios = NULL;

	} else {

		fseek(archivo, 0, SEEK_END); /* Posiciona el cursor al final del archivo */
		*n = ftell(archivo) / sizeof(Usuario); /* # de usuarios almacenados en el archivo. (# de registros) */
		usuarios = (Usuario *)malloc((*n) * sizeof(Usuario)); /* Se asigna memoria para todos los usuarios almacenados en el archivo */

		/* Se recorre el archivo secuencialmente */
		fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
		fread(&usuario, sizeof(usuario), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			usuarios[i++] = usuario;
			fread(&usuario, sizeof(usuario), 1, archivo);
		}

		/* Cierra el archivo */
		fclose(archivo);
	}

	return usuarios;
}

/* Retorna 1 o 0 si el usuario y password son correctos para un usuario en particular */
char logear(char nombreUsuario[], char password[]) {
	FILE *archivo;
	char logeoExitoso;
	Usuario usuario;

	/* Abre el archivo en modo de lectura */
	archivo = fopen(ARCHIVO_USUARIOS, "rb");

	if (archivo == NULL) {
		logeoExitoso = 0;

	} else {
		logeoExitoso = 0;

		/* Lee secuencialmente del archivo de usuarios */
		fread(&usuario, sizeof(usuario), 1, archivo);
		while (!feof(archivo)) {
			if (strcmp(usuario.nombre, nombreUsuario) == 0 && strcmp(usuario.password, password) == 0) {
				/* Encuentra un usuario del archivo con el nombre de usuario y password buscado */
				logeoExitoso = 1;

				break;
			}

			fread(&usuario, sizeof(usuario), 1, archivo);
		}

		/* Cierra el archivo*/
		fclose(archivo);
	}

	return logeoExitoso;
}

int leerLinea(char *cad, int n)
{
	int i, c;

	/* 1 COMPROBACIÓN DE DATOS INICIALES EN EL BUFFER */
	c = getchar();
	if (c == EOF) {
		cad[0] = '\0';
		return 0;
	}

	if (c == '\n') {
		i = 0;
	} else {
		cad[0] = c;
		i = 1;
	}

	/* 2. LECTURA DE LA CADENA */
	for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		cad[i] = c;
	}
	cad[i] = '\0';

	/*3. LIMPIEZA DEL BUFFER */
	if (c != '\n' && c != EOF) /* es un caracter */
		while ((c = getchar()) != '\n' && c != EOF);

	return 1;
}

void leerClave(char *password) {
	char caracter;
	int i = 0;

	while (caracter = getch()) {
		if (caracter == TECLA_ENTER) {
			password[i] = '\0';
			break;

		} else if (caracter == TECLA_BACKSPACE) {
			if (i > 0) {
				i--;
				printf("\b \b");
			}

		} else {
			if (i < MAX) {
				printf("*");
				password[i] = caracter;
				i++;
			}
		}
	}
}
void persona::menu()
{
    int choice;
	char x;
	do
    {
	system("cls");

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t |   REALIZAR CITAS  |"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t 1. Registrar nuevo paciente"<<endl;
	cout<<"\t\t\t 2. Pacientes registrados"<<endl;
	cout<<"\t\t\t 3. Registrar examenes"<<endl;
	cout<<"\t\t\t 4. Agendar cita"<<endl;
	cout<<"\t\t\t 0. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3/4/0]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Que deseas hacer hoy?: ";
    cin>>choice;

    switch(choice)
    {
    case 1:
    	do
    	{
    		insert();
    		cout<<"\n\t\t\t Desea registrar otro paciente?(Y,N): ";
    		cin>>x;
		}while(x=='y'||x=='Y');
		break;
	case 2:
		display();
		break;

	case 3:
		do
    	{
    		insert2();
    		cout<<"\n\t\t\t Desea registrar otro Examen?(Y,N): ";
    		cin>>x;
		}while(x=='y'||x=='Y');
		break;
    case 4:
		do
    	{
    		insert3();
    		cout<<"\n\t\t\t Desea Agendar otra cita?(Y,N): ";
    		cin>>x;
		}while(x=='y'||x=='Y');
		break;

	case 0:
		exit(0);
	default:
		cout<<"\n\t\t\t ¡Ops!... intenta de nuevo";
	}
	getch();
    }while(choice!= 6);
}
void persona::insert()
{
	system("cls");
	fstream file;
	cout<<"\n--------------------------------------------------------------------------------";
	cout<<"\n----------------------Ingrese los datos del paciente ---------------------------"<<endl;
	cout<<"\t\t\tAsignar codigo al paciente             : ";
	cin>>id;
	cout<<"\t\t\tIngresar nombre completo del paciente  : ";
	cin>>name;
    cout<<"\t\t\tIngresar Celular del paciente          : ";
	cin>>phone;
	cout<<"\t\t\tIngresar Fecha de nacimiento del paciente: ";
	cin>>date;
	cout<<"\t\t\tIngresar la direccion del paciente  : ";
	cin>>address;
	file.open("Pacientes.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< date <<std::left<<std::setw(15)<< address << "\n";
	file.close();

}
void persona::insert2()
{
	system("cls");
	fstream file;
	cout<<"\n--------------------------------------------------------------------------------";
	cout<<"\n----------------------Ingrese los datos del paciente ---------------------------"<<endl;
	cout<<"\t\t\tAsignar codigo al examen             : ";
	cin>>id;
	cout<<"\t\t\tIngresar nombre del examen           : ";
	cin>>name;
	cout<<"\t\t\tIngresar el precio del examen        : ";
	cin>>price;
	file.open("RegistroExamenes.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< price << "\n";
	file.close();

}
void persona::insert3()
{
	system("cls");
	fstream file;
	cout<<"\n--------------------------------------------------------------------------------";
	cout<<"\n----------------------Ingrese los datos del paciente ---------------------------"<<endl;
    cout<<"\t\t\tIngresar Codigo del paciente           : ";
	cin>>id;
	cout<<"\t\t\tIngresar nombre completo del paciente  : ";
	cin>>name;
	cout<<"\t\t\tIngresar Celular del paciente          : ";
	cin>>phone;
	cout<<"\t\t\tIngresar Fecha de cita                 : ";
	cin>>date;
	file.open("CitasAgendadas.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< date << "\n";
	file.close();

}

void persona::display()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n------------------------- CLIENTES REGISTRADOS -------------------------"<<endl;
	file.open("Pacientes.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay información...";
		file.close();
	}
	else
	{
		file >> id >> name >> phone >> date >> address;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Id Persona: "<<id<<endl;
			cout<<"\t\t\t Nombre Persona: "<<name<<endl;
			cout<<"\t\t\t Telefono Persona: "<<phone<<endl;
			cout<<"\t\t\t Fecha de nacimiento: "<<date<<endl;
			cout<<"\t\t\t Direccion Persona: "<<address<<endl;
			file >> id >> name >> phone >> date >> address;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion...";
		}
	}
	file.close();
}

