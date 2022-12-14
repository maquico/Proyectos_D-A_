/*
* ENUNCIADO: TAREA 5. LISTAS ENLAZADAS (LINKED LIST)
* ASUNTO: ESTE PROGRAMA PERMITE HACER LAS OPERACIONES INSERTAR, ELIMINAR, BUSCAR, Y MOSTRAR LISTA
AUTORES: ANGEL MORENO ID:1104666
*        GLEIDY ESPINAL ID:1104225
*        ALLEN SILVERIO ID:1104220
*        CRISTIAN JIMÉNEZ ID:1106166
*        WILLIAM FERREIRA ID:1104228
* FECHA: 29/08/2022
*/

#include <stdlib.h> // new, delete
#include <string>
#include <conio.h> // getch
#include <iostream>

using namespace std;

struct NodoT {
    int dato;
    NodoT* siguiente;
};

void Insertar(NodoT*& lista, int entrada) {
    NodoT* aux1 = lista;
    NodoT* aux2 = new NodoT();
    NodoT* nuevoNodo = new NodoT();

    while (aux1 != NULL && aux1->dato < entrada)
    {
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }
    if (lista == aux1)//Coloca el nuevo nodo al inicio de la lista
    {
        lista = nuevoNodo;
    }
    else//Coloca el nuevo nodo a la derecha del auxiliar 2
    {
        aux2->siguiente = nuevoNodo;
    }
    nuevoNodo->siguiente = aux1;
    nuevoNodo->dato = entrada;
}

//Eliminar Un Elemento de la Lista
int EliminarUnElemento(NodoT*& first, int dato)
{
    NodoT* aux = first;
    int i = 0;
    bool founded = false;
    if (aux == NULL) return 1; // Verificar que la lista no este vacia.

    else {
        if (aux->dato == dato) founded = true;//Verificar si es el primer nodo
        while (aux->siguiente != NULL && !founded)
        {
            if (aux->siguiente->dato == dato) founded = true;
            else  aux = aux->siguiente;
            i++;
        }
        if (founded && i != 0)// Si se esta eliminando un elemento diferente del primero de la lista
        {
            NodoT* eliminar = aux->siguiente;
            aux->siguiente = eliminar->siguiente;
            delete(eliminar);
            return 2;
        }
        else if (founded && i == 0)// Si se esta eliminando un elemento el primer elemento de la lista
        {
            first = aux->siguiente;
            delete(aux);
            return 2;
        }
        else return 3; // Si no se encuentra el elemento a eliminar
    }
}

void Mostrar(NodoT* lista) {
    NodoT* actual = new NodoT();
    actual = lista;
    while (actual != NULL)
    {
        if (actual->siguiente != NULL) cout << actual->dato << " , ";
        else cout << actual->dato << ".";
        actual = actual->siguiente;
    }
    _getch();
}

void BuscarElemento(NodoT* lista, int entrada) { //Se le pasa el nodo lista de tipo puntero (que representa el primer elemento de la lista) y se le pasa el dato buscar.

    bool elementoExiste = false;
    NodoT* actual = new NodoT(); //Se crea un nodo auxiliar que representara el nodo actual que se esta comparando con el dato a buscar.
    actual = lista; // Se le asigna al nodo actual el nodo que representa el primer elemento de la lista.

    while (actual != NULL && actual->dato <= entrada) //Mientras el nodo actual sea diferente de nulo (no sea el que le sigue al ultimo nodo de la lista) y el dato del nodo actual sea menor o igual que el dato a buscar
    {
        if (actual->dato == entrada) //Se verifica si el dato del nodo actual es igual al dato a buscar
        {
            elementoExiste = true;
            break;//El elemento existe asi que se sale del bucle
        }

        actual = actual->siguiente;
    }

    if (elementoExiste)
    {
        cout << "El elemento " << entrada << " se encuentra en la lista ";

    }
    else
    {
        cout << "El elemento " << entrada << " NO se encuentra en la lista ";

    }
}

