#pragma once

#include<string>
#include<vector>

using namespace std;

class Combinator {
private:
	string str;
	inline int nth_grey_number(const int& n);
	inline bool check_if_mobile_exists(const vector<unsigned short>& permutation, unsigned short& mobile_index, short& pointing_to);
	void while_permutator(vector<unsigned short>& permutation);
public:
	string getString() const;
	void add(const char& character);
	void generate_addwise_combinations();
	void generate_greycode_combinations();
	void generate_addwise_permutations();


};