//
// Created by Tobias on 21/05/2022.
//

#include "aplikacia.h"
#include "Criterion/criterionNazov.h"
#include "Criterion/criterionUJTyp.h"
#include "Criterion/criterionVZPocet.h"

Aplikacia::Aplikacia() :
        stat(new structures::UnsortedSequenceTable<wstring, StoredData*>),
        kraj(new structures::UnsortedSequenceTable<wstring, StoredData*>),
        okres(new structures::UnsortedSequenceTable<wstring, StoredData*>),
        obec(new structures::UnsortedSequenceTable<wstring, StoredData*>),
        vzdelanieObec(new structures::SortedSequenceTable<wstring, StoredData*>),
        vzdelanieOkres(new structures::SortedSequenceTable<wstring, StoredData*>),
        vzdelanieKraj(new structures::SortedSequenceTable<wstring, StoredData*>),
        vzdelanieStat(new structures::SortedSequenceTable<wstring, StoredData*>),
        nameIndex(new structures::SortedSequenceTable<wstring, StoredData*>),
        codeIndex(new structures::SortedSequenceTable<wstring, StoredData*>),
        statIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>),
        krajIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>),
        okresIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>)
{
    auto *slovensko = new UzemnaJednotka(UJTyp::Stat, L"1", L"SK", L"Slovenska republika", L"Slovensko", L"Slovensko", L"1");
    stat->insert(slovensko->getCode(), slovensko);
    auto *zahranicie = new UzemnaJednotka(UJTyp::Stat, L"2", L"ZZ", L"Zahranicie", L"", L"", L"2");
    stat->insert(zahranicie->getCode(), zahranicie);

    changeColor(Color::Cyan);
    TableLoader tableLoader;
    cout << "Načitávam dáta ";
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
    cout << "Spracuvávam dáta - vzdelavanie ";
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
    cout << "--------------------- SEMESTRALNA PRACA ---------------------" << endl;
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
    cout << "Menu? \n\tAno [1] \n\tNie [0]\nVolba: ";
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
    cout << "--------------------- Bodove vyhľadávanie ---------------------" << endl;
    resetColor();
    cout << "Poznámka: parametre s \"*\" NIEsu povinné, ENTEROM sa preskočia." << endl;
    cout << "\t \t  Keď chcte vyhľadávať KRAJ alebo OKRES, treba to tam napísať, napr.: Trenčiansky kraj, Okres Trenčín" << endl;
    changeColor(Color::Green);
    cout << "Zadaj názov: ";
    wstring vyhladavaneMeno;
    std::getline(wcin, vyhladavaneMeno);

    StoredData *findData;
    try {
        findData = nameIndex->find(vyhladavaneMeno);
    } catch (std::out_of_range) {
        changeColor(Color::Red);
        cout << "Vami zadaná UJ nebola nájdena!" << endl;
        return;
    }

    changeColor(Color::DarkGren);
    cout << "*Vzdelavanie "<< endl;
    cout << "\t- [0] Bez ukončeného vzdelania – osoby vo veku 0-14 rokov (abs.)" << endl;
    cout << "\t- [1] Základné vzdelanie (abs.)" << endl;
    cout << "\t- [2] Stredné odborné (učňovské) vzdelanie (bez maturity) (abs.)" << endl;
    cout << "\t- [3] Úplné stredné vzdelanie (s maturitou) (abs.)" << endl;
    cout << "\t- [4] Vyššie odborné vzdelanie (abs.)" << endl;
    cout << "\t- [5] vysokoškolské vzdelanie (abs.)" << endl;
    cout << "\t- [6] Bez školského vzdelania – osoby vo veku 15 rokov a viac (abs.)" << endl;
    cout << "\t- [7] Nezistené (abs.)" << endl;
    cout << "\t- [8] všetko" << endl;
    cout << "Vaša volba: ";
    string vyhladavanieVzdelavanie;
    std::getline(cin, vyhladavanieVzdelavanie);

    CriterionNazov meno;
    CriterionUJTyp typUJ;
    OstatneUdaje *findOstatne;

    StoredData *odlozenie;
    try {
        switch (typUJ.evaluate(*findData)) {

            case UJTyp::Stat :
                odlozenie = vzdelanieStat->find(findData->getCode());
                break;
            case UJTyp::Kraj :
                odlozenie = vzdelanieKraj->find(findData->getCode());
                break;
            case UJTyp::Okres :
                odlozenie = vzdelanieOkres->find(findData->getCode());
                break;
            case UJTyp::Obec :
                odlozenie = vzdelanieObec->find(findData->getCode());
                break;
        }
        findOstatne = dynamic_cast<OstatneUdaje *>(odlozenie);

    } catch (std::out_of_range) {
        changeColor(Color::Red);
        cout << "Informácie o vzdelávani nebolí nájdené." << endl;
    }

    //----------- Informácie o UJ ----------------
    cout << endl;
    changeColor(Color::BrightGreen);
    cout << "Všeobecné informácie: " << endl;
    changeColor(Color::Green);
    switch (typUJ.evaluate(*findData)) {

        case UJTyp::Stat:
            cout << "Typ UJ: Štát" << endl;
            vypisIformacie(findData, L"");
            break;
        case UJTyp::Kraj:
            cout << "Typ UJ: Kraj" << endl;
            vypisIformacie(findData, L"");
            wcout << "VUJ: \n\t->" << codeIndex->find(findData->at(5).substr(5,2))->getOfficialTitle();
            cout << ", Typ UJ: Štát" << endl;
            break;
        case UJTyp::Okres:
            cout << "Typ UJ: Okres" << endl;
            vypisIformacie(findData, L"");
            wcout << "VUJ: \n\t->" << codeIndex->find(findData->getCode().substr(0,5))->getOfficialTitle();
            cout << ", Typ UJ: Kraj" << endl;
            wcout << "\t->" << codeIndex->find(findData->getCode().substr(0,2))->getOfficialTitle();
            cout << ", Typ UJ: Štát" << endl;
            break;
        case UJTyp::Obec:
            cout << "Typ UJ: Okres" << endl;
            vypisIformacie(findData, L"");
            wcout << "VUJ: \n\t->" << codeIndex->find(findData->getCode().substr(0,6))->getOfficialTitle();
            cout << ", Typ UJ: Okres" << endl;
            wcout << "\t->" << codeIndex->find(findData->getCode().substr(0,5))->getOfficialTitle();
            cout << ", Typ UJ: Kraj" << endl;
            wcout << "\t->" << codeIndex->find(findData->getCode().substr(0,2))->getOfficialTitle();
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
                     << vzPocet->evaluate(*odlozenie) << endl;
                break;
            case 1:
                cout << "Základné vzdelanie (abs.): " << vzPocet->evaluate(*odlozenie) << endl;
                break;
            case 2:
                cout << "Stredné odborné (učňovské) vzdelanie (bez maturity) (abs.): "
                     << vzPocet->evaluate(*odlozenie) << endl;
                break;
            case 3:
                cout << "Úplné stredné vzdelanie (s maturitou) (abs.): " << vzPocet->evaluate(*odlozenie) << endl;
                break;
            case 4:
                cout << "Vyššie odborné vzdelanie (abs.): " << vzPocet->evaluate(*odlozenie) << endl;
                break;
            case 5:
                cout << "vysokoškolské vzdelanie (abs.): " << vzPocet->evaluate(*odlozenie) << endl;
                break;
            case 6:
                cout << "Bez školského vzdelania – osoby vo veku 15 rokov a viac (abs.): "
                     << vzPocet->evaluate(*odlozenie) << endl;
                break;
            case 7:
                cout << "Nezistené (abs.): " << vzPocet->evaluate(*odlozenie) << endl;
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


void Aplikacia::vypisIformacie(StoredData *data, wstring odsadenie) {
    wcout << odsadenie << L"SortNumber: " << data->at(0) << endl;
    wcout << odsadenie << L"Code: " << data->at(1)<< endl;
    wcout << odsadenie << L"OfficialTitle: " << data->at(2)<< endl;
    wcout << odsadenie << L"MediumTitle: " << data->at(3)<< endl;
    wcout << odsadenie << L"ShortTitle: " << data->at(4)<< endl;
    wcout << odsadenie << L"Note: " << data->at(5)<< endl;
}

void Aplikacia::filtrovanie() {
    changeColor(Color::BrightBlue);
    cout << "------------------------- Filtrovanie -------------------------" << endl;
    resetColor();
    cout << "Poznámka: Filtre sa dajú preskočiť s Enterom" << endl;
    //cout << "\t \t  Keď chcte vyhľadávať KRAJ alebo OKRES, treba to tam napísať, napr.: Trenčiansky kraj, Okres Trenčín" << endl;

    wstring filtUJPrisl;
    wstring filtUJTyp;
    int filtVZPocMin;
    int filtVZPocMax;
    int filtVZPodMin;
    int filtVZPodMax;
    wstring tmp;
    changeColor(Color::BrightBlue);
    cout << "Všeobecné informácie" << endl;
    changeColor(Color::DarkBlue);
    cout << "\tFilter typ UJ ";
    resetColor();
    cout << "(Stat, Kraj, Okres, Obec)";
    changeColor(Color::DarkBlue);
    cout <<": ";
    std::getline(wcin, filtUJTyp);

    UJTyp targetTyp = prelozNaUJTyp(filtUJTyp);

    cout << "\tFilter príslušnosť k VUJ ";
    resetColor();
    cout << "(napr.: Trenčiansky kraj, Okres Trenčín, Slovensko...)";
    changeColor(Color::DarkBlue);
    cout <<": ";
    std::getline(wcin, filtUJPrisl);

    changeColor(Color::BrightBlue);
    cout << "Vzdelávanie" << endl;
    changeColor(Color::Red);
    cout << "!! Ak sa rozhodnete aplikovať filter, MUSIA byť vyplnéne všetky parametre !!" << endl;
    changeColor(Color::Cyan);
    cout << "Filtrovať podľa:" << endl;
    cout << "\t- [0] Bez ukončeného vzdelania – osoby vo veku 0-14 rokov (abs.)" << endl;
    cout << "\t- [1] Základné vzdelanie (abs.)" << endl;
    cout << "\t- [2] Stredné odborné (učňovské) vzdelanie (bez maturity) (abs.)" << endl;
    cout << "\t- [3] Úplné stredné vzdelanie (s maturitou) (abs.)" << endl;
    cout << "\t- [4] Vyššie odborné vzdelanie (abs.)" << endl;
    cout << "\t- [5] vysokoškolské vzdelanie (abs.)" << endl;
    cout << "\t- [6] Bez školského vzdelania – osoby vo veku 15 rokov a viac (abs.)" << endl;
    cout << "\t- [7] Nezistené (abs.)" << endl;

    wstring filtPocIndex;
    changeColor(Color::DarkBlue);
    cout << "Filter Počet v zadanej skupine \n\t-> zadajte index: ";
    std::getline(wcin, filtPocIndex);
    if (filtPocIndex.compare(L"") != 0) {
        resetColor();
        cout << "\t(Roz sah pre filter je určený <min, max>)" << endl;
        changeColor(Color::DarkBlue);
        cout << "\t-> zadajte min: ";
        cin >> filtVZPocMin;
        cout << "\t-> zadajte max: ";
        cin >> filtVZPocMax;
        // služi na odchitenie enteru ktorý wcin nezachil predtým
        std::getline(wcin, tmp);
    }

    wstring filtPodIndex;
    changeColor(Color::DarkBlue);
    cout << "Filter Podiel v zadanej skupine \n\t-> zadajte index: ";
    std::getline(wcin, filtPodIndex);
    if (filtPodIndex.compare(L"") != 0) {
        resetColor();
        cout << "\t(Roz sah pre filter je určený <min, max>)" << endl;
        changeColor(Color::DarkBlue);
        cout << "\t-> zadajte min: ";
        cin >> filtVZPodMin;
        cout << "\t-> zadajte max: ";
        cin >> filtVZPodMax;
        // služi na odchitenie enteru ktorý wcin nezachil predtým
        std::getline(wcin, tmp);
    }

//todo dokončiť tak že keď sa narazí na targetTyp tak sa daľej v stromne nepokračuje
    for (auto arrKraj: *statIndex) {
        changeColor(Color::Red);
        auto ixStat = codeIndex->find(arrKraj->getKey());
        if (targetTyp == UJTyp::Stat || targetTyp == UJTyp::Neoznacene) {
            for (int i = 0; i < ixStat->getSize(); ++i) {
                wcout << ixStat->at(i) << L" ";
            }
            wcout << endl;
        }
        for (auto ixKraj: *arrKraj->accessData()) {
            changeColor(Color::Green);
            if (targetTyp == UJTyp::Kraj || targetTyp == UJTyp::Neoznacene) {
                wcout << "\t";
                for (int i = 0; i < ixKraj->getSize(); ++i) {
                    wcout << ixKraj->at(i) << L" ";
                }
                wcout << endl;
            }
            auto arrOkres = krajIndex->find(ixKraj->at(5));
            for (auto ixOkres: *arrOkres) {
                changeColor(Color::Magenta);
                if (targetTyp == UJTyp::Okres || targetTyp == UJTyp::Neoznacene) {
                    wcout << "\t" << "\t";
                    for (int i = 0; i < ixOkres->getSize(); ++i) {
                        wcout << ixOkres->at(i) << L" ";
                    }
                    wcout << endl;
                }
                resetColor();
                auto arrObec = okresIndex->find(ixOkres->getCode());
                for (auto ixObce: *arrObec) {
                    if (targetTyp == UJTyp::Obec || targetTyp == UJTyp::Neoznacene) {
                        wcout << "\t" << "\t" << "\t";
                        for (int i = 0; i < ixObce->getSize(); ++i) {
                            wcout << ixObce->at(i) << L" ";
                        }
                        wcout << endl;
                    }
                }
            }
        }
    }
    resetColor();
}

void Aplikacia::vycistiTable(structures::Table<wstring, StoredData *> *table) {
    for (auto item: *table) {
        delete item->accessData();
    }
}

void Aplikacia::vicistiIndex(structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> *pTable) {
    for (auto item: *pTable) {
        delete item->accessData();
        item->accessData() = nullptr;
    }
}

void Aplikacia::changeColor(Color color) {
    switch (color) {
        case Color::Red:
            wcout << "\x1B[91m";
            break;

        case Color::BrightGreen:
            wcout << "\x1B[92m";
            break;
        case Color::Green:
            wcout << "\x1B[38;5;41m";
            break;
        case Color::DarkGren:
            wcout << "\x1B[38;5;34m";
            break;

        case Color::BrightBlue:
            wcout << "\x1B[94m";
            break;

        case Color::DarkBlue:
            wcout << "\x1B[38;5;27m";
            break;

        case Color::Yellow:
            wcout << "\x1B[93m";
            break;

        case Color::Magenta:
            wcout << "\x1B[95m";
            break;

        case Color::Cyan:
            wcout << "\x1B[96m";
            break;

        case Color::White:
            wcout << "\x1B[97m";
            break;

        default:
            wcout << "\x1B[97m";
            break;
    }
}

void Aplikacia::resetColor() {
    wcout << "\x1B[0m"; // reset farby na zakladne
}

UJTyp Aplikacia::prelozNaUJTyp(wstring naPreklad) {
    if (naPreklad.compare(L"Stat") == 0) {
        return UJTyp::Stat;
    } else if (naPreklad.compare(L"Kraj") == 0) {
        return UJTyp::Kraj;
    } else if (naPreklad.compare(L"Okres") == 0) {
        return UJTyp::Okres;
    } else if (naPreklad.compare(L"Obec") == 0) {
        return UJTyp::Obec;
    } else if (naPreklad.compare(L"") == 0){
        return UJTyp::Neoznacene;
    } else {
        changeColor(Color::Red);
        cout << "Zle zadany parameter UJ typu, budem tento filter ignorovať!";
        resetColor();
        return UJTyp::Neoznacene;
    }
}
