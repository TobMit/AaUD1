#pragma once

#include <string>

namespace ui
{
    enum class Color
    {
        Red,
        Green,
        Blue,
        Yellow,
        Default
    };

    class Console
    {
    public:
        static Console& getInstance();

        void print(const std::string& str);
        void print(const std::string& str, Color color);
        void print(const std::string& str, Color color, std::size_t width);
        void println(const std::string& str);
        void println(const std::string& str, Color color);
        void println(const std::string& str, Color color, std::size_t width);
        void setNextTokenWidth(size_t);
        void setColor(Color);
        void resetColor();

    private:
        Console(const Console&) = delete;

#if defined(_WIN32) || defined(_WIN64)
        Console();
        unsigned short defaultColor_;
#else
        Console() = default;
#endif
    };
}