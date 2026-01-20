#include <iostream>
#include "user.h"
#include "operation.h"
#include "trie.h"
#include "post.h"

using namespace std;

vector<User *> userList;
vector<vector<User *>> userAdj; // If A follows B, B can be found in A's adjacents
Trie myTrie;
User *me;
unsigned int Post::increaseID = 1;

int main()
{
    // ReadFile();
    WelcomeMessage();
    while(1)
    {
        me = nullptr;
        while(me == nullptr)
            Operation();
        Operation();
        Operation();
        myTrie.searchPrefix();
        me->showFollowers();
        me->showFollowings();
        cout << "Enter 1 to exit";
        int action = 0;
        cin >> action;
        if(action == 1)
            break;
    }
    ExitProgram();
}