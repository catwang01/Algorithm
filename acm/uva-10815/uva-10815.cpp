#include <iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

#define TEST

int main()
{
#ifdef TEST
    freopen("uva-10815-input.txt", "r", stdin);
#endif
    set<string> words;
    string word;
    char c;
    while (cin.get(c))
    {
        if (isalpha(c))
            word += tolower(c);
        else
        {
            if (word != "") words.insert(word);
            word = "";
        }
    }
    for_each(words.begin(), words.end(), [](const string & s) { cout << s << endl; });
#ifdef TEST
    fclose(stdin);
#endif
    return 0;
}
