#pragma once

#include <iostream>
#include <algorithm>

#include "time.h"
#include "user.h"
#include "hashtable.h"
#include "maxheap.h"

using namespace std;

class User;

class Post
{
private:
    unsigned int id;
    string text;
    Time publishedTime;
    User *author;
    vector<User *> userLikes;

    void exportHashtag();

public:
    static unsigned int increaseID;
    Post(string text, User *author);
    Post(unsigned int id, string text, Time publishedTime, User *author);
    int getElapsedTime();
    int getID();
    float getScore();
    string getText();
    vector<User *> *getUserLikes();
    void showText();
    void showPost(int index = 0, bool isFeed = false);
};

void postContent();
void searchContentHashtag();
void likePost();
void showFeed();