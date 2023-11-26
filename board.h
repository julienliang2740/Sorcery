#ifndef __BOARD__
#define __BOARD__

#include <iostream>
#include <string>
#include <vector>
#include "player.h"

class Board {
    vector<int> p1Minions;
    vector<int> p2Minions;
    Player * player1;
    Player * player2;
    int activePlayerID;
    // ritual * p1Ritual; WILL UNCOMMENT ONCE RITUALS ARE IMPLEMENTED
    // ritual * p2Ritual;
    vector<int> p1Graveyard, p2Graveyard;
    vector<int> observers;

    public:
        void addObserver(int n);
        int endTurn();
        bool addMinion(int minion);
        bool playCard(int i, int p = -1, int t = -1);
        int checkWinState();
        Board();
}

#endif
