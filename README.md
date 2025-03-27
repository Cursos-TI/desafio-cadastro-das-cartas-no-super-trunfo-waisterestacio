# Super Trunfo - Comparação de Cidades

Um jogo em C que compara cartas de cidades baseado em atributos como população, área, PIB, etc.

## Exemplo de Uso

```
Cadastro da Carta 1:
Estado (A-H): A
Código da Carta: A01
Nome da Cidade: São Paulo
População: 12000000
Área: 1521.0
PIB: 450.0
Pontos Turísticos: 50

Cadastro da Carta 2:
Estado (A-H): B
Código da Carta: B02
Nome da Cidade: Rio de Janeiro
População: 6700000
Área: 1200.0
PIB: 300.0
Pontos Turísticos: 40

--- Menu de Comparação ---
Escolha o primeiro atributo: 1 (População)
Escolha o segundo atributo: 5 (Densidade Demográfica)

Resultado:
- População: São Paulo venceu!
- Densidade Demográfica: Rio de Janeiro venceu!
Soma dos atributos: São Paulo (12000000.00) vs Rio de Janeiro (6700000.00)
Vencedor final: São Paulo!

```
## Como Compilar e Executar

```
bash
gcc CartasSuperTrunfo.c -o CartasSuperTrunfo
./CartasSuperTrunfo
```
