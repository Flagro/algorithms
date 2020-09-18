#include <bits/stdc++.h>

using namespace std;

int query(vector <vector <int> > &sparse_table, vector<int> &log_2, int left, int right)
{
    int len = right - left + 1;
    int level = log_2[len];
    return min(sparse_table[level][left], sparse_table[level][right - (1 << level) + 1]);
}

int main()
{
    int N = 0, u = 0, v = 0;
    cin >> N;
    vector <int> mas(N + 1, 0);
    vector <int> log_2(N + 1, 0);
    for (int i = 1; i <= N; i++)
    {
        mas[i] = rand()%1000;
        cout << mas[i] << " ";
    }
    cout << endl;
    for (int i = 2; i <= N; i++)
        log_2[i] = log_2[i / 2] + 1;
    vector <vector <int> > sparse_table(log_2[N] + 1, vector <int> (N + 1, 0));
    for (int i = 1; i <= N; i++)
        sparse_table[0][i] = mas[i];
    for (int i = 1; (1 << i) <= N; i++)
        for (int j = 1; j + (1 << i) <= N + 1; j++)
            sparse_table[i][j] = min(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]);
    cin >> u >> v;
    cout << query(sparse_table, log_2, u, v);
}
