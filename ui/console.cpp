#include "console.h"
#include <iostream>
#include <iomanip>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

namespace ui
{
    Console& Console::getInstance()
    {
        static Console getInstance;
        return getInstance;
    }

    void Console::print(const std::string& str)
    {
        std::cout << str;
    }

    void Console::print(const std::string& str, const Color color)
    {
        if (color != Color::Default)
        {
            this->setColor(color);
            this->print(str);
            this->resetColor();
        }
        else
        {
            this->print(str);
        }
    }

    void Console::print(const std::string& str, Color color, std::size_t width)
    {
        if (color != Color::Default)
        {
            this->setColor(color);
            this->setNextTokenWidth(width);
            this->print(str);
            this->resetColor();
        }
        else
        {
            this->setNextTokenWidth(width);
            this->print(str);
        }
    }

    void Console::println(const std::string& str)
    {
        std::cout << str << '\n';
    }

    void Console::println(const std::string& str, const Color color)
    {
        if (color != Color::Default)
        {
            this->setColor(color);
            this->println(str);
            this->resetColor();
        }
        else
        {
            this->println(str);
        }
    }

    void Console::println(const std::string& str, Color color, std::size_t width)
    {
        if (color != Color::Default)
        {
            this->setColor(color);
            this->setNextTokenWidth(width);
            this->println(str);
            this->resetColor();
        }
        else
        {
            this->setNextTokenWidth(width);
            this->println(str);
        }
    }

    void Console::setNextTokenWidth(const size_t w)
    {
        std::cout << std::left << std::setw(w);
    }

#if defined(_WIN32) || defined(_WIN64)

    namespace
    {
        WORD convert(const Color color)
        {
            switch (color)
            {
            case Color::Red:
                return FOREGROUND_RED | FOREGROUND_INTENSITY;

            case Color::Green:
                return FOREGROUND_GREEN | FOREGROUND_INTENSITY;

            case Color::Blue:
                return FOREGROUND_BLUE | FOREGROUND_INTENSITY;

            case Color::Yellow:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

            default:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            }
        }

        void windowsSetColor(WORD color)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, color);
        }
    }

    Console::Console()
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        GetConsoleScreenBufferInfo(handle, &csbiInfo);
        defaultColor_ = csbiInfo.wAttributes;
    }

    void Console::setColor(const Color color)
    {
        windowsSetColor(convert(color));
    }

    void Console::resetColor()
    {
        windowsSetColor(defaultColor_);
    }

#endif

#if defined(__APPLE__) || defined(__linux__)

    namespace
    {
        const char* convert(const Color color)
        {
            switch (color)
            {
            case Color::Red:
                return "\x1B[91m";

            case Color::Green:
                return "\x1B[92m";

            case Color::Blue:
                return "\x1B[94m";

            case Color::Yellow:
                return "\x1B[93m";

            default:
                return "\x1B[97m";
            }
        }
    }

    void Console::setColor(const Color color)
    {
        std::cout << convert(color);
    }

    void Console::resetColor()
    {
        std::cout << "\x1B[0m";
    }

#endif
}