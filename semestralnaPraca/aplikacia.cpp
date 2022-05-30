#include "aplikacia.h"

Aplikacia::Aplikacia() :
        stat(new structures::UnsortedSequenceTable<string, StoredData*>),
        kraj(new structures::UnsortedSequenceTable<string, StoredData*>),
        okres(new structures::UnsortedSequenceTable<string, StoredData*>),
        obec(new structures::UnsortedSequenceTable<string, StoredData*>),
        vzdelanieObec(new structures::SortedSequenceTable<string, StoredData*>),
        vzdelanieOkres(new structures::SortedSequenceTable<string, StoredData*>),
        vzdelanieKraj(new structures::SortedSequenceTable<string, StoredData*>),
        vzdelanieStat(new structures::SortedSequenceTable<string, StoredData*>),
        nameIndex(new structures::SortedSequenceTable<string, StoredData*>),
        codeIndex(new structures::SortedSequenceTable<string, StoredData*>),
        statIndex(new structures::SortedSequenceTable<string, structures::ArrayList<StoredData*>*>),
        krajIndex(new structures::SortedSequenceTable<string, structures::ArrayList<StoredData*>*>),
        okresIndex(new structures::SortedSequenceTable<string, structures::ArrayList<StoredData*>*>)
{
    auto *slovensko = new UzemnaJednotka(UJTyp::Stat, "1", "SK", "Slovenská republika", "Slovensko", "Slovensko", "1");
    stat->insert(slovensko->getCode(), slovensko);
    auto *zahranicie = new UzemnaJednotka(UJTyp::Stat, "2", "ZZ", "Zahraničie", "", "", "2");
    stat->insert(zahranicie->getCode(), zahranicie);

    changeColor(Color::Cyan);
    TableLoader tableLoader;
    cout << "Načítavam dáta ";
    tableLoader.loadTable(*kraj, *okres, *obec, *vzdelanieObec, *nameIndex, *codeIndex);
    nameIndex->insert(slovensko->getOfficialTitle(), slovensko);
    nameIndex->insert(slovensko->at(4), slovensko);
    nameIndex->insert(zahranicie->getCode(), zahranicie);

    codeIndex->insert(slovensko->getCode(), slovensko);
    codeIndex->insert(zahranicie->getCode(), zahranicie);

    cout << " - 100%"  << endl;
    cout << "Indexujem územne jednotky ";
    tableLoader.indexingTable(*stat, *kraj, *okres, *obec,
                              *statIndex, *krajIndex, *okresIndex);
    cout << " - 100%"  << endl;
    cout << "Spracovávam dáta - vzdelávanie ";
    tableLoader.spracujVzdelanie(*codeIndex, *statIndex, *krajIndex, *okresIndex, *vzdelanieObec,
                                 *vzdelanieOkres,*vzdelanieKraj, *vzdelanieStat);
    cout << " - 100%"  << endl;
    resetColor();

}

Aplikacia::~Aplikacia() {
    vycistiTable(stat);
    delete stat;
    stat = nullptr;
    vycistiTable(kraj);
    delete kraj;
    kraj = nullptr;
    vycistiTable(okres);
    delete okres;
    okres = nullptr;
    vycistiTable(obec);
    delete obec;
    obec = nullptr;
    vycistiTable(vzdelanieObec);
    delete vzdelanieObec;
    vzdelanieObec = nullptr;
    vycistiTable(vzdelanieOkres);
    delete vzdelanieOkres;
    vzdelanieOkres = nullptr;
    vycistiTable(vzdelanieKraj);
    delete vzdelanieKraj;
    vzdelanieKraj = nullptr;
    vycistiTable(vzdelanieStat);
    delete vzdelanieStat;
    vzdelanieStat = nullptr;

    delete nameIndex;
    nameIndex = nullptr;
    delete codeIndex;
    codeIndex = nullptr;

    vicistiIndex(statIndex);
    delete statIndex;
    statIndex = nullptr;
    vicistiIndex(krajIndex);
    delete krajIndex;
    krajIndex = nullptr;
    vicistiIndex(okresIndex);
    delete okresIndex;
    okresIndex = nullptr;

}

bool Aplikacia::menu() {
    changeColor(Color::Magenta);
    cout << "--------------------- SEMESTRÁLNA PRÁCA ---------------------" << endl;
    cout << "\tBodové vyhľadávanie [1]" << endl;
    cout << "\tFiltrovanie [2]" << endl;
    cout << "\tKoniec [0]" << endl;
    cout << "Vaša voľba: ";
    resetColor();
    string volba = "0";
    std::getline(cin, volba);
    switch (stoi(volba)) {
        case 1:
            bodoveVyhladavanie();
            break;
        case 2:
            filtrovanie();
            break;
        default:
            return false;
    }
    changeColor(Color::Magenta);
    cout << endl << endl;
    cout << "------------------------------------------" << endl;
    cout << "Menu? \n\tÁno [1] \n\tNie [0]\nVoľba: ";
    std::getline(cin, volba);
    resetColor();
    switch (stoi(volba)) {
        case 1:
            return true;
        default:
            return false;
    }

}

