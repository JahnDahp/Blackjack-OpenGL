#include "game.h"

static float centerFunction(float x, float n)
{
  return (x - ((n - 1.0f) / 2.0f));
}
static std::string floatToString(float value, int precision = 2) 
{
  int intPart = (int)value;
  float frac = std::abs(value - intPart);
  std::string result = std::to_string(intPart);
  if (precision > 0) 
  {
    frac = std::round(frac * std::pow(10, precision));
    if (frac > 0) 
    {
      result += '.';
      while (precision > 1 && frac < std::pow(10, precision - 1)) 
      {
        result += '0';
        precision--;
      }
      result += std::to_string((int)frac);
    }
  }
  return result;
}

Game::Game(const Rules& gameRules, int roll, int firstBet) 
  : rules(gameRules),
  initialBet(firstBet),
  bankroll(roll - firstBet),
  discard(nullptr),
  dealer(nullptr),
  choice(PLAY_GAME),
  currentHand(0),
  surrendered(false),
  insured(false),
  exit(false)
{
  for (int i = 0; i < PLAY_GAME; i++)
  {
    choiceButtons.push_back(std::make_unique<ChoiceButton>(i));
    choiceButtons[i]->init();
  }
  playButton = std::make_unique<PlayButton>();

  initialBetLabel = std::make_unique<Text>("../Resources/Fonts/SF.otf", "", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  bet5Label = std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bet 5", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  bet25Label = std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bet 25", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  bet100Label = std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bet 100", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  bankrollLabel = std::make_unique<Text>("../Resources/Fonts/SF.otf", "", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  gainLabel = std::make_unique<Text>("../Resources/Fonts/SF.otf", "", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  shuffleLabel = std::make_unique<Text>("../Resources/Fonts/SF.otf", "New Shuffle Next Hand", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  for (int i = 0; i < 3; i++)
  {
    bettingButtons.push_back(std::make_unique<ArrowButton>());
    bettingButtons[i]->init();
  }
  playButton->init();
} 
void Game::renderPlayers(const glm::mat4& proj, const glm::mat4& view)
{
  for (int j = 0; j < players.size(); j++)
  {
    float x = 0.0f;
    if (currentHand >= players.size()) x = 0.75f * centerFunction((float)j, (float)players.size());
    else x = ((float)j - (float)currentHand);
    for (int i = 0; i < players[j]->getCards().size(); i++)
    {
      Card* card = players[j]->getCard(i);
      card->transform(x + (i * 0.1f), -0.45f + (i * 0.1f), 0.25f, 0.25f);
      card->render(proj, view);
    }
    Text* label = players[j]->getBetLabel();
    label->transform(x, -0.85f, 1.0f, 1.0f);
    label->render(proj);
  }
}
void Game::renderDealer(const glm::mat4& proj, const glm::mat4& view)
{
  int dealerCards = dealer->getCards().size();
  for (int i = 0; i < dealerCards; i++)
  {
    Card* card = dealer->getCard(i);
    if (i == 0 && !dealer->getCard(1)->isVisible()) card->transform(0.0f, 0.65f, 0.25f, 0.25f);
    else if (i == 0) card->transform(0.35f * centerFunction(dealerCards - 2, dealerCards), 0.65f, 0.25f, 0.25f);
    else if (i == 1) card->transform(0.35f * centerFunction(dealerCards - 1, dealerCards), 0.65f, 0.25f, 0.25f);
    else card->transform(-0.35f * centerFunction(i, dealerCards), 0.65f, 0.25f, 0.25f);
    card->render(proj, view);
  }
}
void Game::renderButtons(const glm::mat4& proj, const glm::mat4& view, float aspect)
{
  int visibleButtons = 0;
  for (auto& button : choiceButtons)
  {
    if (button->isVisible()) visibleButtons++;
  }
  int i = 0;
  for (auto& button : choiceButtons)
  {
    if (button->isVisible()) button->transform(1.0f - (aspect + 0.7f), 0.26f * -centerFunction(i++, visibleButtons), 0.25f, 0.25f);
    button->render(proj, view);
  }
  playButton->transform(1.0f - (aspect + 0.7f), 0.0f, 0.25f, 0.25f);
  playButton->render(proj, view);
  for (int i = 0; i < 3; i++)
  {
    bettingButtons[i]->transform((aspect + 0.6f) - 1.0f, 0.35f - (i * 0.1f), 0.05f, 0.05f);
    bettingButtons[i]->render(proj, view);
  }
}
void Game::renderLabels(const glm::mat4& proj, float aspect)
{
  bet5Label->transform((aspect + 0.1f) - 1.0f, 0.35f - bet5Label->getTextHeight() / 2.0f, 1.0f, 1.0f, true);
  bet25Label->transform((aspect + 0.1f) - 1.0f, 0.25f - bet25Label->getTextHeight() / 2.0f, 1.0f, 1.0f, true);
  bet100Label->transform((aspect + 0.1f) - 1.0f, 0.15f - bet100Label->getTextHeight() / 2.0f, 1.0f, 1.0f, true);
  bankrollLabel->transform((aspect + 0.1f) - 1.0f, 0.05f - bankrollLabel->getTextHeight() / 2.0f, 1.0f, 1.0f, true);
  initialBetLabel->transform((aspect + 0.1f) - 1.0f, -0.05f - initialBetLabel->getTextHeight() / 2.0f, 1.0f, 1.0f, true);
  gainLabel->transform((aspect + 0.1f) - 1.0f, -0.15f - gainLabel->getTextHeight() / 2.0f, 1.0f, 1.0f, true);
  shuffleLabel->transform(1.0f - (aspect + 0.95f), 0.28f - gainLabel->getTextHeight() / 2.0f, 1.0f, 1.0f, true);
  initialBetLabel->setText("Bet: " + floatToString(initialBet, 2));
  bankrollLabel->setText("Bankroll: " + floatToString(bankroll, 2));
  initialBetLabel->render(proj);
  bet5Label->render(proj);
  bet25Label->render(proj);
  bet100Label->render(proj);
  bankrollLabel->render(proj);
  gainLabel->render(proj);
  shuffleLabel->render(proj);
}
void Game::render(const glm::mat4& proj, const glm::mat4& view, float aspect) 
{
  renderPlayers(proj, view);
  renderDealer(proj, view);
  renderButtons(proj, view, aspect);
  renderLabels(proj, aspect);
  playGame();
}
void Game::startHand() 
{
  if ((float)shoe.size() / (float)(DECK_SIZE * rules.decks) < 1.0f - rules.pen)
  {
    shoe = Shoe(rules.decks);
    shoe.init();
    discard = shoe.topPop();
    shuffleLabel->setVisible(false);
  }
  std::unique_ptr<Card> p1 = shoe.topPop();
  std::unique_ptr<Card> d1 = shoe.topPop();
  std::unique_ptr<Card> p2 = shoe.topPop();
  std::unique_ptr<Card> d2 = shoe.topPop();
  players.clear();
  players.push_back(std::make_unique<Player>(std::move(p1), std::move(p2), initialBet));
  dealer = std::make_unique<Dealer>(std::move(d1), std::move(d2), rules.H17);
  resetHandGraphics();
  choice = NONE;
  currentHand = 0;
}
void Game::playGame()
{
  if (playButton->isVisible() && choice != PLAY_GAME) return;
  if (choice == PLAY_GAME)
  {
    for (auto& player : players) player.reset();
    players.clear();
    dealer.reset();
    startHand();
  }
  showButtons();
  getChoice();
  if (dealer->canInsure()) return;
  if (dealer->total(false) == 21 || currentHand >= players.size())
  {
    endHand();
    return;
  }
  if (players[currentHand]->total() == 21 || players[currentHand]->isBust()) currentHand++;
  
}
void Game::endHand()
{
  resetGraphics();
  bool isNatural21 = players[0]->total() == 21 && players[0]->getCards().size() == 2 && players.size() == 1;
  if (!initialWinLoss(isNatural21))
  {
    dealerHit(isNatural21);
    winLoss(isNatural21);
  }
  if (initialBet > bankroll) initialBet = (int)bankroll - ((int)bankroll % 5);
}
void Game::showButtons()
{
  for (auto& button : choiceButtons) button->setVisible(false);
  if (currentHand >= players.size()) return;
  auto& player = players[currentHand];
  if (dealer->canInsure())
  {
    choiceButtons[INSURANCE]->setVisible(true);
    choiceButtons[NO_INSURANCE]->setVisible(true);
    return;
  }
  choiceButtons[HIT]->setVisible(true);
  choiceButtons[STAND]->setVisible(true);
  if (player->getCards().size() != 2) return;
  if (rules.doubles[player->total()]) choiceButtons[DOUBLE]->setVisible(true);
  if ((!rules.DAS && players.size() > 1) || bankroll - player->getBet() < 0) choiceButtons[DOUBLE]->setVisible(false);
  if (player->canSplit() && players.size() <= rules.numSplits) choiceButtons[SPLIT]->setVisible(true);
  if (player->getCard(0)->isAce() && players.size() > 1 && !rules.drawSplitAces)
  {
    choiceButtons[HIT]->setVisible(false);
    choiceButtons[DOUBLE]->setVisible(false);
  }
  if ((!rules.resplitAces && player->getCard(1)->isAce() && players.size() > 1) || bankroll - player->getBet() < 0) choiceButtons[SPLIT]->setVisible(false);
  if (rules.surrender && players.size() == 1) choiceButtons[SURRENDER]->setVisible(true);
}
void Game::getChoice()
{
  if (currentHand >= players.size()) return;
  auto& player = players[currentHand];
  if (choice == INSURANCE)
  {
    bankroll -= player->getBet() * 0.5f;
    insured = true;
  }
  if (choice == INSURANCE || choice == NO_INSURANCE)
  {
    dealer->doInsurance(false);
    choiceButtons[INSURANCE]->setVisible(false);
    choiceButtons[NO_INSURANCE]->setVisible(false);
    choice = NONE;
    return;
  }
  if (player->getCard(0)->isAce() && players.size() > 1)
  {
    if (rules.resplitAces && players.size() > rules.numSplits) currentHand++;
    if (!(rules.resplitAces && player->getCard(1)->isAce())) currentHand++;
  }
  if (choice == HIT || choice == DOUBLE) player->hit(shoe.topPop());
  if (choice == DOUBLE)
  {
    bankroll -= player->getBet();
    player->setBet(player->getBet() * 2);
  }
  if (choice == STAND || choice == DOUBLE || choice == SURRENDER) currentHand++;
  if (choice == SURRENDER) surrendered = true;
  if (choice == SPLIT)
  {
    std::unique_ptr<Card> card1 = shoe.topPop();
    std::unique_ptr<Card> card2 = shoe.topPop();
    std::unique_ptr<Player> newPlayer = players[currentHand]->split(std::move(card1), std::move(card2));
    players.push_back(std::move(newPlayer));
    bankroll -= players[currentHand]->getBet();
  }
  choice = NONE;
}
void Game::tryButtonPress(const glm::vec2& worldCoords)
{
  for (auto& button : choiceButtons)
  {
    if (button->tryButtonPress(worldCoords)) choice = button->getValue();
  }
  if (playButton->tryButtonPress(worldCoords))
  {
    choice = PLAY_GAME;
    bankroll -= initialBet;
    if (bankroll < 0) exit = true;
    if (initialBet < 5)  exit = true;
  }
  if (bettingButtons[0]->tryButtonPressLeft(worldCoords) && initialBet >= 10)
  {
    if (initialBet - 5 >= 5) initialBet -= 5;
  }
  if (bettingButtons[0]->tryButtonPressRight(worldCoords) && bankroll >= 5)
  {
    if (bankroll - initialBet - 5 >= 0) initialBet += 5;
  }
  if (bettingButtons[1]->tryButtonPressLeft(worldCoords) && initialBet >= 30)
  {
    if (initialBet - 25 >= 5) initialBet -= 25;
  }
  if (bettingButtons[1]->tryButtonPressRight(worldCoords) && bankroll >= 25)
  {
    if (bankroll - initialBet - 25 >= 0) initialBet += 25;
  }
  if (bettingButtons[2]->tryButtonPressLeft(worldCoords) && initialBet >= 105)
  {
    if (initialBet - 100 >= 5) initialBet -= 100;
  }
  if (bettingButtons[2]->tryButtonPressRight(worldCoords) && bankroll >= 100)
  {
    if (bankroll - initialBet - 100 >= 0) initialBet += 100;
  }
}
void Game::resetHandGraphics()
{
  playButton->setVisible(false);
  bet5Label->setVisible(false);
  bet25Label->setVisible(false);
  bet100Label->setVisible(false);
  for (auto& button : bettingButtons) button->setVisible(false);
  gainLabel->setVisible(false);
  initialBetLabel->setVisible(false);
  gainLabel->setText("");
}
void Game::resetGraphics()
{
  for (auto& button : choiceButtons) button->setVisible(false);
  dealer->getCard(1)->setVisible(true);
  playButton->setVisible(true);
  bet5Label->setVisible(true);
  bet25Label->setVisible(true);
  bet100Label->setVisible(true);
  for (auto& button : bettingButtons) button->setVisible(true);
  gainLabel->setVisible(true);
  initialBetLabel->setVisible(true);
  if ((float)shoe.size() / (float)(DECK_SIZE * rules.decks) < 1.0f - rules.pen) shuffleLabel->setVisible(true);
}
void Game::winLoss(bool isNatural21)
{
  float gain = 0.0f;
  for (int i = 0; i < players.size(); i++)
  {
    auto& player = players[i];
    if (player->isBust())
    {
      gain -= player->getBet();
      continue;
    }
    if (dealer->isBust())
    {
      bankroll += player->getBet() * 2.0f;
      gain += player->getBet();
      continue;
    }
    if (player->total() < dealer->total(false))
    {
      gain -= player->getBet();
      continue;
    }
    if (player->total() > dealer->total(false))
    {
      bankroll += player->getBet() * 2.0f;
      gain += player->getBet();
      continue;
    }
    if (player->total() == dealer->total(false))
    {
      bankroll += player->getBet();
    }
  }
  if (insured)
  {
    gain -= players[0]->getBet() * 0.5f;
    insured = false;
  }
  if (gain >= 0.0f) gainLabel->setText("+" + floatToString(gain, 2));
  if (gain < 0.0f) gainLabel->setText(floatToString(gain, 2));
}
bool Game::initialWinLoss(bool isNatural21)
{
  if (dealer->total(false) == 21 && insured)
  {
    bankroll += players[0]->getBet() * 1.5f;
    if (isNatural21)
    {
      bankroll += players[0]->getBet();
      gainLabel->setText("+" + floatToString(players[0]->getBet()));
    }
    else gainLabel->setText("+0");
    insured = false;
    return true;
  }
  if (isNatural21 && dealer->total(false) != 21)
  {
    bankroll += players[0]->getBet() + (players[0]->getBet() * rules.blackjackPay);
    if (insured)
    {
      gainLabel->setText("+" + floatToString(players[0]->getBet(), 2));
      insured = false;
    }
    else gainLabel->setText("+" + floatToString(players[0]->getBet() * rules.blackjackPay, 2));
    return true;
  }
  if (surrendered)
  {
    bankroll += players[0]->getBet() * 0.5f;
    surrendered = false;
    gainLabel->setText("-" + floatToString(players[0]->getBet() * 0.5f, 2));
    return true;
  }
  return false;
}
void Game::dealerHit(bool isNatural21)
{
  bool letDealerHit = false;
  for (auto& player : players)
  {
    if (!isNatural21 && !player->isBust() && choice != SURRENDER)
    {
      letDealerHit = true;
      break;
    }
  }
  while (!dealer->stop() && letDealerHit) dealer->hit(shoe.topPop());
}
bool Game::isExited() const
{
  return exit;
}
