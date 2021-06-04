# VANET Authentication Using Blockchain

The blockchain network used is the Hyperledger Fabric supported by the Hyperledger Composer Framework.

To install Hyperledger Composer: https://hyperledger.github.io/composer/latest/installing/installing-index.html

# Veins Documentation

Veins is the open source vehicular network simulation framework.

Documentation for the veins modules is at http://veins.car2x.org/

To compile the Veins file and RestAPI file, downloaded the C++ Rest SDK from - https://github.com/microsoft/cpprestsdk

When compiling the file, included these additional command line arguments: -lboost_system -lcrypto -lssl -lcpprest

Also, imported the following libraries in OMNET++ (Menu - Project-> Properties-> Paths and Symbols): boost_system, crypto, ssl, cpprest

The Crypto++ library was installed from - https://www.cryptopp.com/

# Generate Certificates And Signatures

The ECDSA signatures for Blockchain framework - https://www.cryptopp.com/wiki/Elliptic_Curve_Digital_Signature_Algorithm

To install Crypto++ library - https://www.cryptopp.com/

# Rest API file

The RestAPI.cc file contains the functions for different transactions in the Blockchain network which includes vehicle generation, assigning public & private keys, and malicious/attacker vehicles generation.
