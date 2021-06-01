/*
* This code generates 55 sets of Public Keys and Private keys
* and stores them in the files: public.ec.der and private.ec.der
* respectively.
*/

#include <iostream>
#include <sstream>
#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"
#include "/usr/include/crypto++/files.h"

using namespace CryptoPP;

int main(int argc, const char* argv[]) 
{
    AutoSeededRandomPool prng;
    FileSink fs1( "private.ec.der", true /*binary*/ );
    FileSink fs3( "public.ec.der", true /*binary*/ );
    int i = 0;
    while (i<105){
        ECDSA<ECP, SHA256>::PrivateKey k;
        k.Initialize( prng, ASN1::secp256r1() );

        ECDSA<ECP, SHA256>::PublicKey publicKey;
        k.MakePublicKey(publicKey);
        const ECP::Point& q = publicKey.GetPublicElement();
        const Integer& qx = q.x;
        const Integer& qy = q.y;
        std::stringstream ssx, ssy ;
        ssx << std::hex << q.x ;
        ssy << std::hex << q.y ;
        std::string pt1 = ssx.str();
        std::string pt2 = ssy.str();
        if(pt1.length()==65 && pt2.length()==65){
            std::cout<<"Done"<<std::endl;
            publicKey.Save( fs3 );
            k.Save( fs1 );
            i++;
        }
    }

    return 0;
}
