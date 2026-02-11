#include "hashtable.h"

HashTable myTable;

Entry::Entry(string key, Post *newPost) : key(key)
{
    posts.push_back(newPost);
}

HashTable::HashTable() : capacity(1000007)
{
    table.resize(capacity);
}

size_t HashTable::hashFunction(const string &key) const
{
    unsigned long hash = 5381; // DJB2 algorithm initial value
    for (char c : key)
        hash = ((hash << 5) + hash) + c;

    return hash % capacity;
}

void HashTable::insert(string key, Post *newPost)
{
    size_t index = this->hashFunction(key);
    for (auto &i : table[index])
        if (i.key == key)
        {
            i.posts.push_back(newPost);
            return;
        }

    table[index].emplace_back(key, newPost);
}

vector<Post *> *HashTable::getPosts(string key)
{
    size_t index = this->hashFunction(key);
    for(auto &i : table[index])
        if(i.key == key)
            return &(i.posts);

    return nullptr;
}
