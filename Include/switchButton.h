#pragma once

#include "button.h"

class SwitchButton : public Button
{
public:
	SwitchButton();
	void init() override;
	void transform(float x, float y, float scaleX, float scaleY) override;
	void render(const glm::mat4& proj, const glm::mat4& view) override;
	void setOn(bool b);
	bool isOn() const;
	bool tryButtonPress(const glm::vec2& worldCoords);
private:
	bool on;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
};