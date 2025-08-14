#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Definição da estrutura Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
    int jogador; // 0 = neutro, 1 = jogador 1, 2 = jogador 2
} Territorio;

// Função para inicializar os territórios
void inicializarTerritorios(Territorio territorios[], int quantidade) {
    char nomes[][30] = {"América do Norte", "América do Sul", "Europa", "África", "Ásia", "Oceania"};
    char cores[][10] = {"Azul", "Vermelho", "Verde", "Amarelo", "Roxo", "Laranja"};
    
    for (int i = 0; i < quantidade; i++) {
        strcpy(territorios[i].nome, nomes[i % 6]);
        strcpy(territorios[i].cor, cores[i % 6]);
        territorios[i].tropas = rand() % 10 + 1; // 1 a 10 tropas
        territorios[i].jogador = 0; // Neutro
    }
}

// Função para mostrar o mapa
void mostrarMapa(Territorio territorios[], int quantidade) {
    printf("\n=== MAPA DO JOGO ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d: %s\n", i+1, territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("Controlado por: ");
        switch(territorios[i].jogador) {
            case 0: printf("Neutro\n"); break;
            case 1: printf("Jogador 1\n"); break;
            case 2: printf("Jogador 2\n"); break;
        }
    }
    printf("\n");
}

// Função para ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n=== BATALHA ===\n");
    printf("%s (%d tropas) ataca %s (%d tropas)\n", 
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    
    // Simulação de batalha simples
    if (atacante->tropas > defensor->tropas) {
        printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
        defensor->jogador = atacante->jogador;
        defensor->tropas = atacante->tropas - 1;
        atacante->tropas = 1;
    } else {
        printf("Ataque falhou! %s defendeu com sucesso.\n", defensor->nome);
        defensor->tropas -= 1;
        if (defensor->tropas < 1) defensor->tropas = 1;
    }
}

// Função principal do jogo
void jogar() {
    srand(time(0)); // Inicializa o gerador de números aleatórios
    
    const int NUM_TERRITORIOS = 6;
    Territorio territorios[NUM_TERRITORIOS];
    
    inicializarTerritorios(territorios, NUM_TERRITORIOS);
    
    // Jogadores escolhem territórios iniciais
    territorios[0].jogador = 1;
    territorios[1].jogador = 2;
    
    int jogadorAtual = 1;
    bool jogoAtivo = true;
    
    while (jogoAtivo) {
        mostrarMapa(territorios, NUM_TERRITORIOS);
        
        printf("\n=== VEZ DO JOGADOR %d ===\n", jogadorAtual);
        
        // Fase de reforço
        printf("Fase de reforço:\n");
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (territorios[i].jogador == jogadorAtual) {
                territorios[i].tropas += rand() % 3 + 1; // 1-3 tropas extras
                printf("Reforçado %s (+%d tropas)\n", territorios[i].nome, territorios[i].tropas);
            }
        }
        
        // Fase de ataque
        printf("\nFase de ataque (digite 0 para passar):\n");
        int origem, alvo;
        printf("Escolha o território de origem (1-%d): ", NUM_TERRITORIOS);
        scanf("%d", &origem);
        
        if (origem > 0 && origem <= NUM_TERRITORIOS && territorios[origem-1].jogador == jogadorAtual) {
            printf("Escolha o território alvo (1-%d): ", NUM_TERRITORIOS);
            scanf("%d", &alvo);
            
            if (alvo > 0 && alvo <= NUM_TERRITORIOS && territorios[alvo-1].jogador != jogadorAtual) {
                atacar(&territorios[origem-1], &territorios[alvo-1]);
            } else {
                printf("Alvo inválido!\n");
            }
        }
        
        // Verificar condição de vitória
        int territoriosJogador1 = 0;
        int territoriosJogador2 = 0;
        
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (territorios[i].jogador == 1) territoriosJogador1++;
            if (territorios[i].jogador == 2) territoriosJogador2++;
        }
        
        if (territoriosJogador1 == NUM_TERRITORIOS) {
            printf("\nJogador 1 conquistou todos os territórios! VITÓRIA!\n");
            jogoAtivo = false;
        } else if (territoriosJogador2 == NUM_TERRITORIOS) {
            printf("\nJogador 2 conquistou todos os territórios! VITÓRIA!\n");
            jogoAtivo = false;
        }
        
        // Alternar jogador
        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
    }
}

int main() {
    printf("=== JOGO DE ESTRATÉGIA DE TERRITÓRIOS ===\n");
    jogar();
    return 0;
}