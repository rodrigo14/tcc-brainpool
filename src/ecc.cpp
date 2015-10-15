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

    Point operator*(int n)
    {
        Point P = Point(x, y);
        for (int i=0; i<n-1; i++)
            P = P + Point(x, y);

        return P;
    }
};

int main()
{
    A = 1; B = 44;
    p = 229;
    Point P = Point(5, 116);
    Point Q = Point(9, 7);
    // Q = P;

    Point R = P * 176;
    cout << "(" << R.x << ", " << R.y << ")\n";

    return 0;
}