// Función para eliminar lista completa
void EliminarLista(NodoT*& lista) {
    while (lista != NULL) {
        NodoT* aux = lista;
        lista = aux->siguiente;
        delete aux;
    }
}

// Validaciones
bool BuscarLetras(string entrada)
{
    bool hayLetras = false;
    for (int i = 0; i < entrada.length() && !hayLetras; i++)
    {
        if (entrada[0] != '-') (isdigit(entrada[i]) == false) ? hayLetras = true : false;
    }
    return hayLetras;
}

void Alerta(string iniMensaje = "", string finMensaje = "", int variable = NULL) {
    cout << "\n" << iniMensaje;
    if (variable != NULL)
    {
        cout << variable << finMensaje;
    }
    cout << "\nPresione cualquier tecla para continuar\n";
    _getch();
}

int main()
{
    NodoT* lista = NULL;
    string op = "", input;
    bool run = true, hayLetras = false;
    int dato;
    char opDelete;

    while (run) {
        system("cls");

        cout << "Bienvenido al programa de Listas Enlazadas" << endl;
        cout << "1) Insertar en la lista" << endl;
        cout << "2) Eliminar elemento de la lista" << endl;
        cout << "3) Mostrar la lista" << endl;
        cout << "4) Buscar en la lista" << endl;
        cout << "5) Eliminar toda la lista" << endl;
        cout << "0) Salir" << endl;
        cout << "\nOpcion Elegida: ";
        cin >> op;

        if (!BuscarLetras(op))
        {
            switch (stoi(op))
            {
            case 0:           // Cerrar
                run = false;
                break;

            case 1:          // Insertar
                cout << "Ingrese el numero para agregar a la lista: ";
                cin >> input;

                if (!BuscarLetras(input)) {
                    dato = stoi(input);

                    Insertar(lista, dato);
                    Alerta("El elemento ", " fue agregado con exito", dato);
                }
                else {
                    Alerta("No introduzca letras, la lista solo contiene valores enteros");
                }
                break;

            case 2:          // Eliminar
                cout << "\n\nIngrese el dato que quiere eliminar: ";
                cin >> input;
                if (!BuscarLetras(input)) {
                    dato = stoi(input);
                    switch (EliminarUnElemento(lista, dato))
                    {
                    case 1:
                        cout << "\n\nLa lista esta vacia. No puede eliminar elementos.";
                        break;
                    case 2:
                        cout << "\n\nEl elemento " << dato << " se ha eliminado.";
                        break;
                    case 3:
                        cout << "\n\nEl elemento no existe en la lista. Intente con Otro Elemento";
                        break;
                    }
                }
                else 
                {
                    cout << "\nNo introduzca letras";
                }
                cout << "\nPresione cualquier tecla para Continuar";
                _getch();
                system("cls");
                break;
            case 3:          // Mostrar
                cout << "Esta es la lista enlazada de elementos: " << endl;
                if (lista != NULL) {
                    Mostrar(lista);
                }
                else {
                    Alerta("La lista esta vacia");
                }
                break;

            case 4:          // Buscar
                cout << "Ingrese el elemento que desea buscar en la lista: ";
                cin >> input;

                if (!BuscarLetras(input)) {

                    dato = stoi(input);
                    BuscarElemento(lista, dato);
                    Alerta();

                }
                else {
                    Alerta("No introduzca letras, la lista solo contiene valores enteros");
                }
                break;

            case 5: //Eliminar Lista
                if (lista != NULL) {
                    EliminarLista(lista);
                    Alerta("La lista se ha eliminado con exito");
                }
                else {
                    Alerta("La lista esta vacia");
                }
                break;

            default: //Cuando el Numero Ingresado no esta en el menu
                Alerta("El numero no forma parte de las opciones del menu");
                break;
            }
           
        }
    }
}

