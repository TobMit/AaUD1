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


    DataLoader *loader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");


    StoredData *kraj = new UzemnaJednotka();

    if (loader->isOpen()) {
        loader->nextLine();
        loader->nextLine();
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
        kraj->setNextParameter(loader->getNextParameter());
    }
    for (int i = 0; i < kraj->getSize(); ++i) {
        wcout << kraj->at(i) << L"\t";
    }
    wcout << endl;

    loader->openNew("../semestralnaPraca/dataLoader/rawData/vzdelanie.csv");
    OstatneUdaje *vzdelavanie = new OstatneUdaje();

    if (loader->isOpen()) {
        loader->nextLine();
        loader->nextLine();
        vzdelavanie->setCode(loader->getNextParameter());
        vzdelavanie->setOfficialTitle(loader->getNextParameter());
        while (loader->hasNextParameter()) {
            vzdelavanie->setNextParameter(loader->getNextParameter());
        }
    }
    wcout << vzdelavanie->getCode() << L"\t" << vzdelavanie->getOfficialTitle() << L"\t";
    for (int i = 0; i < vzdelavanie->getSize(); ++i) {
        wcout << vzdelavanie->intAt(i) << L"\t";
    }
    wcout << endl;

    delete kraj;
    delete loader;
    delete vzdelavanie;
    return 0;
}