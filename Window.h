#pragma once
#include <Windows.h>

class Window
{
    public:
        Window();
        ~Window();
        bool init(LPCWSTR title, int width, int height);
        bool createBtn(LPCWSTR text, int posx, int posy, int width, int height);
        bool broadcast();
        bool isRunning();
        bool release();

        virtual void onCreate() = 0;
        virtual void onUpdate() = 0;
        virtual void onDestroy();
    protected:
        HWND hwnd;
        bool b_isRunning;
};