void Aplikacia::bodoveVyhladavanie() {
    changeColor(Color::BrightGreen);
    cout << "--------------------- Bodové vyhľadávanie ---------------------" << endl;
    resetColor();
    cout << "Poznámka: parametre s \"*\" NIE sú povinné, ENTEROM sa preskočia." << endl;
    cout << "\t \t  Keď chcete vyhľadávať KRAJ alebo OKRES, treba to tam napísať, napr.: Trenčiansky kraj, Okres Trenčín" << endl;
    changeColor(Color::Green);
    cout << "Zadaj názov: ";
    string vyhladavaneMeno;
    std::getline(cin, vyhladavaneMeno);

    StoredData *findData;
    try {
        findData = nameIndex->find(vyhladavaneMeno);
    } catch (std::out_of_range) {
        changeColor(Color::Red);
        cout << "Vami zadaná UJ nebola nájdená!" << endl;
        return;
    }

    changeColor(Color::DarkGren);
    cout << "*Vzdelávanie "<< endl;
    cout << "\t- [0] Bez ukončeného vzdelania – osoby vo veku 0-14 rokov (abs.)" << endl;
    cout << "\t- [1] Základné vzdelanie (abs.)" << endl;
    cout << "\t- [2] Stredné odborné (učňovské) vzdelanie (bez maturity) (abs.)" << endl;
    cout << "\t- [3] Úplné stredné vzdelanie (s maturitou) (abs.)" << endl;
    cout << "\t- [4] Vyššie odborné vzdelanie (abs.)" << endl;
    cout << "\t- [5] Vysokoškolské vzdelanie (abs.)" << endl;
    cout << "\t- [6] Bez školského vzdelania – osoby vo veku 15 rokov a viac (abs.)" << endl;
    cout << "\t- [7] Nezistené (abs.)" << endl;
    cout << "\t- [8] všetko" << endl;
    cout << "Vaša voľba: ";
    string vyhladavanieVzdelavanie;
    std::getline(cin, vyhladavanieVzdelavanie);

    CriterionNazov meno;
    CriterionUJTyp typUJ;
    OstatneUdaje *findOstatne = nullptr;

    StoredData *odlozenie = findData->getVzdelavanie();
    if (odlozenie != nullptr) {
        findOstatne = dynamic_cast<OstatneUdaje *>(odlozenie);
    } else {
        changeColor(Color::Red);
        cout << "Informácie o vzdelávaní neboly nájdené." << endl;
    }


    //----------- Informácie o UJ ----------------
    cout << endl;
    changeColor(Color::BrightGreen);
    cout << "Všeobecné informácie: " << endl;
    changeColor(Color::Green);
    switch (typUJ.evaluate(*findData)) {

        case UJTyp::Stat:
            cout << "Typ UJ: Štát" << endl;
            vypisIformacie(findData, "");
            break;
        case UJTyp::Kraj:
            cout << "Typ UJ: Kraj" << endl;
            vypisIformacie(findData, "");
            cout << "VUJ: \n\t->" << codeIndex->find(findData->at(5).substr(5,2))->getOfficialTitle();
            cout << ", Typ UJ: Štát" << endl;
            break;
        case UJTyp::Okres:
            cout << "Typ UJ: Okres" << endl;
            vypisIformacie(findData, "");
            cout << "VUJ: \n\t->" << codeIndex->find(findData->getCode().substr(0,5))->getOfficialTitle();
            cout << ", Typ UJ: Kraj" << endl;
            cout << "\t->" << codeIndex->find(findData->getCode().substr(0,2))->getOfficialTitle();
            cout << ", Typ UJ: Štát" << endl;
            break;
        case UJTyp::Obec:
            cout << "Typ UJ: Okres" << endl;
            vypisIformacie(findData, "");
            cout << "VUJ: \n\t->" << codeIndex->find(findData->getCode().substr(0,6))->getOfficialTitle();
            cout << ", Typ UJ: Okres" << endl;
            cout << "\t->" << codeIndex->find(findData->getCode().substr(0,5))->getOfficialTitle();
            cout << ", Typ UJ: Kraj" << endl;
            cout << "\t->" << codeIndex->find(findData->getCode().substr(0,2))->getOfficialTitle();
            cout << ", Typ UJ: Štát" << endl;
            break;
    }
    //----------- Vzdelavanie ----------------
    if (findOstatne != nullptr) {
        CriterionVZPocet *vzPocet;
        if (vyhladavanieVzdelavanie.compare("") == 0) {
            vyhladavanieVzdelavanie = "9";
        }
        // Aby sa nevytváralo kritérium z rozsahu ktoré nemôže vártiť
        if (stoi(vyhladavanieVzdelavanie) <= 7 && stoi(vyhladavanieVzdelavanie) >= 0) {
            vzPocet = new CriterionVZPocet(stoi(vyhladavanieVzdelavanie));
        } else {
            vzPocet = new CriterionVZPocet(0);
        }
        if (stoi(vyhladavanieVzdelavanie) <= 8 && stoi(vyhladavanieVzdelavanie) >= 0) {
            changeColor(Color::BrightGreen);
            cout << "Vzdelávanie Informácie: " << endl;
        }
        changeColor(Color::DarkGren);
        switch (stoi(vyhladavanieVzdelavanie)) {
            case 0:
                cout << "Bez ukončeného vzdelania – osoby vo veku 0-14 rokov (abs.): "
                     << vzPocet->evaluate(*findData) << endl;
                break;
            case 1:
                cout << "Základné vzdelanie (abs.): " << vzPocet->evaluate(*findData) << endl;
                break;
            case 2:
                cout << "Stredné odborné (učňovské) vzdelanie (bez maturity) (abs.): "
                     << vzPocet->evaluate(*findData) << endl;
                break;
            case 3:
                cout << "Úplné stredné vzdelanie (s maturitou) (abs.): " << vzPocet->evaluate(*findData) << endl;
                break;
            case 4:
                cout << "Vyššie odborné vzdelanie (abs.): " << vzPocet->evaluate(*findData) << endl;
                break;
            case 5:
                cout << "Vysokoškolské vzdelanie (abs.): " << vzPocet->evaluate(*findData) << endl;
                break;
            case 6:
                cout << "Bez školského vzdelania – osoby vo veku 15 rokov a viac (abs.): "
                     << vzPocet->evaluate(*odlozenie) << endl;
                break;
            case 7:
                cout << "Nezistené (abs.): " << vzPocet->evaluate(*findData) << endl;
                break;
            case 8:
                cout << "Bez ukončeného vzdelania – osoby vo veku 0-14 rokov (abs.): " << findOstatne->intAt(0) << endl;
                cout << "Základné vzdelanie (abs.): " << findOstatne->intAt(1) << endl;
                cout << "Stredné odborné (učňovské) vzdelanie (bez maturity) (abs.): " << findOstatne->intAt(2) << endl;
                cout << "Úplné stredné vzdelanie (s maturitou) (abs.): " << findOstatne->intAt(3) << endl;
                cout << "Vyššie odborné vzdelanie (abs.): " << findOstatne->intAt(4) << endl;
                cout << "vysokoškolské vzdelanie (abs.): " << findOstatne->intAt(5) << endl;
                cout << "Bez školského vzdelania – osoby vo veku 15 rokov a viac (abs.): " << findOstatne->intAt(6)
                     << endl;
                cout << "Nezistené (abs.): " << findOstatne->intAt(7) << endl;
                break;
            default:
                break;
        }

        delete vzPocet;
    }
}


