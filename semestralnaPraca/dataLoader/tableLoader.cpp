#include "tableLoader.h"

TableLoader::TableLoader() {

}

TableLoader::~TableLoader() {

}

void
TableLoader::loadTable(structures::Table<string, StoredData *> &kraj, structures::Table<string, StoredData *> &okres,
                       structures::Table<string, StoredData *> &obec,
                       structures::Table<string, StoredData *> &vzdelanie,
                       structures::Table<string, StoredData *> &nameIndex,
                       structures::Table<string, StoredData *> &codeIndex)
{
    //------------------- Kraj ------------------
    DataLoader *loader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    if (loader->isOpen()){
        loader->nextLine(); // aby sa preskočil header
        while (loader->nextLine()) {
            UzemnaJednotka *data = new UzemnaJednotka(UJTyp::Kraj);
            while (loader->hasNextParameter()) {
                data->setNextParameter(loader->getNextParameter());
            }
            kraj.insert(data->getOfficialTitle(), data);
            nameIndex.insert(data->getOfficialTitle(), data);
            codeIndex.insert(data->at(5), data);
            codeIndex.insert(data->at(5).substr(5, string::npos), data);
        }
    }

    //------------------- Okres ------------------
    loader->openNew("../semestralnaPraca/dataLoader/rawData/okresy.csv");
    if (loader->isOpen()){
        loader->nextLine(); // aby sa preskočil header
        while (loader->nextLine()) {
            UzemnaJednotka *data = new UzemnaJednotka(UJTyp::Okres);
            while (loader->hasNextParameter()) {
                data->setNextParameter(loader->getNextParameter());
            }
            okres.insert(data->getOfficialTitle(), data);
            nameIndex.insert(data->getOfficialTitle(), data);
            codeIndex.insert(data->getCode(), data);
        }
    }

    //------------------- Obce ------------------
    loader->openNew("../semestralnaPraca/dataLoader/rawData/obce.csv");
    if (loader->isOpen()){
        loader->nextLine(); // aby sa preskočil header
        while (loader->nextLine()) {
            UzemnaJednotka *data = new UzemnaJednotka(UJTyp::Obec);
            while (loader->hasNextParameter()) {
                data->setNextParameter(loader->getNextParameter());
            }
            obec.insert(data->getOfficialTitle(), data);
            nameIndex.insert(data->getOfficialTitle(), data);
            codeIndex.insert(data->getCode(), data);
            if (data->getOfficialTitle().compare(data->at(3)) != 0) {
                nameIndex.insert(data->at(3), data);
            }
            if (data->at(3).compare(data->at(4)) != 0 && data->getOfficialTitle().compare(data->at(4))) {
                nameIndex.insert(data->at(4), data);
            }

        }
    }


    //---------- Pridanie mien pre Okres ---------
    for (auto item: okres) {
        auto data = item->accessData();
        if (data->getOfficialTitle().compare(data->at(3)) != 0 && !nameIndex.containsKey(data->at(3))) {
            nameIndex.insert(data->at(3), data);
        }
        if (data->at(3).compare(data->at(4)) != 0 && data->getOfficialTitle().compare(data->at(4)) && !nameIndex.containsKey(data->at(4))) {
            for (int i = 0; i < data->getSize(); ++i) {
                cout << data->at(i) << ",\t";
            }
            cout << endl;
            nameIndex.insert(data->at(4), data);
        }
    }

    //------------------- Vzdelavanie ------------------
    loader->openNew("../semestralnaPraca/dataLoader/rawData/vzdelanie.csv");
    if (loader->isOpen()){
        loader->nextLine(); // aby sa preskočil header
        while (loader->nextLine()) {
            OstatneUdaje *data = new OstatneUdaje(loader->getNextParameter(), loader->getNextParameter());
            while (loader->hasNextParameter()) {
                data->setNextParameter(loader->getNextParameter());
            }
            vzdelanie.insert(data->getCode(), data);
            auto test = codeIndex.find(data->getCode());
            test->setVzdelavanie(data);
            test->getCode();

        }
    }

    delete loader;
}

void TableLoader::indexingTable(structures::UnsortedSequenceTable<string, StoredData *> &stat,
                                structures::UnsortedSequenceTable<string, StoredData *> &kraj,
                                structures::UnsortedSequenceTable<string, StoredData *> &okres,
                                structures::UnsortedSequenceTable<string, StoredData *> &obec,
                                structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &statIndex,
                                structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &krajIndex,
                                structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &okresIndex)
{
    //---------------- Indexovanie VUC STAT --------------------------------
    structures::ArrayList<StoredData *> *slovensko = new structures::ArrayList<StoredData *>;
    structures::ArrayList<StoredData *> *zahranicie = new structures::ArrayList<StoredData *>;
    for (auto item: kraj) {
        string kod = item->accessData()->at(5).substr(0,2);
        if (kod.compare("ZZ") != 0) {
            slovensko->add(item->accessData());
        } else {
            zahranicie->add(item->accessData());
        }
    }

