#include <iostream>
#include <list>
#include <sstream>
#include <string>

struct data{

	double money;
	double quota;
	int year;

};

struct output{

	double money;
	double incomeTax;

};

double getAliquot(int rescueYear, int contributionYear){
	
	int difference = rescueYear - contributionYear;

	switch(difference){

		case 0: case 1: return 0.35;

		case 2: case 3: return 0.3;

		case 4: case 5: return 0.25;

		case 6: case 7: return 0.2;

		case 8: case 9: return 0.15;

		default: return 0.1;

	}

}

int main(){

	std::list<data> contributions;
	std::list<data> rescues;
	std::list<output> outputs;

	char operationType;

	do{

		std::cin >> operationType;

		if(operationType == 'A' || operationType == 'R'){
			
			data contributionOrRescue;

			std::cin >> contributionOrRescue.money; 
			std::cin >> contributionOrRescue.quota;
			std::cin >> contributionOrRescue.year; 

			operationType == 'A' ? contributions.push_back(contributionOrRescue) : rescues.push_back(contributionOrRescue);

		}

		if(!rescues.empty()){

			bool rescueAll = rescues.front().money < 0;

			output withdrawl;
			withdrawl.money = 0;
			withdrawl.incomeTax = 0;

			bool done = false;

			while(!done || (rescueAll && !contributions.empty())){

				if(!rescueAll){

					if(rescues.front().money <= contributions.front().money * (rescues.front().quota / contributions.front().quota)){

						withdrawl.money += rescues.front().money;
						withdrawl.incomeTax += (rescues.front().money - rescues.front().money / (rescues.front().quota / contributions.front().quota)) * getAliquot(rescues.front().year, contributions.front().year);

						if(rescues.front().money == contributions.front().money * (rescues.front().quota / contributions.front().quota)){
						
							contributions.pop_front();
						
						}else{

							contributions.front().money -= rescues.front().money / (rescues.front().quota / contributions.front().quota);
						
						}	

						rescues.pop_front();

					}else{

						withdrawl.money += contributions.front().money * (rescues.front().quota / contributions.front().quota);
						rescues.front().money -= contributions.front().money * (rescues.front().quota / contributions.front().quota);

						withdrawl.incomeTax += (contributions.front().money * (rescues.front().quota / contributions.front().quota) - contributions.front().money) * getAliquot(rescues.front().year, contributions.front().year);

						contributions.pop_front();

					}

				}else{

					withdrawl.money += contributions.front().money * (rescues.front().quota / contributions.front().quota);

					withdrawl.incomeTax += (contributions.front().money * (rescues.front().quota / contributions.front().quota) - contributions.front().money) * getAliquot(rescues.front().year, contributions.front().year);

					contributions.pop_front();

				}

				done = rescues.empty() || contributions.empty();

			}

			outputs.push_back(withdrawl);

		}

	}while(!contributions.empty());

	for(output i : outputs){

		std::string tax;
		std::string money;

   		std::stringstream sstream;
   		std::stringstream sstream2;

		sstream2.setf(std::ios::fixed);
    	sstream.setf(std::ios::fixed);

    	sstream2.precision(2);
    	sstream.precision(2);
    	
    	sstream << i.money;
    	sstream2 << i.incomeTax;

    	tax = sstream2.str();
    	money = sstream.str();
    
		std::cout << money << " " << tax << std::endl; 
	}

	return 0;
	
}