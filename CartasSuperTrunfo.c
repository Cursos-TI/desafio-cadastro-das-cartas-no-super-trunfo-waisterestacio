#include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.

int main() {
    // Definindo as variáveis da carta
    char estado[30] = "";
    int codigo = 0;
    char nome[50] = "";
    int populacao = 0;
    float area = 0.0;
    float pib = 0.0;
    int pontos = 0;
    float densidadePopulacional = 0.0;
    float pibPerCapta = 0.0;
    
    // Solicitando para o usuário informar o estado
    printf("Insira o estado: ");
    scanf("%s", &estado);
    
    // Solicitando para o usuário informar o código da cidade
    printf("Insira o código da cidade: ");
    scanf("%d", &codigo);
    
    // Solicitando para o usuário informar o nome da cidade
    printf("Insira o nome da cidade: ");
    scanf(" %s", &nome);
    
    // Solicitando para o usuário informar a população da cidade
    printf("Insira o população da cidade: ");
    scanf(" %d", &populacao);
    
    // Solicitando para o usuário informar a área da cidade
    printf("Insira o área da cidade: ");
    scanf("%f", &area);
    
    // Solicitando para o usuário informar o PIB da cidade
    printf("Insira o PIB da cidade: ");
    scanf("%f", &pib);
    
    // Solicitando para o usuário informar o número de pontos turísticos da cidade
    printf("Insira o número de pontos turísticos da cidade: ");
    scanf("%d", &pontos);

    // Calcula a densidade populacional
    densidadePopulacional = populacao / area;

    // Calcula o PIB per capita
    pibPerCapta = pib / populacao;

    // Exibição dos dados da carta:
    printf("*** Informações da carta ***\n");
    printf("- Estado: %s\n", estado);
    printf("- Código: %d\n", codigo);
    printf("- Nome da Cidade: %s\n", nome);
    printf("- População: %d\n", populacao);
    printf("- Área: %.2f\n", area);
    printf("- PIB: %.2f\n", pib);
    printf("- Número de Pontos Turísticos: %d\n", pontos);
    printf("- Densidade Populacional: %.2f hab/km²\n", densidadePopulacional);
    printf("- PIB per Capita: %.2f reais\n", pibPerCapta);

    // Finalizando a execução
    return 0;
}
