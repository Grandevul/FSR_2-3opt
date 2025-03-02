#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

const long double PI = 3.14159265359, INF = 100000;
const double eps = 1e-8;

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

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

void opt3_swap(vector<Point<double>> &a, int type, int v1, int v2, int v3, int n)
{
//    cout << "///\n";
//                        for (int i = 0; i < n; i++)
//                        {
//                            cout << a[i].x << " " << a[i].y << endl;
//                        }
//                        cout << endl;
//    cout << " " << (v1 + 1) % n << " " << v2+1 << endl;
//                        cout << endl;
    switch(type)
    {
    case 1:
//        cout << "type=" << type << endl;
        reverse(a.begin() + (v1 + 1) % n, a.begin() + v2+1);
        break;
    case 2:
        reverse(a.begin() + (v3 + 1) % n, a.begin() + v1+1);
        break;
    case 3:
        reverse(a.begin() + (v2 + 1) % n, a.begin() + v3+1);
        break;
    case 4:
        reverse(a.begin() + (v2 + 1) % n, a.begin() + v3+1);
		reverse(a.begin() + (v1 + 1) % n, a.begin() + v3+1);
        break;
    case 5:
        reverse(a.begin() + (v1 + 1) % n, a.begin() + v2+1);
		reverse(a.begin() + (v2 + 1) % n, a.begin() + v3+1);
        break;
    case 6:
        reverse(a.begin() + (v1 + 1) % n, a.begin() + v2+1);
		reverse(a.begin() + (v1 + 1) % n, a.begin() + v3+1);
        break;
    case 7:
        reverse(a.begin() + (v2 + 1) % n, a.begin() + v3+1);
        reverse(a.begin() + (v1 + 1) % n, a.begin() + v2+1);
		reverse(a.begin() + (v1 + 1) % n, a.begin() + v3+1);
        break;
    }
//                        for (int i = 0; i < n; i++)
//                        {
//                            cout << a[i].x << " " << a[i].y << endl;
//                        }
//                        cout << endl;
}

double dist(vector<Point<double>> &a, int v1, int v2)
{
    int n = a.size();
    double ans = (a[v1%n] - a[v2%n]).len();
    return ans;
}

double dist_all(vector<Point<double>> &a, int v1, int v2, int v3)
{
    double ans = dist(a, v1, v1+1) + dist(a, v2, v2+1) + dist(a, v3, v3+1);
    return ans;
}

const int variants = 8;
double get_change(vector<Point<double>> &a, int &type, int v1, int v2, int v3, int n)
{
    vector <pair <double, int> > w(variants);
    for (int i = 0; i < variants; i++)
    {
        w[i].first = -dist_all(a, v1, v2, v3);
        w[i].second = i;
    }
    w[0].first += dist_all(a, v1, v2, v3);

    w[1].first += dist(a, v1, v2) + dist(a, v1+1, v2+1) + dist(a, v3, v3+1);

    w[2].first += dist(a, v1, v3) + dist(a, v2, v2+1) + dist(a, v3+1, v1+1);

    w[3].first += dist(a, v1, v1+1) + dist(a, v2, v3) + dist(a, v2+1, v3+1);

    w[4].first += dist(a, v1, v2+1) + dist(a, v1+1, v3+1) + dist(a, v3, v2);

    w[5].first += dist(a, v1, v2) + dist(a, v1+1, v3) + dist(a, v3+1, v2+1);

    w[6].first += dist(a, v1, v3) + dist(a, v1+1, v2+1) + dist(a, v2, v3+1);

    w[7].first += dist(a, v1, v2+1) + dist(a, v1+1, v3) + dist(a, v3+1, v2);
    pair <double, int> ans = *min_element(w.begin(), w.end());

//    if (ans.first < -eps)
//    {
//                        cout << "ans: " << ans.first << " " << ans.second << endl;
//                        cout << dist_all(a, v1, v2, v3) << endl;
//                        cout << "dist = " << dist(a, v1, v2) + dist(a, v1+1, v2+1) + dist(a, v3, v3+1) << endl;
//                        cout << v1 << " " << v2 << " " << v3 << endl;
////                        for (int i = 0; i < n; i++)
////                        {
////                            cout << a[i].x << " " << a[i].y << endl;
////                        }
////                        cout << endl;
////                        cout << a[v1].number << " " << a[v1+1].number << endl;
////                        cout << a[v2].number << " " << a[v2+1].number << endl;
////                        cout << a[v3].number << " " << a[v3+1].number << endl << endl;
//    }
    type = ans.second;
    return ans.first;
}

int main()
{
//    ifstream in("data/tsp_5_1");
//    ifstream in("data/tsp_6_1");
//    ifstream in("data/tsp_51_1");
    ifstream in("data/tsp_200_1");

    vector <Point<double>> p;

    if (in.is_open())
    {
        int n;
        in >> n;
//        cout << n << endl;

        for (int i = 0; i < n; i++)
        {
            double x, y;
            in >> x >> y;
//            cout << x << " " << y << endl;
            p.push_back(Point<double>(x, y, i));
        }
//        cout << endl;
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
    int it = 0;
    while (flag)
    {
        flag = false;
        for (int v1 = 0; v1 < n; v1++)
        {
            for (int v2 = v1 + 2; v2 < n; v2++)
            {
                for (int v3 = v2 + 2; v3 < n-1; v3++)
                {
                    int type = 0;
                    double change = get_change(a, type, v1, v2, v3, n);
                    if (change < -eps)
                    {
                        flag = true;
                        opt3_swap(a, type, v1, v2, v3, n);
                        length += change;
                    }
                }
            }
        }
//        it++;
//        if (it > 2)
//        {
//            flag = false;
//        }
    }
    length = 0;
    for (int i = 0; i < n; i++)
    {
        length += (a[i] - a[(i+1)%n]).len();
    }
    cout << length << " " << 1 << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
    }
    cout << endl;
}
