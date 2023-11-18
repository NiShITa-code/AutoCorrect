#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    Trie();
    void insert(const std::string &word);
    bool search(const std::string &word);
    std::vector<std::string> suggest(const std::string &input, int maxo = 3);
    TrieNode* root;
    void getWords(TrieNode* node, const std::string& prefix, std::vector<std::string>& words) const;
    std::vector<std::string> getWords() const;
    int damerauLevenshteinDistance(const std::string &s1, const std::string &s2);
};