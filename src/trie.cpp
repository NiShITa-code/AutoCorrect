#include "trie.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
Trie::Trie() {
    root = new TrieNode();
}
int Trie::damerauLevenshteinDistance(const std::string &s1, const std::string &s2) {
    int m = s1.size();
    int n = s2.size();
    std::vector<std::vector<int>> d(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        d[i][0] = i;
    }

    for (int j = 0; j <= n; j++) {
        d[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = s1[i - 1] == s2[j - 1] ? 0 : 1;

            d[i][j] = min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost});

            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + cost);
            }
        }
    }

    return d[m][n];
}

void Trie::insert(const std ::string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        if (node->children.count(ch) == 0) {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];
    }

    node->isEndOfWord = true;
}

bool Trie::search(const std::string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        if (node->children.count(ch) == 0) {
            return false;
        }
        node = node->children[ch];
    }
    return node != nullptr && node->isEndOfWord;
}
void Trie::getWords(TrieNode* node, const std::string& prefix, std::vector<std::string>& words) const {
    if (node->isEndOfWord) {
        words.push_back(prefix);
    }

    for (const auto& kv : node->children) {
        getWords(kv.second, prefix + kv.first, words);
    }
}
vector<string> Trie::getWords() const {
    std::vector<std::string> words;
    getWords(root, "", words);
    return words;
}

std::vector<std::string> Trie::suggest(const std::string &input, int maxSuggestions) {
    std::vector<std::string> words = getWords();
    multimap<int, std::string> rankedWords;

    for (const std::string &word : words) {
        int distance = damerauLevenshteinDistance(input, word);
        rankedWords.insert({distance, word});
    }

    std::vector<std::string> suggestions;
    auto it = rankedWords.begin();
    for (int i = 0; i < maxSuggestions && it != rankedWords.end(); ++i, ++it) {
        suggestions.push_back(it->second);
    }

    return suggestions;
}





