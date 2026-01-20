#pragma once
#include <iostream>

#include "user.h"
#include "trie.h"

using namespace std;

void WelcomeMessage();
void Helper();
void Operation();
User *Login();
User *SignUp();
void MakeNewUser(string username, string password);

string lowercase(string);

// bool ReadFile();
void ExitProgram();
void FreeMemory();
// bool WriteFile();