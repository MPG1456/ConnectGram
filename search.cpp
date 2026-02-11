#include "search.h"

extern vector<User *> userList;
extern HistorySearch myHistorySearch;

void smartSearch()
{
    string term, username;
    cin >> term;
    myHistorySearch.push(term);

    std::list<User *> results;
    vector<std::pair<int, User *>> hammingResults;
    
    term = lowercase(term);
    int charDis;
    for (auto &u : userList)
    {
        username = u->getUsername();
        charDis = term.size() - username.size();
        charDis = abs(charDis);
        if (charDis == 1)
            results.push_back(u);
        else if (charDis == 0)
        {
            charDis = hammingDistance(term, username);
            if (charDis == 0)
            {
                results.clear();
                results.push_back(u);
                showSmartSearchRes(results, true);
                return;
            }
            else if (charDis <= term.size() / 2)
                hammingResults.push_back(make_pair(charDis, u));
        }
    }
    std::sort(hammingResults.begin(), hammingResults.end(),
              [](const auto &a, const auto &b)
              { return a.first < b.first; });

    for (auto &x : hammingResults)
        results.push_front(x.second);

    showSmartSearchRes(results);
}

int hammingDistance(string u1, string u2)
{
    u2 = lowercase(u2);
    int distance = 0, len = u1.length();
    for (int i = 0; i < len; i++)
    {
        if (u1[i] != u2[i])
        {
            distance++;
        }
    }
    return distance;
}

void showSmartSearchRes(std::list<User *> results, bool isFound)
{
    int len = results.size();
    if (len == 0)
        cout << "\033[31m" << "No Results Found!" << "\033[0m" << endl;
    else if (isFound == true)
        cout << "\033[32m" << "Username Found: " << "\033[0m" << results.front()->getUsername() << endl << endl;
    else
    {
        cout << "\033[32m" << len << " Result(s) Found: " << "\033[0m" << endl;
        int i = 1;
        for (auto &r : results)
            cout << i++ << ". " << r->getUsername() << endl;
        cout << endl;
    }
}

HistorySearch::HistorySearch() : size(0)
{

}

void HistorySearch::push(string newHis)
{
    if (size == 5)
    {
        for (int i = 1; i < 5; ++i)
            his[i - 1] = his[i];
        his[4] = newHis;
    }
    else
        his[size++] = newHis;
}

void HistorySearch::showHistory()
{
    if (size == 0)
        cout << "\033[31m" << "No History Yet!" << "\033[0m" << endl;

    int index = 1;
    for (int i = size - 1; i >= 0; --i)
        cout << index++ << ". " << his[i] << endl;
    cout << endl;
}