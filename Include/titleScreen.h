#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include "text.h"
#include "playButton.h"
#include "switchButton.h"
#include "arrowButton.h"
#include "rules.h"

class TitleScreen
{
public:
	std::unordered_map<int, std::string> bjPay;
	std::unordered_map<int, std::string> deckCount;
	std::unordered_map<int, std::string> splitCount;
	std::unordered_map<int, std::string> doubleCount;

	TitleScreen();
	void render(const glm::mat4& proj, const glm::mat4& view, float screenWidth, float screenHeight);
	void tryButtonPress(const glm::vec2& worldCoords);
	void updateLabels(int index, bool right);
	void setExit(bool b);
	bool isExited() const;
	float getBet() const;
	float getBankroll() const;
	Rules getRules() const;
private:
	Rules rules;
	bool exit;
	std::unique_ptr<Text> titleLabel;
	std::vector<std::unique_ptr<Text>> choiceLabels;
	std::vector<std::unique_ptr<SwitchButton>> switchButtons;
	std::vector<std::unique_ptr<ArrowButton>> arrowButtons;
	std::unique_ptr<PlayButton> playButton;
	std::vector<std::unique_ptr<Text>> bettingLabels;
	std::vector<std::unique_ptr<ArrowButton>> bettingButtons;
	bool playChoice;
	int blackjackPayChoice;
	int deckChoice;
	int splitChoice;
	int doubleChoice;
	int pen;
	float initialBet;
	float bankroll;
};
