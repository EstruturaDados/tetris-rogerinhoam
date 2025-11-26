#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição do tamanho máximo da fila (capacidade de previsão do jogo)
#define TAM_MAX 5

// --- Definição da Struct Peca ---
// Representa a peça do Tetris com seu tipo visual e ID único
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L', etc.
    int id;    // Identificador numérico único
} Peca;

// --- Definição da Struct Fila ---
// Estrutura de controle para a Fila Circular
typedef struct {
    Peca itens[TAM_MAX]; // Vetor estático para armazenar as peças
    int inicio;          // Índice da peça que será jogada (frente)
    int fim;             // Índice onde a próxima peça entrará (trás)
    int quantidade;      // Contador de quantos elementos existem na fila
} Fila;

// --- Funções Auxiliares ---

// Função para gerar uma peça automaticamente
// Utiliza uma variável estática para manter o ID único entre chamadas
Peca gerarPeca() {
    static int contadorId = 0; // Mantém o valor mesmo após a função terminar
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'};
    Peca novaPeca;
    
    novaPeca.id = contadorId++;
    // Sorteia um índice de 0 a 6 para escolher o tipo
    novaPeca.nome = tipos[rand() % 7];
    
    return novaPeca;
}

// Inicializa a fila com valores padrão
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == TAM_MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// --- Operações da Fila (Core Logic) ---

// ENQUEUE: Adiciona uma peça ao final da fila
void inserirPeca(Fila *f) {
    if (filaCheia(f)) {
        printf("\n[!] A fila de previsao esta cheia! Jogue uma peca antes.\n");
        return;
    }

    // Gera a peça automaticamente
    Peca nova = gerarPeca();

    // Cálculo Circular: Se chegar ao fim do vetor, volta para o índice 0
    f->fim = (f->fim + 1) % TAM_MAX;
    
    f->itens[f->fim] = nova;
    f->quantidade++;
    
    printf("\n[+] Nova peca adicionada: [%c %d]\n", nova.nome, nova.id);
}

// DEQUEUE: Remove a peça da frente (Ação de Jogar)
void jogarPeca(Fila *f) {
    if (filaVazia(f)) {
        printf("\n[!] Nao ha pecas para jogar!\n");
        return;
    }

    Peca pecaJogada = f->itens[f->inicio];

    // Cálculo Circular: Move o início para a direita, voltando a 0 se necessário
    f->inicio = (f->inicio + 1) % TAM_MAX;
    
    f->quantidade--;

    printf("\n>>> Voce jogou a peca: [%c %d]\n", pecaJogada.nome, pecaJogada.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("\nFila de pecas futuras:\n");
    printf("INICIO -> ");
    
    int i, idx;
    // Percorre apenas a quantidade de itens existentes
    for (i = 0; i < f->quantidade; i++) {
        // Cálculo para encontrar o índice real no vetor circular
        idx = (f->inicio + i) % TAM_MAX;
        
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("<- FIM\n");
    printf("Total na fila: %d/%d\n", f->quantidade, TAM_MAX);
}

// --- Função Principal ---
int main() {
    // Semente para números aleatórios (para gerar peças diferentes)
    srand(time(NULL));

    Fila filaPecas;
    inicializarFila(&filaPecas);
    int opcao;

    // Preenchimento inicial da fila (Conforme requisito: inicializar com elementos)
    printf("--- Inicializando sistema do Tetris Stack ---\n");
    for(int i = 0; i < TAM_MAX; i++) {
        inserirPeca(&filaPecas);
    }

    do {
        printf("\n============================\n");
        exibirFila(&filaPecas);
        printf("============================\n");
        printf("Opcoes de acao:\n");
        printf("1 - Jogar peca (Dequeue)\n");
        printf("2 - Inserir nova peca (Enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&filaPecas);
                break;
            case 2:
                inserirPeca(&filaPecas);
                break;
            case 0:
                printf("Encerrando Tetris Stack...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}