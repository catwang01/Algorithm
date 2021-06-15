#include <deque>
#include <stack>
#include <iostream>

using namespace std;

// #define TEST

void solve(const string& s)
{
    deque<char> left_cache;
    deque<char> screen_text;
    deque<char>* head = &screen_text;
    for (char ch: s)
    {
        if (ch == '[') 
        {
            while (left_cache.size())
            {
                screen_text.push_front(left_cache.back());
                left_cache.pop_back();
            }
            head = &left_cache;
        }
        else if (ch == ']') 
        { 
            while (left_cache.size())
            {
                screen_text.push_front(left_cache.back());
                left_cache.pop_back();
            }
            head = &screen_text;
        }
        else 
            head->push_back(ch);
    }
    while (left_cache.size())
    {
        screen_text.push_front(left_cache.back());
        left_cache.pop_back();
    }
    while (screen_text.size())
    {
        cout << screen_text.front();
        screen_text.pop_front();
    }
    cout << endl;
}

int main()
{
#ifdef TEST
    freopen("uva-11988-input.txt", "r", stdin);
#endif
// code goes here
    string s;
    while (getline(cin, s))
    {
        solve(s);
    }

// code ends
#ifdef TEST
    fclose(stdin);
#endif
    return 0;
}
