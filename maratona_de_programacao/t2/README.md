<a name="br1"></a> 

Maratona de Programação – DCOM 1001

Cesar Tadeu Pozzer

11/08/2023

Trabalho 2

Faça um programa para determinar quantas possibilidades existem para colocar 8 rainhas em

um tabuleiro de xadrez de forma que nenhuma rainha possa matar outra.

Algumas regras básicas

1\. Não pode ter duas Queens na mesma coluna

2\. Não pode ter duas Queens na mesma diagonal

O programa também deve somar todas as formar de colocar 8 peças no tabuleiro sem as duas

regras acima.

**Passos da solução**

1\. Implemente uma solução recursiva usando backtracking que faça todas as combinações

possíveis de distribuição de peças no tabuleiro. Isso vai gerar uma árvore com todas as

possibilidades. O nó raiz, assim como os demais, vai ter 64 filhos.

a. É necessária alguma estrutura de dados que marque posições já ocupadas

b. Não se pode colocar duas peças na mesma posição.

2\. Crie funções de depuração que imprima na tela configurações do tabuleiro

3\. Utilize #define para generalizar o tamanho da matriz. Para testes iniciais, utilize uma

matriz menor que 8x8.

4\. Vá adicionando condições de poda de ramos infrutíferos e acompanhe o ganho de

desempenho.

5\. Faça uma solução bem modularizada com uso de funções. Deve-se enviar apenas um

arquivo de código fonte.

