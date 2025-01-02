/*
Author: chikien2009
*/
#include <bits/stdc++.h>

using namespace std;

inline void setup()
{
    freopen("CAKECUT.inp", "r", stdin);
    freopen("CAKECUT.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

#define X first
#define Y second

pair<long long, long long> p[100000];

inline long long TriangleArea(int i, int j, int k)
{
    return abs((p[i].X - p[j].X) * (p[i].Y + p[j].Y) + (p[j].X - p[k].X) * (p[j].Y + p[k].Y) + (p[k].X - p[i].X) * (p[k].Y + p[i].Y));
}

int n, a, b;
long long cur_sum = 0, total_sum = 0, cur_min = 9e18, next_sum, dif;

int main()
{
    setup();

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i].X >> p[i].Y;
    }
    for (int i = 2; i < n; ++i)
    {
        total_sum += TriangleArea(0, i - 1, i);
    }
    for (int i = 0, j = 1; i < n; ++i)
    {
        while (abs(total_sum - (cur_sum + TriangleArea(i, j, (j + 1) % n)) * 2) < abs(total_sum - cur_sum * 2))
        {
            cur_sum += TriangleArea(i, j, (j + 1) % n);
            j = (j + 1) % n;
        }
        dif = abs(cur_sum * 2 - total_sum);
        if (dif < cur_min)
        {
            a = i + 1;
            b = j + 1;
            cur_min = dif;
        }
        cur_sum -= TriangleArea(i, (i + 1) % n, j);
    }
    cout << a << " " << b;
    return 0;
}
