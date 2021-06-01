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

#ifndef TraCIDemoRSU11p_H
#define TraCIDemoRSU11p_H

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std::chrono;

using CryptoPP::ECDSA;
using CryptoPP::ECP;
using CryptoPP::AutoSeededRandomPool;

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;

/**
 * Small RSU Demo using 11p
 */
class TraCIDemoRSU11p : public BaseWaveApplLayer {
	protected:
		virtual void onWSM(WaveShortMessage* wsm);
		virtual void onWSA(WaveServiceAdvertisment* wsa);
		static int lastPID;
		static Coord lastPos;
		static long totalBSMs;
		static double totalDuration;
		static long totalWSAs;
	public:
		virtual void onBSM(BasicSafetyMessage* bsm);
		virtual void printValues();
};

#endif
