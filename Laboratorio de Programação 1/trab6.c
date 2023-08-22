#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool compara(char str_1[], char str_2[]){

	bool igual = true;

	for(int i = 0; i < strlen(str_1); i++)
		if(str_1[i] != '\0')
			igual = str_1[i] != str_2[i] ? false : igual ;  

	return igual;	
}

void levenshtein(char str_orig[], char str_busca[]){

	char str_operacional[30];	

	strcpy(str_operacional, str_busca);

	int i = 0, correto = 0, adicao = 0, substituicao = 0, remocao = 0;
	int tamanho = strlen(str_busca);

	bool tem, encontrado = false;

	while(!encontrado){

		tem = false;
		tamanho = strlen(str_operacional) > strlen(str_orig) ? strlen(str_operacional) : strlen(str_orig);

		if(str_operacional[i] != str_orig[i]){

			for(int j = i + 1; j <= tamanho; j++)
				tem = str_orig[j] == str_operacional[i] ? true : tem;

			if(!tem){

				if(compara(str_orig, str_operacional)){

					printf(">>Remoção de %c\n", str_operacional[i]);
					str_operacional[i] = ' ';
					remocao++;

				}else{

					printf(">>Substituição de %c por %c\n", str_operacional[i], str_orig[i]);
					str_operacional[i] = str_orig[i];
					substituicao++;

				}

			}else{

				printf(">>Adição de %c\n", str_orig[i]);

				char str_copiada[strlen(str_operacional) - 1];

				for(int j = 0; j <= strlen(str_copiada); j++)
					str_copiada[j] = str_operacional[j + i];

				str_operacional[i] = str_orig[i];
				strncpy(str_operacional, str_operacional, i + 1);
				str_operacional[i + 1] = '\0';
				strcat(str_operacional, str_copiada);

				adicao++;

			}

		}else{

			correto++;
			printf("Posição correta: %d, caractere: %c, corretos: %d\n", i, str_operacional[i], correto);

		}
		i++;
		encontrado = compara(str_orig, str_operacional) && str_operacional[i] == '\0' ? true : false;

	}

	printf("\n");
	puts(str_operacional);

	printf("\n-->> %d corretos", correto);
	printf("\n-->> %d adição", adicao);
	printf("\n-->> %d remoção", remocao);
	printf("\n-->> %d substituição", substituicao);

	int operacoes = adicao + substituicao + remocao;
	float similaridade = 1 - (float)operacoes / (operacoes + correto);

	printf("\n\n-->> SIMILARIDADE = %.3f%%\n", similaridade * 100);

}

int main(){

	char str_orig[100];
	char str_busca[100];

	printf("Digite a string original: \n");
	scanf("%s", str_orig);

	printf("Digite a string de busca: \n");
	scanf("%s", str_busca);

	levenshtein(str_orig, str_busca);

	return 0;
}