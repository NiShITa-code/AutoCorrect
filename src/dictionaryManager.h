#include <vector>
#include <string>
#include "Trie.h"
using namespace std;
void loadDictionary(Trie &trie, const std::string &filename);
void saveDictionary(const string& filePath, const vector<string>& dictionary);