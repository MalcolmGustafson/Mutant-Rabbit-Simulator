/* Rabbit breeding simulator with mutants
// Currently starts with 5 random rabbits, if there is a M and any number of F rabbits 2 years or older they make another random rabbit
// each new rabbit has a 2% chance to spawn a mutant rabbit. Mutants infect a new rabbit each tick
// normal rabbits die after 10 years. Mutants 50 years
//
// Things that are being added.
// -adding header file for better code readability
// -A "field" for the rabbits to more and interact in
// -new rabbits have the same fur color as their mother
// -timed turns so user input no longer needed
// -Custom start variables to customize how the scenario plays out (ie. number starting rabbits, mutant %chance, multiple rabbits per birth, etc...)
// -More rabbit names and make the string a set length for better output formatting instead of adding spaces into the names

// Potential bugs
// -Array of rabbits has max size 1000 with no error handing if there is more rabbits. Will add in a rabbit culling that kills half the rabbits in case this occures in the rare case
*/

#include <iostream>
using namespace std;
#include <ctime>


struct Bunny {
	bool sex; // 0 is male, 1 is female
	string color; // white, brown, black, spotted
	int age;
	string name;
	bool mutant; // 0 is normal, 1 is mutant
};

void MakeRabbit (Bunny *, int &count);
void PrintColony (Bunny *, int count);
void AgingBunny (Bunny *, int count);
void OldAgeSorter (Bunny *, int &count);
void BreedingRabbits (Bunny *, int &count);
bool MutantCorruption (Bunny *, int count);

int main () {
	int rabbitCount=0;
	Bunny rabbit[1000];
	int wait;
	bool stillNormal=true;

	srand ( time(0)); //Much needed randomization or else the simulation plays the same way every time

	for(int initRabbit=0; initRabbit<5; initRabbit++) {
		MakeRabbit(rabbit, rabbitCount);
		rabbit[initRabbit].mutant=false; //keeps mutants from initial spawn	
	}
	
	PrintColony(rabbit, rabbitCount);

	while(rabbitCount>1 && stillNormal) {
		cin >> wait;
		AgingBunny(rabbit, rabbitCount);
		OldAgeSorter(rabbit, rabbitCount);
		stillNormal = MutantCorruption(rabbit, rabbitCount);
		BreedingRabbits(rabbit, rabbitCount);	
		PrintColony(rabbit, rabbitCount);
	}
	
	if (stillNormal==false) {
		cout << "\nAll the rabbits have been corrupted!\n";
	}
	else {
		cout << "\nAll the rabbits have died!\n";
	}
	cout << "Normal Program Exit!\n";

	return 0;
}

//Ages all the rabbits in the colony
void AgingBunny (Bunny *rabbit, int count) {
	for(int aging=0; aging<count; aging++) {
		rabbit[aging].age++;
	}
}

//Takes the array of rabbits and "kills" off the old rabbits and overwrites the rabbit with a living one if present
void OldAgeSorter (Bunny *rabbit, int &count) {
	int rabbitMover;

	for(int current=0; current<=count; current++) {
		if(rabbit[current].age>=10) {
			//mutant check here to see if they are over 50
			if(rabbit[current].mutant==true && rabbit[current].age>=50) {
				if(current+1<=count) {
					for(rabbitMover=current;rabbitMover<=count; rabbitMover++) {
						rabbit[rabbitMover]=rabbit[rabbitMover+1];
					}
					rabbit[count+1].sex=0;
					rabbit[count+1].age=0;
					rabbit[count+1].name="Dead";
					rabbit[count+1].mutant=0;
					count--;
					current--;
				}
				else {
					rabbit[current].sex=0;
					rabbit[current].age=0;
					rabbit[current].name="Dead";
					rabbit[current].mutant=0;
					count--;
				}
			}
			else if (rabbit[current].mutant==false) { //verified non mutant and age>=2
				if(current+1<=count) {
					for(rabbitMover=current;rabbitMover<=count; rabbitMover++) {
						rabbit[rabbitMover]=rabbit[rabbitMover+1];
					}
					rabbit[count+1].sex=0;
					rabbit[count+1].age=0;
					rabbit[count+1].name="Dead";
					rabbit[count+1].mutant=0;
					count--;
					current--;
				}
				else {
					rabbit[current].sex=0;
					rabbit[current].age=0;
					rabbit[current].name="Dead";
					rabbit[current].mutant=0;
					count--;
				}
			}
		}
	}
}

