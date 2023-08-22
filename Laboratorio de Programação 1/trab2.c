#include <stdio.h>

int main(){

  float minimumSalary, salary, coeficient, tax, gratification = 30.0, food = 0;
  char period, category;
  int hours, classification;

  printf("Qual o valor do salário mínimo?\n");
  scanf("%f", &minimumSalary);

  printf("Qual o turno de trabalho? (N - noite, T - tarde, M - manhã))\n");
  scanf(" %c", &period);

  printf("Qual a categoria? (O - operário, G - gerente))");
  scanf(" %c", &category);

  printf("Quantas horas trabalhadas por mês?\n");
  scanf("%d", &hours);

  switch (period) {
    case 'M':
      coeficient = 0.01 * minimumSalary;
      break;
    case 'T':
      coeficient = 0.015 * minimumSalary;
      break;
    case 'N':
      coeficient = 0.012 * minimumSalary;
      gratification = hours > 80 ? 80.0 : 30.0;
      break;
  }

  salary = coeficient * hours;

  switch (category) {
    case 'O':
      tax = salary < 300 ? 0.03 * salary : 0.05 * salary;
      food = coeficient <= 25.0 ? salary / 3 : salary / 2;
      break;
    case 'G':
      tax = salary < 400 ? 0.04 * salary : 0.06 * salary;
      break;
  }

  float netSalary = salary - tax + gratification + food;

  if(netSalary < 350.0){
    classification = 0;
  }else if(netSalary <= 600.0){
    classification = 1;
  }else{
    classification = 2;
  }

  printf("O coeficiente do salário é: %.2f\n", coeficient);
  printf("O valor do salário bruto é: %.2f\n", salary);
  printf("O imposto é: %.2f\n", tax);
  printf("A gratificação é: %.2f\n", gratification);
  printf("O auxílio alimentação é: %.2f\n", food);
  printf("O salário líquido é: %.2f\n", netSalary);
  printf("A classificação é: ");

  switch (classification) {
    case 0:
      printf("Mal Remunerado\n");
      break;
    case 1:
      printf("Normal\n");
      break;
    case 2:
      printf("Bem remunerado\n");
      break;
  }

  return 0;
}
