#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "operation.h"

using namespace std;


class User
{
private:
    string username;
    unsigned int password_hash;
    int followersCount;
    int followingsCount;

public:
    User(string username, unsigned int passHash);
    string getUsername();
    unsigned int getPassHash();
    void setUsername(string newUsername);
    void setPassHash(string newPass);
    void addFollowing(User *newFollowing); //Adds this as the new follower of newFollowing
    vector<vector<User *>>::iterator getAdjList();
    void showFollowers();
    void showFollowings();
    bool removeFollowing(User *newUnfollow); //Removes newUnfollow from the followings of this
    int getFollowersCount();
    int getFollowingsCount();
};


unsigned int HashThis(string myStr);
User *SearchUser(string username);
bool IsValidUsername(string username);
void Follow();
void Unfollow();