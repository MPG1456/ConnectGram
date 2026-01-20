#pragma once

#include <iostream>
#include <vector>

#include "operation.h"

using namespace std;

class TrieNode
{
public:
    TrieNode *children[40]; //26 Alphabet, 10 number digits, 4 signs(@#_.)
    bool endOfWord;

    TrieNode() : endOfWord(false)
    {
        for(int i = 0; i < 40; ++i)
            children[i] = nullptr;
    }
};

class Trie
{
private:
    TrieNode *root;
    void findWord(TrieNode *start, vector<string> *result, string curWord);
    void removeNode(TrieNode *cur);
    
    public:
    Trie()
    {
        root = new TrieNode;
    }
    
    void insertNewWord(string newWord);
    void searchPrefix();
    ~Trie();
};

int char_to_index(char c);
char index_to_char(int index);