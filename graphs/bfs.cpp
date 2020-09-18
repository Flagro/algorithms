#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    const int INF = 1e9;
    int N = 0, M = 0, a = 0, b = 0;
    cin >> N >> M >> a >> b;
    vector < vector<int> > graph(N + 1);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector <int> dist(N + 1, INF);
    dist[a] = 0;
    vector <int> prev(N + 1, -1);
    queue <int> q;
    q.push(a);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        for (auto el: graph[curr])
            if (dist[el] == INF)
            {
                dist[el] = dist[curr] + 1;
                prev[el] = curr;
                q.push(el);
            }
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
