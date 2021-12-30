#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


// Coordinates of the generator point
long double YofG = 1;
long double XofG = 0;

// y^2 = x^3 + ax + b
int AofCurve = 1;
int BofCurve = 1;

long double Gradient;
long double Cx;
long double Cy;
long double Newx;
long double Newy;

// Outputting to file variables
long double Key1;
long double Key2;


long double PointDouble(int a, int b, long double *x, long double *y, long double xGen, long double yGen, long double nx, long double ny)
{
    // calculate the gradient through substituting values into the derivative
    Gradient = ((3*pow(xGen,2) + a)/2*yGen);

    // calculate coords of the new intersection with the elliptic curve
    nx = pow(Gradient, 2) - 2*xGen;
    ny = Gradient*(xGen - nx) - yGen;

    // set current x and y points to the newly determined points
    *x = nx;
    *y = ny;

}

long double PointAddition(long double xGen, long double yGen, long double *xOther, long double *yOther, long double nx, long double ny)
{
    // calculate the gradient between the points
    Gradient = (yGen - (*yOther))/(xGen - (*xOther));

    // calculate coords of the new intersection with the elliptic curve
    nx = pow(Gradient, 2) - xGen - (*xOther);
    ny = Gradient*(xGen - nx) - yGen;

    // set current x and y points to the newly determined points
    *xOther = nx;
    *yOther = ny;

}

long double ScalarPointMultiplication(int a, int b, long double xGen, long double yGen, long double *x, long double *y, long double nx, long double ny, int repetition)
{
    
    PointDouble(a, b, x, y, xGen, yGen, nx, ny);
    for (int i = 0; i < repetition; i++)
    {
        PointAddition(xGen, yGen, x, y, nx, ny);
    }

}


// Define private key being used
int PrivateKey = 10;

// Define public key array for x, y coords of public keys
long double PublicKey[2];

// Key pair generation function
void PublicKeyGeneration(long double nx, long double ny, long double *x, long double *y, int PrivateKey)
{
    // multiply both together to get public key
    ScalarPointMultiplication(AofCurve, BofCurve, XofG, YofG, x, y, nx, ny, PrivateKey);
    PublicKey[0] = *x;
    PublicKey[1] = *y;
    // PrivateKey * GeneratorPoint; happens above

    Key1 = PublicKey[0];
    Key2 = PublicKey[1];

    // print out variable information
    cout << "your public key x is: " << PublicKey[0] << endl;
    cout << "your public key y is: " << PublicKey[1] << endl;
}


// main function
int main()
{
    Cx = XofG;
    Cy = YofG;
    PublicKeyGeneration(Newx, Newy, &Cx, &Cy, PrivateKey);

    // define path for file and output the x and y public key to the file
    const char *PATH="C:\\Pacemaker-Cryptosystem\\Code\\ECC Code\\ECC_input_files\\ECC_key_exchange_1.txt"; // NOTE: replace with path for ECC key exchange input file
    std::ofstream OutPutFile;
    OutPutFile.open(PATH, std::ios_base::app);
    OutPutFile << std::fixed << std::setprecision(62) << Key1 << endl << Key2;
    cout << Key1 << endl;
    cout << Key2;
    
    return 0;
}