// takes a Scrabble dictionary from Github and builds a new .txt file with only the five-letter words:

#include <iostream>     // standard input/output
#include <fstream>      // file handling
#include <sstream>      // string manipulation
#include <vector>       // vector handling
#include <string>       // string manipulation

using namespace std;

int build_dictionary()
{

    ifstream dictionary_text("dictionary.txt");     // open text file from the file stream

    if (!dictionary_text) {
        cerr << "Error: Unable to open dictionary source file." << endl;
        return 1;
    }

    vector<string> dictionary_vector; // Use a vector to store the words
    string dictionary_entry; // String to store vector elements as we write 

    while (dictionary_text >> dictionary_entry) { // Read words from the dictionary text file into the string variable
        if (dictionary_entry.length() == 5) {
            dictionary_vector.push_back(dictionary_entry);
        }
    }

    dictionary_text.close();

    // Open a file for writing
    ofstream wordle_dictionary("wordle_dictionary.txt"); // This creates or overwrites wordle_dictionary.txt
    if (!wordle_dictionary) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return 2;
    }

    // Write each word to the file
    for (const auto& w : dictionary_vector) {
        wordle_dictionary << w << std::endl; // Write word followed by a newline
    }

     return 0;
}