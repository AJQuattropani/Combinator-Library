#include <iostream>
#include <string>
#include <vector>

#include "Combinator.h"

/*
* CURRENT TO-DO LIST:
* - IMPLEMENT PRINT PERM INTO INVERSION GENERATOR
* - FIX LEXICOGRAPHIC ORDER OF GROUPS
* - ADD A FUNCTION FOR GROUP PRINTING
* - FIX IF STATEMENTS
* - FIX TOO LARGE INVERSION SEQUENCES
* - COMPLETE INVERSION SEQUENCE GENERATOR
* - ADD COMMENTS TO GROUP GENERATORS
* - PROVE NTH GREY NUMBER
* - 
*/

using namespace std;

/*
* Loads, updates, or resets essential class data.
*/
void Combinator::init() {
	
	const unsigned short size = ((15 < str.size()) ? 15 : str.size());
	permutation = vector<unsigned short>(size-1);
	
	for (int i = 0; i < permutation.size(); i++) { // Reset permutation.
		permutation[i] = (i + 1) << 1;
	}

}

Combinator::Combinator() {
	str = "";
}

/*
* Generates the nth-largest grey number.
*/
inline int Combinator::nth_grey_number(const int& n) {
	return (n ^ (n >> 1)); // TODO: Prove this works!
}

/*
* Checks if a mobile number exists in the add-wise permutation algorithm.
*/
inline bool Combinator::check_if_mobile_exists(/*const vector<unsigned short>& permutation, */short& mobile_index, short& pointing_to) {
	
	mobile_index = -1; //Terminate condition taken as default.
	pointing_to = 0;
	short address_pointing_to = 0;

	for (short address = 0; address < permutation.size(); address++) {
		address_pointing_to = address - 1;
		if(permutation[address] & 1) address_pointing_to+=2; // first bit in permutation is delegated as the "direction" of the number
		if (address_pointing_to >= 0 && permutation.size() > address_pointing_to) { // makes sure it is in range
			if (mobile_index == -1 ) { // in the case where no mobile index has been down to exist yet
				if (permutation[address] > permutation[address_pointing_to]) { //TODO: simplify if statements for performance.
					mobile_index = address;
					pointing_to = address_pointing_to;
				}
			}
			else if (permutation[address] > permutation[mobile_index] && permutation[address] > permutation[address_pointing_to]) {
				mobile_index = address;
				pointing_to = address_pointing_to;
			}
		}
	}

	return mobile_index != -1;
}

/*
* Generates and prints all permutations of the string.
*/
void Combinator::while_permutator(vector<unsigned short>& permutation) {
	bool mobile_exists;
	short mobile_index = permutation.size() - 1;
	short pointing_to = mobile_index - 1;

	unsigned long long counter = 1L; // large variable to keep track of number of permutations (long only relevant for months of computation at current speeds)

	do {
		//print current permutation
		print_perm(counter);

		//flip arrows of larger values
		for (int i = 0; i < permutation.size(); i++) {
			if (permutation[i] > permutation[mobile_index]) permutation[i] ^= 1;
		}

		//do swap
		swap(permutation[mobile_index], permutation[pointing_to]);

		counter++;

		//check if mobile exists, and find new indices for loop
		mobile_exists = check_if_mobile_exists(mobile_index, pointing_to);
	} while (mobile_exists);

	//print last permuation
	print_perm(counter);

	cout << endl;

}

/*
* Prints permutation.
*/
inline void Combinator::print_perm() {
	//print new permuation

	short i;

	for (i = 0; i < permutation.size(); i++) {
		cout << str[(permutation[i] >> 1)];
	}

	cout << endl;
}

/*
* Prints permutation with counter.
*/
inline void Combinator::print_perm(unsigned long long& count) {
	//print new permuation

	short i;

	cout << count << ": ";

	for (i = 0; i < permutation.size(); i++) {
		cout << str[(permutation[i] >> 1)];
	}

	cout << endl;
}

/*
* Prints permutation with option of including the permutation number and requires the count.
*/
inline void Combinator::print_perm(unsigned long long& count, bool flag) {
	//print new permuation

	short i;

	if (flag) {
		for (i = 0; i < permutation.size(); i++) {
			cout << (permutation[i] >> 1);
		}
	}

	for (i = 0; i < permutation.size(); i++) {
		cout << str[(permutation[i] >> 1)];
	}

	cout << endl;
}

