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


// Define private key
int PrivateKey = 10;

// Define message
long double Message[2];


// Determine the symmetric key using the private key
void SymKeyPrivateCreation(long double nx, long double ny, long double *x, long double *y, int PrivateKey)
{
    // Read file to obtain values for message
    // define path for input file
    const char *PATH="C:\\Pacemaker-Cryptosystem\\Code\\ECC Code\\ECC_input_files\\ECC_key_exchange_2.txt"; // NOTE: replace for your file path
    std::ifstream InPutFile;
    InPutFile.open(PATH);

    string temp_key_string;
    long double temp_key;

    for (int i = 0; i < 2; i++)
    {
        ( getline (InPutFile,temp_key_string) );
        temp_key = {stold(temp_key_string)};
        Message[i] = temp_key;
    }
    InPutFile.close();



    *x = Message[0];
    *y = Message[1];

    for (int i = 0; i < PrivateKey; i++)
    {
        PointAddition(XofG, YofG, x, y, nx, ny);
    }

    long double SymmetricKeyPrivate[2] = {*x, *y};
    //SymmetricKeyPrivate = Message * PrivateKey; done above

    // setting sym key to key 1
    Key1 = SymmetricKeyPrivate[0];
    Key2 = SymmetricKeyPrivate[1];

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
    SymKeyPrivateCreation(Newx, Newy, &Cx, &Cy, PrivateKey);

    // define path for file and output the x key to the file
    const char *PATH="C:\\Pacemaker-Cryptosystem\\Code\\AES Code\\AES_input_files\\key_exchange_private_side.txt";
    std::ofstream OutPutFile;
    OutPutFile.open(PATH, std::ios_base::app);
    OutPutFile << std::fixed << std::setprecision(37) << Key1;
    cout << Key1 << endl;
    cout << Key2;
    
    return 0;
}