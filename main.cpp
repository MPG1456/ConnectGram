#include <iostream>
#include "user.h"
#include "operation.h"
#include "trie.h"
#include "post.h"
#include "search.h"

using namespace std;

vector<User *> userList;
vector<vector<User *>> userAdj; // If A follows B, B can be found in A's adjacents
Trie myTrie;
User *me;
vector<Post *> allPosts;
HistorySearch myHistorySearch;

unsigned int Post::increaseID = 1;

int main()
{
    WelcomeMessage();
    while(Operation());
    ExitProgram();
}