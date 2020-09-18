#include <bits/stdc++.h>

using namespace std;

struct Point
{
    double x;
    double y;
    Point(): x(0), y(0) {}
    Point(double x__, double y__): x(x__), y(y__) {}
};

double dist (Point A, Point B)
{
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

int main()
{
    const double INF = 1e18;
    int N = 0;
    cin >> N;
    vector <Point> Points(N);
    for (int i = 0; i < N; i++)
        cin >> Points[i].x >> Points[i].y;
    vector < vector<double> > d(N, vector<double>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j)
                d[i][j] = dist(Points[i], Points[j]);
    vector < vector<double> > h(1 << (N - 1), vector<double>(N - 1));
    for (int mask = 0; mask < (1 << (N - 1)); mask++)
        for (int i = 0; i < N - 1; i++)
            if (mask & (1 << i))
            {
                if (mask == (1 << i))
                    h[mask][i] = d[N - 1][i];
                else
                {
                    h[mask][i] = INF;
                    for (int j = 0; j < N - 1; j++)
                        if (i != j && (mask & (1 << j)))
                            h[mask][i] = min(h[mask][i], h[mask^(1 << i)][j] + d[j][i]);
                }
            }
    double ans = INF;
    for (int i = 0; i < N - 1; i++)
        ans = min(ans, h[(1 << (N - 1)) - 1][i] + d[i][N - 1]);
    cout.precision(16);
    cout.setf(ios::fixed);
    cout << ans << endl;
}
