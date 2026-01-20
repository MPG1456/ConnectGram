#include "post.h"

Post::Post(string text, User *author) : id(increaseID), text(text), author(author)
{
    increaseID++;
}

Post::Post(unsigned int id, string text, Time publishedTime, User *author) : id(id), text(text), publishedTime(publishedTime), author(author)
{
}

int Post::getElapsedTime()
{
    Time now;
    return now - this->publishedTime;
}

float Post::getScore()
{
    return (userLikes.size() * 2) + (author->getFollowersCount() * 0.5) + (1000 / this->getElapsedTime());
}

void Post::exportHashtag()
{
    string word;
    for (int i = 0; i < text.size(); ++i)
    {
        word.clear();
        if (text[i] == '#')
        {
            while (text[i + 1] != ' ' && i + 1 < text.size())
                word += text[i++];
            
            
        }
    }
}