//breeds the rabbits if elegible
void BreedingRabbits(Bunny *rabbit, int &count) {
	bool isMale = false;
	int numFemale = 0;
	int rabbitRunner;
	int breeder;

	//Checks for all the conditions needed to make a new rabbit
	for (rabbitRunner=0; rabbitRunner<count; rabbitRunner++) {
		if (rabbit[rabbitRunner].age>=2) {
			if (rabbit[rabbitRunner].mutant==0) {
				if (rabbit[rabbitRunner].sex==0) {
					isMale = true;
				}
				else {
					numFemale++;
				}
			}
		}
	}

	if(isMale && numFemale>0) {
		for(breeder=0; breeder<numFemale; breeder++) {
			MakeRabbit(rabbit, count);
		}
	}
}

//Corrupts a nuymber of bunnies based on number of mutants present
bool MutantCorruption (Bunny *rabbit, int count) {
	int mutantCount=0;
	int rabbitRunner;
	int mutantTest=0;
	int leftToMutate;

	for (rabbitRunner=0; rabbitRunner<count; rabbitRunner++) {
		if(rabbit[rabbitRunner].mutant==1) {
			mutantCount++;
		}
	} 

	leftToMutate = count-mutantCount;
	//Time to corrupt the normal rabbits
	while (mutantCount>=1 && leftToMutate!=0) {
		mutantTest=rand() % count;
		if(rabbit[mutantTest].mutant==0) {
			rabbit[mutantTest].mutant=true;
			mutantCount--;
			leftToMutate--;
		}
		if (leftToMutate==0) {
			return false;
		}
	}
	cout << endl;
	return true;
}

//Function to print off the entire colony of rabbits and some stats at the end
void PrintColony (Bunny *rabbit, int count) {
	int male=0;
	int female=0;
	int mutant=0;
	for(int output=0; output<count; output++) {
		cout << "Sex: ";
		if (rabbit[output].sex==0) {
			cout << "M";
			male++;
		}
		else {
			cout << "F";
			female++;
		}
		cout << " Color: " << rabbit[output].color << " Age: " << rabbit[output].age 
		<< " Name: " << rabbit[output].name << " Mutant: ";
		if(rabbit[output].mutant==0) {
			cout << "N\n";
		}
		else {
			cout << "Yes\n";
			mutant++;
		}		
	}
	cout << "\nStats: \n";
	cout << "Males: " << male << " Females: " << female << endl;
	cout << "Normal: " << count-mutant << " Mutants: " << mutant << endl;

}

//Function to initialize the starting 5 rabbits in the colony
void MakeRabbit (Bunny *init, int &count) {
	int intColor;
	int percentMutant;

	string nameLibrary[10] = {"Ace  ", "Alfie", "Babe ", "Bell ", "Billy", "Chaz ", "Chino", "Flo  ", "Foxy ", "Leo  "}; 
	init[count].sex= rand() % 2;
	intColor = rand() % 4;
	if (intColor == 0) {
		init[count].color = "W"; // White
	}
	else if (intColor == 1) {
		init[count].color = "B"; // Brown
	}
	else if (intColor == 2) {
		init[count].color = "Y"; // Yellow
	}
	else {
		init[count].color = "S"; // Spotted
	}
	init[count].age=0;
	init[count].name = nameLibrary[rand() % 10];
	percentMutant = rand() % 100 + 1;
	if(percentMutant<=2) {
		init[count].mutant=true;
	}
	else {
		init[count].mutant=false;
	}
	count++;
	if(count>1000) {
		//Will cull half the bunnies here to prevent array overflow
	}
}