void Aplikacia::vypisIformacie(StoredData *data, string odsadenie) {
    cout << odsadenie << "SortNumber: " << data->at(0) << endl;
    cout << odsadenie << "Code: " << data->at(1)<< endl;
    cout << odsadenie << "OfficialTitle: " << data->at(2)<< endl;
    cout << odsadenie << "MediumTitle: " << data->at(3)<< endl;
    cout << odsadenie << "ShortTitle: " << data->at(4)<< endl;
    cout << odsadenie << "Note: " << data->at(5)<< endl;
}

void Aplikacia::filtrovanie() {
    structures::UnsortedSequenceTable<string, StoredData *> *dataToSort = new structures::UnsortedSequenceTable<string, StoredData *>;

    changeColor(Color::BrightBlue);
    cout << "------------------------- Filtrovanie -------------------------" << endl;
    resetColor();
    cout << "Poznámka: Filtre sa dajú preskočiť s Enterom" << endl;
    //cout << "\t \t  Keď chcte vyhľadávať KRAJ alebo OKRES, treba to tam napísať, napr.: Trenčiansky kraj, Okres Trenčín" << endl;

    string filtUJPrisl;
    string filtUJTyp;
    string tmp;
    //------------------- Filter Typ UJ -------------------
    changeColor(Color::BrightBlue);
    cout << "Všeobecné informácie" << endl;
    changeColor(Color::DarkBlue);
    cout << "\tFilter typ UJ ";
    resetColor();
    cout << "(Štát, Kraj, Okres, Obec)";
    changeColor(Color::DarkBlue);
    cout <<": ";
    std::getline(cin, filtUJTyp);

    UJTyp targetTyp = prelozNaUJTyp(filtUJTyp);

    //------------------- Filter príslunšnoť k UJ -------------------
    changeColor(Color::DarkBlue);
    cout << "\tFilter príslušnosť k VUJ ";
    resetColor();
    cout << "(napr.: Trenčiansky kraj, Okres Trenčín, Slovensko...)";
    changeColor(Color::DarkBlue);
    cout <<": ";
    std::getline(cin, filtUJPrisl);

    StoredData *targetUJ;
    if (filtUJPrisl.compare("") == 0) {
        // dávam natvordo slovensko, kedže pod slovenskom patrí všetko
        targetUJ = codeIndex->find("SK");
    } else {
        try {
            targetUJ = nameIndex->find(filtUJPrisl);
        } catch (std::out_of_range) {
            changeColor(Color::Red);
            cout << "!! Zadaná UJ nebol nájdená, Budem ju ignorovať!!" << endl;
            // keď sa nenájde nič tak sa tam natvrdo dáva slovensko, keďže pod slovensko patrí všetko ostatné
            targetUJ = codeIndex->find("SK");
        }
    }
    // Keď chcem ukazať iba štát tak v tom prípade je target typ tiež štát a preto sa to musí obýsť
    if (targetTyp == targetUJ->getUJTyp() && targetTyp != UJTyp::Stat) {
        changeColor(Color::Red);
        cout << "!! Zadaná UJ má rovnaký UJ typ ako zadaný filter UJ. Filter budem ignorovať!!" << endl;
        // keď sa nenájde nič tak sa tam natvrdo dáva slovensko, keďže pod slovensko patrí všetko ostatné
        targetUJ = codeIndex->find("SK");
    }

    if (UJTyp::Kraj == targetUJ->getUJTyp() && targetTyp == UJTyp::Stat) {
        changeColor(Color::Red);
        cout << "!! Filter Príslušnosť k UJ musí mať väčšiu UJ ako bola zadaná vo filtri typUJ. Filter budem ignorovať!!" << endl;
        // keď sa nenájde nič tak sa tam natvrdo dáva slovensko, keďže pod slovensko patrí všetko ostatné
        targetUJ = codeIndex->find("SK");
    }
    if (UJTyp::Okres == targetUJ->getUJTyp() && (targetTyp == UJTyp::Stat || targetTyp == UJTyp::Kraj)) {
        changeColor(Color::Red);
        cout << "!! Filter Príslušnosť k UJ musí mať väčšiu UJ ako bola zadaná vo filtri typUJ. Filter budem ignorovať!!" << endl;
        // keď sa nenájde nič tak sa tam natvrdo dáva slovensko, keďže pod slovensko patrí všetko ostatné
        targetUJ = codeIndex->find("SK");
    }
    if (targetUJ->getUJTyp() == UJTyp::Obec) {
        changeColor(Color::Red);
        cout << "!! Nemôže byť zadaná obec. Filter budem ignorovať!!" << endl;
        // keď sa nenájde nič tak sa tam natvrdo dáva slovensko, keďže pod slovensko patrí všetko ostatné
        targetUJ = codeIndex->find("SK");
    }

    //-------------------------------------- VZDELAVANIE --------------------------------------
    CompositeFilter *compositeFilter = nullptr;
    bool findCriterion = false;
    bool itsCritPoc = false;
    bool itsCritPod = false;
    int pIndex;


    changeColor(Color::BrightBlue);
    cout << "Vzdelávanie" << endl;
    changeColor(Color::Red);
    cout << "!! Ak sa rozhodnete aplikovať filter, MUSIA byť vyplnené všetky parametre !!" << endl;
    cout << "!! Ak chcete zadávať iba 1 filter (v skupine) pre spájanie vyberte AND !!" << endl;

    changeColor(Color::DarkBlue);
    cout << "Aplikovať filtre pre vzdelávanie? \n\t[1] Áno \n\t[0] Nie \nVoľba: ";
    string vzVolbaApl;
    int vzVolbaAplikovat;
    getline(cin, vzVolbaApl);
    if (vzVolbaApl.compare("1") == 0) {
        vzVolbaAplikovat = 1;
    } else {
        vzVolbaAplikovat = 0;
    }

    int cislovanieFitrlov = 0;
    if (vzVolbaAplikovat == 1) {
        cout << "Ktorý typ chcete použiť? " << endl;
        cout << "\t[0] Filter POČET VZ" << endl;
        cout << "\t[1] Filter PODIEL VZ" << endl;
        cout << "\t[2] Počet a Podiel" << endl;
        cout << "Voľba: ";
        int volbaTypu;
        cin >> volbaTypu;

        int volbaSpojenia;
        if (volbaTypu == 2) {
            int volba;
            cout << "\t\tAko chcete spájať filter POČET?" << endl;
            cout << "\t\t\t[0] filter AND filter" << endl;
            cout << "\t\t\t[1] filter OR filter" << endl;
            cout << "\t\tVoľba: ";
            cin >> volba;
            CompositeFilter *pocet;
            switch (volba) {
                case 0:
                    pocet = new AND_Filter;
                    break;
                default:
                    pocet = new OR_Filter;
                    break;
            }
            changeColor(Color::Cyan);
            vypisVZmenu();
            while (true) {
                cislovanieFitrlov++;
                changeColor(Color::Red);
                cout << "Filter číslo: " << cislovanieFitrlov << endl;
                changeColor(Color::DarkBlue);
                auto newFilter = filterPocet(cislovanieFitrlov, pIndex, findCriterion, itsCritPoc);
                if (newFilter != nullptr) {
                    pocet->registerFilter(newFilter);
                }
                changeColor(Color::BrightBlue);
                cout << "Chcete zadať znovu Filter?" << endl;
                cout << "\t[1] Áno" << endl;
                cout << "\t[0] Nie" << endl;
                cout << "Voľba: ";
                int pokracovanie;
                cin >> pokracovanie;
                if (pokracovanie != 1 ) {
                    break;
                }
            }

            changeColor(Color::DarkBlue);
            cout << "\t\tAko chcete spájať filter PODIEL?" << endl;
            cout << "\t\t\t[0] filter AND filter" << endl;
            cout << "\t\t\t[1] filter OR filter" << endl;
            cout << "\t\tVoľba: ";

            cin >> volba;
            CompositeFilter *podiel;
            switch (volba) {
                case 0:
                    podiel = new AND_Filter;
                    break;
                default:
                    podiel = new OR_Filter;
                    break;
            }
            changeColor(Color::Cyan);
            vypisVZmenu();
            while (true) {
                cislovanieFitrlov++;
                changeColor(Color::Red);
                cout << "Filter číslo: " << cislovanieFitrlov << endl;
                changeColor(Color::DarkBlue);
                auto newFilter = filterPodiel(cislovanieFitrlov, pIndex, findCriterion, itsCritPod);
                if (newFilter != nullptr) {
                    podiel->registerFilter(newFilter);
                }
                changeColor(Color::BrightBlue);
                cout << "Chcete zadať znovu Filter?" << endl;
                cout << "\t[1] Áno" << endl;
                cout << "\t[0] Nie" << endl;
                cout << "Voľba: ";
                int pokracovanie;
                cin >> pokracovanie;
                if (pokracovanie != 1 ) {
                    break;
                }
            }

            changeColor(Color::DarkBlue);
            cout << "\t\tAko chcete spájať oba filtre?" << endl;
            cout << "\t\t\t[0] filter1 AND filter2" << endl;
            cout << "\t\t\t[1] filter1 OR filter2" << endl;
            cout << "\t\tVoľba: ";
            cin >> volba;
            switch (volba) {
                case 0:
                    compositeFilter = new AND_Filter;
                    break;
                default:
                    compositeFilter = new OR_Filter;
                    break;
            }

            compositeFilter->registerFilter(pocet);
            compositeFilter->registerFilter(podiel);

        } else {
            cout << "\t\tAko chcete spájať filtre?" << endl;
            cout << "\t\t\t[0] filter AND filter" << endl;
            cout << "\t\t\t[1] filter OR filter" << endl;
            cout << "\t\tVoľba: ";
            cin >> volbaSpojenia;
            switch (volbaSpojenia) {
                case 0:
                    compositeFilter = new AND_Filter;
                    break;
                default:
                    compositeFilter = new OR_Filter;
                    break;
            }
            changeColor(Color::Cyan);
            vypisVZmenu();
            while (true) {
                cislovanieFitrlov++;
                changeColor(Color::Red);
                cout << "Filter číslo: " << cislovanieFitrlov << endl;
                changeColor(Color::DarkBlue);
                Filter *newFilter;
                if (volbaTypu == 0) {
                    newFilter = filterPocet(cislovanieFitrlov, pIndex, findCriterion, itsCritPoc);
                } else if (volbaTypu == 1) {
                    newFilter = filterPodiel(cislovanieFitrlov, pIndex, findCriterion, itsCritPod);
                }
                if (newFilter != nullptr) {
                    compositeFilter->registerFilter(newFilter);
                }

                changeColor(Color::BrightBlue);
                cout << "Chcete zadať znovu Filter?" << endl;
                cout << "\t[1] Áno" << endl;
                cout << "\t[0] Nie" << endl;
                cout << "Voľba: ";
                int pokracovanie;
                cin >> pokracovanie;
                if (pokracovanie != 1 ) {
                    break;
                }
            }
        }
        getline(cin, tmp);
    }

    //getline(cin, tmp);
    if (compositeFilter == nullptr) {
        compositeFilter = new AND_Filter;
    }


    //------------------------------------------ Jadro filtrovania ------------------------------------------
    //------------------ Stat ------------------
    auto ixStat = codeIndex->find("SK");
    if ((targetTyp == UJTyp::Stat || targetTyp == UJTyp::Neoznacene) && compositeFilter->pass(*ixStat) && targetUJ->getUJTyp() == UJTyp::Stat) {
        dataToSort->insert(ixStat->getCode(), ixStat);
    }
    auto arrKraj = statIndex->find("SK");
    if (targetTyp == UJTyp::Kraj || targetTyp == UJTyp::Okres || targetTyp == UJTyp::Obec || targetTyp == UJTyp::Neoznacene) {
        //------------------ Kraj ------------------
        for (auto ixKraj: *arrKraj) {
            // overí sa či kraj nepatrí do targetu
            // alebo target nepatrí do kraju
            if (ixKraj->getCode().compare(targetUJ->getCode()) != 0 && targetUJ->getUJTyp() == UJTyp::Kraj) {
                continue;
            }
            if (targetUJ->getUJTyp() == UJTyp::Stat && !ixKraj->belongsTo(*targetUJ)) {
                continue;
            }
            if (targetUJ->getUJTyp() == UJTyp::Okres && !ixKraj->belongsMe(targetUJ)) {
                continue;
            }

            if ((targetTyp == UJTyp::Kraj || targetTyp == UJTyp::Neoznacene) && compositeFilter->pass(*ixKraj) && targetUJ->belongsMe(ixKraj)) {
                dataToSort->insert(ixKraj->getCode(), ixKraj);
            }

            if (targetTyp == UJTyp::Okres || targetTyp == UJTyp::Obec || targetTyp == UJTyp::Neoznacene) {
                //------------------ Okres ------------------
                auto arrOkres = krajIndex->find(ixKraj->at(5));
                for (auto ixOkres: *arrOkres) {
                    // overí sa či kraj nepatrí do targetu
                    // alebo target nepatrí do kraju
                    if (ixOkres->getCode().compare(targetUJ->getCode()) != 0 && targetUJ->getUJTyp() == UJTyp::Okres) {
                        continue;
                    }
                    if (targetUJ->getUJTyp() == UJTyp::Stat && !ixOkres->belongsTo(*targetUJ)) {
                        continue;
                    }

                    if ((targetTyp == UJTyp::Okres || targetTyp == UJTyp::Neoznacene) && compositeFilter->pass(*ixOkres) && targetUJ->belongsMe(ixOkres)) {
                        dataToSort->insert(ixOkres->getCode(), ixOkres);
                    }

                    if (targetTyp == UJTyp::Obec || targetTyp == UJTyp::Neoznacene) {
                        //------------------ Obec ------------------
                        auto arrObec = okresIndex->find(ixOkres->getCode());
                        for (auto ixObce: *arrObec) {
                            if (ixObce->belongsTo(*targetUJ) == false) {
                                continue;
                            }

                            if ((targetTyp == UJTyp::Obec || targetTyp == UJTyp::Neoznacene) && compositeFilter->pass(*ixObce)) {
                                dataToSort->insert(ixObce->getCode(), ixObce);
                            }
                        }
                    }

                }
            }

        }
    }
    if (findCriterion) {
        changeColor(Color::Yellow);
        cout << "Chcete triediť zostupne?" << endl;
        cout << "\tÁno [1] \n\tNie [0]\nVaša voľba: ";
        int volba;
        cin >> volba;
        bool zozstupne = false;
        if (volba == 1) {
            zozstupne = true;
        }
        if (itsCritPoc) {
            ShellSort<int> sort;
            CriterionVZPocet *criterion = new CriterionVZPocet(pIndex);
            sort.sordData(*dataToSort, criterion, zozstupne);
            delete criterion;
        } else {
            ShellSort<double> sort;
            CriterionVZPodiel* criterion = new CriterionVZPodiel(pIndex);
            sort.sordData(*dataToSort, criterion, zozstupne);
            delete criterion;
        }
    } else {
        changeColor(Color::Yellow);
        cout << "Chcete triediť podla mena?" << endl;
        cout << "\tÁno [1] \n\tNie [0]\nVaša voľba: ";
        int volba;
        cin >> volba;
        if (volba == 1) {
            ShellSort<string> sort;
            CriterionNazov *nazov = new CriterionNazov;
            cout << "Chcete triediť zostupne?" << endl;
            cout << "\tÁno [1] \n\tNie [0]\nVaša voľba: ";
            cin >> volba;
            if (volba == 1) {
                sort.sordData(*dataToSort, nazov, true);
            } else {
                sort.sordData(*dataToSort, nazov, false);
            }
            delete nazov;
        }
    }

    //---------------------------------------- Výpis ----------------------------------------
    for (auto item: *dataToSort) {
        switch (item->accessData()->getUJTyp()) {

            case UJTyp::Stat:
                changeColor(Color::Red);
                cout << "Typ UJ: " << prelozUJTypNaString(item->accessData()->getUJTyp()) << endl;
                resetColor();
                cout << "Názov UJ: " << item->accessData()->getOfficialTitle() << endl;
                changeColor(Color::Cyan);
                compositeFilter->coutEvaluate(*item->accessData(),"hodnota kritéria: ");
                cout << endl;
                break;
            case UJTyp::Kraj:
                changeColor(Color::Green);
                cout << "\t" << "Typ UJ: " << prelozUJTypNaString(item->accessData()->getUJTyp()) << endl;
                resetColor();
                cout << "\t" << "Názov UJ: " << item->accessData()->getOfficialTitle() << endl;
                changeColor(Color::Cyan);
                cout << "\t";
                compositeFilter->coutEvaluate(*item->accessData(),"hodnota kritéria: ");
                cout << endl;
                changeColor(Color::DarkBlue);
                cout << "\t" << "VUJ:" << endl;
                cout << "\t\t-> " << codeIndex->find(vypocetVUJ(item->accessData(), UJTyp::Stat))->getOfficialTitle() << ". Typ UJ: Štát" << endl;
                break;
            case UJTyp::Okres:
                changeColor(Color::Magenta);
                cout << "\t\t" << "Typ UJ: " << prelozUJTypNaString(item->accessData()->getUJTyp()) << endl;
                resetColor();
                cout << "\t\t" << "Názov UJ: " << item->accessData()->getOfficialTitle() << endl;
                changeColor(Color::Cyan);
                cout << "\t\t";
                compositeFilter->coutEvaluate(*item->accessData(),"hodnota kritéria: ");
                cout << endl;
                changeColor(Color::DarkBlue);
                cout << "\t\t" << "VUJ:" << endl;
                cout << "\t\t\t-> " << codeIndex->find(vypocetVUJ(item->accessData(), UJTyp::Stat))->getOfficialTitle() << ". Typ UJ: Štát" << endl;
                cout << "\t\t\t-> " << codeIndex->find(vypocetVUJ(item->accessData(), UJTyp::Kraj))->getOfficialTitle() << ". Typ UJ: Kraj" << endl;
                break;
            case UJTyp::Obec:
                changeColor(Color::Yellow);
                cout << "\t\t\t" << "Typ UJ: " << prelozUJTypNaString(item->accessData()->getUJTyp()) << endl;
                resetColor();
                cout << "\t\t\t" << "Názov UJ: " << item->accessData()->getOfficialTitle() << endl;
                changeColor(Color::Cyan);
                cout << "\t\t\t";
                compositeFilter->coutEvaluate(*item->accessData(),"hodnota kritéria: ");
                cout << endl;
                changeColor(Color::DarkBlue);
                cout << "\t\t\t" << "VUJ:" << endl;
                cout << "\t\t\t\t-> " << codeIndex->find(vypocetVUJ(item->accessData(), UJTyp::Stat))->getOfficialTitle() << ". Typ UJ: Štát" << endl;
                cout << "\t\t\t\t-> " << codeIndex->find(vypocetVUJ(item->accessData(), UJTyp::Kraj))->getOfficialTitle() << ". Typ UJ: Kraj" << endl;
                cout << "\t\t\t\t-> " << codeIndex->find(vypocetVUJ(item->accessData(), UJTyp::Okres))->getOfficialTitle() << ". Typ UJ: Okres" << endl;
                break;
            case UJTyp::Neoznacene:
                break;
        }
        cout << endl;
    }


    delete dataToSort;
    delete compositeFilter;
    resetColor();
    getline(cin, tmp);
}

