#pragma once

class InputHandler final
{
public:
	void setLmbPressed();
	void update();

	const bool isLmbPressed() const;

private:
	bool _isLmbPressed = false;
};