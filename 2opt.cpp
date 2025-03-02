#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

const long double PI = 3.14159265359, INF = 100000;

template <class T>
struct Point
{
    T x;
    T y;
    int number;

    Point() {}
    Point(T x, T y, int num) : x(x), y(y), number(num) {}

///_______basic_operations_________

    T operator *(Point a) {
        return x * a.x + y * a.y;
    }
    T operator %(Point a) {
        return x * a.y - y * a.x;
    }
    T len() {
        return sqrt(x * x + y * y);
    }
    T sqr_len() {
        return x * x + y * y;
    }
    Point operator -(Point a) {
        return Point(x - a.x, y - a.y, 0);
    }
    Point operator +(Point a) {
        return Point(x + a.x, y + a.y, 0);
    }
    bool operator ==(Point a) {
        return x == a.x && y == a.y;
    }
    Point operator -() {
        return Point(-x, -y);
    }

///__________---/---_______________


    bool operator [](Point a) {
        return (a.x == x && a.y == y);
    }
    Point& operator ++() {
        x++;
        y++;
        return *this;
    }

///_______New_functions____________

    Point& operator =(Point a)
    {
        x = a.x;
        y = a.y;
        number = a.number;
        return *this;
    }
    Point& operator +=(Point a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }
};

template <class T>
istream &operator >>(istream& in, Point<T> &a)
{
    in >> a.x >> a.y;
    return in;
}

template <class T>
ostream &operator <<(ostream& out, Point<T> &a)
{
    out << a.number << " ";
    return out;
}
///-------------------------------------------------------------------------

void opt2_swap(vector<Point<double>> &a, int v1, int v2, int n)
{
    vector<Point<double>> b(n);
    int it = 0;
    for (int i = 0; i <= v1; i++)
    {
        b[it] = a[i];
        it++;
    }
    for (int i = v2; i > v1; i--)
    {
        b[it] = a[i];
        it++;
    }
    for (int i = v2+1; i < n; i++)
    {
        b[it] = a[i];
        it++;
    }
    a = b;
}

int main()
{
//    vector <int> b(3);
//    b[0] = 0;
//    b[1] = 1;
//    b[2] = 2;
//    reverse(b.begin()+1, b.end());
//
//                        for (int i = 0; i < 3; i++)
//                        {
//                            cout << b[i] << " ";
//                        }
//                        cout << endl;
//
//    return 0;
//    ifstream in("data/tsp_5_1");
//    ifstream in("data/tsp_51_1");
    ifstream in("data/tsp_225_1");

    vector <Point<double>> p;

    if (in.is_open())
    {
        int n;
        in >> n;
        cout << n << endl;

        for (int i = 0; i < n; i++)
        {
            double x, y;
            in >> x >> y;
            cout << x << " " << y << endl;
            p.push_back(Point<double>(x, y, i));
        }
        cout << endl;
    }
    in.close();

///--------------------------

//    auto rng = std::default_random_engine {};
//    std::shuffle(std::begin(a), std::end(a), rng);

    vector <Point<double>> a = p;
    int n = a.size();
    random_shuffle(a.begin(), a.end());

    double length = 0;
    for (int i = 0; i < n; i++)
    {
        length += (a[i] - a[(i+1)%n]).len();
    }

    bool flag = true;
    while (flag)
    {
        flag = false;
        for (int v1 = 0; v1 < n; v1++)
        {
            for (int v2 = v1 + 2; v2 < n-1; v2++)
            {
                double change = - (a[v1] - a[v1+1]).len() - (a[v2] - a[(v2+1)%n]).len() + (a[v1+1] - a[(v2+1)%n]).len() + (a[v1] - a[v2]).len();
                if (change < 0)
                {
                    flag = true;
                    opt2_swap(a, v1, v2, n);
                    length += change;
                }
            }
        }
    }
    cout << length << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
    }
    cout << endl;
}
