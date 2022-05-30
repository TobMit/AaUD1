#pragma once

#include <sstream>
#include "string"
#include "../structures/list/array_list.h"

enum class UJTyp {
    Stat,
    Kraj,
    Okres,
    Obec,
    Neoznacene
};

using namespace std;

///Virtualny trieda ktorú bude dedit kazda trieda ktora uchovava ulozene data
class StoredData {
public:
    StoredData();
    /// destruktor
    virtual ~StoredData();
    /// vrati klus ktory sa bude pouzivat v tabulke
    virtual string getCode() const = 0;
    /// vráti vráti officialny nazov
    virtual string getOfficialTitle() const = 0;
    /// nastavy klúč
    virtual void setCode(const string pCode) = 0;
    /// nastavy officialne meno uzemnej jednotky
    virtual void setOfficialTitle(const string pOffTitleName) = 0;
    /// bude nastavovať všetky paramtetre ktoré treba
    virtual void setNextParameter(const string parameter) = 0;
    /// Vráti veľkosť ktorá sa dá prechádzať pomocou At()
    virtual int getSize() = 0;
    /// Nastavi pointer na vzdelávanie danej UJ. Pre OstatneUdaje je to null ptr.
    /// \param pVzdelanie - Vzdelávanie danej územnej jednotky.
    virtual void setVzdelavanie(StoredData *pVzdelanie) = 0;
    /// Vráti príslušné vzdlávanie ak je nastavené
    /// \return - Pointer na vzedlávanie.
    virtual StoredData* getVzdelavanie() const =0;
    /// Viem prechádzať všetky údaje ktoré boli zadané. V prípade OstatnyUdajov prechadzam všetky data ktore su ulozene v ArrListe
    /// \param index - Index položky ktorú chcem sprístupniť.
    /// \return Vráti string& danej položky.
    virtual string& at(int index) = 0;
    /// operator prístupu
    string operator[](int index) {
        return this->at(index);
    }
    /// Typ ktorým je objekt
    /// \return Vráti UJTyp ktorým je objekt
    virtual UJTyp getUJTyp() const = 0;
    /// Zisti ci objedk paty do zadaneho VUJ. Ak sa jedna o pomocne udaje, defaultne je false.
    /// \param VUJednotka - StoredData s ktorym sa to bude porovnnávať.
    /// \return True / false podla toho ci patri pod uzemnu jednotku.
    virtual bool belongsTo(StoredData &VUJednotka) const =0;

    /// Zisťujem či mi patrí nejaká územná územna jednotka, pre pomocne údaje defaultne false.
    /// \param NUJednotka nižšia územná jednotka.
    /// \return True / false podla toho či patrí podo mňa.
    virtual bool belongsMe(StoredData *NUJednotka) const =0;
};

inline StoredData::~StoredData() {

}

inline StoredData::StoredData() {

}



