#include "aplikacia.h"

int main()
{
    Aplikacia *aplikacia = new Aplikacia();
    bool opakovat = true;
    while (opakovat) {
        opakovat = aplikacia->menu();
    }

    delete aplikacia;
    aplikacia = nullptr;
    return 0;
}