#include <iostream>
#include <string>
#include <vector>

#include "Combinator.h"

using namespace std;

inline int Combinator::nth_grey_number(const int& n) {
	return (n ^ (n >> 1));
}

inline bool Combinator::check_if_mobile_exists(const vector<unsigned short>& permutation, unsigned short& mobile_index, short& pointing_to) {
	unsigned short pointed_to_index = 0;
	mobile_index = 0;

	for (int i = 1; i < permutation.size(); i++) {
		pointed_to_index = i + (permutation[i] & 1 ? 1 : -1);

		if (pointed_to_index > 0 && pointed_to_index < permutation.size()) {
			if (permutation[i] > permutation[pointed_to_index] && permutation[i] > permutation[mobile_index >> 1]) {
				mobile_index = (i << 1) | 1; //flag that a candidate index has been found
			}
		}
	}

	if (mobile_index <= 0) return false;

	mobile_index >>= 1;
	pointing_to = (permutation[mobile_index] & 1 ? 1 : -1);

	return true;
}

void Combinator::while_permutator(vector<unsigned short>& permutation) {
	bool mobile_exists = true;
	unsigned short mobile_index = permutation.size() - 1;
	short pointing_to = -1;

	unsigned long long counter = 2L;

	while (mobile_exists) {

		cout << counter << ": " /* << mobile_index << " " << pointing_to << " "*/;
		//swap elements
		swap(permutation[mobile_index], permutation[mobile_index + pointing_to]);

		//print new permuation
		for (unsigned short x : permutation) {
			cout << str[x >> 1];
		}
		cout << endl;

		//flip first bit for all values larger than the mobile value
		for (int i = 1; i < permutation.size(); i++) {
			if ((permutation[i] >> 1) > (permutation[mobile_index + pointing_to] >> 1)) {
				permutation[i] = permutation[i] ^ 1;
			}
			//cout << endl << (permutation[i] & 1);
		}

		//find a new mobile number
		mobile_exists = check_if_mobile_exists(permutation, mobile_index, pointing_to);
		counter++;
	}
	cout << endl;
}

string Combinator::getString() const {
	return str;
}

void Combinator::add(const char& character) {

	for (int j = 0; j < str.size(); j++) {
		if (character == 0) return;
		if (str[j] == character) {
			cout << "Duplicate characters not supported." << endl;
			return;
		}
	}
	str += character;
}

/* Generates each set of a subset in lexigographic order.*/
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

/* Generates each set of a subset in order such that only one element is changed.*/
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

void Combinator::generate_addwise_permutations() {
	// use a full short as permutation data structure. the first bit in the sequence will be left=0 or right=1.

	// the short provides permutator with range of up to 15, anything more would not be computable since #perms = n!.
	// in principle, the size can climb up to sizeof(unsigned short)/2 but this calculation would outlast the predicted lifespan of all stars and blackholes.
	const unsigned short size = (15 < str.size()) ? 15 : str.size();
	vector<unsigned short> permutation(size);

	//TODO: replace while with do-while statement entirely held in "while permutator"

	//start with an in-order array of numbers, with values starting at 0
	for (int i = 0; i < size; i++) {
		permutation[i] = (i << 1);
	}

	cout << "1: ";
	for (unsigned short x : permutation) {
		cout << str[x >> 1];
	}

	cout << endl;

	if (size > 2) {
		while_permutator(permutation);
	}
}