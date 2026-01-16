/* Bibliotecas padrão */
#include <stdio.h>   // Entrada e saída (printf, scanf, fgets)
#include <stdlib.h>  // calloc, free, rand, srand
#include <string.h>  // Manipulação de strings (strcpy, strcspn)
#include <time.h>    // time() para semente de números aleatórios

/* Constantes */
#define MAX_TERRITORIOS 5   // Número máximo de territórios
#define TAM 50              // Tamanho máximo de strings

/* Estrutura que representa um território */
typedef struct {
    char nome[TAM];  // Nome do território
    char cor[TAM];   // Cor do exército que domina o território
    int tropas;      // Quantidade de tropas no território
} Territorio;

/* --------------------------------------------------
   Função responsável pelo cadastro dos territórios
-------------------------------------------------- */
void cadastrarTerritorios(Territorio *t) {

    /* Percorre todos os territórios alocados dinamicamente */
    for (int i = 0; i < MAX_TERRITORIOS; i++) {

        printf("\n--- Territorio %d ---\n", i + 1);

        /* Leitura do nome do território */
        printf("Nome: ");
        fgets(t[i].nome, TAM, stdin);
        /* Remove o caractere '\n' inserido pelo fgets */
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        /* Leitura da cor do exército */
        printf("Cor do exercito: ");
        fgets(t[i].cor, TAM, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        /* Leitura do número de tropas */
        printf("Numero de tropas: ");
        scanf("%d", &t[i].tropas);
        getchar(); // Limpa o buffer do teclado
    }
}

/* --------------------------------------------------
   Função que exibe o estado atual do mapa
-------------------------------------------------- */
void exibirMapa(Territorio *t) {

    printf("\n📍 ESTADO ATUAL DO MAPA\n");

    /* Exibe os dados de todos os territórios */
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1,
               t[i].nome,
               t[i].cor,
               t[i].tropas);
    }
}

/* --------------------------------------------------
   Função que simula o ataque entre dois territórios
-------------------------------------------------- */
void simularAtaque(Territorio *atacante, Territorio *defensor) {

    /* Um território precisa de pelo menos 2 tropas para atacar */
    if (atacante->tropas <= 1) {
        printf("\n⚠️ Ataque invalido! O atacante precisa de mais de 1 tropa.\n");
        return;
    }

    /* Sorteio dos dados (valores de 1 a 6) */
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Dados de batalha\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    /* Regra do jogo:
       Empate favorece o atacante */
    if (dadoAtacante >= dadoDefensor) {

        /* Defensor perde uma tropa */
        defensor->tropas--;
        printf("✅ Atacante venceu! Defensor perdeu 1 tropa.\n");

        /* Verifica se o defensor perdeu todas as tropas */
        if (defensor->tropas <= 0) {
            printf("🏳️ Territorio conquistado!\n");

            /* Território passa a pertencer ao atacante */
            strcpy(defensor->cor, atacante->cor);

            /* Define tropas mínimas no território conquistado */
            defensor->tropas = 1;

            /* Atacante perde uma tropa para ocupar o território */
            atacante->tropas--;
        }

    } else {
        /* Caso o defensor vença */
        atacante->tropas--;
        printf("❌ Defensor venceu! Atacante perdeu 1 tropa.\n");
    }
}

/* --------------------------------------------------
   Função principal
-------------------------------------------------- */
int main() {

    /* Inicializa o gerador de números aleatórios */
    srand(time(NULL));

    /* Alocação dinâmica do vetor de territórios */
    Territorio *territorios = calloc(MAX_TERRITORIOS, sizeof(Territorio));

    /* Verificação de erro na alocação */
    if (territorios == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    /* Cadastro inicial dos territórios */
    cadastrarTerritorios(territorios);

    int atacante, defensor;
    char continuar;

    /* Laço principal da fase de ataque */
    do {
        exibirMapa(territorios);

        /* Escolha do território atacante */
        printf("\nEscolha o territorio ATACANTE (1 a 5): ");
        scanf("%d", &atacante);

        /* Escolha do território defensor */
        printf("Escolha o territorio DEFENSOR (1 a 5): ");
        scanf("%d", &defensor);
        getchar(); // Limpa buffer

        /* Validação da escolha */
        if (atacante < 1 || atacante > 5 ||
            defensor < 1 || defensor > 5 ||
            atacante == defensor) {

            printf("⚠️ Escolha invalida!\n");
        } else {
            /* Chamada da função de ataque */
            simularAtaque(&territorios[atacante - 1],
                          &territorios[defensor - 1]);
        }

        /* Pergunta se o jogador deseja continuar */
        printf("\nDeseja continuar atacando? (s/n): ");
        scanf("%c", &continuar);
        getchar();

    } while (continuar == 's' || continuar == 'S');

    /* Liberação da memória alocada dinamicamente */
    free(territorios);

    printf("\n🧹 Memoria liberada. Fim do jogo.\n");

    return 0;
}
