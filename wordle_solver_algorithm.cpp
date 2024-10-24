// algorithm to receive green, yellow, and gray character sets and return a list of possible answers:

#include <iostream>     // standard input/output
#include <fstream>      // file handling
#include <sstream>      // string read/write
#include <vector>       // vector handling
#include <string>       // string manipulation
#include <algorithm>	// for vector algorithms like count and remove

/*

Use me for debugging:

	for (int i = 0; i < solution_set.size(); i++) {
		cout << solution_set[i] << " ";
	}

*/

using namespace std;

vector<string> solution_set;

vector<int> find_char_indices(const string& str, char ch);


vector<string> possible_solutions(string green, vector<string> yellow, string gray) {

	ifstream wordle_dictionary_text("wordle_dictionary.txt");

	if (!wordle_dictionary_text) {
		cerr << "Error: Unable to open Wordle dictionary source file." << endl;
		return vector<string>();
	}

	// Step one:

	string word; // string to hold each word in the Wordle dictionary as it comes off the stream
	int pass = 0;	 // variable to check if each word passes through each filter


	while (wordle_dictionary_text >> word) {

		for (int i = 0; i < 5; i++) {

			if (green[i] == word[i] || green[i] == '*') {
				pass++;
			}
		}
		if (pass == 5) {
			solution_set.push_back(word);
		}
		pass = 0;
	}

	// Step two:

	pass = 0;

	// yellow is a vector of strings, i.e. arrays. it looks like, e.g: <ab, abc, q, *, qe>

	vector<string> temp;

	// right now this can't handle index-sensitive rejections. that's a feature i need to add



	for (int i = 0; i < solution_set.size(); i++) {
		bool should_push = true; 

		for (int j = 0; j < yellow.size(); j++) {
			for (int k = 0; k < yellow[j].size(); k++) {
				// If solution_set[i] does not have yellow[j][k] as a character, reject it
				int numberOfYellows = static_cast<int>(count(solution_set[i].begin(), solution_set[i].end(), yellow[j][k]));		// count technically does not return int type
				if (numberOfYellows == 0 && yellow[j][k] != '*') {
					should_push = false;  // Mark the string as rejected
					break;  // Break out of the current loop for this character
				} else {
					// do index checking here
					vector<int> check = find_char_indices(solution_set[i], yellow[j][k]);		// returns indices where yellowjk
																				// appears in s_set
					for (int l : check) {
						if (yellow[l].find(yellow[j][k]) != string::npos) {
							should_push = false;
							break;
						}
					}

					// vector<int> check2 = find_char_indices(yellow[j], yellow[j][k]);
					// what you actually want is to find every index of yellow in which yellow[j][k] appears...
					// ... and reject if any int in check matches any of them!

					// ranged for loop over check; for every int l in check, if yellow[l] contains yellow[j][k], REJECT
					

				}
			}

			if (!should_push) {
				break;  // Break out of the j loop if the string is rejected
			}
		}

		// Push the string to temp only if it passed all checks
		if (should_push) {
			temp.push_back(solution_set[i]);
		}
	}

	
	solution_set = temp;

	// Step three:

	for (int i = 0; i < solution_set.size(); i++) {		// iterate over the elements of solution_set via compare

		for (int j = 0; j < gray.size(); j++) {		// iterate over the length of gray

			if (count(solution_set[i].begin(), solution_set[i].end(), gray[j]) > 0) {
				solution_set[i] = "*";
			}

		}

	}

	solution_set.erase(remove(solution_set.begin(), solution_set.end(), "*"), solution_set.end());	// erase all *


	//
	/* debug tool

	for (int i = 0; i < solution_set.size(); i++) {
		cout << solution_set[i] << " ";
	}

	// */

	return solution_set;
}

vector<int> find_char_indices(const string& str, char ch) {
	vector<int> indices;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ch) {
			indices.push_back(i);  // Store the index
		}
	}

	return indices;
}
