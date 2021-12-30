/*
   Functions created need no inputs as they reference the
   specific variables within themselves.
   Therefore, consider removing the parameters to all functions.
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


// Change any variables below

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


long double GradientofTangentToPoint(int a, int b, long double x, long double y)
{
    //Gradient = ((3*pow(x,2) + a)/(pow(x,3) + a*x + b));
    Gradient = ((3*pow(x,2) + a)/2*y);
    cout << Gradient << endl;
}


long double PointDouble(int a, int b, long double *x, long double *y, long double xGen, long double yGen, long double nx, long double ny)
{
    // calculate the gradient through substituting values into the derivative
    Gradient = ((3*pow(xGen,2) + a)/2*yGen);

    // calculate coords of the new intersection with the elliptic curve
    nx = pow(Gradient, 2) - 2*xGen;
    ny = Gradient*(xGen - nx) - yGen;

    // print readout of the new coords
    //cout << "new x coord: " << nx << endl;
    //cout << "new y coord: " << ny << endl;

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

    //cout << Gradient <<endl;
    // print the readout of the new coords
    //cout << "new x coords: " << nx << endl;
    //cout << "new y coords: " << ny << endl;

    // set current x and y points to the newly determined points
    *xOther = nx;
    *yOther = ny;

}

long double ScalarPointMultiplication(int a, int b, long double xGen, long double yGen, long double *x, long double *y, long double nx, long double ny, int repetition)
{
    //*x = xGen;
    //*y = yGen;

    PointDouble(a, b, x, y, xGen, yGen, nx, ny);
    for (int i = 0; i < repetition; i++)
    {
        PointAddition(xGen, yGen, x, y, nx, ny);
    }
    //return(*x, *y);
}


// Variable setup - Feel free to change
int PrivateKey = 10;
//int GeneratorPoint = 15;
int UpperRandom = 500;

// Other variable setup - Leave unchanged
long double PublicKey[2];
int RandomVariable;
long double Message[2];
//double SymmetricKeyPublic[2];
//double SymmetricKeyPrivate[2];



// Key pair generation function
void PublicKeyGeneration(long double nx, long double ny, long double *x, long double *y, int PrivateKey)
{
    // multiply both together to get public key
    ScalarPointMultiplication(AofCurve, BofCurve, XofG, YofG, x, y, nx, ny, PrivateKey);
    PublicKey[0] = *x;
    PublicKey[1] = *y;
    // PrivateKey * GeneratorPoint; happens above

    // print out variable information
    cout << "your public key x is: " << PublicKey[0] << endl;
    cout << "your public key y is: " << PublicKey[1] << endl;
    //cout << "your generator point is: " << GeneratorPoint << endl;
}

// Generate random value function
void RandomNumberGeneration(int UpperRandom)
{
    srand(time(0));
    RandomVariable = rand() % UpperRandom;

    // inform of random variable
    cout << "Your randomly generated number is: " << RandomVariable << endl;
}

// Create transmitted message
void MessageCreator(long double nx, long double ny, long double *x, long double *y, int RandomVariable)
{
    ScalarPointMultiplication(AofCurve, BofCurve, XofG, YofG, x, y, nx, ny, RandomVariable);
    Message[0] = *x;
    Message[1] = *y;
    //Message = RandomVariable * GeneratorPoint; done above
    
    // inform of transmitted message
    cout << "the message x transmitted is: " << Message[0] << endl;
    cout << "the message y transmitted is: " << Message[1] << endl;
}

// Create symmetric key using public key
void SymKeyPublicCreation(long double nx, long double ny, long double *x, long double *y, int RandomVariable)
{

    *x = PublicKey[0];
    *y = PublicKey[1];

    for (int i = 0; i < RandomVariable; i++)
    {
        PointAddition(XofG, YofG, x, y, nx, ny);
    }

    //ScalarPointMultiplication(AofCurve, BofCurve, PublicKey[0], PublicKey[1], x, y, nx, ny, RandomVariable);
    long double SymmetricKeyPublic[2] = {*x, *y};
    //SymmetricKeyPublic = RandomVariable * PublicKey; done above


    // setting symkey to key 1
    Key1 = SymmetricKeyPublic[0];
    Key2 = SymmetricKeyPublic[1];

    // inform recipient of public key of their generated symmetric key
    cout << "the symmetric x key you have created but have kept hidden is: " << SymmetricKeyPublic[0] << endl;
    cout << "the symmetric y key you have created but have kept hidden is: " << SymmetricKeyPublic[1] << endl;
    cout << "NOTE, the above key is only known to the recipient of the public key" << endl;
}

// Determine the symmetric key using the private key
void SymKeyPrivateCreation(long double nx, long double ny, long double *x, long double *y, int PrivateKey)
{
    *x = Message[0];
    *y = Message[1];

    for (int i = 0; i < PrivateKey; i++)
    {
        PointAddition(XofG, YofG, x, y, nx, ny);
    }

    //ScalarPointMultiplication(AofCurve, BofCurve, Message[0], Message[1], x, y, nx, ny, PrivateKey);
    long double SymmetricKeyPrivate[2] = {*x, *y};
    //SymmetricKeyPrivate = Message * PrivateKey; done above

    // inform creator of private key of their generated symmetric key
    cout << "the symmetric x key you have created but have kept hidden is: " << SymmetricKeyPrivate[0] << endl;
    cout << "the symmetric y key you have created but have kept hidden is: " << SymmetricKeyPrivate[1] << endl;
    cout << "NOTE, the above key is only known to the creator of the private key" << endl;
}


// main function
int main()
{
    Cx = XofG;
    Cy = YofG;
    PublicKeyGeneration(Newx, Newy, &Cx, &Cy, PrivateKey);
    RandomNumberGeneration(UpperRandom);
    MessageCreator(Newx, Newy, &Cx, &Cy, RandomVariable);
    SymKeyPublicCreation(Newx, Newy, &Cx, &Cy, RandomVariable);
    SymKeyPrivateCreation(Newx, Newy, &Cx, &Cy, PrivateKey);
    cout << "if the two seperately symmetric keys are the same, then the process has performed a key exchange" << endl;

    // define path for file and output the x and y key to the file
    const char *PATH="C:\\Pacemaker-Cryptosystem\\Code\\AES Code\\AES_input_files\\key_exchange.txt"; // NOTE: replace path with your path to the AES input key file
    std::ofstream OutPutFile;
    OutPutFile.open(PATH, std::ios_base::app);
    OutPutFile << std::fixed << std::setprecision(37) << Key1;
    cout << Key1 << endl;
    cout << Key2;
    
    return 0;
}