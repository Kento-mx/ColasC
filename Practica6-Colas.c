/* PROGRAMA DE SIMULACION DE SUPERMERCADO UTILIZANDO COLAS
Integrentes del equipo:
    -Leon Cortez Alan Fernando 1274062
    -Morales Ramos Bernardo 1288710
*/

#include <stdio.h>
#include <stdlib.h>
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
void recorrerCola(ptrNodo cabeza, int i);



int main(int argc, char const *argv[])
{
    //Inicializando
    ptrNodo cabeza = NULL;

    srand(time(NULL));

    //generar un numero aleatorio entre 1 y 4
    int tiempo_llegada = rand() % 4 + 1;
    int tiempo_atencion = rand() % 4 + 1;
    int total_clientes_atendidos = 0;
    int numero_cliente = 1;
    int clientes_en_cola, max_clientes_en_cola = 0;

    //ciclo prinicipal que simula los minutos
    for(int i = 0; i < 720; i++) {
        //si el tiempo de llegada es igual al tiempo actual, se encola un cliente
        if(i == tiempo_llegada) {
            //encolar al cliente con el tiempo de llegada y atencion
            Enqueue(&cabeza, tiempo_llegada, tiempo_atencion, numero_cliente);
            
            clientes_en_cola++;
            if(clientes_en_cola > max_clientes_en_cola) {
                max_clientes_en_cola = clientes_en_cola;
            }

            //generar aleatoriamente nuevos tiempos de llegada y atención
            tiempo_llegada += rand() % 4 + 1;
            tiempo_atencion = rand() % 4 + 1;

            //aumentar el numero de clientes que han llegado
            numero_cliente++;
        }


        //verificar que la cabeza no esta vacia
        if(!isEmpty(cabeza)) {
            //decrementar el tiempo de atención del cliente actual (cabeza) hasta llegar a 0
            cabeza->tiempo_atencion--;
            if(cabeza->tiempo_atencion == 0) {
                printf("\nCliente %d atendido en el minuto %d\n", cabeza->id, i);
                //desencolar al cliente y aumentar el numero de clientes atendidos
                Dequeue(&cabeza);
                clientes_en_cola--;
                total_clientes_atendidos++;
            }
        }

        //verificar que la cabeza no esta vacía y recorrerla
        if(!isEmpty(cabeza)){
            recorrerCola(cabeza, i);
        }

        //activar para simular el paso de los minutos
        // delay(1000);
        // Sleep(1000);
    }
    recorrerCola(cabeza, 720);
    
    printf("\nEL NUMERO TOTAL DE CLIENTES ATENDIDOS ES: %d\n", total_clientes_atendidos);
    printf("EL NUMERO MAXIMO DE CLIENTES EN COLA ES: %d\n", max_clientes_en_cola);

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

void recorrerCola(ptrNodo cabeza, int i)
{
    ptrNodo aux = cabeza;
    printf("\n\t\t FILA DE LA CAJA DEL SUPERMERCADO. MINUTO %d...\n", i);
    while(cabeza!= NULL)
    {
        printf(" %d |", cabeza->id);
        cabeza= cabeza->ptrSig;
    }
    printf("\n");
}
