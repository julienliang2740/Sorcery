#ifndef __BOARD__
#define __BOARD__

#include <iostream>
#include <string>
#include <vector>
#include "player.h"

class Board {
    std::vector<int> p1Minions;
    std::vector<int> p2Minions;
    Player * player1;
    Player * player2;
    int activePlayerID;
    // ritual * p1Ritual; WILL UNCOMMENT ONCE RITUALS ARE IMPLEMENTED
    // ritual * p2Ritual;
    std::vector<int> p1Graveyard, p2Graveyard;
    std::vector<int> observers;
    bool placeMinion(std::vector<int>& minions, int minion);
    
    public:
        void addObserver(int n);
        int endTurn();
        bool addMinion(int minion);
        bool playCard(int i, int p = -1, int t = -1);
        int checkWinState();
        Board();
};

#endif
