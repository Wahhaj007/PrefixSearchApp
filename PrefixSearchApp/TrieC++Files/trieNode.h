#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <string>
#include <vector>

class trieNode {
private:
    static const int ALPHABET_SIZE = 27; // 26 letters + 1 space character
    trieNode* children[ALPHABET_SIZE];
    bool wordEnd;

public:
    trieNode();
    ~trieNode();

    static int charToIndex(char c);

    void setNode(char letter);
    trieNode* getNode(char letter) const;
    void setWordEnd();
    bool getWordEnd() const;

    void insert(const std::string& key);
    bool search(const std::string& key) const;
    std::vector<std::string> prefixSearch(const std::string& prefix) const;   
    void getAllWords(const trieNode* node, const std::string& prefix, std::vector<std::string>& results) const;
};

#endif // TRIE_NODE_H
