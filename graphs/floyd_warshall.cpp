#include <iostream>
#include <vector>

using namespace std;

int main()
{
    const int INF = 1e9;
    int N = 0;
    cin >> N;
    vector < vector<int> > graph(N + 1, vector<int>(N + 1));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
        {
            cin >> graph[i][j];
            if (graph[i][j] == 100)
                graph[i][j] = INF;
        }
    vector < vector<int> > dist(graph);
    vector < vector<int> > prev(N + 1, vector<int>(N + 1));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            prev[i][j] = i;
    for (int k = 1; k <= N; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    prev[i][j] = prev[k][j];
                }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
            cout << dist[i][j] << " ";
        cout << endl;
    }
}
