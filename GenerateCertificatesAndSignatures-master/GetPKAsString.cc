/*
* This code is used to generate the PK as a
* string. This is required in my proposed method
* to store the PK in the blockchain as string is
* is only datatype for PK that is supported in 
* Hyperledger Composer. All the PK are stored in the
* file stringPK.dat.
*/

#include <iostream>
#include <vector> 
#include <sstream>
#include <fstream>
#include <string>
#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"
#include "/usr/include/crypto++/files.h"
#include "/usr/include/crypto++/hex.h"

using namespace CryptoPP;
using namespace std; 

int main(int argc, const char* argv[]) 
{   
    ECDSA<ECP, SHA256>::PublicKey publicKey;
    FileSource fs2( "public.ec.der", true  );
    AutoSeededRandomPool prng;
    ECDSA<ECP, SHA256>::PrivateKey k;
    FileSource fs1( "private.ec.der", true  );
    ofstream wfile;
    wfile.open("stringPK.dat", ios::out|ios::binary);

    for (int i=0; i<105;i++){
        publicKey.Load( fs2 );
        const ECP::Point& q = publicKey.GetPublicElement();
        const Integer& qx = q.x;
        const Integer& qy = q.y;

        std::stringstream ss ;
        ss<<std::hex<<q.x<<q.y;
        std::string pt = ss.str();          // is the string to be stored in the BC as the Public Key
        
        wfile<<pt<<std::endl;
    }
    wfile.close();
    return 0;
}
