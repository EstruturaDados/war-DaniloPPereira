
/* Bibliotecas padrão */
#include <stdio.h>   // Entrada e saída (printf, scanf)
#include <stdlib.h>  // rand, srand
#include <string.h>  // strcpy, strcmp
#include <time.h>    // time (semente do rand)

/* Constantes do programa */
#define MAX_TERRITORIOS 5
#define MAX_NOME 30

/* Enumeração das missões possíveis */
typedef enum {
    MISS_DESTRUIR_VERDE,     // Eliminar todos os territórios verdes
    MISS_CONQUISTAR_3        // Conquistar pelo menos 3 territórios
} Missao;

/* Estrutura que representa um território */
typedef struct {
    char nome[MAX_NOME];     // Nome do território
    char cor[10];            // Cor do exército
    int tropas;              // Número de tropas
    int conquistado;         // 1 = jogador / 0 = inimigo
} Territorio;

/* ---------- PROTÓTIPOS DAS FUNÇÕES ---------- */
void inicializarTerritorios(Territorio t[], int size);
void exibirMapa(const Territorio t[], int size);
void atacar(Territorio t[], int size);
int verificarMissao(const Territorio t[], int size, Missao m);
void exibirMissao(Missao m);

/* ---------- FUNÇÃO PRINCIPAL ---------- */
int main(void) {

    /* Vetor de territórios */
    Territorio territorios[MAX_TERRITORIOS];

    int opcao;      // Opção escolhida no menu
    Missao missao;  // Missão do jogador

    /* Inicializa o gerador de números aleatórios */
    srand(time(NULL));

    /* Cria os territórios automaticamente */
    inicializarTerritorios(territorios, MAX_TERRITORIOS);

    /* Sorteia uma missão */
    missao = rand() % 2;

    /* Exibe a missão ao jogador */
    printf("\n🎯 Missão atribuída:\n");
    exibirMissao(missao);

    /* Laço principal do jogo */
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            /* Opção de ataque */
            case 1:
                atacar(territorios, MAX_TERRITORIOS);
                exibirMapa(territorios, MAX_TERRITORIOS);
                break;

            /* Opção de verificação da missão */
            case 2:
                if (verificarMissao(territorios, MAX_TERRITORIOS, missao)) {
                    printf("\n🏆 MISSÃO CONCLUÍDA! VOCÊ VENCEU!\n");
                    return 0; // Finaliza o programa
                } else {
                    printf("\n❌ Missão ainda não concluída.\n");
                }
                break;

            /* Sair do jogo */
            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            /* Tratamento de erro */
            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

/* ---------- FUNÇÃO: INICIALIZAR TERRITÓRIOS ---------- */
void inicializarTerritorios(Territorio t[], int size) {

    /* Dados fixos para inicialização automática */
    const char *nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "Colômbia"};
    const char *cores[] = {"Vermelho", "Verde", "Azul", "Verde", "Amarelo"};

    for (int i = 0; i < size; i++) {
        strcpy(t[i].nome, nomes[i]);   // Copia o nome
        strcpy(t[i].cor, cores[i]);    // Define a cor do exército
        t[i].tropas = rand() % 10 + 5; // Tropas aleatórias entre 5 e 14
        t[i].conquistado = (i == 0);   // Jogador começa com 1 território
    }
}

/* ---------- FUNÇÃO: EXIBIR MAPA ---------- */
void exibirMapa(const Territorio t[], int size) {

    printf("\n🗺️ MAPA ATUAL\n");

    for (int i = 0; i < size; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d | Dono: %s\n",
               i,
               t[i].nome,
               t[i].cor,
               t[i].tropas,
               t[i].conquistado ? "Jogador" : "Inimigo");
    }
}

/* ---------- FUNÇÃO: ATAQUE ---------- */
void atacar(Territorio t[], int size) {

    int origem, alvo;

    /* Exibe o mapa antes do ataque */
    exibirMapa(t, size);

    printf("\nEscolha território de origem: ");
    scanf("%d", &origem);

    printf("Escolha território alvo: ");
    scanf("%d", &alvo);

    /* Validação das regras de ataque */
    if (!t[origem].conquistado || t[alvo].conquistado) {
        printf("\n❌ Ataque inválido.\n");
        return;
    }

    /* Simulação de dados */
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n🎲 Ataque: %d | Defesa: %d\n", dadoAtaque, dadoDefesa);

    /* Resultado do ataque */
    if (dadoAtaque > dadoDefesa) {
        printf("✅ Território conquistado!\n");
        t[alvo].conquistado = 1;
        strcpy(t[alvo].cor, t[origem].cor);
    } else {
        printf("❌ Ataque falhou.\n");
        t[origem].tropas--; // Perde uma tropa
    }
}

/* ---------- FUNÇÃO: VERIFICAR MISSÃO ---------- */
int verificarMissao(const Territorio t[], int size, Missao m) {

    /* Missão: destruir exército verde */
    if (m == MISS_DESTRUIR_VERDE) {
        for (int i = 0; i < size; i++) {
            if (strcmp(t[i].cor, "Verde") == 0)
                return 0; // Ainda existe território verde
        }
        return 1; // Missão cumprida
    }

    /* Missão: conquistar 3 territórios */
    if (m == MISS_CONQUISTAR_3) {
        int total = 0;
        for (int i = 0; i < size; i++) {
            if (t[i].conquistado)
                total++;
        }
        return total >= 3;
    }

    return 0;
}

/* ---------- FUNÇÃO: EXIBIR MISSÃO ---------- */
void exibirMissao(Missao m) {

    if (m == MISS_DESTRUIR_VERDE)
        printf("➡️ Destruir todo o exército Verde\n");
    else
        printf("➡️ Conquistar 3 territórios\n");
}
