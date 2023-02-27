#include "MouseHandler.h"

MouseHandler::MouseHandler(HWND target)
	: targetWindow(target)
{

}

void MouseHandler::SimulateClick(int windowX, int windowY, MouseButton button)
{
	const auto coords = MAKELPARAM(windowX, windowY);
	SendMessage(targetWindow, WM_LBUTTONDOWN, MK_LBUTTON, coords);
}
