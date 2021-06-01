# vanet1-network

The blockchain network used for the proposed method in VANET.

Go to: https://hyperledger.github.io/composer/latest/installing/installing-index.html and install the Hyperledger Composer framework.

I had errors when trying to install it in Virtual Operating System, but faced no trouble installing it in a system with local OS as Ubuntu.

To develop a business network, follow the instructions in: https://hyperledger.github.io/composer/latest/tutorials/developer-tutorial.
In step 2, you will be required to define the modelling assets, participants, and transactions which can be found in: vanetNetwork/models/org.vanet1.mynetwork.cto file. You will also be needed to provide JavaScript transaction logic (chaincode), which can be found in: vanetNetwork/lib/logic.js. The access permissions can be found in vanetNetwork/permissions.acl and the query can be found in: vanetNetwork/queries.qry.
