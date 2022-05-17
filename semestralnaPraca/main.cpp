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
#include "../structures/table/unsorted_sequence_table.h"
/*
structures::ArrayList<StoredData> obce;
structures::ArrayList<StoredData> okresov;
structures::ArrayList<StoredData> krajov;

structures::Table<nazov, list> okres -> indexi obce v danom kraji list{1,7,10} -> indexi obci v ArrayListe;
structures::Table<nazov, index> obce -> index obca podľa názvu
*/



int main()
{


    DataLoader *loader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    structures::UnsortedSequenceTable<wstring, StoredData*> *kraj  = new structures::UnsortedSequenceTable<wstring, StoredData*>;


    if (loader->isOpen()) {
        loader->nextLine();
        while (loader->nextLine()){
            auto ukladana = new UzemnaJednotka();
            for (int i = 0; i < ukladana->getSize(); ++i) {
                ukladana->setNextParameter(loader->getNextParameter());
            }
            kraj->insert(ukladana->getOfficialTitle(), ukladana);
        }

    }

    for (auto item: *kraj) {
        for (int i = 0; i < item->accessData()->getSize(); ++i) {
            wcout << item->accessData()->at(i)<< L"\t";
        }
        wcout << endl;
    }

    cout << "test hladanie \n";
    wstring hladanie = L"Zahraničie";
    auto test = kraj->find(hladanie);
    wcout << test->getOfficialTitle() << L"\t" << test->getCode() << endl;
    delete kraj;
    delete loader;
    return 0;
}