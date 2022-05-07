//
// Created by Tobias on 30/04/2022.
//
#include "iostream"

#include "../structures/table/table.h"
#include "dataLoader/dataLoader.h"
#include "dataStructure/ostatneUdaje.h"
#include "dataStructure/storedData.h"
#include "dataStructure/uzemnaJednotka.h"
#include "../structures/heap_monitor.h"


int main()
{

    /*
    DataLoader *testLoader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    if (testLoader->isOpen()) {
        while (testLoader->nextLine()) {
            while (testLoader->haveNextParameter()) {
                cout << testLoader->getNextParameter() << L" ";
            }
            cout << endl;
        }
    }

    delete testLoader;
*/
    cout << "test" << endl;
    DataLoader *loader = new DataLoader("C:/Users/Tobias/Downloads/AUS_VS2019/AUS_VS2019/semestralnaPraca/dataLoader/rawData/kraje.csv");
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
    cout << kraj->getFullHeader() << endl;
    for (int i = 0; i < kraj->getSize(); ++i) {
        cout << kraj->at(i) << "\t";
    }
    cout << endl;

    loader->openNew("C:/Users/Tobias/Downloads/AUS_VS2019/AUS_VS2019/semestralnaPraca/dataLoader/rawData/vzdelanie.csv");
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
        cout << vzdelanie->getCode() << L" " << vzdelanie->getOfficialTitle() << L" ";
        for (int i = 0; i < vzdelanie->getSize(); ++i) {
            cout << vzdelanie->at(i) << L" ";
        }
        

  //  delete kraj;
   // delete loader;
   // delete vzdelanie;
    return 0;
}
