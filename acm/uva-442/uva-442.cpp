
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define TEST

class Matrix
{ 
    public: 
    int left, right;
    Matrix(int left=0, int right=0): left(left), right(right) {}
};

auto ismatrix = [](char ch) {return 'A' <= ch && ch <='Z';};
auto isleftbrace = [](const Matrix& m) { return m.left==0 && m.right==0;};

string solve(const string& s, stack<Matrix>& st, const vector<Matrix>& matrices)
{
    int i = 0;
    Matrix m;
    int ret = 0;
    while(i < s.size())
    {
        if (ismatrix(s[i]))
        {
            m = matrices[s[i] - 'A'];
            if (st.empty() || isleftbrace(st.top())) 
            {
                st.push(m);
            }
            else 
            { 
                if (st.top().right == m.left)
                {
                    ret += st.top().left * st.top().right * m.right;
                    int newleft = st.top().left, newright = m.right;
                    st.push({newleft, newright});
                    i++;
                    m = matrices[s[i] - 'A'];
                }
                else 
                {
                    return "error";
                }
            }
        }
        else 
        {
            if (s[i] == '(')
            {
                st.push({0, 0});
            } 
            else 
            {
                m = st.top();
                st.pop(); st.pop();
            }
        }
    }
    return to_string(ret);
}


int main()
{
#ifdef TEST
    freopen("uva-442-input.txt", "r", stdin);
#endif
// code goes here
    int n; cin >> n;
    vector<Matrix> matrices(26);
    char ch; Matrix m;
    for (int i=0; i<n; i++)
    {
        cin >> ch >> m.left >> m.right;
        matrices[ch - 'A'] = m;
    }
    int ret = 0;
    stack<Matrix> st;
    string s;
    while (getline(cin, s))
    {
        cout << solve(s, st, matrices) << endl;;
    }

// code ends
#ifdef TEST
    fclose(stdin);
#endif
}
