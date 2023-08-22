#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 8
#define AMOUNT_OF_QUEENS 8

int amount = 0;
bool must_ask_user = true;

struct Point{

    int row;
    int column;

};

struct Result{

    struct Point initial_point;
    int size_control;
    struct Point points[AMOUNT_OF_QUEENS];

};

bool same_row(struct Point p1, struct Point p2){
    return p1.row == p2.row;
}

bool same_column(struct Point p1, struct Point p2){
    return p1.column == p2.column;
}

bool same_diagonal(struct Point p1, struct Point p2){
    return abs(p1.row - p2.row) == abs(p1.column - p2.column);
}

bool are_conflict_points(struct Point p1, struct Point p2){
    return same_row(p1, p2) || same_column(p1, p2) || same_diagonal(p1, p2); 
}

bool has_conflict_point_result(struct Result result, struct Point p){

    for(int i = 0; i < result.size_control; i++)
        if(are_conflict_points(p, result.points[i])) return true;

    return false;

}

bool equals(struct Point p1, struct Point p2){
    return same_row(p1, p2) && same_column(p1, p2);
}

bool has_point(struct Result result, struct Point p){

    for(int i = 0; i < result.size_control; i++)
        if(equals(p, result.points[i])) return true;

    return false;

}

void print_result(struct Result result){


    for(int row = 0; row < BOARD_SIZE; row++){

        for(int column = 0; column < BOARD_SIZE; column++){

            struct Point p;

            p.row = row;
            p.column = column;

            printf(has_point(result, p) ? "X " : "- ");

        }

        printf("\n");

    }

    printf("\n");

}

void ask_user(){

    printf("\n\nDigite 0 para ver a próxima solução\nDigite qualquer outra coisa para calcular todas\n");
    int i;
    scanf(" %d", &i);
    printf("\n");
    must_ask_user = i == 0;

}

void calculate(struct Result result, int row){

    if(result.size_control == AMOUNT_OF_QUEENS){

        amount++;
        printf("SOLUÇÃO %d:\n", amount);
        print_result(result);

        if(must_ask_user)
            ask_user();

        return;

    }

    if(row == BOARD_SIZE) return;

    for(int column = 0; column < BOARD_SIZE; column++){

        struct Point p;
        p.row = row;
        p.column = column;

        if(has_conflict_point_result(result, p)) continue;

        result.points[result.size_control] = p;
        result.size_control++;
        calculate(result, row + 1);
        result.size_control--;

    }

}

int main() {

    struct Result result;

    result.size_control = 0;

    calculate(result, 0);

    printf("Quantidade de soluções: %d\n", amount);
    
}   
