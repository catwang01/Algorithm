
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

#define TEST

void solve(int n) 
{
    stack<int> st;
    queue<int> q;
    bool flag = true;
    while (true)
    {
        int x; 
        for (int i=0; i<n; i++)
        {
            cin >> x; 
            if (x) q.push(x); 
            else {flag = false; break;}
        } 
        if (!flag) break;
        for (int i=1; i<=n; i++)
        {
            st.push(i);
            while (!st.empty() && !q.empty() && st.top() == q.front())
            {
                st.pop(); q.pop();
            }
        }
        if (st.empty()) cout << "Yes" << endl;
        else cout << "No" << endl;
        while (!st.empty()) st.pop();
        while (!q.empty()) q.pop();
    }
}

int main()
{
#ifdef TEST
    freopen("uva-514-input.txt", "r", stdin);
#endif
// code goes here
    int n;
    while (cin >> n && n)  
    {
        solve(n);
        cout << endl;
    }
// code ends
#ifdef TEST
    fclose(stdin);
#endif
    return 0;
}
