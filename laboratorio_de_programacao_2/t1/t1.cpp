#include <iostream>
#include <fstream>

int main(void){

	int** matrix {nullptr};

	int size = 4, sides = 3;
	std::string classification[size];

	matrix = new int*[size]; 

	for(auto i = 0; i < size; i++){
		matrix[i] = new int[sides];
	}

	std::ifstream input{"lados.txt"};

	for(auto i = 0; i < size; i++){
		for(auto j = 0; j < sides; j++)
			input >> matrix[i][j];
	}

	for(auto i = 0; i < size; i++){
    	classification[i] = !(matrix[i][0] + matrix[i][1] > matrix[i][2]
							&& matrix[i][0] + matrix[i][2] > matrix[i][1]
    						&& matrix[i][1] + matrix[i][2] > matrix[i][0])
    						? "invalido" : matrix[i][0] == matrix[i][1] 
    									   	&& matrix[i][0] == matrix[i][2]
    									   	? "equilatero" : matrix[i][0] == matrix[i][1]
    									   					|| matrix[i][0] == matrix[i][2]
    									   					? "isosceles" : "escaleno"; 	
	}


	for(auto i = 0; i < size; i++){
		std::cout << classification[i] << std::endl;    									   					
	}

	for(auto i = 0; i < size; i++){
		delete[] matrix[i];
	}
	delete[] matrix;

	return 0;

}