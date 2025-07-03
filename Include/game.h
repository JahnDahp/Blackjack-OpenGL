#pragma once

#include <algorithm>
#include "shoe.h"
#include "player.h"
#include "dealer.h"
#include "choiceButton.h"
#include "playButton.h"
#include "ArrowButton.h"
#include "rules.h"
#include "text.h"

class Game 
{
  public:
    enum Choice 
    {
      NONE = -1,
      HIT = 0,
      STAND = 1,
      DOUBLE = 2,
      SPLIT = 3,
      SURRENDER = 4,
      INSURANCE = 5,
      NO_INSURANCE = 6,
      PLAY_GAME = 7,
    };
    static const int DECK_SIZE = 52;
    Game(const Rules& gameRules, int roll, int firstBet);
    void renderPlayers(const glm::mat4& proj, const glm::mat4& view);
    void renderDealer(const glm::mat4& proj, const glm::mat4& view);
    void renderButtons(const glm::mat4& proj, const glm::mat4& view, float aspect);
    void renderLabels(const glm::mat4& proj, float aspect);
    void render(const glm::mat4& proj, const glm::mat4& view, float aspect);
    void startHand();
    void playGame();
    void endHand();
    void showButtons();
    void getChoice();
    void tryButtonPress(const glm::vec2& worldCoords);
    void resetHandGraphics();
    void resetGraphics();
    void winLoss(bool isNatural21);
    bool initialWinLoss(bool isNatural21);
    void dealerHit(bool isNatural21);
    void runInsurance();
    bool isExited() const;
  private:
    Rules rules;
    std::vector<std::unique_ptr<ChoiceButton>> choiceButtons;
    std::unique_ptr<PlayButton> playButton;
    Shoe shoe;
    std::unique_ptr<Card> discard;
    std::vector<std::unique_ptr<Player>> players;
    int currentHand;
    std::unique_ptr<Dealer> dealer;
    std::unique_ptr<Text> initialBetLabel;
    std::unique_ptr<Text> bet5Label;
    std::unique_ptr<Text> bet25Label;
    std::unique_ptr<Text> bet100Label;
    std::unique_ptr<Text> bankrollLabel;
    std::unique_ptr<Text> gainLabel;
    std::unique_ptr<Text> shuffleLabel;
    std::vector<std::unique_ptr<ArrowButton>> bettingButtons;
    int choice;
    float bankroll;
    float initialBet;
    bool surrendered;
    bool insured;
    bool exit;
};
