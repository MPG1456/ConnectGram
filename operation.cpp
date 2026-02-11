#include "operation.h"

extern vector<User *> userList;
extern vector<vector<User *>> userAdj;
extern Trie myTrie;
extern User *me;
extern HistorySearch myHistorySearch;
extern vector<Post *> allPosts;

void WelcomeMessage()
{
    system("cls");
    cout << "\033[32m" << "\\\\\\\\\\\\\\\\ConnectGram////////" << "\033[0m" << endl;
    cout << "\033[34m" << "(To use help, enter \"-h\")" << "\033[0m" << endl;
}

void Helper()
{
    cout << "Only Commands Below Are Acceptable!" << endl;
    cout << "Sign Up: " << "\033[34m" << "signup [username] [password]" << "\033[0m" << endl;
    cout << "Log In: " << "\033[34m" << "login [username] [password]" << "\033[0m" << endl;
    cout << "Follow: " << "\033[34m" << "follow [username]" << "\033[0m" << endl;
    cout << "Unfollow: " << "\033[34m" << "unfollow [username]" << "\033[0m" << endl;
    cout << "Show My Followers: " << "\033[34m" << "show_followers" << "\033[0m" << endl;
    cout << "Show My Followings: " << "\033[34m" << "show_followings" << "\033[0m" << endl;
    cout << "Search User: " << "\033[34m" << "search_user [username]" << "\033[0m" << endl;
    cout << "Post a Content: " << "\033[34m" << "post [content]" << "\033[0m" << endl;
    cout << "Search a Trend by Hashtag: " << "\033[34m" << "trend [hashtag]" << "\033[0m" << endl;
    cout << "Like by ID: " << "\033[34m" << "Like [Post_ID]" << "\033[0m" << endl;
    cout << "Follow: " << "\033[34m" << "follow [username]" << "\033[0m" << endl;
    cout << "Show Feed: " << "\033[34m" << "show_feed" << "\033[0m" << endl;
    cout << "Smart Search: " << "\033[34m" << "smart_search [username]" << "\033[0m" << endl;
    cout << "Log Out: " << "\033[34m" << "logout" << "\033[0m" << endl;
    cout << "Exit: " << "\033[34m" << "exit" << "\033[0m" << endl;
    cout << "\033[34m" << "(To use help, enter \"-h\")" << "\033[0m" << endl;
    cout << endl;
}

bool Operation()
{
    string action;
    cin >> action;
    action = lowercase(action);
    if (action == "signup")
        me = SignUp();
    else if (action == "login")
        me = Login();
    else if (action == "follow")
        Follow();
    else if (action == "unfollow")
        Unfollow();
    else if (action == "show_followers")
        me->showFollowers();
    else if (action == "show_followings")
        me->showFollowings();
    else if (action == "search_user")
        myTrie.searchPrefix();
    else if (action == "post")
        postContent();
    else if (action == "trend")
        searchContentHashtag();
    else if (action == "like")
        likePost();
    else if (action == "show_feed")
        showFeed();
    else if (action == "smart_search")
        smartSearch();
    else if (action == "show_history")
        myHistorySearch.showHistory();
    else if (action == "-h")
        Helper();
    else if (action == "logout")
        logout();
    else if (action == "exit")
        return false;
    else
        cout << "\033[31m" << "Wrong input! Try Again" << "\033[0m" << endl;

    return true;
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

    if (IsValidUsername(username) == false)
    {
        cout << "\"" << username << "\" Is Invalid" << endl;
        cout << "Valid Characters: ((a-z) , (A-Z) , @ , # , _ , .)" << endl;
        return nullptr;
    }

    if (SearchUser(username) != nullptr)
    {
        cout << "\033[31m" << "This Username Already Exists! Try Again" << "\033[0m" << endl;
        return nullptr;
    }

    MakeNewUser(username, password);
    cout << "\033[32m" << "SignUp Successful! Welcome " << username << "\033[0m" << endl;
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
    newUserAdj.push_back(temp); // Every vector's first index here is the related user.
    userAdj.push_back(newUserAdj);
}

void logout()
{
    if (me == nullptr)
        cout << "\033[31m" << "You Aren't Signed In!" << "\33[0m" << endl;
    else
    {
        cout << "\033[32m" << "Successfully Logged Out of " << me->getUsername() << "\033[0m" << endl;
        me = nullptr;
    }
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
    for (auto *u : userList)
        delete u;

    for (auto *p : allPosts)
        delete p;
}