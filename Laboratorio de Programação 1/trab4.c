#include <stdio.h>

void troco();
void meteoritos();
void bafo();

int main(){

  int escolha;
  printf("Escolha uma das opções digitando o número:\n1)Troco\n2)Meteoritos\n3)Bafo\n");
  scanf("%d", &escolha);

  switch (escolha) {

    case 1:
      troco();
      break;

    case 2:
      meteoritos();
      break;

    case 3:
      bafo();
      break;
  }

  return 0;

}

void troco(){

  int depositos, joao, ze, dinheiroJoao = 0, dinheiroZe = 0, diferenca = 0;
  printf("Quantos depósitos serão feitos:\n");
  scanf("%d", &depositos);

  for(int i = 0; i < depositos; i++){

    printf("Quanto será depositado (em centavos) no cofre de João e Zé respectivamente:\n");
    scanf("%d %d", &joao, &ze);

    dinheiroJoao += joao;
    dinheiroZe += ze;

    diferenca += joao - ze;

    diferenca > 0 ? printf("João possui %d centavos a mais\n", diferenca) : diferenca == 0 ? printf("Não há diferença no cofrinho dos dois\n") : printf("Zé possui %d centavos a mais\n", 0 - diferenca);;

  }

}

void meteoritos(){

  int x1, y1, x2, y2, x, y, n, j = 1;

  do{

    int meteoritosEncontrados = 0;

    printf("Digite a primeira coordenada da fazenda no formato (x,y), de modo que seja o vértice superior esquerdo.\n");
    scanf("%d, %d", &x1, &y1);

    printf("\nDigite a segunda coordenada da fazenda no formato (x,y), de modo que seja o vértice inferior direito (lembre-se que a coordenada y deve ser inferior à anterior e x superior, uma vez que seja um plano cartesiano)\n");
    scanf("%d, %d", &x2, &y2);

    if(x1 != x2 && y1 != y2){

      printf("\nQuanto meteoritos cairão?\n");
      scanf("%d", &n);

      for(int i = 0; i < n ; i++){

        printf("\nQual a coordenada do %dº meteorito no formato (x,y)\n", i + 1);
        scanf("%d, %d", &x, &y);

        if(x >= x1 && x <= x2 && y <= y1 && y >= y2)
          meteoritosEncontrados++;

      }

      printf("\n---------------------------------------------\n");
      printf("Teste %d\n", j++);
      printf("Meteoritos que caíram na fazenda: %d\n", meteoritosEncontrados);
      printf("\n---------------------------------------------\n");

    }

  }while(x1 != x2 || y1 != y2 || x2 != y1 || x1 != 0);

}

void bafo(){

  int rodadas, alex, beto;
  char resposta;

  do{

    printf("Quantas rodadas irão ser?\n");
    scanf("%d", &rodadas);

    for(int i = 0; i < rodadas; i++){

      printf("Digite quantas figurinhas Alex e Beto viraram respectivamente: \n");
      scanf("%d %d", &alex, &beto);

      alex > beto ? printf("Alex ganhou\n") : alex == beto ? printf("Empatou\n") : printf("Beto ganhou\n");

    }

    printf("Querem jogar outra partida? (S, N)\n");
    scanf(" %c", &resposta);

  }while(resposta == 'S');

}
