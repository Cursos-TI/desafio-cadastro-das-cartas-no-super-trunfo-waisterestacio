#include <stdio.h>
#include <string.h>

// Função para comparar dois atributos e retornar o vencedor
int compararAtributo(int atributo, int carta1_int, int carta2_int, float carta1_float, float carta2_float) {
    if (atributo == 5) { // Densidade Demográfica (menor valor vence)
        return carta1_float < carta2_float ? 1 : (carta1_float > carta2_float ? 2 : 0);
    } else if (atributo == 2 || atributo == 3) { // Área e PIB (float)
        return carta1_float > carta2_float ? 1 : (carta1_float < carta2_float ? 2 : 0);
    } else { // População e Pontos Turísticos (int)
        return carta1_int > carta2_int ? 1 : (carta1_int < carta2_int ? 2 : 0);
    }
}

// Função para descobrir o nome da opção pelo código
const char* opcaoNome(int opcao) {
    switch (opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        default: return "Atributo Inválido";
    }
}

int main() {
    // Variáveis para a primeira carta
    char estado1;
    char codigo1[4];
    char cidade1[50];
    int populacao1;
    float area1;
    float pib1;
    int pontos_turisticos1;
    
    // Variáveis para a segunda carta
    char estado2;
    char codigo2[4];
    char cidade2[50];
    int populacao2;
    float area2;
    float pib2;
    int pontos_turisticos2;

    // Leitura dos dados da primeira carta
    printf("Cadastro da Carta 1:\n");
    printf("Estado (A-H): ");
    scanf(" %c", &estado1);
    printf("Código da Carta (ex: A01): ");
    scanf("%s", codigo1);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", cidade1);
    printf("População: ");
    scanf("%d", &populacao1);
    printf("Área (em km²): ");
    scanf("%f", &area1);
    printf("PIB (em bilhões de reais): ");
    scanf("%f", &pib1);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontos_turisticos1);

    // Leitura dos dados da segunda carta
    printf("\nCadastro da Carta 2:\n");
    printf("Estado (A-H): ");
    scanf(" %c", &estado2);
    printf("Código da Carta (ex: B02): ");
    scanf("%s", codigo2);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", cidade2);
    printf("População: ");
    scanf("%d", &populacao2);
    printf("Área (em km²): ");
    scanf("%f", &area2);
    printf("PIB (em bilhões de reais): ");
    scanf("%f", &pib2);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontos_turisticos2);

    // Cálculos para a Carta 1
    float densidade_populacional1 = populacao1 / area1;
    float pib_per_capita1 = pib1 / populacao1;

    // Cálculos para a Carta 2
    float densidade_populacional2 = populacao2 / area2;
    float pib_per_capita2 = pib2 / populacao2;

    // Menu interativo para escolha de dois atributos
    int opcao1, opcao2;
    do {
        printf("\n--- Menu de Comparação ---\n");
        printf("Escolha o primeiro atributo para comparar as cartas:\n");
        printf("1. População\n");
        printf("2. Área\n");
        printf("3. PIB\n");
        printf("4. Número de Pontos Turísticos\n");
        printf("5. Densidade Demográfica\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao1);

        printf("\nEscolha o segundo atributo para comparar as cartas:\n");
        printf("1. População\n");
        printf("2. Área\n");
        printf("3. PIB\n");
        printf("4. Número de Pontos Turísticos\n");
        printf("5. Densidade Demográfica\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao2);

        if (opcao1 == opcao2) {
            printf("\nErro: Você não pode escolher o mesmo atributo duas vezes. Tente novamente.\n");
        }
    } while (opcao1 == opcao2);

    // Declaração das variáveis para armazenar os resultados das comparações
    int resultado1 = 0, resultado2 = 0;
    float soma1 = 0, soma2 = 0;

    // Comparação dos atributos
    // Primeiro atributo
    switch (opcao1) {
        case 1:
            resultado1 = compararAtributo(1, populacao1, populacao2, 0, 0);
            soma1 += populacao1;
            soma2 += populacao2;
            break;
        case 2:
            resultado1 = compararAtributo(2, 0, 0, area1, area2);
            soma1 += area1;
            soma2 += area2;
            break;
        case 3:
            resultado1 = compararAtributo(3, 0, 0, pib1, pib2);
            soma1 += pib1;
            soma2 += pib2;
            break;
        case 4:
            resultado1 = compararAtributo(4, pontos_turisticos1, pontos_turisticos2, 0, 0);
            soma1 += pontos_turisticos1;
            soma2 += pontos_turisticos2;
            break;
        case 5:
            resultado1 = compararAtributo(5, 0, 0, densidade_populacional1, densidade_populacional2);
            soma1 += densidade_populacional1;
            soma2 += densidade_populacional2;
            break;
    }

    // Segundo atributo
    switch (opcao2) {
        case 1:
            resultado2 = compararAtributo(1, populacao1, populacao2, 0, 0);
            soma1 += populacao1;
            soma2 += populacao2;
            break;
        case 2:
            resultado2 = compararAtributo(2, 0, 0, area1, area2);
            soma1 += area1;
            soma2 += area2;
            break;
        case 3:
            resultado2 = compararAtributo(3, 0, 0, pib1, pib2);
            soma1 += pib1;
            soma2 += pib2;
            break;
        case 4:
            resultado2 = compararAtributo(4, pontos_turisticos1, pontos_turisticos2, 0, 0);
            soma1 += pontos_turisticos1;
            soma2 += pontos_turisticos2;
            break;
        case 5:
            resultado2 = compararAtributo(5, 0, 0, densidade_populacional1, densidade_populacional2);
            soma1 += densidade_populacional1;
            soma2 += densidade_populacional2;
            break;
    }

    // Exibição dos resultados
    printf("\n--- Resultado da Comparação ---\n");
    printf("Carta 1: %s (%c)\n", cidade1, estado1);
    printf("Carta 2: %s (%c)\n", cidade2, estado2);

    printf("\nAtributo 1: %s\n", opcaoNome(opcao1));
    printf("Carta 1: %.2f\n", (opcao1 == 5) ? densidade_populacional1 : (opcao1 == 2 || opcao1 == 3) ? (opcao1 == 2 ? area1 : pib1) : (opcao1 == 1 ? populacao1 : pontos_turisticos1));
    printf("Carta 2: %.2f\n", (opcao1 == 5) ? densidade_populacional2 : (opcao1 == 2 || opcao1 == 3) ? (opcao1 == 2 ? area2 : pib2) : (opcao1 == 1 ? populacao2 : pontos_turisticos2));
    printf("Resultado: %s\n", resultado1 == 1 ? "Carta 1 venceu" : (resultado1 == 2 ? "Carta 2 venceu" : "Empate"));

    printf("\nAtributo 2: %s\n", opcaoNome(opcao2));
    printf("Carta 1: %.2f\n", (opcao2 == 5) ? densidade_populacional1 : (opcao2 == 2 || opcao2 == 3) ? (opcao2 == 2 ? area1 : pib1) : (opcao2 == 1 ? populacao1 : pontos_turisticos1));
    printf("Carta 2: %.2f\n", (opcao2 == 5) ? densidade_populacional2 : (opcao2 == 2 || opcao2 == 3) ? (opcao2 == 2 ? area2 : pib2) : (opcao2 == 1 ? populacao2 : pontos_turisticos2));
    printf("Resultado: %s\n", resultado2 == 1 ? "Carta 1 venceu" : (resultado2 == 2 ? "Carta 2 venceu" : "Empate"));

    // Soma dos atributos e resultado final
    printf("\nSoma dos Atributos:\n");
    printf("Carta 1: %.2f\n", soma1);
    printf("Carta 2: %.2f\n", soma2);

    if (soma1 > soma2) {
        printf("\nResultado Final: Carta 1 (%s) venceu!\n", cidade1);
    } else if (soma1 < soma2) {
        printf("\nResultado Final: Carta 2 (%s) venceu!\n", cidade2);
    } else {
        printf("\nResultado Final: Empate!\n");
    }

    return 0;
}