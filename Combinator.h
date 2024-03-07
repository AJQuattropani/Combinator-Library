#pragma once

#include<string>
#include<vector>

using namespace std;

class Combinator {
private:
	vector<unsigned short> permutation;
	string str;
	inline int nth_grey_number(const int& n);
	inline bool check_if_mobile_exists(/*const vector<unsigned short>& permutation, */short& mobile_index, short& pointing_to);
	void while_permutator(vector<unsigned short>& permutation);
	inline void print_perm();
	inline void print_perm(unsigned long long& count);
	inline void print_perm(unsigned long long& count, bool flag);
public:
	Combinator();
	void init();
	string getString() const;
	void setString(const string& new_string);
	void add(const char& character);
	void generate_addwise_combinations();
	void generate_greycode_combinations();
	void generate_addwise_permutations();
	void generate_permutations_by_inversion();
	void print_permutation_from_inversion(const vector<unsigned short>& inversion_code);
	void print_example_permutations();
};