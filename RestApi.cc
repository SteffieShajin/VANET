/*
* This code is used as the C++ code for executing 
* the different transactions for the Blockchain - REST API 
* calls. You can use this code with the veins application 
* to execute the different transactions.
*/

#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"
#include "/usr/include/crypto++/files.h"
#include "/usr/include/crypto++/hex.h"
#include <iostream>
#include <vector> 
#include <sstream>
#include <fstream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <fstream>
#include <random>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace CryptoPP;
using namespace std; 

bool verifyPseudnm(std::string pnm)
{
    http_client client(std::string("http://localhost:3000/api/queries/selectAllValidVehicles?PIDParam=")+pnm);
    http_response response = client.request(methods::GET).get();
    if(response.status_code() == status_codes::OK)
    {
        utility::string_t body = response.extract_string().get();
        std::cout << "Vehicle details: " << body << std::endl;
        if(body.compare("[]")==0)
            return false;
        string_t value = body.substr(49, 8);
        std::cout<< "Number: " << value << std::endl;
        if(pnm.compare(value)==0)
            return true;
    }
    return false;
}

void registerVehicle(string_t vin, std::string pnm1, std::string pnm2, std::string pnm3)
{
    http_client client(std::string("http://localhost:3000/api/VehicleReg"));
    json::value json_v ;
    json_v["$class"] = json::value("org.vanet1.mynetwork.VehicleReg");
    json_v["VIN"] = json::value(vin);
    json_v["PID"] = json::value(pnm1);
    json_v["PID2"] = json::value(pnm2);
    json_v["PID3"] = json::value(pnm3);
    http_response response = client.request(methods::POST, std::string("/"), json_v).get();
    if(response.status_code() == status_codes::OK)
    {
        printf("VehicleReg Posted successfully\n");
    }
    else
    {
        printf("VehicleReg POST unsuccessful\n");
        const utility::string_t body = response.extract_string().get();
        std::cout << body << std::endl;
    }

}

void registerVehiclePID(std::string pnm1, std::string pk, int atk)
{
    http_client client(std::string("http://localhost:3000/api/Vehicle"));
    json::value json_v ;
    json_v["$class"] = json::value("org.vanet1.mynetwork.Vehicle");
    json_v["PID"] = json::value(pnm1);
    json_v["PK"] = json::value(pk);
    json_v["status"] = json::value("valid");
    json_v["misbehaviorRpt"] = json::value(atk);

    http_response response = client.request(methods::POST, std::string("/"), json_v).get();
    if(response.status_code() == status_codes::OK)
    {
        printf("Vehicle Posted successfully\n");
    }
    else
    {
        printf("Vehicle POST unsuccessful\n");
        const utility::string_t body = response.extract_string().get();
        std::cout << body << std::endl;
    }
}

int findVal(int arr[], int j, int k, int l) 
{ 
	int m; 
	while (k < l) 
	{ 
		m = k + ((l - k) >> 1); 
		(j > arr[m]) ? (k = m + 1) : (l = m); 
	} 
	return (arr[k] >= j) ? k : -1; 
} 


int myRand(int arr[], int f[], int p) 
{ 
	int pre[p], i; 
	pre[0] = f[0]; 
	for (i = 1; i < p; ++i) 
		pre[i] = pre[i - 1] + f[i]; 

	// prefix[n-1] is sum of all frequencies. 
	// Generate a random number with 
	// value from 1 to this sum
	srand (time(NULL)); 
	int j = (rand() % pre[p - 1]) + 1; 

	// Find index of ceiling of r in prefix array 
	int ind = findVal(pre, j, 0, p - 1); 
	return arr[ind]; 
}

//This code will generate n no. of vehicles in a sequencial order
//in the Blockchain. Ensure that you have generated n no. of PK using the code file - GeneratePK_SK.cc
bool createInputBC(int n){
    std::string vid = "1USWE1GHTY7";
    long num = 800000;
    long pid1 = 21000000, pid2 = 31000000, pid3 = 41000000;
    ifstream rfile ("stringPK.dat", ios::in|ios::binary);

    int arr[] = {0,1}; 
    int f[] = {29,25}; 
    int i, p = sizeof(arr) / sizeof(arr[0]);
    srand(time(NULL)); 

    for(int i=0; i<n;i++){
        std::string pt;
        getline(rfile,pt) ;        
        if(i==0){
            continue;
        }
        else{
            int att = myRand(arr, f, p);
            num++, pid1++, pid2++, pid3++;
            std::string sVID = vid + to_string(num);
            registerVehicle(sVID,to_string(pid1), to_string(pid2), to_string(pid3));
            registerVehiclePID(to_string(pid1), pt, att);
        }
    }
    rfile.close();
}

int main(int argc, const char* argv[])
{
    createInputBC(55);
    if(verifyPseudnm("21000044"))
        std::cout<<"Valid vehicle"<<std::endl;
    else
    {
        std::cout<<"Invalid vehicle"<<std::endl;
    }        
    return 0;
    
}
