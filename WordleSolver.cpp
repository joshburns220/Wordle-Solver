// WordleSolver.cpp

#include <iostream>     // standard input/output
#include <fstream>      // file handling
#include <sstream>      // read and write to strings, treating strings as streams
#include <vector>       // vector handling
#include <string>       // use C++ strings instead of default C strings
#include "wordle_solver_algorithm.cpp" // change this to a header file instead of inlining, idk why it won't work
// #include "dictionary_constructor.cpp"    // contains build_dictionary()
// I need to link this with a header file instead of including the entire constructor, etc. But, get it working first!

using namespace std;

// function declarations:

int isCharAllowed(char c, const char allowable[]);

int isInputValid(const string& input, const char F[], int sizeOfF);

void promptOne();
void inputOne();

void promptTwo();
void inputTwo();

void promptThree();
void inputThree();

// the following function is used to build a Wordle dictionary from any ordered text file, if we need to:
// build_dictionary();


// library of acceptable input characters, stored as char array:
const char inputs_permitted[27] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '*' };

string userInput;

string greens;
vector<string> yellows;
string invalid_chars;




int main()
{

    promptOne(); // Prompt functions print text to the console
    inputOne();  // Input functions read and validate strings from the std input stream

    promptTwo();
    inputTwo();

    promptThree();
    inputThree();

    //now compute solution set and print to console
    vector<string> result = possible_solutions(greens, yellows, invalid_chars);

    cout << "Possible solutions: " << endl;
    
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }

    return 0;
}





// function definitions:


int isCharAllowed(char c, const char allowable[]) {
    for (int i = 0; i < 27; i++) {
        if (c == allowable[i]) {
            return 0;  // Character is allowed
        }
    }
    return 1;  // Character not allowed
}

int isInputValid(const string& input, const char F[], int sizeOfF) {
    for (char c : input) {
        if (isCharAllowed(c, F) == 1) {
            return 1;  // 
        }
    }
    return 0;  // all characters are valid
}


void promptOne() {
    cout << "Step 1/3. Enter green letters according to place value." << endl;;
    cout << "Use only capital letters. Indicate unknowns with an asterisk (*) :" << endl;
    cout << "12345" << endl;
}

void inputOne() {
    getline(cin, userInput);  // Get input from the user
    if (isInputValid(userInput, inputs_permitted, 27) == 1 || userInput.empty() || userInput.size() != 5) {
        cout << "Invalid input. Try again:" << endl;
        cout << "12345" << endl;
        inputOne();
    }
    greens = userInput; // This is an inelegant solution, because it writes to the variable as many times
                        // as the input function was called. Will optimize it later, probably by trying something
                        // other than recursion.
    cout << endl;
}

void promptTwo() {
    cout << "Step 2/3. Enter yellow letters according to place value." << endl;
    cout << "If there are no yellow letters at that index, enter asterisk (*)." << endl;
    cout << "Use only capital letters." << endl;
}


void inputTwo() {
    for (int i = 0; i < 5; i++) { // get yellow characters for places 1-5 and store in a string vector
        cout << "Enter the yellow letters at the following index: ";
        cout << i + 1 << endl;
        getline(cin, userInput);
        while (isInputValid(userInput, inputs_permitted, 27) == 1 || userInput.empty()) {
            cout << "Invalid input. Try again." << endl;
            cout << "Enter the yellow letters at the following index: " << i + 1 << endl;
            getline(cin, userInput);
        }
        yellows.push_back(userInput);
    }

    // debug tool
    /*
    cout << "Yellow characters: ";
    for (int i = 0; i < yellows.size(); i++) {
        cout << yellows[i] << " ";
    }
    cout << endl;
    */

    cout << endl;

}

void promptThree() {
    cout << "Step 3/3. Enter gray letters in any order." << endl;
    cout << "Use only capital letters:" << endl;
}

void inputThree() {
    getline(cin, userInput);  // Get input from the user
    if (isInputValid(userInput, inputs_permitted, 27) == 1) {
        cout << "Invalid input. Try again:" << endl;
        inputThree();
    }
    invalid_chars = userInput;
    cout << endl;
}