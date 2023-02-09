#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rollDices();
int points();
int roundMatch();
void printDices();

int main() {

	time_t t;
	srand((unsigned) time(&t));

	int noWin = 1, playerPoints = 0, computerPoints = 0,
			playerPointsMinimum = 0, computerPointsMinimum = 0, roundPoints,
			computerTurn = 1;

	char difficulty;

	do {

		printf("Escolha a dificuldade digitando 1 ou 2:\n\n");
		printf("1)Nível básico\n");
		printf("2)Nível avançado\n");
		scanf(" %c", &difficulty);

	} while (difficulty != '1' && difficulty != '2');

	while (noWin) {

		roundPoints =
				computerTurn ?
						roundMatch(computerPointsMinimum, playerPoints,
								computerPoints, computerTurn, difficulty) :
						roundMatch(playerPointsMinimum, playerPoints,
								computerPoints, computerTurn, difficulty);

		computerTurn ? (computerPoints += computerPoints + roundPoints <= 5000 ? roundPoints : 0)
     : (playerPoints += playerPoints + roundPoints <= 5000 ? roundPoints : 0);

		if (roundPoints == 5000)
			if (computerTurn)
				computerPoints = 5000;
			else
				playerPoints = 5000;

		if (computerPoints != 0)
			computerPointsMinimum = 1;
		if (playerPoints != 0)
			playerPointsMinimum = 1;

		if (roundPoints)
			printf("\n\nPASSOU A VEZ\n\n\n\n");
		else
			printf("\n\nPERDEU A VEZ\n\n\n\n");

		for (int i = 0; i < 2000000000; i++) {
		}

		computerTurn = !computerTurn;

		if (playerPoints == 5000 || computerPoints == 5000)
			noWin = 0;

	}

	playerPoints == 5000 ?
			printf("\n\nVOCÊ VENCEU!!!\n\n") :
			printf("\n\nO COMPUTADOR VENCEU!!!\\n\n");

	return 0;
}

int rollDices(int dices[2][5]) {

	for (int i = 0; i < 5; i++) {

		if (dices[0][i] == 1)
			dices[1][i] = rand() % 6 + 1;

	}

	return dices[2][5];

}

void printDices(int dices[2][5], int playerPoints, int computerPoints,
		int computerTurn, int separatePoints) {

	printf("--------------------------------------\n");
	printf("                PLAYER X COMPUTADOR\n");
	printf("PONTUAÇÃO TOTAL: %04d  |  %04d\n\n", playerPoints, computerPoints);

	if (computerTurn)
		printf("*COMPUTADOR LANÇA OS DADOS*\n");
	else
		printf("*VOCÊ LANÇA OS DADOS*\n");

	printf("\nDados sorteados: | Dados separados: \n");

	for (int i = 0; i < 5; i++) {

		if (dices[0][i] == 1)
			printf("(%d) %d            | \n", i + 1, dices[1][i]);
		else
			printf("                 | (%d) %d \n", i + 1, dices[1][i]);

	}

	printf("Pontuação: %d   | Pontos separados: %d\n\n", points(dices),
			separatePoints);

}

int points(int dices[2][5]) {

	int valueOfDices[6] = { 0, 0, 0, 0, 0, 0 }, pointsRules[9], sum = 0,
			sequence = 0;

	for (int i = 0; i < 5; i++)
		if (dices[0][i] == 1)
			valueOfDices[dices[1][i] - 1]++;

	for (int i = 0; i < 2; i++)
		if (valueOfDices[0 + i] == 1 && valueOfDices[1 + i] == 1
				&& valueOfDices[2 + i] == 1 && valueOfDices[3 + i] == 1
				&& valueOfDices[4 + i] == 1)
			sequence = 1;

	pointsRules[0] = valueOfDices[4] > 0 ? valueOfDices[4] * 50 : 0;
	pointsRules[1] = valueOfDices[0] > 0 ? valueOfDices[0] * 100 : 0;
	pointsRules[2] = sequence ? 500 : 0;
	pointsRules[3] =
			valueOfDices[0] >= 3 ?
					valueOfDices[0] >= 4 ?
							valueOfDices[0] == 5 ? 5000 : 2000 : 1000
					: 0;

	for (int i = 0; i < 5; i++) {
		pointsRules[4 + i] =
				valueOfDices[1 + i] >= 3 ?
						valueOfDices[1 + i] >= 4 ?
								valueOfDices[1 + i] == 5 ?
										400 * (i + 2) : 200 * (i + 2)
								: 100 * (i + 2)
						: 0;
	}

	for (int i = 0; i < 9; i++)
		sum += pointsRules[i];

	if (sequence)
		return pointsRules[2];
	if (valueOfDices[0] < 3 && valueOfDices[4] < 3)
		return sum;
	if (valueOfDices[0] >= 3)
		return sum - pointsRules[1];
	if (valueOfDices[4] >= 3)
		return sum - pointsRules[0];

}