    statIndex.insert(stat.find("SK")->getCode(), slovensko);
    statIndex.insert(stat.find("ZZ")->getCode(), zahranicie);

    //---------------- Indexovanie VUC KRAJ -------------------------------
    int indexOkresu = 0;
    for (auto arrayL: statIndex) {
        for (auto okr: *arrayL->accessData()) {
            structures::ArrayList<StoredData *> *data = new structures::ArrayList<StoredData*>;
            for (; indexOkresu < okres.size(); indexOkresu++) {
                if (okres.getItemAtIndex(indexOkresu).accessData()->at(5).substr(0,1).compare(okr->getCode()) == 0) {
                    data->add(okres.getItemAtIndex(indexOkresu).accessData());
                } else {
                    break;
                }
            }
            krajIndex.insert(okr->at(5), data);
        }
    }


    int indexObce = 0;
    for (auto ixOkres: okres) {
        structures::ArrayList<StoredData *> *data = new structures::ArrayList<StoredData*>;
        for (; indexObce < obec.size(); indexObce++) {
            //cout << ixOkres->accessData()->getCode() << "\t" << obec.getItemAtIndex(indexObce).accessData()->getCode().substr(0,6) << endl;
            if (obec.getItemAtIndex(indexObce).accessData()->getCode().substr(0,6).compare(ixOkres->accessData()->getCode()) == 0) {
                data->add(obec.getItemAtIndex(indexObce).accessData());
            } else {
                break;
            }
        }
        okresIndex.insert(ixOkres->accessData()->getCode(), data);
    }



}

void TableLoader::spracujVzdelanie(
        structures::SortedSequenceTable<string, StoredData *> &codeIndex,
        structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &statIndex,
        structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &krajIndex,
        structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &okresIndex,
        structures::SortedSequenceTable<string, StoredData *> &vzdelanieObec,
        structures::SortedSequenceTable<string, StoredData *> &vzdelanieOkres,
        structures::SortedSequenceTable<string, StoredData *> &vzdelanieKraj,
        structures::SortedSequenceTable<string, StoredData *> &vzdelanieStat)
{
    //----------------- Vzdelanie Okresy -------------------
    for (auto ixOkres: okresIndex) {
        auto findOkres = codeIndex.find(ixOkres->getKey());
        OstatneUdaje *vzOkres = new OstatneUdaje(findOkres->getCode(), findOkres->getOfficialTitle());
        for (int i = 0; i < 8; ++i) {
            vzOkres->setNextIntParameter(spocitajVzdelanie(i, *ixOkres->accessData(), vzdelanieObec));
        }
        vzdelanieOkres.insert(vzOkres->getCode(), vzOkres);
        findOkres->setVzdelavanie(vzOkres);
    }

    //----------------- Vzdelanie Kraje -------------------
    for (auto ixKraj: krajIndex) {
        auto findKraj = codeIndex.find(ixKraj->getKey());
        OstatneUdaje *vzKraj = new OstatneUdaje(findKraj->getCode(), findKraj->getOfficialTitle());
        for (int i = 0; i < 8; ++i) {
            vzKraj->setNextIntParameter(spocitajVzdelanie(i, *ixKraj->accessData(), vzdelanieOkres));
        }
        vzdelanieKraj.insert(vzKraj->getCode(), vzKraj);
        findKraj->setVzdelavanie(vzKraj);
    }

    //----------------- Vzdelanie Stat -------------------
    for (auto ixStat: statIndex) {
        auto findStat = codeIndex.find(ixStat->getKey());
        OstatneUdaje *vzStat = new OstatneUdaje(findStat->getCode(), findStat->getOfficialTitle());
        for (int i = 0; i < 8; ++i) {
            vzStat->setNextIntParameter(spocitajVzdelanie(i, *ixStat->accessData(), vzdelanieKraj));
        }
        vzdelanieStat.insert(vzStat->getCode(), vzStat);
        findStat->setVzdelavanie(vzStat);
    }

}

int TableLoader::spocitajVzdelanie(int index, structures::ArrayList<StoredData *> &data, structures::SortedSequenceTable<string, StoredData *> &vzdelanieUJ) {
    int returnValue = 0;

    for (const auto vzdelanie : data) {
        try {
            auto findData = vzdelanieUJ.find(vzdelanie->getCode());
            auto &newVzdelanie = dynamic_cast<OstatneUdaje &>(*findData);
            returnValue += newVzdelanie.intAt(index);
        } catch (std::out_of_range) {
            // pre prípad že by som chcel aj vypysovať chýbajúce UJ
            //wcerr << "INDEXOVANIE: \tObec: " << vzdelanie->getOfficialTitle() << " nema zaznam v udajoch o vzdelani!!" << endl;
        }
    }
    return returnValue;
}
