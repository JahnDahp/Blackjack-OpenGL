#include "titleScreen.h"

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

TitleScreen::TitleScreen()
  : exit(false), 
  playChoice(false), 
  blackjackPayChoice(0),
  deckChoice(1), 
  splitChoice(3),
  doubleChoice(0), 
  pen(75),
  initialBet(5.0f),
  bankroll(1000.0f)
{
  titleLabel = std::make_unique<Text>("../Resources/Fonts/casino3D.ttf", "Blackjack", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  bjPay[0] = "Blackjack pays 3:2";
  bjPay[1] = "Blackjack pays 6:5";
  bjPay[2] = "Blackjack pays 2:1";
  bjPay[3] = "Blackjack pays 1:1";
  deckCount[0] = "Single deck";
  deckCount[1] = "Double deck";
  deckCount[2] = "Four decks";
  deckCount[3] = "Six decks";
  deckCount[4] = "Eight decks";
  splitCount[0] = "No splitting";
  splitCount[1] = "Split to one hand";
  splitCount[2] = "Split to three hands";
  splitCount[3] = "Split to four hands";
  doubleCount[0] = "Double any total";
  doubleCount[1] = "Double 9, 10, 11";
  doubleCount[2] = "Double 10, 11";
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", bjPay[blackjackPayChoice], glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Dealer hits soft 17", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", deckCount[deckChoice], glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Double after split", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", splitCount[splitChoice], glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Draw split aces", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Resplit aces", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Late surrender", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Pen: " + std::to_string(pen) + "%", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  choiceLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", doubleCount[doubleChoice], glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  for (int i = 0; i < choiceLabels.size(); i++)
  {
    if (i == 1 || i == 3 || i == 5 || i == 6 || i == 7)
    {
      arrowButtons.push_back(nullptr);
      switchButtons.push_back(std::make_unique<SwitchButton>());
      switchButtons[i]->init();
      if (i == 3 || i == 7) switchButtons[i]->setOn(true);
    }
    else
    {
      switchButtons.push_back(nullptr);
      arrowButtons.push_back(std::make_unique<ArrowButton>());
      arrowButtons[i]->init();
    }
  }
	playButton = std::make_unique<PlayButton>();
  playButton->init();
  bettingLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bet 5", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  bettingLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bet 25", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  bettingLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bet 100", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  bettingLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bankroll 100", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  bettingLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bankroll 1000", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  bettingLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bankroll 10000", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  bettingLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "First Bet: " + floatToString(initialBet, 2), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  bettingLabels.push_back(std::make_unique<Text>("../Resources/Fonts/SF.otf", "Bankroll: " + floatToString(bankroll, 2), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
  for (int i = 0; i < 6; i++) bettingButtons.push_back(std::make_unique<ArrowButton>());
  for (auto& button : bettingButtons) button->init();
}
void TitleScreen::render(const glm::mat4& proj, const glm::mat4& view, float screenWidth, float screenHeight)
{
  float aspect = screenWidth / screenHeight;
  titleLabel->transform(0.0f, 0.77f, 4.0f, 4.0f);
  titleLabel->render(proj);
  for (int i = 0; i < choiceLabels.size(); i++)
  {
    Text* label = choiceLabels[i].get();
    label->transform(-(aspect + 0.5f) + 1.0f, 0.5f - i * 0.15f, 1.0f, 1.0f);
    label->render(proj);
    if (switchButtons[i])
    {
      switchButtons[i]->transform(-0.5f, label->getPos().y + label->getTextHeight() / 2.0f, 0.05f, 0.05f);
      switchButtons[i]->render(proj, view);
    }
    if (arrowButtons[i])
    {
      arrowButtons[i]->transform(-0.5f, label->getPos().y + label->getTextHeight() / 2.0f, 0.05f, 0.05f);
      arrowButtons[i]->render(proj, view);
    }
  }
  playButton->transform((aspect + 0.7f) - 1.0f, 0.0f, 0.25f, 0.25f);
	playButton->render(proj, view);
  for (int i = 0; i < bettingButtons.size(); i++)
  {
    bettingLabels[i]->transform(0.0f, 0.5f - (i * 0.15), 1.0f, 1.0f);
    bettingButtons[i]->transform(0.5f, bettingLabels[i]->getPos().y + bettingLabels[i]->getTextHeight() / 2.0f, 0.05f, 0.05f);
    bettingLabels[i]->render(proj);
    bettingButtons[i]->render(proj, view);
  }
  int bettingLabelsEnd = bettingLabels.size() - 1;
  bettingLabels[bettingLabelsEnd - 1]->transform(0.0f, 0.5f - ((bettingLabelsEnd - 1) * 0.15), 1.0f, 1.0f);
  bettingLabels[bettingLabelsEnd]->transform(0.0f, 0.5f - (bettingLabelsEnd * 0.15), 1.0f, 1.0f);
  bettingLabels[bettingLabelsEnd - 1]->setText("First Bet: " + floatToString(initialBet, 2));
  bettingLabels[bettingLabelsEnd]->setText("Bankroll: " + floatToString(bankroll, 2));
  bettingLabels[bettingLabelsEnd - 1]->render(proj);
  bettingLabels[bettingLabelsEnd]->render(proj);
}
void TitleScreen::tryButtonPress(const glm::vec2& worldCoords)
{
  if (playButton->tryButtonPress(worldCoords))
  {
    exit = true;
    if (blackjackPayChoice == 0) rules.blackjackPay = 1.5f;
    if (blackjackPayChoice == 1) rules.blackjackPay = 1.2f;
    if (blackjackPayChoice == 2) rules.blackjackPay = 2.0f;
    if (blackjackPayChoice == 3) rules.blackjackPay = 1.0f;
    rules.H17 = switchButtons[1]->isOn();
    if (deckChoice == 0) rules.decks = 1;
    if (deckChoice == 1) rules.decks = 2;
    if (deckChoice == 2) rules.decks = 4;
    if (deckChoice == 3) rules.decks = 6;
    if (deckChoice == 4) rules.decks = 8;
    rules.DAS = switchButtons[3]->isOn();
    rules.numSplits = splitChoice;
    rules.drawSplitAces = switchButtons[5]->isOn();
    rules.resplitAces = switchButtons[6]->isOn();
    rules.surrender = switchButtons[7]->isOn();
    rules.pen = (float)pen / 100.0f;
    if (doubleChoice == 0) for (int i = 0; i < 21; i++) rules.doubles[i] = true;
    if (doubleChoice != 0)
    {
      for (int i = 0; i < 21; i++) rules.doubles[i] = false;
      rules.doubles[11] = true;
      rules.doubles[10] = true;
      rules.doubles[9] = doubleChoice == 1;
    }
  }
  for (auto& button : switchButtons)
  {
    if (button && button->tryButtonPress(worldCoords)) button->setOn(!button->isOn());
  }
  int i = 0;
  for (auto& button : arrowButtons)
  {
    if (button && button->tryButtonPressLeft(worldCoords)) updateLabels(i, false);
    if (button && button->tryButtonPressRight(worldCoords)) updateLabels(i, true);
    i++;
  }

  if (bettingButtons[0]->tryButtonPressLeft(worldCoords) && initialBet - 5 >= 5) initialBet -= 5;
  if (bettingButtons[0]->tryButtonPressRight(worldCoords) && bankroll - initialBet - 5 >= 0) initialBet += 5;
  if (bettingButtons[1]->tryButtonPressLeft(worldCoords) && initialBet - 25 >= 5) initialBet -= 25;
  if (bettingButtons[1]->tryButtonPressRight(worldCoords) && bankroll - initialBet - 25 >= 0) initialBet += 25;
  if (bettingButtons[2]->tryButtonPressLeft(worldCoords) && initialBet - 100 >= 5) initialBet -= 100;
  if (bettingButtons[2]->tryButtonPressRight(worldCoords) && bankroll - initialBet - 100 >= 0) initialBet += 100;

  if (bettingButtons[3]->tryButtonPressLeft(worldCoords) && bankroll - 100 >= initialBet) bankroll -= 100;
  if (bettingButtons[3]->tryButtonPressRight(worldCoords)) bankroll += 100;
  if (bettingButtons[4]->tryButtonPressLeft(worldCoords) && bankroll - 1000 >= initialBet) bankroll -= 1000;
  if (bettingButtons[4]->tryButtonPressRight(worldCoords)) bankroll += 1000;
  if (bettingButtons[5]->tryButtonPressLeft(worldCoords) && bankroll - 10000 >= initialBet) bankroll -= 10000;
  if (bettingButtons[5]->tryButtonPressRight(worldCoords)) bankroll += 10000;
}
void TitleScreen::updateLabels(int index, bool right)
{
  int offset = 0;
  if (right) offset++;
  if (!right) offset--;
  if (index == 0)
  {
    blackjackPayChoice = (blackjackPayChoice + offset + 4) % 4;
    choiceLabels[index]->setText(bjPay[blackjackPayChoice]);
  }
  if (index == 2)
  {
    deckChoice = (deckChoice + offset + 5) % 5;
    choiceLabels[index]->setText(deckCount[deckChoice]);
    offset = 0;
    index = 8;
  }
  if (index == 4)
  {
    splitChoice = (splitChoice + offset + 4) % 4;
    choiceLabels[index]->setText(splitCount[splitChoice]);
  }
  if (index == 8)
  {
    int limit = 50;
    if (deckChoice != 0) limit = (100 - 50 / (deckChoice * 2));
    pen += offset;
    pen = std::clamp(pen, 25, limit);
    choiceLabels[index]->setText("Pen: " + std::to_string(pen) + "%");
  }
  if (index == 9)
  {
    doubleChoice = (doubleChoice + offset + 3) % 3;
    choiceLabels[index]->setText(doubleCount[doubleChoice]);
  }
}
void TitleScreen::setExit(bool b)
{
	exit = b;
}
bool TitleScreen::isExited() const
{
	return exit;
}
float TitleScreen::getBet() const
{
  return initialBet;
}
float TitleScreen::getBankroll() const
{
  return bankroll;
}
Rules TitleScreen::getRules() const
{
  return rules;
}
