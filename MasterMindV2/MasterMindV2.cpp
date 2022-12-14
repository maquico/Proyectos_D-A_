
/*
* ENUNCIADO: TAREA 1. MASTERMIND BEGINNERS
* ASUNTO: ESTE PROGRAMA ES EL JUEGO MASTERMIND BEGINNER EN EL 
QUE DEBE ADIVINAR UNA CLAVE COMPUESTA DE CUATRO DIGITOS QUE VAN DEL 1 AL 6
*
AUTORES: ANGEL MORENO ID:1104666
*        GLEIDY ESPINAL ID:1104225
*        ALLEN SILVERIO ID:1104220
*        CRISTIAN JIMÉNEZ ID:1106166
*        WILLIAM FERREIRA ID:1104228
* FECHA: 15/08/2022
*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;

int puntuacion = 11;//Variable Global que graba la puntuacion del usuario.

int ValidarClave(string intento, string claveActual, int i) {//La funcion valida la entrada del usuario, pasandolo por varios filtros
	
	
	// 0 indica longitud erronea, 1 indica repetidos, 2 indica que hay letras, 3 indica que la clave tiene numeros diferentes de 1, 2, 3, 4, 5, 6
	bool hayLetras = false, wlongitud = false;
	
	bool limitenumeros = false;
	
	if (intento.length() != 1)//Verifica que solo sea 1 caracter 
	{
		return 0;
	}
	else if (!isdigit(intento[0])) {//Verifica que solo sean digitos
		return 2;
	}
	else if (stoi(intento) < 0 || stoi(intento) > 6)//Verifica que solo sean digitos del 1 al 6
	{
		return 3;
	}
	else if (i!=0 ) //Verifica que no repitan numeros en la clave que esta introduciendo el usuario
	{
		for (int j = 0; j <= i; j++)
		{
			if (claveActual[j]==intento[0])
			{
				return 1;
			}
		}
	}
			
}
void GoToXY(int x, int y)
{//La función coloca el cursor para imprimir en el lugar que queramos.
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}
string GenerarNumRand() {
	//La funcion genenra un numero random para que sea la clave, que tenga numeros del 1 al 6 y que ninguno se repita
	int random;
	bool duplicado = false;
	string numActual, clave;
	for (int i = 0; i < 4; i++)
	{
		random = (rand() % 6) + 1; //genera numero random de 1 a 6
		numActual = to_string(random)[0];

		if (i != 0) // luego de que se genere el segundo numero
		{
			for (int j = 0; j < i; j++)
			{//Bucle para comparar si un numero es igual a los otros que ya estan en la clave
				if (clave[j] == numActual[0]) 
				{
					duplicado = true;
				}
			}
			if (duplicado)
			{
				i--;
				duplicado = false;
			}
			else
			{
				clave += numActual;
			}
		}
		else
		{
			clave = numActual;
		}
	}
	return clave;
}

int Jugar(string clave) {

	string claveActual, pista, cIntento;
	
	bool numDentro = false;
	int tabla1x = 18;
	int tablay = 8;
	int tabla2x = 59;

	cout << "--------------------------Bienvenido a MasterMind--------------------------\n";
	cout << " Vaya introduciendo numero por numero, uno por uno. Luego de escribir un numero\n";
	cout << " de la clave de enter para introducir el otro hasta en introducir los 4 numeros\n";
	cout << " por intento. No introducir mas de 1 numero por columna.  Clave: " << clave << ".\n\n";
	cout << "|         |---Tabla Juego---|                   |---Tabla Pista---|             |\n";
	cout << "|-------------------------------------------------------------------------------|\n";
	cout << "| Calificacion |  A  |  B  |  C  |  D  |  || | Intentos |  A  |  B  |  C  |  D  |\n"; 

	for (int i = 10, m=9; i >0; i--, m-=2)//Bucle para imprimir la tabla
	{	
		if (i != 10 && i!=1) {
			cout << "|    0" << (i) << "        |     |     |     |     |  || |    0" << (i-m) << "    |     |     |     |     |\n";
			cout << "|--------------|-----|-----|-----|-----|  || |----------|-----|-----|-----|-----|\n";
		}
		
		else if(i==10)
		{
			cout << "|    " << (i) << "        |     |     |     |     |  || |    0" << (i-m) << "    |     |     |     |     |\n";
			cout << "|--------------|-----|-----|-----|-----|  || |----------|-----|-----|-----|-----|\n";
		}
		else if (i == 1) 
		{
			cout << "|    0" << (i) << "        |     |     |     |     |  || |    " << (i - m) << "    |     |     |     |     |\n";
			cout << "|--------------|-----|-----|-----|-----|  || |----------|-----|-----|-----|-----|\n";
		}
	}
	cout << "---------------------------------------------------------------------------------\n";

	for (int j = 0; j < 10; j++)
	{
		if (claveActual != clave)
		{
			claveActual = "";
			for (int z = 0; z < 4; z++)
			{
				GoToXY(0, 30);
				cout << "Numero a ingresar :                                                                ";
				GoToXY(20, 30);
				cin >> cIntento;
				switch (ValidarClave(cIntento, claveActual, z))
				{
				case 0:
					//longitud erronea;
					cout << "Longitud erronea\n";
					cout << "Presione cualquier tecla para continuar";
					_getch();
					GoToXY(0, 31);
					cout << "                \n";
					cout << "                                       ";
					z--;
					break;
				case 1:
					//repetidos
					cout << "Numeros repetidos\n";
					cout << "Presione cualquier tecla para continuar";
					_getch();
					GoToXY(0, 31);
					cout << "                 \n";
					cout << "                                       ";
					z--;
					break;
				case 2:
					//hay letras
					cout << "Por favor no pongas letras\n";
					cout << "Presione cualquier tecla para continuar";
					_getch();
					GoToXY(0, 31);
					cout << "                          \n";
					cout << "                                       ";
					z--;
					break;
				case 3:
					//Numero menor que 1 o mayor que 6
					cout << "La clave no puede tener numeros menores que 1 o mayores que 6\n";
					cout << "Presione cualquier tecla para continuar";
					_getch();
					GoToXY(0, 31);
					cout << "                                                              \n";
					cout << "                                                              ";
					z--;
					break;
				default:
					GoToXY(tabla1x, tablay);
					cout << cIntento;
					claveActual += cIntento;
					tabla1x += 6;
					break;
				}
			}
			for (int k = 0; k < 4; k++) // Generacion de la pista
			{
				for (int l = 0; l < 4 && !numDentro; l++)
				{
					if (claveActual[k] == clave[l] && k == l)
					{
						pista += "C";
						numDentro = true;
					}
					else if (claveActual[k] == clave[l])
					{
						pista += "F";
						numDentro = true;
					}
				}
				if (!numDentro)
				{
					pista += "X";
				}
				else
				{
					numDentro = false;
				}
				GoToXY(tabla2x, tablay);
				cout << pista;
				pista = "";
				tabla2x += 6;
			}
			tabla1x = 18;
			tabla2x = 59;
			tablay += 2;
			puntuacion--;
		}
		else
		{
			return 1;
		}

		}
		
	return 0;
}

int main()
{
	srand(time(NULL));
	string numRand;
	bool salir = false;
	numRand = GenerarNumRand();
	string opcion = "0";
	
	do {
		system("cls");
		cout << "Bienvenido al Juego MasterMind. En este juego desafiara tu mente. Elige una de las siguientes opciones: \n\n1) Ir al Juego.\n2) Ver las Instrucciones.\n0) Para Salir\n\nOpcion Elegida: ";
		cin >> opcion;
		if (isdigit(opcion[0]) && opcion.length() == 1) {
			int op = stoi(opcion);

			switch (op)
			{
			case 1:
				system("cls");
				if (Jugar(numRand) == 1)
				{
					GoToXY(0, 31);
					cout << "\n\n!!!!!!!!!Felicidades!!!!!!!!!";
					cout << "\nHa Adivinado la Clave.\nSu puntuacion fue: "<< puntuacion << ".";
					cout << "\nPresione cualquier letra para continuar.";
					_getch();
				}
				else
				{
					GoToXY(0, 31);
					cout << "\n\n!!!!!!!!!Lo Sentimos, Ha Perdido!!!!!!!!!";
					cout << "\nNo Ha Adivinado la Clave y ha agotado todos sus turnos.\n";
					cout << "\nPresione cualquier letra para continuar.";
					_getch();
				}
				break;

			case 2:
				system("cls");
				cout << "En el juego MasterMind, se busca adivinar una contraseña de 4 digitos, donde ninguno se repite, y el programa le va\ndiciendo que tan cerca esta de la siguiente manera: \nA) 'F' indica que el numero introducido en esa posicion esta en la clave, pero no el la posicion correcta.\nB) 'C' indica que el numero esta en la clave y esta en la posicion correcta.\nC) 'X' indica que el numero no pertenece a la clave.\n\n";
				cout << "Notas:\n";
				cout << "1) Recuerde que solo se permiten numeros del 1 al 6\n";
				cout << "2) Recuerde que NINGUN NUMERO se repite\n\n";
				cout << "Despues de haber leido las instrucciones bien, presione cualquier tecla para volver al menu de inicio";
				_getch();

				system("cls");
				break;

			case 0:
				salir = true;
				system("cls");
				break;

			default:
				cout << "\n\nLa opcion no es parte del menu. Elija una de las opciones disponibles";
				_getch();
				system("cls");
				break;
			}
		}
		else {
			cout << "\n\nLa opcion no es parte del menu. Elija una de las opciones disponibles";
			_getch();
			system("cls");
		}

	} while (!salir);
	return 0;
}