string Aplikacia::vypocetVUJ(StoredData *data, UJTyp uroven) {
    switch (uroven) {

        case UJTyp::Stat:
            if (data->getUJTyp() == UJTyp::Kraj) {
                return krajGetCode(data).substr(0,2);
            } else {
                return data->getCode().substr(0,2);
            }
        case UJTyp::Kraj:
            return data->getCode().substr(0,5);
        case UJTyp::Okres:
            return data->getCode().substr(0,6);
    }
}


string Aplikacia::krajGetCode(StoredData *data) {
    return data->at(5).substr(5, string::npos);
}
void Aplikacia::vycistiTable(structures::Table<string, StoredData *> *table) {
    for (auto item: *table) {
        delete item->accessData();
    }
}

void Aplikacia::vicistiIndex(structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> *pTable) {
    for (auto item: *pTable) {
        delete item->accessData();
        item->accessData() = nullptr;
    }
}

void Aplikacia::changeColor(Color color) {
    switch (color) {
        case Color::Red:
            cout << "\x1B[91m";
            break;

        case Color::BrightGreen:
            cout << "\x1B[92m";
            break;
        case Color::Green:
            cout << "\x1B[38;5;41m";
            break;
        case Color::DarkGren:
            cout << "\x1B[38;5;34m";
            break;

        case Color::BrightBlue:
            cout << "\x1B[94m";
            break;

        case Color::DarkBlue:
            cout << "\x1B[38;5;27m";
            break;

        case Color::Yellow:
            cout << "\x1B[93m";
            break;

        case Color::Magenta:
            cout << "\x1B[95m";
            break;

        case Color::Cyan:
            cout << "\x1B[96m";
            break;

        case Color::White:
            cout << "\x1B[97m";
            break;

        default:
            cout << "\x1B[97m";
            break;
    }
}

