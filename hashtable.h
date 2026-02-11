#pragma once

#include <iostream>
#include <list>

#include "post.h"

using namespace std;

class Post;

struct Entry
{
    string key;
    vector<Post *> posts;

    Entry(string key, Post *newPost);
};

class HashTable
{
private:
    vector<list<Entry>> table;
    size_t capacity;
    
    size_t hashFunction(const string &key) const;

public:
    HashTable();
    void insert(string key, Post *newPost);
    vector<Post *> *getPosts(string key);
};