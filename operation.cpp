#include "operation.h"

extern vector<User*> userList;
extern vector<vector<User *>> userAdj;
extern Trie myTrie;
extern User *me;

void WelcomeMessage()
{
    system("cls");
    cout << "\033[32m" << "\\\\\\\\\\\\\\\\ConnectGram////////" << "\033[0m" << endl;
    cout << "\033[34m" << "(To use help, enter \"-h\")" << "\033[0m" << endl;
}

void Operation()
{
    string action;
    cin >> action;
    action = lowercase(action);
    if(action == "signup")
        me = SignUp();
    else if(action == "login")
        me = Login();
    else if(action == "follow")
        Follow();
    else if(action == "unfollow")
        Unfollow();
    else if(action == "search_user")
        myTrie.searchPrefix();
    else
        cout << "\033[31m" << "Wrong input! Try Again" << "\033[0m" << endl;

}

User *Login()
{
    User *tempLogin;
    string username, password;

    cin >> username;
    cin >> password;
    
    if (!(tempLogin = SearchUser(username)))
    {
        cout << "\033[31m" << "Username Not Found! Try Again" << "\033[0m" << endl;
        return nullptr;
    }

    if (HashThis(password) == tempLogin->getPassHash())
    {
        cout << "\033[32m" << "Login Successful! Welcome " << tempLogin->getUsername() << "\033[0m" << endl;
        return tempLogin;
    }
    else
    {
        cout << "\033[31m" << "Password Is Wrong! Try Again" << "\033[0m" << endl;
        return nullptr;
    }
}

User *SignUp()
{
    string username, password;

    cin >> username;
    cin >> password;

    if(IsValidUsername(username) == false)
    {
        cout << "\"" << username << "\" Is Invalid" << endl;
        cout << "Valid Characters: ((a-z) , (A-Z) , @ , # , _ , .)" << endl;
        return nullptr;
    }

    if(SearchUser(username) != nullptr)
    {
        cout << "\033[31m" << "This Username Already Exists! Try Again" << "\033[0m" << endl;
        return nullptr;
    }

    MakeNewUser(username, password);
    cout << "\033[32m" << "SignUp Successful! Welcome " << username << "\033[0m" <<  endl;
    return userList.back();
}

User *SearchUser(string username)
{
    username = lowercase(username);
    for (auto &temp : userList)
    {
        if (lowercase(temp->getUsername()) == username)
            return temp;
    }
    return nullptr;
}

void MakeNewUser(string username, string password)
{
    User *newUser = new User(username, HashThis(password));
    myTrie.insertNewWord(username);
    userList.push_back(newUser);
    User *temp = newUser;
    vector<User *> newUserAdj;
    newUserAdj.push_back(temp); //Every vector's first index here is the related user.
    userAdj.push_back(newUserAdj);
}

string lowercase(string upper)
{
    for (int i = 0; i < upper.size(); ++i)
        if (upper[i] >= 65 && upper[i] <= 90)
            upper[i] += 32;

    return upper;
}

void ExitProgram()
{
    // while(!WriteFile());
    FreeMemory();
    cout << "\033[32m" << "Successfully Exited! GOODBYE :)" << "\033[0m" << endl; 
}

void FreeMemory()
{
    for(auto *u : userList)
        delete u;
}