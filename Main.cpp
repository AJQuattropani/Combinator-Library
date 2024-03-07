#include <iostream>

#include "Combinator.h"

using namespace std;

int main()
{
	char i = 0;
	Combinator combination;
	cout << "Welcome to the Combinator!\nPlease begin by adding your characters." << endl;
	while (i != '-') {
		combination.add(i);
		cout << "Enter any character, or - to terminate." << endl;
		cin >> i;
	}


	cout << combination.getString() << " | " << combination.getString().size() - 1 << endl;
	cout << endl;

	combination.init();

	while (1) {
		cin >> i;
		
		if (i == 'A') combination.generate_addwise_permutations();
		if (i == 'B') combination.generate_addwise_combinations();
		if (i == 'C') combination.generate_greycode_combinations();
		if (i == 'D') combination.print_example_permutations();
		if (i == '-') return 0;
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
