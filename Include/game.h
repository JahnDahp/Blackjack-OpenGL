#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include "Shoe.h"
#include "player.h"
#include "dealer.h"
#include "button.h"

class Game 
{
  public:
    static const int DECK_SIZE = 52;
    Game();
    Game(bool f);
    void play();
    bool continuePlay();
    void decision();
    std::string getDecision(Player player, Dealer dealer, bool firstDecision, int currentSplit);
    std::string getButtonPress();
    void dealerTotal(Dealer dealer, bool end);
    void playerTotal(Player player);
    void outcome(std::vector<Player> splits, Dealer dealer, std::string decision);
    void winLoseDraw(Dealer dealer, Player player);
    void updateButtons(glm::mat4 projection);
  private:
    bool threeToTwo;
    bool H17;
    int decks;
    bool doubleAny;
    int doubles[3];
    bool DAS;
    int numberOfSplits;
    bool drawSplitAces;
    bool resplitAces;
    bool surrender;
    double penetration;
    Shoe shoe;
    Card discard;
    Button hitButton = Button("Hit");
    Button standButton = Button("Stand");
    Button splitButton = Button("Split");
    Button doubleButton = Button("Double");
    Button surrenderButton = Button("Surrender");
    bool showHit;
    bool showStand;
    bool showSplit;
    bool showDouble;
    bool showSurrender;
};
