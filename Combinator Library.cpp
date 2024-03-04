
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Combinator {
    private:
        string str;
        inline int nth_grey_number(const int& n) {
            return (n ^ (n >> 1));
        }
        inline bool check_if_mobile_exists(const vector<unsigned short>& permutation, unsigned short& mobile_index, short& pointing_to) {
            unsigned short pointed_to_index = 0;
            mobile_index = 0;

            for (int i = 1; i < permutation.size(); i++) {
                pointed_to_index = i + (permutation[i] & 1 ? 1 : -1);

                if (pointed_to_index > 0 && pointed_to_index < permutation.size()) {
                    if (permutation[i] > permutation[pointed_to_index] && permutation[i] > permutation[mobile_index >> 1]) {
                        mobile_index = (i << 1) + 1; //flag that a candidate index has been found
                    }
                }
            }

            if (mobile_index <= 0) return false;

            mobile_index >>= 1;
            pointing_to = (permutation[mobile_index] & 1 ? 1 : -1);

            return true;
        }
    public:
        string getString() const {
            return str;
        }

        void add(const char & character) {
            
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
        void generate_addwise_combinations() {
            //start with two longs to be able to hold onto the index and the index max
            long j, max = 1<<(str.size()-1);
            for (j = 0; j < max; j++) {
                cout << j << " ";
                for (int i = 0; i < str.size()-1; i++) {
                    cout << ((j & (1<<i)) >> i);
                }
                cout << ": {";
                for (int i = 0; i < str.size()-1; i++) {
                    //cout << ((j >> (i)) & 1) << "|";
                    cout << ((j >> (i)) & 1 ? str[i+1] : '\0');
                }
                cout << "}" << endl;
            }
            cout << endl;
        }

        /* Generates each set of a subset in order such that only one element is changed.*/
        void generate_greycode_combinations() {
            long j, max = 1<<(str.size()-1);
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

        void generate_addwise_permutations() {
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
                cout << str[x>>1];
            }

            cout << endl;

            if (size > 2) {
                while_permutator(permutation);
            }
        }

        void while_permutator(vector<unsigned short> &permutation) {
            bool mobile_exists = true;
            unsigned short mobile_index = permutation.size()-1;
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

};

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

    while (1) {
        cin >> i;

        if (i == 'A') combination.generate_addwise_permutations();
        if (i == 'B') combination.generate_addwise_combinations();
        if (i == 'C') combination.generate_greycode_combinations();
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
