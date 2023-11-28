#ifndef __BOARD__
#define __BOARD__

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "minioncomponent.h"
#include "minion.h"

class Board {
    Minion* deleteEnchantments(int ownershipID, int minion);
    bool moveMinionToGraveyard(int ownershipID, int minion);
    public:
        std::vector<MinionComponent*> p1Minions;
        std::vector<MinionComponent*> p2Minions;
        int activePlayerID;
        // ritual * p1Ritual; WILL UNCOMMENT ONCE RITUALS ARE IMPLEMENTED
        // ritual * p2Ritual;
        std::vector<Minion*> p1Graveyard, p2Graveyard;
        std::vector<int> observers;
        
        bool placeMinion(std::vector<MinionComponent*>& minions, Minion* minion);
    
        Player* player1;
        Player* player2;

        Board(
            std::vector<MinionComponent*> p1Minions, std::vector<MinionComponent*> p2Minions, 
            Player* player1, Player* player2, 
            int activePlayerID,
            std::vector<Minion*> p1Graveyard, std::vector<Minion*> p2Graveyard);
        int getActiveID();
        void addObserver(int n);
        int endTurn();
        bool addMinion(Minion* minion);
        bool playCard(int i, int p = -1, int t = -1);
        int checkWinState();
        bool attackMinion(int curMinion, int target);
        Board();

        
};

#endif
