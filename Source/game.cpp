#include "game.h"
#define ASK(x, y) std::cout << x; std::cin >> y; std::cout << "\n"
#define LOG(x) std::cout << x << "\n"
#define SLEEP(x) std::this_thread::sleep_for(std::chrono::seconds(x));

Game::Game() {
  threeToTwo = true;
  H17 = false;
  decks = 1;
  doubleAny = true;
  doubles[0] = -1;
  doubles[1] = -1;
  doubles[2] = -1;
  DAS = true;
  numberOfSplits = 3;
  drawSplitAces = false;
  resplitAces = true;
  surrender = true;
  penetration = 0.5/(float)decks;
  shoe = Shoe(decks);
  discard = Card();
  showHit = showStand = showSplit = showDouble = showSurrender = false;
}

Game::Game(bool f) : Game() {

  std::string input;
  ASK("Does Blackjack play 3 to 2? (Y/N) ", input);
  if (input != "Y") threeToTwo = false;
  ASK("Does the dealer hit on soft 17? (Y/N) ", input);
  if (input == "Y") H17 = true;
  ASK("How many decks are in the shoe? ", decks);
  ASK("Can you double on any two cards? (Y/N) ", input);
  if (input == "Y") doubleAny = true;
  else 
  { 
    doubleAny = false; 
    ASK("What card totals can you double on? Say '-1' if all totals have been entered. ", input);
    for (int i = 0; std::stoi(input) != -1 && i < 3; i++) 
    {
      doubles[i] = std::stoi(input);
      ASK("Any more card totals? ", input);
    }
  }
  ASK("Can you double after splitting? (Y/N) ", input);
  if (input != "Y") DAS = false;
  ASK("How many times can you split? ", numberOfSplits);
  if (numberOfSplits > 0) 
  {
    ASK("Can you draw on split aces? (Y/N) ", input);
    if (input == "Y") drawSplitAces = true;
    else 
    {
      ASK("Can you resplit aces? (Y/N) ", input);
      if (input != "Y") resplitAces = false;
    }
  }
  ASK("Can you surrender? (Y/N) ", input);
  if (input != "Y") surrender = false;
  ASK("What is the deck penetration? ", penetration);
  shoe = Shoe(decks);
  discard = Card();
}

void Game::play() {
  while (continuePlay())
  {
    decision();
  }
}

bool Game::continuePlay() {
  char input = 'Y';
  float shoePercentLeft = (float)shoe.size() / (float)(DECK_SIZE * decks);
  if (shoePercentLeft < penetration) 
  {
    LOG("Shuffling...\n");
    SLEEP(1);
    shoe = Shoe(decks);
    LOG("Discarding...\n");
    SLEEP(1);
    discard = shoe.topPop();
    ASK("Would you like to play? (Y/N) ", input);
  }
  return input == 'Y' ? true : false;
}

void Game::decision() {
  std::string decision;
  std::vector<Player> splits;
  int i = 0;
  int currentSplit = 0;
  Card P1 = shoe.topPop();
  Card DU = shoe.topPop();
  Card P2 = shoe.topPop();
  Card DH = shoe.topPop();
  splits.push_back(Player(P1, P2));
  Dealer dealer(DU, DH);
  while (i < splits.size()) {
    SLEEP(1);
    dealerTotal(dealer, false);
    SLEEP(1);
    playerTotal(splits[i]);
    SLEEP(1);
    decision = getDecision(splits[i], dealer, true, currentSplit);
    while (decision == "Hit") {
      std::cout << "\n";
      SLEEP(1);
      splits[i].hit(shoe.topPop());
      dealerTotal(dealer, false);
      SLEEP(1);
      playerTotal(splits[i]);
      SLEEP(1);
      if (splits[i].bust()) {
        std::cout << "Bust!\n";
        SLEEP(1);
        decision = "BUST";
      } else {
        decision = getDecision(splits[i], dealer, false, currentSplit);
      }
    }
    if (decision == "Double") {
      std::cout << "\n";
      SLEEP(1);
      splits[i].hit(shoe.topPop());
      dealerTotal(dealer, false);
      SLEEP(1);
      playerTotal(splits[i]);
      SLEEP(1);
      if (splits[i].bust()) {
        std::cout << "Bust!\n";
        SLEEP(1);
        decision = "BUST";
      }
    }
    if (decision == "Split") {
      Card temp = splits[i].split(shoe.topPop());
      splits.push_back(Player(temp, shoe.topPop()));
      currentSplit++;
      i--;
    }
    i++;
    std::cout << "\n";
  }
  outcome(splits, dealer, decision);
}
std::string Game::getDecision(Player player, Dealer dealer, bool firstDecision, int currentSplit)
{
  showHit = true;
  showStand = true;
  showSplit = false;
  showDouble = false;
  showSurrender = false;

  if (dealer.total() > 20) return "DEALER_21";
  if (player.total() > 20) return "BUST";
  if (!firstDecision) return getButtonPress();

  showSplit = (numberOfSplits != 0) && (currentSplit < numberOfSplits) && (player.first().canSplit(player.second()));
  showSurrender = surrender;
  showDouble = doubleAny;
  if (showDouble) return getButtonPress();
  for (int i : doubles) 
  {
    showDouble = i == player.total();
    if (showDouble) break;
  }
  return getButtonPress();
}

