#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int A, B, p;

int lambda(int yq, int yp, int xq, int xp)
{
    int a, b, d;
    a = (yq - yp) % p;
    if (a > p) a%=p;
    b = xq - xp;

    int aux;
    a < 0 ? aux = -a : aux = a;
    d = (int) GCD(aux, b);

    a /= d; b /= d;
    a = (a+p)%p;
    if (a % b) 
    {
        b = (int) InvMod(b, p);
        return a * b % p;
    }

    return a / b;
}

int lambda(int xp, int yp)
{
    int a, b, d;
    a = (3*xp*xp + A);
    if (a > p) a%=p;
    b = 2*yp;

    int aux;
    a < 0 ? aux = -a : aux = a;
    d = (int) GCD(aux, b);

    a /= d; b /= d;
    a = (a+p)%p;
    if (a % b) 
    {
        b = (int) InvMod(b, p);
        return a * b % p;
    }

    return a / b;
}

class Point
{
public:
    int x; int y;

    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    Point operator+(Point Q)
    {
        Point R;
        int delta;

        if (x == Q.x and y == Q.y) // if P == Q
            delta = lambda(x, y);
        else
            delta = lambda(Q.y, y, Q.x, x);
        
        int kx = (delta * delta - x - Q.x) % p;
        int ky = (delta * (x - kx) - y) % p;

        R.x = kx<0 ? kx+p : kx;
        R.y = ky<0 ? ky+p : ky;

        return R;
    }
};

int main()
{
    A = 3; B = 8;
    p = 13;
    Point P = Point(1, 8);
    Point Q = Point(9, 7);
    // Q = P;

    Point R = P + Q;
    cout << "(" << R.x << ", " << R.y << ")" << endl;

    return 0;
}