int roundMatch(int pointsMinimum, int playerPoints, int computerPoints,
		int computerTurn, int difficulty) {

	int dices[2][5] = { 1, 1, 1, 1, 1 }, reverseDices[2][5] = { 0, 0, 0, 0, 0 },
			reverseDicesValue, wrongDice, noWin = 1, allDices, separatePoints = 0,
      currentPoints, separateDicesQuantity, separateDices[5],
			firstPlay = 1, alreadySeparate, found, playerCondition = 0,
			computerCondition1 = 0, computerCondition2 = 0, computerCondition3 = 0;

	char stop = 'N', go;

	do {

		if (stop != 'S' || computerTurn || firstPlay) {

			printf("Digite qualquer caracter para lançar os ");
			computerTurn ?
					printf(" dados do computador:") : printf("seus dados:\n");
			scanf(" %c", &go);
			dices[2][5] = rollDices(dices);

		}

		for (int i = 0; i < 5; i++)
			reverseDices[1][i] = dices[1][i];

		currentPoints = points(dices);

		if (stop != 'S' || computerTurn || firstPlay)
			printDices(dices, playerPoints, computerPoints, computerTurn,
					separatePoints);

		if (currentPoints == 0 && (stop != 'S' || computerTurn))
			return 0;

		else if (currentPoints == 5000)
			return 5000;

		else if (((!pointsMinimum || stop == 'N' || firstPlay) && !computerTurn)
				|| ((!pointsMinimum || firstPlay) && computerTurn)) {

			if (!computerTurn) {

				do {

					wrongDice = 0;
					alreadySeparate = 0;
					found = 0;
					for (int i = 0; i < 5; i++)
						reverseDices[0][i] = 0;

					printf(
							"Quantos dados que pontuaram você gostaria de retirar?\n");
					scanf("%d", &separateDicesQuantity);

					printf("Quais dados? (1 a 5)\n");
					for (int i = 0; i < separateDicesQuantity; i++)
						scanf("%d", &separateDices[i]);

					for (int i = 0; i < separateDicesQuantity; i++) {

						if (dices[0][separateDices[i] - 1] == 1) {

							dices[0][separateDices[i] - 1] = 0;
							reverseDices[0][separateDices[i] - 1] = 1;

						} else
							alreadySeparate = 1;

					}

					reverseDicesValue = points(reverseDices);

					for (int i = 0; i < separateDicesQuantity; i++) {

						reverseDices[0][separateDices[i] - 1] = 0;
						if (wrongDice == 0)
							wrongDice =
									reverseDicesValue == points(reverseDices) ?
											1 : 0;
						reverseDices[0][separateDices[i] - 1] = 1;

					}

					if (points(dices) == currentPoints || wrongDice) {

						printf(
								"Você não pode retirar esse(s) dado(s), por favor digite novamente:\n");
						for (int i = 0; i < separateDicesQuantity; i++)
							if (!alreadySeparate)
								dices[0][separateDices[i] - 1] = 1;

					} else
						separatePoints += points(reverseDices);

				} while (points(dices) == currentPoints || wrongDice);

			}else if (difficulty == '1') {

				for (int i = 0; i < 5; i++){
          separateDices[i] = 0;
					reverseDices[0][i] = 0;
        }

        separateDicesQuantity = 0;
				int j = 0;
				for (int i = 0; i < 5; i++) {

					if (dices[0][i] == 1) {

						dices[0][i] = 0;
						if (points(dices) != currentPoints) {
							separateDices[j] = i + 1;
							separateDicesQuantity++;
							j++;
						}
						dices[0][i] = 1;

					}

				}

				for (int i = 0; i < separateDicesQuantity; i++) {

					dices[0][separateDices[i] - 1] = 0;
					reverseDices[0][separateDices[i] - 1] = 1;

				}

				separatePoints += points(reverseDices);

			}else{

        for (int i = 0; i < 5; i++){
          separateDices[i] = 0;
					reverseDices[0][i] = 0;
        }

        separateDicesQuantity = 0;
				int j = 0;
				for (int i = 0; i < 5; i++) {

					if (dices[0][i] == 1) {

						dices[0][i] = 0;
						if (points(dices) != currentPoints) {
							separateDices[j] = i + 1;
							separateDicesQuantity++;
							j++;
						}
						dices[0][i] = 1;

					}

				}

				for (int i = 0; i < separateDicesQuantity; i++) {

          if(dices[0][separateDices[i] - 1] != 5){
					   dices[0][separateDices[i] - 1] = 0;
					   reverseDices[0][separateDices[i] - 1] = 1;
           }

				}

				separatePoints += points(reverseDices);

			}

		}

		allDices = 0;
		for (int i = 0; i < 5; i++)
			if (dices[0][i] == 0)
				allDices++;

		if (allDices >= 5)
			for (int i = 0; i < 5; i++)
				dices[0][i] = 1;

    if (separatePoints >= 600 && pointsMinimum == 0)
    			pointsMinimum = 1;

    if (pointsMinimum && separatePoints != 0 && !computerTurn) {

			do {

				printf(
						"Você deseja parar e guardar os %d pontos ou não?(S/N)\n",
						separatePoints);
				scanf(" %c", &stop);

			} while (stop != 'S' && stop != 'N');

		}

		firstPlay = 0;

		if (!computerTurn)
			playerCondition = (stop == 'N' || !pointsMinimum) ? 1 : 0;
		else {

			computerCondition1 = playerPoints > computerPoints + separatePoints ? 1 : 0;
			computerCondition2 = computerPoints > playerPoints && separatePoints < 250 ? 1 : 0;
			computerCondition3 = !pointsMinimum && separatePoints < 600 ? 1 : 0;

		}

	} while (playerCondition || computerCondition1 || computerCondition2
			|| computerCondition3);

	return separatePoints;

}
