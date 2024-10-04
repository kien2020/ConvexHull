/*
Author: chikien2009
*/
#include <bits/stdc++.h>

using namespace std;

struct POINT
{
    int x, y;
    friend bool operator<(const POINT &ina, const POINT &inb)
    {
        return (ina.x == inb.x ? ina.y < inb.y : ina.x < inb.x);
    }
};

class POLYGON
{
private:
    vector<POINT> vertex;
    inline long long Area(vector<POINT> points)
    {
        long long res = 0;
        POINT next;
        for (int i = 0; i < points.size(); ++i)
        {
            next = points[(i + 1) % points.size()];
            res += (long long)(next.x - points[i].x) * (points[i].y + next.y);
        }
        return res;
    }

public:
    inline void Init(vector<POINT> new_vertex)
    {
        vertex = new_vertex;
    }
    inline long long RealArea()
    {
        return abs(Area(vertex));
    }
    inline vector<POINT> ConvexHull()
    {
        vector<POINT> hull, down;
        sort(vertex.begin(), vertex.end());
        for (int i = 0; i < vertex.size(); ++i)
        {
            while (2 <= hull.size() && Area({hull[hull.size() - 2], hull.back(), vertex[i]}) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(vertex[i]);
        }
        for (int i = vertex.size() - 1; i >= 0; --i)
        {
            while (2 <= down.size() && Area({down[down.size() - 2], down.back(), vertex[i]}) <= 0)
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
  
    vector<POINT> v;
    POINT p;
    int n, miny = 2e9, pos;
    cin >> n;
    while (n--)
    {
        cin >> p.x >> p.y;
        miny = min(miny, p.y);
        v.push_back(p);
    }
    POLYGON polygon;
    polygon.Init(v);
    v = polygon.ConvexHull();
    cout << v.size() << "\n";
    polygon.Init(v);
    long long r = polygon.RealArea();
    cout << r / 2 << (r & 1 ? ".5" : ".0") << "\n";
    for (int i = v.size(); i > 0; --i)
    {
        if (v[(i + v.size()) % v.size()].y == miny)
        {
            pos = i;
            break;
        }
    }
    for (int i = 0; i < v.size(); ++i)
    {
        p = v[(pos - i + v.size()) % v.size()];
        cout << p.x << " " << p.y << "\n";
    }
    return 0;
}
