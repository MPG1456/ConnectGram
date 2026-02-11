#include "maxheap.h"

extern vector<Post *> allPosts;

MaxHeap::MaxHeap()
{
    for(auto &p : allPosts)
        push(p);
}

void MaxHeap::heapifyUp(int index)
{
    while(index > 0 && heap[index]->getScore() > heap[(index - 1) / 2]->getScore())
    {
        std::swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void MaxHeap::heapifyDown(int index)
{
    int largest = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int size = heap.size();

    if(left < size && heap[left]->getScore() > heap[largest]->getScore())
        largest = left;

    if(right < size && heap[right]->getScore() > heap[largest]->getScore())
        largest = right;

    if(largest != index)
    {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

void MaxHeap::push(Post *newPost)
{
    heap.push_back(newPost);
    heapifyUp(heap.size() - 1);
}

Post *MaxHeap::pop()
{
    if(heap.empty() == true)
        return nullptr;

    Post *popPost = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    heapifyDown(0);
    return popPost;
}

vector<Post *> extract10Max()
{
    MaxHeap myHeap;
    Post *myPost;
    vector<Post *> max10;

        
    for(int i = 0; i < 10; ++i)
    {
        myPost = myHeap.pop();
        if(myPost == nullptr)
            break;
        max10.push_back(myPost);
    }
    return max10;
}