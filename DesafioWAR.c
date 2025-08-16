#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Definição da estrutura Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
    int jogador; // 0 = neutro, 1 = jogador 1, 2 = jogador 2
} Territorio;

// Protótipos de funções
Territorio* alocarTerritorios(int quantidade);
void inicializarTerritorios(Territorio* territorios, int quantidade);
void mostrarMapa(Territorio* territorios, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void cadastrarTerritorios(Territorio* territorios, int quantidade);
void realizarAtaque(Territorio* territorios, int quantidade, int jogadorAtual);

// Função principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    printf("=== WAR ESTRUTURADO ===\n\n");
    
    int numTerritorios;
    printf("Quantos territorios deseja criar? (min 2, max 20): ");
    scanf("%d", &numTerritorios);
    
    // Validação da entrada
    if(numTerritorios < 2 || numTerritorios > 20) {
        printf("Quantidade invalida. Usando 6 territorios.\n");
        numTerritorios = 6;
    }
    
    // Alocação dinâmica de memória
    Territorio* territorios = alocarTerritorios(numTerritorios);
    if(territorios == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    
    // Cadastro e inicialização
    cadastrarTerritorios(territorios, numTerritorios);
    
    // Jogadores escolhem territórios iniciais
    territorios[0].jogador = 1;
    strcpy(territorios[0].cor, "Azul");
    territorios[1].jogador = 2;
    strcpy(territorios[1].cor, "Vermelho");
    
    int jogadorAtual = 1;
    bool jogoAtivo = true;
    
    while(jogoAtivo) {
        mostrarMapa(territorios, numTerritorios);
        
        printf("\n=== VEZ DO JOGADOR %d (%s) ===\n", 
              jogadorAtual, jogadorAtual == 1 ? "Azul" : "Vermelho");
        
        // Fase de reforço
        printf("\n[FASE DE REFORCO]\n");
        for(int i = 0; i < numTerritorios; i++) {
            if(territorios[i].jogador == jogadorAtual) {
                int reforco = rand() % 3 + 1; // 1-3 tropas
                territorios[i].tropas += reforco;
                printf("- %s recebeu +%d tropas (total: %d)\n", 
                      territorios[i].nome, reforco, territorios[i].tropas);
            }
        }
        
        // Fase de ataque
        printf("\n[FASE DE ATAQUE]\n");
        realizarAtaque(territorios, numTerritorios, jogadorAtual);
        
        // Verificar condição de vitória
        int territoriosJogador1 = 0;
        int territoriosJogador2 = 0;
        
        for(int i = 0; i < numTerritorios; i++) {
            if(territorios[i].jogador == 1) territoriosJogador1++;
            if(territorios[i].jogador == 2) territoriosJogador2++;
        }
        
        if(territoriosJogador1 == numTerritorios) {
            printf("\nJogador 1 (Azul) conquistou todos os territorios! VITORIA!\n");
            jogoAtivo = false;
        } else if(territoriosJogador2 == numTerritorios) {
            printf("\nJogador 2 (Vermelho) conquistou todos os territorios! VITORIA!\n");
            jogoAtivo = false;
        }
        
        // Alternar jogador
        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
    }
    
    liberarMemoria(territorios);
    return 0;
}

// Implementação das funções

Territorio* alocarTerritorios(int quantidade) {
    // Aloca memória para o vetor de territórios
    Territorio* territorios = (Territorio*)calloc(quantidade, sizeof(Territorio));
    return territorios;
}

void inicializarTerritorios(Territorio* territorios, int quantidade) {
    char nomes[][30] = {"América do Norte", "América do Sul", "Europa", "África", 
                       "Ásia", "Oceania", "Alaska", "Groenlandia", "Islandia", 
                       "Madagascar", "Australia", "Brasil", "Argentina", "Peru", 
                       "China", "Japao", "India", "Russia", "Egito", "Canada"};
    
    for(int i = 0; i < quantidade; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].cor, "Neutro");
        territorios[i].tropas = rand() % 5 + 1; // 1 a 5 tropas
        territorios[i].jogador = 0; // Neutro
    }
}

void cadastrarTerritorios(Territorio* territorios, int quantidade) {
    printf("\n=== CADASTRO DE TERRITORIOS ===\n");
    inicializarTerritorios(territorios, quantidade);
    
    // Mostra os territórios criados
    for(int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i+1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("Cor: %s\n", territorios[i].cor);
    }
}

