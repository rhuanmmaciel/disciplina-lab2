#include <stdio.h>

void barra();
void kibonacci();
void primok();

int main(){

  int choice;

  printf("Escolha a função desejada digitando 1, 2 ou 3:\n");
  printf("1) Barra de chocolate\n");
  printf("2) Kibonacci\n");
  printf("3) Primok\n");

  scanf("%d", &choice);

  switch (choice) {
    case 1:
      barra();
      break;
    case 2:
      kibonacci();
      break;
    case 3:
      primok();
      break;
  }

  return 0;
}

void barra(){

  int divisions, amountOfPieces;
  int numberOfPieces = 0;
  printf("Quantas divisões serão feitas?\n");
  scanf("%d", &divisions);

  for(int i = 0; i < divisions; i++){

    printf("Digite o valor da %d divisão:\n", i + 1);
    scanf("%d", &amountOfPieces);
    numberOfPieces += amountOfPieces;
    numberOfPieces--;

  }


  printf("O número de pedaços que serão guardados é: %d\n", numberOfPieces);

}

void kibonacci(){

  int k, n, sum = 0;

  printf("Digite o valor de k: \n");
  scanf("%d", &k);

  printf("Digite o valor de n: (n > k)\n");
  scanf("%d", &n);

  for(int i = 0; i < n; i++){

    if(i < k){

      printf("1 ");
      sum++;

    }else{

      printf("%d ", sum);

      sum = sum * 2 - 1;

    }

  }

}

void primok(){

  int prime, primePlus2;
  for(int i = 2; i <= 251; i++){

    prime = 1;
    for(int j = 2; j < i; j++){

      if(i % j == 0 && j != i){
        prime = 0;
      }

    }

    primePlus2 = 1;
    if(prime == 1){

      for(int j = 2; j <= i; j++){

        if((i + 2) % j == 0 && j != (i + 2)){
          primePlus2 = 0;
        }

      }
    }

    if(prime == 1 && primePlus2 == 1){
      printf("(%d, %d)\n", i, i + 2);
    }
  }

}
