#include <iostream>
#include <fstream>
#include <algorithm>
#include "Trie.h"

void loadDictionary(Trie &trie, const std::string &filename) {   
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << '\n';
        return;
    }    
    std::string word;

    while (std::getline(file, word)) {
        trie.insert(word);
    }
}

void saveDictionary(Trie &trie, const std::string &filename) {
    std::ofstream file(filename);
    std::vector<std::string> words = trie.suggest("");
    for (const std::string &word : words) {
        file << word << "\n";
    }
}
