#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main()
{
    const int INF = 1e9;
    int N = 0, M = 0;
    cin >> N >> M;
    vector < tuple<int, int, int> > edge(M);
    for (int i = 0; i < M; i++)
        cin >> get<0>(edge[i]) >> get<1>(edge[i]) >> get<2>(edge[i]);
    int a = 1;
    vector <int> dist(N + 1, INF);
    dist[a] = 0;
    for (int k = 1; k < N; k++)
        for (auto el: edge)
        {
            int u = get<0>(el);
            int v = get<1>(el);
            int w = get<2>(el);
            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    for (int i = 1; i <= N; i++)
        cout << dist[i] << " ";
    cout << endl;
    return 0;
}
