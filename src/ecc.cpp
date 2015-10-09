#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int A = 9, B = 17;
int p = 23;

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

struct Point
{
    int x; int y;
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
    Point P, Q;
    P.x = 16; P.y = 5;
    Q.x = 12; Q.y = 17;
    // Q = P;

    Point R = P + Q;
    cout << "(" << R.x << ", " << R.y << ")" << endl;

    return 0;
}
