#include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.
//Teste larissa

int main() {
    // Sugestão: Defina variáveis separadas para cada atributo da cidade.
    // Exemplos de atributos: código da cidade, nome, população, área, PIB, número de pontos turísticos.
    int codigo = 0;
    char nome[50] = "";
    int populacao = 0;
    float area = 0.0;
    float pib = 0.0;
    int pontos = 0;
    
    // Cadastro das Cartas:
    // Sugestão: Utilize a função scanf para capturar as entradas do usuário para cada atributo.
    // Solicite ao usuário que insira as informações de cada cidade, como o código, nome, população, área, etc.
    printf("Insira o código da cidade: ");
    scanf("%d", &codigo);
    
    printf("Insira o nome da cidade: ");
    scanf(" %s", &nome);
    
    printf("Insira o população da cidade: ");
    scanf(" %d", &populacao);
    
    printf("Insira o área da cidade: ");
    scanf("%f", &area);
    
    printf("Insira o PIB da cidade: ");
    scanf("%f", &pib);
    
    printf("Insira o número de pontos turísticos da cidade: ");
    scanf("%d", &pontos);
    
    // Exibição dos Dados das Cartas:
    // Sugestão: Utilize a função printf para exibir as informações das cartas cadastradas de forma clara e organizada.
    // Exiba os valores inseridos para cada atributo da cidade, um por linha.
    printf(":: Informações da carta ::");
    printf("- Código: %d\n", codigo);
    printf("- Nome: %s\n", nome);
    printf("- População: %d\n", populacao);
    printf("- Área: %.2f\n", area);
    printf("- PIB: %.2f\n", pib);
    printf("- Pontos turísticos: %d\n", pontos);

    return 0;
}