std::string Game::getButtonPress()
{
  return "";
}

void Game::dealerTotal(Dealer dealer, bool end) {
  if (end) {
    std::cout << "Dealer: ";
    for (Card card : dealer.allCards()) {
      if (card == dealer.allCards().back()) {
        std::cout << card << "\n";
      }
      else {
        std::cout << card << ", ";
      }
    }
    if (dealer.isSoft()) {
      std::cout << "Total: Soft " << dealer.total() << "\n";
    }
    else {
      std::cout << "Total: " << dealer.total() << "\n";
    }
  } else {
    std::cout << "Dealer: " << dealer.up() << "\nTotal: " << dealer.up().total() << "\n";
  }
}

void Game::playerTotal(Player player) {
  std::cout << "Player: ";
  // Fix logic for same card in different deck
  for (Card card : player.allCards()) {
    if (card == player.allCards().back()) {
      std::cout << card << "\n";
    }
    else {
      std::cout << card << ", ";
    }
  }
  if (player.isSoft()) {
    std::cout << "Total: Soft " << player.total() << "\n";
  }
  else {
    std::cout << "Total: " << player.total() << "\n";
  }
}

void Game::outcome(std::vector<Player> splits, Dealer dealer, std::string decision) {
  bool noDraw = true;
  for (Player player : splits) {
    if (!player.bust() && !player.naturalBlackjack() && decision != "Surrender") {
      noDraw = false;
      break;
    }
  }
  dealerTotal(dealer, false);
  SLEEP(1);
  dealerTotal(dealer, true);
  SLEEP(1);
  while ((dealer.total() < 17 || (dealer.total() == 17 && dealer.isSoft())) && !noDraw && !dealer.naturalBlackjack()) {
    if (dealer.total() == 17 && !H17) {
      break;
    }
    dealer.hit(shoe.topPop());
    dealerTotal(dealer, true);
    SLEEP(1);
  }
  std::cout << "\n";
  for (Player player : splits) {
    playerTotal(player);
    SLEEP(1);
    winLoseDraw(dealer, player);
    SLEEP(1);
  }
  std::cout << "\n";
}

void Game::winLoseDraw(Dealer dealer, Player player) {

}

void Game::updateButtons(glm::mat4 projection)
{
  int buttonsShown = showHit + showStand + showSplit + showDouble + showSurrender;
  float yPos = (float)(buttonsShown - 1);
  if (showHit)
  {
    hitButton.transform(-4.0f / 5.0f, yPos / 10.0f, 0.2f, 0.2f);
    hitButton.draw(projection);
    yPos -= 2.0f;
  }
  if (showStand)
  {
    standButton.transform(-4.0f / 5.0f, yPos / 10.0f, 0.2f, 0.2f);
    standButton.draw(projection);
    yPos -= 2.0f;
  }
  if (showSplit)
  {
    splitButton.transform(-4.0f / 5.0f, yPos / 10.0f, 0.2f, 0.2f);
    splitButton.draw(projection);
    yPos -= 2.0f;
  }
  if (showDouble)
  {
    doubleButton.transform(-4.0f / 5.0f, yPos / 10.0f, 0.2f, 0.2f);
    doubleButton.draw(projection);
    yPos -= 2.0f;
  }
  if (showSurrender)
  {
    surrenderButton.transform(-4.0f / 5.0f, yPos / 10.0f, 0.2f, 0.2f);
    surrenderButton.draw(projection);
    yPos -= 2.0f;
  }
}