void Aplikacia::resetColor() {
    cout << "\x1B[0m"; // reset farby na zakladne
}

UJTyp Aplikacia::prelozNaUJTyp(string naPreklad) {
    if (naPreklad.compare("Štát") == 0) {
        return UJTyp::Stat;
    } else if (naPreklad.compare("Kraj") == 0) {
        return UJTyp::Kraj;
    } else if (naPreklad.compare("Kraje") == 0) {
        return UJTyp::Kraj;
    } else if (naPreklad.compare("Okres") == 0) {
        return UJTyp::Okres;
    } else if (naPreklad.compare("Obec") == 0) {
        return UJTyp::Obec;
    } else if (naPreklad.compare("Obce") == 0) {
        return UJTyp::Obec;
    } else if (naPreklad.compare("") == 0){
        return UJTyp::Neoznacene;
    } else {
        changeColor(Color::Red);
        cout << "Zle zadany parameter UJ typu, budem tento filter ignorovať!" << endl;
        resetColor();
        return UJTyp::Neoznacene;
    }
}

Filter *Aplikacia::filterPocet(int filterId, int &pIndex, bool &findCrit, bool &itsCritPoc) {
    int maxVZmenu = 7;
    int minVZmenu = 0;
    string tmp;
    changeColor(Color::DarkBlue);
    cout << "Filter Počet v zadanej skupine \n\t-> zadajte index: ";
    int indexFilter;
    cin >> indexFilter;

    if (indexFilter > maxVZmenu || indexFilter < minVZmenu) {
        changeColor(Color::Red);
        cout << "!! Zle zadaný index. Filter budem ignorovať!!" << endl;
        return nullptr;
    }
    int min;
    int max;
    resetColor();
    cout << "\t(Rozsah pre filter je určený <0, 2 000 000>)";
    changeColor(Color::Red);
    cout << "!!Zadávajte iba čísla!!" << endl;
    changeColor(Color::DarkBlue);
    cout << "\t-> zadajte min: ";
    cin >> min;
    cout << "\t-> zadajte max: ";
    cin >> max;
    // služi na odchitenie enteru ktorý cin nezachil predtým
    std::getline(cin, tmp);
    auto filter = new FilterVzPocet(indexFilter, min, max);
    filter->id(filterId);
    if (!findCrit) {
        changeColor(Color::Yellow);
        cout << "Chcete Triediť podľa tohto filtra?" << endl;
        cout << "\tÁno [1] \n\tNie [0]\nVaša voľba: ";
        int volba;
        cin >> volba;
        if  (volba == 1) {
            pIndex = indexFilter;
            findCrit = true;
            itsCritPoc = true;
        }
    }
    return filter;


}

