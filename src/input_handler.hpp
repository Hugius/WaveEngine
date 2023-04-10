#pragma once

class InputHandler final
{
public:
	void sendMouseDownEvent();
	void sendMouseUpEvent();

	const bool isMouseButtonPressed() const;

private:
	bool _isMouseButtonPressed = false;
};