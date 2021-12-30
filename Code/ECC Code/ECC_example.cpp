/*
   Functions created need no inputs as they reference the
   specific variables within themselves.
   Therefore, consider removing the parameters to all functions.
*/


#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Variable setup - Feel free to change
int PrivateKey = 10;
int GeneratorPoint = 15;
int UpperRandom = 100;

// Other variable setup - Leave unchanged
int PublicKey;
int RandomVariable;
int Message;
int SymmetricKeyPublic;
int SymmetricKeyPrivate;

// Key pair generation function
void PublicKeyGeneration(int PrivateKey, int GeneratorPoint)
{
    // multiply both together to get public key
    PublicKey = PrivateKey * GeneratorPoint;

    // print out variable information
    cout << "your private key is: " << PrivateKey << endl;
    cout << "your public key is: " << PublicKey << endl;
    cout << "your generator point is: " << GeneratorPoint << endl;
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
void MessageCreator(int RandomVariable, int GeneratorPoint)
{
    Message = RandomVariable * GeneratorPoint;
    
    // inform of transmitted message
    cout << "the message transmitted is: " << Message << endl;
}

// Create symmetric key using public key
void SymKeyPublicCreation(int RandomVariable, int PublicKey)
{
    SymmetricKeyPublic = RandomVariable * PublicKey;

    // inform recipient of public key of their generated symmetric key
    cout << "the symmetric key you have created but have kept hidden is: " << SymmetricKeyPublic << endl;
    cout << "NOTE, the above key is only known to the recipient of the public key" << endl;
}

// Determine the symmetric key using the private key
void SymKeyPrivateCreation(int Message, int PrivateKey)
{
    SymmetricKeyPrivate = Message * PrivateKey;

    // inform creator of private key of their generated symmetric key
    cout << "the symmetric key you have created but have kept hidden is: " << SymmetricKeyPrivate << endl;
    cout << "NOTE, the above key is only known to the creator of the private key" << endl;
}


// main function
int main()
{
    PublicKeyGeneration(PrivateKey, GeneratorPoint);
    RandomNumberGeneration(UpperRandom);
    MessageCreator(RandomVariable, GeneratorPoint);
    SymKeyPublicCreation(RandomVariable, PublicKey);
    SymKeyPrivateCreation(Message, PrivateKey);
    cout << "if the two seperately symmetric keys are the same, then the process has performed a key exchange" << endl;
    return(1);
}