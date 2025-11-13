#include <stdio.h>
#include <stdlib.h>

#define MAX 5

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

/*int gerarID(){          //Gerarando ID automaticamente
    //int proximoID = 1;  //Iniciando do 1, com 'static' fazendo a variável manter o valor
    return proximoID++; //Incrementa para o proximo
}*/

int idAtual = 0; //executa quando chama o programa com valor 0

char gerarTipo(){
    char tipos[] = {'I', 'O', 'T', 'L', '+'};    //definindo as peças
    int indice = rand() % MAX;                //numero aleatorio até o meximo de peça permitida 
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

void inicializarFila(Fila *f) { //definição para poder usar só os ponteiros depois
    f->inicio = 0;  //0 pq aponta pro inicio do vetor
    f->fim = 0;     //0 pq no fim nao tem nada
    f->total = 0;   //0 pq a fila anida esta vazia
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
    printf("Peças disponíveis: ");
    for (int i = 0, temp = f->inicio;  //cria 2 variaveis: 'i' que inicia no campo '0' e o 'temp' indice da fila que inicia pro inicio apontado pelo ponetiro 'f->inicio'
        i < f->total; 
        i++, temp = (temp + 1) % MAX) { //vai incrementando i++ e fazendo a lógica circular 'temp = (temp + 1) % MAX'
        printf("[%c.%d] ", f->itens[temp].nome, f->itens[temp].id); 
    }
    printf("\n");
}

int main() {
    Fila f; //declarar a struct
    Peca p;

    inicializarFila(&f);  // Inicializa a fila passando como parametro o ponteiro
    
    int total, opcao; //para contar os itens adicionados
 
    // Iniciando o Jogo
    do {
        printf("\n||||||| TETRIS STACK |||||||\n");
        printf("-------  itens  %d/%d  -------\n\n", f.total, MAX);  
        printf("  1. Jogue uma peça (dequeue)\n");
        printf("  2. Adicione uma peça (enqueue)\n");
        printf("  0. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                remover(&f, &p);    //'&' pega o valor que está no endereço
                mostrarFila(&f);    //mostra a fila após a remoção
                break;

            case 2:
                p = gerarPeca();    //quando 'p' passa a receber o valor gerado pela Função
                inserir(&f, p);
                mostrarFila(&f);    //mostra a fila após a inserção
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