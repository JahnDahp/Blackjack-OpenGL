#pragma once

#include "button.h"

class PlayButton : public Button
{
public:
	PlayButton();
	void init() override;
	void transform(float x, float y, float scaleX, float scaleY) override;
	void render(const glm::mat4& proj, const glm::mat4& view) override;
	bool tryButtonPress(const glm::vec2& worldCoords);
private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
};
