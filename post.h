#pragma once

#include <iostream>

#include "time.h"
#include "user.h"

using namespace std;

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
    float getScore();
};
