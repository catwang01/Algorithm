#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

#define TEST

int main()
{
#ifdef TEST
    freopen("uva-156-input.txt", "r", stdin);
#endif
    string word;
    map<string, int> counter;
    unordered_map<string, string> key2word;
    while (cin >> word)
    {
        if (word == "#") break;
        string key(word);
        for(char& ch : key) ch = tolower(ch);
        sort(key.begin(), key.end());
        counter[key]++;
        key2word[key] = word;
    }
    set<string> outputs;
    for_each(counter.begin(), counter.end(), [&](const pair<string, int>& p)
    {
        if (p.second == 1) outputs.insert(key2word[p.first]);
    });
    for_each(outputs.begin(), outputs.end(), [](const string & s) {cout << s << endl;});
#ifdef TEST
    fclose(stdin);
#endif
    return 0;

}
