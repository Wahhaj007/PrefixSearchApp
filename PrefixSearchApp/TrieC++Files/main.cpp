#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "csv.h"
#include "trieNode.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int main() {
    trieNode* root = new trieNode();
    io::CSVReader<2, io::trim_chars<>, io::double_quote_escape<',','\"'> > in("NewSongCSV.csv");
    in.read_header(io::ignore_extra_column, "Title", "ArtistName");
    std::string songName, songArtist;
    while (in.read_row(songName, songArtist)) {
        songName = trim(songName);
        songArtist = trim(songArtist);
        std::cout << "Trimmed Capital: '" << songName << "' Trimmed Name: '" << songArtist << "'" << std::endl;
        root->insert(songName);
        // root->insert(songArtist);
    }
    // Show all words in the trie for verification
    std::vector<std::string> allWords;
    root->getAllWords(root, "", allWords);
    std::cout << "All words in Trie:" << std::endl;
    for (const std::string& word : allWords) {
        std::cout << word << std::endl;
    }

        // Testing prefix "a"
    std::vector<std::string> aWords = root->prefixSearch("a");

    std::cout << "Words with prefix 'a':" << std::endl;
    for (const std::string& word : aWords) {
        std::cout << word << std::endl;
    }
    
    std::vector<std::string> chWords = root->prefixSearch("ch");

    std::cout << "Words with prefix 'ch':" << std::endl;
    for (const std::string& word : chWords) {
        std::cout << word << std::endl;
    }
    
    std::vector<std::string> newWords = root->prefixSearch("new");

    std::cout << "Words with prefix 'new':" << std::endl;
    for (const std::string& word : newWords) {
        std::cout << word << std::endl;
    }
    // Clean up
    delete root;

    return 0;
}






