#pragma once

#include <Windows.h>

class MouseHandler
{
public:
    enum class MouseButton
    {
        Left,
        Right,
        Middle
    };

    explicit MouseHandler(HWND target);
    void SimulateClick(int windowX, int windowY, MouseButton button);

private:
    HWND targetWindow{ nullptr };
};