/*
* Get the current string held by Combinator.
*/
string Combinator::getString() const {
	return str; //TODO: consider smart pter
}

/*
* Set the current string held by Combinator.
*/
void Combinator::setString(const string& new_string) {
	str = new_string;
}

/*
* Add to the current string held by Combinator.
*/
void Combinator::add(const char& character) {

	for (int j = 0; j < str.size(); j++) {
		if (str[j] == character) {
			cout << "Duplicate characters not supported." << endl;
			return;
		}
	}
	str += character;
}

/* 
* Generates each set of a subset in lexigographic order.
*/
void Combinator::generate_addwise_combinations() {
	//start with two longs to be able to hold onto the index and the index max
	long j, max = 1 << (str.size() - 1);
	for (j = 0; j < max; j++) {
		cout << j << " ";
		for (int i = 0; i < str.size() - 1; i++) {
			cout << ((j & (1 << i)) >> i);
		}
		cout << ": {";
		for (int i = 0; i < str.size() - 1; i++) {
			//cout << ((j >> (i)) & 1) << "|";
			cout << ((j >> (i)) & 1 ? str[i + 1] : '\0');
		}
		cout << "}" << endl;
	}
	cout << endl;
}

/* 
* Generates each set of a subset in order such that only one element is changed.
*/
void Combinator::generate_greycode_combinations() {
	long j, max = 1 << (str.size() - 1);
	for (j = 0; j < max; j++) {
		cout << j << ": {";
		long grey_code = nth_grey_number(j);
		for (int i = 0; i < str.size() - 1; i++) {
			//cout << ((j >> (i)) & 1) << "|";
			cout << ((grey_code >> (i)) & 1 ? str[i + 1] : '\0');
		}
		cout << "}" << endl;
	}
	cout << endl;

}

/*
* Generates the permutations using a basic algorithm.
*/
void Combinator::generate_addwise_permutations() {
	// use a full short as permutation data structure. the first bit in the sequence will be left=0 or right=1.

	// the short provides permutator with range of up to 15, anything more would not be computable since #perms = n!.
	// in principle, the size can climb up to sizeof(unsigned short)/2 but this calculation would outlast the predicted lifespan of all stars and blackholes.
	//vector<unsigned short> permutation(size);

	//start with an in-order array of numbers, with values starting at 0

	for (int i = 0; i < permutation.size(); i++) { // update permutation.
		permutation[i] = (i + 1) << 1;
	}

	if (permutation.size() > 1) { // only bother with a large set
		while_permutator(permutation);
	}
	else {
		print_perm();
	}
}

/*
* Prints a permutation provided the reference for an inversion code.
*/
void Combinator::print_permutation_from_inversion(const vector<unsigned short>& inversion_code) {
	
	fill(permutation.begin(), permutation.end(), 0);
	
	for (unsigned short x : inversion_code) {
		cout << x;
	}

	cout << " : ";

	for (int i = 0; i < inversion_code.size(); i++) {
		int spacings = inversion_code[i];
		int space_counter = 0;
		int index = -1;

		while (space_counter <= spacings) {
			index++;
			//cout << "before {Space counter:" << space_counter << " Perm #:" << permutation[index] << " Index:" << index << "}\n";
			if (permutation[index] == 0) {
				space_counter++;
				//if (space_counter > spacings) break;
			}
			//cout << "after {Space counter:" << space_counter << " Perm #:" << permutation[index] << " Index:" << index << "}\n";
		}
		//cout << "exited with: " << index << endl;
		permutation[index] = i+1;

		//for (unsigned short x : permutation) {
		//	cout << x;
		//}
	}

	for (unsigned short x : permutation) {
		cout << x;
	}

	cout << " : ";

	print_perm();

	cout << endl;

}

/*
* Useful debug function for generating inversion codes and the overall permutation algorithm.
*/
void Combinator::print_example_permutations() {

	vector<unsigned short> code(permutation.size());

	// Most ordered:
	fill(code.begin(), code.end(),0);
	print_permutation_from_inversion(code);

	// Most disordered:
	int i;
	for (i = 1; i < code.size(); i++) {
		code[i] = code.size() - i - 1;
	}
	
	print_permutation_from_inversion(code);
	
	// Random permutation:
	for (i = 1; i < code.size()-1; i++) {
		code[i] = rand() % (code.size() - i);
	}

	print_permutation_from_inversion(code);
	
	

}