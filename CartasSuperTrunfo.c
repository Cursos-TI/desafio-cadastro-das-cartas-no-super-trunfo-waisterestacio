#include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.

int main() {
    // Definindo as variáveis da carta
    int codigo = 0;
    char nome[50] = "";
    int populacao = 0;
    float area = 0.0;
    float pib = 0.0;
    int pontos = 0;
    
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
    
    // Exibição dos Dados das Cartas:
    printf(":: Informações da carta ::");
    printf("- Código: %d\n", codigo);
    printf("- Nome: %s\n", nome);
    printf("- População: %d\n", populacao);
    printf("- Área: %.2f\n", area);
    printf("- PIB: %.2f\n", pib);
    printf("- Pontos turísticos: %d\n", pontos);

    // Finalizando a execução
    return 0;
}
