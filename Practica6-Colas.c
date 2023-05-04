/* PROGRAMA DE SIMULACION DE SUPERMERCADO UTILIZANDO COLAS
Integrentes del equipo:
    -Leon Cortez Alan Fernando 1274062
    -
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int dato;
    struct nodo *ptrSig;
}nodo_t;

typedef nodo_t *ptrNodo;

//Declaracion de funciones.
void Enqueue(ptrNodo *cabeza, int nuevoDato);
void Dequeue(ptrNodo *cabeza);
int Front(ptrNodo cabeza);
int QueueSize(ptrNodo cabeza);
int isEmpty(ptrNodo cabeza);
void recorrerCola(ptrNodo cabeza);



int main(int argc, char const *argv[])
{
    //Inicializando
    ptrNodo cabeza;
    cabeza = NULL;

    Enqueue(&cabeza, 1);
    Enqueue(&cabeza, 2);
    Enqueue(&cabeza, 3);
    Enqueue(&cabeza, 4);
    recorrerCola(cabeza);
    printf("\n FRONT: %d", Front(cabeza));
    printf("\n TAMANO: %d", QueueSize(cabeza));
    system("pause");
    Dequeue(&cabeza);
    recorrerCola(cabeza);
    printf("\n FRONT: %d", Front(cabeza));
    printf("\n TAMANO: %d", QueueSize(cabeza));
    system("pause");

    free(cabeza);

    return 0;
}

//Funciones
void Enqueue(ptrNodo *cabeza, int nuevoDato)
{
    ptrNodo nuevoNodo;
    nuevoNodo = malloc(sizeof(nodo_t));

    ptrNodo aux = *cabeza; //Se guarda la direccion de la cabeza actual.
    nuevoNodo->dato = nuevoDato;

    if(nuevoNodo != NULL)
    {
        //Verificando cola vacia.
        if(*cabeza == NULL)
        {
            *cabeza = nuevoNodo;
            nuevoNodo->ptrSig = NULL;
        }else
        {
            //Se recorre la lista al final con aux.
            while(aux->ptrSig != NULL)
            {
                aux = aux->ptrSig;
            }
            //Se asignan los valores al nuevo nodo.
            nuevoNodo->dato = nuevoDato;
            nuevoNodo->ptrSig = NULL;
            aux->ptrSig = nuevoNodo;
        }

    }else
    {
        printf("\n\t No se pudo insertar. !MEMORIA INSUFICIENTE!");
    }
}

void Dequeue(ptrNodo *cabeza)
{
    //Verificando cola NO vacia.
    if(*cabeza != NULL)
    {
        if(QueueSize(*cabeza) == 1)
        {
            *cabeza = NULL;
            free(*cabeza);
        }else
        {
            ptrNodo aux = *cabeza;
            *cabeza = (*cabeza)->ptrSig;
            free(aux);
        }
    }else
    {
        printf("\n\n\t COLA VACIA. \n");
    }

}

int Front(ptrNodo cabeza)
{
    return cabeza->dato;
}

int QueueSize(ptrNodo cabeza)
{
    int acum = 0;
    while(cabeza != NULL)
    {
        acum++;
        cabeza = cabeza->ptrSig;
    }

    return acum;
}

//Regresa 1 si esta vacio.
//Regresa 0 si hay algun valor.
int isEmpty(ptrNodo cabeza)
{
    if (cabeza == NULL)
        return 1;
    else
        return 0;
}

void recorrerCola(ptrNodo cabeza)
{
    printf("\n\t\t FILA DE LA CAJA DEL SUPERMERCADO...\n");
    while(cabeza!= NULL)
    {
        printf(" %d |", cabeza->dato);
        cabeza = cabeza->ptrSig;
    }
}