Filter *Aplikacia::filterPodiel(int filterId, int &pIndex, bool &findCrit, bool &itsCritPod) {
    int maxVZmenu = 7;
    int minVZmenu = 0;
    string tmp;
    changeColor(Color::DarkBlue);
    cout << "Filter Podiel v zadanej skupine \n\t-> zadajte index: ";
    int indexFilter;
    cin >> indexFilter;
    if (indexFilter > maxVZmenu || indexFilter < minVZmenu) {
        changeColor(Color::Red);
        cout << "!! Zle zadaný index. Filter budem ignorovať!!" << endl;
        return nullptr;
    }
    double min;
    double max;
    resetColor();
    cout << "\t(Rozsah pre filter je určený <0, 100>)";
    changeColor(Color::Red);
    cout << "!!Zadávajte iba čísla!!" << endl;
    changeColor(Color::DarkBlue);
    cout << "\t-> zadajte min: ";
    cin >> min;
    cout << "\t-> zadajte max: ";
    cin >> max;
    // služi na odchitenie enteru ktorý cin nezachil predtým
    std::getline(cin, tmp);
    auto filter = new FilterVzPodiel(indexFilter, min, max);
    filter->id(filterId);
    if (!findCrit) {
        changeColor(Color::Yellow);
        cout << "Chcete Triediť podľa tohto filtra?" << endl;
        cout << "\tÁno [1] \n\tNie [0]\nVaša voľba: ";
        int volba;
        cin >> volba;
        if  (volba == 1) {
            pIndex = indexFilter;
            findCrit = true;
            itsCritPod = true;
        }
    }
    return filter;

}



