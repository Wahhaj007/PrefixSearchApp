#include "trieNode.h"
#include <cctype> // for tolower and isalpha functions

trieNode::trieNode() : wordEnd(false) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        children[i] = nullptr;
    }
}

trieNode::~trieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        delete children[i];
    }
}

int trieNode::charToIndex(char c) {
    if (c == ' ') return 26;
    return c - 'a';
}

void trieNode::setNode(char letter) {
    int index = charToIndex(letter);
    if (children[index] == nullptr) {
        children[index] = new trieNode();
    }
}

trieNode* trieNode::getNode(char letter) const {
    return children[charToIndex(letter)];
}

void trieNode::setWordEnd() {
    wordEnd = true;
}

bool trieNode::getWordEnd() const {
    return wordEnd;
}

void trieNode::insert(const std::string& key) {
    trieNode* crawl = this;
    for (char ch : key) {
        if (isalpha(ch) || ch == ' ') {
            ch = tolower(ch);
            crawl->setNode(ch);
            crawl = crawl->getNode(ch);
        }
    }
    crawl->setWordEnd();
}

bool trieNode::search(const std::string& key) const {
    const trieNode* crawl = this;
    for (char ch : key) {
        if (!isalpha(ch) && ch != ' ') continue;
        ch = tolower(ch);
        // if node ends before key is finished
        if (crawl->getNode(ch) == nullptr) {
            return false;
        }
        // get the next character in the word
        crawl = crawl->getNode(ch);
    }
    // return True if word ended (on success)
    return crawl->getWordEnd();
}

std::vector<std::string> trieNode::prefixSearch(const std::string& prefix) const {
    std::vector<std::string> results;
    const trieNode* node = this;
    for (char ch : prefix) {
        // skip over none alphabetic characters and unneccessary whitespace
        if (!isalpha(ch) && ch != ' ') continue;
        ch = tolower(ch);
        if (node->children[charToIndex(ch)] == nullptr) {
            return results; // Prefix does not exist
        }
        node = node->children[charToIndex(ch)];
    }
    getAllWords(node, prefix, results);
    return results;
}

void trieNode::getAllWords(const trieNode* node, const std::string& prefix, std::vector<std::string>& results) const {
    if (node == nullptr) {
        return;
    }
    if (node->getWordEnd()) {
        results.push_back(prefix);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            char nextChar = (i == 26) ? ' ' : 'a' + i;
            getAllWords(node->children[i], prefix + nextChar, results);
        }
    }
}
