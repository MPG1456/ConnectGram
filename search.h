#pragma once

#include <iostream>
#include <list>

#include "user.h"

using namespace std;

class User;

class HistorySearch
{
private:
    string his[5];
    int size;
    
public:
    HistorySearch();
    void push(string newHis);
    void showHistory();
};

void smartSearch();
int hammingDistance(string u1, string u2);
void showSmartSearchRes(std::list<User *>, bool isFound = false);

