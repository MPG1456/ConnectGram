#include "post.h"

extern HashTable myTable;
extern User *me;
extern vector<Post *> allPosts;

Post::Post(string text, User *author) : id(increaseID), text(text), author(author)
{
    increaseID++;
    this->exportHashtag();
}

Post::Post(unsigned int id, string text, Time publishedTime, User *author) : id(id), text(text), publishedTime(publishedTime), author(author)
{
    this->exportHashtag();
}

int Post::getElapsedTime()
{
    Time now;
    return now - this->publishedTime;
}

int Post::getID()
{
    return this->id;
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
            ++i;
            while (i < text.size() && text[i] != ' ')
                word += text[i++];

            --i;
            if (!word.empty())
                myTable.insert(word, this);
        }
    }
}

string Post::getText()
{
    return this->text;
}

vector<User *> *Post::getUserLikes()
{
    return &(this->userLikes);
}

void postContent()
{
    string text;
    getline(std::cin, text);

    if (me == nullptr)
    {
        cout << "\033[31m" << "You Have to Login/Signup First!" << "\033[0m" << endl;
        return;
    }

    allPosts.emplace_back(new Post(text, me));
    cout << "\033[32m" << "Successfully Posted." << "\033[0m" << endl;
}

void searchContentHashtag()
{
    string hashtag;
    cin >> hashtag;

    if (hashtag[0] == '#')
        hashtag = hashtag.substr(1); // Removes #

    vector<Post *> *posts = myTable.getPosts(hashtag);
    if (posts == nullptr)
        cout << "\033[31m" << "No Posts Found!" << "\033[0m" << endl;
    else
    {
        int i = 1;
        for (auto &p : *posts)
            p->showPost(i++);
    }
}

void Post::showPost(int index, bool isFeed)
{
    cout << endl;
    if (index != 0)
        cout << index << ". " << this->author->getUsername() << endl;
    else
        cout << this->author->getUsername();

    this->showText();
    if(isFeed == true)
        cout << "Score: " << this->getScore() << "      ";
    cout << "Likes: " << userLikes.size() << "      " << "ID: " << id << "      ";
    this->publishedTime.displayTime();
    cout << "------------------------------------------------------------" << endl;
}

void Post::showText()
{
    int startPoint = 0;
    while (text[startPoint] == ' ')
        startPoint++;
    int charCount = 0;
    for (int i = startPoint; i < text.size(); ++i)
    {
        if (charCount > 45)
        {
            charCount = 0;
            cout << endl;
        }

        int j = i;
        while (j < text.size() && text[j] != ' ')
        {
            cout << text[j++];
            charCount++;
        }
        cout << text[j];
        i = j;
    }
    cout << endl;
}

void likePost()
{
    int id;
    cin >> id;

    if (me == nullptr)
    {
        cout << "\033[31m" << "You Have to Login/Signup First!" << "\033[0m" << endl;
        return;
    }

    for (auto &p : allPosts)
        if (p->getID() == id)
        {
            vector<User *> *userLikes = p->getUserLikes();
            if(find(userLikes->begin(), userLikes->end(), me) != userLikes->end())
            {
                cout << "\033[31m" << "You Have Already Liked This Post!" << "\033[0m" << endl;
                return;
            }
            userLikes->push_back(me);
            cout << "\033[32m" << "Successfully Liked Post With ID " << id << "\033[0m" << endl;
            return;
        }

    cout << "\033[31m" << "Post With ID " << id << " Doesn't Exist!" << "\033[0m" << endl;
}

void showFeed()
{
    vector<Post *> top10Posts = extract10Max();
    if(top10Posts.size() == 0)
    {
        cout << "\033[31m" << "There Are No Posts At The Time. Try Again Later!" << "\033[0m" << endl;
        return;
    }
    int i = 1;
    for(auto &p : top10Posts)
        p->showPost(i++, true);
}