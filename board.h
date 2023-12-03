#ifndef __BOARD__
#define __BOARD__

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "minioncomponent.h"
#include "minion.h"
#include "enchantment.h"

class Observer;

class Board {
    Minion* deleteEnchantments(int ownershipID, int minion);
    bool moveMinionToGraveyard(int ownershipID, int minion);
    public:
        std::vector<MinionComponent*> p1Minions;
        std::vector<MinionComponent*> p2Minions;
        int activePlayerID;

        // Delinquent code:
        Ritual * p1Ritual;
        Ritual * p2Ritual;

        std::vector<Minion*> p1Graveyard, p2Graveyard;
        std::vector<Observer*> observers;
        
        bool placeMinion(std::vector<MinionComponent*>& minions, Minion* minion);
    
        Player* player1;
        Player* player2;

        Board(
            std::vector<MinionComponent*> p1Minions, std::vector<MinionComponent*> p2Minions, 
            Player* player1, Player* player2, 
            int activePlayerID,
            std::vector<Minion*> p1Graveyard, std::vector<Minion*> p2Graveyard);
        int getActiveID();
        void addObserver(Observer* o);
        int endTurn();
        bool addMinion(Minion* minion);
        bool playCard(int i, int p = -1, int t = -1);
        int checkWinState();
        bool attackMinion(int curMinion, int target);
        bool useActivatedAbility(int minionUser, int targetPlayerID = -1, int targetMinion = -1);
        Board();
        Player* getActivePlayer();
        void attackPlayer(int minion);
        void destroyMinion(int player, int minion); // int minion is NOT zero-indexed     
};

#endif
