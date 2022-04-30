//
// Created by Tobias on 30/04/2022.
//
#include "iostream"
#include "dataLoader.h"

int main()
{
    DataLoader *loader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    if (loader->isOpen()) {
        while (loader->nextLine()) {
            wcout << loader->getNextParameter() << L" "
                    << loader->getNextParameter() << L" "
                    << loader->getNextParameter() << L" "
                    << loader->getNextParameter() << L" "
                    << loader->getNextParameter() << L" "
                    << loader->getNextParameter() << L" "
                    << loader->getNextParameter() << L" "
                    << loader->getNextParameter() << L" "
                    << loader->getNextParameter() << L" \n";
        }
    }


    delete loader;
    return 0;
}