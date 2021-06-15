#include <iostream>
#include <deque>
#include <map>
#include <unordered_map>

using namespace std;

#define TEST

void solve(int n)
{
    int npeople, peopleno;
    unordered_map<int, int> people2team;
    for (int i = 0; i < n; i++)
    {
        cin >> npeople;
        for (int j = 0; j < npeople; j++)
        {
            cin >> peopleno;
            people2team[peopleno] = i;
        }
    }

    string s;
    unordered_map<int, int> team_order;
    map<int, deque<int>> waiting_lines;
    int next_order = 0;
    while (cin >> s)
    {
        if (s == "STOP") break;
        else
        {
            if (s == "ENQUEUE")
            {
                cin >> peopleno;
                int team = people2team[peopleno];
                if (team_order.find(team) == team_order.end())
                    team_order[team] = next_order++;
                waiting_lines[team_order[team]].push_back(peopleno);
            }
            if (s == "DEQUEUE")
            {
                map<int, deque<int>>::iterator p = waiting_lines.begin();
                cout << p->second.front() << endl;
                int team = people2team[p->second.front()];
                p->second.pop_front();
                if (p->second.empty()) 
                {
                    waiting_lines.erase(p);
                    team_order.erase(team);
                }
            }
        }
    }
}

int main()
{
#ifdef TEST
    freopen("uva-540-input.txt", "r", stdin);
#endif
    int i = 1;
    int n;
    while (cin >> n)
    {
        if (n == 0) break;
        cout << "Scenario #" << i << endl;
        solve(n);
        cout << endl;
        i++;
    }
#ifdef TEST
    fclose(stdin);
#endif
}
