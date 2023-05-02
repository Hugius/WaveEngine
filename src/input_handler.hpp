#pragma once

class InputHandler final
{
public:
	void setLmbDown();
	void setLmbUp();
	void update();

	const bool isLmbPressed() const;
	const bool isLmbHeld() const;

private:
	bool _isLmbPressed = false;
	bool _isLmbHeld = false;
};