#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char* argv[]){

	std::ifstream input(argv[1]);
	
	int size;
	input >> size;

	char** matrix{nullptr};
	matrix = new char*[size];

	for(auto i = 0; i < size; i++){
		matrix[i] = new char[size];
	}

	for(auto i = 0; i < size; i++){
		for(auto j = 0; j < size; j++){
			input >> matrix[i][j];
		}
	}

	int** values{nullptr};
	values = new int*[size];

	for(auto i = 0; i < size; i++){
		values[i] = new int[size];
	}

	for(auto i = 0; i < size; i++){
		for(auto j = 0; j < size; j++){
			values[i][j] = 0;
		}
	}
	
	for(auto i = 0; i < size; i++){
		for(auto j = 0; j < size; j++){

			if(matrix[i][j] == '*'){

				for(auto k = 0; k < size; k++){
					for(auto l = 0; l < size; l++){

						if(abs(i - k) <= 1 && abs(j - l) <= 1 && !(i == k && j == l) ){
							values[k][l]++;
						}

					}
				}

			}

		}
	}

	for(auto i = 0; i < size; i++){
		for(auto j = 0; j < size; j++){

			if(matrix[i][j] == '*'){
				std::cout << '*';
			}else{
				std::cout << values[i][j];
			}

		}
		std::cout << std::endl;

	}

	for(auto i = 0; i < size; i++){
	    delete[] matrix[i];
	    delete[] values[i];
	}

	delete[] matrix;
	delete[] values;

	return 0;
}