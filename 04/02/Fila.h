#define MAXTAM 1000
typedef int TipoApontador;

typedef struct {
    int Item[MAXTAM];
    TipoApontador Frente, Tras;
}Fila;

Fila inicializa_Queue();
void EmptyNow(Fila *);
int isEmpty(Fila *);
int isFull(Fila *);
int Enqueue(int , Fila *);
int Dequeue(Fila *);
int showQueue(Fila *);
int furarFila(int, Fila*);
