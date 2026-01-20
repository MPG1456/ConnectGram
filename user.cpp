#include "user.h"

extern vector<vector<User *>> userAdj;
extern User *me;

User::User(string username, unsigned int passHash) : username(username), password_hash(passHash), followersCount(0), followingsCount(0)
{
}

string User::getUsername()
{
    return username;
}

unsigned int User::getPassHash()
{
    return password_hash;
}

void User::setUsername(string newUsername)
{
    username = newUsername;
}

void User::setPassHash(string newPass)
{
    password_hash = HashThis(newPass);
}

void User::addFollowing(User *newFollowing)
{
    vector<vector<User *>>::iterator it = this->getAdjList();
    it->push_back(newFollowing);
    (newFollowing->followersCount)++;
    (this->followingsCount)++;
}

vector<vector<User *>>::iterator User::getAdjList()
{
    vector<vector<User *>>::iterator it;
    int i = 1;
    for (it = userAdj.begin(); it != userAdj.end(); ++it)
        if (it->front() == this)
            return it;
}

void User::showFollowers()
{
    int i = 1;
    cout << "Followers: " << followersCount << endl;
    for (auto &adj : userAdj)
    {
        if (adj.front() == this)
            continue;
        for (auto &u : adj)
            if (u == this)
            {
                cout << i++ << ". " << adj.front()->getUsername() << endl;
                continue;
            }
    }
    if (i == 1)
        cout << "\033[31m" << "No Matches Found!" << "\033[0m" << endl;
}

void User::showFollowings()
{
    int i = 0;
    vector<vector<User *>>::iterator it = getAdjList();
    cout << "Followings: " << followingsCount << endl;
    for (auto &u : *it)
        if (u == this)
            ++i;
        else
            cout << i++ << ". " << u->getUsername() << endl;

    if (i == 1)
        cout << "\033[31m" << "No Matches Found!" << "\033[0m" << endl;
}

unsigned int HashThis(string myStr)
{
    unsigned int m = 1e9 + 7;
    unsigned int hash = 0;
    for (auto &c : myStr)
        hash = (hash * 31 + (unsigned int)c) % m;

    return hash;
}

bool IsValidUsername(string username)
{
    for (int i = 0; i < username.size(); ++i)
        if (!(username[i] >= 'a' && username[i] <= 'z')) //(a - z)
            if (!(username[i] >= 'A' && username[i] <= 'Z')) //(A - Z)
                if (!(username[i] >= '0' && username[i] <= '9')) //(0 - 9)
                    if (username[i] != '_' && username[i] != '#') // _ , #
                        if (username[i] != '@' && username[i] != '.') // @ , .
                            return false;

    return true;
}

void Follow()
{
    string username;
    cin >> username;

    if (me == nullptr)
    {
        cout << "\033[31m" << "You Have to Login/Signup First!" << "\033[0m" << endl;
        return;
    }

    User *newFollowing = SearchUser(username);
    if (newFollowing == nullptr)
    {
        cout << "\033[31m" << "User " << username << " Wasn't Found! Try Again" << "\033[0m" << endl;
        return;
    }

    if (me == newFollowing)
    {
        cout << "\033[31m" << "You Can't Follow Yourself!" << "\033[0m" << endl;
        return;
    }

    vector<vector<User *>>::iterator it = me->getAdjList();
    for (auto &u : *it)
        if (u == newFollowing)
        {
            cout << "\033[31m" << "You Are Already Following " << u->getUsername() << "\033[0m" << endl;
            return;
        }

    me->addFollowing(newFollowing);
    cout << "\033[32m" << "Successfully Followed " << username << "\033[0m" << endl;
}

void Unfollow()
{
    string username;
    cin >> username;

    if (me == nullptr)
    {
        cout << "\033[31m" << "You Have to Login/Signup First!" << "\033[0m" << endl;
        return;
    }

    User *newUnfollow = SearchUser(username);
    if (newUnfollow == nullptr)
    {
        cout << "\033[31m" << "User " << username << " Wasn't Found! Try Again" << "\033[0m" << endl;
        return;
    }

    if (me == newUnfollow)
    {
        cout << "\033[31m" << "You Can't Unfollow Yourself!" << "\033[0m" << endl;
        return;
    }

    vector<vector<User *>>::iterator it = me->getAdjList();
    if(me->removeFollowing(newUnfollow) == false)
        cout << "\033[31m" << "You Aren't Following " << newUnfollow->getUsername() << "\033[0m" << endl;
    else
        cout << "\033[32m" << "Successfully Unfollowed " << newUnfollow->getUsername() << "\033[0m" << endl;
}

bool User::removeFollowing(User *newUnfollow)
{
    vector<vector<User *>>::iterator it = this->getAdjList();
    vector<User *>::iterator it2;
    for(it2 = it->begin(); it2 != it->end(); ++it2)
        if(*it2 == newUnfollow)
        {
            (*it).erase(it2);
            (this->followingsCount)--;
            (newUnfollow->followersCount)--;
            return true;
        }

    return false;
}

int User::getFollowersCount()
{
    return followersCount;
}

int User::getFollowingsCount()
{
    return followingsCount;
}

