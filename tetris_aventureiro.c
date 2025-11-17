#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5   //máximo de peças na fila
#define PIL 3   //máximo de peças reservadas na pilha

typedef struct {
    char nome;  // I, O, T, L
    int id;     //ID unico
} Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

typedef struct {
    Peca itens[PIL];    //são os itens com tamanho maximo de '[PIL]'
    int topo;           //precisa apontar o Topo, pq ele controla tudo
    int total;          //para contabilizar depois
} Pilha;

int idAtual = 0;        //executa quando chama o programa com valor 0

/*--------------------- GERANDO PEÇAS ---------------------*/
char gerarTipo(){
    char tipos[] = {'I', 'O', 'T', 'L'};    //definindo as peças
    int indice = rand() % 4;                //numero aleatorio até o meximo de 4 tipos 
    return tipos[indice];
}

Peca gerarPeca (){  //função tipo 'Peca' pra poder retornar uma 'nova'
    Peca nova;
    int idTemp = idAtual + 1;     //cria um id temporario para incrementar
    idAtual = idTemp;           //o 'idAtual' passa a receber o valor do temporario
    nova.id = idAtual;          //o 'id' da struct nova recebe o valor do 'id' incrementado
    nova.nome = gerarTipo();
    return nova;
}

Peca gerarTopo(Fila *f){
    return f->itens[f->inicio];
}

/*--------------------- FUNÇÕES DE FILA ---------------------*/
void inicializarFila(Fila *f) { //definição para poder usar só os ponteiros depois
    f->inicio = 0;  //0 pq aponta pro inicio do vetor
    f->fim = 0;     //0 pq no fim nao tem nada
    f->total = 0;   //0 pq a fila ainda esta vazia
}

int filaCheia(Fila *f) {
    return f->total == MAX; //se o o total for igual ao MAX está cheia
}

int filaVazia(Fila *f) {
    return f->total == 0; //se o o total for igual ao 0 está vazia
}

void inserir(Fila *f, Peca p) {     //'p' é "cópia" do valor q esta no campo, não o valor original
    if (filaCheia(f)) {     //chama a função de lista cheia
        printf("\nDisplay completo, NÃO é possível inserir mais peças.\n");
        return;
    }
 
    f->itens[f->fim] = p;           //o valor que esta no campo 'f->fim' da linha 'itens' da struct 'Fila' ('f') equivale à 'p'
    f->fim = (f->fim + 1) % MAX;    //lógica circular para percorrer o array de tamanho fixo
    f->total++;
}

void remover(Fila *f, Peca *p) {    //'*p' é o campo, e exclui o valor original
    if (filaVazia(f)) {     //chama a função de lista vazia
        printf("\nOwn!! Não há peças neste display!!\n");
        return;
    }

    *p = f->itens[f->inicio];              //ponteiro pra 'Peca', e indica onde armazenar o elemento e remover 
    f->inicio = (f->inicio + 1) % MAX;     //lógica circular para percorrer o array de tamanho fixo
    f->total--;                        
}

void mostrarFila(Fila *f) {
    int temp = f->inicio;

    printf("\nPeças disponíveis: ");
    for (int i = 0; i < f->total; i++) { 
        printf("[%c.%d] ", f->itens[temp].nome, f->itens[temp].id);
        temp = (temp + 1) % MAX;    //faz a lógica circular 'temp = (temp + 1) % MAX'
    }
    printf("\n");
}

/*--------------------- FUNÇÕES DE PILHA ---------------------*/
void iniciarPilha(Pilha *pi) {
    pi->topo = -1;
    pi->total = 0;   //0 pq a pilha ainda esta vazia
}

int pilhaVazia(Pilha *pi){
    return pi->topo == -1;  //se for menor q 0 está vazia
}

int pilhaCheia(Pilha *pi){
    return pi->topo == PIL - 1;
}

void push(Pilha *pi, Peca nova){
    if (pilhaCheia(pi)) {
        printf("ESPAÇO ESGOTADO: Não é possivel armazenar!\n");
        return;
    }
    pi->topo++;     //caso nao esteja chheia, vai aumetar o espaço e inserir
    pi->itens[pi->topo] = nova;     //inserir nova
    pi->total++;    //incrementta pra sempre manter os 5 campos
}

void pop(Pilha *pi, Peca *removida){
    if  (pilhaVazia(pi)) {
        printf("Não há peças reservadas. \n");
        return;
    }
    *removida = pi->itens[pi->topo];
    pi->topo--;     //dedcrementa qdo remove
    pi->total--;    //atualiza o total decrementando
}

void mostrarPilha(Pilha *pi){
    printf("Sua Reserva (do topo à base): ");
    for (int i = pi->topo; i >= 0; i--) {
        printf("[%c.%d] ", pi->itens[i].nome, pi->itens[i].id);
    }
    if (pi->topo == -1){
        printf("(Reserva vazia)\n");
    }
    printf("\n");
}

/*--------------------- FUNÇÃO PRINCIPAL ---------------------*/
int main() {
    //1º 
    srand(time(NULL));  //função rand pra adicionar peças aletorias e completar a fila
    int opcao;          //para contar os itens adicionados

    //2º declarar as structs
    Fila f; 
    Pilha pi;
    Peca p;

    //3º inicializa a fila e a pilha
    inicializarFila(&f);
    iniciarPilha(&pi);

    // Preencher a fila com 5 peças
    for (int i = 0; i < MAX; i++) {
        inserir(&f, gerarPeca());
    }
 
    // Iniciando o Jogo
    do {
        printf("\n------------------------------------------------------------\n");
        printf("||||||| TETRIS STACK ||| Peças: %d/%d ||| Reserva: %d/%d |||||||\n", f.total, MAX, pi.total, PIL);
        printf("------------------------------------------------------------\n");
        printf("  1. Jogue uma peça (dequeue)\n");
        printf("  2. Reservar próxima peça (push)\n");
        printf("  3. Descartar peça reservada (pop)\n");    //Atenção: as peças removidas da fila ou da pilha não voltam para o jogo.
        printf("  0. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                remover(&f, &p);    //'&' pega o valor que está no endereço
                inserir(&f, gerarPeca());   //A cada ação, uma nova peça é automaticamente gerada e adicionada ao final da fila, mantendo-a sempre cheia
                printf("\nVocê jogou a peça [%c.%d]\n", p.nome, p.id);
                mostrarFila(&f);    //mostra a fila após a remoção
                mostrarPilha(&pi);  //mostra ordem das peças reservadas
                break;

            case 2:
                p = gerarTopo(&f);          //chama a função de pegar do inicio da fila para colocar na pilha
                push(&pi, p);
                mostrarPilha(&pi);          //mostra a pilha de reserva
                remover(&f, &p);            //removendo pra nao ficar repetido e a fila andar
                inserir(&f, gerarPeca());   //completando a Fila de novo
                printf("\nEm jogo...");
                mostrarFila(&f);            //mostra a fila atualizada
                break;

            case 3: //AGORA É USAR RESERVA (POP)
                pop(&pi, &p);           //recebe ponteiro e nao gera nova eça, só remove
                mostrarPilha(&pi);    //mostra a pilha de reserva
                printf("Suas peças em jogo são:\n");
                mostrarFila(&f);
                break;

            case 0:
                printf("\n...Encerrando programa...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}