void mostrarMapa(Territorio* territorios, int quantidade) {
    printf("\n=== MAPA DO JOGO ===\n");
    printf("%-25s | %-10s | %-6s | %s\n", "Territorio", "Cor", "Tropas", "Jogador");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < quantidade; i++) {
        char jogadorStr[10];
        switch(territorios[i].jogador) {
            case 0: strcpy(jogadorStr, "Neutro"); break;
            case 1: strcpy(jogadorStr, "Jogador1"); break;
            case 2: strcpy(jogadorStr, "Jogador2"); break;
        }
        
        printf("%-25s | %-10s | %-6d | %s\n", 
              territorios[i].nome, territorios[i].cor, territorios[i].tropas, jogadorStr);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== BATALHA ===\n");
    printf("%s (%s - %d tropas) ataca %s (%s - %d tropas)\n", 
          atacante->nome, atacante->cor, atacante->tropas,
          defensor->nome, defensor->cor, defensor->tropas);
    
    // Simulação de dados de batalha
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("Dados: Atacante (%d) vs Defensor (%d)\n", dadoAtacante, dadoDefensor);
    
    if(dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("%s VENCEU a batalha!\n", atacante->nome);
        
        // Defensor perde metade das tropas (arredondado para baixo)
        int perdaDefensor = defensor->tropas / 2;
        if(perdaDefensor < 1) perdaDefensor = 1;
        
        // Atacante perde 1 tropa
        atacante->tropas -= 1;
        if(atacante->tropas < 1) atacante->tropas = 1;
        
        // Defensor muda de dono
        defensor->jogador = atacante->jogador;
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas - 1; // O atacante deixa 1 tropa no original
        
        printf("- %s agora pertence ao Jogador %d (%s)\n", 
              defensor->nome, defensor->jogador, defensor->cor);
    } else {
        // Defensor vence
        printf("%s DEFENDEU com sucesso!\n", defensor->nome);
        
        // Atacante perde 1 tropa
        atacante->tropas -= 1;
        if(atacante->tropas < 1) atacante->tropas = 1;
        
        // Defensor perde 1 tropa
        defensor->tropas -= 1;
        if(defensor->tropas < 1) defensor->tropas = 1;
    }
    
    printf("\nRESULTADO POS-BATALHA:\n");
    printf("- %s: %d tropas\n", atacante->nome, atacante->tropas);
    printf("- %s: %d tropas\n", defensor->nome, defensor->tropas);
}

void realizarAtaque(Territorio* territorios, int quantidade, int jogadorAtual) {
    int origem, alvo;
    bool ataqueValido = false;
    
    do {
        printf("\nTerritorios disponiveis para ataque:\n");
        for(int i = 0; i < quantidade; i++) {
            if(territorios[i].jogador == jogadorAtual && territorios[i].tropas > 1) {
                printf("%d) %s (%d tropas)\n", i+1, territorios[i].nome, territorios[i].tropas);
            }
        }
        
        printf("\nEscolha o territorio de ORIGEM (0 para passar): ");
        scanf("%d", &origem);
        
        if(origem == 0) {
            printf("Jogador %d passou a vez de atacar.\n", jogadorAtual);
            return;
        }
        
        if(origem < 1 || origem > quantidade || 
           territorios[origem-1].jogador != jogadorAtual || 
           territorios[origem-1].tropas <= 1) {
            printf("Origem invalida! Escolha novamente.\n");
            continue;
        }
        
        printf("\nTerritorios que podem ser atacados:\n");
        for(int i = 0; i < quantidade; i++) {
            if(territorios[i].jogador != jogadorAtual && 
               territorios[i].jogador != 0) { // Só pode atacar inimigos (não neutros)
                printf("%d) %s (%d tropas)\n", i+1, territorios[i].nome, territorios[i].tropas);
            }
        }
        
        printf("Escolha o territorio ALVO (0 para cancelar): ");
        scanf("%d", &alvo);
        
        if(alvo == 0) {
            continue;
        }
        
        if(alvo < 1 || alvo > quantidade || 
           territorios[alvo-1].jogador == jogadorAtual || 
           territorios[alvo-1].jogador == 0) {
            printf("Alvo invalido! Escolha novamente.\n");
        } else {
            ataqueValido = true;
        }
    } while(!ataqueValido);
    
    // Realiza o ataque
    atacar(&territorios[origem-1], &territorios[alvo-1]);
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}