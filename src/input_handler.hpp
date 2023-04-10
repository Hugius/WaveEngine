#pragma once

class InputHandler final
{
public:
	void sendMouseButtonDownEvent();
	void update();

	const bool isMouseButtonPressed() const;

private:
	bool _isMouseButtonPressed = false;
};