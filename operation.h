#pragma once
#include <iostream>

#include "user.h"
#include "trie.h"
#include "post.h"
#include "search.h"

using namespace std;

class User;

void WelcomeMessage();
void Helper();
bool Operation();
User *Login();
User *SignUp();
void MakeNewUser(string username, string password);
void logout();

string lowercase(string);

// bool ReadFile();
void ExitProgram();
void FreeMemory();
// bool WriteFile();