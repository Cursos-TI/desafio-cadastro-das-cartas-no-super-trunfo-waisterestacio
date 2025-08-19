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
void liberarMemoria(Territorio* mapa, char* missaoJogador1, char* missaoJogador2);
void cadastrarTerritorios(Territorio* territorios, int quantidade);
void realizarAtaque(Territorio* territorios, int quantidade, int jogadorAtual);
char* atribuirMissao(char* missoes[], int totalMissoes);
void exibirMissao(char* missao, int jogador);
int verificarMissao(char* missao, Territorio* territorios, int numTerritorios, int jogador);

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    printf("=== WAR ESTRUTURADO COM MISSOES ===\n\n");
    
    // Vetor de missões estratégicas
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Destruir todas as tropas da cor Vermelha",
        "Controlar 50%% dos territorios",
        "Conquistar um territorio de cada cor",
        "Manter 10 tropas em pelo menos 3 territorios"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);
    
    int numTerritorios;
    printf("Quantos territorios deseja criar? (min 4, max 20): ");
    scanf("%d", &numTerritorios);
    
    // Validação da entrada
    if(numTerritorios < 4 || numTerritorios > 20) {
        printf("Quantidade invalida. Usando 8 territorios.\n");
        numTerritorios = 8;
    }
    
    // Alocação dinâmica de memória para territórios
    Territorio* territorios = alocarTerritorios(numTerritorios);
    if(territorios == NULL) {
        printf("Erro ao alocar memoria para territorios!\n");
        return 1;
    }
    
    // Cadastro e inicialização dos territórios
    cadastrarTerritorios(territorios, numTerritorios);
    
    // Atribuição de territórios iniciais aos jogadores
    territorios[0].jogador = 1;
    strcpy(territorios[0].cor, "Azul");
    territorios[1].jogador = 2;
    strcpy(territorios[1].cor, "Vermelho");
    
    // Atribuição de missões aos jogadores
    char* missaoJogador1 = atribuirMissao(missoes, totalMissoes);
    char* missaoJogador2 = atribuirMissao(missoes, totalMissoes);
    
    // Exibir missões iniciais
    printf("\n=== MISSOES INICIAIS ===\n");
    exibirMissao(missaoJogador1, 1);
    exibirMissao(missaoJogador2, 2);
    printf("\nPressione Enter para continuar...");
    getchar(); getchar(); // Pausa para leitura
    
    int jogadorAtual = 1;
    bool jogoAtivo = true;
    int vencedor = 0;
    
    while(jogoAtivo) {
        system("clear || cls"); // Limpa a tela (funciona em Linux e Windows)
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
        
        // Verificar missão do jogador atual
        if(verificarMissao(jogadorAtual == 1 ? missaoJogador1 : missaoJogador2, 
                          territorios, numTerritorios, jogadorAtual)) {
            vencedor = jogadorAtual;
            jogoAtivo = false;
            break;
        }
        
        // Verificar condição de vitória por dominação total
        int territoriosJogador1 = 0;
        int territoriosJogador2 = 0;
        
        for(int i = 0; i < numTerritorios; i++) {
            if(territorios[i].jogador == 1) territoriosJogador1++;
            if(territorios[i].jogador == 2) territoriosJogador2++;
        }
        
        if(territoriosJogador1 == numTerritorios) {
            vencedor = 1;
            jogoAtivo = false;
        } else if(territoriosJogador2 == numTerritorios) {
            vencedor = 2;
            jogoAtivo = false;
        }
        
        // Alternar jogador
        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        
        // Pausa entre turnos
        printf("\nPressione Enter para continuar...");
        getchar(); getchar();
    }
    
    // Tela final
    system("clear || cls");
    if(vencedor > 0) {
        printf("\n=== JOGADOR %d VENCEU! ===\n", vencedor);
        printf("Missao cumprida: %s\n", 
              vencedor == 1 ? missaoJogador1 : missaoJogador2);
        mostrarMapa(territorios, numTerritorios);
    }
    
    liberarMemoria(territorios, missaoJogador1, missaoJogador2);
    return 0;
}

// Implementação das funções

Territorio* alocarTerritorios(int quantidade) {
    return (Territorio*)calloc(quantidade, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* territorios, int quantidade) {
    char nomes[][30] = {"América do Norte", "América do Sul", "Europa", "África", 
                       "Ásia", "Oceania", "Alasca", "Groenlândia", "Islândia", 
                       "Madagascar", "Austrália", "Brasil", "Argentina", "Peru", 
                       "China", "Japão", "Índia", "Rússia", "Egito", "Canadá"};
    char cores[][10] = {"Verde", "Amarelo", "Roxo", "Laranja", "Cinza", "Marrom"};
    
    for(int i = 0; i < quantidade; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].cor, cores[i % 6]);
        territorios[i].tropas = rand() % 5 + 1; // 1 a 5 tropas
        territorios[i].jogador = 0; // Neutro
    }
}

