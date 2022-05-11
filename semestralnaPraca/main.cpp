//
// Created by Tobias on 30/04/2022.
//

//todo sort(nejaka tabulka<K,T>, bool vzostp, kriteria<T,R>)
// volá sa to evaluator, to jest že sort používa krtiéria
//todo do tabuľky sa dá dostať aj cez getItemAtIndex
// poto sa to dá cez kritería getovať vlastnosti a tie porovnávať
// T data = tabs.getItemAtIndex(i)->accessData
// R vlastnostI = krti.evaluate(data)
// if(zostupne) {
//  vlastnostI < vlastnostJ
// }

//todo filter preberie ktritérium a sptía sa či to funguje, rozširuje sa to iba potomkami
// vytvoriť metódy na kritéria a návratova hodnota by bola to kritérim a poto ho viem využiť na viacerých miestach
// vytvoriť kritérium pre názov , opýtať sa aký nazov chce a potom to vyhodnocuje
#include "iostream"
#include "dataLoader.h"
#include "uzemnaJednotka.h"
#include "storedData.h"
#include "ostatneUdaje.h"
#include "../structures/table/table.h"
/*
structures::ArrayList<StoredData> obce;
structures::ArrayList<StoredData> okresov;
structures::ArrayList<StoredData> krajov;

structures::Table<nazov, list> kraj -> index okresov
structures::Table<nazov, list> okres -> indexi obce v danom kraji list{1,7,10} -> indexi obci v ArrayListe;
structures::Table<nazov, index> obce -> index obca podľa názvu
*/

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

/*
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

*/
    delete kraj;
    delete loader;
    //delete vzdelanie;

    return 0;
}