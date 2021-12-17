typedef int Posicao;
#define InicioVetor 0
#define MaxTam 1000

typedef struct processos{
  int id;
  int time;
  int nice;
}Process;

typedef struct lista_linear{
  Process item[MaxTam];
  Posicao primeiro, ultimo;
}ListaLinear;

ListaLinear* inicializa();
void FLVazia(ListaLinear*);
void Insere(Process*, ListaLinear*);
Process* Retira(ListaLinear*, Posicao);
int Vazia(ListaLinear*);
void Imprime(ListaLinear*);