void Aplikacia::vypisVZmenu() {
    cout << "Filtrovať podľa:" << endl;
    cout << "\t- [0] Bez ukončeného vzdelania – osoby vo veku 0-14 rokov (abs.)" << endl;
    cout << "\t- [1] Základné vzdelanie (abs.)" << endl;
    cout << "\t- [2] Stredné odborné (učňovské) vzdelanie (bez maturity) (abs.)" << endl;
    cout << "\t- [3] Úplné stredné vzdelanie (s maturitou) (abs.)" << endl;
    cout << "\t- [4] Vyššie odborné vzdelanie (abs.)" << endl;
    cout << "\t- [5] Vysokoškolské vzdelanie (abs.)" << endl;
    cout << "\t- [6] Bez školského vzdelania – osoby vo veku 15 rokov a viac (abs.)" << endl;
    cout << "\t- [7] Nezistené (abs.)" << endl;
}

string Aplikacia::prelozUJTypNaString(UJTyp typ) {
    switch (typ) {
        case UJTyp::Stat:
            return "Štát";
        case UJTyp::Kraj:
            return "Kraj";
        case UJTyp::Okres:
            return "Okres";
        case UJTyp::Obec:
            return "Obec";
        case UJTyp::Neoznacene:
            return "Neoznačené";
    }
}
