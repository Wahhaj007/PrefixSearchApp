//
//  TrieNode.swift
//  SwiftPrefixSearch
//
//  Created by Wahhaj Malik on 4/19/24.
//

import Foundation

class TrieNode {
    var children: [Character: TrieNode] = [:]
    var isEndOfWord: Bool = false

    // Insert a word into the trie
    func insert(word: String) {
        var current = self
        for char in word.lowercased() {
            if !char.isLetter && char != " " {
                continue
            }
            if current.children[char] == nil {
                current.children[char] = TrieNode()
            }
            current = current.children[char]!
        }
        current.isEndOfWord = true
    }

    // Search for a word in the trie
    func search(word: String) -> Bool {
        var current = self
        for char in word.lowercased() {
            if !char.isLetter && char != " " {
                continue
            }
            guard let nextNode = current.children[char] else {
                return false
            }
            current = nextNode
        }
        return current.isEndOfWord
    }

    // Perform a prefix search in the trie
    func starts(with prefix: String) -> [String] {
        var results = [String]()
        var current = self
        for char in prefix.lowercased() {
            if !char.isLetter && char != " " {
                continue
            }
            guard let nextNode = current.children[char] else {
                return []
            }
            current = nextNode
        }
        findAllWords(from: current, prefix: prefix, results: &results)
        return results
    }

    // Helper function to find all words starting with a given node
    private func findAllWords(from node: TrieNode, prefix: String, results: inout [String]) {
        if node.isEndOfWord {
            results.append(prefix)
        }
        for (char, childNode) in node.children {
            findAllWords(from: childNode, prefix: prefix + String(char), results: &results)
        }
    }
}

