#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "stack.h"

using namespace std;
string SOURCE_FILE_NAME = "source.txt";

void check_extreme_conditions(const Stack<string> &stackSymbol);

string LETTERS[3] = {"x", "y", "z"};


void write_file(string data, string file_name) {
    ofstream new_file;
    new_file.open(file_name);
    new_file << data;
    new_file.close();
}

void read_file() {
    bool brackets = 0;
    string all_strings, line;
    Stack<string> stackSymbol(30);
    ifstream file("source.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            line = line;
            string word;
            istringstream iss(line, ios_base::in);
            vector<string> wordsVector;
            while (iss >> word) {
                //cout << word + "\n";
                stackSymbol.push(word);
                //stackSymbol.printStack();
                //cout << "_________\n";
            }
            reverse(begin(wordsVector), end(wordsVector));
        }
        file.close();
        check_extreme_conditions(stackSymbol);
        for (int i = stackSymbol.getTop(); i >= 1; i--) {
            //for (int j = 0; j <= sizeof(LETTERS)/sizeof(*LETTERS); j++) {
                if (stackSymbol.Peek(i) == "x" || stackSymbol.Peek(i) == "y" || stackSymbol.Peek(i) == "z" ) {
                    if (i == 1 || (i == 2 && stackSymbol.Peek(1) == ")" && brackets)) {
                        cout << "File is correct";
                        exit(0);
                    } else if (stackSymbol.Peek(i-1) == "+" || stackSymbol.Peek(i-1) == "-") {
                        i--;
                    } else if (stackSymbol.Peek(i-1)==")" && brackets) {
                        brackets = 0;
                        i--;
                    } else {
                        cout << "File is incorrect";
                        exit(0);
                    }
                } else if (stackSymbol.Peek(i) == "(") {
                    brackets = 1;
                } else if (stackSymbol.Peek(i) != "+" && stackSymbol.Peek(i) != "-") {
                    cout << "File is incorrect";
                    exit(0);
                }
            //}

        }
        //write_file(all_strings, EDITED_FILE_NAME);
        //cout << "Output: " + all_strings;
    } //else cout << "Unable to open file";
}

void check_extreme_conditions(const Stack<string> &stackSymbol) {
    if (stackSymbol.getTop() == 0) {
            cout << "File is empty! Please enter some data next time.\n";
        }
    if (stackSymbol.getTop() == 1) {
            for (int i = 0; i <= sizeof(LETTERS)/sizeof(*LETTERS); i++) {
                if (stackSymbol.Peek(1) == LETTERS[i]) {
                    cout << "File is correct";
                    exit(0);
                }
            }
        cout << "File is incorrect";
        exit(0);
        }
}

int main() {
    int is_correct;
    string answer, data;
    cout << "File is ready: Yes or No?\n";
    is_correct = 0;
    while (is_correct == 0) {
        cin >> answer;
        if (answer == "No") {
            cout << "Enter some data to file\n";
            while (data == "") {
                getline(cin, data);
            }
            write_file(data, SOURCE_FILE_NAME);
        } else if (answer != "Yes") {
            cout << "Yes or No?\n";
            continue;
        }
        is_correct = 1;
    };
    read_file();
    return 0;
}

