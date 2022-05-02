//
// Created by Tobias on 30/04/2022.
//
#include "iostream"
#include "dataLoader.h"
#include "uzemnaJednotka.h"
#include "storedData.h"

int main()
{
    /*
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

    //cout << "+ľščťžýáíé";
    delete loader;
    */
    DataLoader *loader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    StoredData<wstring> *kraj = new UzemnaJednotka<wstring>();
    if (loader->isOpen()) {
        loader->nextLine();
        kraj->nastavDalsiParameter(loader->getNextParameter());
        kraj->setCode(loader->getNextParameter());
        kraj->setOfficialTitle(loader->getNextParameter());
        kraj->nastavDalsiParameter(loader->getNextParameter());
        kraj->nastavDalsiParameter(loader->getNextParameter());
        kraj->nastavDalsiParameter(loader->getNextParameter());
        kraj->nastavDalsiParameter(loader->getNextParameter());
    }
    for (int i = 0; i < kraj->getSize(); ++i) {
        wcout << kraj->at(i) << L" ";
    }

    delete kraj;
    delete loader;
    return 0;
}