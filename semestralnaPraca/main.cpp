//
// Created by Tobias on 30/04/2022.
//
#include "iostream"
#include "dataLoader.h"
#include "uzemnaJednotka.h"
#include "storedData.h"
#include "ostatneUdaje.h"
#include "../structures/table/table.h"



int main()
{

    /*
    DataLoader *testLoader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    if (testLoader->isOpen()) {
        while (testLoader->nextLine()) {
            while (testLoader->haveNextParameter()) {
                wcout << testLoader->getNextParameter() << L" ";
            }
            wcout << endl;
        }
    }

    delete testLoader;
*/

    DataLoader *loader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    StoredData *kraj = new UzemnaJednotka();
    if (loader->isOpen()) {
        loader->nextLine();
        while (loader->haveNextParameter()){
            kraj->setNextHeader(loader->getNextParameter());
        }
        loader->nextLine();
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setCode(loader->getNextParameter());
        kraj->setOfficialTitle(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
    }
    wcout << kraj->getFullHeader() << endl;
    for (int i = 0; i < kraj->getSize(); ++i) {
        wcout << kraj->at(i) << L"\t";
    }
    wcout << endl;

    loader->openNew("../semestralnaPraca/dataLoader/rawData/vzdelanie.csv");
    StoredData *vzdelanie = new OstatneUdaje();
    if (loader->isOpen()) {
        loader->nextLine();
        loader->nextLine();
        loader->nextLine();
        vzdelanie->setCode(loader->getNextParameter());
        vzdelanie->setOfficialTitle(loader->getNextParameter());
        for (int i = 0; loader->haveNextParameter(); i++) {
            vzdelanie->setNextParameter(loader->getNextParameter());
        }
    }
        wcout << vzdelanie->getCode() << L" " << vzdelanie->getOfficialTitle() << L" ";
        for (int i = 0; i < vzdelanie->getSize(); ++i) {
            wcout << vzdelanie->at(i) << L" ";
        }


    delete kraj;
    delete loader;
    return 0;
}