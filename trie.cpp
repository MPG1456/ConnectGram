#include "trie.h"

void Trie::insertNewWord(string newWord)
{
    newWord = lowercase(newWord);
    TrieNode *current = root;
    int index;
    for (auto w : newWord)
    {
        index = char_to_index(w);
        if (index != '?') // Should never be equal to ?
        {
            if(current->children[index] == nullptr)
                current->children[index] = new TrieNode;
            current = current->children[index];
        }
    }

    current->endOfWord = true;
}

void Trie::searchPrefix()
{
    string firstKey, key;
    cin >> firstKey;
    key = lowercase(firstKey);
    TrieNode *current = root;
    int index;
    for (auto w : key)
    {
        index = char_to_index(w);
        if (current->children[index] == nullptr)
        {
            cout << "\033[31m" << "No results Found!" << "\033[0m" << endl;
            return;
        }
        current = current->children[index];
    }
    vector<string> result;
    findWord(current, &result, key);

    if (result.size() == 0)
    {
        cout << "\033[31m" << "No results Found!" << "\033[0m" << endl;
        return;
    }

    cout << "Results for \"" << firstKey << "\":(max 10 closest results) " << endl;
    for (index = 0; index < result.size(); ++index)
        cout << index + 1 << ". " << result[index] << endl;
}

int char_to_index(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    if (c == '@')
        return 36;
    if (c == '#')
        return 37;
    if (c == '_')
        return 38;
    if (c == '.')
        return 39;
    return -1; // Should never happen
}

char index_to_char(int index)
{
    if (index >= 0 && index <= 9)
        return (char)('0' + index);
    if (index >= 10 && index <= 35)
        return (char)('a' + (index - 10));
    if (index == 36)
        return '@';
    if (index == 37)
        return '#';
    if (index == 38)
        return '_';
    if (index == 39)
        return '.';
    return '?'; // Should not happen
}

void Trie::findWord(TrieNode *start, vector<string> *result, string curWord)
{
    if (result->size() > 10 || start == nullptr)
        return;

    if (start->endOfWord == true)
        result->push_back(curWord);

    char nextChar;
    for (int i = 0; i < 40; ++i)
    {
        if (start->children[i] != nullptr)
        {
            nextChar = index_to_char(i);
            findWord(start->children[i], result, curWord + nextChar);
        }
        if (result->size() > 10)
            return;
    }
}

Trie::~Trie()
{
    removeNode(root);
}

void Trie::removeNode(TrieNode *cur)
{
    if(cur == nullptr)
        return;
    for(int i = 0; i < 40; ++i)
        removeNode(cur->children[i]);
    delete cur;
}

