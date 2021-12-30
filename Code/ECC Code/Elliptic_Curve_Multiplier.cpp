#include <iostream>
#include <cmath>

using namespace std;

// Change any variables below

// Coordinates of the generator point
double YofG = 1;
double XofG = 0;

// y^2 = x^3 + ax + b
int AofCurve = 1;
int BofCurve = 1;

double Gradient;
double Cx;
double Cy;
double Newx;
double Newy;


double GradientofTangentToPoint(int a, int b, double x, double y)
{
    //Gradient = ((3*pow(x,2) + a)/(pow(x,3) + a*x + b));
    Gradient = ((3*pow(x,2) + a)/2*y);
    cout << Gradient << endl;
}


double PointDouble(int a, int b, double *x, double *y, double nx, double ny)
{
    // calculate the gradient through substituting values into the derivative
    Gradient = ((3*pow((*x),2) + a)/2*(*y));

    // calculate coords of the new intersection with the elliptic curve
    nx = pow(Gradient, 2) - 2*(*x);
    ny = Gradient*((*x) - nx) - (*y);

    // print readout of the new coords
    cout << "new x coord: " << nx << endl;
    cout << "new y coord: " << ny << endl;

    // set current x and y points to the newly determined points
    *x = nx;
    *y = ny;

}

double PointAddtion(double xGen, double yGen, double *xOther, double *yOther, double nx, double ny)
{
    // calculate the gradient between the points
    Gradient = (yGen - (*yOther))/(xGen - (*xOther));

    // calculate coords of the new intersection with the elliptic curve
    nx = pow(Gradient, 2) - xGen - (*xOther);
    ny = Gradient*(xGen - nx) - yGen;

    cout << Gradient <<endl;
    // print the readout of the new coords
    cout << "new x coords: " << nx << endl;
    cout << "new y coords: " << ny << endl;

    // set current x and y points to the newly determined points
    *xOther = nx;
    *yOther = ny;

}

double ScalarPointMultiplication(int a, int b, double xGen, double yGen, double *x, double *y, double nx, double ny, int repetition)
{
    PointDouble(a, b, x, y, nx, ny);
    for (int i = 0; i < repetition; i++)
    {
        PointAddtion(xGen, yGen, x, y, nx, ny);
    }
}


int main()
{
    Cx = XofG;
    Cy = YofG;
    //PointDouble(AofCurve, BofCurve, &Cx, &Cy, Newx, Newy);
    //cout << Cx << endl;
    //for (int i = 0; i < 25; i++)
    //{
      //  PointAddtion(XofG, YofG, &Cx, &Cy, Newx, Newy);
    //}
    ScalarPointMultiplication(AofCurve, BofCurve, XofG, YofG, &Cx, &Cy, Newx, Newy, 26);
}