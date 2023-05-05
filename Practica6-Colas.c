/* PROGRAMA DE SIMULACION DE SUPERMERCADO UTILIZANDO COLAS
Integrentes del equipo:
    -Leon Cortez Alan Fernando 1274062
    -Morales Ramos Bernardo 1288710
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
typedef struct nodo
{
    int tiempo_llegada;
    int tiempo_atencion;
    int id;
    struct nodo *ptrSig;
}cliente;

typedef cliente *ptrNodo;
//Declaracion de funciones.
void Enqueue(ptrNodo *cabeza, int tiempo_llegada, int tiempo_atencion, int numero_cliente);
void Dequeue(ptrNodo *cabeza);
int Front(ptrNodo cabeza);
int QueueSize(ptrNodo cabeza);
int isEmpty(ptrNodo cabeza);
void recorrerCola(ptrNodo cabeza);



int main(int argc, char const *argv[])
{
    //Inicializando
    ptrNodo cabeza = NULL;

    srand(time(NULL));

    //generar un numero aleatorio entre 1 y 4
    int tiempo_llegada = rand() % 4 + 1;
    int tiempo_llegada_primer_cliente = tiempo_llegada;
    int tiempo_atencion = rand() % 4 + 1;
    int total_clientes_atendidos = 0;
    int tiempo_espera = 0;
    int numero_cliente = 1;
    // int temp = 0;
    // bool se_esta_atendiendo = true;

    for(int i = 0; i < 720; i++) {
        //si el tiempo de llegada es igual al tiempo actual, se encola un cliente
        
        if(i == tiempo_llegada) {
            Enqueue(&cabeza, tiempo_llegada, tiempo_atencion, numero_cliente);
            tiempo_llegada += rand() % 4 + 1;
            tiempo_atencion = rand() % 4 + 1;
            // printf("\nEl tiempo de atencion es: %d\n", tiempo_atencion);
            numero_cliente++;
        }
        //si el tiempo de llegada es igual al tiempo actual, se encola un cliente


        //si se ha llegado al tiempo de atencion, se atiende al cliente y se saca de la cola
        
        if(!isEmpty(cabeza) && i == cabeza->tiempo_llegada + cabeza->tiempo_atencion) {
            // printf("Test2\n");

            printf("\nCliente %d atendido en el minuto %d\n", cabeza->id, i);
            Dequeue(&cabeza);
            total_clientes_atendidos++;
        } else if (!isEmpty(cabeza) && i > cabeza->tiempo_llegada + cabeza->tiempo_atencion) {
            printf("\nCliente %d se ha ido porque lleva esperando demasiado.\n", cabeza->id);
            Dequeue(&cabeza);
        }
        // printf("Pasa if\n");

        if(!isEmpty(cabeza)){
            recorrerCola(cabeza);
        }
        Sleep(1000);
    }
    recorrerCola(cabeza);
    
    printf("EL NUMERO TOTAL DE CLIENTES ATENDIDOS ES: %d\n", total_clientes_atendidos);
    // system("pause");


    // free(cabeza);
    // Liberando memoria
    while (!isEmpty(cabeza))
    {
        Dequeue(&cabeza);
    }
    return 0;
}

//Funciones
void Enqueue(ptrNodo *cabeza, int tiempo_llegada, int tiempo_atencion, int numero_cliente)
{
    ptrNodo nuevoNodo;
    nuevoNodo = malloc(sizeof(cliente));

    ptrNodo aux = *cabeza; //Se guarda la direccion de la cabeza actual.
    nuevoNodo->tiempo_llegada = tiempo_llegada;
    nuevoNodo->tiempo_atencion = tiempo_atencion;
    nuevoNodo->id = numero_cliente;

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
    return cabeza->id;
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
    ptrNodo aux = cabeza;
    printf("\n\t\t FILA DE LA CAJA DEL SUPERMERCADO...\n");
    while(cabeza!= NULL)
    {
        printf(" %d |", cabeza->id);
        cabeza= cabeza->ptrSig;
    }
    // printf("\n FRONT: %d", Front(aux));
    // printf("\n TAMANO: %d\n", QueueSize(cabeza));
}
