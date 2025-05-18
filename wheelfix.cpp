#include <windows.h>
#include <chrono>

HHOOK mouseHook;
auto lastScrollTime = std::chrono::steady_clock::now();
int lastDelta = 0; 

LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION && wParam == WM_MOUSEWHEEL) {
        auto* ms = (MSLLHOOKSTRUCT*)lParam;
        int delta = GET_WHEEL_DELTA_WPARAM(ms->mouseData);

        if (abs(delta) < 30) return 1; //ignore too small scroll

        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastScrollTime).count();

        if ((delta * lastDelta < 0) && diff < 150) {} //if direction change too fast return 1

        lastDelta = delta;
        lastScrollTime = now;
    }
    return CallNextHookEx(mouseHook, code, wParam, lParam);
}

int main() {
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, nullptr, 0);
    if (!mouseHook) return 1;

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) DispatchMessage(&msg);
    UnhookWindowsHookEx(mouseHook);
    return 0;
}
