#include <stdio.h>   // Biblioteca padrão para entrada e saída (printf, scanf)
#include <string.h>  // Biblioteca para manipulação de strings (fgets, strcspn)

// Define a quantidade máxima de territórios
#define MAX_TERRITORIOS 5

// Define o tamanho máximo das strings
#define TAM_STRING 50

// Definição da struct Territorio
// Ela agrupa informações relacionadas a um território
typedef struct {
    char nome[TAM_STRING];        // Nome do território
    char corExercito[TAM_STRING]; // Cor do exército dominante
    int numeroTropas;             // Número de tropas no território
} Territorio;

int main() {

    // Criação de um vetor estático de 5 territórios
    Territorio territorios[MAX_TERRITORIOS];

    printf("=== Cadastro de Territorios ===\n\n");

    // Laço para entrada de dados dos territórios
    for (int i = 0; i < MAX_TERRITORIOS; i++) {

        printf("Territorio %d\n", i + 1);

        // Leitura do nome do território
        printf("Nome do territorio: ");
        fgets(territorios[i].nome, TAM_STRING, stdin);

        // Remove o caractere '\n' que o fgets adiciona no final
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        // Leitura da cor do exército
        printf("Cor do exercito: ");
        fgets(territorios[i].corExercito, TAM_STRING, stdin);

        // Remove o '\n' da string
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        // Leitura do número de tropas
        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].numeroTropas);

        // Limpa o buffer do teclado para evitar problemas com fgets
        getchar();

        printf("\n");
    }

    // Exibição do estado atual do mapa
    printf("\n=== Estado Atual do Mapa ===\n\n");

    // Laço para imprimir todos os territórios cadastrados
    for (int i = 0; i < MAX_TERRITORIOS; i++) {

        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].corExercito);
        printf("Numero de Tropas: %d\n", territorios[i].numeroTropas);
        printf("-----------------------------\n");
    }

    // Finaliza o programa
    return 0;
}