void cadastrarTerritorios(Territorio* territorios, int quantidade) {
    printf("\n=== INICIALIZANDO TERRITORIOS ===\n");
    inicializarTerritorios(territorios, quantidade);
    
    // Mostra os territórios criados
    for(int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i+1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
}

void mostrarMapa(Territorio* territorios, int quantidade) {
    printf("\n=== MAPA DO JOGO ===\n");
    printf("%-20s | %-10s | %-6s | %s\n", "Territorio", "Cor", "Tropas", "Jogador");
    printf("--------------------------------------------\n");
    
    for(int i = 0; i < quantidade; i++) {
        char jogadorStr[10];
        switch(territorios[i].jogador) {
            case 0: strcpy(jogadorStr, "Neutro"); break;
            case 1: strcpy(jogadorStr, "Jogador1"); break;
            case 2: strcpy(jogadorStr, "Jogador2"); break;
        }
        
        printf("%-20s | %-10s | %-6d | %s\n", 
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
            if(territorios[i].jogador != jogadorAtual && territorios[i].jogador != 0) {
                printf("%d) %s (%d tropas - %s)\n", i+1, territorios[i].nome, 
                      territorios[i].tropas, territorios[i].jogador == 1 ? "Azul" : "Vermelho");
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

char* atribuirMissao(char* missoes[], int totalMissoes) {
    // Aloca memória para a missão
    char* missao = (char*)malloc(100 * sizeof(char));
    if(missao == NULL) {
        printf("Erro ao alocar memoria para missao!\n");
        exit(1);
    }
    
    // Sorteia uma missão aleatória
    int indice = rand() % totalMissoes;
    strcpy(missao, missoes[indice]);
    
    return missao;
}

void exibirMissao(char* missao, int jogador) {
    printf("Missao do Jogador %d: %s\n", jogador, missao);
}

int verificarMissao(char* missao, Territorio* territorios, int numTerritorios, int jogador) {
    // Verifica qual missão foi cumprida
    if(strstr(missao, "Conquistar 3 territorios seguidos")) {
        // Lógica simplificada - verifica se tem pelo menos 3 territórios
        int count = 0;
        for(int i = 0; i < numTerritorios; i++) {
            if(territorios[i].jogador == jogador) count++;
        }
        return count >= 3;
    }
    else if(strstr(missao, "Destruir todas as tropas da cor Vermelha")) {
        // Verifica se não há mais territórios vermelhos
        for(int i = 0; i < numTerritorios; i++) {
            if(strcmp(territorios[i].cor, "Vermelho") == 0 && territorios[i].jogador != jogador) {
                return 0;
            }
        }
        return 1;
    }
    else if(strstr(missao, "Controlar 50%% dos territorios")) {
        int count = 0;
        for(int i = 0; i < numTerritorios; i++) {
            if(territorios[i].jogador == jogador) count++;
        }
        return count >= numTerritorios / 2;
    }
    else if(strstr(missao, "Conquistar um territorio de cada cor")) {
        // Lógica simplificada - verifica se tem territórios de pelo menos 3 cores diferentes
        int coresDiferentes = 0;
        char coresVistas[6][10] = {0};
        
        for(int i = 0; i < numTerritorios; i++) {
            if(territorios[i].jogador == jogador) {
                int novaCor = 1;
                for(int j = 0; j < coresDiferentes; j++) {
                    if(strcmp(territorios[i].cor, coresVistas[j]) == 0) {
                        novaCor = 0;
                        break;
                    }
                }
                if(novaCor) {
                    strcpy(coresVistas[coresDiferentes], territorios[i].cor);
                    coresDiferentes++;
                }
            }
        }
        return coresDiferentes >= 3;
    }
    else if(strstr(missao, "Manter 10 tropas em pelo menos 3 territorios")) {
        int count = 0;
        for(int i = 0; i < numTerritorios; i++) {
            if(territorios[i].jogador == jogador && territorios[i].tropas >= 10) {
                count++;
            }
        }
        return count >= 3;
    }
    
    return 0;
}

void liberarMemoria(Territorio* mapa, char* missaoJogador1, char* missaoJogador2) {
    free(mapa);
    free(missaoJogador1);
    free(missaoJogador2);
    printf("\nMemoria liberada com sucesso!\n");
}