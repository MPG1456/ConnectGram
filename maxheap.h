#pragma once

#include <iostream>

#include "post.h"

class Post;

class MaxHeap
{
private:
    vector<Post *> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MaxHeap();
    void push(Post *newPost);
    Post *pop();
};

vector<Post *> extract10Max();