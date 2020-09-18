#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    const int INF = 1e9;
    int N = 0, a = 0, b = 0;
    cin >> N >> a >> b;
    vector < vector<int> > graph(N + 1, vector<int>(N + 1));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> graph[i][j];
    vector <int> dist(N + 1, INF);
    dist[a] = 0;
    vector <int> prev(N + 1, -1);
    vector <bool> used(N + 1, false);
    int curr = a;
    while (curr != 0)
    {
        used[curr] = true;
        for (int i = 1; i <= N; i++)
            if (graph[curr][i] != -1 && dist[curr] + graph[curr][i] < dist[i])
            {
                dist[i] = dist[curr] + graph[curr][i];
                prev[i] = curr;
            }
        curr = 0;
        for (int i = 1; i <= N; i++)
            if (!used[i] && dist[i] < dist[curr])
                curr = i;
    }
    if (dist[b] != INF)
    {
        cout << dist[b] << endl;
        vector <int> ans;
        while (b != -1)
        {
            ans.push_back(b);
            b = prev[b];
        }
        reverse(ans.begin(), ans.end());
        for (auto el: ans)
            cout << el << " ";
        cout << endl;
    }
    else
        cout << -1 << endl;
    return 0;
}
