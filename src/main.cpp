#include <iostream>
#include <fstream>
#include <algorithm>
#include "dictionaryManager.h"
bool isValidInput(const std::string &input) {
    for (char ch : input) {
        if (!std::isalpha(ch)) {
            return false;
        }
    }
    return true;
}
int main() {
    Trie trie;
    string file = "D:/cpp projects/AutoCorrect/data/enable1.txt";
    loadDictionary(trie, file);
   
    std::string userInput;
    std::cout << "Enter a potentially misspelled word: ";
    std::cin >> userInput;
  
    if (trie.search(userInput)) {
        std::cout << "The word is spelled correctly.\n";
    } else {
        std::vector<std::string> suggestions = trie.suggest(userInput);
        if (!suggestions.empty()) {
            std::cout << "Did you mean:\n";
            for (const std::string& suggestion : suggestions) {
                std::cout << suggestion << '\n';
            }
        } else {
            std::cout << "No suggestions found.\n";
        }

        std::string addWordOption;
        std::cout << "Do you want to add this word to the dictionary? (yes/no): ";
        std::cin >> addWordOption;

        if (addWordOption == "yes") {
            trie.insert(userInput);
            std::cout << "Dictionary modified. New word added.\n";
        } else {
            std::cout << "Dictionary not modified.\n";
        }
    }

    return 0;
}