/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

'use strict';
/**
 * Write your transction processor functions here
 */

/**
 * Sample transaction processor function.
 * @param {org.vanet1.mynetwork.Misbehavior} mb The sample transaction instance.
 * @transaction
 */
async function Misbehavior(mb) {  // eslint-disable-line no-unused-vars

    mb.car.misbehaviorRpt++;
  	// If the misbehaviour report is more than 3 then the vechile is revoked.
  	if(mb.car.misbehaviorRpt >= 3){
  		mb.car.status = "revoked";
    }
  	// Get the asset registry for the asset.
    const assetRegistry = await getAssetRegistry('org.vanet1.mynetwork.Vehicle');
    // Update the asset in the asset registry.
    await assetRegistry.update(mb.car);
}

/**
 * Sample transaction processor function.
 * @param {org.vanet1.mynetwork.Revocation} rv The sample transaction instance.
 * @transaction
 */
async function Revocation(rv) {  // eslint-disable-line no-unused-vars

    rv.car.status = "revoked";
    // Get the asset registry for the asset.
    const assetRegistry = await getAssetRegistry('org.vanet1.mynetwork.Vehicle');
    // Update the asset in the asset registry.
    await assetRegistry.update(rv.car);
}

/**
 * Sample transaction processor function.
 * @param {org.vanet1.mynetwork.Readmission} ra The sample transaction instance.
 * @transaction
 */
async function Readmission(ra) {  // eslint-disable-line no-unused-vars

    ra.car.PID = ra.pseudo1;
    ra.car.PID2 = ra.pseudo2;
    ra.car.PID3 = ra.pseudo3;
    // Get the asset registry for the asset.
    const assetRegistry = await getAssetRegistry('org.vanet1.mynetwork.VehicleReg');
    // Update the asset in the asset registry.
    await assetRegistry.update(ra.car);
}
