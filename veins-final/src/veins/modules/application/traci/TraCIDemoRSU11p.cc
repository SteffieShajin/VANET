//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "veins/modules/application/traci/TraCIDemoRSU11p.h"

Define_Module(TraCIDemoRSU11p);
int TraCIDemoRSU11p::lastPID = 0;
Coord TraCIDemoRSU11p::lastPos = {0.0,0.0,0.0};
long TraCIDemoRSU11p::totalBSMs = 0;
double TraCIDemoRSU11p::totalDuration = 0.0;
long TraCIDemoRSU11p::totalWSAs = 0;

void TraCIDemoRSU11p::onWSA(WaveServiceAdvertisment* wsa) {
    //if this RSU receives a WSA for service 42, it will tune to the chan
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(wsa->getTargetChannel());
    }
}

void TraCIDemoRSU11p::onWSM(WaveShortMessage* wsm) {
    //this rsu repeats the received traffic update in 2 seconds plus some random delay
    //wsm->setSenderAddress(myId);
      sendDelayedDown(wsm->dup(), 2 + uniform(0.01,0.2));
}

void TraCIDemoRSU11p::onBSM(BasicSafetyMessage* bsm) {

    std::clock_t start, start1, start2;
    double duration, duration1, duration2;
    start2 = std::clock();

    totalBSMs++;

    if(bsm->getSenderPos()==lastPos && bsm->getSenderAddress()==lastPID) {
         return void();
    }

    CryptoPP::ECDSA<ECP, CryptoPP::SHA256>::PublicKey publicKey = bsm->getSenderPK();
    const CryptoPP::ECP::Point& q = publicKey.GetPublicElement();
    const CryptoPP::Integer& qx = q.x;
    const CryptoPP::Integer& qy = q.y;

    std::stringstream ss;
    ss<<std::hex<<q.x<<q.y;
    std::string pk = ss.str();
    std::string pnm = to_string(bsm->getSenderAddress());

    start1 = std::clock();
    if(this->verifyPKSignature(bsm)) {

    }

    http_client client(std::string("http://localhost:3000/api/queries/selectAllValidVehicles?PIDParam=")+pnm);
    http_response response = client.request(methods::GET).get();
    if(response.status_code() == status_codes::OK)
    {
       utility::string_t body = response.extract_string().get();
       string_t value1 = body.substr(49, 8);
       string_t value3 = body.substr(231,1);

       if(value3=="1"){
           WaveServiceAdvertisment* wsa = new WaveServiceAdvertisment();
           this->populateWSM(wsa);
           wsa->setValidPID(bsm->getSenderAddress());
           wsa->setValidPK(pk);
           cancelEvent(wsa);
           scheduleAt(simTime()+dblrand()*0.1, wsa);

           totalWSAs++;

           this->lastPID = bsm->getSenderAddress();
           this->lastPos = bsm->getSenderPos();
           duration = (std::clock()-start1)/(double)CLOCKS_PER_SEC;
           totalDuration += duration;
       }
    }
}


void TraCIDemoRSU11p::printValues() {
    std::cout<<"Total Warning Messages: "<<totalWSAs<<std::endl;
    std::cout<<"Total BSMs: "<<totalBSMs<<std::endl;
    std::cout<<"Total Duration for Authentication is: "<<totalDuration<<std::endl;
}
