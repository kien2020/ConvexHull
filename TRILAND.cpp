/*
Author: chikien2009
*/
#include <bits/stdc++.h>

using namespace std;

void setup()
{
#ifndef ONLINE_JUDGE
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

struct POINT
{
    long long x, y;
    friend bool operator<(const POINT &ina, const POINT &inb)
    {
        return (ina.x == inb.x ? ina.y < inb.y : ina.x < inb.x);
    }
};

inline long long TriangleArea(POINT a, POINT b, POINT c)
{
    return (b.x - a.x) * (a.y + b.y) + (c.x - b.x) * (b.y + c.y) + (a.x - c.x) * (a.y + c.y);
}

inline long long RealArea(POINT a, POINT b, POINT c)
{
    return abs(TriangleArea(a, b, c));
}

class POLYGON
{
private:
    vector<POINT> vertex;

public:
    inline void Init(vector<POINT> new_vertex)
    {
        vertex = new_vertex;
    }
    inline vector<POINT> ConvexHull()
    {
        vector<POINT> hull, down;
        sort(vertex.begin(), vertex.end());
        for (int i = 0; i < vertex.size(); ++i)
        {
            while (2 <= hull.size() && TriangleArea(hull[hull.size() - 2], hull.back(), vertex[i]) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(vertex[i]);
        }
        for (int i = vertex.size() - 1; i >= 0; --i)
        {
            while (2 <= down.size() && TriangleArea(down[down.size() - 2], down.back(), vertex[i]) <= 0)
            {
                down.pop_back();
            }
            down.push_back(vertex[i]);
        }
        hull.pop_back();
        down.pop_back();
        hull.insert(hull.end(), down.begin(), down.end());
        return hull;
    }
};



int main()
{
    setup();

    int n;
    vector<POINT> v;
    cin >> n;
    long long res = 0, base;
    v.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i].x >> v[i].y;
    }
    POLYGON polygon;
    polygon.Init(v);
    v = polygon.ConvexHull();
    n = v.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1, k = i + 2; j <= k && k < n; ++j)
        {
            base = RealArea(v[i], v[j], v[k]);
            while (k + 1 < n && RealArea(v[i], v[j], v[k + 1]) > base)
            {
                k++;
                base = RealArea(v[i], v[j], v[k]);
            }
            res = max(res, base);
        }
    }
    cout << res / 2 << (res & 1 ? ".5" : ".0");
    return 0;
}
