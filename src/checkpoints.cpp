// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // Yo dawg, this is the secret. Checkpoint 0 hash == Genesis block hash.
        (         0, uint256("0xb640fb4d0621c762295a42e3f9b28247d0c0454bc71674c515f3cdc2cc934597"))
		(       100, uint256("8ffb2f9d7e0d28b9a3d0da00eb81cd2addb1abe713c9430952bf832cfbdbf6a4"))
		(	    500, uint256("d21b49c566847ee8c8b4e86887d5338ec22383f30798efdd97e3ae379e99def2"))
		(	   1000, uint256("8aa053e95dd7d44f6e6dd93a49e66981ba65b44d130fb863d1d27d7fc7fd4f24"))
		(	   1500, uint256("d4cb6d4d34503ef6378b170ec4b5bed6e100e643b914894000b8b95e1c20d892"))
		(     10000, uint256("6a8903ee78dbfa677e30085aa6b6f28a23bbcd23468620f7d85c4f95c613b4b9"))
		;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
