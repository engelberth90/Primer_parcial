#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#define v 40
using namespace std;
void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void cambiarcolor(int X)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X);
}
void co(int, int);
const char *nombe_archivo = "primer_parcial.dat";
const char *nom_temporal = "Primer_parcial.dat";

struct Planilla
{
    int codigo;
    char nombre[v];
    char apellido[v];
    char puesto[v];
    float sueldo;
    float bonificacion;
    float total;
};
void eliminar33();
void ingresar_usuario();
void mostrar_usuario();
void control();
void modificar_usuario();
void buscar();

int main()
{
    control();
}

void control()
{
    int a, b, c;
    do
    {
        cout<<endl;
        cout<<"-----------MENU PARA REGISTRAR PERSONAL----------"<<endl;
        cout<<endl;
        cout << ("   [1] Ingresar Datos\n");
        cout << ("   [2] Mostrar Datos\n");
        cout << ("   [3] Eliminar datos\n");
        cout << ("   [4] Buscar datos por ID\n");
        cout << ("   [5] Modificar\n");
        cout << ("   [6] Salir\n");
        cout << ("                                Ingrese opcion: ");
        cin >> a;
        switch (a)
        {
        case 1:
            system("cls");
            ingresar_usuario();
            break;
        case 2:
            system("cls");
            mostrar_usuario();
            break;
        case 3:
            system("cls");
            eliminar33();
            break;
        case 4:
            system("cls");
            buscar();
            break;

        case 5:
            system("cls");
            modificar_usuario();
            break;
        }
    } while (a != 6);
}

void ingresar_usuario()
{
    char continuar;
    FILE *archivo = fopen(nombe_archivo, "ab"); // ab
    Planilla plan;
        string nombre,apellido, puesto;
    do
    {
        system("cls");
        fflush(stdin);
        plan.codigo = 0;
        plan.codigo = plan.codigo + 1;
        cout<<endl;
        cout << "    Ingrese nombre: ";
        getline(cin, nombre);
        strcpy(plan.nombre, nombre.c_str());

        cout << "    Ingrese apellido: ";
        getline(cin, apellido);
        strcpy(plan.apellido, apellido.c_str());

        cout << "    Ingrese puesto: ";
        getline(cin, puesto);
        strcpy(plan.puesto, puesto.c_str());

        cout << "    sueldo base: ";
        cin >> plan.sueldo;
        cin.ignore();

        cout << "    Bonificacion: ";
        cin >> plan.bonificacion;
        cin.ignore();
        plan.total = plan.sueldo + plan.bonificacion;

        fwrite(&plan, sizeof(Planilla), 1, archivo);

        cout << "  Desea Agregar otro Empleado s/n : ";
        cin >> continuar;
    } while ((continuar == 's') || (continuar == 'S'));
    fclose(archivo);
    system("cls");
}

void modificar_usuario(){
	
	FILE* archivo = fopen(nombe_archivo, "r+b");
	
		int id;
		char respuesta[v];
		string nombre,apellido,puesto;	
    	Planilla plan;
    
		cout << "Ingrese el ID que desea Modificar: ";
    		cin >> id;
    		cin.ignore();
    		fseek ( archivo, id * sizeof(Planilla), SEEK_SET );  // esto es lo que permite modificar en la pocision
	
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(plan.nombre, nombre.c_str()); 
    	
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(plan.apellido, apellido.c_str()); 
		
					
		cout<<"Ingrese el Puesto:";
		getline(cin,puesto);
		strcpy(plan.puesto, puesto.c_str()); 
		
		
		cout<<"Ingrese el sueldo:";
		cin>>plan.sueldo;
	    cin.ignore();
		
		cout<<"Ingrese el bonificacion:";
		cin>>plan.bonificacion;
		cin.ignore();
		
		 plan.total = plan.sueldo + plan.bonificacion;
		
		fwrite( &plan, sizeof(Planilla), 1, archivo );
		
	fclose(archivo);
	 mostrar_usuario();
		system("PAUSE");
}

void mostrar_usuario()
{
    system("cls");
    FILE *archivo = fopen(nombe_archivo, "rb");
    if (!archivo)
    {
        archivo = fopen(nombe_archivo, "w+b");
    }

    Planilla plan;
    int registro = 0;
    fread(&plan, sizeof(Planilla), 1, archivo);

    do
    {
        cout << "_______________________________________________________________________________" << endl;
        cout<<"  ID:            "<<registro <<endl;
		cout<<"  Nombre:        "<<plan.nombre<<endl;
		cout<<"  Apellido:      "<<plan.apellido <<endl;
		cout<<"  Puesto:        "<<plan.puesto <<endl;
		cout<<"  Sueldo:        "<<plan.sueldo <<endl;
		cout<<"  Bonificacion   "<<plan.bonificacion <<endl;
		cout<<"  TOTAL:         "<<plan.total << endl;

        fread(&plan, sizeof(Planilla), 1, archivo);
        registro += 1;

    } while (feof(archivo) == 0);

    cout << endl;
    fclose(archivo);
    getch();
}

void buscar()
{
   FILE* archivo = fopen(nombe_archivo, "rb");
	
	int pos=0;
	cout<<endl;
	cout<<"   Que registro desea ver: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Planilla), SEEK_SET );
	
	Planilla plan;    
    fread(&plan, sizeof(Planilla), 1, archivo);
    cout << "Codigo:         " <<pos<< endl;
    cout << "Nombre:         " << plan.nombre << endl;
    cout << "Apellido:       " << plan.apellido << endl;
    cout << "puesto:         " << plan.puesto << endl;
    cout << "Sueldo Base:    " << plan.sueldo << endl;
    cout << "Bonificacion:   " << plan.bonificacion << endl;
    cout << "Total:          " << plan.total << endl;
    cout << endl;

    fclose(archivo);
    system("PAUSE");
}

void eliminar33()
{
    Planilla plan;
    FILE *temporal = fopen(nom_temporal, "w+b");
    FILE *archivo = fopen(nombe_archivo, "r+b");
    int id;
    cout<<endl;
    cout <<"   Ingrese el ID que desea eliminar: ";
    cin >> id;
    fseek(archivo, id * sizeof(Planilla), SEEK_SET);
    plan.codigo = -1;
    fwrite(&plan, sizeof(Planilla), 1, archivo);
    fclose(archivo);

    archivo = fopen(nombe_archivo, "r+b");

    fread(&plan, sizeof(Planilla), 1, archivo);
    temporal = fopen(nom_temporal, "a+b");
    do
    {
        if (plan.codigo == -1)
        {
            cout << "Archivo eliminado";
        }
        if (plan.codigo >= 0)
        {
            fwrite(&plan, sizeof(Planilla), 1, temporal);
        }
        fread(&plan, sizeof(Planilla), 1, archivo);
    } while (feof(archivo) == 0);
    fclose(temporal);
    fclose(archivo);

    archivo = fopen(nombe_archivo, "w");
    fclose(archivo);

    temporal = fopen(nom_temporal, "r+b");

    fread(&plan, sizeof(Planilla), 1, temporal);
    archivo = fopen(nombe_archivo, "a+b");
    do
    {
        fwrite(&plan, sizeof(Planilla), 1, archivo);
        fread(&plan, sizeof(Planilla), 1, temporal);
    } while (feof(temporal) == 0);
    fclose(archivo);
    fclose(temporal);

    temporal = fopen(nom_temporal, "w");
    fclose(temporal);

    mostrar_usuario();
}
