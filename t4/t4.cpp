#include <stack>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
#include<bits/stdc++.h>
#include <string>
#include <string.h>

using namespace std;

struct Cell {
  
  string equation;
  int content;

};

template<typename T>
int solveEquation(stack<T> &operandos, stack<char> &operadores);
int whichOperation(int firstNumber, int secondNumber, char operation);
int numberOfDigits(string st);
void stacker(stack<char> &operations, stack<int> &numbers, string st);
bool comparator(string a, string b);

template<typename T>
struct Calculadora {

    stack<T> operandos;    
    stack<char> operadores; 
    
    void cria(void){

    }

    void destroi(void){
        while(operandos.empty() == false) operandos.pop();
        while(operadores.empty() == false) operadores.pop();
    }

    void operando(T op) {
        operandos.push(op);
    }

    void operador(char op){
        operadores.push(op);
    }

    void formula(string form, map<string, Cell> &cells){

        if(!form.empty()){
            if(form[0] == '='){

                form.erase(0, 1);
                stacker(operadores, operandos, form, cells);

            }else{

                operando(stoi(form));
                
            }
        }

    }

    bool fim() {
        if(operandos.empty()){

            return false;

        }
        if(operandos.size() != 1) operandos.push(solveEquation(operandos, operadores));

        return true;
    }

    T resultado(void) {
        if(operandos.empty())
            return static_cast<T>(0);

        return operandos.top();
    }
};

int main(int argc, char* argv[]){

    list<string> lines;
    string line;

    while(getline(cin, line)){

        lines.push_back(line);

    }

    Calculadora<int> calculator;
    calculator.cria();

    map<string, Cell> cells;
    vector<string> ids;

    while(!lines.empty()){
        
        string cellId{""};
        
        int i{0};

        while(lines.front()[i] != ' '){
            cellId += lines.front()[i];
            i++;
        }

        lines.front().erase(0, i + 1);

        cells[cellId] = Cell();
        cells[cellId].equation = lines.front();
        cells[cellId].content = 0;   

        ids.push_back(cellId);

        lines.pop_front();
    
    }

    for(auto i = 0; i < (int)ids.size(); i++){

        calculator.formula(cells[ids[i]].equation, cells);  

        cells[ids[i]].content = cells[ids[i]].equation.empty() ? 0 : calculator.resultado();
        
        while(calculator.fim()){

            if(calculator.operandos.size() == 1){
                cells[ids[i]].content = calculator.operandos.top();
                calculator.operandos.pop();
            }

        }     
        
        calculator.destroi();

    }

    sort(ids.begin(), ids.end(), comparator);

    for(auto i = 0; i < (int) ids.size(); i++){

        if(!cells[ids[i]].equation.empty()){

            cout << ids[i] << " " << cells[ids[i]].content << endl;   
        
        }

    }

    return 0;
}

int whichOperation(int firstNumber, int secondNumber, char operation){

    if(operation == '+'){
        return firstNumber + secondNumber;
    }else if(operation == '-'){
        return firstNumber - secondNumber;
    }else if(operation == '*'){
        return firstNumber * secondNumber;
    }else if(operation == '/'){
        return round((float)firstNumber / (float)secondNumber);
    }
    return 0;

}

int numberOfDigits(string st){

    int amount = 1;
    for(int i = 1; i < (int)st.size(); i++){

        if(isdigit(st[i])) amount++;
        else return amount;

    }
    return amount;

}

void error(){

        cout << "ERRO DE ENTRADA" << endl;
        exit(EXIT_FAILURE);

}

void changeCellToItValue(string* st, map<string, Cell> &cells){

    while((*st)[1] == ' ') {
    
        (*st).erase(1, 1);
    
    }

    if(!isdigit((*st)[1])){

        error();

    }

    while((*st)[2] == ' ') {
    
        (*st).erase(2, 1);
    
    }

    string content;
    if(isdigit((*st)[2])){

        content = to_string(cells[(*st).substr(0, 3)].content);
        (*st).erase(0, 3);

    }else{

        content = to_string(cells[(*st).substr(0, 2)].content);
        (*st).erase(0, 2);

    }

    (*st).insert(0, content);

}

void stacker(stack<char> &operations, stack<int> &numbers, string st, map<string, Cell> &cells){

    while(!st.empty()){

        if(st[0] == ' '){

            st.erase(0, 1);

        }else if(st[0] == '+' || st[0] == '-' || st[0] == '*' || st[0] == '/' || st[0] == '(' || st[0] == ')'){

            operations.push(st[0]);
            st.erase(0, 1);
        
        }else if(st[0] == '-' && numbers.empty()){ 

            st[1] == ' ' ? st.erase(1, 1) : st.erase(0, 0);  
            numbers.push(stoi(st.substr(0, 2)));
            st.erase(0, 2);
            
        }else if(isdigit(st[0])){

            int size = numberOfDigits(st);

            if(!operations.empty()){

                if(operations.top() == '-'){

                    operations.pop();
                    operations.push('+');
                    numbers.push(-stoi(st.substr(0, size)));

                }else{

                    numbers.push(stoi(st.substr(0, size)));

                }

            }else{

                numbers.push(stoi(st.substr(0, size)));

            }            

            st.erase(0, size);

        }else if(isalpha(st[0])){

            changeCellToItValue(&st, cells);

        }else{

            error();

        }

    }

}

bool comparator(string a,string b){

    return a<b;

}

template<typename T>
int solveEquation(stack<T> &operandos, stack<char> &operadores){

    int lastNumber;
    char operation;

    do{
        
        operation = operadores.top();
        operadores.pop();

        if(operation == '('){

            operation = operadores.top();
            operadores.pop();
        
        }

    }while(operation == '(');

    if(operation == ')'){

        operation = operadores.top();
        operadores.pop();

        if(operation == ')'){

            return solveEquation(operandos, operadores);

        }

        lastNumber = operandos.top();
        operandos.pop();
        int secondNumber;

        if(operadores.top() == '('){

            operadores.pop();

            secondNumber = operandos.top();
            operandos.pop();

            lastNumber = whichOperation(secondNumber, lastNumber, operation);

            operation = operadores.top();
            operadores.pop();

        }

        if(operadores.empty() || operadores.top() == '+' || operadores.top() == '-'){

            secondNumber = operandos.top();
            operandos.pop();

            return whichOperation(secondNumber, lastNumber, operation);
        }

        return whichOperation(solveEquation(operandos, operadores), lastNumber, operation);

    }

    lastNumber = operandos.top();
    operandos.pop();

    if(operadores.empty() || operadores.top() == '+' || operadores.top() == '-' || operadores.top() == '('){

        int secondNumber = operandos.top();
        operandos.pop();

        return whichOperation(secondNumber, lastNumber, operation);

    }

    return whichOperation(solveEquation(operandos, operadores), lastNumber, operation);

}