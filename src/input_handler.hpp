#pragma once

class InputHandler final
{
public:
	void setLmbDown();
	void update();

	const bool isLmbPressed() const;

private:
	bool _isLmbPressed = false;
};